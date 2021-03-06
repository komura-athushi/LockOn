#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
private:
	void ProcessNormal();
	void ProcessLockOn();
	Player* m_player = nullptr;					//プレイヤー。
	Vector3				m_toCameraPos = Vector3::One;		//注視点から視点に向かうベクトル。
};

