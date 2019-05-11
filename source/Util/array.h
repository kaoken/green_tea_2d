//-----------------------------------------------------------------------------------
// ファイル： SimpleArray.h, SimpleArray.cpp
//
// 説　明　：
//   可変の配列を生成する
//　
// 履　歴　：
// 　2006/12/05 Ver.0.1 制作開始
//
//
// 情　報　：
//  Copyright (c) Microsoft Corporation. All rights reserved
// 　
//-----------------------------------------------------------------------------------
#pragma once

#include <Core/greenTea2D.h>

template< typename TYPE >
class MCStackStore
{
private:
	gtVector<TYPE*> m_vStack;
	gtVector<TYPE*> m_vStorePtr;
	size_t m_Minimum;
public:
	MCStackStore() {
		m_Minimum = 64;
		Reserve(64);
	}
	~MCStackStore() {
		gtUINT i;
		for (i = 0; i<m_vStorePtr.size(); ++i) {
			m_vStorePtr[i]->~TYPE();
			free((void*)m_vStorePtr[i]);
		}
		for (i = 0; i<m_vStack.size(); ++i) {
			free((void*)m_vStack[i]);
		}
	}

	void Reserve(size_t szie) {
		m_Minimum = szie;
		m_vStack.reserve(m_Minimum);
		m_vStorePtr.reserve(m_Minimum);

		Optimization();
	}

	/**
	* 最適化する
	*/
	void Optimization() {
		size_t n = (m_vStorePtr.size() + m_vStack.size());
		if (n < m_Minimum) {
			size_t nn = m_Minimum - n;
			for (size_t i = 0; i<nn; ++i) {
				TYPE* p = (TYPE*)malloc(sizeof(TYPE));
				assert(p != nullptr);
				m_vStack.push_back(p);
			}
		}
		else if (n > m_Minimum) {
			size_t nn = n - m_Minimum;
			TYPE* p;
			for (size_t i = 0; i<nn; ++i) {
				p = m_vStack[m_vStack.size() - 1];
				free((void*)p);
				m_vStack.pop_back();
			}
		}
	}

	/**
	* 現在のサイズを返す
	*/
	inline size_t Size() {
		return m_vStorePtr.size();
	}

	inline TYPE* GetPtr(size_t index) {
		return m_vStorePtr[index];
	}

	void Push(const TYPE &val) {
		if (m_vStack.size() <= 0) {
			for (int i = 0; i<16; ++i) {
				TYPE* p = (TYPE*)malloc(sizeof(TYPE));
				assert(p != nullptr);
				m_vStack.push_back(p);
			}
		}
		TYPE* p = m_vStack[m_vStack.size() - 1];
		::new (p) TYPE;
		*p = val;
		m_vStorePtr.push_back(p);
		m_vStack.pop_back();
	}

	/**
		* データをすべてクリアする
		*/
	void Clear() {
		for (size_t i = 0; i<m_vStorePtr.size(); ++i) {
			m_vStorePtr[i]->~TYPE();
			m_vStack.push_back(m_vStorePtr[i]);
		}
		m_vStorePtr.clear();
	}
};
