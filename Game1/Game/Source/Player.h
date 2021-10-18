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
/*
#include <random>

class Random
{
public:
	Random();
	~Random();
	int RandInt(int min, int max);
	float RandFloat(int min, int max);

protected:
	std::mt19937 m_MiddleVariable;
};*/

