/*
    INDI Rotator Simulator
    Copyright (C) 2020 Jasem Mutlaq (mutlaqja@ikarustech.com)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#pragma once

#include "indirotator.h"

class LX200_OnstepX_rotator : public INDI::Rotator
{
    public:

        LX200_OnstepX_rotator();
        virtual ~LX200_OnstepX_rotator() = default;
        const char * getDefaultName() override;
        virtual bool initProperties() override;

    protected:
        // Device Override
        virtual bool Connect() override;
        virtual bool Disconnect() override;
        // Rotator Overrides
        virtual IPState MoveRotator(double angle) override;
        virtual bool SyncRotator(double angle) override;
        virtual bool AbortRotator() override;

        // Misc.
        virtual bool ReverseRotator(bool enabled) override;

    private:
};
