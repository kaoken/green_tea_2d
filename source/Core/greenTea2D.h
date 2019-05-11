#pragma once
#if !defined(__cplusplus)
#  error Not a C + + !!
#endif
#if defined (__STDC__)
#  if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)  /* C11 */
#  else
#    error Compiler not C11
#  endif
#endif
#define _FILE_OFFSET_BITS 64

#include <utility>
#include <regex>

// C std
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <cerrno>
#include <cstring>
#include <cwchar>
#include <cstdlib>

#include <memory>
#include <string>
#include <algorithm>
#include <locale>

// thread
#include <thread>
#include <mutex>

// SLT
#include <map>
#include <unordered_map>
#include <stack>
#include <set>
#include <new>
#include <list>
#include <vector>
#include <queue>

// stream
#include <fstream>
#include <sstream>
#include <strstream>
#include <ostream>
#include <iomanip>

#include <typeinfo>

#include <exception>


// PY Bind11 用
#ifdef _DEBUG
#  undef _DEBUG
#  define TMP_DEBUG
#endif

#include<pybind11/pybind11.h>
#include <pybind11/eval.h>

namespace py = pybind11;
#ifdef TMP_DEBUG
#  define _DEBUG 1
#  undef TMP_DEBUG
#endif

// SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_ttf.h>

//----------------------
// OSごとのマクロ
//----------------------

#if defined(_WIN32) || defined(_WIN64)	// windousか？
#  define _WIN
#  define _WINSOCKAPI_
#  include <Windows.h>
#  include <commctrl.h>
#  include <atlbase.h> 
#  include <tchar.h>
#  include <direct.h>
#  include <winuser.h>
#  include <Richedit.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <psapi.h>
#  include <Dwrite.h>
#  include <d2d1.h>
#  ifdef GetObject
#    undef GetObject
#  endif
#  if defined(_DEBUG)
#    define _CRTDBG_MAP_ALLOC
#    include <crtdbg.h>
#  endif
// OSのバージョンをチェック
#  if defined(_MSC_VER) && (_MSC_VER < 1916)
#    error Smaller version than Visual studio `Visual Studio 2017 version 15.9.7` is not supported.
#  endif
#elif defined(ANDROID) || defined(__ANDROID__)	// Androidか？
#  define GT2_GLES
#  define GT2_ANDROID	1
#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux__) \
	|| defined(linux) || defined(__unix__) || defined(__unix) \
	|| defined(unix) || defined(__ELF__)		// Linuxか？
#  define GT2_LINUX
#elif defined(__APPLE__) || defined(__MACH__)	// Appleか？
#  define GT2_MAC
#endif


//--------------------------------------------
// ブレークポイントマクロ
//--------------------------------------------
#if defined(_M_IX86) || defined(__i386__)
#  if  defined(_DEBUG)
#	 if defined(_MSC_VER)
#		define MCDbgBreak() __asm { int 3 }
#		define MCDbgBreakIF(_flg) if( _flg ){ __asm { int 3 } }
#	 elif defined(__GNUC__)
#		define MCDbgBreak() __asm__ ("int $3");
#		define MCDbgBreakIF(_flg) if( _flg ){ __asm__ ("int $3"); }
#	 else
#		error Unknown compiler
#	 endif
#  else
#		define MCDbgBreak() (__noop)
#		define MCDbgBreakIF(_flg) (__noop)
#  endif
#else
#	define DbgBreak() (__noop)
#	define DbgBreakIF(_flg) (__noop)
#endif

//--------------------------------------------
// OSごとのコンパイラバージョンチェック
//--------------------------------------------
#if defined(_LINUX) || defined(_ANDROID)
#  if defined(__GNUC__) && (GCC_VERSION < 4.9 )
#    error It is not supported version of GCC is smaller than 4.9.
#  endif
#endif



/******************************************
 * 32bit or 64bit ?
 */
