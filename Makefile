CC = clang
CFLAGS_EXTRA :=
CFLAGS := -std=c99 -Wall -Wextra $(CFLAGS_EXTRA)
DEBUG_FLAGS := $(CFLAGS) -fsanitize=address -g

all: build 

.PHONY: build
build:
	mkdir -p build
	$(CC) $(CFLAGS) src/mrkd.c -o build/mrkd

debug-build:
	mkdir -p build
	$(CC) $(DEBUG_FLAGS) -g src/mrkd.c -o build/mrkd.debug

clean:
	rm -r build
