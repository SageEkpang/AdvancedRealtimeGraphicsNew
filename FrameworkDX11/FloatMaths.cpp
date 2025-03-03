#include "FloatMaths.h"

namespace FloatMaths
{
	float* XMFLOAT2toFloatArray(XMFLOAT2 value)
	{
		float t_TempArray[2] = { 0 };
		t_TempArray[0] = value.x;
		t_TempArray[1] = value.y;

		return t_TempArray;
	}

	float* XMFLOAT3toFloatArray(XMFLOAT3 value)
	{
		float t_TempArray[3] = { 0 };
		t_TempArray[0] = value.x;
		t_TempArray[1] = value.y;
		t_TempArray[2] = value.z;

		return t_TempArray;
	}

	float* XMFLOAT4toFloatArray(XMFLOAT4 value)
	{
		float t_TempArray[4] = { 0 };
		t_TempArray[0] = value.x;
		t_TempArray[1] = value.y;
		t_TempArray[2] = value.z;
		t_TempArray[3] = value.w;

		return t_TempArray;
	}
}