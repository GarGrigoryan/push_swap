# Requirements: push_swap

**Defined:** 2026-04-20
**Core Value:** Correct sorting with minimum operations to pass 42 evaluation

## v1.1 Requirements

### Benchmark Output

- [x] **BENCH-01**: `--bench` output includes disorder percentage formatted as `XX.XX%`
- [x] **BENCH-02**: `--bench` output includes strategy name based on actual strategy used (e.g. `Adaptive / O(n√n)`)
- [x] **BENCH-03**: `--bench` output includes total operation count (sum of all 11 op counters)
- [x] **BENCH-04**: `--bench` output includes individual counts for all 11 operations (sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr)
- [x] **BENCH-05**: `print_bench` logic extracted into `bench.c` helper to keep `main` under 25 lines

### Count-Only Flag

- [x] **COUNT-01**: `t_ops` struct has `count_only` integer field in `push_swap.h`
- [x] **COUNT-02**: `flag_checker` in `parser.c` parses `--count-only` flag and sets `ops->count_only = 1`
- [x] **COUNT-03**: All 11 operation functions (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`) skip `write()` when `ops->count_only` is set
- [x] **COUNT-04**: Program prints total operation count to stdout after sorting when `--count-only` is given

### Cleanup

- [x] **CLEAN-01**: `compute_disorder.c` added to Makefile `SRC` variable
- [x] **CLEAN-02**: Duplicate/broken `compute_disorder` function removed from `utils.c`
- [x] **CLEAN-03**: Unused `find_min_position` prototype removed from `push_swap.h`

## Future Requirements

*(None identified — all known issues either in scope or deferred to norminette session)*

## Out of Scope

| Feature | Reason |
|---------|--------|
| Norminette fixes | Handled in a separate dedicated session to avoid mixing fix types |
| 42 header additions | Manual step — cannot be automated |
| New sorting strategies | Current strategies are sufficient for evaluation |

## Traceability

| Requirement | Phase | Status |
|-------------|-------|--------|
| BENCH-01 | Phase 1 | Complete |
| BENCH-02 | Phase 1 | Complete |
| BENCH-03 | Phase 1 | Complete |
| BENCH-04 | Phase 1 | Complete |
| BENCH-05 | Phase 1 | Complete |
| COUNT-01 | Phase 2 | Complete |
| COUNT-02 | Phase 2 | Complete |
| COUNT-03 | Phase 2 | Complete |
| COUNT-04 | Phase 2 | Complete |
| CLEAN-01 | Phase 3 | Complete |
| CLEAN-02 | Phase 3 | Complete |
| CLEAN-03 | Phase 3 | Complete |

**Coverage:**
- v1.1 requirements: 12 total
- Mapped to phases: 12
- Unmapped: 0 ✓

---
*Requirements defined: 2026-04-20*
*Last updated: 2026-04-20 — traceability confirmed after roadmap creation*
