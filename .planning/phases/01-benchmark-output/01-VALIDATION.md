---
phase: 1
slug: benchmark-output
status: draft
nyquist_compliant: false
wave_0_complete: false
created: 2026-04-20
---

# Phase 1 — Validation Strategy

> Per-phase validation contract for feedback sampling during execution.

---

## Test Infrastructure

| Property | Value |
|----------|-------|
| **Framework** | None — manual shell testing only (C project, no test framework) |
| **Config file** | none |
| **Quick run command** | `make && ./push_swap --bench 5 3 1 4 2` |
| **Full suite command** | `make re && ./push_swap --bench 5 3 1 4 2 && ./push_swap --bench 1 && ./push_swap --bench 100 $(seq 100 -1 1)` |
| **Estimated runtime** | ~5 seconds |

---

## Sampling Rate

- **After every task commit:** Run `make && ./push_swap --bench 5 3 1 4 2`
- **After every plan wave:** Run `make re && ./push_swap --bench 5 3 1 4 2 && wc -l main.c`
- **Before `/gsd:verify-work`:** Full suite must be green (all 5 success criteria visually confirmed)
- **Max feedback latency:** ~5 seconds

---

## Per-Task Verification Map

| Task ID | Plan | Wave | Requirement | Test Type | Automated Command | File Exists | Status |
|---------|------|------|-------------|-----------|-------------------|-------------|--------|
| 1-01-01 | 01 | 0 | BENCH-01,05 | static | `ls bench.c && grep print_bench push_swap.h` | ❌ W0 | ⬜ pending |
| 1-01-02 | 01 | 1 | BENCH-01 | smoke | `./push_swap --bench 5 3 1 4 2 2>&1 \| grep disorder` | ✅ | ⬜ pending |
| 1-01-03 | 01 | 1 | BENCH-02 | smoke | `./push_swap --bench 5 3 1 4 2 2>&1 \| grep strategy` | ✅ | ⬜ pending |
| 1-01-04 | 01 | 1 | BENCH-03 | smoke | `./push_swap --bench 5 3 1 4 2 2>&1 \| grep total_ops` | ✅ | ⬜ pending |
| 1-01-05 | 01 | 1 | BENCH-04 | smoke | `./push_swap --bench 5 3 1 4 2 2>&1` | ✅ | ⬜ pending |
| 1-01-06 | 01 | 2 | BENCH-05 | static | `wc -l main.c` | ✅ | ⬜ pending |

*Status: ⬜ pending · ✅ green · ❌ red · ⚠️ flaky*

---

## Wave 0 Requirements

- [ ] `bench.c` — does not yet exist; must be created before Wave 1 tasks run
- [ ] `print_bench` prototype in `push_swap.h` — not yet present

*No test framework to install — project uses manual shell verification.*

---

## Manual-Only Verifications

| Behavior | Requirement | Why Manual | Test Instructions |
|----------|-------------|------------|-------------------|
| disorder prints as `XX.XX%` | BENCH-01 | Float formatting, visual check | Run `./push_swap --bench 5 3 1 4 2 2>&1 \| grep disorder` and confirm `XX.XX%` format |
| strategy name matches actual | BENCH-02 | String content, visual check | Run with `--simple` flag and `--bench`, confirm strategy name matches dispatch used |
| total_ops is sum of all 11 counters | BENCH-03 | Arithmetic cross-check | Run `./push_swap --bench 5 3 1 4 2 2>&1`, manually sum individual op counts and verify total |
| all 11 op labels present | BENCH-04 | Label counting, visual check | Count all op lines in output, verify all 11 are present |
| main.c under 25 lines | BENCH-05 | Line count | `wc -l main.c` — must output ≤ 25 |

---

## Validation Sign-Off

- [ ] All tasks have `<automated>` verify or Wave 0 dependencies
- [ ] Sampling continuity: no 3 consecutive tasks without automated verify
- [ ] Wave 0 covers all MISSING references
- [ ] No watch-mode flags
- [ ] Feedback latency < 5s
- [ ] `nyquist_compliant: true` set in frontmatter

**Approval:** pending
