#include "lx200_OnStep_focuser.h"
#include "indicom.h"


#include <termios.h>
#include <unistd.h>

#define RB_MAX_LEN    64

LX200_OnStep_Focuser::LX200_OnStep_Focuser(int PortFD, int id)
{
    PortFD = PortFD;
    focuser_id = id;
    setSupportedConnections(CONNECTION_NONE);
    SetCapability(FOCUSER_CAN_ABS_MOVE | FOCUSER_CAN_REL_MOVE | FOCUSER_CAN_ABORT);

}

const char * LX200_OnStep_Focuser::getDefaultName()
{
    return focuser_names[focuser_id];
}

bool LX200_OnStep_Focuser::initProperties()
{
    INDI::Focuser::initProperties();
    setConnected(true, IPS_OK);
    updateProperties();   
    return true;
}

bool LX200_OnStep_Focuser::Connect()
{
    return true;
}

bool LX200_OnStep_Focuser::Disconnect()
{
    return true;
}

bool LX200_OnStep_Focuser::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    if (strstr(name, "CONNECT"))
    {
        LOG_INFO("connect button does not have any effect");
        return true;
    }
    else if (strstr(name, "DISCONNECT"))
    {
        LOG_INFO("disconnect button does not have any effect");
        return true;
    }
    return INDI::Focuser::ISNewSwitch(dev, name, states, names, n);
}


IPState LX200_OnStep_Focuser::MoveFocuser(FocusDirection dir, int speed, uint16_t duration)
{
    INDI_UNUSED(speed);
    //  :FRsnnn#  Set focuser target position relative (in microns)
    //            Returns: Nothing
    double output;
    char read_buffer[32];
    output = duration;
    if (dir == FOCUS_INWARD) output = 0 - output;
    snprintf(read_buffer, sizeof(read_buffer), ":FR%5f#", output);
    sendOnStepCommandBlind(read_buffer);
    return IPS_BUSY; // Normal case, should be set to normal by update.
}

IPState LX200_OnStep_Focuser::MoveAbsFocuser(uint32_t targetTicks)
{
    //  :FSsnnn#  Set focuser target position (in microns)
    //            Returns: Nothing
    if (FocusAbsPosN[0].max >= int(targetTicks) && FocusAbsPosN[0].min <= int(targetTicks))
    {
        char read_buffer[32];
        snprintf(read_buffer, sizeof(read_buffer), ":FS%06d#", int(targetTicks));
        sendOnStepCommandBlind(read_buffer);
        return IPS_BUSY; // Normal case, should be set to normal by update.
    }
    else
    {
        LOG_INFO("Unable to move focuser, out of range");
        return IPS_ALERT;
    }
}



IPState LX200_OnStep_Focuser::MoveRelFocuser(FocusDirection dir, uint32_t ticks)
{
    //  :FRsnnn#  Set focuser target position relative (in microns)
    //            Returns: Nothing
    int output;
    char read_buffer[32];
    output = ticks;
    if (dir == FOCUS_INWARD) output = 0 - ticks;
    snprintf(read_buffer, sizeof(read_buffer), ":FR%04d#", output);
    sendOnStepCommandBlind(read_buffer);
    return IPS_BUSY; // Normal case, should be set to normal by update.
}

bool LX200_OnStep_Focuser::sendOnStepCommandBlind(const char *cmd)
{
    int error_type;
    int nbytes_write = 0;


    flushIO(PortFD);

    tcflush(PortFD, TCIFLUSH);


    if ((error_type = tty_write_string(PortFD, cmd, &nbytes_write)) != TTY_OK)
    {
        LOGF_ERROR("CHECK CONNECTION: Error sending command %s", cmd);
        return 0; //Fail if we can't write
        //return error_type;
    }

    return 1;
}


int LX200_OnStep_Focuser::flushIO(int fd)
{
    tcflush(fd, TCIOFLUSH);
    int error_type = 0;
    int nbytes_read;
    tcflush(fd, TCIOFLUSH);
    do
    {
        char discard_data[RB_MAX_LEN] = {0};
        error_type = tty_read_section_expanded(fd, discard_data, '#', 0, 1000, &nbytes_read);
        if (error_type >= 0)
        {
            LOGF_DEBUG("flushIO: Information in buffer: Bytes: %u, string: %s", nbytes_read, discard_data);
        }
        //LOGF_DEBUG("flushIO: error_type = %i", error_type);
    }
    while (error_type > 0);
    return 0;
}
