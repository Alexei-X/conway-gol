CC := gcc

OS := $(shell uname)
ifeq ($(OS),Darwin)
	CFLAGS = -Wall -Wextra -I/opt/homebrew/Cellar/sdl3/3.2.22/include/
	LDFLAGS = -L/opt/homebrew/Cellar/sdl3/3.2.22/lib/ -lSDL3
else ifeq ($(OS),Linux)
	CFLAGS := -Wall -Wextra
	LDFLAGS := -lSDL3
endif

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj

TARGET := gameoflife

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: $(BIN_DIR)/$(TARGET)

-include $(DEPS)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< $(CFLAGS) -MMD -MP -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: run
run:
	./$(BIN_DIR)/$(TARGET)

