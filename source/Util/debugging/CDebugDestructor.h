/*! @file  CDebugDestructor.h
* @brief �f�X�g���N�^�A�R���X�g���N�^���ɐݒu���āA��������̃��O���Ƃ�
* @author kaoken
* @date 2014/01/17 �쐬�J�n
*/
#pragma once

#include <MCLib/MCLib.h>

namespace MCLib
{
	//------------------------------
	//! @brief �f�X�g���N�^�A�R���X�g���N�^���ɐݒu���āA��������̃��O���Ƃ�N���X
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
	//!< �R���g���N�^�[���Ő錾����}�N��
#	define MC_DESTRUCTOR_START(_ptr_no_uint)	CDebugDestructor::GetSingleton().Save(MC_T(__FILE__),__LINE__, typeid(*_ptr_no_uint).name(), _ptr_no_uint)
	//!< �f�X�g���N�^�[���Ő錾����}�N��
#	define MC_DESTRUCTOR_END(_ptr_no_uint)		CDebugDestructor::GetSingleton().Release(_ptr_no_uint)
#else
#	define MC_DESTRUCTOR_START(_ptr_no_uint) (__noop)
#	define MC_DESTRUCTOR_END(_ptr_no_uint) (__noop)
#endif

};// namespace MCLib
