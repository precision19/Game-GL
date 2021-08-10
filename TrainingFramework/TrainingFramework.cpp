// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include <conio.h>
#include "SceneManager.h"
#include "ContactManager.h"
#include "Input.h"
#include "Physic.h"

int Init ( ESContext *esContext )
{
	Input::CreateInstance();
	Camera::CreateInstance();

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->LoadResource("Level1");

	PrefabManager::CreateInstance();
	PrefabManager::GetInstance()->LoadPrefabs("Level1");

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->LoadScene("Level1");
	Physic::CreateInstance();
	SceneManager::GetInstance()->AddPhysicsToScene();

	ContactManager::CreateInstance();

	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

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
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//printf("%d %c\n", bIsPressed, key);
	Input::SetKeyPressed(key, bIsPressed);
	if (key == 'J') {
		if (bIsPressed) {
			Physic::GetInstance()->jumpPressed = 1;
		}
		else {
			Physic::GetInstance()->jumpPressed = 0;
		}
	}
	//printf("%c\n", key);
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
	Camera::DestroyInstance();
	ResourceManager::DestroyInstance();
	PrefabManager::DestroyInstance();
	SceneManager::DestroyInstance();
	ContactManager::DestroyInstance();
	Physic::DestroyInstance();
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

