*This activity has been created as part of the 42 curriculum by arsezaka, gargrigo*

# push_swap

## Description

push_swap is a sorting algorithm project from the 42 school curriculum. The goal is to sort a stack of integers using two stacks (A and B) and a restricted set of operations, while minimising the total number of moves.

What makes this implementation unique is a **Dynamic Dispatcher**: before executing a single operation, the program analyses the initial stack using a custom Disorder Metric — the ratio of inverted pairs out of all possible pairs — and automatically routes the input to the mathematically optimal sorting strategy. Users can also manually select a strategy via command-line flags.

Supported operations: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`.

---

## Instructions

### Compilation

```bash
make
```

This produces the `push_swap` executable. Standard Makefile rules are available:

```bash
make clean    
make fclean   
make re       
```

### Running push_swap

```bash
./push_swap 3 1 4 1 5 9 2 6
```

The program prints the sorted sequence of operations to stdout, one per line. If the input is already sorted, nothing is printed.

### Strategy flags

| Flag | Algorithm | Use case |
|------|-----------|----------|
| `--simple` | O(n²) selection sort | Tiny or nearly sorted stacks |
| `--medium` | O(n√n) chunk-based k-sort | Moderately scrambled stacks |
| `--complex` | O(n log n) radix sort | Large, highly chaotic stacks |
| `--adaptive` | Auto-selects based on disorder | Default behaviour |

```bash
./push_swap --complex 5 4 3 2 1
./push_swap --adaptive 42 7 13 2 99
./push_swap 3 1 4 2 5         
```

### Benchmark mode

Adding `--bench` prints performance metrics to stderr without interfering with stdout (checker compatibility preserved):

```bash
./push_swap --bench --complex 5 4 3 2 1
./push_swap --bench --complex 5 4 3 2 1 2>/dev/null   # stdout only (for checker)
./push_swap --bench --complex 5 4 3 2 1 >/dev/null    # stderr only (benchmark info)
```

### Using with the checker

```bash
ARG="3 1 4 2 5"
./push_swap $ARG | ./checker_linux $ARG
```

### Testing with large inputs

```bash
# 100 numbers
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ') && echo "$ARG" | xargs ./push_swap | tee /tmp/ops.txt | wc -l && cat /tmp/ops.txt | ./checker_linux $ARG

# 500 numbers
ARG=$(shuf -i 1-1000 -n 500 | tr '\n' ' ') && echo "$ARG" | xargs ./push_swap | tee /tmp/ops.txt | wc -l && cat /tmp/ops.txt | ./checker_linux $ARG
```

### Error cases

The program prints `Error` to stderr and exits for: non-numeric arguments, duplicate values, integers outside the 32-bit signed range. With no arguments it exits silently.

---

## Algorithms

### Disorder Metric

Before any sorting begins, the program calculates the **disorder** of the stack: the ratio of inverted pairs (pairs where `a[i] > a[j]` for `i < j`) to total pairs. This produces a float in the range `[0.0, 1.0]` where `0.0` is fully sorted and `1.0` is fully reversed. The adaptive dispatcher uses this value to pick the right algorithm.

### Simple — O(n²) selection sort

Implemented in `n_square.c`. Repeatedly finds the minimum element in stack A, rotates it to the top using the fewest rotations (comparing `ra` vs `rra` cost), pushes it to B, then pushes everything back. Special-cased hardcoded solutions handle 2, 3, and 5 elements for optimal move counts.

Used when: `--simple` flag is set, or adaptive mode detects disorder < 0.2 (nearly sorted), or stack size ≤ 5.

### Medium — O(n√n) chunk-based k-sort

Implemented in `k_sort.c`. Elements are assigned rank indexes, then divided into chunks of size √n. During distribution, elements in the current chunk window are pushed to B (with `rb` to keep the largest on top); elements outside the window trigger `ra`. Stack B is then drained back to A by repeatedly finding and rotating the maximum to the top.

Chunk sizes: 15 for n ≤ 100, 30 for n ≤ 500, 45 for larger inputs.

Used when: `--medium` flag is set, or adaptive mode detects 0.2 ≤ disorder < 0.5.

### Complex — O(n log n) radix sort

Implemented in `radix.c`. Elements are assigned zero-based rank indexes, then sorted bitwise from the least significant bit upward. On each pass, elements with a `0` bit at the current position are pushed to B; elements with a `1` bit are rotated in A. After each pass, B is pushed back to A. The number of passes equals ⌈log₂(n)⌉.

This algorithm is insensitive to initial order and performs consistently on large, chaotic inputs.

Used when: `--complex` flag is set, or adaptive mode detects disorder ≥ 0.5.

### Adaptive — dynamic dispatcher (default)

The dispatcher reads the disorder metric and stack size, then routes:

```
len <= 5              → sort_5 (hardcoded optimal)
disorder < 0.2        → simple sort
0.2 <= disorder < 0.5 → k-sort (medium)
disorder >= 0.5       → radix sort (complex)
```

Running without any flag uses adaptive mode.

---

## Resources

### Documentation and references

- [42 push_swap subject (official PDF)](https://cdn.intra.42.fr/pdf/pdf/192775/en.subject.pdf)
- [Radix sort — Wikipedia](https://en.wikipedia.org/wiki/Radix_sort)
- [Counting inversions (disorder metric)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics))
- [visualgo.net — sorting visualisations](https://visualgo.net/en/sorting)

### AI usage


- **Algorithm design review**: validating the chunk-size selection logic in `k_sort.c` and the bitwise pass count calculation in `radix.c`
- **Debugging**: identifying the cause of the 25-operation count on 5-element inputs (adaptive dispatcher incorrectly routing small high-disorder inputs to radix sort) and designing the `sort_5` fix
- **Code review**: catching Norminette violations (variable declarations after executable statements, missing 42 headers, misaligned prototypes)

AI was not used to write the core sorting algorithms or the stack operation functions — those were written and debugged by the team directly.

---

## Contributions

### arsezaka
- Project scaffolding and Makefile
- Parsing system: `parser.c`, `parser_utils.c`, `parser_utils2.c`
- Flag parsing (`flag_checker`) and negative number disambiguation
- `ft_split.c`, `ft_strncmp.c` string utilities
- `radix.c` — O(n log n) radix sort implementation
- Integration of all modules in `main.c`
- Error handling and memory cleanup

### gargrigo
- Stack operation functions: `p_functions.c`, `s_functions.c`, `r_functions.c`, `rr_functions.c`, `ra_rra_handlers.c`
- `n_square.c`, `n_square_utils.c` — O(n²) selection sort and sort_3/sort_5 hardcoded solutions
- `k_sort.c` — O(n√n) chunk-based distribution sort
- `compute_disorder` metric in `utils.c`
- Adaptive dispatcher logic in `main.c`
- Benchmark mode output (`--bench` flag)
- `print_stack.c` debug utility