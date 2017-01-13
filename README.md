Synergy
=======
Share one buggy mouse and one buggy keyboard between multiple computers.

This is fork whose main goal is to remove licensing and paid features.
And maybe improve it by fixing bugs.

This repository uses submodules for googletest and in the future for OpenSSL or LibreSSL also so to clone do the following:
```
git clone --recursive https://github.com/yupi2/synergy.git
```
If or when OpenSSL or LibreSSL is included as a submodule then running this should/might clone the module into an repository:
```
git submodule update --init
```

License and stuff
--
Synergy and it's components are, unless otherwise specified, licensed under the terms of the GNU General Public License, Version 2 (GPLv2). There's an additional exemption so compiling, linking, and/or using OpenSSL is allowed.

Each file should/might have a copyright notice showing who contributed.

Synergy includes software developed by Eric Young (eay@cryptsoft.com) and software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/). The OpenSSL toolkit is licensed under two BSD-style open-source licenses: the OpenSSL License and the SSLeay License. Full texts of both licenses can be found in the the file `./ext/LICENSE (OpenSSL)`


Changes in this fork
--
There's a few things not listed here. Go through the commits.
+ Removed activation requirement for features.
+ Python 3 is supported.
+ Auto-generating translations.
+ Building on Windows should now put binaries in arch specific folders.
+ OpenSSL v1.1.x support.
+ Printscreen doesn't send Alt+Printscreen to Windows anymore.
+ Some new icons for OSX? (TODO recheck this)
+ EXTREMELY EXTREMELY BUGGY AND BAD MEMORY LEAK FIX FOR LINUX SERVER.
+ Building tests now uses a googletest submodule instead of including zip files.
+ Some misc pull-requests from the symless/synergy repo.


Building
--
There's not a detailed or good building guide yet so you should view the [wiki entry for building](https://github.com/symless/synergy/wiki/Compiling) in the [symless/synergy](https://github.com/symless/synergy) repository.

Here's how I build on Linux:
```
./hm.sh conf -g1 -d
./hm.sh build -d
```

On 64-bit Windows with Visual Studio 2015 (the Community edition is free):
```
hm conf -g2 -d
hm build -d
```
If it's a newly cloned repository then sometimes `synergyd.exe` doesn't build on Windows. Using hm-conf and then building again with hm-build fixes this. I don't know why this happens.


Skim the `./ext/toolchain/commands1.py` file if you want to.


TODO
--
+ Have OpenSSL build libraries locally (maybe switch to LibreSSL).
+ Unicode support layer for Windows.
+ Setup a build server maybe.
+ Clean any CMAKE things that can be cleaned.
+ Correct the media-toggle button mapping for Windows (play-pause toggle).
+ Wayland support (probably not).
