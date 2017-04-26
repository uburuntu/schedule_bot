# Schedule Bot
[![Build Status](https://travis-ci.org/uburuntu/schedule_bot.svg?branch=master)](https://travis-ci.org/uburuntu/schedule_bot)

Telegram bot for easy scheduling with notifying

# Libraries and packages
At first you need to install all dependencies with [install_dependencies.sh](https://github.com/uburuntu/schedule_bot/blob/master/install_dependencies.sh) script:
```sh
sudo ./install_dependencies.sh
```
or manually.

# Build and run bot
Follow this instruction:
* Set your API Token key in [token.h](https://github.com/uburuntu/schedule_bot/blob/master/config/token.h)
* Compile with this script: [build.sh](https://github.com/uburuntu/schedule_bot/blob/master/build.sh) or by other way with CMake or qmake
* Run executable: ./schedule_bot
