//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.h ***
//========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CEnemy : public CObjectX
{
public:

	// ***** ��` *****
	static const int MAX_ENEMY = 30;	// �G�̍ő吔
	static const int STAND_TIME = 30;	// �ҋ@���Ԃ̍ő�l
	static const int STOP_TIME = 90;	// ��~���Ԃ̍ő�l

	// ***** �񋓌^ *****

	// ���
	enum STATE
	{
		STATE_NORMAL,	// �ʏ�
		STATE_STAND,	// �ҋ@
		STATE_STOP,		// ��~
		STATE_DAMAGE,	// �_���[�W
		STATE_MAX,
	};

	// ***** �\���� *****

	// �G���
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 moveRot;	// �ړ�����
		D3DXVECTOR3 targetRot;	// �ڕW����
		D3DXVECTOR3 move;		// �ړ���
		D3DCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nMove;				// �ړ����
		int nLife;				// ����
		int nLifeMax;			// �����̍ő�l
		STATE state;			// ���
		STATE stateOld;			// �ߋ��̏��
		int nCntState;			// ��ԊǗ��J�E���^�[
		int nCntStop;			// ��~����
		int nCntTime;			// �s���J�E���^�[
		int nTimeMax;			// �s�����Ԃ̍ő�l
		int nStandTime;			// �ҋ@����
		bool bRotMove;			// �����̐��ڃt���O
		bool bCube;				// �L���[�u�ɓ���������
		bool bGravity;			// �d��
		int nID;				// ID
	};

	// ***** �֐� *****
	CEnemy(int nPriority = PRIO_OBJECT);
	virtual~CEnemy();

	/* ���C�� */

	// ����
	static CEnemy *Create(int nType,int nMove,D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nCntTime);

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ���Z�b�g	*/static void Reset(void);
	/* Hit����	*/void HitLife(int nDamage);

	/* �ݒ�	*/
	/* ��Ԑݒ�		*/void SetState(STATE state);
	/* �S�̂̏d��	*/static void SetGravity(bool bSet) { m_bGravity = bSet; }

	/* �擾 */
	/* �G���		*/Info GetInfo(void) { return m_Info; }
	/* �ʒu			*/D3DXVECTOR3 GetPos(void) { return m_Info.pos; }
	/* �ߋ��ʒu		*/D3DXVECTOR3 GetPosOld(void) { return m_Info.posOld; }
	/* �S�̂̏d��	*/static bool IsmGravity(void) { return m_bGravity; }
	/* �G�̑���		*/static int GetEnemyAll(void) { return m_nNumAll; }
	/* ID			*/int GetID(void) { return m_Info.nID; }

private:

	// ***** �\���� *****

	// �z�u���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		int nType;			// ���
		int nSpeed;			// �ړ���
		int nStage;			// �X�e�[�WID
		int nUnit;			// ����ID
		bool bSet;			// �z�u�������ǂ���

	} SetInfo;

	// ***** �֐� *****
	/* ��Ԑ���				*/void StateShift(void);
	/* �����蔻��(�����w��)	*/bool Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos);
	/* �����蔻��(�S��)		*/void ModelCollsion(PRIO nPrio, TYPE nType, D3DXVECTOR3 pos);

	// ***** �ϐ� *****
	Info m_Info;			// ���
	static SetInfo *pSet;	// �z�u

	static int m_nNumAll;		// �G�̑���
	static bool m_bGravity;		// �S�̂̏d��
};
#endif