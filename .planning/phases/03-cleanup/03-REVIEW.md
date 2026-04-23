---
phase: 03-cleanup
reviewed: 2026-04-23T00:00:00Z
depth: standard
files_reviewed: 3
files_reviewed_list:
  - utils.c
  - push_swap.h
  - Makefile
findings:
  critical: 0
  warning: 2
  info: 3
  total: 5
status: issues_found
---

# Phase 03: Code Review Report

**Reviewed:** 2026-04-23
**Depth:** standard
**Files Reviewed:** 3
**Status:** issues_found

## Summary

Three files were reviewed as part of the phase-03 cleanup: `utils.c` (duplicate `compute_disorder` removed), `push_swap.h` (stale `find_min_position` prototype removed), and `Makefile` (`compute_disorder.c` added to `SRC`). All Makefile source files exist on disk and the build graph is correct. No critical issues were found. Two warnings and three informational items remain.

---

## Warnings

### WR-01: Redundant `#include <stddef.h>` in `utils.c`

**File:** `utils.c:13`
**Issue:** `utils.c` explicitly includes `<stddef.h>` to get `size_t`, but it then immediately includes `"push_swap.h"` (line 14), which already includes `<stddef.h>` at line 17 of the header. The standalone `#include <stddef.h>` in `utils.c` is redundant. Under 42-norm strict compilation (`-Wall -Wextra -Werror`) this does not produce a warning, but it creates a false impression that the file depends on something `push_swap.h` does not already provide. If `push_swap.h` later changes its include order, this becomes a latent ordering trap.
**Fix:** Remove the direct `<stddef.h>` include from `utils.c`; rely solely on the transitive include through `push_swap.h`:
```c
/* Remove this line: */
#include <stddef.h>
#include "push_swap.h"   /* already transitively includes stddef.h */
```

---

### WR-02: Mismatched parameter name in `compute_disorder` prototype vs. definition

**File:** `push_swap.h:95`
**Issue:** The prototype declares `float compute_disorder(t_stack *stack_a);` but the definition in `compute_disorder.c:25` uses `t_stack *stack`. The parameter name mismatch is legal in C but confusing: the prototype suggests the argument is specifically stack A, while the function itself is generic. More concretely, the prototype was left with the old name (`stack_a`) from when the function lived in `utils.c` and the prototype was not updated. This is an artifact of the cleanup that was not fully finished.
**Fix:** Align the parameter name in the prototype with the definition:
```c
/* push_swap.h line 95 — change to: */
float	compute_disorder(t_stack *stack);
```

---

## Info

### IN-01: Commented-out algorithm pseudocode in `compute_disorder.c`

**File:** `compute_disorder.c:15-23`
**Issue:** Nine lines of pseudocode comment (lines 15–23) describe the algorithm in plain English. This was acceptable as a design note during development but is dead documentation in a submitted project. 42-norm style guidelines discourage block comments that are not 42-header format; reviewers may flag this.
**Fix:** Remove the pseudocode comment block entirely. The implementation is straightforward enough to be self-documenting.

---

### IN-02: Inconsistent prototype alignment in `push_swap.h` (lines 95–100)

**File:** `push_swap.h:95-100`
**Issue:** The last six prototypes added to the header (`compute_disorder`, `ft_putnbr_fd`, `sort_5`, `find_min_index`, `print_bench`, `print_count`) use a single tab or inconsistent tab width for alignment, breaking the visual column alignment used by the rest of the prototypes. For example:
- Line 95: `float compute_disorder(...)` — no tab before return type, no alignment tab
- Line 96: `void\tft_putnbr_fd(...)` — one tab
- Lines 51–93: `int\t\t\t\tft_atoi(...)` — multiple tabs to align names at column ~25

Under 42-norm, all prototypes in a header should align the function name at a consistent column. These new entries are misaligned relative to the existing block.
**Fix:** Reformat lines 95–100 to match the tab-alignment column used by the rest of the file:
```c
float				compute_disorder(t_stack *stack);
void				ft_putnbr_fd(int n, int fd);
void				sort_5(t_stack *a, t_stack *b, t_ops *ops);
int					find_min_index(t_stack *a);
void				print_bench(t_ops *ops, float disorder, int strategy, int len);
void				print_count(t_ops *ops);
```

---

### IN-03: Makefile has no explicit dependency on headers

**File:** `Makefile:9`
**Issue:** The Makefile compiles `.c` files to `.o` objects via the implicit rule but does not declare `push_swap.h` as a dependency of the object files. If `push_swap.h` is modified, `make` will not recompile stale objects, requiring a manual `make re`. This is a common 42 project footgun.
**Fix:** Add the header as a prerequisite:
```makefile
$(OBJ): push_swap.h
```
Place this line after the `OBJ` variable definition. This forces full recompilation whenever the header changes.

---

_Reviewed: 2026-04-23_
_Reviewer: Claude (gsd-code-reviewer)_
_Depth: standard_
