# Doom Raycaster - Packaging Summary

## ✅ Available Packages

### Linux (Ready to Distribute!)
- **File**: `Doom-Raycaster-1.0.0-Linux.tar.gz` (384KB)
- **Location**: `build/Doom-Raycaster-1.0.0-Linux.tar.gz`
- **Status**: ✅ Built, tested, and ready
- **Features**:
  - Statically linked with SFML 3.0.2
  - Includes doom executable and Assets directory
  - Portable - only requires standard Linux libraries

**To use:**
```bash
tar -xzf Doom-Raycaster-1.0.0-Linux.tar.gz
cd Doom-Raycaster-1.0.0-Linux
./doom
```

### Windows
- **Status**: 📋 Build instructions provided
- **Options**:
  1. **WSL Users**: Run the Linux build through WSLg (works perfectly!)
  2. **Native Windows**: Follow [WINDOWS_BUILD.md](WINDOWS_BUILD.md)
  3. **From WSL**: See [BUILD_FROM_WSL.md](BUILD_FROM_WSL.md)

## Quick Start (WSL on Windows)

Since you're using WSL2 with WSLg, you can run the Linux package directly:

```bash
cd build
tar -xzf Doom-Raycaster-1.0.0-Linux.tar.gz
cd Doom-Raycaster-1.0.0-Linux
./doom
```

The game will open in a Windows window - no separate Windows build needed!

## Building Packages

### Rebuild Linux Package:
```bash
cd build
cmake ..
make
cpack
```

### Create Windows Package:
See [WINDOWS_BUILD.md](WINDOWS_BUILD.md) for native Windows build instructions.

## Files in This Branch

- `CMakeLists.txt` - Updated with CPack packaging support
- `PACKAGING.md` - Detailed packaging instructions
- `WINDOWS_BUILD.md` - Windows native build guide  
- `BUILD_FROM_WSL.md` - WSL-specific information
- `toolchain-mingw64.cmake` - MinGW toolchain (for future cross-compilation)
- `build/Doom-Raycaster-1.0.0-Linux.tar.gz` - Ready-to-distribute Linux package

## Distribution

The Linux package is ready to distribute and share. It includes everything needed to run the game on Linux or WSL.

For Windows-only distribution, a native Windows build is recommended.
