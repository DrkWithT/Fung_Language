# Makefile
# Project: Fung Language
# Derek Tan

# compiler vars
CXX := clang -std=c11
CXXFLAGS := -Wall -Wextra -Werror

ifeq ($(DEBUG_BUILD),1)
	CXXFLAGS += -g -Og
else
	CXXFLAGS += -O2
endif

# executable dir
BIN_DIR := ./bin

# important dirs
BUILD_DIR := ./build
MAIN_DIR := ./mains
INCL_DIR := ./include
SRC_DIR := ./src

# auto generate source targets
SRCS := $(shell find $(SRC_DIR) -name '*.c')
MAINS := $(shell find $(MAIN_DIR) -name '*.c')
ALL_SRCS := $(SRCS) $(MAINS)

# auto generate object targets
SRCS_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
MAINS_OBJS := $(patsubst $(MAIN_DIR)/%.c,$(BUILD_DIR)/%.o,$(MAINS))

# auto generate executable targets
EXECS := $(patsubst $(BUILD_DIR)/%.o,$(BIN_DIR)/%,$(MAINS_OBJS))

# search ./src and ./test for C sources
vpath %.c $(MAIN_DIR)
vpath %.c $(SRC_DIR)
# vpath %.h $(INCL_DIR)

.PHONY: sloc tell all objs execs clean_all clean_execs

# utility rule: show SLOC
sloc:
	@wc -l $(MAIN_DIR)/*.c $(SRC_DIR)/*.c

# entry build rule
all: objs execs

# object file build stage
objs: $(SRCS_OBJS) $(MAINS_OBJS)

# executable link stage
execs: $(EXECS)

# sub-rules
$(BIN_DIR)/%: $(BUILD_DIR)/%.o $(SRCS_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(INCL_DIR) -o $@

$(BUILD_DIR)/%.o: $(MAIN_DIR)/%.c
	$(CXX) $(CXXFLAGS) -c $< -I$(INCL_DIR) -o $@

# clean rules
clean_all:
	rm -f $(EXECS) $(BUILD_DIR)/*.o

clean_execs:
	rm -f $(EXECS)

clean_tests:
	rm -f $(BIN_DIR)/test_*
