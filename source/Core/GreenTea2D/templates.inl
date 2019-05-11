/*! @file  templates.h
 * @brief テンプレート関連を主に扱う
 * @author kaoken
 * @date 2014/01/17 作成開始
 */
#pragma once

/**
	* シングルトンテンプレートクラス
	* @tparam T 型
	*/
template <typename T> class CSingleton
{
private:
	static T* ms_pSingleton;

public:
	/*!
	* @brief デストラクタ
	*/
	CSingleton()
	{
		assert(!ms_pSingleton);
		ms_pSingleton = (T*)(this);
	}
	/*!
	* @brief コンストラクタ
	*/
	~CSingleton()
	{
		assert(ms_pSingleton);  ms_pSingleton = nullptr;
	}

	/*!
	* @brief シングルトンポインタのセット
	*/
	inline static void SetSingletonPtr(T* my)
	{
		ms_pSingleton = my;
	}
	/*!
	* @brief 自信の参照を取得
	* @return 自信の参照を取得
	*/
	inline static T& GetSingleton()
	{
		assert(ms_pSingleton);  return (*ms_pSingleton);
	}
	/*!
	* @brief シングルトンポインタの取得
	* @return 自信のポインタを取得
	*/
	inline static T* GetSingletonPtr()
	{
		return (ms_pSingleton);
	}
};
template <typename T> T* CSingleton <T>::ms_pSingleton = nullptr;


/**
* 単純な共有ポインタマネージャー
* @tparam _T_INT 整数の型
* @tparam _T_SP  共有ポインタ shared_ptr
*/
template <typename _T_INT, class TargetClass> class SimpleSharedPtrMgr
{
	int m_num;
	std::map< _T_INT, TargetClass>	m_map;
public:
	typedef typename std::map< _T_INT, TargetClass>::iterator iterator;
public:
	//! コンストラクタ
	SimpleSharedPtrMgr()
	{
		m_num = 1;
	}
	inline TargetClass& operator[](_T_INT idx) {
		return m_map[idx];
	}
	/**
		* 長さを返す。
		* @return 長さ
		*/
	inline uint32_t len()
	{
		return m_map.size();
	}
	/**
	* 消す。
	* @param [in] n 番号
	* @return 成功した場合trueを返す。
	*/
	inline bool erase(_T_INT n)
	{
		return m_map.erase(n) != 0;
	}
	/**
	* 探す
	* @param [in] n 番号
	* @return 見つけた場合trueを返す。
	*/
	inline bool find(_T_INT n)
	{
		iterator i;
		if ((i = m_map.find(n)) == m_map.end())return false;
		return true;
	}
	/**
	* マップ・コンテナ内の最初の要素を参照する反復子を返します。
	* @return 反復子を返す。
	*/
	inline iterator begin()
	{
		return m_map.begin();
	}
	/**
	* マップコンテナの過去・エンドの要素を参照する反復子を返します。
	* @return 反復子を返す。
	*/
	inline iterator end()
	{
		return m_map.end();
	}
	/**
	* クリアする。
	*/
	void clear()
	{
		m_map.clear();
	}
	/**
	* 挿入する
	* @param [in] rSP 共有ポインタ型
	* @return 現在の挿入された位置（id）を返す。
	*/
	_T_INT insert(TargetClass &rSP)
	{
		std::pair<iterator, bool> rc;
		rc = m_map.insert(mcMkPair(m_num, rSP));
		if (rc.second) {
			//---- 新しく挿入
			++m_num;
		}
		else {
			//---- すでに存在する
			return 0;
		}
		return m_num - 1;
	}
};


//-----------------------------------------
//! @brief GenericObjectFactoryで使用する
//! @see GenericObjectFactory
//! @tparam BaseClass 基本クラス
//! @tparam SubType   任意の型を表すid
//-----------------------------------------
template <class BaseType, class SubType>
BaseType* GenericObjectCreationFunction() { return new SubType; }

//-----------------------------------------
//! @brief ファクトリー
//!
//! @tparam BaseClass 基本クラス
//! @tparam IdType    任意の型を表すid
//-----------------------------------------
template <class BaseClass, class IdType>
class GenericObjectFactory
{
	typedef BaseClass* (*ObjectCreationFunction)(void);
	std::map<IdType, ObjectCreationFunction> m_creationFunctions;

public:
	//-----------------------------------------
	//! 任意のクラスとidを登録する
	//! @param  id 
	//! @tparam SubClass 任意のクラス
	//! @return 登録に成功した場合はtrueを返す
	//-----------------------------------------
	template <class SubClass>
	bool Register(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt == m_creationFunctions.end())
		{
			m_creationFunctions[id] = &GenericObjectCreationFunction<BaseClass, SubClass>;
			return true;
		}

		return false;
	}
	//-----------------------------------------
	//! 指定idから任意のクラスを作る
	//! @param  id 
	//! @return 成功した場合はそのポインタを返す。
	//-----------------------------------------
	BaseClass* Create(IdType id)
	{
		auto findIt = m_creationFunctions.find(id);
		if (findIt != m_creationFunctions.end())
		{
			ObjectCreationFunction pFunc = findIt->second;
			return pFunc();
		}

		return nullptr;
	}
};

////////////////////////////////////////
// COM継承ヘルパー。

// COMオブジェクトを解放し、ポインタを無効にします。
template <typename InterfaceType>
inline void SafeRelease(InterfaceType** currentObject)
{
	if (*currentObject != nullptr)
	{
		(*currentObject)->Release();
		*currentObject = nullptr;
	}
}


// 非nullの場合は、追加の参照を取得します。
template <typename InterfaceType>
inline InterfaceType* SafeAcquire(InterfaceType* newObject)
{
	if (newObject != nullptr)
		newObject->AddRef();

	return newObject;
}


// 新しいCOMオブジェクトを設定し、古いCOMオブジェクトを解放します。
template <typename InterfaceType>
inline void SafeSet(InterfaceType** currentObject, InterfaceType* newObject)
{
	SafeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}


// 同等のHRESULTへの例外のマップ
inline HRESULT ExceptionToHResult() throw()
{
	try
	{
		throw;  // Rethrow previous exception.
	}
	catch (std::bad_alloc&)
	{
		return E_OUTOFMEMORY;
	}
	catch (...)
	{
		return E_FAIL;
	}
}
