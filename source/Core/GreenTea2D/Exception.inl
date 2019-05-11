/*! @m_file  string.inl
 * @brief GreenTea2D.hファイル内から呼び出されるので、ほかから呼び出さないように！
 *  これは、文字列関係
 * @author kaoken
 * @date 2019/03/19 作成開始
 */
#pragma once

/**
 * オリジナルの例外
 */
class GTException : public std::exception
{
protected:
	long	line;			//!< 行番号
	int		number;			//!< 例外番号
	TString typeName;		//!< 型名
	TString description;	//!< 例外の説明
	TString source;			//!< メソッドまたは関数名
	TString file;			//!< 発生したソーソファイルパス
	mutable TString fullDesc;
public:
	enum ExceptionCodes {
		ERR_CANNOT_WRITE_TO_FILE,	//!< ファイルに書き込むことはできません
		ERR_INVALID_STATE,			//!< 無効な状態
		ERR_INVALIDPARAMS,			//!< 無効なパラメーター
		ERR_RENDERINGAPI_ERROR,		//!< レンダリングAPIエラー
		ERR_DUPLICATE_ITEM,			//!< 重複したアイテム
		ERR_ITEM_NOT_FOUND,			//!< アイテムが見つからない
		ERR_FILE_NOT_FOUND,			//!< ファイルが見つからない
		ERR_INTERNAL_ERROR,			//!< 内部エラー
		ERR_RT_ASSERTION_FAILED,	//!< 実行時間アサーションに失敗
		ERR_NOT_IMPLEMENTED,		//!< 実装されていない
		ERR_SCRIPT_ERROR,			//!< スクリプト関連でエラー
		ERR_CREAT,					//!< 作成時エラー
		ERR_REGISTER,				//!< 登録時エラー
		ERR_CREATED,				//!< すでに作成済み
		ERR_OUTOFMEMORY,			//!< アプリ呼び出しを完了するうえで十分なメモリーを割り当てることができませんでした。
		ERR_INITIALIZATION			//!< 初期化に失敗
	};
	/** 通常コンストラクタ
	*/
	GTException(int num, const TString& desc, const TString& src) :
		line(0),
		number(num),
		description(desc),
		source(src)
	{
		Logger::Log(Logger::T_FATAL, true, this->GetFullDescription(), nullptr, nullptr, 0);
	}

	/** 高度なコンストラクタ。
	*/
	GTException(int num, const TString& desc, const TString& src, const TString& typ, const TChar* pFile, long lin) :
		line(lin),
		number(num),
		typeName(typ),
		description(desc),
		source(src),
		file(pFile)
	{
		Logger::Log(Logger::T_FATAL, true, this->GetFullDescription(), nullptr, nullptr, 0);
	}

	/** コピーコンストラクタ
	*/
	GTException(const GTException& rhs) :
		line(rhs.line),
		number(rhs.number),
		typeName(rhs.typeName),
		description(rhs.description),
		source(rhs.source),
		file(rhs.file)
	{
	}

	//! std::exception の互換で必要
	virtual ~GTException() noexcept {}

	/** 代入演算子
	*/
	void operator = (const GTException& rhs)
	{
		description = rhs.description;
		number = rhs.number;
		source = rhs.source;
		file = rhs.file;
		line = rhs.line;
		typeName = rhs.typeName;
	}

	/** このエラーの完全な説明を文字列で返します
	*/
	virtual const TString& GetFullDescription() const 
	{
		if (fullDesc.empty())
		{
			gt2_tstringstream desc;

			desc << _T("Green Tea 2D EXCEPTION(") << number << _T(":") << typeName << _T("): ")
				<< description;

			if (!source.empty())
				desc << _T(" in ") << source;

			if (line > 0)
			{
				desc << _T(" at ") << file << _T(" (line ") << line << _T(")");
			}

			fullDesc = desc.str();
		}

		return fullDesc;
	}

	/** エーラーコードを取得
	*/
	virtual int GetNumber() const throw()

	{
		return number;
	}

	/** 元となる関数を取得
	*/
	virtual const TString &GetSource() const { return source; }

	/** 元となるファイル名を取得
	*/
	virtual const TString &GetFile() const { return file; }

	/** 行番号を取得
	*/
	virtual long GetLine() const { return line; }

	/** この例外の唯一の「説明」フィールドに文字列を返します。
	getFullDescriptionto使用し、行番号を含むエラーの完全な説明を取得
	エラー番号とどのような機能が例外をスローしました。
	*/
	virtual const TString &GetDescription() const { return description; }

	//! Override std::exception::what
	virtual const char* what() const throw() {
#ifdef _UNICODE
		return ToSJIS(GetFullDescription()).c_str();
#else
		return GetFullDescription().c_str();
#endif
	}

};

template <int num>
struct GTExceptionCodeType
{
	enum { number = num };
};

