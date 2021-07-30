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

SceneManager* LevelsMapScene;

int Init ( ESContext *esContext )
{
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	//glEnable(GL_DEPTH_TEST);

	Input::CreateInstance();
	//SceneManager::CreateInstance();
	LevelsMapScene = new SceneManager("Managers/LevelsMap");

	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//SceneManager::GetInstance()->Draw();
	LevelsMapScene->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
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

