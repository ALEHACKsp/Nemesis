#pragma once

#include <string>

class Logger
{
	//
	//
	// Variables
	//
	//

	/**
	 * \brief Will be inserted at the beginning of the log.
	 */
	static std::string prefix;

public:

	//
	//
	// Important functions
	//
	//

	/**
	 * \brief Prints the specified wide string.
	 * \param format the format string
	 * \param ... the additional parameters
	 */
	static auto Log(std::wstring format, ...) -> VOID;

	/**
	 * \brief Prints the specified string.
	 * \param format the format string
	 * \param ... the additional parameters
	 */
	static auto Log(std::string format, ...) -> VOID;
};
