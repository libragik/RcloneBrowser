# Rclone Browser (Modernized)

[![CI Build](https://github.com/YOUR_USERNAME/RcloneBrowser/actions/workflows/build.yml/badge.svg)](https://github.com/YOUR_USERNAME/RcloneBrowser/actions/workflows/build.yml)
[![License](https://img.shields.io/github/license/kapitainsky/RcloneBrowser.svg)](LICENSE)

A simple cross-platform GUI for [rclone](https://rclone.org/) command line tool.

Supports **macOS**, **GNU/Linux**, **BSD family**, and **Windows**.

> **Note:** This is a modernized fork with Qt6 support, updated to modern C++17 standards, and fixed deprecated API usage.

## What's New in 2.0

- **Qt6 Support** - Full compatibility with Qt6 while maintaining Qt5 support
- **Modern C++17** - Updated to C++17 standard
- **Fixed Deprecations** - All deprecated Qt5 APIs updated for Qt6 compatibility
- **GitHub Actions CI** - Modern CI/CD pipeline replacing Travis CI and AppVeyor
- **CMake 3.16+** - Modern CMake practices with proper targets and exports

## Features

- Browse and modify any rclone remote, including encrypted ones
- Uses same configuration file as rclone, no extra configuration required
- Supports custom location and encryption for `rclone.conf` configuration file
- Simultaneously navigate multiple repositories in separate tabs
- Lists files hierarchically with file name, size and modify date
- All rclone commands are executed asynchronously, no freezing GUI
- File hierarchy is lazily cached in memory for faster traversal of folders
- Upload, download, create new folders, rename or delete files and folders
- Calculate size of folder, export list of files and copy rclone command to clipboard
- Process multiple upload or download jobs in background
- Drag & drop support for uploading files from local file explorer
- Streaming media files for playback in VLC or similar players
- Mount and unmount folders on macOS, GNU/Linux and Windows
- Optionally minimizes to tray with notifications when upload/download finishes
- Supports portable mode
- Supports Google Drive shared-with-me
- Public link sharing for remotes that support it
- Configurable dark mode for all systems

## Installation

### Pre-built Binaries

Download the latest release from the [Releases](https://github.com/YOUR_USERNAME/RcloneBrowser/releases) page.

### Building from Source

#### Requirements

- CMake 3.16 or higher
- Qt 5.15+ or Qt 6.2+
- C++17 compatible compiler

#### Linux (Ubuntu/Debian)

```bash
# Install dependencies
sudo apt update
sudo apt install -y git g++ cmake qt6-base-dev qt6-tools-dev

# Or for Qt5:
# sudo apt install -y git g++ cmake qtbase5-dev qttools5-dev

# Clone and build
git clone https://github.com/YOUR_USERNAME/RcloneBrowser.git
cd RcloneBrowser
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

#### macOS

```bash
# Install dependencies via Homebrew
brew install cmake qt

# Clone and build
git clone https://github.com/YOUR_USERNAME/RcloneBrowser.git
cd RcloneBrowser
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt)
make -j$(sysctl -n hw.ncpu)

# Create app bundle
macdeployqt build/rclone-browser.app
```

#### Windows

1. Install [Visual Studio 2022](https://visualstudio.microsoft.com/) with "Desktop development with C++" workload
2. Install [CMake](https://cmake.org/download/)
3. Install [Qt 6](https://www.qt.io/download-open-source/) (or Qt 5.15)

```cmd
# Clone and build
git clone https://github.com/YOUR_USERNAME/RcloneBrowser.git
cd RcloneBrowser
mkdir build && cd build
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:\Qt\6.5.3\msvc2019_64 ..
cmake --build . --config Release

# Deploy Qt DLLs
C:\Qt\6.5.3\msvc2019_64\bin\windeployqt.exe build\Release\RcloneBrowser.exe
```

## Portable Mode

To enable portable mode, create a file with the same name as the executable but with `.ini` extension:

- **Windows/macOS**: Create `RcloneBrowser.ini` next to the executable
- **Linux AppImage**: Create a `.config` directory next to the AppImage

In portable mode, all configuration files are stored alongside the application, and paths to rclone can be relative.

## Configuration File Locations

### Standard Mode

| Platform | Preferences | Tasks |
|----------|------------|-------|
| **Windows** | Registry: `HKCU\Software\rclone-browser` | `%LOCALAPPDATA%\rclone-browser\tasks.bin` |
| **macOS** | `~/Library/Preferences/com.rclone-browser.rclone-browser.plist` | `~/Library/Application Support/rclone-browser/tasks.bin` |
| **Linux** | `~/.config/rclone-browser/rclone-browser.conf` | `~/.local/share/rclone-browser/tasks.bin` |

## Credits

- Original project by [mmozeiko](https://github.com/mmozeiko/RcloneBrowser)
- Maintained by [kapitainsky](https://github.com/kapitainsky/RcloneBrowser)
- Modernized fork with Qt6 support

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request
