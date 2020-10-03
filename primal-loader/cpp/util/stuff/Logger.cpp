#include "../../hpp/Vendor.hpp"

//Extern.
std::ofstream GLoggerFile (std::string (getenv ("USERPROFILE")) + "\\Documents\\primal.log");

void Logger::SetOutput (Output out) {
	m_output = out;
}

void Logger::AllowDebugPrint () {
	m_isDebugPrintAllowed = true;
}

void Logger::Space (int count) {

	switch (m_output) {

		case Output::FILE:

		   GLoggerFile << "\n" << std::endl;

		  break;

	}

}

void Logger::Info (Type type, std::string message) {

	switch (m_output) {

		case Output::FILE:

			if (type == Type::DEBUG && !m_isDebugPrintAllowed) return;
			GLoggerFile << ConstructFormatedString (type, message) << std::endl;

		   break;

	}

}

void Logger::Free () {

	if (m_output == Output::FILE) GLoggerFile.close ();

}

std::string Logger::ConstructFormatedString (Type type, std::string message) {
	return (std::ostringstream () << "[" << ParseTypePrefix (type) << "-" << CommonUtil::GetCurrentTimeAsString () << "]" << " " << message).str ();
}