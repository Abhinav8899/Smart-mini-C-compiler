CC      = gcc
CFLAGS  = -Wall -Wno-unused-function -g
TARGET  = compiler

SRC     = compiler_utils.c semantic.c parser.tab.c lex.yy.c main.c

# Arch Linux: flex ships libfl.a but the flag is still -lfl
# If linking fails, fall back to no flex lib (noyywrap handles it)
LDFLAGS = -lm
FLEX_LIB := $(shell $(CC) -lfl -x c /dev/null -o /dev/null 2>/dev/null && echo "-lfl" || echo "")
LDFLAGS += $(FLEX_LIB)

all: $(TARGET)

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

$(TARGET): parser.tab.c lex.yy.c $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET) parser.tab.c parser.tab.h lex.yy.c *.o

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	@echo "--- Test 1: for loop ---"
	./$(TARGET) < tests/test_for.txt
	@echo ""
	@echo "--- Test 2: functions ---"
	./$(TARGET) < tests/test_func.txt
	@echo ""
	@echo "--- Test 3: do-while ---"
	./$(TARGET) < tests/test_dowhile.txt
	@echo ""
	@echo "--- Test 4: switch ---"
	./$(TARGET) < tests/test_switch.txt
	@echo ""
	@echo "--- Test 5: arrays ---"
	./$(TARGET) < tests/test_arrays.txt
	@echo ""
	@echo "--- Test 6: full ---"
	./$(TARGET) < tests/test_full.txt
	@echo ""
	@echo "--- Test 7: error recovery (expected errors) ---"
	./$(TARGET) < tests/test_errors.txt || true

.PHONY: all clean run test
