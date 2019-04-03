#include "DumpUtils.hpp"

#include "Module.hpp"
#include "FileWriter.hpp"
#include "Dump.hpp"

auto DumpMainModule(const DWORD process_id, const LPCSTR file_name) -> BOOL
{
	//
	// Create the classes
	//
	Dump dump(process_id, file_name);

	//
	// Dump it
	//
	if (dump.DumpProcess())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

auto DumpModule(const DWORD process_id, const DWORD_PTR base_address, const LPCSTR file_name) -> BOOL
{
	//
	// Create the Memory wrapper
	//
	ProcessMemory process_memory(process_id);
	if (!process_memory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the pe file
	//
	Module module(&process_memory, base_address);
	if (!module.Initialize())
	{
		return FALSE;
	}

	module.SetFileAlignment();
	module.AlignSectionHeaders();
	module.FixHeader();
	module.RemoveIat();

	//
	// Write to file
	//
	FileWriter file_writer(file_name);
	if (file_writer.WriteToFile(&module))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

auto DumpMemory(const DWORD process_id, const DWORD_PTR start_address, const DWORD size, const LPCSTR file_name) -> BOOL
{
	//
	// Create the Memory wrapper
	//
	ProcessMemory process_memory(process_id);
	if (!process_memory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the Memory
	//
	Memory memory(&process_memory, start_address, size);
	if (!memory.Initialize())
	{
		return FALSE;
	}

	//
	// Write to file
	//
	FileWriter file_writer(file_name);
	if (file_writer.WriteToFile(&memory))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
