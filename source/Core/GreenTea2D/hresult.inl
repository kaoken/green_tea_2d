/*! @file  hresult.inl
* @brief MetalCube.h�t�@�C��������Ăяo�����̂ŁA�ق�����Ăяo���Ȃ��悤�ɁI
*  ����́A�Z�a�������\���̂��g�����߂̂���
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once

//------------------------------------------------------------
//! @name windows��HRESULT�ƌ݊������������邽�߂�
//  �ȉ��̂悤�ɂ�HRESULT32�r�b�g�l�����C�A�E�g����Ă���
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
//      S - Severity(�d�v�x) - ����/���s�������Ă���
//
//          0 - ����
//          1 - ���s (COERROR)
//
//      R - �t�@�V���e�B�R�[�h�̗\�񕔕��́ANT�̓�Ԗڂ�Severity�̃r�b�g�ɑΉ�����B
//
//      C - �t�@�V���e�B�R�[�h�̗\�񕔕��́ANT��C�t�B�[���h�ɑΉ����Ă��܂��B
//
//      N - �t�@�V���e�B�R�[�h�̗\�񕔕��B�}�b�v���ꂽNT��Ԓl���������߂Ɏg�p�����B
//
//      r - �t�@�V���e�B�R�[�h�̗\�񕔕��B�����g�p�̂��߂ɗ\�񂳂�Ă��܂��B
//          �X�e�[�^�X�l�ł͂���܂���HRESULT�l�������Ă���̂ł͂Ȃ��A�\��������̃��b�Z�[�WID�̂��߂Ɏg�p���܂��B
//
//      Facility - �t�@�V���e�B�R�[�h�ł��B
//
//      Code - �t�@�V���e�B�̃X�e�[�^�X�R�[�h�ł�
//------------------------------------------------------------
//@{
typedef long gt2HRESULT;
#define GT_HRESULT_TYPEDEF_(_sc) ((gt2HRESULT)_sc)
//!< �\�����i����HRESULT�l���쐬���܂��B
#define GT_MAKE_HRESULT(sev,fac,code) ((gt2HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
//!< �C�ӂ̃X�e�[�^�X�l�ɂ�鎸�s�̂��߂̈�ʓI�ȃe�X�g��񋟂��܂��B
#define GT_FAILED(hr) (((gt2HRESULT)(hr)) < 0)
//!< �C�ӂ̃X�e�[�^�X�l�ɂ�鐬���̂��߂̈�ʓI�ȃe�X�g��񋟂��܂��B
#define GT_SUCCEEDED(hr) (((gt2HRESULT)(hr)) >= 0)
//!< ���[�U�[��`�̃G���[���쐬
#define GT_MK_ERR_HRESULT(_no) GT_MAKE_HRESULT( 1, FACILITY_ITF, 0xF000+_no )

//***************
// �G���[�R�[�h
//***************

//! �G���[�͔������Ă��܂���B
#define GT_S_OK ((gt2HRESULT)0L)
//! ����ɏ������ꂽ���̂́A��W���̊�����������֐����l�ł� (���m�ȈӖ��̓R���e�L�X�g�ɂ���ĈقȂ�܂�)�B
#define GT_S_FALSE ((gt2HRESULT)1L)
//! ���s�����A�\���ł��Ȃ��G���[�ł��B
#define GT_E_FAIL			GT_HRESULT_TYPEDEF_(0x80004005L)
//! �v���I�ȃG���[
#define GT_E_UNEXPECTED		GT_HRESULT_TYPEDEF_(0x8000FFFFL)
//! �A�v���P�[�V������`�܂��̓I�u�W�F�N�g��`�̃G���[�ł��B
#define GT_E_ABORT			GT_HRESULT_TYPEDEF_(0x80004004L)
//! �A�N�Z�X�����ۂ���܂����B
#define GT_E_ACCESSDENIED	GT_HRESULT_TYPEDEF_(0x80070005L)
//! �|�C���^�[�l�Ɍ���� nullptr ���n����܂����B
#define GT_E_POINTER		GT_HRESULT_TYPEDEF_(0x80004003L)
//! �֐��ɖ����ȃp�����[�^�[���n����܂����B
#define GT_E_INVALIDARG		GT_HRESULT_TYPEDEF_(0x80070057L)
//! �A�v���Ăяo�����������邤���ŏ\���ȃ������[�����蓖�Ă邱�Ƃ��ł��܂���ł����B
#define GT_E_OUTOFMEMORY	GT_HRESULT_TYPEDEF_(0x8007000EL)
//! ����̎�ނ̃X�e�[�g �I�u�W�F�N�g�̈�ӂ̃C���X�^���X���������܂��B
#define GT_E_TOO_MANY_UNIQUE_STATE_OBJECTS	GT_HRESULT_TYPEDEF_(0x887C0001L)
//! �t�@�C����������܂���ł����B
#define GT_E_FILE_NOT_FOUND	GT_HRESULT_TYPEDEF_(0x887C0002L)
//! ����̎�ނ̃r���[ �I�u�W�F�N�g�̈�ӂ̃C���X�^���X���������܂��B
#define GT_E_TOO_MANY_UNIQUE_VIEW_OBJECTS	GT_HRESULT_TYPEDEF_(0x887C0003L)
//! ���\�[�X���Ƃ� ID3D11Device::CreateDeferredContext �̌Ăяo���܂��� ID3D11DeviceContext::FinishCommandList �̌Ăяo���̌�ōŏ��ɌĂяo���� ID3D11DeviceContext::Map �� D3D11_MAP_WRITE_DISCARD �ł͂���܂���ł����B
#define GT_E_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD	GT_HRESULT_TYPEDEF_(0x887C0004L)
//! ���\�b�h�̌Ăяo���������ł��B���Ƃ��΁A���\�b�h�̃p�����[�^�[���L���ȃ|�C���^�[�łȂ��\��������܂��B
#define GT_E_INVALIDCALL	GT_MAKE_HRESULT( 1, 0x876, 2156 )
//! ���łɍ쐬�ς�
#define GT_E_CREATED		GT_MK_ERR_HRESULT(1)
//! �쐬����Ă��Ȃ�
#define GT_E_NOT_CREATED	GT_MK_ERR_HRESULT(2)
//! ������Ȃ�����
#define GT_E_NOT_FIND		GT_MK_ERR_HRESULT(3)
//! �쐬����Ă������A�^���Ⴄ��ނ�����
#define GT_E_CREATED_DIFFERENT_TYPE		GT_MK_ERR_HRESULT(4)
//! �o�^���s
#define GT_E_REGISTER_FAIL				GT_MK_ERR_HRESULT(5)
//! �X�N���v�g�ŁA���s�����f����A�ĊJ���邱�Ƃ��ł���B
#define GT_E_AS_EXECUTION_SUSPENDED		GT_MK_ERR_HRESULT(6)
//! �X�N���v�g�ŁA���s�̓A�v���P�[�V�����ɂ���Ē��~����܂����B
#define GT_E_AS_EXECUTION_ABORTED		GT_MK_ERR_HRESULT(7)
//! �X�N���v�g�ŁA���s�́A�������̃X�N���v�g��O�ɂ���ďI�������B
#define GT_E_AS_EXECUTION_EXCEPTION		GT_MK_ERR_HRESULT(8)
//! �X�N���v�g�ŁA�R���e�L�X�g���A�V�������s�̂��߂ɏ�������Ă���B
#define GT_E_AS_EXECUTION_PREPARED		GT_MK_ERR_HRESULT(9)
//! �X�N���v�g�ŁA�R���e�L�X�g������������Ă��܂���B
#define GT_E_AS_EXECUTION_UNINITIALIZED	GT_MK_ERR_HRESULT(10)
//! �X�N���v�g�ŁA�R���e�L�X�g���A���݂̊֐��Ăяo�������s���Ă���B
#define GT_E_AS_EXECUTION_ACTIVE		GT_MK_ERR_HRESULT(11)
//! �X�N���v�g�ŁA�R���e�L�X�g���A�G���[�������������߁A�ď���������K�v������܂��B
#define GT_E_AS_EXECUTION_ERROR			GT_MK_ERR_HRESULT(12)
//@}
