#pragma once

class Enemy;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	const bool IsLockOn() const
	{
		return m_isLockOn;
	}
	/// <summary>
	/// ターゲットの座標を取得。
	/// </summary>
	/// <returns></returns>
	const Vector3& GetTargetPosition() const
	{
		return m_targetPosition;
	}
private:
	void Move();
	void Rotation();
	void TakeAim();
	void LockOn();
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Quaternion m_rotation;
	Enemy* m_enemy = nullptr;
	SpriteRender		m_spriteRender;
	bool m_isTakeAim = false;
	bool m_isLockOn = false;
	Vector3 m_forward = Vector3::AxisZ;
	Vector3 m_targetPosition = Vector3::Zero;
};

