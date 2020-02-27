.PHONY: all clean

all:
	$(foreach file, $(wildcard *.dot), m4 ${file} | dot -Tpng -o ${basename ${file}}.png;)

clean:
	rm -f *.png
