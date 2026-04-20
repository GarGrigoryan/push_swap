# Phase 1: Benchmark Output - Research

**Researched:** 2026-04-20
**Domain:** C output formatting, strategy name resolution, bench.c extraction
**Confidence:** HIGH

## Summary

Phase 1 replaces a minimal benchmark stub (`"Benchmark: Total moves = N"`) with the
full five-line format the 42 evaluator expects on stderr. All data is already
available: disorder is computed before sorting, the strategy integer is known, and
every op counter lives in `t_ops`. The only engineering work is (a) formatting
`float` disorder as `XX.XX%` without `printf`, (b) mapping strategy integer + context
to a human-readable name, and (c) moving the printing logic into a new `bench.c` file
so `main.c` stays under 25 lines.

No new data structures are needed. `t_ops`, `t_stack`, and the strategy integer passed
through `flag_checker` already carry everything `print_bench` needs. The codebase uses
`write()` + `ft_putnbr_fd` for all output — this constraint is already established and
must be respected here too.

**Primary recommendation:** Create `bench.c` with a `print_bench(t_ops *ops, float
disorder, int strategy, int len)` function. Call it from `main.c` before `free_stack`.
Add `bench.c` to Makefile SRC. No other files need touching for this phase.

<phase_requirements>
## Phase Requirements

| ID | Description | Research Support |
|----|-------------|-----------------|
| BENCH-01 | `--bench` output includes disorder percentage formatted as `XX.XX%` | Float-to-fixed-decimal output via write() — see Code Examples section |
| BENCH-02 | `--bench` output includes strategy name based on actual strategy used | Strategy name resolution table documented below; requires `len` and `disorder` context for adaptive |
| BENCH-03 | `--bench` output includes total operation count (sum of all 11 op counters) | Already computed in main.c lines 73-74; move computation into print_bench |
| BENCH-04 | `--bench` output includes individual counts for all 11 operations | All 11 fields exist in t_ops; must be printed on two lines per required format |
| BENCH-05 | `print_bench` logic extracted into `bench.c` helper to keep `main` under 25 lines | main.c currently 57 lines; bench block is lines 71-79; extraction is the primary structural goal |
</phase_requirements>

---

## Standard Stack

### Core
| Component | Location | Purpose | Notes |
|-----------|----------|---------|-------|
| `write(2, str, len)` | POSIX | All string output | No printf — project constraint |
| `ft_putnbr_fd(int n, int fd)` | `utils.c` | Print integers to any fd | Already available |
| `t_ops *ops` | `push_swap.h` | Holds all 11 op counters | Passed to print_bench |
| `float disorder` | computed in `main.c` before sorting | Input to disorder formatting | 0.0 to 1.0 range |
| `int strategy` | returned by `flag_checker` | 1=simple, 2=medium, 3=complex, 4=adaptive | Input to strategy name |
| `int len` | `get_stack_length(&stack_a)` | Stack size before sorting | Needed for adaptive name resolution |

### New File
| File | Purpose | Added To |
|------|---------|---------|
| `bench.c` | Contains `print_bench` function | Makefile SRC variable |

### Alternatives Considered
| Instead of | Could Use | Tradeoff |
|------------|-----------|----------|
| New `bench.c` | Inline in `main.c` | Inline would push main.c over 25 lines — not allowed |
| Custom float formatter | `printf("%.2f", ...)` | printf not allowed per project constraints |

**Makefile addition:**
```
SRC = main.c parser.c parser_utils.c parser_utils2.c \
      ft_split.c ft_strncmp.c p_functions.c s_functions.c \
      r_functions.c rr_functions.c ra_rra_handlers.c \
      n_square.c n_square_utils.c utils.c print_stack.c radix.c k_sort.c \
      bench.c
```

---

## Architecture Patterns

### Required Output Format

The evaluator expects exactly this format on **stderr (fd 2)**:

```
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n√n)
[bench] total_ops:  13
[bench] sa:  0  sb:  0  ss:  0  pa:  5  pb:  5
[bench] ra:  2  rb:  1  rr:  0  rra:  0  rrb:  0  rrr:  0
```

