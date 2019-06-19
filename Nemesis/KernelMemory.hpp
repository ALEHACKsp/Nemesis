#pragma once

#include <Windows.h>

#include "IMemorySource.hpp"
#include "SmartHandle.hpp"

/**
 * \brief The read request ioctl
 */
#define IOCTL_READ_REQUEST				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2222, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

/**
 * \brief The base address request ioctl
 */
#define IOCTL_BASE_ADDRESS_REQUEST		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2223, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

/**
 * \brief The struct for the kernel read request.
 */
typedef struct _READ_REQUEST
{
	//
	// In
	//
	ULONG process_id;
	DWORD_PTR target_address;

	//
	// Both
	//
	SIZE_T buffer_size;

	// 
	// Out
	// 
	BYTE * buffer_address;
} READ_REQUEST, *PREAD_REQUEST;

/**
 * \brief The struct for the base address request.
 */
typedef struct _BASE_ADDRESS_REQUEST
{
	//
	// In
	//
	ULONG process_id;

	// 
	// Out
	// 
	PVOID base_address;
} BASE_ADDRESS_REQUEST, *PBASE_ADDRESS_REQUEST;


class KernelMemory final : public IMemorySource
{
	/**
	 * \brief The symbolic link for the driver.
	 */
	LPCWSTR registry_path = L"\\\\?\\globalroot\\Device\\KernelMemory\\"; // \\\\.\\KernelMemory is not working

	/**
	 * \brief The driver handle.
	 */
	SmartHandle driver_handle = nullptr;

public:

	/**
	 * \brief Connects to the driver.
	 * \param process_id the id of the process
	 */
	explicit KernelMemory(DWORD process_id);

	/**
	 * \brief Reads the memory from the process.
	 * \param start_address the memory start address
	 * \param size the buffer size
	 * \return the memory buffer
	 */
	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) -> std::shared_ptr<BYTE> override;

	/**
	 * \brief Checks whether the memory source is valid.
	 * \return true if valid
	 */
	auto IsValid() -> BOOL override;

	/**
	 * \brief Returns the base address.
	 * \return the base address of the process
	 */
	auto GetBaseAddress() -> DWORD_PTR override;
};
