/*
 ==============================================================================
 
 NamespaceID.h
 Created: 31 Aug 2025 10:27:56pm
 Author:  JoEunsoo
 
 ==============================================================================
 */

#pragma once
#include "Define.h"

namespace ID {
#define PARAMETER_ID(str) static const ParameterID str { #str, 1 };

PARAMETER_ID (bypass)

PARAMETER_ID (threshold)
PARAMETER_ID (attack)
PARAMETER_ID (release)

PARAMETER_ID (tilt)

PARAMETER_ID (midSide)
PARAMETER_ID (emphasis)

PARAMETER_ID (inputGain)
PARAMETER_ID (outputGain)

PARAMETER_ID (dryWet)
PARAMETER_ID (wetSolo)
PARAMETER_ID (linkChannels)

#if ADVANCED
PARAMETER_ID (fastAttack)
PARAMETER_ID (fastRelease)
PARAMETER_ID (slowAttack)
PARAMETER_ID (slowRelease)
#endif

#undef PARAMETER_ID
}

