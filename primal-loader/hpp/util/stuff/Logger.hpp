#pragma once

#include "../../Vendor.hpp"

//File to r/w log.
extern std::ofstream GLoggerFile;

class Logger {

public:

	//Used for get type of current log method. (Rem - If you wanna custom output add here you type)
	enum class Output {
		FILE
	};

	//Just prefixes.
	enum class Type {

		INFO		,
		RUNTIME		,
		FRAMEWORK	,
		EXCEPTION	,
		DEBUG

	};

	/**
	 * Set logger output.
	 * 
	 * @param out - Logger type.
	 * @rem - default value is FILE.
	 **/

	void SetOutput (Output out),

    /**
	 * Allow debug print.
	 * 
	 * @rem Default value - false.
     **/

	AllowDebugPrint (),

	/**
	 * Just add empty line to current output.
	 *
	 * @param count - Lines count.
	 * @rem Default value - 1.
	 **/

	 Space (int count = 1),

	/**
	 * Write or show message to logger.
	 * 
	 * @param type    - Prefix.
	 * @param message - Message to print.
	 **/

	 Info (Type type, std::string message),

	 /**
  	  * Clean up.
	  **/

     Free ();

	 /**
	  * Build string and format it for print.
	  *
	  * @param type    - Prefix.
	  * @param message - Message to format.
	  * @rem -
	  * Input:  printf (Logger::Type::INFO, "Six six six");
	  * Output: [13:37/INFO] Six six six.
	  **/

	std::string ConstructFormatedString (Type type, std::string message);

private:

	/**
	 * @return Prefix name.
	 **/

	const char* ParseTypePrefix (Type type) {

		switch (type) {

			case Type::INFO:		return "INFO";
			case Type::RUNTIME:		return "RUNTIME";
			case Type::FRAMEWORK:	return "FRAMEWORK";
			case Type::EXCEPTION:	return "EXCEPTION";
			case Type::DEBUG:		return "DEBUG";

		}

		return "UNKNOWN";
	}

private:

	Output m_output = Output::FILE;
	bool m_isDebugPrintAllowed = false;

};