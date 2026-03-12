#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

EXEC="./push_swap"

# Check if the executable exists
if [ ! -f "$EXEC" ]; then
    echo -e "${RED}Error: Executable '$EXEC' not found. Please compile your program first.${NC}"
    exit 1
fi

echo "======================================"
echo "      PUSH_SWAP AUTOMATED TESTS       "
echo "======================================"

# --- 1. ERROR HANDLING TESTS (Your Parser) ---
echo -e "\n--- PARSER: ERROR CASES (Should print 'Error' to stderr) ---"

test_error() {
    local test_name="$1"
    local args="$2"
    
    # Run the program, capture stderr (2>&1), discard stdout (> /dev/null)
local output=$(eval $EXEC $args 2>&1 > /dev/null)    
    if [[ "$output" == *"Error"* ]]; then
        echo -e "${GREEN}[OK]${NC} $test_name"
    else
        echo -e "${RED}[KO]${NC} $test_name -> Expected 'Error', got: '$output'"
    fi
}

test_error "Empty string" '""'
test_error "String of spaces" '"   "'
test_error "Non-numeric character" "1 2 a 3"
test_error "Duplicate numbers" "1 2 2 3"
test_error "Integer overflow (INT_MAX + 1)" "2147483649"
test_error "Integer underflow (INT_MIN - 1)" "-2147483649"
test_error "Sign without number" "1 2 + 3"


# --- 2. VALID PARSING TESTS (No output expected if already sorted) ---
echo -e "\n--- PARSER: VALID CASES (Should run without errors) ---"

test_valid() {
    local test_name="$1"
    local args="$2"
    
    # Run program, check exit code and stderr
local error_output=$(eval $EXEC $args 2>&1 > /dev/null)    
    if [[ "$error_output" == *"Error"* ]]; then
        echo -e "${RED}[KO]${NC} $test_name -> Should NOT print Error"
    else
        echo -e "${GREEN}[OK]${NC} $test_name"
    fi
}

test_valid "Already sorted (3 args)" "1 2 3"
test_valid "Already sorted (quoted)" '"1 2 3 4 5"'
test_valid "Negative numbers" "-1 -2 -3"
test_valid "Single number" "42"


# --- 3. SORTING ALGORITHM TESTS (Your Partner's Logic) ---
echo -e "\n--- ALGORITHM: SORTING MOVES COUNT ---"

test_sorting() {
    local test_name="$1"
    local max_moves="$2"
    local args="$3"
    
    # Count the number of lines (moves) outputted to stdout
    local moves=$($EXEC $args 2>/dev/null | wc -l | tr -d ' ')
    
    if [ "$moves" -le "$max_moves" ]; then
        echo -e "${GREEN}[OK]${NC} $test_name -> $moves moves (Max: $max_moves)"
    else
        echo -e "${RED}[KO]${NC} $test_name -> $moves moves (Exceeded max: $max_moves)"
    fi
}

# 42 Subject limits: 3 elements <= 2 moves. 5 elements <= 12 moves.
test_sorting "Sort 3 elements (Reversed)" 2 "3 2 1"
test_sorting "Sort 3 elements (Random)" 2 "2 1 3"
test_sorting "Sort 5 elements (Reversed)" 12 "5 4 3 2 1"
test_sorting "Sort 5 elements (Random)" 12 "1 5 2 4 3"

# --- LARGE STACK TESTS (RADIX) ---
echo -e "\n--- ALGORITHM: LARGE STACKS ---"

# Test 100 numbers (Limit: 700 moves)
test_sorting "Sort 100 elements" 700 "$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-500, 500), 100))))")"

# Test 500 numbers (Limit: 5500 moves)
test_sorting "Sort 500 elements" 5500 "$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-2000, 2000), 500))))")"
echo -e "\n======================================"
echo "             TESTS FINISHED           "
echo "======================================"