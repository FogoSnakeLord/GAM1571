#pragma once
#include "GameObject.h"

class Player: public GameObject{
public:
	Player(std::vector<float> v, int nV, fw::FWCore& fwCore);
	~Player();
	void Update(float deltaTime);

protected:
	fw::FWCore& m_FWCore;
};

