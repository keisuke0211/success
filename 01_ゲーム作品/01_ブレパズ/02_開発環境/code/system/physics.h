//========================================
// 
// �����֘A & ���ʏ��
// 
//========================================
//  *** physics.h ***
//========================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include "../main.h"

//****************************************
// �N���X
//****************************************
class CPhysics
{
public:

	// ***** �񋓌^ *****

	// ���f�����
	enum MODEL
	{
		MODEL_GRASS_00 = 0,	// �� 1�~1�~1
		MODEL_GRASS_01,		// �� 3�~1�~3
		MODEL_GRASS_02,		// �� 5�~1�~5
		MODEL_STONE,		// �� 1�~1�~1
		MODEL_WOOD_BOX,		// �ؔ�
		MODEL_IRON_BOX,		// �S��
		MODEL_BOMB,			// ���e
		MODEL_FENCE,		// ��E��
		MODEL_FENCE1,		// ��E�c
		MODEL_BULLET,		// �e
		MODEL_PLAYER_00,	// �v���C���[ ��
		MODEL_PLAYER_01,	// �v���C���[ ��
		MODEL_PLAYER_02,	// �v���C���[ ����
		MODEL_PLAYER_03,	// �v���C���[ �E��
		MODEL_PLAYER_04,	// �v���C���[ ����
		MODEL_PLAYER_05,	// �v���C���[ �E��
		MODEL_ENEMY_00,		// ���G�l�~�[
		MODEL_EFFECT_00,	// �G�t�F�N�g�@���q
		MODEL_MAX
	};

	// �x�N�g���̎��
	enum VECTOR
	{
		VECTOR_X,		// X����
		VECTOR_Y,		// Y����
		VECTOR_Z,		// Z����
		VECTOR_NONE,	// ����
		VECTOR_MAX
	};

	// 4����
	enum DIRECTION
	{
		DIRECTION_UP,			// ��
		DIRECTION_DOWN,			// ��
		DIRECTION_LEFT,			// ��
		DIRECTION_RIGHT,		// �E
		DIRECTION_BACK,			// ��
		DIRECTION_FRONT,		// ��O

		DIRECTION_LEFT_BACK,	// ����
		DIRECTION_LEFT_FRONT,	// ����O
		DIRECTION_RIGHT_BACK,	// �E��
		DIRECTION_RIGHT_FRONT,	// �E��O
		DIRECTION_MAX,
	};

	enum ROT
	{
		ROT_UP,		// ��
		ROT_RIGHT,	// ��
		ROT_DOWN,	// ��
		ROT_LEFT,	// �E
		ROT_MAX
	};

	// ***** �֐� *****
	CPhysics();		// �R���X�g���N�^
	virtual~CPhysics();	// �f�X�g���N�^

	/* int�^�̒l�̐���			*/void IntControl(int *pData, int nMax, int nMin);
	/* int�^�̒l�̃��[�v����	*/void IntLoopControl(int *pData, int nMax, int nMin);
	/* float�^�̒l�̐���		*/void FloatControl(float *pData, float fMax, float fMin);
	/* float�^�̒l�̃��[�v����	*/void FloatLoopControl(float *pData, float fMax, float fMin);

	/* 2�_�̊p�x�����߂�		*/float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
	/* �����𐧌�				*/void RotControl(D3DXVECTOR3 *pRot);

	/* �p�x�̍������߂�			*/float AngleDifference(float fAngle, float fTargetAngle);
	/* �p�x�̐���				*/void ControlAngle(float *pAngle);
	/* �ʒu�̍������߂�			*/float PosDifference(float fPos, float fTargetPos);
	/* ���������߂�				*/D3DXVECTOR3 Length(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos);
	/* �����蔻��(�S����)		*/bool Collsion(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3	PairSize);
	/* �����蔻��(��)			*/bool CollsionX(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize);
	/* �����蔻��(��)			*/bool CollsionY(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize);
	/* �����蔻��(��)			*/bool CollsionZ(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize);
	/* �����蔻��(�w�����)		*/bool CollsionDirection(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 PosOld, D3DXVECTOR3 PairPosOld, D3DXVECTOR3 size, D3DXVECTOR3 PairSize, DIRECTION nDirection);

private:

};
#endif