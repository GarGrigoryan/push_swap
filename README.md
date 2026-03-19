## 🚀 To-Do / Final Checklist

### 1. Core Fixes & Memory
- [x] **Git Sync:** Reconciled divergent branches.
- [x] **Makefile Cleanup:** Removed radix, fixed multiple definitions.
- [x] **Memory Leak on Error:** Fixed the Valgrind leak by calling `free_stack` before `exit(1)` when a duplicate/invalid argument is found, and patched the 44-byte `ops` leak in `main.c`.
- [x] **Norminette:** Run `norminette *.c *.h` and resolve all styling errors.

### 2. The 42 "Sorting Suite" Requirements
- [x] **Disorder Metric:** Implemented the `compute_disorder` function to calculate the percentage of "mistakes" (0.0 to 1.0) before making any moves.
- [x] **Strategy Flags:** Added command-line parsing to safely separate flags from negative numbers and handle routing:
  - [x] `--simple` -> Forces the O(n^2) algorithm.
  - [x] `--medium` -> Forces the O(n√n) algorithm.
  - [x] `--complex` -> Forces the O(n log n) algorithm.
  - [x] `--adaptive` (Default) -> Routes to Simple (< 0.2), Medium (0.2 - 0.5), or Complex (>= 0.5) based on disorder.
- [x] **Benchmark Mode (`--bench`):**
  - [x] Prints standard sorting operations to `stdout` for the checker script.
  - [x] Prints performance metrics safely to `stderr` (File Descriptor 2) so it doesn't interfere with standard 42 evaluation tools.

---

## 🧠 Algorithm Strategy & Dynamic Routing

Unlike standard `push_swap` projects that rely on a single algorithm, this program implements a **Dynamic Dispatcher**. 

Before a single operation is executed, the program analyzes the initial stack using a custom **Disorder Metric** (calculating the ratio of inverted pairs out of all possible pairs). Based on the chaos level of the starting stack—or user-provided flags—the dispatcher routes the numbers to the mathematically optimal sorting strategy:

* **Simple Sort (O(n^2)):** Best for tiny stacks or nearly sorted data (Disorder < 0.2).
* **K-Sort (O(n√n)):** A highly optimized distribution sort using dynamic chunking. Serves as the backbone for standard, moderately scrambled data (Disorder 0.2 - 0.5).
* **Radix Sort (O(n log n)):** A bitwise sorting algorithm that excels at crushing massive, highly chaotic datasets (Disorder >= 0.5).

---

## 📂 File Structure & Descriptions

To keep development organized, the source code is divided into logical components:

* **Core & Entry:**
    * `main.c`: The entry point and **Dynamic Dispatcher**. Calculates initial stack disorder, evaluates strategy flags, and routes the stack to the optimal algorithm. Also handles final memory cleanup and `--bench` outputs.
* **Parsing & Validation:**
    * `parser.c`, `parser_utils.c`, `parser_utils2.c`: Reads command-line arguments, converts strings to integers, and checks for errors (invalid characters, overflows, and duplicates).
    * `parse_flags`: Intelligently scans `argv` to decouple strategy/benchmark flags (`--`) from negative numbers (`-`), ensuring safe parsing.
* **Sorting Algorithms:**
    * `k_sort.c`: The Medium (O(n√n)) sorting logic using chunking.
    * `radix.c`: The Complex (O(n log n)) sorting logic using bitwise operations.
    * `n_square.c`, `n_square_utils.c`: The Simple (O(n^2)) sorting logic.
* **Stack Operations (Push_swap rules):**
    * `p_functions.c`: Push operations (`pa`, `pb`).
    * `s_functions.c`: Swap operations (`sa`, `sb`, `ss`).
    * `r_functions.c`, `rr_functions.c`: Rotate and reverse rotate operations.
    * `ra_rra_handlers.c`: Optimization handlers for combined rotations.
* **Utilities & Helpers:**
    * `utils.c`: Contains mathematical helpers, including the `compute_disorder` metric calculation.
    * `stack_utils.c`: List management, node creation, and stack freeing (`free_stack`) functions.
    * `ft_split.c`, `ft_strncmp.c`: Custom string manipulation.
    * `print_stack.c`: Debugging tool to visualize the stacks.
* **Testing:**
    * `tester.sh`, `checker_linux`: Bash scripts and the official 42 binary for validation.