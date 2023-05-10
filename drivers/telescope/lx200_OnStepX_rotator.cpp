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

#include "lx200_OnStepX_rotator.h"
#include "indicom.h"

#include <memory>
#include <cmath>
#include <math.h>



LX200_OnstepX_rotator::LX200_OnstepX_rotator()
{
    setRotatorConnection(CONNECTION_NONE);
    SetCapability(ROTATOR_CAN_ABORT | ROTATOR_CAN_SYNC | ROTATOR_CAN_REVERSE);
}

const char * LX200_OnstepX_rotator::getDefaultName()
{
    return "Onstep_Rotator";
}


bool LX200_OnstepX_rotator::initProperties()
{
    // initialize the parent's properties first
    INDI::Rotator::initProperties();

    setConnected(true, IPS_OK);
    updateProperties();   

    return true;
}

bool LX200_OnstepX_rotator::Connect()
{
    return true;
}

bool LX200_OnstepX_rotator::Disconnect()
{
    return true;
}

IPState LX200_OnstepX_rotator::MoveRotator(double angle)
{
    return IPS_BUSY;
}

bool LX200_OnstepX_rotator::SyncRotator(double angle)
{
    INDI_UNUSED(angle);
    return true;
}

bool LX200_OnstepX_rotator::AbortRotator()
{
    return true;
}

bool LX200_OnstepX_rotator::ReverseRotator(bool enabled)
{
    INDI_UNUSED(enabled);
    return true;
}
