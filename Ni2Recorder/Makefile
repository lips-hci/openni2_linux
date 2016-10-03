PWD = $(shell pwd)
SRC = ./Ni2Recorder.cpp
CPPFLAGS = -I../../Include -std=c++11
LDFLAGS = -L$(PWD) -Wl,-rpath ./ -lOpenNI2

LOCAL_TARGET = Ni2Recorder

all: $(LOCAL_TARGET)

$(LOCAL_TARGET): $(SRC)
	$(CXX) $(SRC) $(CPPFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(LOCAL_TARGET)
