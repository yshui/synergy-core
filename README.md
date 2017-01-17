Synergy
=======
Share one buggy mouse and one buggy keyboard between multiple computers.

This is fork whose main goal is to remove licensing and paid features. And maybe improve it by fixing bugs.

**IMPORTANT:** The `master` branch of this repo will considered the "stable" branch. Since I use this repo as a way to share commits between computers I end up pushing commits that have not been able to be tested on multiple environments yet. This does not mean the `master` will be "stable" from bugs and building errors though. See the `activey` branch for more active changes and for more buggy behavior.

**IMPORTANT:** This is repo is not in a stable state! **Please please please file issues if you have problems or questions.** Backwards compatibility not is something I value very much. Expect failing builds, incorrect OSX behavior as I don't have an OSX environment, and changing of settings/config paths.

**IMPORTANT:** Linux is probably the only completely supported platform at the moment. Using this on Windows cleanly requires a Synergy service to startup the synergyd.exe which is currently not created automatically. Feel free to create an auto-starting service for Synergy if you're on Windows.

This repository uses a submodule for [a testing framework](https://github.com/google/googletest) so to clone do this:
```
git clone --recursive https://github.com/yupi2/synergy.git
```
If any new submodules are added in the future then running this should/might clone the module into the repository:
```
git submodule update --init
```


License and stuff
-----------------
Synergy and it's components are, unless otherwise specified, licensed under the terms of the GNU General Public License, Version 2 (GPLv2). There's an additional exemption so compiling, linking, and/or using OpenSSL is allowed.

More information regarding file licensing should be obtainable by looking for a copyright notice as the header of a file.

A tar-gz archive is included for LibreSSL which includes software developed by Eric Young (eay@cryptsoft.com) and software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org) along with work contributed from many other sources including the OpenBSD project and associates. More license information can be obtained by looking through the files in the tar-gz archive.

The archive was retrieved from [here](https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/)


Changes in this fork
--------------------
There's a few things not listed here. Go through the commits.
+ Removed activation requirement for features.
+ Moved configuration files location.
  + Windows uses `C:\ProgramData\Synergy\`.
    + Though the daemon still uses a few registry values that I haven't scraped out yet.
  + macOS uses something. Consult the `COMPILE.md` for more lacking info on this.
  + Linux/everything-else uses `~/.config/Synergy/`.
+ Switch from using `hm` as helper script catchall to using purely CMake.
+ Removed Python requirement (by deprecation of `hm`).
+ Linking with a locally built LibreSSL (version 2.4.4 at time of writing).
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
Read through the [`COMPILE.md`](https://github.com/yupi2/synergy/blob/master/COMPILE.md) file. **READ THE ENTIRE THING OR YOU WILL MISS SOMETHING IMPORTANT**. Here's a link to [symless/synergy]()'s compiling guide on their wiki. It's highly outdated and differs greatly along with it's use of the now deprecated `hm` catch-all Python build script. There may be missing information in the `COMPILE.md` file so open an issue if needed.

Here's how I build on Linux:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../
cmake --build . -- -j5
```

On 64-bit Windows with Visual Studio 2015 (the Community edition is free):
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G"Visual Studio 14 2015 Win64" ../
cmake --build . --config Debug
```


TODO
----
+ Unicode support layer for Windows.
+ Setup a build server maybe (probably not).
+ Clean any CMake things that can be cleaned.
+ Correct the media-toggle button on Windows (it might be broken).
+ Wayland support (requires support from the compositor: GNOME, KWin, etc).
+ Fix bugs.
+ Verify MinGW(-64) builds work (they certainly don't).
