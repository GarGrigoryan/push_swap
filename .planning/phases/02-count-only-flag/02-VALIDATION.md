---
phase: 2
slug: count-only-flag
status: draft
nyquist_compliant: false
wave_0_complete: false
created: 2026-04-20
---

# Phase 2 — Validation Strategy

> Per-phase validation contract for feedback sampling during execution.

---

## Test Infrastructure

| Property | Value |
|----------|-------|
| **Framework** | shell/bash (no test framework — direct binary invocation) |
| **Config file** | none |
| **Quick run command** | `make && ./push_swap --count-only 5 3 1 4 2` |
| **Full suite command** | `make && ./push_swap --count-only 5 3 1 4 2 && ./push_swap --count-only 5 3 1 4 2 2>/dev/null | wc -l` |
| **Estimated runtime** | ~2 seconds |

---

## Sampling Rate

- **After every task commit:** Run `make && ./push_swap --count-only 5 3 1 4 2`
- **After every plan wave:** Run full suite command above
- **Before `/gsd:verify-work`:** Full suite must be green
- **Max feedback latency:** 5 seconds

---

## Per-Task Verification Map

| Task ID | Plan | Wave | Requirement | Test Type | Automated Command | File Exists | Status |
|---------|------|------|-------------|-----------|-------------------|-------------|--------|
| 2-01-01 | 01 | 1 | COUNT-03 | compile | `make 2>&1` | ✅ | ⬜ pending |
| 2-01-02 | 01 | 1 | COUNT-01 | functional | `./push_swap --count-only 5 3 1 4 2` | ✅ | ⬜ pending |
| 2-01-03 | 01 | 1 | COUNT-02 | functional | `./push_swap --count-only 5 3 1 4 2 2>/dev/null \| grep -cE '^(sa\|sb\|ss\|pa\|pb\|ra\|rb\|rr\|rra\|rrb\|rrr)$'` | ✅ | ⬜ pending |
| 2-01-04 | 01 | 1 | COUNT-01 | functional | `./push_swap --count-only 5 3 1 4 2 2>/dev/null \| wc -l` (expect 1) | ✅ | ⬜ pending |

*Status: ⬜ pending · ✅ green · ❌ red · ⚠️ flaky*

---

## Wave 0 Requirements

Existing infrastructure covers all phase requirements. No test framework installation needed — all verification is via binary invocation.

---

## Manual-Only Verifications

| Behavior | Requirement | Why Manual | Test Instructions |
|----------|-------------|------------|-------------------|
| Header struct field visible | COUNT-03 | compile check only | `grep count_only push_swap.h` |

---

## Validation Sign-Off

- [ ] All tasks have `<automated>` verify or Wave 0 dependencies
- [ ] Sampling continuity: no 3 consecutive tasks without automated verify
- [ ] Wave 0 covers all MISSING references
- [ ] No watch-mode flags
- [ ] Feedback latency < 5s
- [ ] `nyquist_compliant: true` set in frontmatter

**Approval:** pending
