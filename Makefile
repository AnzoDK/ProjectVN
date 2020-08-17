SO_DIRS := -Wl,-rpath,./includes/RPEngine -L./includes/RPEngine -Wl,-rpath,./includes/RPAudio -L./includes/RPAudio
DEBUG_LEVEL := -g3
CXX := g++
#OBJECTS := ./includes/RPAudio/libRPAudio.a
OBJECTS := main.o projectvn.o
LIB_OBJECTS := rpengine.o rppng.o ui.o
INCLUDES := -I./includes
LIB_FLAGS := -fPIC
CXX_FLAGS := -std=c++17 -Wall -pthread
LINK := -lrpengine -lrpaudio
SRC := ./src

release: projectvn.o main.o
	./dependency-builder.sh
	$(CXX) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn $(LINK)
	make clean
dev-deps: projectvn.o main.o
	./dependency-builder.sh --use-dev
	$(CXX) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn $(LINK)
	make clean
no-dep: projectvn.o main.o
	$(CXX) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn $(LINK)
	make clean
projectvn.o:
	$(CXX) -c $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) -o projectvn.o $(SRC)/projectvn.cpp
main.o:
	$(CXX) -c $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) -o main.o main.cpp
clean:
	-rm *.o