#ifdef _WIN32
#  if defined(_WIN64) || defined(_M_X64)
#    define _64BIT
#  else
#    define _32BIT
#  endif
#else
#  ifdef __x86_64__
#    define _64BIT
#  else
#    define _32BIT
#  endif
#endif


namespace std
{
	inline string to_string(bool b) { return b ? "true" : "false"; }
	inline wstring to_wstring(bool b) { return b ? L"true" : L"false"; }
}

#define GT2ZeroMemory(Destination,Length) std::memset((Destination),0,(Length))




#ifdef _DEBUG
#	define KN_NEW new(_NORMAL_BLOCK,__FILE__, __LINE__)
#else
#	define KN_NEW new
#endif

#include "GreenTea2D\hresult.inl"
#include "GreenTea2D\type.inl"
#include "GreenTea2D\templates.inl"
#include "GreenTea2D\config.inl"
#include "GreenTea2D\logger.inl"
#include "GreenTea2D\Exception.inl"


#if !defined(_WIN)
#  include "win.h"
#endif


//------------------------------------------------------------
//! @name キャストマクロ
//------------------------------------------------------------
//@{
//! dynamic_cast
#define	D_CAST( _to, _var) (dynamic_cast<_to>(_var))
	//! static_cast
#define	S_CAST( _to, _var) (static_cast<_to>(_var))
	//! reinterpret_cast
#define	R_CAST( _to, _var) (reinterpret_cast<_to>(_var))
	//! const_cast
#define	C_CAST( _to, _var) (const_cast<_to>(_var))
	//! 通常キャスト
#define N_CAST( _to, _var) ((_to)(_var))

	//! @brief オブジェクトをReleaseを使って解放するタイプに便利なヘルパーテンプレート
	//! @note 例としてこのように使う、shared_ptr<T>(_var,&gt2_helper_release<T>)
	template<class T>
	void gt2_helper_release(T* p) {
		if (p != nullptr) p->Release();
	}
	//! @brief オブジェクトをReleaseを使って解放するタイプに便利なヘルパーテンプレート
	//! @note 例としてこのように使う、shared_ptr<T>(_var,&gt2_helper_release<T>)
	template<class T>
	void gt2_helper_vrelease(T* p) {
		if (p != nullptr) p->VRelease();
	}
	//!< std::auto_ptr<_type>のマクロ
#  define A_PTR std::auto_ptr
	//  #define I_PTR(_type) std::intrusive_ptr<_type>
	//!< std::unique_ptr<_type>のマクロ
#  define U_PTR std::unique_ptr

	//!< std::weak_ptr<_type>のマクロ
#  define W_PTR std::weak_ptr
	//!< std::shared_ptr<_type>のマクロ
#  define S_PTR std::shared_ptr
	//!< std::shared_ptr<_type>(_var,&gt2_helper_release<_type>)のマクロ
#  define S_PTR_RELEASE(_type,_var) S_PTR<_type>(_var,&gt2_helper_release<_type>)
	//!< std::shared_ptr<_type>(_var,&gt2_helper_release<_type>)のマクロ
#  define S_PTR_VRELEASE(_type,_var) S_PTR<_type>(_var,&gt2_helper_vrelease<_type>)
	//!< std::dynamic_pointer_cast<_to>(_var)のマクロ
#  define S_D_CAST( _to, _var ) (std::dynamic_pointer_cast<_to>(_var))
	//!< std::static_pointer_cast<_to>(_var)のマクロ
#  define S_S_CAST( _to, _var ) (std::static_pointer_cast<_to>(_var))
	//!< std::dynamic_pointer_cast<_to>(_var)のマクロ
#  define C_P_CAST( _to, _var ) (std::const_pointer_cast<_to>(_var))
	//!< std::dynamic_pointer_cast<_to>(_var)のマクロ
