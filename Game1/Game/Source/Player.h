#pragma once
#include "GameObject.h"

class Player: public GameObject{
public:
	Player(std::vector<float> v, int nV, fw::FWCore& fwCore);
	~Player();
	void Update(float deltaTime);
	void Respawn();
	void ChangeScore(int score);
	int GetScore();
protected:
	fw::FWCore& m_FWCore;
	int m_Score;
};

