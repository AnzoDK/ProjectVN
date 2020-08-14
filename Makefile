SO_DIRS := -Wl,-rpath,./includes/RPEngine -L./includes/RPEngine -Wl,-rpath,./includes/RPAudio -L./includes/RPAudio
DEBUG_LEVEL := -g3
CXX := g++
#OBJECTS := ./includes/RPAudio/libRPAudio.a
OBJECTS := main.o rpengine.o rppng.o ui.o
LIB_OBJECTS := rpengine.o rppng.o ui.o
INCLUDES := -I./includes
LIB_FLAGS := -fPIC
CXX_FLAGS := -std=c++17 -Wall -pthread
LINK := -lrpengine
SRC := ./src

release:
	./dependency-builder.sh
	$(CXX) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) -o projectvn main.cpp $(LINK)
no-dep:
	$(CXX) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) -o projectvn main.cpp $(LINK)
