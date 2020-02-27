ifdef OS
	EXT := .exe
else
	EXT :=
endif

CXX := g++
CPPFLAGS := -std=c++17 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

.PHONY: all clean

all: minmax_heap$(EXT)
	
minmax_heap$(EXT): minmax_heap.o
	$(CXX) $(CPPFLAGS) -o $@ minmax_heap.cpp

clean:
	rm -f minmax_heap$(EXT) minmax_heap.o
