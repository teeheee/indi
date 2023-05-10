
#pragma once

#include "indifocuser.h"

class LX200_OnStep_Focuser : public INDI::Focuser
{
    public:
        LX200_OnStep_Focuser(int PortFD, int id);
        virtual const char *getDefaultName() override;

    protected:
        virtual bool Connect() override;
        virtual bool Disconnect() override;
        virtual bool initProperties() override;
        virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;
        
        virtual IPState MoveFocuser(FocusDirection dir, int speed, uint16_t duration) override;
        virtual IPState MoveAbsFocuser(uint32_t targetTicks) override;
        virtual IPState MoveRelFocuser(FocusDirection dir, uint32_t ticks) override;
        
    private:
        
        bool sendOnStepCommandBlind(const char *cmd);
        int flushIO(int fd);

        int PortFD;
        int focuser_id;
        const char* focuser_names[9] = {
            "onstep_focuser_1",
            "onstep_focuser_2",
            "onstep_focuser_3",
            "onstep_focuser_4",
            "onstep_focuser_5",
            "onstep_focuser_6",
            "onstep_focuser_7",
            "onstep_focuser_8",
            "onstep_focuser_9"
        };
};
