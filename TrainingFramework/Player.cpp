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
	m_Renderer = NULL;
	m_currentAnimationId = 0;
	canJump = 0;
	canSlide = 0;
	onTheGround = 1;
	m_SpeedX = 100.0f;
	m_SlideSpeed = -80.0f;
	m_IsRunning = false;
	m_JumpForce = 300;
	foot = NULL;
	left = NULL;
	right = NULL;
	m_ReadyForInput = true;
}

void Player::CreateCollider()
{
	if (m_Collider == NULL)
	{
		m_Collider = new DynamicBox(this, m_ColliderSize, CATEGORY_PLAYER);
		((DynamicBox*)m_Collider)->getBody()->SetGravityScale(0);;
		m_GatePosition = m_Transform.position;
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

void Player::Reset()
{
	((DynamicBox*)m_Collider)->getBody()->SetTransform(b2Vec2(m_GatePosition.x, m_GatePosition.y), 0.0f);
	((DynamicBox*)m_Collider)->getBody()->SetGravityScale(0);;
	((DynamicBox*)m_Collider)->SetVelocity(Vector2());
	m_IsRunning = false;
	m_ReadyForInput = false;
}

void Player::SetSpeed(float speed)
{
	m_SpeedX = speed;
}

void Player::SetJumpForce(float jumpForce)
{
	m_JumpForce = jumpForce;
}

void Player::SetRenderer(string name)
{
	Renderer* renderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
	m_Animations.push_back(renderer);
	if (m_Renderer == NULL)
		m_Renderer = renderer;
}

void Player::Update(float deltaTime)
{
	if (!Input::GetTouch()) m_ReadyForInput = true;

	UpdateAnimation(deltaTime);
	m_Renderer->Update(deltaTime);
	UpdateSensorOfPlayer(deltaTime);

	DynamicBox* db = (DynamicBox*)m_Collider;
	SetPosition(Vector3(db->getBody()->GetPosition().x, db->getBody()->GetPosition().y, GetPosition().z));

	if (!m_IsRunning)
	{
		if (Input::GetTouch() && m_ReadyForInput)
		{
			m_IsRunning = true;
			m_ReadyForInput = false;
			((DynamicBox*)m_Collider)->getBody()->SetGravityScale(1);;
		}
		else
			return;
	}

	ConsiderJumpAndSlide();
	//printf("%f %f\n", db->GetVelocity().x, db->GetVelocity().y);
	HandleJumpAndSlide();
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

void Player::UpdateAnimation(float deltaTime)
{
	DynamicBox* db = ((DynamicBox*)m_Collider);
	Vector2 velocity = db->GetVelocity();

	if (canJump)
	{
		if (db->GetVelocity().x > 1)
		{
			m_Renderer = m_Animations.at(1);
		}
		else 
			m_Renderer = m_Animations.at(0);
	}
	else
	{
		if (velocity.y > 0)
			m_Renderer = m_Animations.at(2);
		else
			m_Renderer = m_Animations.at(3);
	}

	if (velocity.x > 1 && !m_IsFacingRight)
	{
		m_Transform.rotation.y += PI;
		m_IsFacingRight = true;
	}
	else if (velocity.x < -1 && m_IsFacingRight)
	{
		m_Transform.rotation.y -= PI;
		m_IsFacingRight = false;
	}
}

void Player::OnColliderEnter(GameObject* other) 
{
	if (other->m_Name == "Saw Blade" || other->m_Name == "Guard")
	{
		EventManager::GetInstance()->InvokeEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_DIE);
	}

	if (other->m_Name == "Chest")
	{
		EventManager::GetInstance()->InvokeEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_WIN);
	}
}

void Player::OnColliderExit(GameObject* other) 
{
	
}

Player::~Player()
{
	for each (Renderer * renderer in m_Animations)
		delete renderer;
	m_Renderer = NULL;
	if (foot) delete foot;
	if (left) delete left;
	//if (right) delete right;
}

void Player::ConsiderJumpAndSlide() {
	if (foot->GetNumContact()) canJump = 1;
	else canJump = 0;

	if (left->GetNumContact())
		canSlide = 1;
	else if (right->GetNumContact())
		canSlide = 1;
	else 
		canSlide = 0;
}

void Player::HandleJumpAndSlide() {
	DynamicBox* db = (DynamicBox*)m_Collider;
	if (canSlide && !canJump)
		onTheGround = 0;
	else if (canJump && !onTheGround && db->GetVelocity().y < 0)
		onTheGround = 1;
	if (canJump)
	{
		if (Input::GetTouch() && m_ReadyForInput)
		{
			if (canSlide)
				db->SetVelocity(Vector2(0.0, m_JumpForce * 1.2));
			else
				db->SetVelocity(Vector2(0.0, m_JumpForce));

			onTheGround = 0;
			AudioManager::GetInstance()->PlaySoundEffect("Jump", false);
			//Input::SetTouchStatus(false);
			m_ReadyForInput = false;
		}
	}
	else if (Input::GetTouch() && m_ReadyForInput && canSlide && !onTheGround)
	{
		//Input::SetTouchStatus(false);
		m_ReadyForInput = false;
		db->SetVelocity(Vector2(0.0, m_JumpForce));
		AudioManager::GetInstance()->PlaySoundEffect("Jump", false);
		SetSpeed(-m_SpeedX);
	}
	else if (canSlide && db->GetVelocity().y < 0) 
	{
		db->SetVelocity(Vector2(m_SpeedX, m_SlideSpeed));
	}

	db->SetVelocity(Vector2(m_SpeedX, db->GetVelocity().y));
}

void Player::Stop()
{
	m_IsRunning = false;
	((DynamicBox*)m_Collider)->SetVelocity(Vector2());
	((DynamicBox*)m_Collider)->getBody()->SetGravityScale(0);
}

void Player::Die()
{
	m_Renderer = m_Animations.at(4);
	Stop();
	m_Enable = false;
}