#  define D_P_CAST( _to, _var ) (std::dynamic_pointer_cast<_to>(_var))


	//!< S_PTR、W_PTRのマクロを使って、型を定義する　_type##SP;_type##WP;
#  define TYPEDEF_S_W_PTR( _type ) \
	typedef S_PTR< _type > _type##SP; \
	typedef W_PTR< _type > _type##WP;
	//@}





	//======================================================================================
	//! @name メンバー関数にスレッド安全性を備えた、そのアクセス・メンバー変数を作ってやるヘルプマクロ
	//======================================================================================
	//@{
#define NO_LOCK() (__noop)

	//-------------------------------------------------------------
	//! @name 通常版
	//-------------------------------------------------------------
	//@{
	//!< 通常のメンバ変数の作成
#define MEMBA_V( _type, _name )		_type m_##_name;
	//!< Set##_name(_type)
#define SET_M_ACCESSOR( _type, _name, _lock )		inline void Set##_name( _type t )	{ _lock; m_##_name = t; };
	//!< _type Get##_name()
#define GET_M_ACCESSOR( _type, _name, _lock )		inline _type Get##_name() const     { _lock; return m_##_name; };
	//!< bool Is##_name()
#define IS_M_ACCESSOR( _name, _lock )			    inline bool Is##_name()	const	    { _lock; return m_##_name; };
	//!< _type Get_name(); Set_name(_type); 
#define GET_M_SET_ACCESSOR( _type, _name, _lock ) \
	SET_M_ACCESSOR(_type, _name, _lock) \
	GET_M_ACCESSOR(_type, _name, _lock)
	//!< bool Is_name(); Set_name(bool); 
#define IS_M_SET_ACCESSOR( _name, _lock ) \
	SET_M_ACCESSOR(bool, _name, _lock) \
	IS_M_ACCESSOR(_name, _lock)

	//!< private _type m_name;　private _type Get_name(); private Set_name(_type); 
#define M_GET_SET_PUB( _type, _name, _lock ) \
private: \
	MEMBA_V(_type, _name); \
public: \
	GET_M_SET_ACCESSOR(_type, _name, _lock)
	//!< private bool m_name;　public bool Is_name(); public Set_name(bool); 
#define M_IS_SET_PUB( _name, _lock ) \
private: \
	MEMBA_V(bool, _name); \
public: \
	IS_M_SET_ACCESSOR(_name, _lock)


	//!< private _type m_name;　private _type Get_name(); private Set_name(_type); 
#define M_GET_SET_PRI( _type, _name, _lock ) \
private: \
	MEMBA_V(_type, _name); \
	GET_M_SET_ACCESSOR(_type, _name, _lock)
	//!< private bool m_name;　private bool Is_name(); private Set_name(bool); 
#define M_IS_SET_PRI( _name, _lock ) \
private: \
	MEMBA_V(bool, _name); \
	IS_M_SET_ACCESSOR(_name, _lock)


	//!< protected _type m_name;　protected _type Get_name(); protected Set_name(_type); 
#define M_GET_SET_PRO( _type, _name, _lock ) \
protected: \
	MEMBA_V(_type, _name); \
	GET_M_SET_ACCESSOR(_type, _name, _lock)
	//!< protected bool m_name;　protected bool Is_name(); protected Set_name(bool); 
#define M_IS_SET_PRO( _name, _lock ) \
protected: \
	MEMBA_V(bool, _name); \
	IS_M_SET_ACCESSOR(_name, _lock)


	//!< private _type m_name;　public _type Get_name(); private Set_name(_type); 
#define M_GET_PUB_SET_PRI( _type, _name, _lock ) \
private: \
	MEMBA_V(_type, _name); \
	SET_M_ACCESSOR(_type, _name, _lock) \
public: \
	GET_M_ACCESSOR(_type, _name, _lock)
	//!< private bool m_name;　public bool Is_name(); private Set_name(bool); 
