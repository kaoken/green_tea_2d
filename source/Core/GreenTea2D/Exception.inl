/*! @m_file  string.inl
 * @brief GreenTea2D.h�t�@�C��������Ăяo�����̂ŁA�ق�����Ăяo���Ȃ��悤�ɁI
 *  ����́A������֌W
 * @author kaoken
 * @date 2019/03/19 �쐬�J�n
 */
#pragma once

/**
 * �I���W�i���̗�O
 */
class GTException : public std::exception
{
protected:
	long	line;			//!< �s�ԍ�
	int		number;			//!< ��O�ԍ�
	TString typeName;		//!< �^��
	TString description;	//!< ��O�̐���
	TString source;			//!< ���\�b�h�܂��͊֐���
	TString file;			//!< ���������\�[�\�t�@�C���p�X
	mutable TString fullDesc;
public:
	enum ExceptionCodes {
		ERR_CANNOT_WRITE_TO_FILE,	//!< �t�@�C���ɏ������ނ��Ƃ͂ł��܂���
		ERR_INVALID_STATE,			//!< �����ȏ��
		ERR_INVALIDPARAMS,			//!< �����ȃp�����[�^�[
		ERR_RENDERINGAPI_ERROR,		//!< �����_�����OAPI�G���[
		ERR_DUPLICATE_ITEM,			//!< �d�������A�C�e��
		ERR_ITEM_NOT_FOUND,			//!< �A�C�e����������Ȃ�
		ERR_FILE_NOT_FOUND,			//!< �t�@�C����������Ȃ�
		ERR_INTERNAL_ERROR,			//!< �����G���[
		ERR_RT_ASSERTION_FAILED,	//!< ���s���ԃA�T�[�V�����Ɏ��s
		ERR_NOT_IMPLEMENTED,		//!< ��������Ă��Ȃ�
		ERR_SCRIPT_ERROR,			//!< �X�N���v�g�֘A�ŃG���[
		ERR_CREAT,					//!< �쐬���G���[
		ERR_REGISTER,				//!< �o�^���G���[
		ERR_CREATED,				//!< ���łɍ쐬�ς�
		ERR_OUTOFMEMORY,			//!< �A�v���Ăяo�����������邤���ŏ\���ȃ������[�����蓖�Ă邱�Ƃ��ł��܂���ł����B
		ERR_INITIALIZATION			//!< �������Ɏ��s
	};
	/** �ʏ�R���X�g���N�^
	*/
	GTException(int num, const TString& desc, const TString& src) :
		line(0),
		number(num),
		description(desc),
		source(src)
	{
		Logger::Log(Logger::T_FATAL, true, this->GetFullDescription(), nullptr, nullptr, 0);
	}

	/** ���x�ȃR���X�g���N�^�B
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

	/** �R�s�[�R���X�g���N�^
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

	//! std::exception �̌݊��ŕK�v
	virtual ~GTException() noexcept {}

	/** ������Z�q
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

	/** ���̃G���[�̊��S�Ȑ����𕶎���ŕԂ��܂�
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

	/** �G�[���[�R�[�h���擾
	*/
	virtual int GetNumber() const throw()

	{
		return number;
	}

	/** ���ƂȂ�֐����擾
	*/
	virtual const TString &GetSource() const { return source; }

	/** ���ƂȂ�t�@�C�������擾
	*/
	virtual const TString &GetFile() const { return file; }

	/** �s�ԍ����擾
	*/
	virtual long GetLine() const { return line; }

	/** ���̗�O�̗B��́u�����v�t�B�[���h�ɕ������Ԃ��܂��B
	getFullDescriptionto�g�p���A�s�ԍ����܂ރG���[�̊��S�Ȑ������擾
	�G���[�ԍ��Ƃǂ̂悤�ȋ@�\����O���X���[���܂����B
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
 * �I���W�i���̗�O�쐬�t�@�N�g���[
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


//! �V���v���ȗ�O
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

// �������s��
#define GT_IF_EXCEPT_OUTOFMEMORY(_p, _func, src) \
	if( _p == nullptr) { \
		GT_EXCEPT(GTException::ERR_OUTOFMEMORY, \
			_T("'") \
			_func \
			_T("', �������s���ɂ�莸�s�I"), src); \
	}

#define GT_IF_EXCEPT_EX_OUTOFMEMORY(_p,_func, src) \
	if( _p == nullptr) { \
		GT_EXCEPT(GTException::ERR_OUTOFMEMORY, \
			_T("'") \
			_func \
			_T("', �������s���ɂ�莸�s�I"), src); \
	}
