# Hide commands
.SILENT:

build: $(wildcard ./src/*.c)
	@echo "Building..."
	gcc -o game -Wall -std=c11 -pedantic $^ -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
	if [ $$? -eq 0 ]; then \
		echo "Build successful."; \
	else \
		echo "Build failed."; \
	fi

run: build
	./game

clean:
	rm -f game
