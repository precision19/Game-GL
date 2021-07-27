#pragma once
#include "Vertex.h"
#include "Globals.h"
#include <string>

using namespace std;

#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3

#define MOVE_UP 1 << 4
#define MOVE_DOWN 1 << 5

#define ROTATE_LEFT 1 << 6
#define ROTATE_RIGHT 1 << 7

#define LOOK_UP 1 << 8
#define LOOK_DOWN 1 << 9

class Camera
{
protected:
	static Camera * ms_Instance;

	Vector3 m_Position;
	Vector3 m_Target;
	Vector3 m_Up;

	Matrix m_WorldMatrix;
	Matrix m_ViewMatrix;
	Matrix m_Perspective;

	float m_Near;
	float m_Far;
	float m_FOV;

	float m_Speed;
	float m_RotateSpeed;

	float m_FaceAngle;

	void SetWorldMatrix();
	void SetViewMatrix();
public:
	static void CreateInstance();
	static Camera* GetInstance();
	static void DestroyInstance();

	Camera();
	Camera(Vector3, Vector3, bool);
	void Init();
	Vector3 GetPosition();
	void SetPosition(Vector3);
	void SetTarget(Vector3);
	void SetUpVector(Vector3);
	void SetFOVY(float);
	void SetNear(float);
	void SetFar(float);
	void SetMoveSpeed(float);
	void SetRotateSpeed(float);
	Matrix GetWorldMatrix();
	Matrix GetViewMatrix();
	Matrix GetPerspective();
	void Update(int, float);
};