Source: ISSUES.md PRIORITY 2 section (project documentation, HIGH confidence).

### Recommended File Structure Addition

```
push_swap/
├── bench.c          # NEW — print_bench function (this phase)
├── main.c           # modified: add bench.c call, remove inline bench block
├── Makefile         # modified: add bench.c to SRC
└── push_swap.h      # modified: add print_bench prototype
```

### Pattern 1: Float to XX.XX% Without printf

The project bans `printf`. The disorder float (0.0–1.0) must be printed as `XX.XX%`.

```c
/* Source: derived from existing ft_putnbr_fd pattern in utils.c */
static void  print_percent(float val, int fd)
{
    int  pct_int;
    int  pct_dec;

    val = val * 100.0f;
    pct_int = (int)val;
    pct_dec = (int)((val - pct_int) * 100.0f + 0.5f);
    if (pct_dec >= 100)
    {
        pct_int++;
        pct_dec = 0;
    }
    ft_putnbr_fd(pct_int, fd);
    write(fd, ".", 1);
    if (pct_dec < 10)
        write(fd, "0", 1);
    ft_putnbr_fd(pct_dec, fd);
    write(fd, "%", 1);
}
```

Key detail: leading zero for single-digit decimal (e.g. `40.05%` not `40.5%`).

### Pattern 2: Strategy Name Resolution

The `strategy` integer from `flag_checker` combined with `disorder` and `len` determines
the actual strategy that ran.

```c
/* Source: ISSUES.md PRIORITY 2 + main.c strategy dispatch logic */
static char  *get_strategy_name(int strategy, float disorder, int len)
{
    if (len <= 5)
        return ("Adaptive / O(n^2)");
    if (strategy == 1)
        return ("Simple / O(n^2)");
    if (strategy == 2)
        return ("Medium / O(n*sqrt(n))");
    if (strategy == 3)
        return ("Complex / O(n log n)");
    /* strategy == 4 (adaptive) */
    if (disorder < 0.2f)
        return ("Adaptive / O(n^2)");
    if (disorder < 0.5f)
        return ("Adaptive / O(n*sqrt(n))");
    return ("Adaptive / O(n log n)");
}
```

The thresholds (0.2f, 0.5f) MUST match main.c lines 61-66 exactly. These are the
branch conditions already in production.

### Pattern 3: print_bench Signature

```c
/* Source: analysis of main.c + ISSUES.md requirements */
void  print_bench(t_ops *ops, float disorder, int strategy, int len);
```

Called from `main.c` before `free_stack`. Needs `len` captured before sorting (since
sorting empties/reorders the stack).

### Pattern 4: Two-Line Op Count Format

Line 4: `[bench] sa: N  sb: N  ss: N  pa: N  pb: N`
Line 5: `[bench] ra: N  rb: N  rr: N  rra: N  rrb: N  rrr: N`

Helper to print one label+value pair:

```c
/* Source: derived from existing write+ft_putnbr_fd pattern */
static void  print_op(char *label, int count, int fd)
{
    write(fd, label, ft_strlen(label));
    write(fd, " ", 1);
    ft_putnbr_fd(count, fd);
    write(fd, "  ", 2);
}
```

`ft_strlen` is already prototyped in `push_swap.h` and implemented in the project.

### Anti-Patterns to Avoid

- **Using printf**: Not allowed. All output via `write()` + `ft_putnbr_fd`.
- **Reading strategy name from a string enum**: Use a function returning a string
  literal — avoids heap allocation and free complexity.
- **Putting print logic in main.c**: Violates the 25-line limit requirement (BENCH-05).
- **Computing total_moves in main.c**: Move it into `print_bench` — keeps main.c
  smaller and avoids a local variable that pushes the line count.
- **Capturing `len` after sorting**: `sort_n_square`, `sort_radix`, etc. consume
  stack_b. `len` must be captured before the sort dispatch block.

