# Phase 2: Count-Only Flag - Research

**Researched:** 2026-04-20
**Domain:** C flag parsing, struct field addition, conditional write() suppression, integer output
**Confidence:** HIGH

<phase_requirements>
## Phase Requirements

| ID | Description | Research Support |
|----|-------------|-----------------|
| COUNT-01 | `t_ops` struct has `count_only` integer field in `push_swap.h` | `t_ops` is defined in `push_swap.h` lines 33-47; `bench` field was added last in Phase 1 — `count_only` follows the same pattern |
| COUNT-02 | `flag_checker` in `parser.c` parses `--count-only` and sets `ops->count_only = 1` | `flag_checker` currently takes `int *bench` as 4th param; same extension mechanism applies for `count_only` |
| COUNT-03 | All 11 op functions skip `write()` when `ops->count_only` is set | Every op function already has `if (!ops->bench) write(...)` guards — `count_only` adds a second condition to the same guard |
| COUNT-04 | Program prints total op count to stdout after sorting when `--count-only` is given | `ft_putnbr_fd` exists in `utils.c`; `print_bench` already computes total; `run()` in `main.c` is the callsite |
</phase_requirements>

---

## Summary

Phase 2 adds `--count-only` mode: when the flag is present the program sorts silently and then prints a single integer (total operation count) to stdout. No operation strings (`sa`, `pb`, `ra`, etc.) appear on stdout. The flag is a peer of `--bench` — same parsing mechanism, same write-guard pattern.

The codebase is already structured for exactly this extension. Phase 1 added `ops->bench` and established the pattern: every one of the 11 op functions guards its `write()` with `if (!ops->bench)`. Phase 2 repeats that pattern for `count_only` — the guard becomes `if (!ops->bench && !ops->count_only)`. The only genuinely new behaviour is printing the integer total to fd 1 at the end of `run()`.

**Primary recommendation:** Mirror Phase 1's `bench` implementation exactly — add `count_only` as the next field in `t_ops`, extend `flag_checker`'s parameter list identically, add one extra condition to the existing write guards, and emit the total via `ft_putnbr_fd` + a trailing `"\n"` to fd 1.

---

## Standard Stack

### Core (this is a C project, no external libraries)

| Component | Location | Purpose | Notes |
|-----------|----------|---------|-------|
| `t_ops` struct | `push_swap.h` lines 33-47 | Holds per-operation counters + mode flags | Add `count_only` field after `bench` |
| `flag_checker` | `parser.c` lines 57-82 | Parses `--` flags, returns start index for numbers | Extend with `--count-only` branch |
| `ft_putnbr_fd` | `utils.c` lines 59-73 | Writes integer to arbitrary fd | Use with fd 1 to print total |
| `run()` | `main.c` lines 46-74 | Orchestrates parse, sort, output | Add `count_only` wiring and output call |

### No new files or libraries needed

All required primitives (`ft_putnbr_fd`, `write`, `ft_strncmp`) already exist. No new `.c` file is required for this phase.

---

## Architecture Patterns

### Existing Pattern: Mode Flag in t_ops

Phase 1 established this exact pattern for `bench`. Replicate it verbatim.

**Step 1 — Struct field** (`push_swap.h`):
```c
// Source: push_swap.h lines 33-47 (current state after Phase 1)
typedef struct s_ops
{
    int     pa;
    int     pb;
    int     ra;
    int     rb;
    int     rr;
    int     rra;
    int     rrb;
    int     rrr;
    int     sa;
    int     sb;
    int     ss;
    int     bench;
    int     count_only;   // ADD: last field, zeroed by ft_memset in init_ops
}           t_ops;
```

**Step 2 — flag_checker signature** (`parser.c`):

Current signature:
```c
int flag_checker(int argc, char **argv, int *strategy, int *bench);
```

Extended signature:
```c
int flag_checker(int argc, char **argv, int *strategy, int *bench, int *count_only);
```

Add a branch inside the while loop (same style as `--bench`):
```c
else if (!ft_strncmp(argv[i], "--count-only", 13))
    *count_only = 1;
```

**Step 3 — Update prototype** in `push_swap.h`:
```c
int flag_checker(int argc, char **argv, int *strategy, int *bench, int *count_only);
```

**Step 4 — Wire in run()** (`main.c`):
```c
// Existing locals (bench already declared):
int     count_only;
// ...
start_idx = flag_checker(argc, argv, &strategy, &bench, &count_only);
// ...
ops->count_only = count_only;
// After sort_dispatch, before free_stack:
if (count_only)
{
    total = ops->pa + ops->pb + ops->ra + ops->rb + ops->rr
        + ops->rra + ops->rrb + ops->rrr + ops->sa + ops->sb + ops->ss;
    ft_putnbr_fd(total, 1);
    write(1, "\n", 1);
}
```

**Step 5 — Write guard in all 11 op functions**:

