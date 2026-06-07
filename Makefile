CC = gcc

TARGET = game

SRC_DIR = src
OBJ_DIR = obj
VENDOR_DIR = vendor

INCLUDES = \
	-Ivendor/raylib/include

LIBS = \
	-lraylib \
	-lm \
	-lpthread \
	-ldl \
	-lX11

RELEASE_CFLAGS = \
	-Wall \
	-Wextra \
	-std=c99 \
	-O2 \
	-march=native \
	-flto \
	-ffast-math

RELEASE_LDFLAGS = \
	-Lvendor/raylib/lib \
	-flto

DEBUG_CFLAGS = \
	-Wall \
	-Wextra \
	-std=c99 \
	-g3 \
	-O0 \
	-fsanitize=address \
	-fsanitize=undefined

DEBUG_LDFLAGS = \
	-Lvendor/raylib/lib \
	-fsanitize=address \
	-fsanitize=undefined

SRC = $(shell find $(SRC_DIR) -name "*.c")
VENDOR_SRC = $(shell find $(VENDOR_DIR) -name "*.c")

OBJ = \
	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC)) \
	$(patsubst $(VENDOR_DIR)/%.c,$(OBJ_DIR)/vendor/%.o,$(VENDOR_SRC))

# Default = release
all: release

release: CFLAGS=$(RELEASE_CFLAGS)
release: LDFLAGS=$(RELEASE_LDFLAGS)
release: $(TARGET)

release-run: release
	./$(TARGET)

debug: CFLAGS=$(DEBUG_CFLAGS)
debug: LDFLAGS=$(DEBUG_LDFLAGS)
debug: clean $(TARGET)

debug-run: debug
	ulimit -c unlimited && ./$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LIBS)
	./vxpck pack data.vxpck assets/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/vendor/%.o: $(VENDOR_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) data.vxpck

rebuild: clean release