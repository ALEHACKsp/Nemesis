#pragma once

#include "ProcessMemory.hpp"
#include "PESection.hpp"

#include <algorithm>
#include <vector>
#include <Windows.h>

class PEFile
{
private:
	const DWORD FileAlignmentConstant = 0x200;

	ProcessMemory *pProcessMemory;

public:
	BYTE *pDosStub;
	DWORD DosStubSize;

	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS32 pNTHeader32;
	PIMAGE_NT_HEADERS64 pNTHeader64;

	std::vector<PESection> Sections;

private:
	//
	// Init Functions
	//
	VOID ReadPEHeader();
	VOID SetPEHeaders(PVOID HeaderMemory, DWORD HeaderSize);
	VOID SetSections();

public:
	PEFile(ProcessMemory *pProcessMemory);
	~PEFile();

	//
	// Functions
	//
	VOID SetFileAlignment();
	VOID SetEntryPoint(DWORD_PTR EntryPoint);
	VOID AlignSectionHeaders();
	VOID FixPEHeader();
	VOID RemoveIAT();

	VOID SetSectionSize(PESection &Section, const DWORD_PTR ReadOffset);
	BOOL ReadSection(PESection &Section, const DWORD_PTR ReadOffset);

	DWORD GetInstructionByteCount(BYTE *Data, DWORD Size);
	DWORD AlignValue(DWORD BadValue, DWORD AlignTo);

	//
	// Checks
	//
	BOOL IsValidPeFile();
	BOOL IsPE64();
	BOOL IsPE32();

	//
	// Getters
	//
	DWORD GetImageSize();
	DWORD GetHeaderSize();
	WORD GetSectionCount();
};

