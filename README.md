## How to build

Pre-built binaries are available in [Releases](https://github.com/yshui/synergy-core-mingw/releases)

### Dependencies

* qt5-base
* qt5-tools

### Configure

```bash
cmake -DSYNERGY_BUILD_LEGACY_GUI=Off -DSYNERGY_BUILD_LEGACY_INSTALLER=Off -DSYNERGY_BUILD_LEGACY_SERVICE=Off .
```

### Build

```bash
make
```

* * *
Original README:

# Synergy Core

This is the open source core component of Synergy, a keyboard and mouse sharing tool.

## Recommended

Things most people will need.

* [Help Guides](https://symless.com/synergy-help) - Self-help guides and information for when you don't want to talk to people.
* [Join us on Slack](https://bit.ly/synergy-slack-2020) - Talk to other Synergy users in real time using instant messaging.
* [Symless Forums](https://symless.com/forums/forum/11-synergy/) - Discuss Synergy issues on the Symless Forums.
* [Symless Blog](https://symless.com/blog/) - Find out what's happening with Synergy development.

## Advanced Users

Not for the faint hearted. Only use these if you know what you're doing.

* [Getting Started](https://github.com/symless/synergy-core/wiki/Getting-Started) - How to checkout the code from git and use the right branch.
* [Compiling](https://github.com/symless/synergy-core/wiki/Compiling) - Instructions on how to compile Synergy Core from source.
* [Translations](https://crowdin.com/project/synergy-core) - If you want to submit translations to the Synergy Core.
* [Text Config](https://github.com/symless/synergy-core/wiki/Text-Config) - Write a text config file when running Synergy Core manually.
* [Command Line](https://github.com/symless/synergy-core/wiki/Command-Line) - Go full manual and run Synergy Core from the command line.
* [Doxygen Documentation](https://docs.symless.com/synergy-core/) - Doxygen documentation.
