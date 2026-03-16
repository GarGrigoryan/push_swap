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


## 📂 File Structure & Descriptions

To keep development organized, the source code is divided into logical components:

* **Core & Entry:**
    * `main.c`: The entry point. Handles the overall flow, algorithm routing, and final memory cleanup.
* **Parsing & Validation:**
    * `parser.c`, `parser_utils.c`, `parser_utils2.c`: Reads command-line arguments, converts strings to integers, and checks for errors (invalid characters, overflows, and duplicates).
* **Sorting Algorithms:**
    * `k_sort.c`: The Medium ($O(n\sqrt{n})$) sorting logic using chunking.
    * `radix.c`: The Complex ($O(n \log n)$) sorting logic using bitwise operations.
    * `n_square.c`, `n_square_utils.c`: The Simple ($O(n^2)$) sorting logic.
* **Stack Operations (Push_swap rules):**
    * `p_functions.c`: Push operations (`pa`, `pb`).
    * `s_functions.c`: Swap operations (`sa`, `sb`, `ss`).
    * `r_functions.c`, `rr_functions.c`: Rotate and reverse rotate operations.
    * `ra_rra_handlers.c`: Optimization handlers for combined rotations.
* **Utilities & Helpers:**
    * `utils.c`, `stack_utils.c`: List management, node creation, and stack freeing (`free_stack`) functions.
    * `ft_split.c`, `ft_strncmp.c`: Custom string manipulation.
    * `print_stack.c`: Debugging tool to visualize the stacks.
* **Testing:**
    * `tester.sh`, `checker_linux`: Bash scripts and the official 42 binary for validation.