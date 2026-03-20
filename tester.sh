#!/bin/bash

# ============================================================
#  push_swap — 42 Yerevan Evaluation Tester
#  Based on the official evaluation scale
# ============================================================

# ── Colors ──────────────────────────────────────────────────
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
DIM='\033[2m'
RESET='\033[0m'

# ── Counters ─────────────────────────────────────────────────
PASS=0
FAIL=0
SKIP=0

# ── Helpers ──────────────────────────────────────────────────
ok()   { echo -e "  ${GREEN}[PASS]${RESET} $1"; ((PASS++)); }
fail() { echo -e "  ${RED}[FAIL]${RESET} $1"; ((FAIL++)); }
skip() { echo -e "  ${YELLOW}[SKIP]${RESET} $1"; ((SKIP++)); }
info() { echo -e "  ${DIM}$1${RESET}"; }
header() { echo -e "\n${BOLD}${CYAN}══════════════════════════════════════════${RESET}"; \
           echo -e "${BOLD}${CYAN}  $1${RESET}"; \
           echo -e "${BOLD}${CYAN}══════════════════════════════════════════${RESET}"; }

# ── Locate checker binary ─────────────────────────────────────
CHECKER=""
if [[ -f "./checker_linux" ]]; then
    CHECKER="./checker_linux"
elif [[ -f "./checker_Mac" ]]; then
    CHECKER="./checker_Mac"
elif [[ -f "./checker" ]]; then
    CHECKER="./checker"
fi

# ── Count instructions helper ─────────────────────────────────
count_ops() {
    # $1 = ARG string
    local out
    out=$(./push_swap $1 2>/dev/null)
    echo "$out" | grep -c '[a-z]' 2>/dev/null || echo 0
}

check_sorted() {
    # Returns 0 if checker says OK
    local arg="$1"
    if [[ -z "$CHECKER" ]]; then
        # Fallback: verify sorted ourselves
        local out
        out=$(./push_swap $arg 2>/dev/null | "$CHECKER" $arg 2>/dev/null)
        [[ "$out" == "OK" ]]
    else
        local result
        result=$(./push_swap $arg 2>/dev/null | $CHECKER $arg 2>/dev/null)
        [[ "$result" == "OK" ]]
    fi
}

# ════════════════════════════════════════════════════════════════
#   0. PREFLIGHT
# ════════════════════════════════════════════════════════════════
header "0. PREFLIGHT"

if [[ ! -f "./push_swap" ]] && [[ ! -f "./Makefile" ]]; then
    echo -e "${RED}  No push_swap binary and no Makefile found. Run this script from the repo root.${RESET}"
    exit 1
fi

if [[ -z "$CHECKER" ]]; then
    echo -e "  ${YELLOW}Warning: no checker binary found (checker_linux / checker_Mac / checker).${RESET}"
    echo -e "  ${YELLOW}Correctness tests will be skipped where checker is required.${RESET}"
else
    info "Using checker: $CHECKER"
    chmod +x "$CHECKER" 2>/dev/null
fi

# ════════════════════════════════════════════════════════════════
#   1. MAKEFILE & COMPILATION
# ════════════════════════════════════════════════════════════════
header "1. MAKEFILE & COMPILATION"

# Check Makefile exists
if [[ -f "./Makefile" ]]; then
    ok "Makefile present"
else
    fail "Makefile not found"
fi

# Check required rules exist in Makefile
for rule in NAME all clean fclean re; do
    if grep -qE "^$rule" ./Makefile 2>/dev/null; then
        ok "Makefile rule '$rule' found"
    else
        fail "Makefile rule '$rule' missing"
    fi
done

# Check -Wall -Wextra -Werror flags
if grep -q "\-Wall" ./Makefile && grep -q "\-Wextra" ./Makefile && grep -q "\-Werror" ./Makefile; then
    ok "Compilation flags: -Wall -Wextra -Werror present"
else
    fail "Missing one or more of: -Wall -Wextra -Werror in Makefile"
fi

