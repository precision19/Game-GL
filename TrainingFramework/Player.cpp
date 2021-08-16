#include "stdafx.h"
#include "Player.h"
#include "DynamicBox.h"
#include "GroundBox.h"
#include "Sensor.h"

Player::Player()
{
	m_Name = "Player";
	m_ID = ms_IDMaker;
	ms_IDMaker++;
	m_Collider = NULL;
	m_currentAnimationId = 0;
	canJump = 0;
	canSurf = 0;
	surf = 0;
	m_SpeedX = 70.0f;
}

void Player::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_PLAYER);
	}
	else
	{
		printf("%s already has a collider", m_Name.c_str());
	}
	CreateSensorCollider();
}

void Player::CreateSensorCollider() {
	foot = new Sensor(FOOT);
	foot->SetCollider(0.1f);
	foot->SetPosition(Vector3(GetPosition().x, GetPosition().y - m_ColliderSize, GetPosition().z));
	foot->CreateCollider();

	left = new Sensor(SIDE);
	left->SetCollider(0.1f);
	left->SetPosition(Vector3(GetPosition().x - m_ColliderSize, GetPosition().y, GetPosition().z));
	left->CreateCollider();

	right = new Sensor(SIDE);
	right->SetCollider(0.1f);
	right->SetPosition(Vector3(GetPosition().x + m_ColliderSize, GetPosition().y, GetPosition().z));
	right->CreateCollider();
}

void Player::SetSpeed(float speed)
{
	m_SpeedX = speed;
}

void Player::SetJumpForce(float jumpForce)
{
	m_JumpForce = jumpForce;
}

void Player::AddAnimation(Renderer* renderer)
{
	m_Animations.push_back(renderer);
	if (m_Renderer == NULL)
		m_Renderer = renderer;
}

void Player::Update(float deltaTime)
{
	Vector2 gravity = Vector2(Physic::GetInstance()->GetWorld()->GetGravity().x, Physic::GetInstance()->GetWorld()->GetGravity().y);
	DynamicBox* db = (DynamicBox*)m_Collider;
	SetPosition(Vector3(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y, GetPosition().z));

	UpdateSensorOfPlayer(deltaTime);

	if (foot->GetNumContact()) canJump = 1;
	else canJump = 0;
	
	if (left->GetNumContact()) {
		canSurf = 1;
		printf("Collision with right side of block\n");
	}
	else if (right->GetNumContact()) {
		canSurf = 1;
		printf("Collision with left side of block\n");
	}
	else canSurf = 0;

	if (!canSurf) surf = 0;
	if (surf) {
		float impulse = db->getBody()->GetMass() * 1000;
		db->ApplyForce(Vector2(0.0f, impulse));
		if (Input::GetTouch()) {
			surf = 0;
			SetSpeed(-m_SpeedX);
		}
	}
	else {
		if (Input::GetTouch() && canSurf > 0 && surf == 0) {
			surf = 1;
		}
		else if (Input::GetTouch() && canJump)
		{
			float impulse = db->getBody()->GetMass() * 1000;
			db->ApplyForce(Vector2(0.0f, impulse));
		}
	}
	db->SetVelocity(Vector2(m_SpeedX, db->GetVelocity().y));

	m_Renderer->Update(deltaTime);
}

void Player::UpdateSensorOfPlayer(float deltaTime) {
	DynamicBox* db = (DynamicBox*)m_Collider;
	DynamicBox* fdb = (DynamicBox*)(foot->GetColliderBox());
	DynamicBox* ldb = (DynamicBox*)(left->GetColliderBox());
	DynamicBox* rdb = (DynamicBox*)(right->GetColliderBox());

	fdb->getBody()->SetTransform(b2Vec2(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y - m_ColliderSize), 0.0f);
	ldb->getBody()->SetTransform(b2Vec2(db->getBody()->GetPosition().x - m_ColliderSize, db->getBody()->GetPosition().y), 0.0f);
	rdb->getBody()->SetTransform(b2Vec2(db->getBody()->GetPosition().x + m_ColliderSize, db->getBody()->GetPosition().y), 0.0f);
}

void Player::OnColliderEnter(GameObject* other) {
	
}

void Player::OnColliderExit(GameObject* other) {
	
}

Player::~Player()
{
	delete foot;
	delete left;
	delete right;
}