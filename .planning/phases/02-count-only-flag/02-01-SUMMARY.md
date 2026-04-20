---
phase: 02-count-only-flag
plan: 01
subsystem: cli
tags: [c, push_swap, flag, count, benchmark]

# Dependency graph
requires:
  - phase: 01-benchmark-output
    provides: bench field in t_ops, write-guard pattern with ops->bench, flag_checker mechanism
provides:
  - count_only field in t_ops struct (zeroed by ft_memset in init_ops)
  - --count-only flag parsed by flag_checker and wired through run()
  - print_count() helper in bench.c printing total op count to stdout
  - All 11 op write guards extended to suppress output in count_only mode
affects: [03-norminette, evaluation, scripted-testing]

# Tech tracking
tech-stack:
  added: []
  patterns: [same struct-field + write-guard + flag_checker pattern as --bench from Phase 1]

key-files:
  created: []
  modified:
    - push_swap.h
    - parser.c
    - bench.c
    - main.c
    - s_functions.c
    - p_functions.c
    - r_functions.c
    - rr_functions.c

key-decisions:
  - "count_only field placed last in t_ops after bench — zeroed by existing ft_memset in init_ops, no init_ops changes needed"
  - "print_count() added to bench.c (not a new file) — keeps related output helpers together and avoids Makefile churn"
  - "ft_strncmp n=13 for --count-only (length 12 + 1) — follows established codebase convention for prefix-match safety"
  - "Norminette line-count compliance for run() deferred to Phase 3 per REQUIREMENTS.md out-of-scope section"

patterns-established:
  - "Write guard pattern: if (!ops->bench && !ops->count_only) write(...) — all 11 op functions use this double-flag guard"
  - "Flag parser extension: add *flag = 0 init + else-if branch in flag_checker while loop, update prototype with new int* param"

requirements-completed: [COUNT-01, COUNT-02, COUNT-03, COUNT-04]

# Metrics
duration: 2min
completed: 2026-04-20
---

# Phase 2 Plan 01: Count-Only Flag Summary

**--count-only mode: silent sort then single integer op-count to stdout, same struct-field and write-guard pattern as --bench**

## Performance

- **Duration:** 2 min
- **Started:** 2026-04-20T21:03:30Z
- **Completed:** 2026-04-20T21:05:10Z
- **Tasks:** 2
- **Files modified:** 8

## Accomplishments
- Added count_only field to t_ops (zeroed by existing ft_memset — no init_ops changes)
- Extended flag_checker with --count-only branch (n=13, same convention as all other flags)
- Extended all 11 write guards with && !ops->count_only to suppress op strings in count-only mode
- Added print_count() to bench.c that sums all 11 op counters and prints total to stdout
- Wired count_only through run(): local var, flag_checker call, ops assignment, print_count call
- Already-sorted input with --count-only correctly prints 0

## Task Commits

Each task was committed atomically:

1. **Task 1: Add count_only to t_ops and extend flag_checker** - `4c75f5d` (feat)
2. **Task 2: Update write guards, add print_count helper, wire run()** - `aa880b5` (feat)

**Plan metadata:** (docs commit follows)

## Files Created/Modified
- `push_swap.h` - Added int count_only to t_ops struct; updated flag_checker prototype; added print_count prototype
- `parser.c` - Extended flag_checker signature, init, and while loop with count_only support
- `bench.c` - Added print_count() function appended after print_bench()
- `main.c` - Added count_only local, updated flag_checker call, set ops->count_only, call print_count
- `s_functions.c` - Extended write guards for sa, sb, ss with && !ops->count_only
- `p_functions.c` - Extended write guards for pa, pb with && !ops->count_only
- `r_functions.c` - Extended write guards for ra, rb, rr with && !ops->count_only
- `rr_functions.c` - Extended write guards for rra, rrb, rrr with && !ops->count_only

## Decisions Made
- count_only field placed last in t_ops after bench — zeroed by existing ft_memset in init_ops, no init_ops changes needed
- print_count() added to bench.c (not a new file) — keeps related output helpers together and avoids Makefile churn
- ft_strncmp n=13 for --count-only (length 12 + 1) — follows established codebase convention for prefix-match safety
- Norminette line-count compliance for run() deferred to Phase 3 per REQUIREMENTS.md out-of-scope section

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness
- --count-only mode fully functional and regression-clean
- --bench mode regression verified (still 0 stdout lines, 5 stderr lines)
- Normal mode regression verified (op strings still printed)
- Ready for Phase 3: Norminette compliance (line count, formatting)
- Known blocker from Phase 1 still active: compute_disorder.c not in Makefile SRC — must be fixed before eval run

---
*Phase: 02-count-only-flag*
*Completed: 2026-04-20*