# Build
echo ""
info "Running 'make'..."
make -s 2>&1
if [[ -f "./push_swap" ]]; then
    ok "push_swap compiled successfully"
else
    fail "push_swap binary not produced — stopping compilation section"
fi

# Clean / fclean / re
info "Testing 'make clean'..."
make clean -s 2>/dev/null && ok "'make clean' works" || fail "'make clean' failed"

info "Testing 'make re'..."
make re -s 2>&1 >/dev/null
if [[ -f "./push_swap" ]]; then
    ok "'make re' works and binary present"
else
    fail "'make re' failed to produce binary"
fi

info "Testing 'make fclean'..."
make fclean -s 2>/dev/null && ok "'make fclean' works" || fail "'make fclean' failed"

info "Rebuilding for rest of tests..."
make -s 2>&1 >/dev/null

# ════════════════════════════════════════════════════════════════
#   2. README.md COMPLIANCE
# ════════════════════════════════════════════════════════════════
header "2. README.md COMPLIANCE"

if [[ -f "./README.md" ]]; then
    ok "README.md present"

    # First line italicized with 42 curriculum format
    FIRST_LINE=$(head -1 ./README.md)
    if echo "$FIRST_LINE" | grep -qiE "42 curriculum"; then
        ok "README first line references '42 curriculum'"
    else
        fail "README first line does not reference '42 curriculum' (expected italicized line)"
    fi

    # Sections
    for section in "Description" "Instructions" "Resources"; do
        if grep -qi "## *$section\|# *$section" ./README.md; then
            ok "README has '$section' section"
        else
            fail "README missing '$section' section"
        fi
    done

    # Algorithm explanation
    if grep -qi "algorithm\|O(n\|adaptive\|complex\|simple\|medium" ./README.md; then
        ok "README contains algorithm documentation"
    else
        fail "README missing algorithm explanation (Simple O(n²), Medium O(n√n), Complex O(n log n), Adaptive)"
    fi

    # Contributions
    if grep -qi "contribution\|contributed\|login\|author" ./README.md; then
        ok "README has learner contributions section"
    else
        fail "README missing learner contributions documentation"
    fi

    # AI usage
    if grep -qi "AI\|ChatGPT\|Claude\|artificial intelligence" ./README.md; then
        ok "README documents AI tool usage"
    else
        fail "README missing AI usage documentation in Resources section"
    fi
else
    fail "README.md not found"
fi

# ════════════════════════════════════════════════════════════════
#   3. ERROR MANAGEMENT
# ════════════════════════════════════════════════════════════════
header "3. ERROR MANAGEMENT"

ERROR_PASS=0

# Non-numeric parameter
OUT=$(./push_swap abc 2>&1)
if echo "$OUT" | grep -q "^Error$"; then
    ok "Non-numeric input → prints 'Error'"
    ((ERROR_PASS++))
else
    fail "Non-numeric input → expected 'Error\\n' on stderr, got: '$OUT'"
fi

# Duplicate numeric parameter
OUT=$(./push_swap 1 2 3 1 2>&1)
if echo "$OUT" | grep -q "^Error$"; then
    ok "Duplicate number → prints 'Error'"
    ((ERROR_PASS++))
else
    fail "Duplicate number → expected 'Error\\n' on stderr, got: '$OUT'"
fi

# Greater than MAXINT
OUT=$(./push_swap 1 2147483648 3 2>&1)
if echo "$OUT" | grep -q "^Error$"; then
    ok "Number > MAXINT → prints 'Error'"
    ((ERROR_PASS++))
else
    fail "Number > MAXINT → expected 'Error\\n' on stderr, got: '$OUT'"
fi

# No parameters — should print nothing
OUT=$(./push_swap 2>&1)
if [[ -z "$OUT" ]]; then
    ok "No parameters → no output (correct)"
    ((ERROR_PASS++))
else
    fail "No parameters → should produce no output, got: '$OUT'"
fi

