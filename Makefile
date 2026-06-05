CC = gcc

TARGET = game

SRC_DIR = src
OBJ_DIR = obj
VENDOR_DIR = vendor

CFLAGS = \
	-Wall \
	-Wextra \
	-std=c99 \
	-O2 \
	-march=native \
	-flto \
	-ffast-math

INCLUDES = \
	-Ivendor/raylib/include

LDFLAGS = \
	-Lvendor/raylib/lib \
	-flto

LIBS = \
	-lraylib \
	-lm \
	-lpthread \
	-ldl \
	-lX11

SRC = $(shell find $(SRC_DIR) -name "*.c")
VENDOR_SRC = $(shell find $(VENDOR_DIR) -name "*.c")

OBJ = \
	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC)) \
	$(patsubst $(VENDOR_DIR)/%.c,$(OBJ_DIR)/vendor/%.o,$(VENDOR_SRC))

DEBUG_CFLAGS = \
	-Wall \
	-Wextra \
	-std=c99 \
	-g3 \
	-O0 \
	-fsanitize=address \
	-fsanitize=undefined

DEBUG_LDFLAGS = \
	-fsanitize=address \
	-fsanitize=undefined

debug: CFLAGS=$(DEBUG_CFLAGS)
debug: LDFLAGS=$(DEBUG_LDFLAGS)
debug: clean $(TARGET)

debug-run: debug
	ulimit -c unlimited && ./$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)
	./vxpck pack data.vxpck assets/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/vendor/%.o: $(VENDOR_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) game data.vxpck

rebuild: clean all