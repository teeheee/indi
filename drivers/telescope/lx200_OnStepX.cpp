#include "lx200_OnStepX.h"

#include <memory>

static std::unique_ptr<LX200_OnStepX> lx200_onstepx(new LX200_OnStepX());

LX200_OnStepX::LX200_OnStepX()
{
    setVersion(2, 1);

    currentSiteNum = 1;
    trackingMode   = TRACK_SIDEREAL;
    GuideNSTID     = 0;
    GuideWETID     = 0;

    DBG_SCOPE = INDI::Logger::getInstance().addDebugLevel("Scope Verbose", "SCOPE");

    setLX200Capability( LX200_HAS_TRACKING_FREQ | LX200_HAS_ALIGNMENT_TYPE | LX200_HAS_SITES |
                       LX200_HAS_PULSE_GUIDING);

    SetTelescopeCapability(TELESCOPE_CAN_PARK | TELESCOPE_CAN_SYNC | TELESCOPE_CAN_GOTO | TELESCOPE_CAN_ABORT |
                           TELESCOPE_HAS_TIME | TELESCOPE_HAS_LOCATION | TELESCOPE_HAS_TRACK_MODE,
                           4);

    int arbitrary_number_of_focusers = 3;

    for(int i = 0; i < arbitrary_number_of_focusers; i++)
    {
        lx200_onstepx_focuser_list.push_front((std::unique_ptr<LX200_OnStepX_Focuser>)new LX200_OnStepX_Focuser(focuser_names[i]));
    }
    lx200_onstepx_rotator.reset(new LX200_OnstepX_rotator());

    LOG_DEBUG("Initializing from Generic LX200 device...");
}


const char *LX200_OnStepX::getDefaultName()
{
    return "Onstep_Telescope";
}


bool LX200_OnStepX::Connect() 
{
    for (auto const& focuser : lx200_onstepx_focuser_list) 
    {
        focuser->setConnected(true, IPS_OK);
    }
    lx200_onstepx_rotator->setConnected(true, IPS_OK);
    return true;
}

bool LX200_OnStepX::Disconnect() 
{
    for (auto const& focuser : lx200_onstepx_focuser_list) 
    {
        focuser->setConnected(false, IPS_OK);
    }
    lx200_onstepx_rotator->setConnected(false, IPS_OK);
    return true;
}