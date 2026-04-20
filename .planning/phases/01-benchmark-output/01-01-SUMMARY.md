---
phase: 01-benchmark-output
plan: 01
subsystem: cli
tags: [c, push_swap, benchmark, norminette, stderr, write]

# Dependency graph
requires: []
provides:
  - bench.c with print_bench function outputting 5-line evaluator format to stderr
  - print_bench prototype in push_swap.h
  - bench.c listed in Makefile SRC
  - main() refactored to 6-line body via run and sort_dispatch static helpers
affects:
  - 01-benchmark-output (phase 2, 3 plans)

# Tech tracking
tech-stack:
  added: []
  patterns:
    - Static helper pattern for keeping norminette functions under 25 lines
    - All benchmark output goes to fd 2 (stderr) via write() and ft_putnbr_fd()
    - Float percentage formatting with two decimal places using integer arithmetic

key-files:
  created:
    - bench.c
  modified:
    - push_swap.h
    - Makefile
    - main.c

key-decisions:
  - "Extract run() and sort_dispatch() static helpers to reduce main() to 6 lines — cleaner than inline compression tricks"
  - "Use (free_stack(&stack_a), 1) comma-expression in run() return to handle ops null case in one line"
  - "print_ops_line2 uses rra:/rrb:/rrr: labels with one extra space in write string vs ra:/rb:/rr: to maintain alignment"

patterns-established:
  - "Benchmark output: always fd 2 (stderr), never fd 1 (stdout)"
  - "Float-to-percent formatting: multiply by 100, split integer/decimal parts, handle carry when decimal >= 100"

requirements-completed: [BENCH-01, BENCH-02, BENCH-03, BENCH-04, BENCH-05]

# Metrics
duration: 3min
completed: 2026-04-20
---

# Phase 1 Plan 01: Benchmark Output — bench.c and main.c refactor Summary

**5-line `[bench]` stderr output with disorder%, strategy name, total ops, and per-op counts; main() reduced to 6-line body via sort_dispatch and run helpers**

## Performance

- **Duration:** ~3 min
- **Started:** 2026-04-20T20:09:36Z
- **Completed:** 2026-04-20T20:12:38Z
- **Tasks:** 2
- **Files modified:** 4

## Accomplishments

- Created bench.c with print_bench and four static helpers (print_percent, resolve_strategy, print_ops_line1, print_ops_line2)
- Added print_bench prototype to push_swap.h; added bench.c to Makefile SRC
- Refactored main.c: extracted sort_dispatch and run static helpers, reducing main() body to 6 lines
- Verified all 5 [bench] output lines go to stderr only with correct format

## Task Commits

Each task was committed atomically:

1. **Task 1: Create bench.c and wire header + Makefile** - `e855a26` (feat)
2. **Task 2: Refactor main.c — extract sort_dispatch, call print_bench, reach under 25 lines** - `c32bf19` (feat)

## Files Created/Modified

- `/home/nomad/tmp/push_swap/bench.c` - New file: print_bench and 4 static helpers for 5-line evaluator output format
- `/home/nomad/tmp/push_swap/push_swap.h` - Added print_bench prototype before #endif
- `/home/nomad/tmp/push_swap/Makefile` - Added bench.c to SRC variable
- `/home/nomad/tmp/push_swap/main.c` - Refactored: added sort_dispatch and run helpers; main() body is now 6 lines

## Decisions Made

- **Extracted `run()` helper:** Moving all initialization and sort logic into a `run(int argc, char **argv)` static function reduces main() to 6 lines while keeping all logic intact. This is cleaner than combining declarations or using C tricks.
- **Comma-expression return:** `return (free_stack(&stack_a), 1)` handles the ops-null early-return in run() without requiring a multi-line if block.
- **Per-op write() strings:** Each label in print_ops_line1/line2 uses explicit write() calls with exact byte counts to avoid printf dependency and keep output deterministic.

## Deviations from Plan

None - plan executed exactly as written.

The plan noted that reducing main() to 25 lines might require a `run()` helper approach — that approach was used and reduced main() to 6 lines (well under the 25-line ceiling).

## Issues Encountered

None — build passed with zero errors and zero warnings on first attempt for bench.c. main.c initial version had 30 lines in main() so the `run()` extraction was applied to meet the 25-line ceiling.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness

- bench.c is complete and wire-ready — evaluator can invoke `./push_swap --bench N...` and receive 5-line stderr output
- main() is norminette-compliant in line count (6 lines); has 8 variables in run() which exceeds norminette 5-variable limit — Phase 3 cleanup can address
- compute_disorder.c is still not in Makefile SRC (pre-existing blocker noted in STATE.md) — must be fixed before eval run

---
*Phase: 01-benchmark-output*
*Completed: 2026-04-20*

## Self-Check: PASSED

- FOUND: bench.c
- FOUND: push_swap.h (with print_bench prototype)
- FOUND: Makefile (with bench.c in SRC)
- FOUND: main.c (main() body = 6 lines)
- FOUND: 01-01-SUMMARY.md
- FOUND commit e855a26: feat(01-01): create bench.c and wire header + Makefile
- FOUND commit c32bf19: feat(01-01): refactor main.c — extract sort_dispatch and run helpers, main under 25 lines
