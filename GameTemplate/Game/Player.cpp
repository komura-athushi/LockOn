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

	//���̃t���[���̈ړ��ʂ����߂�B
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed += cameraForward * lStick_y * 250.0f;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * 250.0f;		//�E�����ւ̈ړ����x�����Z�B

	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
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

	//�v���C���[�ƃG�l�~�[�����ȏ㗣��Ă�����B
	//�^�[�Q�b�e�B���O���Ȃ��B
	//�߂����Ă��^�[�Q�b�e�B���O���Ȃ��B
	if (diff.Length() >= 500.0f || diff.Length() <= 20.0f)
	{
		m_isTakeAim = false;
		return;
	}
	
	diff.y = 0.0f;
	diff.Normalize();

	float angle = acosf(m_forward.Dot(diff));

	//�v���C���[�̐��ʃx�N�g���ƁB
	//�v���C���[����G�l�~�[�Ɍ������x�N�g���́B
	//�p�x��90�x�ȏォ�B
	//���b�N�I����ԂłȂ�������B
	//�^�[�Q�b�e�B���O���Ȃ��B
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
	//�^�[�Q�b�e�B���O������Ă��Ȃ�������B
	//���b�N�I�����Ȃ��B
	if (m_isTakeAim == false)
	{
		m_isLockOn = false;
		return;
	}

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//���b�N�I�����Ă��Ȃ���΁B
		if (m_isLockOn == false)
		{
			//���b�N�I������B
			m_isLockOn = true;
		}
		//���b�N�I�����Ă���΁B
		else
		{
			//���b�N�I�����Ȃ��B
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