---

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Integer output | Custom itoa | `ft_putnbr_fd` already in utils.c | It exists and works |
| String length | Custom loop | `ft_strlen` already in push_swap.h | Already prototyped and implemented |
| Float formatting | Complex float library | Simple int arithmetic on the float | Only 2 decimal places needed; trivial with int casts |

---

## Common Pitfalls

### Pitfall 1: Adaptive Strategy Name Mismatch

**What goes wrong:** The name printed does not match what actually ran because the
adaptive thresholds in `get_strategy_name` differ from main.c's dispatch thresholds.

**Why it happens:** The thresholds are duplicated — once in main.c, once in bench.c.
If one is changed the other may not be updated.

**How to avoid:** Copy the exact float literals from main.c lines 61-66:
`disorder < 0.2f` and `disorder >= 0.5f`. Mirror the `len <= 5` short-circuit too.

**Warning signs:** `./push_swap --bench 5 3 1 4 2` shows `Adaptive / O(n log n)` but
a 5-element input always uses sort_5 (O(n^2) path).

### Pitfall 2: Decimal Formatting Edge Cases

**What goes wrong:** `40.00%` prints as `40.0%` or `40%` (missing trailing zero or
missing leading zero on decimal).

**Why it happens:** Single-digit decimal part needs a leading `"0"` write before
`ft_putnbr_fd`. `100.00%` case needs carry handling when rounding pushes decimal to 100.

**How to avoid:** Add `if (pct_dec < 10) write(fd, "0", 1)` before `ft_putnbr_fd`.
Add rounding carry check (`if pct_dec >= 100 { pct_int++; pct_dec = 0; }`).

**Warning signs:** Disorder of exactly 0.5 (50.00%) printing as `50.0%`.

### Pitfall 3: len Captured After Sorting

**What goes wrong:** `len` passed to `print_bench` is 0 or wrong because it was
read from the stack after operations have been applied.

**Why it happens:** `get_stack_length` is called after the sort dispatch block.

**How to avoid:** Capture `len = get_stack_length(&stack_a)` at the same point as the
existing `len` variable in main.c — before the sort dispatch.

**Warning signs:** Adaptive strategy always resolves to `O(n^2)` because `len <= 5`
is always true.

### Pitfall 4: Output Goes to stdout Instead of stderr

**What goes wrong:** Benchmark output appears on stdout (fd 1), which could interfere
with checker tools that read stdout.

**Why it happens:** `write(1, ...)` instead of `write(2, ...)`.

**How to avoid:** All `write` calls in `print_bench` use fd 2 (stderr).

**Warning signs:** `./push_swap --bench 5 3 1 4 2 | wc -l` counts benchmark lines.

### Pitfall 5: main.c Still Exceeds 25 Lines After Extraction

**What goes wrong:** After moving the bench block to bench.c, main.c still exceeds 25
lines because the sort dispatch block was not extracted.

**Why it happens:** main.c currently has 57 lines. Removing only lines 71-79 (bench
block) leaves ~48 lines — still over 25. The sort dispatch block (lines 51-70) must
also be extracted into a `sort_dispatch` helper, OR accepted as a norminette fix for
a later session.

**How to avoid:** Phase 1 only needs `main.c` to remain under 25 lines per BENCH-05.
The current main.c is 57 lines. To meet BENCH-05, the sort dispatch must also be
extracted. Extract `sort_dispatch(t_stack *a, t_stack *b, t_ops *ops, int len, int
strategy, float disorder)` into main.c as a static function — this is within scope
since BENCH-05 requires the 25-line constraint.

**Warning signs:** Line count of main.c after changes still above 25.

---

## Code Examples

### Full print_bench Structure

