CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lSDL

SRCDIR=src
OBJDIR=obj
INCLUDEDIR=include
EXECDIR=bin

SRC= $(wildcard $(SRCDIR)/*.cpp)
OBJ= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
INCLUDE= $(wildcard $(INCLUDEDIR)/*.h)
EXEC=$(EXECDIR)/tetris

all: $(EXEC)

$(EXEC): $(OBJ) $(INCLUDE)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC) $(OBJ)
