# push_swap

## What This Is

push_swap is a 42 school project that sorts a stack of integers using two stacks (A and B) and a defined set of 11 operations (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr). The program selects among three sorting strategies (O(n²), O(n√n), O(n log n)) based on input size and disorder level. It is evaluated on correctness, move efficiency, norminette compliance, and a live coding challenge.

## Core Value

The program must sort any valid integer input correctly using the minimum number of operations to pass the 42 evaluation.

## Requirements

### Validated

- ✓ Core sorting logic (n², k-sort, radix) — Phase 0 (pre-GSD)
- ✓ Strategy selection with --simple / --medium / --complex / --adaptive flags — Phase 0
- ✓ Argument parsing and error handling — Phase 0
- ✓ All 11 stack operations with write() output — Phase 0
- ✓ compute_disorder function (exists in compute_disorder.c) — Phase 0

### Active

- [ ] Benchmark output in correct format (disorder%, strategy name, all op counts)
- [ ] --count-only flag that suppresses operation output and prints only total count
- [ ] compute_disorder.c added to Makefile SRC
- [ ] Unused find_min_position prototype removed from push_swap.h

### Out of Scope

- Norminette fixes — handled separately, not in this milestone
- 42 header additions — manual step, not automated
- New sorting algorithms — current strategies are sufficient

## Context

- Language: C (C99/C11 compatible, compiled with cc -Wall -Wextra -Werror)
- No external libraries; only write() and custom helpers allowed
- Makefile compiles all .c files in SRC variable; compute_disorder.c is missing from SRC
- utils.c contains a duplicate/broken compute_disorder — should be removed (Option A from ISSUES.md)
- 11 operation functions spread across s_functions.c, p_functions.c, r_functions.c, rr_functions.c
- Benchmark output currently only prints "Benchmark: Total moves = N" — needs full format
- Defense evaluation checks: norminette, make, valgrind, error management, strategy flags, sort correctness, benchmark mode, 100/500 number tests, live coding

## Constraints

- **No printf**: Only write() + ft_putnbr_fd for output — no printf calls allowed
- **Function length**: Max 25 lines per function (norminette rule — respect even outside norminette session)
- **No external libs**: All utilities must be self-implemented
- **42 evaluation order**: Correctness → memory safety → then features

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| Remove compute_disorder from utils.c (Option A) | Clean separation; compute_disorder.c already exists and is correct | — Pending |
| Add bench.c for print_bench function | Keeps main.c under 25 lines; isolated benchmark logic | — Pending |
| Add count_only field to t_ops struct | Minimal change; all op functions already receive ops pointer | — Pending |

---
*Last updated: 2026-04-20 after milestone v1.1 initialization*
