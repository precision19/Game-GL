// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Globals.h"
#include <conio.h>
#include "SceneManager.h"
#include "Input.h"
#include "MyContactListener.h"
#include "PlayerPrefs.h"
#include <thread>
#include "../Utilities/Math.h" // if you use STL, please include this line AFTER all other include
#include <iostream>
#include "vld/vld.h"

int Init ( ESContext *esContext )
{
	Input::CreateInstance();
	EventManager::CreateInstance();
	Camera::CreateInstance();
	AudioManager::CreateInstance();
	ResourceManager::CreateInstance();
	PrefabManager::CreateInstance();
	SceneManager::CreateInstance();
	ContactManager::CreateInstance();
	MyContactListener::CreateInstance();
	Physic::CreateInstance();
	PlayerPrefs::CreateInstance();
	PlayerPrefs::GetInstance()->LoadData();
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SceneManager::GetInstance()->Draw();
	

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}
	
void Update ( ESContext *esContext, float deltaTime )
{
	Camera::GetInstance()->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
	//AudioManager::GetInstance()->SetMusicFile(SceneManager::GetInstance()->getCurrentState());
	//AudioManager::GetInstance()->PlayMusic();
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//Input::SetKeyPressed(key, bIsPressed);
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
	Input::DestroyInstance();
	EventManager::DestroyInstance();
	Camera::DestroyInstance();
	ResourceManager::DestroyInstance();
	PrefabManager::DestroyInstance();
	SceneManager::DestroyInstance();
	Physic::DestroyInstance();
	ContactManager::DestroyInstance();
	MyContactListener::DestroyInstance();
	AudioManager::DestroyInstance();
	PlayerPrefs::DestroyInstance();
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
	//MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