info "Error management: $ERROR_PASS/4 passed (need ≥3)"
[[ $ERROR_PASS -ge 3 ]] && ok "Error management section PASSED" || fail "Error management section FAILED (< 3/4)"

# ════════════════════════════════════════════════════════════════
#   4. STRATEGY FLAGS — BASIC TESTS
# ════════════════════════════════════════════════════════════════
header "4. STRATEGY FLAGS — BASIC TESTS"

STRAT_PASS=0
ARG="5 4 3 2 1"

for flag in --simple --medium --complex --adaptive; do
    OUT=$(./push_swap $flag $ARG 2>/dev/null)
    if [[ -n "$OUT" ]]; then
        if [[ -n "$CHECKER" ]]; then
            RESULT=$(echo "$OUT" | $CHECKER $ARG 2>/dev/null)
            if [[ "$RESULT" == "OK" ]]; then
                ok "$flag sorts correctly (checker: OK)"
                ((STRAT_PASS++))
            else
                fail "$flag: checker returned '$RESULT' instead of OK"
            fi
        else
            ok "$flag produces output (checker not available to verify)"
            ((STRAT_PASS++))
        fi
    else
        fail "$flag produced no output for '$ARG'"
    fi
done

# Default (no flag) = --adaptive
OUT=$(./push_swap $ARG 2>/dev/null)
if [[ -n "$OUT" ]]; then
    if [[ -n "$CHECKER" ]]; then
        RESULT=$(echo "$OUT" | $CHECKER $ARG 2>/dev/null)
        if [[ "$RESULT" == "OK" ]]; then
            ok "No flag (default/adaptive) sorts correctly (checker: OK)"
            ((STRAT_PASS++))
        else
            fail "No flag: checker returned '$RESULT'"
        fi
    else
        ok "No flag produces output"
        ((STRAT_PASS++))
    fi
else
    fail "No flag: no output produced"
fi

info "Strategy flags: $STRAT_PASS/5 passed (need ≥3)"
[[ $STRAT_PASS -ge 3 ]] && ok "Strategy flags section PASSED" || fail "Strategy flags section FAILED (< 3/5)"

# ════════════════════════════════════════════════════════════════
#   5. IDENTITY TESTS — ALREADY SORTED
# ════════════════════════════════════════════════════════════════
header "5. IDENTITY TESTS — ALREADY SORTED INPUTS"

IDENTITY_PASS=0
SORTED_TESTS=("42" "2 3" "0 1 2 3" "0 1 2 3 4 5 6 7 8 9")

for ARG in "${SORTED_TESTS[@]}"; do
    OUT=$(./push_swap $ARG 2>/dev/null)
    if [[ -z "$OUT" ]]; then
        ok "Already sorted '$ARG' → 0 instructions (correct)"
        ((IDENTITY_PASS++))
    else
        OPS=$(echo "$OUT" | wc -l | tr -d ' ')
        fail "Already sorted '$ARG' → $OPS instructions (expected 0)"
    fi
done

info "Identity tests: $IDENTITY_PASS/4 passed (need ≥3)"
[[ $IDENTITY_PASS -ge 3 ]] && ok "Identity section PASSED" || fail "Identity section FAILED (< 3/4)"

# ════════════════════════════════════════════════════════════════
#   6. SMALL INPUTS — 3 NUMBERS
# ════════════════════════════════════════════════════════════════
header "6. SMALL INPUTS — 3 NUMBERS"

SMALL_TESTS=("2 1 0" "0 2 1" "1 0 2" "2 0 1" "1 2 0")
for ARG in "${SMALL_TESTS[@]}"; do
    OPS=$(./push_swap $ARG 2>/dev/null | grep -c '[a-z]' || echo 0)
    if [[ -n "$CHECKER" ]]; then
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
        if [[ "$RESULT" == "OK" ]]; then
            if [[ $OPS -le 3 ]]; then
                ok "3-num '$ARG' → OK, $OPS ops (≤3: excellent)"
            elif [[ $OPS -le 5 ]]; then
                ok "3-num '$ARG' → OK, $OPS ops (≤5: acceptable)"
            else
                fail "3-num '$ARG' → OK but $OPS ops (>5: too many)"
            fi
        else
            fail "3-num '$ARG' → checker: '$RESULT' (expected OK)"
        fi
    else
        if [[ $OPS -le 5 ]]; then
            ok "3-num '$ARG' → $OPS ops (checker not available)"
        else
            fail "3-num '$ARG' → $OPS ops (>5: too many)"
        fi
    fi
