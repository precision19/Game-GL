#include "stdafx.h"
#include "LevelState.h"
#include "EffectManager.h"
#include "Input.h"

LevelState::LevelState() 
{
	m_Name = "Level";
	m_LevelID = 1;
	m_Score = 0;
	m_PauseButton = NULL;
	m_TapToStartText = NULL;

	string path = "Managers/LevelBaseSM.txt";

	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	int amount, id;
	float x[3], y[3], z[3];
	char keyword[20], name[20], nameRender[20];

	fscanf(f, "#Objects: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "%s %s\n", keyword, name);
		fscanf(f, "RENDERER %s\n", nameRender);
		fscanf(f, "POSITION %f %f %f\n", &x[0], &y[0], &z[0]);
		fscanf(f, "ROTATION %f %f %f\n", &x[1], &y[1], &z[1]);
		fscanf(f, "SCALE %f %f %f\n", &x[2], &y[2], &z[2]);
		if (strcmp(name, "TapToStart") == 0) {
			m_TapToStartText = new Object();
			m_TapToStartText->SetRenderer(nameRender);
			m_TapToStartText->SetPosition(Vector3(x[0], y[0], z[0]));
			m_TapToStartText->SetRotation(Vector3(x[1], y[1], z[1]));
			m_TapToStartText->SetScale(Vector3(x[2], y[2], z[2]));
		}
		else if (strcmp(name, "PauseButton") == 0) {
			m_PauseButton = new Button();
			m_PauseButton->SetRenderer(nameRender);
			m_PauseButton->SetPosition(Vector3(x[0], y[0], z[0]));
			m_PauseButton->SetRotation(Vector3(x[1], y[1], z[1]));
			m_PauseButton->SetScale(Vector3(x[2], y[2], z[2]));
			m_PauseButton->SetButtonID(BUTTON_PAUSE);
		}
		else {
			Button* button = new Button();
			//button->SetRenderer(nameRender);
			button->SetPosition(Vector3(x[0], y[0], z[0]));
			button->SetRotation(Vector3(x[1], y[1], z[1]));
			button->SetScale(Vector3(x[2], y[2], z[2]));
			if (strcmp(name, "ContinueButton") == 0) {
				button->SetButtonID(BUTTON_CONTINUE);
				m_PauseMenu.push_back(button->Clone());
				m_PauseMenu[m_PauseMenu.size() - 1]->SetRenderer(nameRender);
			}
			else if (strcmp(name, "RestartButton") == 0) {
				button->SetButtonID(BUTTON_RESTART);
				m_PauseMenu.push_back(button->Clone());
				m_PauseMenu[m_PauseMenu.size() - 1]->SetRenderer(nameRender);
				m_WinMenu.push_back(button->Clone());
				m_WinMenu[m_WinMenu.size() - 1]->SetRenderer(nameRender);
			}
			else if (strcmp(name, "QuitButton") == 0) {
				button->SetButtonID(BUTTON_RETURN_MAP);
				m_PauseMenu.push_back(button->Clone());
				m_PauseMenu[m_PauseMenu.size() - 1]->SetRenderer(nameRender);
				m_WinMenu.push_back(button->Clone());
				m_WinMenu[m_WinMenu.size() - 1]->SetRenderer(nameRender);
			}
			else if (strcmp(name, "NextLevelButton") == 0) 
			{
				Button* nextLevel = button->Clone();
				nextLevel->SetButtonID(BUTTON_NEXT_LEVEL);
				nextLevel->SetRenderer(nameRender);
				m_WinMenu.push_back(nextLevel);
			}
			else {
				Object* object = new Object();
				object->SetRenderer(nameRender);
				object->SetPosition(Vector3(x[0], y[0], z[0]));
				object->SetRotation(Vector3(x[1], y[1], z[1]));
				object->SetScale(Vector3(x[2], y[2], z[2]));
				if (strcmp(name, "Background") == 0)
				{
					m_PauseMenu.push_back(object->Clone());
					m_WinMenu.push_back(object->Clone());
				}
				if (strcmp(name, "BackgroundPause") == 0)
				{
					m_PauseMenu.push_back(object->Clone());
				}
				if (strcmp(name, "BackgroundWin") == 0)
				{
					m_WinMenu.push_back(object->Clone());
				}
				delete object;
			}
			delete button;
		}
	}
}

