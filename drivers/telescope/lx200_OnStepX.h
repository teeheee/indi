#pragma once

#include "lx200_OnStepX_focuser.h"
#include "lx200_OnStepX_rotator.h"

#include "lx200telescope.h"

#include <list>

class LX200_OnStepX: public LX200Telescope
{
    public:
        LX200_OnStepX();
        virtual ~LX200_OnStepX() override = default;
      
        virtual const char *getDefaultName() override;

    protected:
        
        virtual bool Connect() override;
        virtual bool Disconnect() override;

        std::list<std::unique_ptr<LX200_OnStepX_Focuser>> lx200_onstepx_focuser_list;
        std::unique_ptr<LX200_OnstepX_rotator> lx200_onstepx_rotator;
        
        const char* focuser_names[9] = {
            "Onstep_Focuser1",
            "Onstep_Focuser2",
            "Onstep_Focuser3",
            "Onstep_Focuser4",
            "Onstep_Focuser5",
            "Onstep_Focuser6",
            "Onstep_Focuser7",
            "Onstep_Focuser8",
            "Onstep_Focuser9"
        };
};
