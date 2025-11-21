# Building Windows Executable from WSL

## Current Status

Cross-compilation from Linux/WSL to Windows using MinGW has compatibility issues with SFML 3.0.2 (missing mutex headers in MinGW's standard library).

## ✅ Recommended: Run Linux Version Through WSL (Easiest!)

**Good news**: Since you're using WSL2 with WSLg (which you have configured), you can run the Linux executable directly on Windows!

```bash
# Extract and run the Linux package in WSL
tar -xzf Doom-Raycaster-1.0.0-Linux.tar.gz
cd Doom-Raycaster-1.0.0-Linux
./doom
```

This will open a native Windows window and run perfectly! No Windows build needed.

## Other Options

### Option 1: Use Visual Studio on Windows

See [WINDOWS_BUILD.md](WINDOWS_BUILD.md) for complete instructions.

### Option 2: Use WSL with Native Windows Tools

If you have Windows build tools installed, you can access them from WSL:

```bash
# From WSL, call Windows CMake and build tools
/mnt/c/Program\ Files/CMake/bin/cmake.exe .. -G "Visual Studio 17 2022"
/mnt/c/Program\ Files/CMake/bin/cmake.exe --build . --config Release
```

### Option 3: Manual Cross-Compilation Fix (Not Recommended)

Requires patching SFML 3.0.2 source code and advanced knowledge.

## Summary

For your WSL setup, **the Linux build works perfectly on Windows** through WSLg! You don't need to create a separate Windows `.exe` unless you want to distribute to users without WSL.