int LevelState::GetLevel()
{
	return m_LevelID;
}

void LevelState::SetStateManager(StateManager* stateManager)
{
	m_StateManager = stateManager;
}

void LevelState::SetLevel(int levelID) 
{
	m_LevelID = levelID;
}

void LevelState::OnStart()
{
	printf("open level %d\n", m_LevelID);
	Camera::GetInstance()->SetDefault();
	AudioManager::GetInstance()->PlayBackgroundMusic(m_Name);
	LoadLevel();
}

void LevelState::LoadLevel()
{
	m_Player = (Player*)ObjectPool::GetInstance()->GetGameObject(PLAYER);
	m_Gate = ObjectPool::GetInstance()->GetGameObject(GATE);
	m_Chest = (TreasureChest*)ObjectPool::GetInstance()->GetGameObject(TREASURE_CHEST);
	AudioManager::GetInstance()->PlaySoundEffect("Ambiance", true, 20.0f);
	int amount, id, iBool, numBullets;
	float x, y, z, speed;
	char keyword[30], name[20];

	string path = "Managers/LevelMap/Level" + to_string(m_LevelID) + "SM.txt";
	FILE* fileMap = fopen(path.c_str(), "r+");
	if (fileMap == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	fscanf(fileMap, "#%s\n", name);

	if (strcmp(name, "DungeonBackground") == 0)
	{
		Object* object = new Object(name);

		fscanf(fileMap, "RENDERER %s\n", name);
		object->SetRenderer(name);
		fscanf(fileMap, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));
		fscanf(fileMap, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));
		fscanf(fileMap, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		m_Backgrounds.push_back(object);
	}
	else 
	{
		printf("Can't find BackGround!");
	}

	fscanf(fileMap, "#GameObjects: %d\n", &amount);

	int dungeon[10][16] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < amount; i++)
	{
		fscanf(fileMap, "%s %s\n", keyword, name);

		if (strcmp(name, "Dungeon") == 0)
		{
			for (int k = -1; k <= Dungeon::Height; k++)
			{
				for (int j = -1; j <= Dungeon::Width; j++)
				{
					if (j == Dungeon::Width - 1)
					{
						fscanf(fileMap, "%d\n", &iBool);
					}
					else
					{
						fscanf(fileMap, "%d ", &iBool);
					}

					if (iBool == 1)
					{
						dungeon[k + 1][j + 1] = 1;
					}
					else if (iBool == 9)
					{
						m_Gate->SetPosition(Dungeon::GridToWorld(j, Dungeon::Height - k - 1));
						m_GameObjects.push_back(m_Gate);
						m_Player->SetPosition(Dungeon::GridToWorld(j, Dungeon::Height - k - 1));
						m_Player->CreateCollider();
						m_GameObjects.push_back(m_Player);
					}
					else if (iBool == 8)
					{
						m_Chest->SetPosition(Dungeon::GirdToWord(j, Dungeon::Height - k - 1, 1));
						m_Chest->CreateCollider();
						m_GameObjects.push_back(m_Chest);
					}
				}
			}

			for (int k = 0; k < 10; k++)
			{
				for (int j = 0; j < 16; j++)
				{
					if (dungeon[k][j] == 1)
					{
						GameObject* block = ObjectPool::GetInstance()->GetGameObject(BLOCK);
						block->SetPosition(Dungeon::GirdToWord(j - 1, Dungeon::Height - k, 1));
						block->CreateCollider();
						int B = (k == 0) ? k : k - 1;
						int N = (k == 9) ? k : k + 1;
						int T = (j == 0) ? j : j - 1;
						int D = (j == 15) ? j : j + 1;
						((Block*)block)->SetRenderer(dungeon[k][D], dungeon[k][T], dungeon[N][j], dungeon[B][j]);
						//													 dungeon[B][D], dungeon[N][D], dungeon[B][T], dungeon[N][T]);
						m_GameObjects.push_back(block);
					}
				}
			}
		}

		else if (strcmp(name, "Gun") == 0)
		{
			fscanf(fileMap, "NUMBERGUNS %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				Gun* gun = (Gun*)ObjectPool::GetInstance()->GetGameObject(GUN);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				gun->SetPosition(Dungeon::GirdToWord(x, y, 0));
				char dir[10];
				fscanf(fileMap, "DIRECTION %s\n", dir);
				if (strncmp(dir, "EAST", 4) == 0) gun->SetDirection(EAST);
				if (strncmp(dir, "WEST", 4) == 0) gun->SetDirection(WEST);
				if (strncmp(dir, "NORTH", 5) == 0) gun->SetDirection(NORTH);
				if (strncmp(dir, "SOUTH", 5) == 0) gun->SetDirection(SOUTH);
				int numBullets;
				fscanf(fileMap, "NUMBULLETS %d\n", &numBullets);
				for (int j = 0; j < numBullets; j++) {
					Bullet* b = (Bullet*)ObjectPool::GetInstance()->GetGameObject(BULLET);
					if (strcmp(dir, "EAST") == 0) {
						b->SetVectorSpeed(Vector2(1.0f, 0.0f));
						b->SetPosition(Vector3(gun->GetPosition().x + 44.0f, gun->GetPosition().y, gun->GetPosition().z));
					}
					if (strcmp(dir, "WEST") == 0) {
						b->SetVectorSpeed(Vector2(-1.0f, 0.0f));
						b->SetPosition(Vector3(gun->GetPosition().x - 44.0f, gun->GetPosition().y, gun->GetPosition().z));
					}
					if (strcmp(dir, "NORTH") == 0) {
						b->SetVectorSpeed(Vector2(0.0f, 1.0f));
						b->SetPosition(Vector3(gun->GetPosition().x, gun->GetPosition().y + 44.0f, gun->GetPosition().z));
					}
					if (strcmp(dir, "SOUTH") == 0) {
						b->SetVectorSpeed(Vector2(0.0f, -1.0f));
						b->SetPosition(Vector3(gun->GetPosition().x, gun->GetPosition().y - 44.0f, gun->GetPosition().z));
					}
					b->SetBasePosition(b->GetPosition());
					b->CreateCollider();
					gun->bullets.push_back(b);
					m_GameObjects.push_back(b);
				}
				gun->CreateCollider();
				m_GameObjects.push_back(gun);
			}
		}

		else if (strcmp(name, "Chaser") == 0)
		{
			fscanf(fileMap, "NUMBERCHASERS %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				Chaser* chaser = (Chaser*)ObjectPool::GetInstance()->GetGameObject(CHASER);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				chaser->SetPosition(Dungeon::GirdToWord(x, y, 0));
				chaser->SetPositionStart(Dungeon::GirdToWord(x, y, 0));
				chaser->SetPositionTarget(Vector2(0.0f, 0.0f));
				chaser->SetScale(Vector3(0.35, 0.35, 0.35));
				chaser->CreateCollider();
				m_GameObjects.push_back(chaser);
			}
		}

		else if (strcmp(name, "SawBlade") == 0)
		{
			fscanf(fileMap, "NUMBERBLADES %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				//Guard* guard = m_GuardPrefab->Clone();
				SawBlade* blade = (SawBlade*)ObjectPool::GetInstance()->GetGameObject(SAW_BLADE);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				blade->SetPosition(Dungeon::GirdToWord(x, y, 0));
				blade->CreateCollider();
				m_GameObjects.push_back(blade);
			}
		}

		else if (strcmp(name, "DynamicBlade") == 0)
		{
			fscanf(fileMap, "NUMBERDYNAMICBLADES %d\n", &iBool);
			printf("%d", iBool);
			for (int i = 0; i < iBool; i++)
			{
				DynamicBlade* blade = (DynamicBlade*)ObjectPool::GetInstance()->GetGameObject(DYNAMIC_BLADE);
				fscanf(fileMap, "POSITIONSTART %f %f\n", &x, &y);
				blade->SetPosition(Dungeon::GirdToWord(x, y, 0));
				blade->SetPositionStart(Dungeon::GirdToWord(x, y, 0));
				fscanf(fileMap, "POSITIONEND %f %f\n", &x, &y);
				blade->SetPositionEnd(Dungeon::GirdToWord(x, y, 0));
				blade->CreateCollider();
				m_GameObjects.push_back(blade);
			}
		}

		else if (strcmp(name, "Guard") == 0)
		{
			fscanf(fileMap, "NUMBERGUARDS %d\n", &iBool);
			printf("%d", iBool);
			for (int i = 0; i < iBool; i++)
			{
				Guard* guard = (Guard*)ObjectPool::GetInstance()->GetGameObject(GUARD);
				fscanf(fileMap, "POSITIONSTART %f %f\n", &x, &y);
				guard->SetPosition(Dungeon::GirdToWord(x, y, 0));
				guard->SetPositionStart(Dungeon::GirdToWord(x, y, 0));
				fscanf(fileMap, "POSITIONEND %f %f\n", &x, &y);
				guard->SetPositionEnd(Dungeon::GirdToWord(x, y, 0));
				guard->CreateCollider();
				m_GameObjects.push_back(guard);
			}
		}
		else if (strcmp(name, "Spinner") == 0)
		{
			fscanf(fileMap, "NUMBERSPINNERS %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				SpinnerFly* spinner = (SpinnerFly*)ObjectPool::GetInstance()->GetGameObject(SPINNER);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				spinner->SetPosition(Dungeon::GirdToWord(x, y, 0));
				fscanf(fileMap, "POSITIONCENTER %f %f\n", &x, &y);
				spinner->SetPositionCenter(Dungeon::GirdToWord(x, y, 0));
				spinner->SetRadius();
				spinner->SetScale(Vector3(0.3, 0.3, 0.3));
				spinner->CreateCollider();
				m_GameObjects.push_back(spinner);
			}		
		}

		else if (strcmp(name, "Star") == 0)
		{
			fscanf(fileMap, "NUMBERSTARS %d\n", &iBool);
			for (int i = 0; i < iBool; i++)
			{
				Star* star = (Star*)ObjectPool::GetInstance()->GetGameObject(STAR);
				fscanf(fileMap, "POSITION %f %f\n", &x, &y);
				star->SetPosition(Dungeon::GirdToWord(x, y, 0));
				star->CreateCollider();
				m_GameObjects.push_back(star);
			}
		}

	}

	fscanf(fileMap, "#%s\n", name);

	if (strcmp(name, "Decoration") == 0)
	{
		fscanf(fileMap, "NUMBERS %d\n", &amount);
		for (int i = 0; i < amount; i++)
		{
			Object* object = new Object(name);

			fscanf(fileMap, "RENDERER %s\n", name);
			object->SetRenderer(name);
			fscanf(fileMap, "POSITION %f %f %f\n", &x, &y, &z);
			object->SetPosition(Vector3(x, y, z));
			fscanf(fileMap, "ROTATION %f %f %f\n", &x, &y, &z);
			object->SetRotation(Vector3(x, y, z));
			fscanf(fileMap, "SCALE %f %f %f\n", &x, &y, &z);
			object->SetScale(Vector3(x, y, z));

			m_Backgrounds.push_back(object);
		}
		
	}


	fclose(fileMap);

	FlagManager::GetInstance()->Set(FLAG_GAME_STATUS, GAME_ON_READY);
}

