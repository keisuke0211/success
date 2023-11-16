//========================================
// 
// ���[�V�������f������
// 
//========================================
// *** motion_model.h ***
//========================================
#ifndef _MOTION_MODEL_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_MODEL_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "../object.h"
#include "../../main.h"

//****************************************
// �O���錾
//****************************************
class CMotion;

//****************************************
// �N���X
//****************************************
class CMotionModel : public CObject
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CMotionModel *Create();			// 3D���f���̐���

	CMotionModel(int nPriority = PRIO_OBJECT);		// �R���X�g���N�^
	virtual~CMotionModel();							// �f�X�g���N�^

	// ***** �֐� *****
	HRESULT Init(void);													// ������
	void Uninit(void);													// �I��
	void Update(void);													// �X�V
	void Draw(void);													// �`��
	void ChangeColar(D3DXCOLOR color);									// �F�̕ύX

	/* �ݒ� */
	void SetPos(const D3DXVECTOR3 &pos) { m_pos = m_posOld =pos; };		// �ʒu
	void SetRot(const D3DXVECTOR3 &rot) { m_rot = m_rotOld = rot; };	// ����
	void SetScale(const D3DXVECTOR3 &scale) { m_scale = scale; }		// �T�C�Y
	void SetColor(D3DXCOLOR color) { m_color = color; }					// �F
	void SetIsColor(bool bcolor) { m_bcolor = bcolor; }					// �F�ύX
	void SetSize(const D3DXVECTOR3 &size) { m_size = size; }			// �����蔻��
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ���[���h�}�g���b�N�X
	void SetMotion(const char *pName);									// ���[�V�������
	void SetStencil(bool isStencil) { m_Stencil = isStencil; }			// �X�e���V���o�b�t�@
	void SetQuat(D3DXQUATERNION quat) { m_quat = quat; }				// �N�I�[�^�j�I��


	/* �擾 */
	D3DXVECTOR3 GetPos() { return m_pos; }								// �ʒu
	D3DXVECTOR3 GetPosOld() { return m_posOld; }						// �ʒu(�ߋ�)
	D3DXVECTOR3 GetRot() { return m_rot; }								// ����
	D3DXVECTOR3 GetRotOld() { return m_rotOld; }						// ����(�ߋ�)
	D3DXVECTOR3 GetScale() { return m_scale; }							// �T�C�Y
	D3DXCOLOR GetColor() { return m_color; }							// �F
	bool GetIsColor() { return m_bcolor; }								// �F�ύX
	D3DXVECTOR3 GetSize() { return m_size; }							// �����蔻��
	D3DXMATRIX* GetMtxWorld() { return &m_mtxWorld; }					// ���[���h�}�g���b�N�X
	CMotion *GetMotion() { return m_pMotion; }							// ���[�V�������
	D3DXQUATERNION GetQuat() { return m_quat; }							// �N�I�[�^�j�I��

private:
	// ***** �ϐ� *****
	CMotion			*m_pMotion;				// ���[�V�����C���X�^���X
	D3DXMATRIX		m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXVECTOR3		m_posOld;				// �ʒu(�ߋ�)
	D3DXVECTOR3		m_rot;					// ����
	D3DXVECTOR3		m_rotOld;				// ����(�ߋ�)
	D3DXVECTOR3		m_scale;				// �X�P�[��
	D3DXVECTOR3		m_size;					// �����蔻��
	D3DXCOLOR		m_color;				// �F
	D3DXQUATERNION m_quat;					// �N�I�[�^�j�I��
	bool m_Stencil;							// �X�e���V���o�b�t�@�̗L�����ǂ���
	bool m_bcolor;							// �F��ς��邩
};
#endif