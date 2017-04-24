shell=/bin/bash

all:
	gcc demo.c src/fancy-progress.c -Isrc -o demo
	./demo

clean:
	rm -f demo