void LevelState::Restart()
{
	m_Score = 0;
	for each (GameObject * object in m_GameObjects)
		object->Reset();
}

void LevelState::Update(float deltaTime)
{
	if (!FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PAUSE, GAME_ON_WIN))
		if (m_PauseButton) m_PauseButton->Update(deltaTime);

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_READY))
		if (m_TapToStartText) m_TapToStartText->Update(deltaTime);

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PAUSE))
		for each (Object * object in m_PauseMenu)
			object->Update(deltaTime);

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_WIN))
		for each (Object * object in m_WinMenu)
			object->Update(deltaTime);

	if (Input::CheckButtonBuffer(BUTTON_RETURN_MAP))
	{
		ClearLevel();
		m_StateManager->SwitchState("Map");
		return;
	}

	if (Input::CheckButtonBuffer(BUTTON_PAUSE))
	{
		FlagManager::GetInstance()->Set(FLAG_GAME_STATUS, GAME_ON_PAUSE);
	}

	if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_DIE) || Input::CheckButtonBuffer(BUTTON_RESTART))
	{
		Restart();
	}

	if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_WIN))
	{
		PlayerPrefs::GetInstance()->SetData(m_LevelID, m_Score);
		PlayerPrefs::GetInstance()->SaveData();
	}

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_WIN))
	{
		if (Input::CheckButtonBuffer(BUTTON_NEXT_LEVEL))
		{
			m_LevelID++;
			if (m_LevelID > 21)
			{
				m_StateManager->SwitchState("Map");
			}
			else 
			{
				ClearLevel();
				LoadLevel();
				m_Score = 0;
			}
			return;
		}
	}

	if (Input::CheckButtonBuffer(BUTTON_CONTINUE))
	{
		// EffectManager::AddAnimationEffect();
		FlagManager::GetInstance()->Set(FLAG_GAME_STATUS, GAME_ON_PLAYING);
	}


	if (!FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PAUSE))
	{
		for each (Object * object in m_Backgrounds)
			object->Update(deltaTime);

		for each (GameObject * object in m_GameObjects)
			object->Update(deltaTime);
	}

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PLAYING, GAME_ON_READY))
		Physic::GetInstance()->Update(deltaTime);

	if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_GAMEPLAY, EVENT_PLAYER_SCORE))
	{
		m_Score++;
	} 

}

