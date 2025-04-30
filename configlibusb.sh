#! /bin/sh
cd /home/nbone/Documents/cppProjects/C-gui/externals/libusb
# This script is used to configure and build the libusb library.
# It assumes that you have already installed the required dependencies.
# If the dependencies are not installed, isntsall them with the command:
# sudo apt update
# sudo apt install autoconf automake libtool
# sudo apt-get install libudev-dev libusb-1.0-0-dev
# You can run this script from the command line or include it in your build process.
./bootstrap.sh 
    ./configure --prefix=/home/nbone/Documents/cppProjects/C-gui/libraries/libusb
 make -j$(nproc)
    make install