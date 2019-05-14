#include <MCLib/util/filesystem.h>
#include <MCLib/util/debugging/CDebugDestructor.h>

using namespace MCLib;
//------------------------------
//! @brief �R���X�g���N�^
//------------------------------
CDebugDestructor::CDebugDestructor(){}
//------------------------------
//! @brief �f�X�g���N�^
//------------------------------
CDebugDestructor::~CDebugDestructor(){
	int n = 0;

#if defined(MC_ANDROID)
	for (IdxI = IdxBegin; IdxI != IdxEnd; ++IdxI)
	{
		__android_log_print(ANDROID_LOG_WARN, "DebugDestructor", "%s", IdxI->second.c_str());
	}
#else
	CMCFile file;

	if (file.Open(MC_LOG_DIR MC_T("/Destructor.log"), MC_T("w")))
	{
		for (auto val : m_SaveData){
			file.Printf(MC_T("%s\r\n"), val.second.c_str());
			++n;
		}
		file.Close();
	}
#	if defined(MC_DEBUG)
	if (n > 0){
		DEBUG_ERR_ICONMMC_EX(
			MC_T("�f�X�g���N�^�G���["),
			MC_T("%d �����f�X�g���N�^���Ă΂�Ă��Ȃ��ꏊ������܂��B\r\n")
			MC_T("�ڂ�������Destructor.log �t�@�C���̒��ɂ���܂��B"),
			n
			);
	}
#	endif
#endif
	m_SaveData.clear();
}
//-----------------------------------------------------------------------------------
//! @brief �C���X�^���X�������N���X�̃R���X�g���N�^�����ꏊ�ŕۑ�
//! @param [in] pFile    �t�@�C����
//! @param [in] line     �s�ԍ�
//! @param [in] pPtrNum  �C���X�^���X�������N���X�̃|�C���^
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void CDebugDestructor::Save(const mcTCHAR* pFile, int line, const mcCHAR* typeidName, const void* pPtrNum){
	mcTCHAR szMsg[1024] = { 0 };
	mcHandleID uNo = R_CAST(mcHandleID, pPtrNum);
	mcTString strTName;

	Convert_SJIS_To_TCHAR(typeidName, &strTName);

#ifdef MC_32
	mc_sprintf(szMsg, MC_T("%s \n[Line:%4d] [%s] (Address:0x%08X)"), pFile, line, strTName.c_str(), uNo);
#else
	mc_sprintf(szMsg, MC_T("%s \n[Line:%4d] [%s] (Address:0x%016llX)"), pFile, line, strTName.c_str(), uNo);
#endif
	m_SaveData.insert(mcMkPair(uNo, szMsg));
}
//-----------------------------------------------------------------------------------
//! @brief �C���X�^���X�������N���X�̃f�X�g���N�^�����ꏊ�ŉ��
//! @param [in] pPtrNum  �C���X�^���X�������N���X�̃|�C���^
//! @return �Ȃ�
//-----------------------------------------------------------------------------------
void CDebugDestructor::Release(const void* pPtrNum){
	m_SaveData.erase(R_CAST(mcHandleID, pPtrNum));
}