void LevelState::Draw()
{
	for each (Object * object in m_Backgrounds)
		object->Draw();

	for each (GameObject * object in m_GameObjects)
		object->Draw();

	if (!FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PAUSE, GAME_ON_WIN))
		if (m_PauseButton) m_PauseButton->Draw();

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_READY))
		if (m_TapToStartText) m_TapToStartText->Draw();

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_PAUSE))
		for each (Object * object in m_PauseMenu)
			object->Draw();

	if (FlagManager::GetInstance()->Check(FLAG_GAME_STATUS, GAME_ON_WIN))
		for each (Object * object in m_WinMenu)
			object->Draw();
}

void LevelState::ClearLevel() 
{
	for each (Object * object in m_Backgrounds)
		delete object;
	m_Backgrounds.clear();
	for each (GameObject * object in m_GameObjects)
	{
		object->DestroyCollider();
		ObjectPool::GetInstance()->ReturnGameObject(object);
	}
	m_Score = 0;
	m_GameObjects.clear();
}

LevelState::~LevelState()
{
	for each (Object * object in m_Backgrounds)
		delete object;

	for each (Object * object in m_GameObjects)
		delete object;

	delete m_TapToStartText;
	delete m_PauseButton;
	
	for (int i = 0; i < m_PauseMenu.size(); i++) {
		delete m_PauseMenu[i];
	}
	printf("%d %d\n", m_PauseMenu.size(), m_WinMenu.size());

	for (int i = 0; i < m_WinMenu.size(); i++) {
		delete m_WinMenu[i];
	}
}