#define M_IS_PUB_SET_PRI( _name, _lock ) \
private: \
	MEMBA_V(bool, _name); \
	SET_M_ACCESSOR(bool, _name, _lock) \
public: \
	IS_M_ACCESSOR(_name, _lock)


	//!< private _type m_name;　public _type Get_name(); protected Set_name(_type); 
#define M_GET_PUB_SET_PRO( _type, _name, _lock ) \
private: \
	MEMBA_V(_type, _name); \
protected: \
	SET_M_ACCESSOR(_type, _name, _lock) \
public: \
	GET_M_ACCESSOR(_type, _name, _lock)
	//!< private bool m_name;　public bool Is_name(); protected Set_name(bool); 
#define M_IS_PUB_SET_PRO( _name, _lock ) \
private: \
	MEMBA_V(bool, _name); \
protected: \
	SET_M_ACCESSOR(bool, _name, _lock) \
public: \
	IS_M_ACCESSOR(_name, _lock)


	//!< private _type m_name;　public _type Get_name(); Set_name(_type); 
#define M_GET_PUB_SET_PUB( _type, _name, _lock ) \
private: \
	MEMBA_V(_type, _name); \
public: \
	SET_M_ACCESSOR(_type, _name, _lock) \
	GET_M_ACCESSOR(_type, _name, _lock)
	//!< private bool m_name;　public bool Is_name(); Set_name(bool); 
#define M_IS_PUB_SET_PUB( _name, _lock ) \
private: \
	MEMBA_V(bool, _name); \
public: \
	SET_M_ACCESSOR(bool, _name, _lock) \
	IS_M_ACCESSOR(_name, _lock)

	//@}


	//----------------------------------------
	//! @name 通常版:参照
	//----------------------------------------
	//@{
#define SETR_M_ACCESSOR( _type, _name, _lock )		inline void Set##_name( _type &t )  { _lock; m_##_name = t; };
#define GETR_M_ACCESSOR( _type, _name, _lock )		inline _type &Get##_name() const    { _lock; return m_##_name; };
#define GETR_M_SET_ACCESSOR( _type, _name, _member, _lock ) \
	SET_M_ACCESSOR(_type, _name, _lock) \
	GETR_M_ACCESSOR(_type, _name, _lock)
#define GET_M_SETR_ACCESSOR( _type, _name, _member, _lock ) \
	SETR_M_ACCESSOR(_type, _name, _lock) \
	GET_M_ACCESSOR(_type, _name, _lock)
#define GETR_M_SETR_ACCESSOR( _type, _name, _member, _lock ) \
	SETR_M_ACCESSOR(_type, _name, _lock) \
	GETR_M_ACCESSOR(_type, _name, _lock)
	//@}

	//----------------------------------------
	//! @name クラス内にまた構造体を呼び出す為のもの
	//----------------------------------------
	//@{
#define SET_M_MEM( _type, _name, _member, _lock )      inline void Set##_name( _type t )  { _lock; _member.m_##_name = t; };
#define GET_M_MEM( _type, _name, _member, _lock )      inline _type Get##_name() const    { _lock; return _member.m_##_name; };
#define IS_M_MEM( _name, _member, _lock )			   inline bool Is##_name()   const    { _lock; return _member.m_##_name; };
#define GET_M_SET_MEM( _type, _name, _member, _lock ) \
	SET_M_MEM(_type, _name, _member, _lock) \
	GET_M_MEM(_type, _name, _member, _lock)
#define IS_M_SET_MEM( _name, _member, _lock ) \
	SET_M_MEM(bool, _name, _member, _lock) \
	IS_M_MEM(_name, _member, _lock)
	//@}

	//---------------------------------------------
	//! @name クラス内にまた構造体を呼び出す為のポインタ版
	//---------------------------------------------
	//@{
