#pragma once
#ifndef FLOAT_MATHS
#define FLOAT_MATHS

#include "structures.h"
#include "constants.h"

namespace FloatMaths
{
	float* XMFLOAT2toFloatArray(XMFLOAT2 value);
	float* XMFLOAT3toFloatArray(XMFLOAT3 value);
	float* XMFLOAT4toFloatArray(XMFLOAT4 value);
};

#endif