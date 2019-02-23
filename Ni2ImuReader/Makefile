PWD = $(shell pwd)
SRC = ./Ni2ImuReader.cpp
CPPFLAGS = -I../../Include -std=c++11 -g
LDFLAGS = -L$(PWD) -Wl,-rpath ./ -lOpenNI2

# OpenCV
CPPFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

LOCAL_TARGET = Ni2ImuReader

all: $(LOCAL_TARGET)

$(LOCAL_TARGET): $(SRC)
	$(CXX) $(SRC) $(CPPFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(LOCAL_TARGET)
