#include "stdafx.h"
#include "Game.h"

#include "Enemy.h"
#include "Player.h"
#include "GameCamera.h"

Game::~Game()
{
	DeleteGO(m_enemy);
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_skyCube);
}

Game::Game()
{

}

bool Game::Start()
{
	m_enemy = NewGO<Enemy>(0, "enemy");
	m_player = NewGO<Player>(0, "player");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_skyCube->SetScale(Vector3::One * 100.0f);
	m_skyCube->SetLuminance(0.5f);
	return true;
}

void Game::Update()
{

}
