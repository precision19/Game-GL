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
	//testBox2D
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

	Input::CreateInstance();

	LevelsMapScene = new SceneManager("Managers/Level1");

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
	//test box 2D
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world.Step(deltaTime, velocityIterations, positionIterations);
	b2Vec2 position = body->GetPosition();
	float angle = body->GetAngle();
	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	//SceneManager::GetInstance()->Update(deltaTime);
	LevelsMapScene->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Input::SetKeyPressed(key, bIsPressed);
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	Input::SetTouchStatus(true);
	Input::SetTouchPosition(Vector2(x, y));
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	Input::SetTouchStatus(false);
	Input::SetTouchPosition(Vector2(x, y));
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	Input::SetTouchPosition(Vector2(x, y));
}

void CleanUp()
{
	//SceneManager::DestroyInstance();
	delete LevelsMapScene;
	Input::DestroyInstance();
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