Current guard (example from `s_functions.c`):
```c
if (!ops->bench)
    write(1, "sa\n", 3);
```

Updated guard:
```c
if (!ops->bench && !ops->count_only)
    write(1, "sa\n", 3);
```

Apply this change in all three op files:
- `s_functions.c` — `sa`, `sb`, `ss` (3 ops)
- `p_functions.c` — `pa`, `pb` (2 ops)
- `r_functions.c` — `ra`, `rb`, `rr` (3 ops)
- `rr_functions.c` — `rra`, `rrb`, `rrr` (3 ops)

### Files Touched

| File | Change |
|------|--------|
| `push_swap.h` | Add `count_only` field to `t_ops`; update `flag_checker` prototype |
| `parser.c` | Add `int *count_only` param + `--count-only` branch in `flag_checker` |
| `main.c` | Declare `count_only`, pass to `flag_checker`, set `ops->count_only`, print total |
| `s_functions.c` | Update 3 write guards |
| `p_functions.c` | Update 2 write guards |
| `r_functions.c` | Update 3 write guards |
| `rr_functions.c` | Update 3 write guards |

Total: 7 files, all small diffs.

### Anti-Patterns to Avoid

- **Separate suppression variable in each op function:** The ops pointer is already available everywhere. Do not add a local or global flag — use `ops->count_only` directly.
- **Printing total before sorting:** `sort_dispatch` must complete first; total is only meaningful afterwards.
- **Using printf:** This is a 42 project — only `write` and `ft_putnbr_fd` are safe. `printf` is forbidden.
- **Computing total in a new function for this phase:** The total computation is a single expression already used in `print_bench`. Inline it in `run()` or extract only if `run()` line count demands it.
- **Adding `count_only` before `bench` in the struct:** Keep `bench` in its current position; add `count_only` after it. The `ft_memset` zeroing in `init_ops` handles both automatically.

---

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Print integer to stdout | Custom digit extraction | `ft_putnbr_fd(total, 1)` | Already in codebase, tested |
| Detect flag string | Manual character loop | `ft_strncmp(argv[i], "--count-only", 13)` | Already the established pattern |

---

## Common Pitfalls

### Pitfall 1: Wrong string length in ft_strncmp call
**What goes wrong:** `"--count-only"` is 12 characters. Passing `n=12` allows a prefix match that would also match `"--count-only-extra"`. The convention in this codebase (see lines 67-76 of `parser.c`) is to pass `strlen + 1` to require the null terminator to match.
**How to avoid:** Pass `13` as the third argument: `ft_strncmp(argv[i], "--count-only", 13)`.
**Warning signs:** A flag like `--count-only-foo` is incorrectly accepted.

### Pitfall 2: Forgetting to initialise count_only in flag_checker
**What goes wrong:** `count_only` is a stack variable in `run()`; if `flag_checker` does not set `*count_only = 0` at the start, it holds garbage when the flag is absent.
**How to avoid:** Set `*count_only = 0` at the top of `flag_checker`, alongside `*bench = 0`.

### Pitfall 3: main.c line count
**What goes wrong:** `run()` currently has 17 locals + statements. Adding `count_only` declaration, total computation, `ft_putnbr_fd` call, and `write` call could push the function over the 42 Norminette 25-line limit.
**How to avoid:** Count lines carefully. If needed, extract total computation + output into a `print_count(t_ops *ops)` helper (analogous to `print_bench`). Given current `run()` is 29 lines (line 46-74), watch this closely — extraction may be required.
**Warning signs:** `cc -Wall -Wextra -Werror` succeeds but norminette reports function length violation.

### Pitfall 4: --count-only and --bench used together
**What goes wrong:** If both flags are given, `ops->bench` suppresses op writes but also triggers `print_bench` to stderr; `ops->count_only` would additionally print the total to stdout. This dual-output is not necessarily wrong, but it should be a conscious decision.
**How to avoid:** The requirements do not mention interaction between the two flags. Implement them independently (both can be set simultaneously). The write guard `if (!ops->bench && !ops->count_only)` handles both cleanly.

### Pitfall 5: Printing total when already sorted (0 ops)
**What goes wrong:** If the input is already sorted, `sort_dispatch` is skipped (`is_sorted` returns 1). Total will be 0. This is correct behaviour — the program should still print `0`.
**How to avoid:** Print unconditionally when `count_only` is set, regardless of whether sorting happened.

---

## Code Examples

### Total computation (from bench.c line 79-80, for reference)
```c
// Source: bench.c lines 79-80
total = ops->pa + ops->pb + ops->ra + ops->rb + ops->rr
    + ops->rra + ops->rrb + ops->rrr + ops->sa + ops->sb + ops->ss;
```

### Writing integer + newline to stdout
```c
// Pattern: ft_putnbr_fd writes to any fd; fd 1 = stdout
ft_putnbr_fd(total, 1);
write(1, "\n", 1);
```