done

# ════════════════════════════════════════════════════════════════
#   7. MEDIUM INPUTS — 5 NUMBERS
# ════════════════════════════════════════════════════════════════
header "7. MEDIUM INPUTS — 5 NUMBERS"

MEDIUM_TESTS=("1 5 2 4 3" "5 1 4 2 3" "3 5 1 4 2" "4 2 5 1 3")
for ARG in "${MEDIUM_TESTS[@]}"; do
    OPS=$(./push_swap $ARG 2>/dev/null | grep -c '[a-z]' || echo 0)
    if [[ -n "$CHECKER" ]]; then
        RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
        if [[ "$RESULT" == "OK" ]]; then
            if [[ $OPS -le 12 ]]; then
                ok "5-num '$ARG' → OK, $OPS ops (≤12: good)"
            elif [[ $OPS -le 15 ]]; then
                ok "5-num '$ARG' → OK, $OPS ops (≤15: acceptable)"
            elif [[ $OPS -le 25 ]]; then
                echo -e "  ${YELLOW}[WARN]${RESET} 5-num '$ARG' → OK, $OPS ops (>15 but ≤25: correctness OK, optimize further)"
            else
                fail "5-num '$ARG' → OK but $OPS ops (>25: too many even for lenient grading)"
            fi
        else
            fail "5-num '$ARG' → checker: '$RESULT' (expected OK)"
        fi
    else
        if [[ $OPS -le 25 ]]; then
            ok "5-num '$ARG' → $OPS ops (checker not available)"
        else
            fail "5-num '$ARG' → $OPS ops (>25: too many)"
        fi
    fi
done

# ════════════════════════════════════════════════════════════════
#   8. BENCHMARK MODE
# ════════════════════════════════════════════════════════════════
header "8. BENCHMARK MODE"

ARG="5 4 3 2 1"

# stdout should have sorting instructions
OUT_STDOUT=$(./push_swap --bench --simple $ARG 2>/dev/null)
if [[ -n "$OUT_STDOUT" ]]; then
    ok "--bench --simple: produces sorting instructions on stdout"
else
    fail "--bench --simple: no stdout output"
fi

# stderr should have benchmark info
OUT_STDERR=$(./push_swap --bench --simple $ARG 2>&1 >/dev/null)
if echo "$OUT_STDERR" | grep -qiE "benchmark|disorder|operation|moves|strategy|total|complexity"; then
    ok "--bench: stderr contains benchmark info"
    info "  Benchmark output: $(echo "$OUT_STDERR" | head -3)"
else
    fail "--bench: stderr missing benchmark info — got: '$OUT_STDERR'"
fi

# Disorder for sorted input ≈ 0%
OUT_SORTED=$(./push_swap --bench --simple 1 2 3 4 5 2>&1 >/dev/null)
SORTED_MOVES=$(echo "$OUT_SORTED" | grep -oiE "[0-9]+" | tail -1)
if [[ "${SORTED_MOVES:-99}" -eq 0 ]]; then
    ok "Disorder/moves of sorted input = 0 (correct)"
else
    info "Benchmark for sorted '1 2 3 4 5': '$OUT_SORTED'"
    skip "Disorder for sorted input — verify manually that disorder/moves ≈ 0"
fi

# Disorder for reverse-sorted — should be more than sorted
OUT_REV=$(./push_swap --bench --simple 5 4 3 2 1 2>&1 >/dev/null)
REV_MOVES=$(echo "$OUT_REV" | grep -oiE "[0-9]+" | tail -1)
if [[ "${REV_MOVES:-0}" -gt "${SORTED_MOVES:-0}" ]]; then
    ok "Disorder/moves of reverse-sorted ($REV_MOVES) > sorted (${SORTED_MOVES:-0}) — makes sense"
