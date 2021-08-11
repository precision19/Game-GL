#pragma once
#include "StateBase.h"


class LevelState : public StateBase {
public:
	LevelState();
	void Update(float deltaTime) override;
	void Draw() override;
	void Destroy() override;
};