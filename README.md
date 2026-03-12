## 🚀 To-Do / Final Checklist

### 1. Core Fixes & Memory
- [x] **Git Sync:** Reconciled divergent branches.
- [x] **Makefile Cleanup:** Removed radix, fixed multiple definitions.
- [ ] **Memory Leak on Error:** Fix the Valgrind leak by calling `free_stack` before `exit(1)` when a duplicate/invalid argument is found.
- [ ] [cite_start]**Norminette:** Run `norminette *.c *.h` and resolve all styling errors[cite: 33].

### 2. The 42 "Sorting Suite" Requirements
- [ ] [cite_start]**Disorder Metric:** Implement the `compute_disorder` function to calculate the percentage of "mistakes" (0.0 to 1.0) before making any moves[cite: 160, 161, 178].
- [ ] [cite_start]**Strategy Flags:** Add command-line parsing to handle optional flags[cite: 261]:
  - [ ] [cite_start]`--simple` -> Forces the O(n^2) algorithm[cite: 262].
  - [ ] [cite_start]`--medium` -> Forces the O(n√n) algorithm[cite: 263].
  - [ ] [cite_start]`--complex` -> Forces the O(n log n) algorithm[cite: 264].
  - [ ] [cite_start]`--adaptive` (Default) -> Routes to Simple (< 0.2), Medium (0.2 - 0.5), or Complex (>= 0.5) based on disorder[cite: 205, 206, 207, 265].
- [ ] **Benchmark Mode (`--bench`):**
  - [ ] [cite_start]Print standard sorting operations to `stdout`[cite: 288].
  - [ ] [cite_start]Print metrics to `stderr`: Disorder %, Strategy name & complexity, Total Ops, and precise counts for every specific operation (sa, pb, ra, etc.)[cite: 280, 281, 282, 283, 284, 285].

---
