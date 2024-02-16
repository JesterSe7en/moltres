# Hide commands
.SILENT:

build: $(wildcard ./src/*.c)
	@echo "Building..."
	# gcc -o game -Wall -std=c11 -pedantic $^ -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
	#
	# use this one if you are manually downloading and installing SDL via github repo
	# gcc -o game -Wall -std=c11 -pedantic $^ -I/usr/local/include -L/usr/local/lib -Wl,-rpath=/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
	#
	#
	# https://man7.org/linux/man-pages/man3/strdup.3.html for the POSIX version -0 strdup 
	clang -o game -Wall -std=c17 -pedantic -D_POSIX_C_SOURCE=200809L $^ -I/usr/local/include -L/usr/local/lib -Wl,-rpath=/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf
	if [ $$? -eq 0 ]; then \
		echo "Build successful."; \
	else \
		echo "Build failed."; \
	fi

run:
	./game

clean:
	rm -f game



CC = gcc
CFLAGS_COMMON = -Wall -Wextra
LDFLAGS = -lm

# Debug version
CFLAGS_DEBUG = -g -DDEBUG
TARGET_DEBUG = your_program_debug

# Release version
CFLAGS_RELEASE = -O3
TARGET_RELEASE = your_program_release

# Source files
SRC = main.c file1.c file2.c

# Object files
OBJ_DEBUG = $(SRC:.c=_debug.o)
OBJ_RELEASE = $(SRC:.c=_release.o)

# Build targets
all: debug release

debug: $(TARGET_DEBUG)

release: $(TARGET_RELEASE)

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_DEBUG) -o $@ $^ $(LDFLAGS)

$(TARGET_RELEASE): $(OBJ_RELEASE)
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_RELEASE) -o $@ $^ $(LDFLAGS)

%_debug.o: %.c
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_DEBUG) -c -o $@ $<

%_release.o: %.c
	$(CC) $(CFLAGS_COMMON) $(CFLAGS_RELEASE) -c -o $@ $<

clean:
	rm -f $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) $(TARGET_RELEASE)