#define SETP_M_MEM( _type, _name, _member, _lock )      inline void Set##_name( _type* t )  { _lock; _member.m_##_name = *t; };
#define GETP_M_MEM( _type, _name, _member, _lock )      inline _type* Get##_name() const    { _lock; return &_member.m_##_name; };
#define ISP_M_MEM( _name, _member, _lock )				inline bool Is##_name()    const    { _lock; return &_member.m_##_name; };
#define GETP_M_SETP_MEM( _type, _name, _member, _lock ) \
	SETP_M_MEM(_type, _name, _member, _lock) \
	GETP_M_MEM(_type, _name, _member, _lock)
#define ISP_M_SETP_MEM( _name, _member, _lock ) \
	SETP_M_MEM(bool, _name, _member, _lock) \
	ISP_M_MEM(_name, _member, _lock)
	//@}

	//---------------------------------------------
	//! @name クラス内にまた構造体を呼び出す為の参照版
	//---------------------------------------------
	//@{
#define SETR_M_MEM( _type, _name, _member, _lock )      inline void Set##_name( _type& t )  { _lock; _member.m_##_name = t; };
#define GETR_M_MEM( _type, _name, _member, _lock )      inline _type& Get##_name() const    { _lock; return _member.m_##_name; };
#define GETR_M_SETR_MEM( _type, _name, _member, _lock ) \
	SETR_M_MEM(_type, _name, _member, _lock) \
	GETR_M_MEM(_type, _name, _member, _lock)
	//@}


	//-------------------------------------------------------------
	//! @name ポインタ版
	//-------------------------------------------------------------
	//@{
#define P_MEMBA_V( _type, _name )		_type* m_p##_name;
#define SETP_M_ACCESSOR( _type, _name, _lock )		inline void Set##_name( _type* t )	   { _lock; m_p##_name = t; };
#define GETP_M_ACCESSOR( _type, _name, _lock )		inline _type* Get##_name()       const { _lock; return m_p##_name; };
#define C_GETP_M_ACCESSOR( _type, _name, _lock )	inline const _type* Get##_name() const { _lock; return m_p##_name; };
#define ISP_M_ACCESSOR( _name, _lock )		        inline bool* Get##_name()        const { _lock; return m_p##_name; };
#define GETP_M_SETP_ACCESSOR( _type, _name, _lock ) SETP_M_ACCESSOR( _type, _name, _lock ) GETP_M_ACCESSOR( _type, _name, _lock )
#define ISP_M_SETP_ACCESSOR( _name, _lock ) SETP_M_ACCESSOR( bool, _name, _lock ) ISP_M_ACCESSOR( _name, _lock )


	//!< private _type* m_name;　public _type Get_name(); Set_name(_type); 
#define MP_GET_SET_PUB( _type, _name, _lock ) \
private: \
	P_MEMBA_V(_type, _name); \
public: \
	GETP_M_SETP_ACCESSOR(_type, _name, _lock)

	//!< private _type* m_name;　protected _type Get_name(); Set_name(_type); 
#define MP_GET_SET_PRO( _type, _name, _lock ) \
private: \
	P_MEMBA_V(_type, _name); \
protected: \
	GETP_M_SETP_ACCESSOR(_type, _name, _lock)

	//!< private _type* m_name;　private _type Get_name(); Set_name(_type); 
#define MP_GET_SET_PRI( _type, _name, _lock ) \
private: \
	P_MEMBA_V(_type, _name); \
	GETP_M_SETP_ACCESSOR(_type, _name, _lock)

	//!< private _type* m_name;　public _type Get_name(); Set_name(_type); 
#define MP_GET_PUB_SET_PRI( _type, _name, _lock ) \
private: \
	P_MEMBA_V(_type, _name); \
	SETP_M_ACCESSOR(_type, _name, _lock) \
public: \
	GETP_M_ACCESSOR(_type, _name, _lock)
	//@}





//======================================================================================
//! @name スレッド関連
//======================================================================================
//@{
typedef S_PTR<std::thread> mcThreadSP;
//@}