```c
/* bench.c — Source: ISSUES.md format spec + existing write/ft_putnbr_fd pattern */
#include "push_swap.h"

static void  print_percent(float disorder, int fd)
{
    int  pct_int;
    int  pct_dec;
    float  pct;

    pct = disorder * 100.0f;
    pct_int = (int)pct;
    pct_dec = (int)((pct - (float)pct_int) * 100.0f + 0.5f);
    if (pct_dec >= 100)
    {
        pct_int++;
        pct_dec = 0;
    }
    ft_putnbr_fd(pct_int, fd);
    write(fd, ".", 1);
    if (pct_dec < 10)
        write(fd, "0", 1);
    ft_putnbr_fd(pct_dec, fd);
    write(fd, "%\n", 2);
}

static char  *resolve_strategy(int strategy, float disorder, int len)
{
    if (len <= 5)
        return ("Adaptive / O(n^2)");
    if (strategy == 1)
        return ("Simple / O(n^2)");
    if (strategy == 2)
        return ("Medium / O(n*sqrt(n))");
    if (strategy == 3)
        return ("Complex / O(n log n)");
    if (disorder < 0.2f)
        return ("Adaptive / O(n^2)");
    if (disorder < 0.5f)
        return ("Adaptive / O(n*sqrt(n))");
    return ("Adaptive / O(n log n)");
}

void  print_bench(t_ops *ops, float disorder, int strategy, int len)
{
    int  total;
    char *name;

    total = ops->sa + ops->sb + ops->ss + ops->pa + ops->pb
        + ops->ra + ops->rb + ops->rr + ops->rra + ops->rrb + ops->rrr;
    name = resolve_strategy(strategy, disorder, len);
    write(2, "[bench] disorder:  ", 19);
    print_percent(disorder, 2);
    write(2, "[bench] strategy:  ", 19);
    write(2, name, ft_strlen(name));
    write(2, "\n", 1);
    write(2, "[bench] total_ops:  ", 20);
    ft_putnbr_fd(total, 2);
    write(2, "\n", 1);
    write(2, "[bench] sa:  ", 13);
    ft_putnbr_fd(ops->sa, 2);
    write(2, "  sb:  ", 7);
    ft_putnbr_fd(ops->sb, 2);
    /* ... etc for all 11 ops on two lines ... */
}
```

Note: The above is illustrative. The actual implementation will need to split into
static helpers to respect the 25-line-per-function norminette rule.

### main.c After Extraction

```c
/* main.c — after Phase 1 changes */
int  main(int argc, char **argv)
{
    t_stack  stack_a;
    t_stack  stack_b;
    t_ops    *ops;
    int      strategy;
    int      bench;
    int      len;
    int      start_idx;
    float    disorder;

    if (argc < 2)
        return (0);
    stack_a.top = NULL;
    stack_b.top = NULL;
    start_idx = flag_checker(argc, argv, &strategy, &bench);
    parse_arguments(argc, argv, &stack_a, start_idx);
    assign_indexes(&stack_a);
    init_ops(&ops);  /* static helper already in main.c */
    if (!ops)
    {
        free_stack(&stack_a);
        return (1);
    }
    disorder = compute_disorder(&stack_a);
    len = get_stack_length(&stack_a);
    sort_dispatch(&stack_a, &stack_b, ops, len, strategy, disorder);
    if (bench == 1)
        print_bench(ops, disorder, strategy, len);
    free_stack(&stack_a);
    free(ops);
    return (0);
}
```

This is approximately 28 lines including braces. The `init_ops` static helper and
`sort_dispatch` static helper absorb the body. Fine-tuning during implementation may
be needed to land exactly at or under 25.

---

## State of the Art

| Old Approach | Current Approach | Notes |
|--------------|------------------|-------|
| `"Benchmark: Total moves = N"` on stderr | 5-line format with disorder%, strategy, total, per-op counts | Required by 42 evaluator |
| Inline in main.c | Extracted to bench.c | Required by BENCH-05 |

---

## Open Questions

1. **Exact character counts for write() labels**
   - What we know: Format strings like `"[bench] disorder:  "` require exact byte counts
   - What's unclear: Whether evaluator is sensitive to exact spacing (single space vs double space after colon)
   - Recommendation: Match ISSUES.md format exactly — two spaces after colon, as shown

