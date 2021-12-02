#include "stdafx.h"
#include "Player.h"

#include "Enemy.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	m_spriteRender.Init("Assets/sprite/lock.dds",200,200);
	m_enemy = FindGO<Enemy>("enemy");
	return true;
}

void Player::Update()
{
	Move();
	Rotation();
	TakeAim();
	LockOn();
	m_modelRender.Update();
	m_spriteRender.Update();
}

void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//このフレームの移動量を求める。
	//左スティックの入力量を受け取る。
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed += cameraForward * lStick_y * 250.0f;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * lStick_x * 250.0f;		//右方向への移動速度を加算。

	//キャラクターコントローラーを使用して、座標を更新。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Player::TakeAim()
{
	Vector3 enemyPosition = m_enemy->GetPosition();
	Vector3 diff = enemyPosition - m_position;

	//プレイヤーとエネミーが一定以上離れていたら。
	//ターゲッティングしない。
	//近すぎてもターゲッティングしない。
	if (diff.Length() >= 500.0f || diff.Length() <= 20.0f)
	{
		m_isTakeAim = false;
		return;
	}
	
	diff.y = 0.0f;
	diff.Normalize();

	float angle = acosf(m_forward.Dot(diff));

	//プレイヤーの正面ベクトルと。
	//プレイヤーからエネミーに向かうベクトルの。
	//角度が90度以上かつ。
	//ロックオン状態でなかったら。
	//ターゲッティングしない。
	if (angle > Math::PI / 2 && m_isLockOn == false)
	{
		m_isTakeAim= false;
		return;
	}
	m_isTakeAim = true;

	Vector2 screenPosition;
	g_camera3D->CalcScreenPositionFromWorldPosition(screenPosition, enemyPosition);
	m_spriteRender.SetPosition(Vector3(screenPosition.x, screenPosition.y, 0.0f));
	m_targetPosition = enemyPosition;
}

void Player::LockOn()
{
	//ターゲッティングがされていなかったら。
	//ロックオンしない。
	if (m_isTakeAim == false)
	{
		m_isLockOn = false;
		return;
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//ロックオンしていなければ。
		if (m_isLockOn == false)
		{
			//ロックオンする。
			m_isLockOn = true;
		}
		//ロックオンしていれば。
		else
		{
			//ロックオンしない。
			m_isLockOn = false;
		}
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	if (m_isTakeAim == false)
	{
		return;
	}
	m_spriteRender.Draw(rc);
}