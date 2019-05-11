#include <MCLib/util/filesystem.h>
#include <MCLib/util/debugging/CDebugDestructor.h>

using namespace MCLib;
//------------------------------
//! @brief コンストラクタ
//------------------------------
CDebugDestructor::CDebugDestructor(){}
//------------------------------
//! @brief デストラクタ
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
			MC_T("デストラクタエラー"),
			MC_T("%d ヵ所デストラクタが呼ばれていない場所があります。\r\n")
			MC_T("詳しい情報はDestructor.log ファイルの中にあります。"),
			n
			);
	}
#	endif
#endif
	m_SaveData.clear();
}
//-----------------------------------------------------------------------------------
//! @brief インスタンス化したクラスのコンストラクタした場所で保存
//! @param [in] pFile    ファイル名
//! @param [in] line     行番号
//! @param [in] pPtrNum  インスタンス化したクラスのポインタ
//! @return なし
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
//! @brief インスタンス化したクラスのデストラクタされる場所で解放
//! @param [in] pPtrNum  インスタンス化したクラスのポインタ
//! @return なし
//-----------------------------------------------------------------------------------
void CDebugDestructor::Release(const void* pPtrNum){
	m_SaveData.erase(R_CAST(mcHandleID, pPtrNum));
}