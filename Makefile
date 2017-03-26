BINFOLDER := bin/
INCFOLDER := inc/
SRCFOLDER := src/
OBJFOLDER := obj/

CC := g++
CFLAGS := -Wall
FLAGS := -std=c++11 -lSDL2 -lSDL2_image

SRCFILES := $(wildcard $(SRCFOLDER)*.cpp)

all: $(SRCFILES:$(SRCFOLDER)%.cpp=$(OBJFOLDER)%.o)
	$(CC) $(CFLAGS) $(OBJFOLDER)*.o -o $(BINFOLDER)main $(FLAGS)

$(OBJFOLDER)%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I./$(INCFOLDER) $(FLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJFOLDER)*
	rm -rf $(BINFOLDER)*

run:
		$(BINFOLDER)main
