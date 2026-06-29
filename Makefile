CC := clang

all: build test_run

.PHONY: build
build:
	mkdir -p build
	$(CC) src/mrkd.c -o build/mrkd

test_run:
	./build/mrkd 

clean:
	rm -r build
