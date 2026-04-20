# Phase 3: Cleanup - Research

**Researched:** 2026-04-20
**Domain:** C build system (Makefile) and C source cleanup (duplicate symbol removal, stale prototype removal)
**Confidence:** HIGH

<user_constraints>
## User Constraints (from CONTEXT.md)

### Locked Decisions

- Add `compute_disorder.c` to the `SRC` variable in Makefile — no other Makefile changes needed
- Remove the entire `compute_disorder` function (lines 31–57) from `utils.c` — this is the broken/non-norminette duplicate; keep `ft_memset` and `ft_putnbr_fd`
- Remove the `find_min_position` prototype (line 77) from `push_swap.h` — unused, stale
- Order of operations: remove `compute_disorder` from `utils.c` FIRST, then add `compute_disorder.c` to Makefile SRC

### Claude's Discretion

- Whitespace cleanup adjacent to removed code (leave clean, minimal blank lines)
- Whether to run `make` as a verification step after changes

### Deferred Ideas (OUT OF SCOPE)

None — discussion stayed within phase scope.
</user_constraints>

<phase_requirements>
## Phase Requirements

| ID | Description | Research Support |
|----|-------------|-----------------|
| CLEAN-01 | `compute_disorder.c` added to Makefile `SRC` variable | Verified: file exists at project root, Makefile SRC does not include it; pattern is space-separated `.c` names with `\` continuation |
| CLEAN-02 | Duplicate/broken `compute_disorder` function removed from `utils.c` | Verified: function occupies lines 31–57 of `utils.c`; canonical implementation is in `compute_disorder.c` (norminette-compliant) |
| CLEAN-03 | Unused `find_min_position` prototype removed from `push_swap.h` | Verified: prototype on line 77; no corresponding `.c` implementation exists anywhere in the project |
</phase_requirements>

---

## Summary

Phase 3 is purely destructive: three targeted deletions and one line addition. No new logic is introduced. The primary risk is compilation failure from a duplicate symbol (`compute_disorder` defined in both `utils.c` and `compute_disorder.c`) if the Makefile is updated before the duplicate is removed. The CONTEXT.md locks in a safe order of operations to prevent this.

The canonical `compute_disorder.c` already exists at the project root with a norminette-compliant implementation. The broken copy in `utils.c` (lines 31–57) uses `double` locals, misaligned indentation, and inconsistent style — none of that matters since it is simply being deleted.

The `find_min_position` prototype in `push_swap.h` line 77 has no corresponding `.c` implementation. It is safe to delete; removing it eliminates a misleading declaration that could cause confusion during evaluation.

**Primary recommendation:** Delete the `compute_disorder` block from `utils.c` first, then add `compute_disorder.c` to the Makefile SRC line, then remove the `find_min_position` prototype from `push_swap.h`. Run `make re` to confirm clean compilation.

---

## Standard Stack

### Core

| Tool | Version | Purpose | Why Standard |
|------|---------|---------|--------------|
| cc (gcc) | system | C compiler | Required by project Makefile |
| make | system | Build orchestration | Project already uses GNU make |

No additional libraries or packages needed — this phase only edits existing files.

**Verification command:**
```bash
make re
```

---

## Architecture Patterns

### Makefile SRC Pattern

The project Makefile uses a space-separated SRC variable with backslash line continuation. The existing pattern (from `Makefile` lines 4–8):

```makefile
SRC         = main.c parser.c parser_utils.c parser_utils2.c \
              ft_split.c ft_strncmp.c p_functions.c s_functions.c \
              r_functions.c rr_functions.c ra_rra_handlers.c \
              n_square.c n_square_utils.c utils.c print_stack.c radix.c k_sort.c \
              bench.c
