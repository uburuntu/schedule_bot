#!/bin/sh

# Standard packages install
apt-get -qq update
apt-get -qq install -y make cmake binutils libssl-dev

# Install latest boost library parts
wget https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.bz2
tar --bzip2 -xf boost_1_64_0.tar.bz2
cd ./boost_1_64_0
./bootstrap.sh && ./b2 install --with-system --with-iostreams --with-date_time --with-test > boost_install.log
cd ..  && rm -rf ./boost_1_64_0 boost_1_64_0.tar.bz2

# Bot library install and cleaning up
git clone --depth=5 https://github.com/reo7sp/tgbot-cpp
cd ./tgbot-cpp
cmake . && make -j4 && make install
cd .. && rm -rf ./tgbot-cpp

