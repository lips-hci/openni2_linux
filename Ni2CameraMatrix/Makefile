PWD = $(shell pwd)
SRC = ./Ni2CameraMatrix.cpp
CPPFLAGS = -I../../Include -std=c++11 -g
LDFLAGS = -L$(PWD) -L../../Tools -Wl,-rpath ./ -lOpenNI2

# OpenCV
CPPFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

LOCAL_TARGET = Ni2CameraMatrix

all: $(LOCAL_TARGET)

$(LOCAL_TARGET): $(SRC)
	$(CXX) $(SRC) $(CPPFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(LOCAL_TARGET)
