# Roadmap: push_swap

## Milestones

- **v1.0 Core** - Phases 0 (pre-GSD, complete)
- **v1.1 Benchmark + Count-Only** - Phases 1-3 (in progress)

## Phases

<details>
<summary>v1.0 Core (Phase 0) - pre-GSD, complete</summary>

### Phase 0: Core Implementation
**Goal**: Sorting program is complete and operational
**Plans**: pre-GSD

All core work completed before GSD tracking:
- [x] Three sorting strategies (n², k-sort, radix)
- [x] Strategy selection with --simple / --medium / --complex / --adaptive flags
- [x] Argument parsing and error handling
- [x] All 11 stack operations with write() output
- [x] compute_disorder function in compute_disorder.c

</details>

### v1.1 Benchmark + Count-Only (In Progress)

**Milestone Goal:** Full benchmark output with disorder%, strategy, and per-op counts; --count-only flag for scripted evaluation; Makefile and header cleanup.

- [x] **Phase 1: Benchmark Output** - `--bench` prints complete stats in correct format (completed 2026-04-20)
- [ ] **Phase 2: Count-Only Flag** - `--count-only` suppresses op output and prints total
- [ ] **Phase 3: Cleanup** - Makefile, utils.c, and header pruned of dead code

## Phase Details

### Phase 1: Benchmark Output
**Goal**: Running `--bench` shows disorder percentage, strategy name, total op count, and individual op counts in correct format
**Depends on**: Phase 0 (pre-GSD complete)
**Requirements**: BENCH-01, BENCH-02, BENCH-03, BENCH-04, BENCH-05
**Success Criteria** (what must be TRUE):
  1. `./push_swap --bench 5 3 1 4 2` prints disorder percentage formatted as `XX.XX%`
  2. `./push_swap --bench 5 3 1 4 2` prints the strategy name that was actually used (e.g., `Adaptive / O(n√n)`)
  3. `./push_swap --bench 5 3 1 4 2` prints total operation count and individual counts for all 11 operations
  4. `main.c` stays under 25 lines — benchmark printing logic lives in `bench.c`
**Plans**: 1 plan

Plans:
- [ ] 01-01-PLAN.md — Create bench.c with full print_bench output; refactor main.c under 25 lines

### Phase 2: Count-Only Flag
**Goal**: Users can run `./push_swap --count-only <numbers>` to get only the total operation count printed, with no operation strings emitted
**Depends on**: Phase 1
**Requirements**: COUNT-01, COUNT-02, COUNT-03, COUNT-04
**Success Criteria** (what must be TRUE):
  1. `./push_swap --count-only 5 3 1 4 2` prints a single integer (total op count) and nothing else to stdout
  2. `./push_swap --count-only 5 3 1 4 2` produces no `sa`, `pb`, `ra` etc. lines — operation strings are fully suppressed
  3. `t_ops` struct in `push_swap.h` has a `count_only` field and `flag_checker` sets it when `--count-only` is given
**Plans**: TBD

### Phase 3: Cleanup
**Goal**: Codebase compiles cleanly with compute_disorder linked, no duplicate functions, and no stale prototypes in the header
**Depends on**: Phase 2
**Requirements**: CLEAN-01, CLEAN-02, CLEAN-03
**Success Criteria** (what must be TRUE):
  1. `make` succeeds and `compute_disorder` is available at link time (compute_disorder.c is in Makefile SRC)
  2. `utils.c` contains no `compute_disorder` definition — the duplicate is gone
  3. `push_swap.h` has no `find_min_position` prototype
**Plans**: TBD

## Progress

**Execution Order:** 1 -> 2 -> 3

| Phase | Plans Complete | Status | Completed |
|-------|----------------|--------|-----------|
| 1. Benchmark Output | 1/1 | Complete   | 2026-04-20 |
| 2. Count-Only Flag | 0/TBD | Not started | - |
| 3. Cleanup | 0/TBD | Not started | - |
