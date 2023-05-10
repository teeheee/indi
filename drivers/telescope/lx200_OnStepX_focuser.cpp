#include <cstring>

#include "indicom.h"

#include "config.h"
#include "lx200_OnStepX_focuser.h"

LX200_OnStepX_Focuser::LX200_OnStepX_Focuser(const char* name)
{
    setVersion(1, 0);

    default_name = name;
    // Here we tell the base Focuser class what types of connections we can support
    setSupportedConnections(CONNECTION_NONE);

    // And here we tell the base class about our focuser's capabilities.
    SetCapability(FOCUSER_CAN_ABS_MOVE | FOCUSER_CAN_REL_MOVE | FOCUSER_CAN_ABORT);
}


const char *LX200_OnStepX_Focuser::getDefaultName()
{
    return default_name;
}

bool LX200_OnStepX_Focuser::initProperties()
{
    // initialize the parent's properties first
    INDI::Focuser::initProperties();

    setConnected(true, IPS_OK);
    updateProperties();   

    return true;
}


IPState LX200_OnStepX_Focuser::MoveFocuser(FocusDirection dir, int speed, uint16_t duration)
{
    // NOTE: This is needed if we don't specify FOCUSER_CAN_ABS_MOVE
    // TODO: Actual code to move the focuser. You can use IEAddTimer to do a
    // callback after "duration" to stop your focuser.
    LOGF_INFO("MoveFocuser: %d %d %d", dir, speed, duration);
    return IPS_OK;
}

IPState LX200_OnStepX_Focuser::MoveAbsFocuser(uint32_t targetTicks)
{
    // NOTE: This is needed if we do specify FOCUSER_CAN_ABS_MOVE
    // TODO: Actual code to move the focuser.
    LOGF_INFO("MoveAbsFocuser: %d", targetTicks);
    return IPS_OK;
}

IPState LX200_OnStepX_Focuser::MoveRelFocuser(FocusDirection dir, uint32_t ticks)
{
    // NOTE: This is needed if we do specify FOCUSER_CAN_REL_MOVE
    // TODO: Actual code to move the focuser.
    LOGF_INFO("MoveRelFocuser: %d %d", dir, ticks);
    return IPS_OK;
}

bool LX200_OnStepX_Focuser::AbortFocuser()
{
    // NOTE: This is needed if we do specify FOCUSER_CAN_ABORT
    // TODO: Actual code to stop the focuser.
    LOG_INFO("AbortFocuser");
    return true;
}

bool LX200_OnStepX_Focuser::Connect()
{
    return true;
}

bool LX200_OnStepX_Focuser::Disconnect()
{
    return true;
}