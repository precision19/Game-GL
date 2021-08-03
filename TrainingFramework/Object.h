#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Component.h"

class Object
{
protected: 
	int m_modelId;
	vector<int> m_TextureIds;
	vector<int> m_CubeTextureIds;
	int m_shadersId;

	Model* m_Model;
	Texture* m_Texture;
	vector<Texture*> m_Textures;
	Shaders* m_Shaders;

	Sprite* m_Sprite;
	int m_spriteId;

	Vector3 m_Scale;
	Vector3 m_Rotation;
	Vector3 m_Position;

	Matrix GetWVP(Camera*);

	vector<Component*> m_Components;
public:
	Transform* transform;

	Object();
	void Init(ResourceManager* resource);
	void SetSpriteId(int);
	void SetNativeSize();
	void SetModelId(int);
	void SetTextureId(int);
	void SetTextureCubeId(int);
	void SetShadersId(int);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	Vector3 GetPosition();
	void SetPosition(Vector3);
	void Draw(Camera*);
	void Update(float);
	~Object();
};

