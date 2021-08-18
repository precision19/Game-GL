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
	canSlide = 0;
	onTheGround = 1;
	m_SpeedX = 200.0f;
	m_SlideSpeed = -80.0f;
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
	foot->SetPosition(Vector3(GetPosition().x, GetPosition().y - m_ColliderSize + 0.1f, GetPosition().z));
	foot->CreateCollider();

	left = new Sensor(SIDE);
	left->SetCollider(0.1f);
	left->SetPosition(Vector3(GetPosition().x - m_ColliderSize +0.1f, GetPosition().y, GetPosition().z));
	left->CreateCollider();

	right = new Sensor(SIDE);
	right->SetCollider(0.1f);
	right->SetPosition(Vector3(GetPosition().x + m_ColliderSize-0.1f, GetPosition().y, GetPosition().z));
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
	DynamicBox* db = (DynamicBox*)m_Collider;
	SetPosition(Vector3(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y, GetPosition().z));

	UpdateSensorOfPlayer(deltaTime);
	ConsiderJumpAndSlide();
	//printf("%f %f\n", db->GetVelocity().x, db->GetVelocity().y);
	HandleJumpAndSlide();
	
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

void Player::ConsiderJumpAndSlide() {
	if (foot->GetNumContact()) canJump = 1;
	else canJump = 0;

	if (left->GetNumContact()) {
		canSlide = 1;
		printf("Collision with right side of block\n");
	}

	else if (right->GetNumContact()) {
		canSlide = 1;
		printf("Collision with left side of block\n");
	}
	else canSlide = 0;
}

void Player::HandleJumpAndSlide() {
	DynamicBox* db = (DynamicBox*)m_Collider;
	if (canSlide && !canJump) onTheGround = 0;
	else if (canJump && !onTheGround && db->GetVelocity().y < 0) onTheGround = 1;
	if (canJump) {
		if (Input::GetTouch()) {
			float impulse;
			if(canSlide) impulse = db->getBody()->GetMass() * 270;
			else impulse = db->getBody()->GetMass() * 170;
			db->ApplyForce(Vector2(0.0f, impulse));
			onTheGround = 0;
			Input::SetTouchStatus(false);
		}
	}
	else if (Input::GetTouch() && canSlide && !onTheGround) {
		Input::SetTouchStatus(false);
		float impulse = db->getBody()->GetMass() * 224;
		db->ApplyForce(Vector2(0.0f, impulse));
		SetSpeed(-m_SpeedX);
	}
	else if (canSlide && db->GetVelocity().y < 0) {
		db->SetVelocity(Vector2(m_SpeedX, m_SlideSpeed));
	}

	db->SetVelocity(Vector2(m_SpeedX, db->GetVelocity().y));
}