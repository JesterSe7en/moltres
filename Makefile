# Hide commands
.SILENT:

CC = clang
CFLAGS_COMMON = -Wall -std=c17 -pedantic -D_POSIX_C_SOURCE=200809L -I/usr/local/include
LDFLAGS = -L/usr/local/lib -Wl,-rpath=/usr/local/lib
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

# Debug version
CFLAGS_DEBUG = -g -DDEBUG
TARGET_DEBUG = game_debug

# Release version
CFLAGS_RELEASE = -O3
TARGET_RELEASE = game_release

# Source files
SRC = $(wildcard ./src/*.c)

# Object files
OBJ_DEBUG = $(SRC:./src/%.c=./obj/%_debug.o)
OBJ_RELEASE = $(SRC:./src/%.c=./obj/%_release.o)

# Build targets
all: debug release

debug: $(TARGET_DEBUG)

release: $(TARGET_RELEASE)

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_DEBUG) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(TARGET_RELEASE): $(OBJ_RELEASE)
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_RELEASE) -o $@ $^ $(LDFLAGS) $(LDLIBS)

obj/%_debug.o: ./src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_DEBUG) -c -o $@ $<

obj/%_release.o: ./src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_RELEASE) -c -o $@ $<

clean:
	rm -rf obj $(TARGET_DEBUG) $(TARGET_RELEASE)

run_debug: debug
	./$(TARGET_DEBUG)

run_release: release
	./$(TARGET_RELEASE)

