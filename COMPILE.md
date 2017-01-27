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
+ [CMake 3.0 or higher.](https://cmake.org/download/)
+ A C++11 environment:
  + (macOS) Xcode
  + (Windows) Visual Studio 2013, 2015, and 2017 whenever that arrives and Qt supports it.
    + MinGW should work but CMakeLists.txt will probably need to be changed for some paths.
  + (everything else) Just install your distribution's dev package that includes everything
    + You'll need to install the X11/Xorg dev packages too. Also something to do with this `libXtst-devel`
+ Qt 5.6, 5.7, or 5.8. You can grab the online installer from [here](https://www.qt.io/download-open-source/) if you're on Windows or macOS. You'll need to check-mark the items you'll need like x32/x64 VS2015/VS2013 or for x32 MinGW. And obviously you'll need to check the relevant ticks for macOS. None of the sub-options need to be installed under a Qt version (stuff from `Qt Charts` through to the bottom like `Qt Scripts (Derecated)`)
  + Note for Windows: I only test x64 VS2015.
  + Another note for Windows: You'll need to add the installed Qt bin folder into your `%Path%` environment variable. For example since I use x64 VS2015 I have this in my %Path% `C:\Qt\5.8\msvc2015_64\bin`. You can do this if you want a temporary change `set "Path=%Path%;C:\Qt\5.8\msvc2015_64\bin"`
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
