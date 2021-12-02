#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	m_modelRender.Init("Assets/modelData/box.tkm");
	m_modelRender.SetPosition(m_position);
	return true;
}

void Enemy::Update()
{
	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}