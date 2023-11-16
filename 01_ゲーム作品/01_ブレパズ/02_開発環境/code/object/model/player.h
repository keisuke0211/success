//========================================
// 
// �v���C���[����
// 
//========================================
// *** player.h ***
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../../main.h"
#include "motion_model.h"

//****************************************
// �N���X
//****************************************
class CPlayer : public CMotionModel
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

	static const int PLAYER_MAX = 1;	// �v���C���[�̍ő吔
	static const float PLAYER_SPEED;	// �v���C���[�̈ړ���

	// ***** �\���� *****

	// �v���C���[���
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3 moveRot;	// �ړ�����
		D3DXVECTOR3 targetRot;	// �ڕW����
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// ���_�J���[
		float fWidth;			// ��
		float fHeight;			// ����
		float fDepth;			// ���s��
		bool bMove;				// �ړ��t���O
		bool bMotion;			// ���[�V�����t���O
		bool bAction;			// �s���t���O
		bool bRotMove;			// ��]�t���O

	};

	// ***** �֐� *****
	CPlayer(int nPriority = PRIO_OBJECT);
	~CPlayer();

	/* ���C�� */

	// ����
	static CPlayer *Create(D3DXVECTOR3 pos,float rotY);

	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

	/* �ݒ� */
	void PlayerSetPos(D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }

	/* �擾 */
	D3DXVECTOR3 GetPos() { return m_Info.pos; }
	D3DXVECTOR3 GetPlayerMove() { return m_Info.move; }

private:
	// ***** �֐� *****
	/* �����蔻��			*/D3DXVECTOR3 Collision(PRIO nPrio, TYPE nType,VECTOR vector,D3DXVECTOR3 pos);

	/* �ړ� */
	void MoveInput(DIRECTION drct);	// �L�[�{�[�h�̈ړ�����
	void MovePos(float fMove);	// �ړ�
	void UpdatePos(void);		// �ʒu�X�V

	/* ���� */
	void KeyInput(void);	// �L�[���͏���
	void BulletStop(void);	// �e��~

	// ***** �ϐ� *****
	Info m_Info;			// �v���C���[���
};
#endif