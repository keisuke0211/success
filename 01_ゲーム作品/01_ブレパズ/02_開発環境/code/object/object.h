//========================================
// 
// �I�u�W�F�N�g����
// 
//========================================
// *** objext.h ***
//========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../main.h"
#include "../system/physics.h"

//****************************************
// �O���錾
//****************************************
class CScore;	// �X�R�A
class CTime;	// �^�C��

//****************************************
// �N���X
//****************************************
class CObject : public CPhysics
{
public:

	// ***** �񋓌^ *****

	// �D�揇�ʎ��
	enum PRIO
	{
		PRIO_NONE = 0,	// ����
		PRIO_OBJECT,	// �I�u�W�F�N�g
		PRIO_BLOCK,		// �u���b�N
		PRIO_CUBE,		// �L���[�u
		PRIO_EFFECT,	// �G�t�F�N�g
		PRIO_UI,		// UI
		PRIO_TEXT,		// �e�L�X�g
		PRIO_FADE,		// �t�F�[�h
		PRIO_MAX
	};

	// �I�u�W�F�N�g���
	enum TYPE
	{
		TYPE_NONE = 0,	// ����
		TYPE_BG,		// �w�i
		TYPE_BG_MULTI,	// �}���`�w�i
		TYPE_BLOCK,		// �u���b�N
		TYPE_CUBE,		// �L���[�u
		TYPE_PLAYER,	// �v���C���[
		TYPE_ENEMY,		// �G�l�~�[
		TYPE_BULLET,	// �o���b�g
		TYPE_EFFECT,	// �G�t�F�N�g
		TYPE_PARTICLE,	// �p�[�e�B�N��
		TYPE_TIME,		// �^�C��
		TYPE_SCORE,		// �X�R�A
		TYPE_FONT,		// �t�H���g
		TYPE_TEXT,		// �e�L�X�g
		TYPE_MAX
	};

	// ***** �ÓI�֐� *****
	/* �S�Ă̔j��			*/static void ReleaseAll(void);
	/* �S�Ă̔j��(��ޖ�)	*/static void ReleaseAll(TYPE type);	// [�I�[�o�[���[�h]
	/* �S�Ă̍X�V			*/static void UpdateAll(void);
	/* �S�Ă̕`��			*/static void DrawAll(void);

	// ***** �֐� *****
	CObject(int nPriority = 0);
	virtual~CObject();

	/* ������	*/virtual HRESULT Init(void) = 0;
	/* �I��		*/virtual void Uninit(void) = 0;
	/* �X�V		*/virtual void Update(void) = 0;
	/* �`��		*/virtual void Draw(void) = 0;

	// -- �ݒ� ------------------------------------------
	/* ��ސݒ�*/void SetType(TYPE type);

	// -- �擾 ------------------------------------------
	/* �擪�̏��				*/static CObject *GetTop(int nPriority) { return m_apTop[nPriority]; }
	/* �Ō���̏��				*/static CObject *GetCur(int nPriority) { return m_apCir[nPriority]; }
	/* �O�̃I�u�W�F�N�g���		*/CObject *GetPrev(void) { return m_pPrev; }
	/* �O�̃I�u�W�F�N�g���		*/CObject *GetNext(void) { return m_pNext; }
	/* ��						*/virtual float GetWidth(void) { return 0.0f; }
	/* ����						*/virtual float GetHeight(void) { return 0.0f; }
	/* ���s��					*/virtual float GetDepth(void) { return 0.0f; }
	/* �T�C�Y					*/virtual D3DXVECTOR3 GetSize(void) { return INIT_D3DXVECTOR3; }
	/* �ʒu						*/virtual D3DXVECTOR3 GetPos(void) { return INIT_D3DXVECTOR3; }
	/* �ʒu(�ߋ�)				*/virtual D3DXVECTOR3 GetPosOld(void) { return INIT_D3DXVECTOR3; }
	/* ����						*/virtual D3DXVECTOR3 GetRot(void) { return INIT_D3DXVECTOR3; }
	/* ����(�ߋ�)				*/virtual D3DXVECTOR3 GetRotOld(void) { return INIT_D3DXVECTOR3; }
	/* ���						*/TYPE GetType(void) { return m_type; }
	/* �X�R�A���				*/static CScore *GetScore(int nPriority,int nIdx);
	/* �^�C�����				*/static CTime *GetTime(int nPriority, int nIdx);

protected:
	
	// ***** �֐� ****
	/* ������� */void Release(void);

	// ***** �ϐ� *****
	CObject *m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^

private:
	// ***** �֐� *****
	/* �������	*/void ReleaseList(void);

	// ***** �ϐ� *****
	static CObject *m_apTop[PRIO_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_apCir[PRIO_MAX];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nPriority;					// �D�揇�ʂ̈ʒu
	TYPE m_type;						// �������g�̎��
	bool m_bDeath;						// ���S�t���O

};
#endif