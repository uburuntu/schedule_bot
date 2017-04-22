# Schedule Bot
Telegram bot for easy scheduling with notifying

# Libraries and packages
At first you need to install these packages, for example: 
```sh
sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev libboost-iostreams-dev
```
And install [TgBot](https://github.com/reo7sp/tgbot-cpp) library.

# Build and run bot
Follow this instruction:
* Set your API Token key in [token.h](https://github.com/uburuntu/schedule_bot/blob/master/config/token.h)
* Compile with ./[build.sh](https://github.com/uburuntu/schedule_bot/blob/master/build.sh) or by other way with CMake or qmake
* Run executable: ./schedule_bot
