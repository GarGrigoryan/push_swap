# push_swap

## What This Is

push_swap is a 42 school project that sorts a stack of integers using two stacks (A and B) and a defined set of 11 operations. The program selects among three sorting strategies (O(n²), O(n√n), O(n log n)) based on input size and disorder level. It supports `--bench` mode for full benchmark output and `--count-only` for scripted evaluation. It is evaluated on correctness, move efficiency, norminette compliance, and a live coding challenge.

## Core Value

The program must sort any valid integer input correctly using the minimum number of operations to pass the 42 evaluation.

## Current State (v1.1)

Shipped benchmark output and count-only flag. Binary compiles cleanly with compute_disorder linked. Evaluation-ready for scripted 100/500 number tests.

## Requirements

### Validated

- ✓ Core sorting logic (n², k-sort, radix) — v1.0 (pre-GSD)
- ✓ Strategy selection with --simple / --medium / --complex / --adaptive flags — v1.0
- ✓ Argument parsing and error handling — v1.0
- ✓ All 11 stack operations with write() output — v1.0
- ✓ compute_disorder function (exists in compute_disorder.c) — v1.0
- ✓ Benchmark output in correct format (disorder%, strategy name, all op counts) — v1.1
- ✓ --count-only flag that suppresses operation output and prints only total count — v1.1
- ✓ compute_disorder.c added to Makefile SRC — v1.1
- ✓ Unused find_min_position prototype removed from push_swap.h — v1.1
- ✓ Duplicate compute_disorder removed from utils.c — v1.1

### Active

None — planning next milestone.

### Out of Scope

- Norminette fixes — handled separately, not in this milestone
- 42 header additions — manual step, not automated
- New sorting algorithms — current strategies are sufficient

## Context

- Language: C (C99/C11 compatible, compiled with cc -Wall -Wextra -Werror)
- No external libraries; only write() and custom helpers allowed
- Makefile compiles all .c files in SRC variable; compute_disorder.c in SRC since v1.1
- 11 operation functions across s_functions.c, p_functions.c, r_functions.c, rr_functions.c
- bench.c holds all benchmark and count-only output helpers
- Defense evaluation checks: norminette, make, valgrind, error management, strategy flags, sort correctness, benchmark mode, 100/500 number tests, live coding
- Known norminette debt: run() in main.c has 8 variables (exceeds 5-variable limit)

## Constraints

- **No printf**: Only write() + ft_putnbr_fd for output — no printf calls allowed
- **Function length**: Max 25 lines per function (norminette rule)
- **No external libs**: All utilities must be self-implemented
- **42 evaluation order**: Correctness → memory safety → then features

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| Remove compute_disorder from utils.c | Clean separation; compute_disorder.c is canonical | Done — v1.1 Phase 3 |
| Add bench.c for print_bench function | Keeps main.c under 25 lines; isolated benchmark logic | Done — v1.1 Phase 1 |
| Add count_only field to t_ops struct | Minimal change; all op functions already receive ops pointer | Done — v1.1 Phase 2 |
| Guard write() with if (!ops->bench) inline | Norminette-safe; no signature changes needed | Done — v1.1 Phase 1 |
| print_count() in bench.c (not new file) | Keeps output helpers together; avoids Makefile churn | Done — v1.1 Phase 2 |

---
*Last updated: 2026-04-23 after v1.1 milestone*
