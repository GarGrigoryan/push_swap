# STATE.md — push_swap

## Current Position

Phase: Not started (defining requirements)
Plan: —
Status: Defining requirements
Last activity: 2026-04-20 — Milestone v1.1 started

## Project Reference

See: .planning/PROJECT.md (updated 2026-04-20)

**Core value:** Correct sorting with minimum operations to pass 42 evaluation
**Current focus:** Milestone v1.1 — Benchmark output, --count-only flag, minor cleanup

## Accumulated Context

- Project is a 42 school push_swap implementation
- Three sorting strategies: n² (simple), k-sort (medium/√n), radix (complex/log n)
- All 11 operations already implemented and output via write()
- compute_disorder.c exists but is NOT in Makefile SRC
- utils.c has a broken duplicate of compute_disorder — needs removal
- Benchmark currently only prints "Benchmark: Total moves = N"
- ISSUES.md documents all known issues; this milestone covers Priority 2, 3, 4 only
