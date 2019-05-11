#include "pyAppConfig.h"
#include "Util/PYUtil.h"
#include "Util/pyErrOut.h"
#include <pybind11/embed.h>
#include <iostream>

namespace py = pybind11;



//-----------------------------------------------------------------------------------
// Python側で使用するモデルの登録
//-----------------------------------------------------------------------------------
PYBIND11_MODULE(gt2_config, m) {
	//m.doc() = "test";
	//py::class_<PYConfig>(m, "GT2Config")
	//	.def(py::init())
	//	.PY11_DEF_POPERTY("isWindowMaximizeButton", WindowMaximizeButton, PYConfig)
	//	.PY11_DEF_POPERTY("isWindowMinimizeButton", WindowMinimizeButton, PYConfig);
		//.PY11_DEF_POPERTY("isResizableWindow", ResizableWindow, PYConfig)
		//.PY11_DEF_POPERTY("isFullScreenFromAltEnterKey", FullScreenFromAltEnterKey, PYConfig)
		//.PY11_DEF_POPERTY("isExitAppFromALtF4Key", ExitAppFromALtF4Key, PYConfig)
		//.PY11_DEF_POPERTY("isExitAppFromEscKey", ExitAppFromEscKey, PYConfig)
		//.PY11_DEF_POPERTY("isPauseAppFromPauseKey", PauseAppFromPauseKey, PYConfig);

	//r = engine->RegisterGlobalFunction("void RegisterState(const string &in, const string &in, const string &in)", asFUNCTION(PY_RegisterState), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void StartState(const string &in)", asFUNCTION(PY_StartState), asCALL_CDECL);  PY_ERR_ASSERT();
	// 関数の登録
	//r = engine->RegisterGlobalFunction("void SetAppClassName(const string &in)", asFUNCTION(PY_SetAppClassName), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void SetTitle(const string &in)", asFUNCTION(PY_SetTitle), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void SetScreenResolution(uint,uint)", asFUNCTION(PY_SetScreenResolution), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void CheckMinCPU_MHz(uint)", asFUNCTION(PY_CheckMinCPU_MHz), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void CheckMinMemorySize(uint)", asFUNCTION(PY_CheckMinCPU_MHz), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void CheckMinVideoMemorySize(uint)", asFUNCTION(PY_CheckMinVideoMemorySize), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void CheckMinTextureSize(uint)", asFUNCTION(PY_CheckMinTextureSize), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void SetConstantFrameTime(bool,float)", asFUNCTION(PY_SetConstantFrameTime), asCALL_CDECL);  PY_ERR_ASSERT();
	//r = engine->RegisterGlobalFunction("void SetWaitFrameTime(bool,float)", asFUNCTION(PY_SetWaitFrameTime), asCALL_CDECL);  PY_ERR_ASSERT();

	//r = engine->RegisterGlobalFunction("bool AddFontPath(const string &in)", asFUNCTION(PY_AddFontPath), asCALL_CDECL);  PY_ERR_ASSERT();

}


//-----------------------------------------------------------------------------------
//! @brief 実行
//! 
//-----------------------------------------------------------------------------------
void PYConfig::Run()
{
	//py::scoped_interpreter guard{};

	auto configMule = py::detail::embedded_module("gt2_config", PyInit_gt2_config);
	py::scoped_interpreter guard{};

		PYUtil pySys;
	//wchar_t* program = Py_DecodeLocale(argv[0], NULL);
	//if (program == NULL) {
	//	fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
	//	exit(1);
	//}
	//Py_SetProgramName(program);  /* optional but recommended */
	



	try {
		// ここにコードを記述していく


		pySys.addPath("Media\\Script");

		//py::exec(
		//	"import gt2config\n"
		//);
		py::exec(
			"print(\"test1\")\n"
			"print(\"test2\")\n"
		);
		auto tttt = pySys.getPaths();
		auto s = pySys.getError();
		int n = 0;
	}
	catch (py::error_already_set & e) {
		TraceA("Python error.%s\n", e.what());
	}
	catch (std::exception & e) {
		TraceA("error.%s\n", e.what());

	}




	auto ty = gGt2Config.GetWindowMaximizeButton();
	int n = 0;
	//PyMem_RawFree(program);
}
