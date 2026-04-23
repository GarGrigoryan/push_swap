# Milestones: push_swap

## v1.1 — Benchmark + Count-Only

**Shipped:** 2026-04-23
**Phases:** 1–3 | **Plans:** 4 | **Tasks:** ~8
**Files changed:** 33 | **LOC:** +3485 / -148
**Timeline:** 2026-04-20 → 2026-04-23 (3 days)

### Delivered

Full benchmark output and count-only scripting support shipped and verified; codebase cleaned of duplicate symbols and stale prototypes.

### Key Accomplishments

1. Created `bench.c` with complete 5-line `[bench]` output to stderr — disorder%, strategy name, total ops, all 11 per-op counts
2. Refactored `main.c` to 6-line body via `run()` and `sort_dispatch()` static helpers — norminette function-length compliant
3. Added `ops->bench` guard to all 11 op functions — bench mode emits zero op strings to stdout
4. Added `--count-only` flag: total operation count printed to stdout, all op strings suppressed
5. Wired `compute_disorder.c` into Makefile SRC; removed duplicate from `utils.c` and stale `find_min_position` prototype from header

### Archive

- `.planning/milestones/v1.1-ROADMAP.md` — full phase details
- `.planning/milestones/v1.1-REQUIREMENTS.md` — requirements with outcomes

---
