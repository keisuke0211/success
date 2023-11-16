//========================================
// 
// �T�E���h�̃w�b�_�t�@�C��
// Author : AKIRA TANAKA
// |
// Arrange: KEISUKE OTONO
// 
//========================================
// *** sys_stage_00.h ***
//========================================
#ifndef _SOUND_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "../main.h"

//****************************************
// �N���X
//****************************************
class CSound
{
public:
	// ***** ��` *****
	static const int SOUND_MAX = 64;	// �T�E���h�̍ő吔
	static const char* FILE_PATH;		// �ǂݍ��ރt�@�C���p�X

	// ***** �񋓌^ *****

	// �T�E���h�̎��
	enum SOUND_TYPE
	{
		SOUND_TYPE_BGM,	// ���y
		SOUND_TYPE_SE,	// ���ʉ�
		SOUND_TYPE_MAX,
	};

	// �T�E���h�̎��
	enum TYPE
	{
		TYPE_TITLE,		// �^�C�g��
		TYPE_GAME00,	// �Q�[��0
		TYPE_GAME01,	// �Q�[��1
		TYPE_RANKING,	// �����L���O
		TYPE_SELECT,	// �I��
		TYPE_CYBER,		// ����
		TYPE_SET,		// �u���b�N�z�u
		TYPE_ERASE,		// �u���b�N����
		TYPE_HIT,		// �q�b�g
		TYPE_ADD_SCORE,	// �X�R�A���Z
		TYPE_MAX,
	};

	// ***** �\���� *****

	// �T�E���h���
	struct SOUNDINFO
	{
		char		aFileName	// �t�@�C����
			[TXT_MAX];
		int			nCntLoop;	// ���[�v�J�E���g
		float		fVolume;	// ����
		SOUND_TYPE	type;		// �T�E���h�̎��
	};

	// ***** �֐� *****
	CSound();
	virtual~CSound();

	/* ���C�� */
	HRESULT Init(HWND hWnd);	// ������
	void Uninit(void);			// �I��
	void Load(void);			// �ǂݍ���

	HRESULT PlaySound(int nSoundIdx);	// �Z�O�����g�Đ�(�Đ����Ȃ��~)
	void StopSound(int nSoundIdx);		// �Z�O�����g��~(���x���w��)
	void StopSound(void);				// �Z�O�����g(�S��)

	void SoundTypeVolumeChange(SOUND_TYPE type, float fVolume);	// ��ޖ��ɉ��ʕύX
	void StopSoundType(SOUND_TYPE type);						// ��ޖ��ɍĐ���~

	/* �擾 */
	SOUNDINFO *GetInfo() { return m_aSoundInfo; }

private:

	// ***** �֐� *****
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	// �`�����N�̃`�F�b�N
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�̓ǂݍ���

	// ***** �ϐ� *****
	IXAudio2 *m_pXAudio2 = NULL;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_MAX] = {};						// �I�[�f�B�I�f�[�^�T�C�Y

	static float m_aSoundVolume[SOUND_TYPE_MAX];	// ����
	static float m_aSettingVolume[SOUND_TYPE_MAX];	// �ݒ�̉���
	SOUNDINFO m_aSoundInfo[SOUND_MAX];				// �T�E���h�̏��
	int m_nSoundNum;								// �T�E���h�̐�
};
#endif
