clear:
	@clear
run: bin/flapy
	@./bin/flapy
build:
	cmake -S . -B build/
comp:
	make -C build/

all: clear build comp run
