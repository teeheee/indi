#ifndef _LX200_ONSTEP_SERIAL_H_
#define _LX200_ONSTEP_SERIAL_H_

#include "lx200generic.h"
#include "lx200driver.h"
#include "indicom.h"
#include "indifocuserinterface.h"
#include "indiweatherinterface.h"
#include "indirotatorinterface.h"
#include "connectionplugins/connectiontcp.h"


#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <mutex>

#define RB_MAX_LEN 64
#define CMD_MAX_LEN 32

#define PORTS_COUNT 10
#define STARTING_PORT 0

enum ResponseErrors {RES_ERR_FORMAT = -1001};

enum Errors {ERR_NONE, ERR_MOTOR_FAULT, ERR_ALT_MIN, ERR_LIMIT_SENSE, ERR_DEC, ERR_AZM, ERR_UNDER_POLE, ERR_MERIDIAN, ERR_SYNC, ERR_PARK, ERR_GOTO_SYNC, ERR_UNSPECIFIED, ERR_ALT_MAX, ERR_GOTO_ERR_NONE, ERR_GOTO_ERR_BELOW_HORIZON, ERR_GOTO_ERR_ABOVE_OVERHEAD, ERR_GOTO_ERR_STANDBY, ERR_GOTO_ERR_PARK, ERR_GOTO_ERR_GOTO, ERR_GOTO_ERR_OUTSIDE_LIMITS, ERR_GOTO_ERR_HARDWARE_FAULT, ERR_GOTO_ERR_IN_MOTION, ERR_GOTO_ERR_UNSPECIFIED};
enum RateCompensation {RC_NONE, RC_REFR_RA, RC_REFR_BOTH, RC_FULL_RA, RC_FULL_BOTH}; //To allow for using one variable instead of two in the future

enum MountType {MOUNTTYPE_GEM, MOUNTTYPE_FORK, MOUNTTYPE_FORK_ALT, MOUNTTYPE_ALTAZ};

enum OnStepVersion {OSV_UNKNOWN, OSV_OnStepV1or2, OSV_OnStepV3, OSV_OnStepV4, OSV_OnStepV5, OSV_OnStepX};


class LX200_Onstep_Serial
{
    public: 
        LX200_Onstep_Serial();
        bool sendOnStepCommandBlind(const char *cmd);
        bool sendOnStepCommand(const char *cmd);
        int getCommandSingleCharResponse(int fd, char *data, const char *cmd);
        int getCommandDoubleResponse(int fd, double *value, char *data, const char *cmd);
        int getCommandIntResponse(int fd, int *value, char *data, const char *cmd);
        int getCommandSingleCharErrorOrLongResponse(int fd, char *data, const char *cmd);
        const char *getDeviceName()
        {
            return m_DeviceName.c_str();
        };
    protected:
        int flushIO(int fd);
        long int OSTimeoutSeconds = 0;
        long int OSTimeoutMicroSeconds = 100000;
        std::string m_DeviceName = "Onstep";
        std::mutex lx200CommsLock;  
        unsigned int DBG_SCOPE;
        int PortFD                           = -1;
};

#endif