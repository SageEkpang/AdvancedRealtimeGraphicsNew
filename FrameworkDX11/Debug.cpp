#include "Debug.h"

namespace Debug
{
	void PrintGeneral(const char* message)
	{
		printf("\n");
		printf(message);
	}

	void PrintLight(Light light)
	{
		light.Color;
		light.ConstantAttenuation;
		light.Direction;
		light.Enabled;
		light.LightType;
		light.LinearAttenuation;
		light.Position;
		light.QuadraticAttenuation;
		light.SpotAngle;

		printf("\n");
		printf("Light Position: x(%f), y(%f), z(%f), w(%f)", light.Position.x, light.Position.y, light.Position.z, light.Position.w);
		printf("Light Colour: r(%f), g(%f), b(%f), w(%f)\n", light.Color.x, light.Color.y, light.Color.z, light.Color.w);
		printf("Light Direction: x(%f), y(%f), z(%f), w(%f)", light.Direction.x, light.Direction.y, light.Direction.z, light.Direction.w);

		printf("Constant Attenuation: (%f)", light.ConstantAttenuation);
		printf("Linear Attenuation: %f", light.LinearAttenuation);
		printf("Quadratic Attenuation: %f", light.QuadraticAttenuation);
		printf("Spot Angle: %f", light.SpotAngle);

		printf("Light Enabled: %d", light.Enabled);
		printf("Light Type: %d", light.LightType);
	}

	void PrintMaterial(_Material material)
	{
		material.Ambient;
		material.Diffuse;
		material.Emissive;
		material.Specular;
		material.SpecularPower;
		material.UseTexture;

		printf("\n");
		printf("Ambient: x(%f), y(%f), z(%f), w(%f)\n", material.Ambient.x, material.Ambient.y, material.Ambient.z, material.Ambient.w);
		printf("Diffuse: x(%f), y(%f), z(%f), w(%f)\n", material.Diffuse.x, material.Diffuse.y, material.Diffuse.z, material.Diffuse.w);
		printf("Emissive: x(%f), y(%f), z(%f), w(%f)\n", material.Emissive.x, material.Emissive.y, material.Emissive.z, material.Emissive.w);
		printf("Specular: x(%f), y(%f), z(%f), w(%f)\n", material.Specular.x, material.Specular.y, material.Specular.z, material.Specular.w);

		printf("Specular Power: %f\n", material.SpecularPower);
		printf("Use Texture: %d\n", material.UseTexture);
	}

	void PrintVertex(SimpleVertex simpleVertex)
	{
		simpleVertex.biTangent;
		simpleVertex.Normal;
		simpleVertex.Pos;
		simpleVertex.tangent;
		simpleVertex.TexCoord;

		printf("\n");
		printf("Vertex Position: x(%f), y(%f), z(%f)", simpleVertex.Pos.x, simpleVertex.Pos.y, simpleVertex.Pos.z);
		printf("Vertex Normal: x(%f), y(%f), z(%f)", simpleVertex.Normal.x, simpleVertex.Normal.y, simpleVertex.Normal.z);
		printf("Texture Coordinates: x(%f), y(%f)", simpleVertex.TexCoord.x, simpleVertex.TexCoord.y);

		printf("Bi Tangent: x(%f), y(%f), z(%f)", simpleVertex.biTangent.x, simpleVertex.biTangent.y, simpleVertex.biTangent.z);
		printf("Tangent: x(%f), y(%f), z(%f)", simpleVertex.tangent.x, simpleVertex.tangent.y, simpleVertex.tangent.z);
	}
};