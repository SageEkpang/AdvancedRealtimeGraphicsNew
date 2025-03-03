#pragma once

#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "constants.h"
#include "structures.h"

namespace MeshLoader
{
	/// <summary> Standard Mesh Loader for namespace </summary>
	LoadMesh* Load(char* path);

	/// <summary> OBJ Mesh Loader for namespace </summary>
	LoadMesh* LoadObj(char* path);
};

#endif