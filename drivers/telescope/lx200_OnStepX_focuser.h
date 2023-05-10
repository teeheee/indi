#pragma once

#include "indifocuser.h"

class LX200_OnStepX_Focuser : public INDI::Focuser
{
    public:
        LX200_OnStepX_Focuser(const char* name);
        virtual ~LX200_OnStepX_Focuser() = default;
        virtual const char *getDefaultName() override;
        virtual bool initProperties() override;

    protected:
        // Device Override
        virtual bool Connect() override;
        virtual bool Disconnect() override;

        virtual IPState MoveFocuser(FocusDirection dir, int speed, uint16_t duration);
        virtual IPState MoveAbsFocuser(uint32_t targetTicks);
        virtual IPState MoveRelFocuser(FocusDirection dir, uint32_t ticks);
        virtual bool AbortFocuser();

        const char* default_name;
};