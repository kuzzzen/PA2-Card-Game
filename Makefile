OBJS	= player.o card.o main.o game.o menu.o deckLoader.o effect.o effectDamage.o effectHealing.o effectGetCard.o effectRestriction.o howToPlayWindow.o gameMenu.o playerComputer.o
SOURCE	= $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
HEADER	= $(wildcard src/*.h) $(wildcard src/*/*.h)
OUT	= kasatnik
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lncurses # -lstdc++fs

# THIS MAKEFILE IS MISSING SOME DEPENDENCIES
# SO IF YOU'RE WRITING YOUR PA2 PROJECT AND
# YOUR FRIEND TOLD YOU TO GO ON GITHUB AND STEAL
# SOMEONE'S MAKEFILE PLEASE DON'T USE THIS ONE

dep: $(SOURCE)
	g++ -MM src/*.cpp > dependencies.mk

include dependencies.mk

compile: dep $(OUT)

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(OBJS): $(SOURCE)
	$(CC) $(FLAGS) $^ -std=c++17

doc:
	doxygen Doxyfile

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)

