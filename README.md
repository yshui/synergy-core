Synergy
=======
Share one buggy mouse and one buggy keyboard between multiple computers.
---

This is fork whose main goal is to remove licensing and paid features (it's open-source so why not), fix a few bugs, and to make building a little better.

The `master` branch will be considered the "stable" branch. I use the `activey` branch to test and share commits between computers.

**IMPORTANT:** I don't have an evironment setup to test Apple macOS so expect building to fail completely. Feel free to contribute.

This repository uses a submodule for [a testing framework](https://github.com/google/googletest) so to clone do this:
```
git clone --recursive https://github.com/yupi2/synergy.git
```
If any new submodules are added in the future then running this should/might clone the module into the repository:
```
git submodule update --init
```


Licenses and stuff
------------------
Synergy and it's components are licensed under the terms of the GNU General Public License Version 2 (GPLv2) with an additional exemption so compiling, linking, and/or using OpenSSL is allowed.

uSynergy (micro Synergy) is a seperate project that falls under the zlib License. It is unused but is kept in the repo for "historical value".

A tar-gz archive is included for [LibreSSL](https://www.libressl.org/) which includes software developed by Eric Young (eay@cryptsoft.com) and software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org) along with work contributed from many other sources including the OpenBSD project and associates. More license information can be obtained by looking through the files in the tar-gz archive.

The archive was retrieved from [here](https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/)


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
+ OpenSSL replaced with LibreSSL tarball (building as an external CMake project is easy).
  + OpenSSL could probably be used on Linux/everything-else instead but that can be done again in the future.
  + Generating certificates now uses 4096 bits for RSA instead of 1024 but it doesn't really matter.
+ Auto-generating translations (through CMake).
+ Building on Windows should now put binaries in arch specific folders.
+ Printscreen doesn't send Alt+Printscreen to Windows clients anymore.
+ Some new icons for OSX? (TODO recheck this)
+ EXTREMELY EXTREMELY BUGGY AND BAD MEMORY LEAK FIX FOR LINUX SERVER.
+ Building tests now uses a googletest submodule instead of including zip files.
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
+ Any recent version of Git

Here's how I build on Linux:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -D_EXP_LEAK_FIX=ON ../
cmake --build ./ -- -j$(nproc)
```

On 64-bit Windows with Visual Studio 2015 (the Community edition is free):
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G"Visual Studio 14 2015 Win64" ../
cmake --build ./ --config Debug
```


(Windows) Compiling with Microsoft's Visual C++ environment
===========================================================
Requirements:
+ Visual C++ Build Tools (2013 or 2015)
  + Visual Studio 2013 and 2015 will provide this if installed with `C++ Tools` selected
  + There's a standalone download for the 2015 build tools [here](http://landinghub.visualstudio.com/visual-cpp-build-tools)
+ [CMake](https://cmake.org/download/)
+ [Qt 5.6, 5.7 or 5.8](https://www.qt.io/download-open-source/)
  + [Here's what I select since I plan to only have x64 builds with Visual Studio 2015](https://imgur.com/YP6v8rE)




(Linux / POSIX) Compiling
=========================
Requirements:
+ Compiler!
+ CMake!
+ Qt!

(Windows) (**DOESN'T WORK**) Compiling with MSYS2 & MinGW
======================================
**The `synergyd.exe` binary doesn't build (I really wanted it to but CMake and linker errors are numerous) so this is basically useless.** It had a lot of nice things going for it like one place to grab Git, CMake, Qt and a compiler.
Requirements:
+ [MSYS2](http://www.msys2.org/)
  + HTTPS downloads on sourceforge for [32bit](https://sourceforge.net/projects/msys2/files/Base/i686/) and [64bit](https://sourceforge.net/projects/msys2/files/Base/x86_64/)

1.  Run MSYS2 installer and finish with `Run MSYS2 XXbit now`.
2.  Run `pacman -Syu`, type `y` and press `Enter` to upgrade packages.
3.  It will ask you to close your terminal now which you can do by clicking the window's close button and then OK.
4.  Start Menu -> `MSYS2 XXbit` -> `MSYS2 MinGW XX-bit`
5.  Run `pacman -Syu` again.
6.  Run `pacman -S git mingw-w64-?????-cmake mingw-w64-?????-toolchain mingw-w64-?????-qt5
--* Replace `?????` with either `i686` or `x86_64`
7.  Find something to do for a few minutes while everything installs.
8.  Reopen your `MSYS2 MinGW XX-bit` terminal
8.  Find a directory that you want to clone this repo to
--* For example I'll use `/c/code/test/synergy` which is equivalent to `C:\code\test\synergy`
9.  Run `cd /c/code/test`
10. Run `git clone --recursive https://github.com/yupi2/synergy.git`
11. Run `cd synergy ; mkdir build ; cd build`
13. Run `cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../`
14. Run `cmake --build ./ -- -j$(nproc)

(Apple macOS) Compiling
=======================
TODO