### Guard condition after extension
```c
// Before (Phase 1 pattern):
if (!ops->bench)
    write(1, "sa\n", 3);

// After (Phase 2 extension):
if (!ops->bench && !ops->count_only)
    write(1, "sa\n", 3);
```

---

## State of the Art

| Old Approach | Current Approach | Impact |
|--------------|------------------|--------|
| No mode flags | `ops->bench` added in Phase 1 | Established the pattern this phase follows |
| `main()` over 25 lines | Refactored to `run()` + `sort_dispatch()` helpers | Phase 2 must respect this; may need `print_count()` helper |

---

## Open Questions

1. **run() line budget**
   - What we know: `run()` is currently 29 lines (lines 46-74 in main.c). Adding count_only wiring + output adds approximately 5-6 lines.
   - What's unclear: Whether Norminette enforcement is active for this project right now (Phase 3 mentions a "norminette session").
   - Recommendation: Planner should count run() lines after change and extract `print_count(t_ops *ops)` to `bench.c` or a new `count.c` if the function exceeds 25 lines. Safest path: always extract.

2. **Interaction with --bench flag**
   - What we know: Requirements do not specify combined behaviour.
   - What's unclear: Should `--count-only --bench` be an error, or silently coexist?
   - Recommendation: Let them coexist silently. The write guard handles suppression; both outputs are on different fds (stderr for bench, stdout for count).

---

## Validation Architecture

> `workflow.nyquist_validation` is absent from `.planning/config.json` — treat as enabled.

### Test Framework

| Property | Value |
|----------|-------|
| Framework | None detected — this is a C project with a manual shell tester |
| Config file | `tester.sh` (manual test script at project root) |
| Quick run command | `make re && ./push_swap --count-only 5 3 1 4 2` |
| Full suite command | `make re && bash tester.sh` |

### Phase Requirements → Test Map

| Req ID | Behavior | Test Type | Automated Command | File Exists? |
|--------|----------|-----------|-------------------|-------------|
| COUNT-01 | `t_ops` has `count_only` field | compile-time | `make re 2>&1` (fails if field missing) | ❌ Wave 0 |
| COUNT-02 | `flag_checker` parses `--count-only` | smoke | `make re && ./push_swap --count-only 5 3 1 4 2` | ❌ Wave 0 |
| COUNT-03 | No op strings on stdout with `--count-only` | smoke | `make re && ./push_swap --count-only 5 3 1 4 2 \| grep -E '^(sa\|sb\|pa\|pb\|ra\|rb\|rr\|rra\|rrb\|rrr\|ss)$'` — must return empty | ❌ Wave 0 |
| COUNT-04 | Single integer printed to stdout | smoke | `make re && ./push_swap --count-only 5 3 1 4 2 \| wc -l` — must be `1`; value must be numeric | ❌ Wave 0 |

### Sampling Rate

- **Per task commit:** `make re && ./push_swap --count-only 5 3 1 4 2`
- **Per wave merge:** Full smoke suite: COUNT-01 through COUNT-04 commands above
- **Phase gate:** All 4 smoke checks pass before `/gsd:verify-work`

### Wave 0 Gaps

- [ ] Manual smoke commands above — no automated test file exists; must be run by hand or added to `tester.sh`
- [ ] `make re` clean build — confirms COUNT-01 (struct compiles)

*(No formal test framework is present; all validation is compile + manual run)*

---

## Sources

### Primary (HIGH confidence)

- Direct source read: `push_swap.h` — confirms `t_ops` structure, `bench` field position, `flag_checker` prototype
- Direct source read: `parser.c` — confirms `flag_checker` implementation pattern (lines 57-82)
- Direct source read: `main.c` — confirms `run()` structure, `bench` wiring, callsite for output
- Direct source read: `s_functions.c`, `p_functions.c`, `r_functions.c`, `rr_functions.c` — confirms all 11 write guards use `if (!ops->bench)` pattern
- Direct source read: `utils.c` — confirms `ft_putnbr_fd(int n, int fd)` signature and behaviour
- Direct source read: `bench.c` — confirms total computation expression (lines 79-80)

### Secondary (MEDIUM confidence)

- `.planning/STATE.md` Decisions section — confirms "add count_only field to t_ops struct — minimal change; all op functions already receive ops pointer" was a pre-roadmap decision

---

## Metadata

**Confidence breakdown:**
- Standard stack: HIGH — entire codebase read directly; no external dependencies
- Architecture: HIGH — pattern is an exact mirror of Phase 1's `bench` implementation, which is complete and visible in source
- Pitfalls: HIGH — derived from direct reading of the code; string-length and line-count pitfalls are concrete

**Research date:** 2026-04-20
**Valid until:** Indefinite — pure C project with no external dependencies; only changes if source files are modified
