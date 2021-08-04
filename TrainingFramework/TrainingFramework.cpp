// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <fstream>
#include <string>
#include <iostream>
#include "SceneManager.h"
#include "Input.h"
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"

//testBox2D
b2Vec2 gravity(0.0f, -10.0f);
b2World world(gravity);
b2Body* body;


SceneManager* LevelsMapScene;

int Init ( ESContext *esContext )
{
	Input::CreateInstance();
	Camera::CreateInstance();

	LevelsMapScene = new SceneManager("Managers/Level1");
	//testBox2D
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -450.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(500.0f, 500.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(LevelsMapScene->m_vObjects[1]->GetPosition().x, LevelsMapScene->m_vObjects[1]->GetPosition().y);
	body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );


	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LevelsMapScene->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	LevelsMapScene->Update(deltaTime);
	Camera::GetInstance()->Update(deltaTime);
	//test box 2D
	printf("%f\n", LevelsMapScene->m_vObjects[1]->GetPosition().x);
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world.Step(deltaTime, velocityIterations, positionIterations);
	LevelsMapScene->m_vObjects[1]->SetPosition(Vector3(body->GetPosition().x, body->GetPosition().y, LevelsMapScene->m_vObjects[1]->GetPosition().z));
	printf("%f %f\n", body->GetPosition().x, body->GetPosition().y);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Input::SetKeyPressed(key, bIsPressed);
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	y = Globals::screenHeight - y;
	Input::SetTouchPosition(Vector2(x, y));
	Input::SetTouchStatus(true);
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	y = Globals::screenHeight - y;
	Input::SetTouchPosition(Vector2(x, y));
	Input::SetTouchStatus(false);
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	y = Globals::screenHeight - y;
	Input::SetTouchPosition(Vector2(x, y));
}

void CleanUp()
{
	delete LevelsMapScene;
	Input::DestroyInstance();
	Camera::DestroyInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "King of Towers", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseDownFunc (&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

