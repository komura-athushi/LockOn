#pragma once

class Enemy;
class Player;
class GameCamera;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	ModelRender			m_modelRender;
	Enemy*				m_enemy = nullptr;
	Player*				m_player = nullptr;
	GameCamera*			m_gameCamera = nullptr;
	SkyCube*			m_skyCube = nullptr;
};

