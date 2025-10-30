Process Utilities: Error Convention, Truncation Policy, Test Plan
Error Convention
All Process utilities return 0 for success and -1 for error (such as invalid argument or buffer too small).

String Truncation Policy
In process_make, name and state are truncated if too long:

name: maximum 63 characters + null byte

state: maximum 15 characters + null byte

Mock Insert Policy
process_fill_mock adds multiple Process items to a PList.

If error occurs, valid items before error are kept (partial insert), no rollback.

If the PList pointer is NULL, function returns -1, no action.

Supported States
Supported state codes include:

Short forms: "R", "S", "Z"

Long forms: "running", "sleeping", "zombie"

Manual Test Plan
A. Create and Validate Process

Create three Process items:

PID=1234, name="bash", state="R", mem_kb=2048 (valid)

PID=1, name that is very long, state="S", mem_kb=100 (valid, name should be truncated)

PID=42, name="init", state="zombie", mem_kb=0 (valid)

Use process_is_valid for each.

Use process_format_brief with buffers of exact size, and smaller, to check error return.

B. Mock Fill and PList Access

Call plist_init, then process_fill_mock.

Check 6 items: verify PID, name, state, mem_kb (one name near length limit).

Use plist_get on first and last item for verification.

C. Robustness and Errors

Run process_fill_mock(NULL) — should return error.

Trigger allocation error (for example, force very large capacity in PList): only records added before error are present.

Run process_fill_mock twice on the same PList: no crash.

Validation Criteria
process.h is self-contained, well documented, no unnecessary includes.

Utility functions respect field length limits.

Manual tests run without crash, proper output, errors detected.