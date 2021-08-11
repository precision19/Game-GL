#pragma once
#include "StateBase.h"

class MenuState : public StateBase {
public:
	MenuState();
	void Update(float deltaTime) override;
	void Draw() override;
    void Destroy() override;
};