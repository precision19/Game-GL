#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "ResourceManager.h"

class Object
{
protected: 
	int m_modelId;
	int m_textureId;
	vector<int> m_TextureIds;
	int m_textureCubeId;
	vector<int> m_CubeTextureIds;
	int m_shadersId;

	Model* m_Model;
	Texture* m_Texture;
	vector<Texture*> m_Textures;
	Shaders* m_Shaders;

	Vector3 m_Scale;
	Vector3 m_Rotation;
	Vector3 m_Translation;

	Matrix GetWVP();
public:
	Object();
	void Init();
	Object(const char*, const char*);
	void SetModelId(int);
	void SetTextureId(int);
	void SetTextureCubeId(int);
	void SetShadersId(int);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	void SetTranslation(Vector3);
	void Draw();
	void Update(float);
	~Object();
};

