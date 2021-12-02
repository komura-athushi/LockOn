#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
private:
	ModelRender				m_modelRender;
	Vector3 m_position;
};