```

`compute_disorder.c` must be appended to this list. The cleanest placement is at the end of the final SRC continuation line, after `bench.c`. The last line has no trailing `\`, so `compute_disorder.c` should follow `bench.c` on the same line or as a new continuation line.

### Exact Source Locations (verified by direct file read)

**`utils.c` — lines to delete:**
- Lines 31–57: the entire `compute_disorder` function from `float compute_disorder(t_stack *stack_a){` through the closing `}` and the trailing blank line

```c
// utils.c lines 31-57 (DELETE THIS BLOCK)
float compute_disorder(t_stack *stack_a){
	t_node *curr;
	t_node *cmp;

	double mistakes;
	double total_pairs;

	if(!stack_a || !stack_a->top || !stack_a->top->next)
		return(0.0f);

	mistakes = 0;
	total_pairs= 0;
	curr = stack_a->top;

		while(curr)
		{
			cmp = curr->next;
			while(cmp){
				total_pairs++;
				if(curr->num > cmp->num)
					mistakes++;
				cmp = cmp->next;
			}
			curr = curr->next;
		}
		return ((float)(mistakes / total_pairs));
}
```

After deletion, `ft_putnbr_fd` (currently starting at line 59) becomes the second function in the file, immediately following `ft_memset`. One blank line between them is appropriate.

**`push_swap.h` — line to delete:**
- Line 77: `int					find_min_position(int min, int length);`

Context (surrounding lines 76–78 as read):
```c
int					find_min_ops(int min, int length);
int					find_min_position(int min, int length);   // DELETE THIS LINE
int					handle_min_ra(t_stack *a, t_stack *b, int min_ops,
```

Deleting line 77 leaves `find_min_ops` and `handle_min_ra` as adjacent declarations, which is correct — no extra blank lines needed.

### Anti-Patterns to Avoid

- **Adding `compute_disorder.c` to Makefile before removing the duplicate:** causes duplicate symbol linker error (`multiple definition of 'compute_disorder'`). The locked order of operations prevents this.
- **Leaving trailing blank lines after deletion in `utils.c`:** the removed block (lines 31–57) includes a blank line at line 57 vicinity. Leave exactly one blank line between `ft_memset` and `ft_putnbr_fd`.
- **Removing `compute_disorder` prototype from `push_swap.h`:** do NOT remove it — it is at line 96 (`float compute_disorder(t_stack *stack_a);`) and is the valid declaration pointing at `compute_disorder.c`. Only remove `find_min_position` (line 77).

---

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Verifying compilation success | Custom build check script | `make re` | Already in Makefile; tests full clean rebuild |
| Finding duplicate symbols | Manual search | `nm push_swap \| grep compute_disorder` or compiler error | Linker will catch duplicate at compile time |

---

## Common Pitfalls

### Pitfall 1: Wrong deletion order causes duplicate symbol error
**What goes wrong:** If `compute_disorder.c` is added to Makefile SRC while `utils.c` still defines the function, the linker emits `multiple definition of 'compute_disorder'` and compilation fails.
**Why it happens:** Both translation units define the same symbol at global scope.
**How to avoid:** Delete the `utils.c` function body first, verify it is gone, then update Makefile.
**Warning signs:** Linker error mentioning `compute_disorder` during `make`.

### Pitfall 2: Removing the wrong `compute_disorder` prototype from the header
**What goes wrong:** `push_swap.h` line 96 (`float compute_disorder(t_stack *stack_a);`) is the VALID prototype pointing to `compute_disorder.c`. Deleting it would cause an implicit declaration warning/error.
**Why it happens:** There are two references to `compute_disorder` in the header vicinity — the valid prototype at line 96 and the stale prototype should not exist (only `find_min_position` at line 77 is stale).
**How to avoid:** Only delete line 77 (`find_min_position`). Leave line 96 (`compute_disorder`) untouched.
**Warning signs:** Compiler warning about implicit function declaration for `compute_disorder` after changes.

### Pitfall 3: Off-by-one in blank line cleanup leaves extra whitespace
**What goes wrong:** After removing lines 31–57 from `utils.c`, there may be zero or two blank lines between `ft_memset` and `ft_putnbr_fd`, depending on the exact deletion boundary.
**Why it happens:** The deleted block may or may not include its trailing blank line.
**How to avoid:** After deletion, confirm exactly one blank line separates the two remaining functions (Claude's discretion per CONTEXT.md).

---

## Code Examples

### utils.c — Expected State After Cleanup
```c
// Source: utils.c (verified current state)

#include <stddef.h>
#include "push_swap.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	num;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	c = (num % 10) + '0';
	write(fd, &c, 1);
}
```

### Makefile SRC — Expected State After Cleanup (CLEAN-01)
```makefile
SRC         = main.c parser.c parser_utils.c parser_utils2.c \
              ft_split.c ft_strncmp.c p_functions.c s_functions.c \
              r_functions.c rr_functions.c ra_rra_handlers.c \
              n_square.c n_square_utils.c utils.c print_stack.c radix.c k_sort.c \
              bench.c compute_disorder.c
