# Windows Build Instructions

## Building on Windows

### Prerequisites
1. Install CMake: https://cmake.org/download/
2. Install Visual Studio 2019 or newer (Community Edition is free)
3. Download SFML 3.0.2 for Visual C++ from: https://www.sfml-dev.org/download.php
   - Extract to `C:\SFML-3.0.2\`

### Build Steps

1. Open Command Prompt or PowerShell in the project directory

2. Create build directory:
   ```cmd
   mkdir build-windows
   cd build-windows
   ```

3. Configure with CMake:
   ```cmd
   cmake .. -DSFML_DIR=C:\SFML-3.0.2\lib\cmake\SFML
   ```

4. Build:
   ```cmd
   cmake --build . --config Release
   ```

5. Copy SFML DLLs to the build directory:
   ```cmd
   copy C:\SFML-3.0.2\bin\*.dll Release\
   ```

6. Run the game:
   ```cmd
   cd Release
   doom.exe
   ```

### Creating Windows Package

After building, you can create a distributable package:

```cmd
cpack -C Release
```

This will create `Doom-Raycaster-1.0.0-win64.zip` containing:
- `doom.exe`
- `Assets\` directory
- All required SFML DLLs

## Cross-Compilation from Linux (Alternative - Currently Has Issues)

Due to compatibility issues with SFML 3.0.2 and MinGW, cross-compilation from Linux is not currently supported. Please build on Windows natively or use Wine to run the Windows executable on Linux.

## Note

The Linux package is fully functional and ready to distribute. For Windows builds, native compilation on Windows is recommended.
