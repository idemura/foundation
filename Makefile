# Compiler settings
CC := gcc
CFLAGS := -std=gnu2x -Wall -Wextra -Isrc

AR := ar
ARFLAGS := rcs

# Directories
SRC_DIR := src
PORT_DIR := $(SRC_DIR)/port
TEST_DIR := $(SRC_DIR)/test
FDS_DIR := $(SRC_DIR)/fds
BUILD_DIR := build

# Libraries and output
LIB_PORT := $(BUILD_DIR)/libport.a
LIB_TEST := $(BUILD_DIR)/libtest.a
LIB_FDS := $(BUILD_DIR)/libfds.a
FDS_TEST_BIN := $(BUILD_DIR)/fds_tests

# Source files
PORT_SRC := $(wildcard $(PORT_DIR)/*.c)
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
FDS_SRC := $(filter-out %_test.c, $(wildcard $(FDS_DIR)/*.c))
FDS_TEST_SRC := $(wildcard $(FDS_DIR)/*_test.c)

# Object files
PORT_OBJ := $(patsubst $(PORT_DIR)/%.c,$(BUILD_DIR)/port_%.o,$(PORT_SRC))
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SRC))
FDS_OBJ := $(patsubst $(FDS_DIR)/%.c,$(BUILD_DIR)/fds_%.o,$(FDS_SRC))
FDS_TEST_OBJ := $(patsubst $(FDS_DIR)/%.c,$(BUILD_DIR)/fdstest_%.o,$(FDS_TEST_SRC))

# Phony targets
.PHONY: all clean

all: $(LIB_PORT) $(LIB_TEST) $(LIB_FDS) $(FDS_TEST_BIN)

# Compile object files
$(BUILD_DIR)/port_%.o: $(PORT_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/fds_%.o: $(FDS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/fdstest_%.o: $(FDS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create static libraries
$(LIB_PORT): $(PORT_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(LIB_TEST): $(TEST_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(LIB_FDS): $(FDS_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Link test executable
$(FDS_TEST_BIN): $(FDS_TEST_OBJ) $(LIB_PORT) $(LIB_TEST) $(LIB_FDS)
	$(CC) $(CFLAGS) $^ -L$(BUILD_DIR) -lport -ltest -lfds -o $@

# Create build directory if missing
$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
