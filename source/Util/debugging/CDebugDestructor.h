/*! @file  CDebugDestructor.h
* @brief デストラクタ、コンストラクタ内に設置して、解放処理のログをとる
* @author kaoken
* @date 2014/01/17 作成開始
*/
#pragma once

#include <MCLib/MCLib.h>

namespace MCLib
{
	//------------------------------
	//! @brief デストラクタ、コンストラクタ内に設置して、解放処理のログをとるクラス
	//------------------------------
	class CDebugDestructor : public CSingleton<CDebugDestructor>
	{
		mcMap<mcHandleID, mcTString> m_SaveData;
	public:
		CDebugDestructor();
		~CDebugDestructor();

		void Save(const mcTCHAR* pFile, int line, const mcCHAR* typeidName, const void* pPtrNum);
		void Release(const void* pPtrNum);

	};

#ifdef MC_DEBUG
	//!< コントラクター内で宣言するマクロ
#	define MC_DESTRUCTOR_START(_ptr_no_uint)	CDebugDestructor::GetSingleton().Save(MC_T(__FILE__),__LINE__, typeid(*_ptr_no_uint).name(), _ptr_no_uint)
	//!< デストラクター内で宣言するマクロ
#	define MC_DESTRUCTOR_END(_ptr_no_uint)		CDebugDestructor::GetSingleton().Release(_ptr_no_uint)
#else
#	define MC_DESTRUCTOR_START(_ptr_no_uint) (__noop)
#	define MC_DESTRUCTOR_END(_ptr_no_uint) (__noop)
#endif

};// namespace MCLib
