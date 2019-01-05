EXE = Tanks
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

CC = g++

ifeq ($(OS),Windows_NT)
    LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_net -lSDL2_ttf -std=c++11
    SDL_INCLUDE_DIR = -I C:\tools\mingw64\include
    SDL_LIBRARY_DIR = -L C:\tools\mingw64\lib
endif

SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp )
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

IFLAGS = -I$(INC_DIR) $(SDL_INCLUDE_DIR)
LFLAGS = $(SDL_LIBRARY_DIR)

.PHONY : all clean

all : $(EXE)

$(EXE) : $(OBJ)
	$(CC) $^ $(IFLAGS) $(LFLAGS) $(LIBS) $(LIBS_OSX) -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(LIBS) -c $< $(IFLAGS) $(LFLAGS) -o $@

clean :
	rm -rf $(OBJ)
