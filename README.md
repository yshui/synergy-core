Synergy
=======
Share one buggy mouse and one buggy keyboard between multiple computers.
---

**You can find 32-bit and 64-bit Windows installers in the [Releases tab](https://github.com/yupi2/synergy/releases)**

appveyor master: [![Build status master](https://ci.appveyor.com/api/projects/status/ayhyxtpmgmfr3x9n/branch/master?svg=true)](https://ci.appveyor.com/project/yupi2/synergy/branch/master)<br/>
appveyor activey: [![Build status activey](https://ci.appveyor.com/api/projects/status/ayhyxtpmgmfr3x9n/branch/activey?svg=true)](https://ci.appveyor.com/project/yupi2/synergy/branch/activey)

This is a fork whose goal is to be less buggy, build easier, and to remove the activation requirement for features.

The `master` branch is what you want to use. `activey` is used for sharing code between my computers and is likely to have compilation errors or buggy code.

**IMPORTANT: I DON'T BUILD OR TEST OSX/MACOS.** I don't have an environment to use so builds are likely to fail.

Random thing: `-D_USE_C_DATE=OFF` will help with reproducible builds.


Changes in this fork
--------------------
There's a few things not listed here. Go through the commits.
+ Removed activation requirement for features.
+ Made it easier to build.
+ Moved configuration files location for no good reason.
  + Windows uses `%localappdata%\Synergy\`
  + macOS uses `~/Library/Preferences/Synergy/`
  + Linux/everything-else uses `~/.config/Synergy/`
+ Removed Python requirement by switching from the `hm` help script to purely CMake.
+ Replaced OpenSSL with LibreSSL because it can be built with CMake and statically linked to avoid .dlls
  + Source tarball is now downloaded from LibreSSL website (since 2017-04-11).
  + OpenSSL could probably be used on Linux/everything-else instead but that can be done again in the future.
  + Generating certificates now uses 4096 bits for RSA instead of 1024.
+ Printscreen doesn't send Alt+Printscreen to Windows clients anymore.
+ Some new icons for OSX? (maybe)
+ EXTREMELY EXTREMELY BUGGY AND BAD MEMORY LEAK FIX FOR SERVERS (LINUX ONLY?).
  + Toggle the checkbox in `Configured Server->Advanced server settings` named `VERY experimental memory leak fix for yupi2`.
  + Also for a server config file in `section: options` you can add a `
  expLeakFix = true` line.
+ Removed in-tree googletest source-code and replaced it with a git submodule.
+ Working Mouse 4 (browser backwards) and Mouse 5 (browser forwards).
+ Working Horizontal scrolling.
+ New screen option to pass NumLock, ScrollLock, and CapsLock to the target screen.
  + As opposed to not sending the keycodes and only treating them as modifiers.
  + `Configure Server -> Double-click a screen -> Pass LOCK keys`
+ Merged some pull-requests that are fine from the symless/synergy repo.
  + Some that I haven't merged but will look into: #6064 #5730 #5245 #5073 #4542 #4499


Licenses and stuff
------------------
Synergy and it's components are licensed under the terms of the GNU General Public License Version 2 (GPLv2) with an additional exemption so compiling, linking, and/or using OpenSSL is allowed.

uSynergy (micro Synergy) is a seperate project that falls under the zlib License. It is unused but is kept in the repo for "historical value".

A tar-gz archive of [LibreSSL](https://www.libressl.org/), an OpenSSL fork, is downloaded through CMake which includes software developed by Eric Young (eay@cryptsoft.com) and software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org) along with work contributed from many other sources including the OpenBSD project and associates. More license information can be obtained by looking through the files in the tar-gz archive.

The archive is retrieved from https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/


Building
--------
**You should really really really not downloading anything to build just yet. This is just a little run-down on requirements to build with more detailed instructions lower down.**

+ Operating system:
  + Windows OS with support for XP or newer APIs
  + Apple macOS (TODO)
  + Linux (and maybe some POSIX systems)
+ [CMake 3.0 or newer](https://cmake.org/)
+ A C++11 environment (maybe?)
+ Qt 5.6, 5.7, 5.8 or 5.9 (earlier versions might work but I haven't tested)
+ WiX Toolset if you plan to make installers for Windows Platforms.
+ Any recent version of Git in your command path

Here's how I build on Linux:<br/>
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build ./ -- -j$(nproc)
```

And on 64-bit Windows 7 with Visual Studio 2015:<br/>
```
mkdir build
cd build
set PATH=%PATH%;C:\Qt\5.9.1\msvc2015_64\bin
cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ../
cmake --build ./ --config Release
msbuild synwix.sln
```

If you want to build the tests for Synergy (`-D_TESTS=ON`) you'll the [googletest (and googlemock)](https://github.com/google/googletest) framework. It is included as a submodule which will be downloaded if you run:
```
git clone --recursive https://github.com/yupi2/synergy.git
```
If you have a Synergy repository already but didn't run the command above initially then you can download the submodule by running this:
```
git submodule update --init
```
If you have a preinstalled version of *googletest* from a package-manager or something and want to use it then check out `src/test/CMakeLists.txt` and maybe change some directories.


(Windows) Compiling with Microsoft's Visual C++ environment (and creating an installer!)
-----------------------------------------------------------
Requirements:
+ Visual C++ Build Tools (2013, 2015, or 2017)
  + Visual Studio 2013, 2015, and 2017 will provide this if installed with `C++ Tools` selected
  + Also you can optionally install the 2015 build tools with the VS2017 installer too.
  + There's standalone download for 2015 and 2017 build tools [here](http://landinghub.visualstudio.com/visual-cpp-build-tools)
+ [CMake](https://cmake.org/download/)
+ [Qt 5.6, 5.7, 5.8 or 5.9](https://www.qt.io/download-open-source/)
  + [Here's what I have selected for x32/x64 VS2015 and x64 VS2017](https://imgur.com/ImOghWy)
    + Some notes: 5.6 is a LTS (long term support) version ending in 2019 and 5.9 too ending in 2020.
    + Also you'll need to use 5.6 if you want to build targeting Windows XP.
+ [WiX Toolset build tools](http://wixtoolset.org/releases/) and maybe also the `WiX Toolset Visual Studio 201x Extension`

Notes:
+ If you're NOT going to use an installer and just want to run Synergy from the build directory you'll need to create a service to run `synergyd.exe` nicely. Here's something to put into an elevated (admin) command prompt to create a service (you'll need to correct the path to your binary location:
  + `sc create Synergy type= own start= auto error= ignore obj= LocalSystem DisplayName= "Synergy Daemon" binPath= "C:\code\synergy\build\bin\x64\Release\synergyd.exe"`
      + It might not start after creation so you'll need to do `sc start Synergy`. It will auto-start on boot though.
    + Also when `synergyd.exe` crashes you can restart the Service with `sc stop Synergy` then `sc start Synergy`

 1. Open a Visual Studio Native/Cross Tools Command Prompt. You should be able to find these in your start menu under your Visual Studio version folder.
     + Alternatively you can use `vcvarsall` (google it) in a command prompt
     + These tools might be prefixed with the VS version like `VS2015`
     + `x86 Native Tools Command Prompt` -- x86_32 builds on an x86_32 machine
       + Will work on x86_64 systems too.
     + `x86 x64 Cross Tools Command Prompt` -- x86_64 builds on an x86_32 machine
       + Will work on x86_64 systems too.
 2. `cd C:\`
 3. `mkdir code`
 4. `cd code`
 5. `git clone https://github.com/yupi2/synergy.git`
 6. `cd synergy`
 7. `mkdir build`
 8. `cd build`
 9. `set PATH=%PATH%;C:\Qt\5.9.1\msvc2015_64\bin`
     + You'll need to change this if you want to use other versions of Qt or VS.
10. `cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015 Win64" ../`
     + [Generators (-G)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators) don't include the `Win64` if targetting x86_32 builds.
     + Examples:
       + `Visual Studio 14 2015` -- x86_32 VS2015
       + `Visual Studio 15 2017 Win64` -- x86_64 VS2017
       + `Visual Studio 12 2013` -- x86_32 VS2013
     + Also for targetting Windows XP you might need to provide a toolset argument such as `-T v140_xp` (the 2015 build tools XP target) or `-T v120_xp` (the 2013 one).
       + so `cmake -DCMAKE_BUILD_TYPE=Release -G"Visual Studio 14 2015" -T v140_xp ../`
11. `cmake --build ./ --config Release`
12. And if you want to build an installer: `msbuild synwix.sln`
     + You can find the installer at `build\bin\synergy_installer_*.msi` where `*` is a version, git branch, git revision, and architecture.
+ **Note:** You can also replace all instances above of `Release` with `Debug`, `RelWithDebInfo`, or `MinSizeRel`.


(Linux / POSIX) Compiling
-------------------------
Requirements:
+ Compiler!
+ CMake!
+ Qt!
  + ~~Also you'll need the Qt5 Linguist Tools which might be `qttools5-dev-tools` or `qt5-tools`.~~ Maybe not.
+ X11!
  + X11/Xorg dev packages along with something like `libXtst-devel`.

1. Open terminal.
2. `cd ~/code`
3. `git clone https://github.com/yupi2/synergy.git`
4. `cd synergy ; mkdir build ; cd build`
5. `cmake -DCMAKE_BUILD_TYPE=Release ../`
    + You can replace `Release` with `Debug` here
6. `cmake --build ./ -- -j$(nproc)`
    + `$(nproc)` uses the number of processors available. You can use a static number of cores with `-jN` where `N` is your number or remove it entirely `cmake -build ./`
7. `ls bin`


(Apple macOS) Compiling
-----------------------
TODO
