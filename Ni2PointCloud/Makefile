PWD = $(shell pwd)
SRC = ./Ni2PointCloud.cpp
CPPFLAGS = -std=c++11 -g -Dlinux -I../../Include
LDFLAGS = -L$(PWD) -Wl,-rpath ./ -lOpenNI2

# OpenCV
CPPFLAGS += -I/usr/local/include
LDFLAGS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_viz -lopencv_contrib

LOCAL_TARGET = Ni2PointCloud

all: $(LOCAL_TARGET)

$(LOCAL_TARGET): $(SRC)
	$(CXX) $(SRC) $(CPPFLAGS) $(LDFLAGS) -o $@

clean:
	@rm -rf $(LOCAL_TARGET)
