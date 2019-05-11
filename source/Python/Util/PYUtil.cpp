#include "PYUtil.h"
#include "PyLogHook.h"
#include <pybind11/stl.h>
#include <pybind11/iostream.h>
//! @see https://docs.python.org/ja/3/library/sys.html?highlight=sys%20path


/**
 * デフォルトのPythonで使用される出力
 * @param w 出力内容
 */
static void PYStdOut(const char* w)
{
	std::string cnv;
	Convert_UTF8_To_SJIS(stringU8((charU8*)w), &cnv);
	TraceA("%s\n", cnv.c_str());
	//TraceA("%s", w);
}
/**
 * デフォルトのPythonで使用されるエラー出力
 * @param w 出力内容
 */
static void PYStdErr(const char* w)
{
	std::string cnv;
	Convert_UTF8_To_SJIS(stringU8((charU8*)w), &cnv);
	TraceA("%s\n", cnv.c_str());
	//TraceA("%s", w);
}

//-----------------------------------------------------------------------------------
//! @brief コンストラクタ
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
		GT_EXCEPT_EX_INIT(_T("Pythonが初期化されていない"), _T("PYSys::PYSys()"));
	}
	Initialize();

}

//-----------------------------------------------------------------------------------
//! @brief PYコンフィグの初期化
//-----------------------------------------------------------------------------------
void PYUtil::Initialize()
{
	//tyti::pylog::redirect_stdout(m_pyStdOut);
	//tyti::pylog::redirect_stderr(m_pyStdErr);
}


//-----------------------------------------------------------------------------------
//! @brief Python内のエラーを文字列として取得する
//-----------------------------------------------------------------------------------
TString PYUtil::getError()
{
	return "";
}


//-----------------------------------------------------------------------------------
//! @brief 実行するPythonのシステムパス群を取得する
//-----------------------------------------------------------------------------------
VString PYUtil::getPaths()
{
	py::module sys = py::module::import("sys");

	return sys.attr("path").cast<std::vector<std::string>>();
}

//-----------------------------------------------------------------------------------
//! @brief 実行するPythonのシステムに読み込むモージュル・ディレクトリのパスを追加する
//! @param [in] path パス
//! @param [in] isFromCurrentDir 'true'の場合、アプリが実行されている
//!  カレントディレクトリからの相対パスとする。デフォルトで'true'
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