make: library build run

library:
	cd obj;\
	gcc ../src/tdRGB/*.c -c -O2;\
	cd ../lib;\
	ar rcs libtdRGB.a ../obj/*.o;\
	cd ../;\
	cp src/tdRGB/td.h lib

build:
	gcc src/*.c -o bin/exe -Ilib -Llib -ltdRGB -O2

run:
	./bin/exe