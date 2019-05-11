/*! @file  NumberMgr.h
* @brief 数値を管理するクラス！
* @author kaoken
* @date 2014/03/19 作成開始
*/
#pragma once


#include <Core/greenTea2D.h>


template<typename _T>
class GT2NumberMgr
{
private:
	struct NumberReference{
		_T	id;		//!< 数値
		_T	refCnt;	//!< 参照数

		//!< コンストラクタ
		NumberReference(){
			id = refCnt = 0;
		}
	};
private:
	typedef gtMap <_T, NumberReference>		UseNumberMap;
	typedef gtVector<NumberReference>		FreeVec;

	UseNumberMap	m_useData;		//!< 取得する予定のデータ
	FreeVec			m_freeSlots;	//!< データの空きスロット

	_T	m_numCount;	//!< 現在のカウント値
	_T	m_countMax;	//!< カウント値の最大値
public:

	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	GT2NumberMgr(_T maxNum)  {
		m_numCount = 0;
		m_countMax = maxNum;
		MC_DESTRUCTOR_START(this);
	}
	//-----------------------------------------------------------------------------------
	//! @brief コンストラクタ
	//-----------------------------------------------------------------------------------
	GT2NumberMgr()  {
		m_numCount = 0;
		m_countMax = std::numeric_limits<_T>::max()-1;
		MC_DESTRUCTOR_START(this);

	}
	//-----------------------------------------------------------------------------------
	//! @brief デストラクタ
	//-----------------------------------------------------------------------------------
	~GT2NumberMgr()
	{
		MC_DESTRUCTOR_END(this);
	}

	//-----------------------------------------------------------------------------------
	//! @brief 指定した数値numをセットする
	//! @return 解放後、参照カウンタを１下げた値を返す。0の場合は、完全に解放されたことを示す。
	//-----------------------------------------------------------------------------------
	inline _T GT2NumberMgr::Acquire(_T* pnum)
	{
		NumberReference Tmp;

		UseNumberMap::iterator itTmp;
		//-------------------------------------------
		// 存在する場合はカウントを＋１する。
		//-------------------------------------------
		if (*pnum != 0){
			itTmp = m_useData.find(*pnum);
			if (itTmp != m_useData.end()){
				++itTmp->second.refCnt;
				return (itTmp->second).refCnt;
			}
		}
		//-------------------------------------------
		// フリーリストが空なら、新しいものを追加し、
		// そうでなければ、使用済みの値を使う。
		//-------------------------------------------

		if (m_freeSlots.empty()){
			// コンテナが空
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
	//! @brief 指定した数値numを解放する
	//! @return 解放後、参照カウンタを１下げた値を返す。0の場合は、完全に解放されたことを示す。
	//-----------------------------------------------------------------------------------
	inline _T GT2NumberMgr::Release(_T num)
	{
		NumberReference Tmp;
		// どれか？

		// それが有効なことを確認
		UseNumberMap::iterator itTmp;
		itTmp = m_useData.find(num);
		if (itTmp == m_useData.end()){
			assert(0);
			return 0;
		}

		if (--itTmp->second.refCnt <= 0){
			// 削除 & 未使用のフリーリストに追加
			m_freeSlots.push_back(itTmp->second);
			m_useData.erase(num);
			return 0;
		}

		return itTmp->second.refCnt;
	}

	//-----------------------------------------------------------------------------------
	//! @brief 現在、使用されている数値の数を返す
	//! @return 現在、使用されている数値の数を返す
	//-----------------------------------------------------------------------------------
	inline _T GetUseNumbers(){
		return (_T)m_useData.size();
	}
	//-----------------------------------------------------------------------------------
	//! @brief 現在のカウントの値が、最大カウント値を超えたか？
	//! @return trueの場合超えた。falseの場合超えていない。
	//-----------------------------------------------------------------------------------
	inline bool CheckExceedsNumbers(){
		return ((_T)m_useData.size()) >= m_countMax;
	}
};