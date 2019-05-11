#pragma once

#include <Core/greenTea2D.h>



using gt2py_out_err = void (*)(const char* w);

/**
 * Pythoで使用する便利なクラス
 */
class PYUtil
{
private:
	py::dict m_global;			//!< 
	py::dict m_local;			//!< 
	PyObject* m_mainObj;		//!< 
	PyObject* m_catcherObj;		//!< 

	gt2py_out_err m_pyStdOut;
	gt2py_out_err m_pyStdErr;
public:
	PYUtil();

	void Initialize();
	VString getPaths();
	void addPath(const std::string &path, const bool isFromCurrentDir = true);
	TString getError();
};