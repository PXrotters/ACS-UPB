# PCom Homework #4

This repository contains starter scripts for the PCom HTTP client assignment.

## Checker

Dependencies:

- Python >= 3.7;
- [`pexpect`](https://pexpect.readthedocs.io/en/stable/) (third party Python package);

It is highly recommended to use a VirtualEnv:
```sh
python3 -mvenv .venv
# Note: you need to source activate each time you start a new terminal
source .venv/bin/activate
```

Afterwards, install `pexpect` using PIP:
```sh
python3 -mpip install pexpect
```

### Usage

Invoke the checker on your client's compiled executable:

```sh
# !!! don't forget to source .venv/bin/activate !!!
# first, read the tool's internal help:
python3 checker/checker.py --help 
# run the checker using default settings:
python3 checker/checker.py ../path/to/client
# Hint: supply a custom username:password (make sure to use something unique)
python3 checker/checker.py --user 'myuser-1337:hunter2' ../path/to/client
```

> **Warning**: the checker has default credentials (`test:test123`) as constants
> inside the source code. You may want to change them to avoid always specifying
> the `--user user:pass` argument at each invocation.

Also, the server is shared between all students and never forgets an user
account or its stored books (for the duration of the assignment, at least).
Thus, you might wish to occasionally create a new user for having a clean slate.

Alternately, use `--script delete_all` if you have a functioning implementation
for `get_books` and `delete_book` (and the common login part, ofc!).

Also make sure to check out [the source code](./checker/checker.py) for the
actual details about the script being tested.

> <span style="color: #A33">**Warning**: The checker is just an instrument used by
our team to automate the verification process. It should not be regarded as the
single source of truth for assessing the correctness of a solution.
It may also contain bugs (we also manually validate your programs when
a script fails), though forum reports and PRs are welcome!</span>