#define GTExceptionCreateClass(_className) \
	class _className : public GTException { \
	public: \
		_className(int inNumber, const TString& inDescription, const TString& inSource, const TChar* pFile, long inLine) \
			: GTException(inNumber, inDescription, inSource, _T(#_className), pFile, inLine) {} \
		_className(int inNumber, const TString& inDescription, const TString& inSource) \
			: GTException(inNumber, inDescription, inSource ) {} \
	};

GTExceptionCreateClass(GTUnimplementedException)
GTExceptionCreateClass(GTFileNotFoundException)
GTExceptionCreateClass(GTIOException)
GTExceptionCreateClass(GTInvalidStateException)
GTExceptionCreateClass(GTInvalidParametersException)
GTExceptionCreateClass(GTItemIdentityException)
GTExceptionCreateClass(GTItemDuplicateException)
GTExceptionCreateClass(GTInternalErrorException)
GTExceptionCreateClass(GTRenderingAPIException)
GTExceptionCreateClass(GTRuntimeAssertionException)
GTExceptionCreateClass(GTScriptErrorException)
GTExceptionCreateClass(GTCreatedException)
GTExceptionCreateClass(GTCreatException)
GTExceptionCreateClass(GTRegisterException)
GTExceptionCreateClass(GTOutOfMemoryException)
GTExceptionCreateClass(GTInitializationException)

#define GTExceptionFactoryInCreateMethod(_className,_err_type) \
	static _className Create( \
		GTExceptionCodeType<GTException::_err_type> code, const TString &desc, const TString &src, const TChar* pFile, long line) \
	{  return _className(code.number, desc, src, pFile, line);  } \
	static _className Create( \
		GTExceptionCodeType<GTException::_err_type> code, const TString &desc, const TString &src) \
	{  return _className(code.number, desc, src);  }

/**
 * オリジナルの例外作成ファクトリー
 */
class GTExceptionFactory
{
private:
	//! Private constructor, no construction
	GTExceptionFactory() {}
public:
	GTExceptionFactoryInCreateMethod(GTUnimplementedException,		ERR_NOT_IMPLEMENTED)
	GTExceptionFactoryInCreateMethod(GTFileNotFoundException,		ERR_FILE_NOT_FOUND)
	GTExceptionFactoryInCreateMethod(GTIOException,					ERR_CANNOT_WRITE_TO_FILE)
	GTExceptionFactoryInCreateMethod(GTInvalidStateException,		ERR_INVALID_STATE)
	GTExceptionFactoryInCreateMethod(GTInvalidParametersException,	ERR_INVALIDPARAMS)
	GTExceptionFactoryInCreateMethod(GTItemIdentityException,		ERR_ITEM_NOT_FOUND)
	GTExceptionFactoryInCreateMethod(GTItemDuplicateException,		ERR_DUPLICATE_ITEM)
	GTExceptionFactoryInCreateMethod(GTInternalErrorException,		ERR_INTERNAL_ERROR)
	GTExceptionFactoryInCreateMethod(GTRenderingAPIException,		ERR_RENDERINGAPI_ERROR)
	GTExceptionFactoryInCreateMethod(GTRuntimeAssertionException,	ERR_RT_ASSERTION_FAILED)
	GTExceptionFactoryInCreateMethod(GTScriptErrorException,		ERR_SCRIPT_ERROR)
	GTExceptionFactoryInCreateMethod(GTCreatedException,			ERR_CREATED)
	GTExceptionFactoryInCreateMethod(GTCreatException,				ERR_CREAT)
	GTExceptionFactoryInCreateMethod(GTRegisterException,			ERR_REGISTER)
	GTExceptionFactoryInCreateMethod(GTOutOfMemoryException,		ERR_OUTOFMEMORY)
	GTExceptionFactoryInCreateMethod(GTInitializationException,		ERR_INITIALIZATION)

};


//! シンプルな例外
#ifdef _UNICODE
#  define	GT_EXCEPTION(_msg) throw std::exception( _msg )
#else
#  define	GT_EXCEPTION(_msg) throw std::exception( _msg )
#endif

#define	GT_EXCEPTION(_msg)				throw std::exception( _msg )

#define GT_EXCEPT(num, desc, src)		throw GTExceptionFactory::Create( GTExceptionCodeType<num>(), desc, src );

#define GT_EXCEPT_EX(num, desc, src)	throw GTExceptionFactory::Create( \
	GTExceptionCodeType<num>(), desc, src, __TFILE__, __LINE__ );

#define GT_EXCEPT_SCRIPT(desc, src)		GT_EXCEPT(GTException::ERR_SCRIPT_ERROR, desc, src)
#define GT_EXCEPT_EX_SCRIPT(desc, src)	GT_EXCEPT_EX(GTException::ERR_SCRIPT_ERROR, desc, src)

#define GT_EXCEPT_EX_INIT(desc, src)	GT_EXCEPT_EX(GTException::ERR_INITIALIZATION, desc, src)

// メモリ不足
#define GT_IF_EXCEPT_OUTOFMEMORY(_p, _func, src) \
	if( _p == nullptr) { \
		GT_EXCEPT(GTException::ERR_OUTOFMEMORY, \
			_T("'") \
			_func \
			_T("', メモリ不足により失敗！"), src); \
	}

#define GT_IF_EXCEPT_EX_OUTOFMEMORY(_p,_func, src) \
	if( _p == nullptr) { \
		GT_EXCEPT(GTException::ERR_OUTOFMEMORY, \
			_T("'") \
			_func \
			_T("', メモリ不足により失敗！"), src); \
	}
