#pragma once
#include <Core/greenTea2D.h>


class PyStdErrOutStreamRedirect {
	py::object m_stdout;
	py::object m_stderr;
	py::object m_stdout_buffer;
	py::object m_stderr_buffer;
public:
	PyStdErrOutStreamRedirect() {
		auto sysm = py::module::import("sys");
		m_stdout = sysm.attr("stdout");
		m_stderr = sysm.attr("stderr");
		auto stringio = py::module::import("io").attr("StringIO");
		m_stdout_buffer = stringio();  // Other filelike object can be used here as well, such as objects created by pybind11
		m_stderr_buffer = stringio();
		sysm.attr("stdout") = m_stdout_buffer;
		sysm.attr("stderr") = m_stderr_buffer;
	}
	std::string stdoutString() {
		m_stdout_buffer.attr("seek")(0);
		return py::str(m_stdout_buffer.attr("read")());
	}
	std::string stderrString() {
		m_stderr_buffer.attr("seek")(0);
		return py::str(m_stderr_buffer.attr("read")());
	}
	~PyStdErrOutStreamRedirect() {
		auto sysm = py::module::import("sys");
		sysm.attr("stdout") = m_stdout;
		sysm.attr("stderr") = m_stderr;
	}
};