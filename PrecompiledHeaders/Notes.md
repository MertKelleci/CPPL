# Notes

## Why precompiled headers?
1. Precompiled headers can significantly reduce compilation times by compiling a set of headers once and reusing the compiled version for subsequent compilations.
1. Precompiled headers create binary files that can be reused across multiple source files, which can speed up the compilation process, especially for large projects with many header files.

## When not to use precompiled headers?
1. If your project has a small number of header files or if the headers are not included in many source files, the benefits of precompiled headers may be minimal.
1. If you frequently change the header files included in the precompiled header, it can lead to longer compilation times since the precompiled header will need to be regenerated each time a change is made.

## How to create precompiled headers in Visual Studio:
1. Create a header file (e.g., `pch.h`) and include all the headers you want to precompile.
1. Create a source file (e.g., `pch.cpp`) that includes the header file you just created.
1. Right click the source file (e.g., `pch.cpp`) in the Solution Explorer, select **Properties > C/C++ > Precompiled Headers, and set "Precompiled Header" to "Create (/Yc)"**.
1. Right click the project in the Solution Explorer, select **Properties > C/C++ > Precompiled Headers, and set "Precompiled Header" to "Use (/Yu)"**, and set **"Precompiled Header File"** to the name of your header file (e.g., `pch.h`).

## Some settings I needed to change to make this project work:
1. **Tools > Options > Text Editor > Code Cleanup > Optimize file include graph (C++)** removed (Deletes all my include directories in the header file).
1. **Tools > Options > Text Editor > Code Cleanup > Remove unnecessary includes and usings** removed (Same as above).

## Some shortcuts I found useful:
1. **Ctrl + D:** Duplicate line or selection.
1. **Alt + Shift + Up/Down:** Add text cursor.
1. **Alt + Up/Down:** Move line up/down.
1. **Tools > Options > Project and Solutions > VC++ Project Settings > Build Timing:** Gives you a breakdown of how long each step of the build process takes, which can help identify bottlenecks in the compilation process.