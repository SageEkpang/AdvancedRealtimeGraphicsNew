#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include "constants.h"
#include "structures.h"

namespace Debug
{
	void PrintGeneral(const char* message);
	void PrintLight(Light light);
	void PrintMaterial(_Material material);
	void PrintVertex(SimpleVertex simpleVertex);

};

#endif