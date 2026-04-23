# Project Retrospective

*A living document updated after each milestone. Lessons feed forward into future planning.*

## Milestone: v1.1 — Benchmark + Count-Only

**Shipped:** 2026-04-23
**Phases:** 3 | **Plans:** 4 | **Sessions:** ~3

### What Was Built

- `bench.c` with complete 5-line `[bench]` stderr output — disorder%, strategy name, total + per-op counts
- `--count-only` flag for scripted evaluation — single integer stdout, zero op strings
- Clean build with `compute_disorder` symbol linked; duplicate removed from `utils.c`

### What Worked

- Struct field pattern (`bench`, then `count_only` placed last in `t_ops`) — zeroed by existing `ft_memset`, no `init_ops` changes needed either time
- Inline `if (!ops->bench)` guard reused identically for `count_only` — consistent pattern across phases made Phase 2 very fast
- Keeping output helpers in `bench.c` (both `print_bench` and `print_count`) — avoided Makefile churn and kept output code in one place
- Phase 1 gap closure (plan 02) correctly identified and planned: bench stdout suppression was a separate orthogonal concern from the initial print_bench work

### What Was Inefficient

- Phase 1 required two plans because the stdout suppression concern (plan 02) wasn't caught in the initial plan scope — could have been planned together since it was a predictable follow-on
- run() in main.c accumulated 8 variables during refactoring — norminette debt that wasn't caught until code review

### Patterns Established

- `ops->{flag}` guard: all op `write(1,...)` calls check `!ops->bench` and `!ops->count_only` — this pattern should be followed for any future output-mode flag
- Output helpers belong in `bench.c`, not `main.c` or new files
- `ft_strncmp(flag, "--flag-name", n+1)` for flag parsing — n = strlen of flag + 1 for prefix-match safety

### Key Lessons

1. When adding a new output-suppression flag, the struct field + write guard pattern is well-established — just follow it, don't redesign
2. Norminette variable count limits should be checked during implementation, not discovered at code review
3. Cleanup phases (dead code, stale prototypes) are low-risk and fast — plan them tightly, they don't need deep research

### Cost Observations

- Model mix: ~100% sonnet
- Sessions: ~3 across phases + review + fix
- Notable: Each plan executed in under 5 minutes — well-scoped atomic changes

---

## Cross-Milestone Trends

### Process Evolution

| Milestone | Sessions | Phases | Key Change |
|-----------|----------|--------|------------|
| v1.1 | ~3 | 3 | First GSD-tracked milestone; established ops-flag pattern |

### Cumulative Quality

| Milestone | UAT Tests | Issues | Zero-Dep Additions |
|-----------|-----------|--------|--------------------|
| v1.1 | 4 | 0 | 0 (pure C, no deps) |

### Top Lessons (Verified Across Milestones)

1. Small, orthogonal struct fields zeroed by existing `ft_memset` are the safest way to add state to the ops pipeline
2. Code review finds cosmetic/norminette issues that code changes miss — worth running after each phase
