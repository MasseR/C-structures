all:
	if [ ! -d build ]; then mkdir build; cd build/ ; cmake ../ ; fi
	make -C build/

test: all
	build/tests/test
