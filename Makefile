.PHONY: build run

build:
	rm -rf build
	mkdir build
	cmake -S . -G"Unix Makefiles" -B build
	make -C build

run: bin/flapy.out
	bin/./flapy
