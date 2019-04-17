﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Nemesis.Utils
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct MemorySourcesStruct
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 12)]
        public IntPtr[] MemorySources;
    }


    [StructLayout(LayoutKind.Sequential)]
    internal struct Driver
    {
        public long ImageBase;
        public int ImageSize;
        public ushort OffsetToFileName;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string FullPathName;
    }


    [StructLayout(LayoutKind.Sequential)]
    internal struct Process
    {

    }

    internal class NemesisImports
    {
        [DllImport("Nemesis.dll")]
        protected static extern bool DumpProcessExport(int processId, string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpModuleExport(int processId, IntPtr baseAddress, string fileName);

        [DllImport("Nemesis.dll")]
        protected static extern bool DumpMemoryExport(int processId, IntPtr startAddress, uint size, string fileName);


        [DllImport("Nemesis.dll")]
        protected static extern void GetMemorySourcesExport(ref MemorySourcesStruct structure);

        [DllImport("Nemesis.dll")]
        protected static extern bool SetMemorySourceExport(string memorySource);

        
        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool GetDriverListElementExport(uint index, ref Driver structure);

        [DllImport("D:\\3_Programming\\1_Github\\Nemesis\\x64\\Debug\\Nemesis.dll")]
        protected static extern bool GetProcessListElementExport(uint index, ref Process structure);
    }

    internal class NemesisApi : NemesisImports
    {
        public static bool DumpProcess(int processId, string fileName)
        {
            return DumpProcessExport(processId, fileName);
        }

        public static bool DumpModule(int processId, IntPtr baseAddress, string fileName)
        {
            return DumpModuleExport(processId, baseAddress, fileName);
        }

        public static bool DumpMemory(int processId, IntPtr startAddress, uint size, string fileName)
        {
            return DumpMemoryExport(processId, startAddress, size, fileName);
        }


        public static bool SetMemorySource(string memorySource)
        {
            return SetMemorySourceExport(memorySource);
        }

        public static List<string> GetMemorySources()
        {
            //
            // Create a new struct
            //
            var structure = new MemorySourcesStruct();

            //
            // Get the memory sources
            //
            GetMemorySourcesExport(ref structure);

            //
            // Convert the pointers to strings and return the list
            //
            return (from pointer in structure.MemorySources
                where pointer != IntPtr.Zero
                select Marshal.PtrToStringAnsi(pointer)).ToList();
        }


        public static List<Driver> GetDriverList()
        {
            var list = new List<Driver>();

            //
            // Get the memory sources
            //
            for (uint index = 0; index < 512; index++)
            {
                //
                // Create the driver object
                //
                var structure = new Driver();

                //
                // Get the driver at the specified index
                //
                if (!GetDriverListElementExport(index, ref structure))
                {
                    break;
                }

                //
                // Add the item to the list
                //
                list.Add(structure);
            }

            //
            // Return the list
            //
            return list;
        }

        public static List<Process> GetProcessList()
        {
            var list = new List<Process>();

            //
            // Get the memory sources
            //
            for (uint index = 0; index < 512; index++)
            {
                //
                // Create the driver object
                //
                var structure = new Process();

                //
                // Get the driver at the specified index
                //
                if (!GetProcessListElementExport(index, ref structure))
                {
                    break;
                }

                //
                // Add the item to the list
                //
                list.Add(structure);
            }

            //
            // Return the list
            //
            return list;
        }
    }
}