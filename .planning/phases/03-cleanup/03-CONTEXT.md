# Phase 3: Cleanup - Context

**Gathered:** 2026-04-20
**Status:** Ready for planning

<domain>
## Phase Boundary

Prune dead code and fix the Makefile so `compute_disorder` links correctly. Three targeted deletions: one Makefile line, one function body from `utils.c`, one prototype from `push_swap.h`. No new behavior.

</domain>

<decisions>
## Implementation Decisions

### Makefile
- Add `compute_disorder.c` to the `SRC` variable in Makefile
- No other Makefile changes needed — all other files already present

### utils.c
- Remove the entire `compute_disorder` function (lines 31–57) — this is the broken/non-norminette duplicate
- Keep `ft_memset` and `ft_putnbr_fd` — they are canonical and used everywhere
- No other changes to `utils.c`

### push_swap.h
- Remove the `find_min_position` prototype (line 77) — unused, stale
- No other header changes

### Order of operations
- Remove `compute_disorder` from `utils.c` FIRST to eliminate linker conflict, THEN add `compute_disorder.c` to Makefile SRC
- This prevents a duplicate symbol error if both are compiled simultaneously

### Claude's Discretion
- Whitespace cleanup adjacent to removed code (leave clean, minimal blank lines)
- Whether to run `make` as a verification step after changes

</decisions>

<specifics>
## Specific Ideas

No specific requirements — pure deletion with pre-specified targets.

</specifics>

<code_context>
## Existing Code Insights

### Reusable Assets
- `compute_disorder.c`: Canonical implementation already exists and is correct — just needs to be wired into SRC
- `utils.c`: Contains `ft_memset` and `ft_putnbr_fd` — both must be preserved; only the `compute_disorder` duplicate removed

### Established Patterns
- Makefile SRC: Space-separated `.c` filenames, continuation lines with `\`
- No tests or scaffolding needed — `make` success is the verification

### Integration Points
- `compute_disorder.c` references `t_stack` and `t_node` from `push_swap.h` — header already includes these types
- `find_min_position` prototype in `push_swap.h` has no corresponding implementation; safe to delete

</code_context>

<deferred>
## Deferred Ideas

None — discussion stayed within phase scope.

</deferred>

---

*Phase: 03-cleanup*
*Context gathered: 2026-04-20*
