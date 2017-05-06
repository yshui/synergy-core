Synergy
=======
Share one buggy mouse and one buggy keyboard between multiple computers.
---

This is fork whose main goal is to remove licensing and paid features (it's open-source so why not), fix a few bugs, and to make building a little better.

The `master` branch will be considered the "stable" branch. I use the `activey` branch to test and share commits between computers.

**IMPORTANT:** I don't have an evironment setup to test Apple macOS so expect building to fail completely. Feel free to contribute.

If you want to build the tests for Synergy (`-D_TESTS=ON`) you'll the [googletest (and googlemock)](https://github.com/google/googletest) framework. It is included as a submodule which will be downloaded if you run:
```
git clone --recursive https://github.com/yupi2/synergy.git
```
If you have a Synergy repository already but didn't run the command above initially then you can download the submodule by running this:
```
git submodule update --init
```
If you have a preinstalled version of *googletest* from a package-manager or something and want to use it then check out `src/test/CMakeLists.txt` and maybe change some directories.


Licenses and stuff
------------------
Synergy and it's components are licensed under the terms of the GNU General Public License Version 2 (GPLv2) with an additional exemption so compiling, linking, and/or using OpenSSL is allowed.

uSynergy (micro Synergy) is a seperate project that falls under the zlib License. It is unused but is kept in the repo for "historical value".

A tar-gz archive of [LibreSSL](https://www.libressl.org/), an OpenSSL fork, is downloaded through CMake which includes software developed by Eric Young (eay@cryptsoft.com) and software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org) along with work contributed from many other sources including the OpenBSD project and associates. More license information can be obtained by looking through the files in the tar-gz archive.

The archive is retrieved from https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/


Changes in this fork
--------------------
There's a few things not listed here. Go through the commits.
+ Removed activation requirement for features.
+ Moved configuration files location for no good reason.
  + Windows uses `%localappdata%\Synergy\`
  + macOS uses `~/Library/Preferences/Synergy/`
  + Linux/everything-else uses `~/.config/Synergy/`
+ Switch from using `hm` as helper script catchall to purely CMake.
+ Removed Python requirement (by deprecation of `hm`).
+ OpenSSL replaced with LibreSSL tarball because building LibreSSL as an external CMake project is easy and requires fewer dependencies than OpenSSL (+ no .dlls).
  + Tarball is now downloaded from LibreSSL website (2017-04-11).
  + OpenSSL could probably be used on Linux/everything-else instead but that can be done again in the future.
  + Generating certificates now uses 4096 bits for RSA instead of 1024 but it doesn't really matter.
+ Building on Windows should now put binaries in arch specific folders.
+ Printscreen doesn't send Alt+Printscreen to Windows clients anymore.
+ Some new icons for OSX? (maybe)
+ EXTREMELY EXTREMELY BUGGY AND BAD MEMORY LEAK FIX FOR LINUX SERVERS.
  + Add `-D_EXP_LEAK_FIX=ON` to the CMake configuration command.
+ Building tests now uses a googletest submodule instead of including zipped source files.
+ Some misc pull-requests from the symless/synergy repo.


Building
--------
**You should really really really not downloading anything to build just yet. This is just a little run-down on requirements to build with more detailed instructions lower down.**

+ Operating system:
  + Windows OS with support for XP or newer APIs
  + Apple macOS (TODO)
  + Linux (and maybe some POSIX systems)
+ [CMake 3.0 or newer](https://cmake.org/)
+ A C++11 environment
+ Qt 5.6, 5.7 or 5.8
+ WiX Toolset if you plan to make installers for Windows Platforms.
+ Any recent version of Git in your command path

Here's how I build on Linux:<br/>
The `-D_EXP_LEAK_FIX=ON` part might not be desired ([#2](https://github.com/yupi2/synergy/issues/2))
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -D_EXP_LEAK_FIX=ON ../
cmake --build ./ -- -j$(nproc)
```

On 64-bit Windows with Visual Studio 2015 (the Community edition is free):<br/>
Open a `VS2015 x64 Native Tools Command Prompt`.
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ../
cmake --build ./ --config Release
```


(Windows) Compiling with Microsoft's Visual C++ environment (and creating an installer!)
-----------------------------------------------------------
Requirements:
+ Visual C++ Build Tools (2013 or 2015)
  + Visual Studio 2013 and 2015 will provide this if installed with `C++ Tools` selected
  + There's a standalone download for the 2015 build tools [here](http://landinghub.visualstudio.com/visual-cpp-build-tools)
+ [CMake](https://cmake.org/download/)
+ [Qt 5.6, 5.7 or 5.8](https://www.qt.io/download-open-source/) in your %Path% environment variable.
  + Example %Path% addition: `;C:\Qt\5.8\msvc2015_64\bin`
  + [Here's what I select since I plan to only have x64 builds with Visual Studio 2015](https://imgur.com/YP6v8rE)
+ [WiX Toolset build tools](http://wixtoolset.org/releases/) and maybe also the `WiX Toolset Visual Studio 201x Extension`

Notes:
+ If you're NOT going to use an installer and just want to run Synergy from the build directory you'll need to create a service to run `synergyd.exe` nicely. Here's something to put into an elevated (admin) command prompt to create a service (you'll need to correct the path to your binary location:
  + `sc create Synergy type= own start= auto error= ignore obj= LocalSystem DisplayName= "Synergy Daemon" binPath= "C:\code\synergy\build\bin\x64\Release\synergyd.exe"`
      + It might not start after creation so you'll need to do `sc start Synergy`. It will auto-start on boot though.
    + Also when `synergyd.exe` crashes you can restart the Service with `sc stop Synergy` then `sc start Synergy`

 1. Open a `VS2015 x64 Native Tools Command Prompt` (or whatever thing you'd use for 32-bit or VS2013)
 2. `cd C:\`
 3. `mkdir code`
 4. `cd code`
 5. `git clone --recursive https://github.com/yupi2/synergy.git`
 6. `cd synergy`
 7. `mkdir build`
 8. `cd build`
 9. `cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ../`
10. `cmake --build ./ --config Release`
11. And now continue on if you want to create an installer.
12. `windeployqt bin\x64\Release\synergygui.exe`
13. `msbuild ../src/setup/win32/synergy.sln /p:Configuration="Release" /p:Platform="x64"`
14. Now you can find the installer at `build\bin\x64\Release\synergy_installer_x64.msi`


(Linux / POSIX) Compiling
-------------------------
Requirements:
+ Compiler!
+ CMake!
+ Qt!
  + Also you'll need the Qt5 Linguist Tools which might be `qttools5-dev-tools` or `qt5-tools`.
+ X11!
  + X11/Xorg dev packages along with something like `libXtst-devel`.

1. Open terminal.
2. `cd ~/code`
3. `git clone --recursive https://github.com/yupi2/synergy.git`
4. `cd synergy ; mkdir build ; cd build`
5. `cmake -DCMAKE_BUILD_TYPE=Release ../`
6. `cmake --build ./ -- -j$(nproc)`
7. `ls bin`

If you have memory leaks with Synergy then you can add a flag to the CMake configure step (`cmake -DCMAKE_BUILD_TYPE=Release -D_EXP_LEAK_FIX=ON ../`) and it might solve it.


(Apple macOS) Compiling
-----------------------
TODO