2. **25-line limit for main.c — requires sort_dispatch extraction**
   - What we know: main.c is currently 57 lines; removing the bench block alone still leaves ~48 lines
   - What's unclear: Whether BENCH-05 acceptance test only counts bench extraction or also requires the dispatch extraction
   - Recommendation: Extract `sort_dispatch` as a static function in main.c to guarantee the 25-line ceiling is met; this is minimal work and keeps Phase 1 self-contained

3. **print_bench line count with 11 ops**
   - What we know: Printing all 11 op names+values inline will exceed 25 lines per function
   - What's unclear: Best split point
   - Recommendation: Split into `print_ops_line1(ops, fd)` (sa/sb/ss/pa/pb) and `print_ops_line2(ops, fd)` (ra/rb/rr/rra/rrb/rrr) as static helpers in bench.c

---

## Validation Architecture

No automated test framework is configured in this project (`pytest.ini`, `jest.config.*`,
`vitest.config.*`, test directories — none found). This is a C project compiled with `make`.

### Test Framework

| Property | Value |
|----------|-------|
| Framework | None — manual shell testing only |
| Config file | None |
| Quick run command | `make && ./push_swap --bench 5 3 1 4 2` |
| Full suite command | `make re && ./push_swap --bench 5 3 1 4 2 && ./push_swap --bench 1 && ./push_swap --bench 100 $(seq 100 -1 1)` |

### Phase Requirements -> Test Map

| Req ID | Behavior | Test Type | Automated Command | Notes |
|--------|----------|-----------|-------------------|-------|
| BENCH-01 | disorder prints as `XX.XX%` | smoke | `./push_swap --bench 5 3 1 4 2 2>&1 \| grep disorder` | manual verify format |
| BENCH-02 | strategy name matches actual strategy used | smoke | `./push_swap --simple --bench 5 3 1 4 2 2>&1 \| grep strategy` | manual verify name |
| BENCH-03 | total_ops is sum of all 11 counters | smoke | `./push_swap --bench 5 3 1 4 2 2>&1 \| grep total_ops` | manual cross-check |
| BENCH-04 | all 11 op names present with counts | smoke | `./push_swap --bench 5 3 1 4 2 2>&1` | count lines, check labels |
| BENCH-05 | main.c under 25 lines | static | `wc -l main.c` | target: output < 26 |

### Sampling Rate

- **Per task commit:** `make && ./push_swap --bench 5 3 1 4 2`
- **Per wave merge:** `make re && ./push_swap --bench 5 3 1 4 2 && wc -l main.c`
- **Phase gate:** All 5 success criteria visually confirmed before marking phase complete

### Wave 0 Gaps

- [ ] `bench.c` — does not yet exist; must be created in Wave 1
- [ ] `print_bench` prototype in `push_swap.h` — not yet present

*(No test framework to install — project uses manual shell verification)*

---

## Sources

### Primary (HIGH confidence)

- `ISSUES.md` PRIORITY 2 — exact required output format, strategy name strings,
  disorder formatting algorithm
- `main.c` lines 61-70 — exact float thresholds (0.2f, 0.5f) for adaptive strategy
  dispatch — must be mirrored in bench.c
- `push_swap.h` — complete t_ops struct (all 11 fields confirmed)
- `utils.c` — ft_putnbr_fd implementation (write-based integer output)
- `Makefile` — current SRC list (bench.c is absent, confirming it must be added)

### Secondary (MEDIUM confidence)

- `ISSUES.md` PRIORITY 1 — 25-line function limit and norminette constraints
  (confirmed as project rule; norminette binary not run, constraint taken from docs)

### Tertiary (LOW confidence)

- Strategy name strings (`O(n√n)` vs `O(n*sqrt(n))`) — ISSUES.md shows both forms in
  different places; planner should verify which Unicode/ASCII form the evaluator expects

---

## Metadata

**Confidence breakdown:**
- Standard stack: HIGH — all components confirmed present in codebase
- Architecture: HIGH — output format specified verbatim in ISSUES.md
- Pitfalls: HIGH — derived from direct code analysis of main.c and existing patterns

**Research date:** 2026-04-20
**Valid until:** 2026-05-20 (stable C project, no external dependencies to go stale)
