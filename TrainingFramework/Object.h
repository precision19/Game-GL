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
	Transform m_Transform;
	Renderer* m_Renderer;
	string m_Name;
public:
	Object();
	Object(string);
	virtual Object* Clone();

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
	void Draw();
	void Draw(Camera*);
	void Update(float);
	~Object();
};

