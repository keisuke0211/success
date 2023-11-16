//========================================
// 
// �J��������
// 
//========================================
// *** camera.h ***
//========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../main.h"
#include "physics.h"

//****************************************
// �N���X
//****************************************
class CCamera : public CPhysics
{
public:

	// ***** �񋓌^ *****

	// �J�����̓��e���
	enum SCREEN
	{
		SCREEN_NONE = 0,	// ����
		SCREEN_2D,			// ���s���e
		SCREEN_3D,			// �������e
		SCREEN_MAX
	};

	// ***** �\���� *****

	// �J�������
	struct Info
	{
		D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X

		D3DXVECTOR3 posV;			// ���݂̎��_
		D3DXVECTOR3 posR;			// ���݂̒����_
		D3DXVECTOR3 posOldV;		// �O��̎��_
		D3DXVECTOR3 posOldR;		// �O��̒����_
		D3DXVECTOR3 vecU;			// ������x�N�g��
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 targetRot;		// �ڕW����
		D3DXVECTOR3 spin;			// ��]��

		int nScreen;				// ���e���[�h

		float fDistance;			// ����
		float fTargetDistance;		// �ڕW����
		float fHeight;				// ����
		float fTargetHeight;		// �ڕW����
		float fVerticalMove;		// �c�̈ړ���
		bool bRotMove;				// �����̈ړ��؂�ւ��t���O

		int nRotType;				// �������
	};

	// ***** �֐� *****
	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	/* �ݒ� */
	void SetCamera(void);							// �J����
	void SetScreen(void);							// ��ʐݒ�
	void SetPosV(D3DXVECTOR3 pos, int nIdx = 0);	// ���_
	void SetPosR(D3DXVECTOR3 pos, int nIdx = 0);	// �����_
	void SetRot(D3DXVECTOR3 rot, int nIdx = 0);		// ����
	void SetHeigth(float Heigth);					// ����
	void SetDistance(float fDistance);				// ����

	/* �擾 */
	Info GetInfo() { return m_Info; }			// �J�����̏��

private:

	// ***** �\���� *****

	// �J�����̕ۑ����
	typedef struct
	{
		D3DXVECTOR3 posV;			// ���_
		D3DXVECTOR3 posR;			// �����_
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 spin;			// ��]��

		float fDistance;			// ����
		float fHeight;				// ����
		float fVerticalMove;		// �c�̈ړ���
	} Save;

	// ***** �֐� *****
	void AxisRotationCamera(DIRECTION drct, float fRot, int nIdx = 0); //��]����

	// ***** �ϐ� *****
	Info m_Info;		// �J����
	Save m_Save;		// �ۑ� 

};

#endif