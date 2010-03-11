all:
	if [ ! -d build ]; then mkdir build; cd build/ ; cmake ../ -DCMAKE_BUILD_TYPE=Debug; fi
	make -C build/

test: all
	build/tests/test