else
    info "Benchmark for reverse '5 4 3 2 1': '$OUT_REV'"
    skip "Disorder for reverse-sorted — verify manually that value is higher than sorted"
fi

# ════════════════════════════════════════════════════════════════
#   9. LARGE INPUTS — 100 NUMBERS
# ════════════════════════════════════════════════════════════════
header "9. LARGE INPUTS — 100 NUMBERS"

if ! command -v shuf &>/dev/null; then
    skip "100-number tests: 'shuf' not available on this system"
else
    LARGE_PASS=0
    for i in 1 2 3; do
        ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
        OPS=$(./push_swap $ARG 2>/dev/null | grep -c '[a-z]' || echo 0)
        if [[ -n "$CHECKER" ]]; then
            RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
            if [[ "$RESULT" == "OK" ]]; then
                ((LARGE_PASS++))
                if [[ $OPS -lt 700 ]]; then
                    ok "100-num run $i → OK, $OPS ops (excellent: <700)"
                elif [[ $OPS -lt 1500 ]]; then
                    ok "100-num run $i → OK, $OPS ops (good: <1500)"
                elif [[ $OPS -lt 2000 ]]; then
                    ok "100-num run $i → OK, $OPS ops (acceptable: <2000)"
                else
                    fail "100-num run $i → OK but $OPS ops (>2000: too many)"
                fi
            else
                fail "100-num run $i → checker: '$RESULT'"
            fi
        else
            if [[ $OPS -lt 2000 ]]; then
                ok "100-num run $i → $OPS ops (checker not available)"
            else
                fail "100-num run $i → $OPS ops (>2000: too many)"
            fi
        fi
    done
fi

# ════════════════════════════════════════════════════════════════
#   10. STRATEGY COMPARISON — 50 NUMBERS
# ════════════════════════════════════════════════════════════════
header "10. STRATEGY FLAG COMPARISON — 50 NUMBERS"

if ! command -v shuf &>/dev/null; then
    skip "Strategy comparison: 'shuf' not available"
