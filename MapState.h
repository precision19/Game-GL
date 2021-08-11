#pragma once
#pragma once
#include "StateBase.h"

class MapState : public StateBase {
public:
	MapState();
	void Update(float deltaTime) override;
	void Draw() override;
	void Destroy() override;
};