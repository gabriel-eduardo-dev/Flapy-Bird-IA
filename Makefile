.PHONY: build run

build:
	rm -rf build
	rm -rf bin
	mkdir build
	mkdir bin
	cmake -S . -G"Unix Makefiles" -B build
	make -C build

run: bin/flapy
	bin/./flapy.out
