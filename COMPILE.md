Some notes
==========
+ Everything
  + This has only been tested running in the build directory. Don't expect installers for anything either.
+ Windows
  + You'll need a Service to run `synergyd.exe` nicely. Here's something to put into an elevated (admin) command prompt to create a Service (you'll need to correct the path to your build location):
    + `sc create Synergy type= own start= auto error= ignore obj= LocalSystem DisplayName= "Synergy Daemon" binPath= "C:\code\synergy\build\bin\x64\Debug\synergyd.exe"`
      + It doesn't start after creation so you'll need to do `sc start Synergy`. It will auto-start on boot though.
    + Also when `synergyd.exe` crashes you can restart the Service with `sc stop Synergy` then `sc start Synergy`
+ Apple macOS
  + Completely untested and likely inaccurate. Feel free to update.
+ Linux / everything else
  + I forgot what I had for this

Requirements
============
+ WinXP or higher, macOS, or Linux. (Other operating systems are not officially supported)
+ [CMake 3.0 or higher.](https://cmake.org/)
+ A C++11 environment:
  + (macOS) Xcode
  + (Windows) Visual Studio (only VS2015 is tested to work but VS2013 should work too)
    + MinGW might work but the CMakeLists.txt will need to be modified a bit. Plus I haven't tested MinGW
  + (everything else) Just install your distribution's dev package that includes everything
    + You'll need to install the X11/Xorg dev packages too. Also something to do with this `libXtst-devel`
+ Qt 5.6 or higher. (Suggested downloads for Windows and macOS: [Visual Studio 2015 x64](https://download.qt.io/official_releases/qt/5.7/5.7.1/qt-opensource-windows-x86-msvc2015_64-5.7.1.exe.mirrorlist), [Visual Studio 2015 x32](https://download.qt.io/official_releases/qt/5.7/5.7.1/qt-opensource-windows-x86-msvc2015-5.7.1.exe.mirrorlist), and [macOS](https://download.qt.io/official_releases/qt/5.7/5.7.1/qt-opensource-mac-x64-clang-5.7.1.dmg.mirrorlist))
  + Note for Windows: MinGW is not tested so sorry for forcing Visual Studio 2015 on you.
  + Another note for Windows: Install both x32 and x64 Qt installers if you want to build for multiple Windows architectures.
  + Another note for Windows: You'll need to add the installed Qt bin folder into your `%Path%` environment variable. For example since I use VS2015 x64 I have this in my path `C:\Qt\Qt5.7.1\5.7\msvc2015_64\bin`. You can do this if you want a temporary change `set "Path=%Path%;C:\Qt\Qt5.7.1\5.7\msvc2015_64\bin"`
  + Note for Linux: you'll need download the Qt5 Linguist Tools from your package manager.
    + Should be `qttools5-dev-tools` on Ubuntus and maybe Debian.
    + Might be `qt5-tools` on Arch Linux.
+ Any recent version of Git
  + For Windows you should check [this](https://git-scm.com/downloads) or [this](https://git-for-windows.github.io/) out.
    + [Also Windows XP does not appear to be support anymore](https://github.com/git-for-windows/git/wiki/FAQ#which-versions-of-windows-are-supported)

How to configure and compile Synergy 101 !!
===========================================
Navigate to your `synergy` folder in a terminal/command-prompt
```
mkdir build
cd build
```

Now decide what build-type you're going to use. Options are:
`Debug`, `Release`, `RelWithDebInfo` and `MinSizeRel`.
What you choose will be referred to as `<BR>` from herein.

Now back to configuring. You should be in the 'build' directory here.
```
cmake -DCMAKE_BUILD_TYPE=<BT> ../
```

If you're using Windows and Visual Studio then you'll need a generator too.
For example I use the following for VS2015 x64 builds:
```
cmake -DCMAKE_BUILD_TYPE=<BT> -G"Visual Studio 14 2015 Win64" ../
```
Removing the "Win64" at the end defaults uses x32 builds.
Other Visual Studio versions that might be supported are:
`Visual Studio 12 2013` and `Visual Studio 15 2017`

Some other flags you can include for the above CMake step are:
+ `-DDISABLE_TESTS=0` # to enable building tests
+ `-DDISABLE_GIT_REVISION=1` # to disable calling git for a revision number (uses 00000000)

<**TODO**: Add MinGW stuff here.>


Finally to build Synergy. You need to be in the 'build' directory.
```
cmake --build ./
```

If your cmake uses `make` internally then you can do this for multi-core builds:
```
cmake --build ./ -- -j5
```

And if you're Visual Studio then you'll need to do:
```
cmake --build ./ --config <BT>
```


That's it. Synergy binaries should now be in the `build/bin/<BT>` directory.
With Visual Studio the binaries will be placed into the `build\bin\<ARCH>\<BT>` directory.
<ARCH> is either x64 or Win32 for x64 or x32 builds respectively.
