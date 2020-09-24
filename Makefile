SO_DIRS := -Wl,-rpath,./includes/RPEngine -L./includes/RPEngine -Wl,-rpath,./includes/RPAudio -L./includes/RPAudio -Wl,-rpath,./includes/RPAudio/libsndio -L./includes/RPAudio/libsndio
DEBUG_LEVEL := -g3
PG:=
CXX := g++
#OBJECTS := ./includes/RPAudio/libRPAudio.a
MAIN_OBJECTS := main.o projectvn.o
LIB_OBJECTS := rpengine.o rppng.o ui.o
INCLUDES := -I./includes
LIB_FLAGS := -fPIC
CXX_FLAGS := -std=c++17 -Wall -pthread
LINK := -lrpengine -lrpaudio
SRC := ./src
OS := Linux




#Default we load from this path
SCRIPTS := ./Resources/scripts
#Default
RPPATH := ./includes/RPEngine


LINK_SOURCES := $(wildcard $(SCRIPTS)/*.cpp)
LINK_OBJECTS := $(patsubst $(SCRIPTS)/%.cpp,$(SCRIPTS)/%.o,$(LINK_SOURCES))
OBJECTS := $(MAIN_OBJECTS)
OBJECTS += $(LINK_OBJECTS)

ifeq ($(OS), Windows)
	CXX:= x86_64-w64-mingw32-g++
	CXX_FLAGS += 
	LINK += -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_image -lSDL2_ttf 
endif
ifeq ($(OS), Linux)
	LINK += -lSDL2 -lSDL2_image -lSDL2_ttf -lsndio
endif


$(SCRIPTS)/%.o: $(SCRIPTS)/%.cpp
	$(CXX) $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) -c -o $@ $<

link:
	./RPScriptLinker $(SCRIPTS) $(RPPATH)

dev-deps-windows: $(OBJECTS)
	./dependency-builder.sh --use-dev --Windows
	./RPScriptLinker $(SCRIPTS) $(RPPATH)
	$(CXX) $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn.exe $(LINK)
	make clean
no-dep-windows: $(OBJECTS)
	./RPScriptLinker $(SCRIPTS) $(RPPATH)
	$(CXX) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn.exe $(LINK)
	make clean
release: $(OBJECTS)
	./dependency-builder.sh
	$(CXX) $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn $(LINK)
	make clean
dev-deps: link $(OBJECTS)
	./dependency-builder.sh --use-dev
	$(CXX) $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn $(LINK)
	make clean
no-dep: $(OBJECTS)
	./RPScriptLinker $(SCRIPTS) $(RPPATH)
	$(CXX) $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) $(SO_DIRS) $(OBJECTS) -o projectvn $(LINK)
	make clean
projectvn.o:
	$(CXX) -c $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) -o projectvn.o $(SRC)/projectvn.cpp
main.o:
	$(CXX) -c $(PG) $(DEBUG_LEVEL) $(CXX_FLAGS) $(INCLUDES) -o main.o main.cpp
clean:
	-rm *.o
	-rm $(SCRIPTS)/*.o
