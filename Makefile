MAIN_NAME = main

INCLUDES = include
LINKS = -lm
CFLAGS = -Wall -I$(INCLUDES)

CC = gcc
BIN = bin
SRC = src
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(SRCS))
DEPS = $(wildcard $(INCLUDES)/*.h)

TEST_FOLDER = test
TEST_OBJS = $(filter-out $(BIN)/$(MAIN_NAME).o, $(OBJS))
TEST_SRC = $(filter-out $(TEST_FOLDER)/unity.c, $(wildcard $(TEST_FOLDER)/*.c))
TEST_EXECUTABLES = $(TEST_SRC:.c=)
UNITY_SRC = $(TEST_FOLDER)/unity/unity.c
TEST_FLAGS = -I$(INCLUDES) $(DEBUG_FLAGS)

.PHONY: test debug clean

all: clean $(OBJS) $(BIN)/$(MAIN_NAME)

debug: CFLAGS += -g -DDEBUG
debug: all

$(BIN)/$(MAIN_NAME): $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LINKS)

$(BIN)/%.o: $(SRC)/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) $(LINKS)

clean:
	@rm -rf $(BIN)
	@find . -name "*.o" -exec rm -rf {} \;
	@find . -name "*.log" -exec rm -rf {} \;

test: $(TEST_OBJS) $(TEST_EXECUTABLES)
	@echo "[i] Compiling tests..."
	@$(foreach test, $(TEST_SRC), \
	$(CC) $(TEST_FLAGS) $(test) -o $(test:.c=) $(TEST_OBJS) $(UNITY_SRC) $(LINKS); \
	)
	@echo "[i] Compilation tests complete"