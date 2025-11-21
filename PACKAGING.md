# Doom Raycaster - Packaging Guide

## Linux Package

### Building the Package

1. Ensure SFML 3.0.2 is installed on your system
2. Build the project:
   ```bash
   cd build
   cmake ..
   make
   ```
3. Create the package:
   ```bash
   cpack
   ```

This will generate: `Doom-Raycaster-1.0.0-Linux.tar.gz`

### Running the Packaged Version

1. Extract the package:
   ```bash
   tar -xzf Doom-Raycaster-1.0.0-Linux.tar.gz
   cd Doom-Raycaster-1.0.0-Linux
   ```

2. Run the executable:
   ```bash
   ./doom
   ```

**Note**: The Linux executable is statically linked with SFML, but still requires system libraries:
- libfreetype6
- libopenal
- libvorbis
- libflac
- libX11, libXrandr, libXcursor, libXi
- libudev
- OpenGL drivers

### Creating a Fully Portable AppImage (Optional)

For a truly portable single-file executable on Linux, you can create an AppImage:

```bash
# Install linuxdeploy
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage

# Create AppImage
./linuxdeploy-x86_64.AppImage --appdir AppDir --executable build/doom --desktop-file doom.desktop --icon-file Assets/sprite.png --output appimage
```

## Windows Package (Cross-compilation from Linux)

To build for Windows from Linux:

1. Install MinGW cross-compiler:
   ```bash
   sudo apt install mingw-w64
   ```

2. Download SFML 3.0.2 for MinGW from https://www.sfml-dev.org/download.php

3. Configure CMake for cross-compilation:
   ```bash
   mkdir build-windows
   cd build-windows
   cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake
   make
   cpack
   ```

This will generate: `Doom-Raycaster-1.0.0-win64.zip`

## Distribution

The packaged files can be distributed and will include:
- `doom` executable (Linux) or `doom.exe` (Windows)
- `Assets/` directory with all required assets
