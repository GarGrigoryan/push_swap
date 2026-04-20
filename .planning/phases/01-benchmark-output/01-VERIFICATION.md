---
phase: 01-benchmark-output
verified: 2026-04-20T21:00:00Z
status: passed
score: 6/6 must-haves verified
re_verification:
  previous_status: gaps_found
  previous_score: 5/6
  gaps_closed:
    - "All benchmark output goes to stderr (fd 2), not stdout — stdout now returns 0 lines during --bench"
  gaps_remaining: []
  regressions: []
human_verification:
  - test: "Visual format check for evaluator alignment"
    expected: "Each [bench] line renders clearly aligned in a terminal — spacing between labels and counts looks intentional"
    why_human: "Cannot verify visual column alignment or evaluator aesthetics programmatically"
---

# Phase 1: Benchmark Output Verification Report

**Phase Goal:** `--bench` prints complete stats in correct format; stdout empty during bench
**Verified:** 2026-04-20T21:00:00Z
**Status:** passed
**Re-verification:** Yes — after gap closure (01-02-PLAN.md: add `bench` field to `t_ops`, guard all 11 op `write()` calls)

## Goal Achievement

### Observable Truths

| #  | Truth                                                                                                          | Status     | Evidence                                                                                                        |
|----|----------------------------------------------------------------------------------------------------------------|------------|-----------------------------------------------------------------------------------------------------------------|
| 1  | `./push_swap --bench 5 3 1 4 2` prints a line containing disorder formatted as `XX.XX%`                       | VERIFIED   | Live: `[bench] disorder:  70.00%` — two decimal digits, percent sign, correct value                            |
| 2  | `./push_swap --bench 5 3 1 4 2` prints a strategy name line matching the actual dispatch used                 | VERIFIED   | Live: `[bench] strategy:  Adaptive / O(n^2)` — len=5 hits len<=5 path in sort_dispatch and resolve_strategy    |
| 3  | `./push_swap --bench 5 3 1 4 2` prints a total_ops line equal to the sum of all 11 op counters                | VERIFIED   | Live: `[bench] total_ops:  8` — pa=2 + pb=2 + ra=4 = 8, all others 0                                          |
| 4  | `./push_swap --bench 5 3 1 4 2` prints all 11 op labels (sa sb ss pa pb ra rb rr rra rrb rrr) with counts    | VERIFIED   | Live line 1: `[bench] sa:  0  sb:  0  ss:  0  pa:  2  pb:  2` — line 2: `[bench] ra:  4  rb:  0  rr:  0  rra:  0  rrb:  0  rrr:  0` |
| 5  | All benchmark output goes to stderr (fd 2), not stdout                                                         | VERIFIED   | Live: `./push_swap --bench 5 3 1 4 2 2>/dev/null \| wc -l` returns `0`; `2>&1 1>/dev/null \| wc -l` returns `5` |
| 6  | `main()` function body in `main.c` is 25 lines or fewer                                                       | VERIFIED   | `main()` body = 7 lines (opening brace to closing brace inclusive, counted with awk)                           |

**Score:** 6/6 truths verified

### Required Artifacts

**01-01 artifacts:**

| Artifact      | Expected                                                            | Status   | Details                                                                                           |
|---------------|---------------------------------------------------------------------|----------|---------------------------------------------------------------------------------------------------|
| `bench.c`     | print_bench + static helpers for float, strategy, per-op lines      | VERIFIED | 93 lines; 4 static helpers (print_percent, resolve_strategy, print_ops_line1, print_ops_line2) + print_bench |
| `push_swap.h` | print_bench prototype                                               | VERIFIED | Line 99: `void	print_bench(t_ops *ops, float disorder, int strategy, int len);`               |
| `Makefile`    | bench.c in SRC list                                                 | VERIFIED | bench.c listed in SRC; `make re` compiles bench.o with zero errors/warnings                      |
| `main.c`      | Refactored main under 25 lines calling sort_dispatch + print_bench  | VERIFIED | main() body = 7 lines; sort_dispatch and print_bench called from run() static helper             |

**01-02 artifacts (gap closure):**

| Artifact        | Expected                                                     | Status   | Details                                                         |
|-----------------|--------------------------------------------------------------|----------|-----------------------------------------------------------------|
| `push_swap.h`   | t_ops struct with `int bench` field added                    | VERIFIED | Line 46: `int				bench;` — 12th member of s_ops struct |
| `s_functions.c` | sa/sb/ss write() calls guarded by `if (!ops->bench)`        | VERIFIED | Lines 34-35, 42-43, 51-52 — all three ops guarded              |
| `p_functions.c` | pa/pb write() calls guarded by `if (!ops->bench)`           | VERIFIED | Lines 27-28, 42-43 — both ops guarded                          |
| `r_functions.c` | ra/rb/rr write() calls guarded by `if (!ops->bench)`        | VERIFIED | Lines 37-38, 45-46, 54-55 — all three ops guarded              |
| `rr_functions.c`| rra/rrb/rrr write() calls guarded by `if (!ops->bench)`     | VERIFIED | Lines 40-41, 48-49, 57-58 — all three ops guarded              |
| `main.c`        | ops->bench set from bench local variable after init_ops      | VERIFIED | Line 65 of main.c: `ops->bench = bench;` after init_ops guard  |

