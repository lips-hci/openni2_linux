# README #

This README is for the user who

* Want to develop application with LIPS 3D depth camera.
* Already has a LIPS camera module on hand.
* The target platform is Linux
* Develop application with OpenNI 2

If you don't have one and are interesting with it, please contact with us by e-mail [info@lips-hci.com](mailto:info@lips-hci.com)

### System Requirements ###

* Ubuntu 14.04 or later

### Prepare Software Development Environment ###

#### Install OpenCV 2 ####

* Install required packages for building OpenCV 2.

```
sudo apt-get install cmake pkg-config libgtk2.0-dev

```

* Download OpenCV source code from https://github.com/opencv/opencv/releases.

* Extract and enter OpenCV root folder, for example
```
cd ~/opencv-2.4.11
```
* Create a folder for cmake and change directory to it, for example,
```
mkdir build && cd build
```
* Enter following command to generate cmake files
```
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
```
* Once generation is done, enter make command to start the build
```
make
```
* Then, install OpenCV to your system, administrator permission may required.
```
sudo make install
```
#### Install USB-1.0 library ####

```
sudo apt-get install libusb-1.0-0

```

#### Install LIPS 3D depth camera SDK ####

* Download SDK from [LIPS SDK] (http://www.lips-hci.com/products/sdk/)

* Extract the tarball of LIPS 3D depth camera SDK

* Enter the SDK folder and install the SDK with administrator permission
```
sudo ./install.sh
```

### Download LIPS Sample Code ###

#### Install GIT ####

```
sudo apt-get install git-core
```

#### Clone sample code ####
Clone the project into the SDK folder.

```
git clone https://github.com/lips-hci/openni2_linux.git LIPS_Sample
```

#### Build Samples ####
##### Ni2Recorder #####
```
cd LIPS_Sample\Ni2Recorder
cp -r ../../Redist/* .
cp ../../Tools/OpenNI2/Drivers/libmodule-lips2.so OpenNI2/Drivers/
CXX=g++ make
```

#### Build your own application ####
You can base the samples we provided to develop your own application. What you need to know are:

##### Makefile #####

* Append the source files' name to SRC
* According the path related to SDK, modify the CPPFLAGS and LDFLAGS appropriately. i.e., you man need to add -I and -L to the correct location.
* You can also use Clang to compile your application by change CXX from g++ to clang.

##### Redist folder #####

* You have to copy contents under Redist folder to your execution folder.
* And copy LIPS module driver library (libmodule-lips2.so) from Tools for Samples  folder to OpenNI2/Drivers you just copied from Redist folder.
