//========================================
// 
// �p�[�c����
// 
//========================================
// *** parts.h ***
//========================================
#ifndef _PARTS_H_			// ���̃}�N����`������ĂȂ�������
#define _PARTS_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "model.h"
#include "../../main.h"

//****************************************
// �N���X
//****************************************
class CParts : public CModel
{
public:
	// ***** �ÓI�֐� *****
	static CParts *Create();	// ����

	CParts();			// �R���X�g���N�^
	virtual~CParts();	// �f�X�g���N�^

	// ***** �֐� *****

	/* �ݒ� */
	void SetPosOrigin(const D3DXVECTOR3 &posOrigin) { m_posOrigin = posOrigin; }		// ���̈ʒu
	void SetRotOrigin(const D3DXVECTOR3 &rotOrigin) { m_rotOrigin = rotOrigin; }		// ���̌���
	void SetPosDest(const D3DXVECTOR3 &posDest) { m_posDest = posDest; }				// �ړI�ʒu
	void SetRotDest(const D3DXVECTOR3 &rotDest) { m_rotDest = rotDest; }				// �ړI����

	/* �擾 */
	D3DXVECTOR3 GetPosOrigin() { return m_posOrigin; }									// ���̈ʒu
	D3DXVECTOR3 GetRotOrigin() { return m_rotOrigin; }									// ���̌���
	D3DXVECTOR3 GetPosDest() { return m_posDest; }										// �ړI�ʒu
	D3DXVECTOR3 GetRotDest() { return m_rotDest; }										// �ړI����

private:
	// ***** �ϐ� *****
	D3DXVECTOR3 m_posOrigin;		// ���̈ʒu
	D3DXVECTOR3 m_rotOrigin;		// ���̌���
	D3DXVECTOR3 m_posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
};

#endif