else
    ARG=$(shuf -i 1-200 -n 50 | tr '\n' ' ')
    info "Testing same 50-number input across all strategy flags..."

    OPS_SIMPLE=0; OPS_MEDIUM=0; OPS_COMPLEX=0
    declare -A STRAT_OPS

    for flag in --simple --medium --complex --adaptive; do
        OPS=$(./push_swap $flag $ARG 2>/dev/null | grep -c '[a-z]' || echo 0)
        STRAT_OPS[$flag]=$OPS
        if [[ -n "$CHECKER" ]]; then
            RESULT=$(./push_swap $flag $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
            if [[ "$RESULT" == "OK" ]]; then
                ok "$flag → OK, $OPS ops"
            else
                fail "$flag → checker: '$RESULT'"
            fi
        else
            ok "$flag → $OPS ops (checker not available)"
        fi
    done

    # --complex should generally use fewer ops than --simple
    if [[ ${STRAT_OPS[--complex]:-0} -lt ${STRAT_OPS[--simple]:-0} ]]; then
        ok "--complex (${STRAT_OPS[--complex]} ops) uses fewer ops than --simple (${STRAT_OPS[--simple]} ops)"
    else
        info "--complex (${STRAT_OPS[--complex]:-?} ops) vs --simple (${STRAT_OPS[--simple]:-?} ops) — performance expectation not met (not failing)"
    fi
fi

# ════════════════════════════════════════════════════════════════
#   11. VERY LARGE INPUTS — 500 NUMBERS
# ════════════════════════════════════════════════════════════════
header "11. VERY LARGE INPUTS — 500 NUMBERS"

if ! command -v shuf &>/dev/null; then
    skip "500-number tests: 'shuf' not available"
else
    for i in 1 2; do
        ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ')
        OPS=$(./push_swap $ARG 2>/dev/null | grep -c '[a-z]' || echo 0)
        if [[ -n "$CHECKER" ]]; then
            RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
            if [[ "$RESULT" == "OK" ]]; then
                if [[ $OPS -lt 5500 ]]; then
                    ok "500-num run $i → OK, $OPS ops (excellent: <5500)"
                elif [[ $OPS -lt 8000 ]]; then
                    ok "500-num run $i → OK, $OPS ops (good: <8000)"
                elif [[ $OPS -lt 12000 ]]; then
                    ok "500-num run $i → OK, $OPS ops (acceptable: <12000)"
                else
                    fail "500-num run $i → OK but $OPS ops (>12000: too many)"
                fi
            else
                fail "500-num run $i → checker: '$RESULT'"
            fi
        else
            if [[ $OPS -lt 12000 ]]; then
                ok "500-num run $i → $OPS ops (checker not available)"
            else
                fail "500-num run $i → $OPS ops (>12000: too many)"
            fi
        fi
    done
fi

# ════════════════════════════════════════════════════════════════
#   12. BONUS — CHECKER PROGRAM (if ./checker exists)
# ════════════════════════════════════════════════════════════════
if [[ -f "./checker" ]]; then
    header "12. BONUS — CHECKER ERROR MANAGEMENT"

    # Non-numeric
    OUT=$(echo "" | ./checker abc 2>&1)
    if echo "$OUT" | grep -q "^Error$"; then
        ok "Checker: non-numeric → 'Error'"
    else
        fail "Checker: non-numeric → expected 'Error', got: '$OUT'"
    fi

    # Duplicate
    OUT=$(echo "" | ./checker 1 2 3 1 2>&1)
    if echo "$OUT" | grep -q "^Error$"; then
        ok "Checker: duplicate → 'Error'"
    else
        fail "Checker: duplicate → expected 'Error', got: '$OUT'"
    fi

    # > MAXINT
    OUT=$(echo "" | ./checker 1 2147483648 3 2>&1)
    if echo "$OUT" | grep -q "^Error$"; then
        ok "Checker: > MAXINT → 'Error'"
    else
        fail "Checker: > MAXINT → expected 'Error', got: '$OUT'"
    fi

    # No parameters → no output
    OUT=$(echo "" | ./checker 2>&1)
    if [[ -z "$OUT" ]]; then
        ok "Checker: no params → no output"
    else
        fail "Checker: no params → should produce no output, got: '$OUT'"
    fi

    # Invalid instruction
    OUT=$(printf "zzz\n" | ./checker 0 9 1 8 2 2>&1)
    if echo "$OUT" | grep -q "^Error$"; then
        ok "Checker: invalid instruction → 'Error'"
    else
        fail "Checker: invalid instruction → expected 'Error', got: '$OUT'"
    fi

    # Instruction with extra spaces
    OUT=$(printf " sa \n" | ./checker 1 0 2>&1)
    if echo "$OUT" | grep -q "^Error$"; then
        ok "Checker: instruction with spaces → 'Error'"
    else
        fail "Checker: instruction with spaces → expected 'Error', got: '$OUT'"
    fi

    header "12b. BONUS — CHECKER FALSE TESTS"

    # KO test from the scale
    OUT=$(printf "sa\npb\nrrr\n" | ./checker 0 9 1 8 2 7 3 6 4 5 2>/dev/null)
    if [[ "$OUT" == "KO" ]]; then
        ok "Checker: [sa, pb, rrr] on '0 9 1 8 2 7 3 6 4 5' → KO"
    else
        fail "Checker: expected 'KO', got: '$OUT'"
    fi

    # Another invalid sort
    OUT=$(printf "sa\n" | ./checker 1 2 3 2>/dev/null)
    if [[ "$OUT" == "KO" ]]; then
        ok "Checker: wrong ops on '1 2 3' → KO"
    else
        fail "Checker: expected 'KO' for unsorted result, got: '$OUT'"
    fi

    header "12c. BONUS — CHECKER RIGHT TESTS"

    # Already sorted → CTRL+D (EOF)
    OUT=$(printf "" | ./checker 0 1 2 2>/dev/null)
    if [[ "$OUT" == "OK" ]]; then
        ok "Checker: '0 1 2' with no instructions → OK"
    else
        fail "Checker: expected 'OK', got: '$OUT'"
    fi

    # Valid instruction list from the scale
    OUT=$(printf "pb\nra\npb\nra\nsa\nra\npa\npa\n" | ./checker 0 9 1 8 2 2>/dev/null)
    if [[ "$OUT" == "OK" ]]; then
        ok "Checker: [pb,ra,pb,ra,sa,ra,pa,pa] on '0 9 1 8 2' → OK"
    else
        fail "Checker: expected 'OK', got: '$OUT'"
    fi

    # Dynamic: sort a random small set via push_swap, then verify with checker
    ARG="3 1 4 1 5"  # intentionally avoid dup — use clean set
    ARG="3 1 4 2 5"
    INSTRUCTIONS=$(./push_swap $ARG 2>/dev/null)
    OUT=$(echo "$INSTRUCTIONS" | ./checker $ARG 2>/dev/null)
    if [[ "$OUT" == "OK" ]]; then
        ok "Checker: push_swap output for '$ARG' → OK (dynamic)"
    else
        fail "Checker: push_swap output for '$ARG' → '$OUT' (expected OK)"
    fi
else
    header "12. BONUS — CHECKER"
    skip "No ./checker binary found — bonus section skipped"
fi

# ════════════════════════════════════════════════════════════════
#   MEMORY LEAK HINT
# ════════════════════════════════════════════════════════════════
header "MEMORY LEAKS (manual guidance)"
if command -v valgrind &>/dev/null; then
    info "Running valgrind on 'push_swap 5 4 3 2 1'..."
    LEAK_OUT=$(valgrind --leak-check=full --error-exitcode=1 ./push_swap 5 4 3 2 1 2>&1 >/dev/null)
    if echo "$LEAK_OUT" | grep -q "no leaks are possible\|0 bytes in 0 blocks"; then
        ok "valgrind: no leaks detected"
    elif echo "$LEAK_OUT" | grep -q "definitely lost: 0 bytes"; then
        ok "valgrind: 0 bytes definitely lost"
    else
        LOST=$(echo "$LEAK_OUT" | grep "definitely lost" | head -1)
        fail "valgrind: $LOST"
    fi
else
    skip "valgrind not available — check leaks manually with: valgrind --leak-check=full ./push_swap 5 4 3 2 1"
fi

# ════════════════════════════════════════════════════════════════
#   SUMMARY
# ════════════════════════════════════════════════════════════════
TOTAL=$((PASS + FAIL))
echo ""
echo -e "${BOLD}${CYAN}══════════════════════════════════════════${RESET}"
echo -e "${BOLD}  SUMMARY${RESET}"
echo -e "${BOLD}${CYAN}══════════════════════════════════════════${RESET}"
echo -e "  ${GREEN}PASS : $PASS${RESET}"
echo -e "  ${RED}FAIL : $FAIL${RESET}"
echo -e "  ${YELLOW}SKIP : $SKIP${RESET}"
echo -e "  Total checks run: $TOTAL"
echo ""
if [[ $FAIL -eq 0 ]]; then
    echo -e "  ${GREEN}${BOLD}All checks passed! 🎉${RESET}"
elif [[ $FAIL -le 3 ]]; then
    echo -e "  ${YELLOW}${BOLD}Minor issues found — review FAILs above.${RESET}"
else
    echo -e "  ${RED}${BOLD}Several issues found — review FAILs above.${RESET}"
fi
echo ""
echo -e "  ${DIM}Note: The live coding task (--count-only flag) must be${RESET}"
echo -e "  ${DIM}done manually during the defense session.${RESET}"
echo ""
