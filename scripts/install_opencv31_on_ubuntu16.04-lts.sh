#!/bin/bash
#
# Refer to URL https://www.pyimagesearch.com/2016/10/24/ubuntu-16-04-how-to-install-opencv/
#
# This auto script tries to download OpenCV source 3.1.0.zip, buid and install it on Ubuntu16.04 LTS
#
sudo apt-get install build-essential cmake pkg-config
sudo apt-get install libtbb2 libtbb-dev
sudo apt-get install libjpeg-dev libpng-dev libtiff-dev libjasper-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
sudo apt-get install libgtk-3-dev
sudo apt-get install libatlas-base-dev gfortran

#sudo apt-get install python-dev python-numpy
#sudo apt-get install python2.7-dev
#sudo apt-get install python3.5-dev

cd ~/Download
wget -O opencv3.1.0.zip https://github.com/opencv/opencv/archive/3.1.0.zip
unzip opencv3.1.0.zip

cd opencv-3.1.0
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
  -D CMAKE_INSTALL_PREFIX=/usr/local \
  -D WITH_TBB=ON \
  -D WITH_V4L=ON \
  -D WITH_OPENGL=ON \
  -D INSTALL_PYTHON_EXAMPLES=OFF \
  -D INSTALL_C_EXAMPLES=OFF \
  -D BUILD_EXAMPLES=OFF ..
make -j4

sudo make install
sudo ldconfig
