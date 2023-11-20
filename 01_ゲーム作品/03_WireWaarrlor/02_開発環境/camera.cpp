//��====================��
//�b�@�@�@�@�@�@�@�@�@�@�b
//�b�@ �J�����̏����@�@ �b
//�b�@Author:��a�c��@ �b
//�b                    �b
//��====================��
#include"camera.h"
#include"player.h"

Camera g_camera;
//========================================
//�J�����̏��������� -
//========================================
void InitCamera(void)
{
	Player *pPlayer = Getplayer();
	g_camera.fWidth = 0.3f;
	g_camera.fHeighy = 0.9f;
	g_camera.bCamera_Y = true;
	g_camera.pos = D3DXVECTOR3(100, SCREEN_HEIGHT - 150, 0);
}

//========================================
// �J�����̏I������ -
//========================================
void UninitCamera(void)
{

}

//========================================
//�J�����̍X�V���� -
//========================================
void UpdateCamera(void)
{
	Player *pPlayer = Getplayer();	//�v���C���[�̏��ւ̃|�C���^

	if (pPlayer->bCamera == true)
	{
		//�v���C���[�̈ʒu���J�����̈ʒu���ɑ������
		g_camera.pos = Getplayer()->pos;
	}
}

//========================================
// �`��ʒu���J�����ɍ��킹�� -
//========================================
void CameraPosition(D3DXVECTOR3 *pDrawPos)
{
	// �`��ʒu���J�����ɍ��킹��
	//Position(pDrawPos, g_camera.pos);


	// �ʒu���v���C���[�̈ʒu�ɍ��킹��
	pDrawPos->x = pDrawPos->x - g_camera.pos.x + (SCREEN_WIDTH * g_camera.fWidth);

	if (g_camera.bCamera_Y == true)
	{
		pDrawPos->y = pDrawPos->y - g_camera.pos.y + (SCREEN_HEIGHT * g_camera.fHeighy);
	}
}
//========================================
// �J�������̎擾
//========================================
Camera *GetCamera(void)
{
	return &g_camera;
}