//-----------------------------------------
//! @brief 静的ロックヘルパーテンプレートクラス
//!
//!  同じスレッド間（ID）同士の場合ロックしない
//-----------------------------------------
template <typename T>
class StaticRecursiveLock
{
private:
	static std::recursive_mutex ms_mutex;
protected:
	virtual ~StaticRecursiveLock() {}
	inline static void  Create() { Lock(); }
	inline static void  Destroy() { Unlock(); }
	inline static void  Lock() {
		ms_mutex.lock();
	}
	inline static void  Unlock() {
		ms_mutex.unlock();
	}
};
template <typename T> std::recursive_mutex StaticRecursiveLock <T>::ms_mutex;

//-----------------------------------------
//! @brief 普通に使いたいときに使う便利な再帰的ロック
//!
//!  同じスレッド間（ID）同士の場合ロックしない
//-----------------------------------------
class UtilRecursiveLock final : public StaticRecursiveLock<UtilRecursiveLock>
{
public:
	UtilRecursiveLock() { Create(); }
	~UtilRecursiveLock() { Destroy(); }
};
#define UTIL_RECUTSIVE_LOCK()	UtilRecursiveLock mcASAppMainLock

//** 安全にスレッド間でキュー処理をするクラス */
template<class T>
class ThreadSafeQueue
{
	std::queue<T> m_queue;
public:
	ThreadSafeQueue() {}
	virtual ~ThreadSafeQueue() {}

	//! 取り出す
	bool try_pop(T& value)
	{
		UTIL_RECUTSIVE_LOCK();
		if (m_queue.empty()) return false;

		value = m_queue.front();
		m_queue.pop();
		return true;
	}

	//! 空か？
	bool empty() const { UTIL_RECUTSIVE_LOCK(); return m_queue.empty(); }

	//! 入れる
	bool push(const T& value)
	{
		UTIL_RECUTSIVE_LOCK();
		m_queue.push(value);
		return true;
	}
};


template<typename _T>
class SimpleErrMsg {
protected:
	std::string m_simpleErrMsg;
protected:
	virtual _T SetErrMsg(_T ret, const TChar *pFmt, ...)
	{
		UTIL_RECUTSIVE_LOCK();
		if (pFmt == nullptr) { m_simpleErrMsg.clear(); return ret; }

		TChar szMsgTmp[4096] = { 0 };
		va_list args;
		va_start(args, pFmt);

		gt2_vsnprintf(szMsgTmp, 4096, pFmt, args);

		va_end(args);

		m_simpleErrMsg = szMsgTmp;
		return ret;
	}
	const std::string &GetErrMsg() {
		return m_simpleErrMsg;
	}
};

	//-------------------------------------------------------------
	//! @name 解放マクロ
	//-------------------------------------------------------------
	//@{
#ifndef SAFE_DELETE
#  define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#  define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#endif

#ifndef SAFE_RELEASE
#  define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=nullptr; } }
#endif

#ifndef SAFE_SET_GET_M_RELEASE
#  define SAFE_SET_GET_M_RELEASE(_name)     { if(this->Get##_name()) { this->Get##_name()->Release(); this->Set##_name(nullptr); } }
#endif

#ifndef SAFE_ARY_RELEASE
#  define SAFE_ARY_RELEASE(_aryMax, p)      {for(gtUINT iAry=0; iAry<_aryMax; ++iAry){ if(p[iAry] != nullptr) { p[iAry]->Release(); p[iAry]=nullptr; } } }
#endif

#ifndef SAFE_VRELEASE
#  define SAFE_VRELEASE(p)     { if(p) { (p)->VRelease(); (p)=nullptr; } }
#endif
	//@}
#define A_RET_NULL(_val) if( _val == nullptr ){assert(_val);return nullptr;}


#include "GreenTea2D\MsgBox.h"
