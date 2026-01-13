CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lpthread

all: thread_app

thread_app: main.cpp Thread.cpp
	$(CXX) $(CXXFLAGS) main.cpp Thread.cpp -o counter_app $(LIBS)