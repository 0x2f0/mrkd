CC := clang

all: build 

.PHONY: build
build:
	mkdir -p build
	$(CC) src/mrkd.c -o build/mrkd
	$(CC) -g src/mrkd.c -o build/mrkd.debug

clean:
	rm -r build
