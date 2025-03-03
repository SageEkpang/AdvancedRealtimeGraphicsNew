#include "MeshLoader.h"

using namespace std;

namespace MeshLoader
{
	// Standard OBJ loader
	void LoadVertices(ifstream& inFile, LoadMesh& mesh);
	void LoadNormals(ifstream& inFile, LoadMesh& mesh);
	void LoadIndices(ifstream& inFile, LoadMesh& mesh);
	void LoadTextureCoords(ifstream& InFile, LoadMesh& mesh);

	void LoadVertices(ifstream& inFile, LoadMesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new SimpleVertex[mesh.VertexCount];
			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].Pos.x;
				inFile >> mesh.Vertices[i].Pos.y;
				inFile >> mesh.Vertices[i].Pos.z;
			}
		}
	}

	void LoadTextureCoords(ifstream& InFile, LoadMesh& mesh)
	{
		InFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			for (int i = 0; i < mesh.TexCoordCount; ++i)
			{
				InFile >> mesh.Vertices[i].TexCoord.x;
				InFile >> mesh.Vertices[i].TexCoord.y;
			}
		}
	}

	void LoadNormals(ifstream& inFile, LoadMesh& mesh)
	{
		inFile >> mesh.NormalCount;
		if (mesh.NormalCount > 0)
		{
			for (int i = 0; i < mesh.NormalCount; ++i)
			{
				inFile >> mesh.Vertices[i].Normal.x;
				inFile >> mesh.Vertices[i].Normal.y;
				inFile >> mesh.Vertices[i].Normal.z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, LoadMesh& mesh)
	{
		// Load in index count and Indices
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.indices = new WORD[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; ++i)
			{
				inFile >> mesh.indices[i];
			}
		}
	}

	LoadMesh* MeshLoader::Load(char* path)
	{
		LoadMesh* mesh = new LoadMesh();

		ifstream InFile;

		InFile.open(path);

		if (!InFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(InFile, *mesh);
		LoadTextureCoords(InFile, *mesh);
		LoadNormals(InFile, *mesh);
		LoadIndices(InFile, *mesh);

		InFile.close();
		return mesh;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void LoadOBJContent(ifstream& InFile, LoadMesh& mesh);

	void LoadOBJContent(ifstream& InFile, LoadMesh& mesh)
	{
		// File Variables
		std::string MeshReadData{};
		std::ifstream MaterialInFile;
		std::string MaterialReadData{};

		// Counting Contents Variables
		unsigned int VerticesCount{};
		unsigned int VertexNormalCount{};
		unsigned int VertexTextureCount{};
		unsigned int FCount{};

		// Vertex, Normals and Texture Array
		XMFLOAT3 Pos = XMFLOAT3();
		XMFLOAT3 Normals = XMFLOAT3();
		XMFLOAT2 Tex = XMFLOAT2();

		std::vector < XMFLOAT3 > PositionArray;
		std::vector < XMFLOAT3 > NormalsArray;
		std::vector < XMFLOAT2 > TextureArray;

		// Face Vertex, Normals and Textures
		XMFLOAT3 FVer;
		XMFLOAT3 FVerNorm;
		XMFLOAT3 FVerT;

		std::vector < unsigned int > FIndices, NIndices, TIndices;


		while (!InFile.eof())
		{
			if (InFile.eof())
				break;

			std::getline(InFile, MeshReadData);

			if (MeshReadData[0] == 'v' && MeshReadData[1] == ' ')
			{
				++VerticesCount;
				sscanf_s(MeshReadData.c_str(), "v %f %f %f", &Pos.x, &Pos.y, &Pos.z);
				PositionArray.push_back(Pos);
			}

			if (MeshReadData[0] == 'v' && MeshReadData[1] == 't')
			{
				++VertexTextureCount;
				sscanf_s(MeshReadData.c_str(), "vt %f %f", &Tex.x, &Tex.y);
				TextureArray.push_back(Tex);
			}

			if (MeshReadData[0] == 'v' && MeshReadData[1] == 'n')
			{
				++VertexNormalCount;
				sscanf_s(MeshReadData.c_str(), "vn %f %f %f", &Normals.x, &Normals.y, &Normals.z);
				NormalsArray.push_back(Normals);
			}

			if (MeshReadData[0] == 'f' && MeshReadData[1] == ' ')
			{
				++FCount;
				sscanf_s(MeshReadData.c_str(), "f %f/%f/%f %f/%f/%f %f/%f/%f", &FVer.x, &FVerT.x, &FVerNorm.x, &FVer.y, &FVerT.y, &FVerNorm.y, &FVer.z, &FVerT.z, &FVerNorm.z);

				FIndices.push_back(FVer.x);
				FIndices.push_back(FVer.y);
				FIndices.push_back(FVer.z);

				NIndices.push_back(FVerNorm.x);
				NIndices.push_back(FVerNorm.y);
				NIndices.push_back(FVerNorm.z);

				TIndices.push_back(FVerT.x);
				TIndices.push_back(FVerT.y);
				TIndices.push_back(FVerT.z);
			}
		}

		mesh.VertexCount = VerticesCount;
		mesh.TexCoordCount = VertexTextureCount;
		mesh.NormalCount = VertexNormalCount;
		mesh.IndexCount = (FCount * 3);

		// Load Indices for Mesh
		if (mesh.IndexCount > 0)
		{
			mesh.indices = new WORD[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; ++i)
			{
				mesh.indices[i] = i;
			}
		}

		// Load Vertices for Mesh
		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new SimpleVertex[mesh.IndexCount];
			for (int i = 0; i < mesh.IndexCount; ++i)
			{
				mesh.Vertices[i].Pos = PositionArray[FIndices[i] - 1];
				mesh.Vertices[i].biTangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
				mesh.Vertices[i].tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
			}
		}

		// Load Texture for Mesh
		if (mesh.TexCoordCount > 0)
		{
			for (int i = 0; i < mesh.IndexCount; ++i)
			{
				mesh.Vertices[i].TexCoord = (TextureArray[TIndices[i] - 1]);
			}
		}

		// Load Normals for Mesh
		if (mesh.NormalCount > 0)
		{
			for (int i = 0; i < mesh.IndexCount; ++i)
			{
				mesh.Vertices[i].Normal = NormalsArray[NIndices[i] - 1];
			}
		}
	}

	LoadMesh* LoadObj(char* path)
	{
		LoadMesh* mesh = new LoadMesh();

		ifstream InFile;

		InFile.open(path);

		if (!InFile.good())
		{
			std::cerr << "Can not open OBJ File: " << path << endl;
			return mesh;
		}

		// Please Work
		LoadOBJContent(InFile, *mesh);

		InFile.close();
		return mesh;
	}

}