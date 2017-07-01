EXE = skiopen

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/include/SDL2/
LDLIBS = -lSDL2 -lSDL2main

RM = rm -f

SRC = $(wildcard src/*.cpp)
SRC += $(wildcard src/behaviours/*.cpp)
SRC += $(wildcard src/levels/*.cpp)
SRC += $(wildcard src/structures/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: LDFLAGS += -s
all: $(EXE)

debug: CXXFLAGS += -g
debug: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

depend: .depend

.depend: $(SRC)
	$(CXX) $(CXXFLAGS) -MM $^ > $@

include .depend

clean:
	$(RM) $(OBJ) $(EXE)

.PHONY: clean
