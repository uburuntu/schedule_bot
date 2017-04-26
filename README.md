# Schedule Bot
[![Build Status](https://travis-ci.org/uburuntu/schedule_bot.svg?branch=master)](https://travis-ci.org/uburuntu/schedule_bot)

Telegram bot for easy scheduling with notifying

# Building
## Third-party libraries and packages
At first you need to install all dependencies with [install_dependencies.sh](https://github.com/uburuntu/schedule_bot/blob/master/install_dependencies.sh) script:
```sh
sudo ./install_dependencies.sh
```
or manually.

## Build and run bot
* Create bot and get it API Token from [@BotFather](https://t.me/BotFather)
* Set your API Token key in [token.h](https://github.com/uburuntu/schedule_bot/blob/master/config/token.h) and untrack file `git update-index --assume-unchanged config/token.h` from repo, it needed to prevent accidential private token pushing
* Compile with script [build.sh](https://github.com/uburuntu/schedule_bot/blob/master/build.sh) or by other way using CMake or qmake
* Run executable on host with internet: ./build/schedule_bot

# Used libraries and services
* [Telegram](https://telegram.org), messaging app with special [bot API](https://core.telegram.org/bots)
* [OpenSSL](https://www.openssl.org) 1.0.1f (or newer)
* [Boost C++ Libraries](http://www.boost.org) 1.59 (or newer) packages:
  * system
  * iostreams
  * date_time
  * test
* [TgBot](https://github.com/reo7sp/tgbot-cpp), C++ library for Telegram bot API
  * Special thanks to its developer [@reo7sp](https://github.com/reo7sp).
* [Travis CI](https://travis-ci.org/uburuntu/schedule_bot), automated system to build and test any projects
* [AStyle](https://astyle.sourceforge.net) 3.0 (or newer), automatic code formatter
  * Our team code style options: [code_style.astylerc](https://github.com/uburuntu/schedule_bot/blob/master/config/code_style.astylerc)
  * It used with [QtCreator](https://www.qt.io/ide) module [Beautifier](http://doc.qt.io/qtcreator/creator-beautifier.html)