### Key Link Verification

| From                               | To            | Via                                                   | Status  | Details                                                                      |
|------------------------------------|---------------|-------------------------------------------------------|---------|------------------------------------------------------------------------------|
| `main.c` run()                     | `bench.c`     | `print_bench(ops, disorder, strategy, len)` guarded by `bench == 1` | WIRED | Line 70-71: `if (bench == 1) / print_bench(ops, disorder, strategy, len);` |
| `bench.c`                          | `push_swap.h` | `#include "push_swap.h"` — uses t_ops, ft_putnbr_fd, ft_strlen | WIRED | Line 1 of bench.c: `#include "push_swap.h"` |
| `Makefile`                         | `bench.c`     | SRC variable lists bench.c                            | WIRED   | bench.c in SRC; `make re` confirms bench.o compiled                         |
| `main.c` run()                     | `t_ops.bench` | `ops->bench = bench` assignment after init_ops guard  | WIRED   | Line 65: `ops->bench = bench;` — bench local propagated into ops struct     |
| `s_functions.c / p_functions.c / r_functions.c / rr_functions.c` | `t_ops.bench` | `if (!ops->bench)` guard on every write(1,...) call | WIRED | All 11 op functions confirmed in source — each write() is guarded           |

### Requirements Coverage

| Requirement | Source Plans        | Description                                                             | Status    | Evidence                                                                                    |
|-------------|---------------------|-------------------------------------------------------------------------|-----------|----------------------------------------------------------------------------------------------|
| BENCH-01    | 01-01, 01-02        | `--bench` output includes disorder percentage formatted as `XX.XX%`     | SATISFIED | Live: `[bench] disorder:  70.00%` — format matches exactly                                  |
| BENCH-02    | 01-01, 01-02        | `--bench` output includes strategy name based on actual strategy used   | SATISFIED | Live: `[bench] strategy:  Adaptive / O(n^2)` — threshold logic matches sort_dispatch        |
| BENCH-03    | 01-01, 01-02        | `--bench` output includes total operation count (sum of all 11)         | SATISFIED | Live: `[bench] total_ops:  8` = pa(2)+pb(2)+ra(4)+all others(0)                             |
| BENCH-04    | 01-01, 01-02        | `--bench` output includes individual counts for all 11 operations       | SATISFIED | Live: all 11 labels present across two output lines                                          |
| BENCH-05    | 01-01, 01-02        | print_bench logic in bench.c; main() under 25 lines                     | SATISFIED | bench.c exists with print_bench; main() body = 7 lines (awk-confirmed)                      |

No orphaned requirements — all 5 BENCH requirements are claimed by 01-01-PLAN.md and 01-02-PLAN.md and traced to Phase 1 in REQUIREMENTS.md.

### Anti-Patterns Found

No blockers. Previous `write(1, ...)` warnings in s_functions.c, p_functions.c, r_functions.c, rr_functions.c are resolved — all 11 calls are now guarded with `if (!ops->bench)`.

Remaining note (out of scope, unchanged):
- `push_swap.h` line 76 retains `find_min_position` prototype (stale). Tracked as CLEAN-03 in Phase 3. No impact on Phase 1 goal.

### Human Verification Required

#### 1. Visual Format Alignment

**Test:** Run `./push_swap --bench 5 3 1 4 2` in a terminal and visually inspect the five [bench] lines.
**Expected:** Labels and counts are consistently spaced; the evaluator can read disorder%, strategy name, total, and per-op counts at a glance.
**Why human:** Column alignment and aesthetic readability cannot be verified programmatically.

## Re-Verification Summary

**Gap from initial verification:** Truth 5 ("All benchmark output goes to stderr (fd 2), not stdout") was FAILED because op functions unconditionally called `write(1, ...)` regardless of bench mode. `./push_swap --bench 5 3 1 4 2 2>/dev/null | wc -l` returned 8.

**Gap closure method (01-02-PLAN.md):**
- Added `int bench` as 12th field of `s_ops` struct in `push_swap.h` — zeroed automatically by `ft_memset` in `init_ops`, so normal mode (bench=0) is fully preserved.
- Added `ops->bench = bench;` in `run()` immediately after the `init_ops` guard block in `main.c`.
- Wrapped every `write(1, ...)` call in all 11 op functions across 4 files with `if (!ops->bench)`.

**Verified closure:** Live run confirms `./push_swap --bench 5 3 1 4 2 2>/dev/null | wc -l` now prints `0`. Normal mode `./push_swap 5 3 1 4 2 | wc -l` still prints `8`. Bench stderr `./push_swap --bench 5 3 1 4 2 2>&1 1>/dev/null | wc -l` still prints `5`. Build clean: `make re` with `-Wall -Wextra -Werror` passes with zero errors and zero warnings.

**Regressions:** None detected.

---

_Verified: 2026-04-20T21:00:00Z_
_Verifier: Claude (gsd-verifier)_
