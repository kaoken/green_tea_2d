/*! @file  NumberMgr.h
* @brief ���l���Ǘ�����N���X�I
* @author kaoken
* @date 2014/03/19 �쐬�J�n
*/
#pragma once


#include <Core/greenTea2D.h>


template<typename _T>
class GT2NumberMgr
{
private:
	struct NumberReference{
		_T	id;		//!< ���l
		_T	refCnt;	//!< �Q�Ɛ�

		//!< �R���X�g���N�^
		NumberReference(){
			id = refCnt = 0;
		}
	};
private:
	typedef gtMap <_T, NumberReference>		UseNumberMap;
	typedef gtVector<NumberReference>		FreeVec;

	UseNumberMap	m_useData;		//!< �擾����\��̃f�[�^
	FreeVec			m_freeSlots;	//!< �f�[�^�̋󂫃X���b�g

	_T	m_numCount;	//!< ���݂̃J�E���g�l
	_T	m_countMax;	//!< �J�E���g�l�̍ő�l
public:

	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	GT2NumberMgr(_T maxNum)  {
		m_numCount = 0;
		m_countMax = maxNum;
		MC_DESTRUCTOR_START(this);
	}
	//-----------------------------------------------------------------------------------
	//! @brief �R���X�g���N�^
	//-----------------------------------------------------------------------------------
	GT2NumberMgr()  {
		m_numCount = 0;
		m_countMax = std::numeric_limits<_T>::max()-1;
		MC_DESTRUCTOR_START(this);

	}
	//-----------------------------------------------------------------------------------
	//! @brief �f�X�g���N�^
	//-----------------------------------------------------------------------------------
	~GT2NumberMgr()
	{
		MC_DESTRUCTOR_END(this);
	}

	//-----------------------------------------------------------------------------------
	//! @brief �w�肵�����lnum���Z�b�g����
	//! @return �����A�Q�ƃJ�E���^���P�������l��Ԃ��B0�̏ꍇ�́A���S�ɉ�����ꂽ���Ƃ������B
	//-----------------------------------------------------------------------------------
	inline _T GT2NumberMgr::Acquire(_T* pnum)
	{
		NumberReference Tmp;

		UseNumberMap::iterator itTmp;
		//-------------------------------------------
		// ���݂���ꍇ�̓J�E���g���{�P����B
		//-------------------------------------------
		if (*pnum != 0){
			itTmp = m_useData.find(*pnum);
			if (itTmp != m_useData.end()){
				++itTmp->second.refCnt;
				return (itTmp->second).refCnt;
			}
		}
		//-------------------------------------------
		// �t���[���X�g����Ȃ�A�V�������̂�ǉ����A
		// �����łȂ���΁A�g�p�ς݂̒l���g���B
		//-------------------------------------------

		if (m_freeSlots.empty()){
			// �R���e�i����
			*pnum = ++m_numCount;
			Tmp.id = m_numCount;
			Tmp.refCnt = 1;
			m_useData.insert(UseNumberMap::value_type(Tmp.id, Tmp));

		}
		else{
			Tmp = m_freeSlots.back();
			*pnum = Tmp.id;
			Tmp.refCnt = 1;
			m_useData.insert(UseNumberMap::value_type(Tmp.id, Tmp));
			m_freeSlots.pop_back();
		}
		return Tmp.refCnt;
	}

	//-----------------------------------------------------------------------------------
	//! @brief �w�肵�����lnum���������
	//! @return �����A�Q�ƃJ�E���^���P�������l��Ԃ��B0�̏ꍇ�́A���S�ɉ�����ꂽ���Ƃ������B
	//-----------------------------------------------------------------------------------
	inline _T GT2NumberMgr::Release(_T num)
	{
		NumberReference Tmp;
		// �ǂꂩ�H

		// ���ꂪ�L���Ȃ��Ƃ��m�F
		UseNumberMap::iterator itTmp;
		itTmp = m_useData.find(num);
		if (itTmp == m_useData.end()){
			assert(0);
			return 0;
		}

		if (--itTmp->second.refCnt <= 0){
			// �폜 & ���g�p�̃t���[���X�g�ɒǉ�
			m_freeSlots.push_back(itTmp->second);
			m_useData.erase(num);
			return 0;
		}

		return itTmp->second.refCnt;
	}

	//-----------------------------------------------------------------------------------
	//! @brief ���݁A�g�p����Ă��鐔�l�̐���Ԃ�
	//! @return ���݁A�g�p����Ă��鐔�l�̐���Ԃ�
	//-----------------------------------------------------------------------------------
	inline _T GetUseNumbers(){
		return (_T)m_useData.size();
	}
	//-----------------------------------------------------------------------------------
	//! @brief ���݂̃J�E���g�̒l���A�ő�J�E���g�l�𒴂������H
	//! @return true�̏ꍇ�������Bfalse�̏ꍇ�����Ă��Ȃ��B
	//-----------------------------------------------------------------------------------
	inline bool CheckExceedsNumbers(){
		return ((_T)m_useData.size()) >= m_countMax;
	}
};