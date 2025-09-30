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

PARAMETER_ID (attack)
PARAMETER_ID (release)

PARAMETER_ID (threshold)

PARAMETER_ID (bpfPower)
PARAMETER_ID (bpfFrequency)
PARAMETER_ID (sidechainListen)

PARAMETER_ID (tilt)
PARAMETER_ID (midSide)

PARAMETER_ID (noiseLevelGain)
PARAMETER_ID (outputGain)

PARAMETER_ID (dryWet)
PARAMETER_ID (wetSolo)
PARAMETER_ID (linkChannels)

#undef PARAMETER_ID
}

