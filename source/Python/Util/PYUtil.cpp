#include "PYUtil.h"
#include "PyLogHook.h"
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
//! @see https://docs.python.org/ja/3/library/sys.html?highlight=sys%20path


/**
 * �f�t�H���g��Python�Ŏg�p�����o��
 * @param w �o�͓��e
 */
static void PYStdOut(const char* w)
{
	std::string cnv;
	Convert_UTF8_To_SJIS(stringU8((charU8*)w), &cnv);
	TraceA("%s\n", cnv.c_str());
	//TraceA("%s", w);
}
/**
 * �f�t�H���g��Python�Ŏg�p�����G���[�o��
 * @param w �o�͓��e
 */
static void PYStdErr(const char* w)
{
	std::string cnv;
	Convert_UTF8_To_SJIS(stringU8((charU8*)w), &cnv);
	TraceA("%s\n", cnv.c_str());
	//TraceA("%s", w);
}

//-----------------------------------------------------------------------------------
//! @brief �R���X�g���N�^
//-----------------------------------------------------------------------------------
PYUtil::PYUtil() :
	m_mainObj(nullptr),
	m_catcherObj(nullptr),
	m_pyStdOut(PYStdOut),
	m_pyStdErr(PYStdErr)
{
	m_global	= py::dict(py::module::import("__main__").attr("__dict__"));
	m_local		= py::dict();

	if (!Py_IsInitialized) {
		GT_EXCEPT_EX_INIT(_T("Python������������Ă��Ȃ�"), _T("PYSys::PYSys()"));
	}
	Initialize();

}

//-----------------------------------------------------------------------------------
//! @brief PY�R���t�B�O�̏�����
//-----------------------------------------------------------------------------------
void PYUtil::Initialize()
{
	//tyti::pylog::redirect_stdout(m_pyStdOut);
	//tyti::pylog::redirect_stderr(m_pyStdErr);
}


//-----------------------------------------------------------------------------------
//! @brief Python���̃G���[�𕶎���Ƃ��Ď擾����
//-----------------------------------------------------------------------------------
TString PYUtil::getError()
{
	return "";
}


//-----------------------------------------------------------------------------------
//! @brief ���s����Python�̃V�X�e���p�X�Q���擾����
//-----------------------------------------------------------------------------------
VString PYUtil::getPaths()
{
	py::module sys = py::module::import("sys");

	return sys.attr("path").cast<std::vector<std::string>>();
}

//-----------------------------------------------------------------------------------
//! @brief ���s����Python�̃V�X�e���ɓǂݍ��ރ��[�W�����E�f�B���N�g���̃p�X��ǉ�����
//! @param [in] path �p�X
//! @param [in] isFromCurrentDir 'true'�̏ꍇ�A�A�v�������s����Ă���
//!  �J�����g�f�B���N�g������̑��΃p�X�Ƃ���B�f�t�H���g��'true'
//-----------------------------------------------------------------------------------
void PYUtil::addPath(const std::string& path, const bool isFromCurrentDir)
{
	std::string code =
		"import sys\n"
		"import os\n";
	if (isFromCurrentDir) {
		code +=
			"sys.path.append(os.path.dirname(os.path.abspath(\"__file__\"))+\"\\" + path + "\")\n";
	}
	else {
		code += 
			"sys.path.append(\"" + path + "\")\n";
	}
	py::exec(code.c_str());
}