```

### push_swap.h — Expected State After Cleanup (CLEAN-03)
Lines 76–81 become:
```c
void				print_stack(t_stack *stack);
int					find_min_ops(int min, int length);
int					handle_min_ra(t_stack *a, t_stack *b, int min_ops,
					t_ops *ops);
int					handle_min_rra(t_stack *a, t_stack *b, int min_ops,
					t_ops *s_ops);
```
(Line 77 `find_min_position` is gone; everything else shifts up by one line.)

---

## State of the Art

| Old State | New State | When Changed | Impact |
|-----------|-----------|--------------|--------|
| `compute_disorder` duplicated in `utils.c` and `compute_disorder.c` | Only in `compute_disorder.c` | Phase 3 | Linker no longer sees duplicate symbol; `make` succeeds |
| `compute_disorder.c` not in Makefile SRC | Added to SRC | Phase 3 | Function available at link time for `bench.c` callers |
| `find_min_position` prototype in header with no implementation | Removed | Phase 3 | Header accurately reflects available API |

---

## Open Questions

1. **Blank line count after deletion in `utils.c`**
   - What we know: Lines 31–57 are the duplicate function; lines 30 and 58 are blank or code
   - What's unclear: Whether line 30 is a blank separator or part of the header block
   - Recommendation: After deletion, read the resulting file and normalise to one blank line between functions (Claude's discretion, per CONTEXT.md)

---

## Validation Architecture

### Test Framework

| Property | Value |
|----------|-------|
| Framework | Shell script (tester.sh) — no unit test framework |
| Config file | none |
| Quick run command | `make re 2>&1` |
| Full suite command | `bash /home/nomad/tmp/push_swap/tester.sh` |

### Phase Requirements to Test Map

| Req ID | Behavior | Test Type | Automated Command | File Exists? |
|--------|----------|-----------|-------------------|-------------|
| CLEAN-01 | `compute_disorder.c` in Makefile SRC; `make` succeeds | smoke | `make re 2>&1 && echo BUILD_OK` | N/A — Makefile edit |
| CLEAN-02 | No `compute_disorder` definition in `utils.c` | smoke | `grep -c 'compute_disorder' /home/nomad/tmp/push_swap/utils.c` (expect 0) | N/A — source edit |
| CLEAN-03 | No `find_min_position` prototype in header | smoke | `grep -c 'find_min_position' /home/nomad/tmp/push_swap/push_swap.h` (expect 0) | N/A — header edit |

### Sampling Rate

- **Per task commit:** `make re 2>&1 | tail -5`
- **Per wave merge:** `make re 2>&1 && bash /home/nomad/tmp/push_swap/tester.sh`
- **Phase gate:** Full suite green before `/gsd:verify-work`

### Wave 0 Gaps

None — existing infrastructure (`make`, `tester.sh`) covers all phase requirements. No new test files needed.

---

## Sources

### Primary (HIGH confidence)

- Direct file read: `/home/nomad/tmp/push_swap/utils.c` — confirmed `compute_disorder` occupies lines 31–57
- Direct file read: `/home/nomad/tmp/push_swap/push_swap.h` — confirmed `find_min_position` at line 77, `compute_disorder` prototype at line 96
- Direct file read: `/home/nomad/tmp/push_swap/Makefile` — confirmed `compute_disorder.c` absent from SRC
- Direct file read: `/home/nomad/tmp/push_swap/compute_disorder.c` — confirmed canonical norminette-compliant implementation exists
- Direct file read: `.planning/phases/03-cleanup/03-CONTEXT.md` — locked decisions and order of operations

### Secondary (MEDIUM confidence)

- None required — all findings verified directly from source.

### Tertiary (LOW confidence)

- None.

---

## Metadata

**Confidence breakdown:**
- Standard stack: HIGH — no new dependencies; only existing tools (`cc`, `make`)
- Architecture: HIGH — all changes verified against actual file contents with line numbers
- Pitfalls: HIGH — duplicate symbol risk confirmed by direct inspection of both definitions

**Research date:** 2026-04-20
**Valid until:** Until source files are modified — these findings reference exact line numbers in current file state
