#pragma once

#include "../GameEngine.h"
#include "fbxsdk.h"


typedef struct _tagFbxMaterial
{
	Vector4			Dif;
	Vector4			Amb;
	Vector4			Spc;
	Vector4			Emv;
	float			SpecularPower;
	float			TransparencyFactor;
	float			Shininess;
	std::string		DifTex;
	std::string		BumpTex;
	std::string		SpcTex;
}FBXMATERIAL, * PFBXMATERIAL;

typedef struct _tagFBXMeshContainer
{
	std::vector<Vector3>	vecPos;
	std::vector<Vector3>	vecNormal;
	std::vector<Vector2>	vecUV;
	std::vector<Vector3>	vecTangent;		// Á¢¼±º¤ÅÍ
	std::vector<Vector3>	vecBinormal;	// Á¾¹ý¼±º¤ÅÍ
	//std::vector<Vector4>	vecBlendWeight;
	//std::vector<Vector4>	vecBlendIndex;
	std::vector<std::vector<UINT>>	vecIndices;
	//std::unordered_map<int, vector<FBXWEIGHT>>	mapWeights;
	bool				Bump;
	bool				Animation;

	_tagFBXMeshContainer()
	{
		Bump = false;
		Animation = false;
	}
}FBXMESHCONTAINER, * PFBXMESHCONTAINER;


class CFBXLoader
{
	friend class CMesh;
	friend class CStaticMesh;
	friend class CAnimationMesh;

private:
	CFBXLoader();
	~CFBXLoader();

private:
	FbxManager* m_Manager;
	FbxScene* m_Scene;

private:
	std::vector<std::vector<PFBXMATERIAL>>	m_vecMaterials;

public:
	bool LoadFBX(const char* FullPath, bool Static = true);

private:
	void Triangulate(FbxNode* pNode);
	void LoadMaterial(FbxSurfaceMaterial* pMtrl);
};

