#pragma once

#include <string>
#include <Windows.h>

class FileReader
{
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The path to the file.
	 */
	std::string path;

	/**
	 * \brief The handle to the file.
	 */
	HANDLE file_handle = INVALID_HANDLE_VALUE;

public:

	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Stores the parameter.
	 * \param file_name the name of the dump file
	 */
	FileReader(std::string path);

	/**
	 * \brief The default destructor.
	 */
	~FileReader();


	//
	//
	// Functions
	//
	//

	/**
	 * \brief Reads from a file.
	 * \param offset the file offset
	 * \param size the buffer size
	 * \return the buffer
	 */
	auto ReadFromFile(LONG offset, DWORD size) -> PVOID;

};

