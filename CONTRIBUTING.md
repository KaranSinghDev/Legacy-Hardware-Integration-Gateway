# Contributing to OpenBench

Thanks for your interest in OpenBench. This document covers how to get
a working build, the coding conventions we enforce, and the licensing
terms under which contributions are accepted.

## Quick start

1. Clone the repository, including submodules:

   ```
   git clone --recurse-submodules \
     https://github.com/KaranSinghDev/Legacy-Hardware-Integration-Gateway.git
   cd Legacy-Hardware-Integration-Gateway
   ```

2. Build and run with Docker (recommended for first-time contributors):

   ```
   docker compose up --build
   ```

3. Or build natively (requires CMake ≥ 3.10 and a C++17 compiler):

   ```
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

4. Install pre-commit hooks before making any changes:

   ```
   pip install pre-commit
   pre-commit install
   ```

## Running tests

The integration benchmark suite spins the whole stack up via
docker-compose, then runs `pytest` against the live OPC UA endpoint:

```
pip install -r benchmark/requirements.txt
docker compose up --detach
pytest -v -s benchmark/test_gateway.py
docker compose down -v
```

## Coding style

| Language | Tool | Configuration |
|----------|------|---------------|
| C++ (.cpp, .hpp) | `clang-format` | `-style=LLVM` |
| Python (.py) | `black` + `flake8` | `--max-line-length=88` |
| CMake | manual | 2-space indent, lowercase commands |

All three are enforced by `pre-commit` locally and by the CI workflow
in `.github/workflows/ci.yml`. PRs that fail formatting checks will be
blocked.

## Branch naming

- `feat/<short-name>` — new feature
- `fix/<short-name>` — bug fix
- `docs/<short-name>` — documentation only
- `chore/<short-name>` — tooling, deps, or other maintenance
- `refactor/<short-name>` — internal restructuring with no behavior change

## Commit messages

Conventional-style prefixes are encouraged: `feat:`, `fix:`, `docs:`,
`chore:`, `refactor:`, `test:`, `ci:`. Write the subject in imperative
mood, ~70 characters or less. The body, when present, should explain
*why* the change is needed — not what changed (the diff shows that).

## Licensing of contributions

OpenBench is licensed under the **GNU Affero General Public License
v3 or later (AGPL-3.0-or-later)**. By submitting a pull request you
certify that:

1. The contribution is your own original work, or you have permission
   from the rights holder to submit it under AGPL-3.0-or-later.
2. You agree your contribution will be distributed under
   AGPL-3.0-or-later, matching the rest of the project (inbound =
   outbound).
3. Every new source file you create includes the standard AGPL SPDX
   header at the top. For C/C++:

   ```
   // SPDX-License-Identifier: AGPL-3.0-or-later
   // Copyright (c) <year> <your name>
   //
   // This program is free software: you can redistribute it and/or modify
   // it under the terms of the GNU Affero General Public License as
   // published by the Free Software Foundation, either version 3 of the
   // License, or (at your option) any later version.
   //
   // This program is distributed in the hope that it will be useful, but
   // WITHOUT ANY WARRANTY; without even the implied warranty of
   // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   // Affero General Public License for more details.
   //
   // You should have received a copy of the License along with this
   // program. If not, see <https://www.gnu.org/licenses/>.
   ```

   For Python, swap `//` for `#`.

No separate Contributor License Agreement (CLA) is required; the
inbound = outbound AGPL-3.0-or-later license is implicit.

## Reporting bugs

Open a GitHub issue with:

- What you tried (commands, configuration, environment).
- What you expected to happen.
- What actually happened (full logs and any error messages).
- The version you reproduced against (commit SHA or release tag).

## Discussion before large changes

For non-trivial changes — new transports, new sinks, breaking config
changes, license-touching work — open a GitHub Discussion or draft PR
first so we can align on direction before significant code is written.

## Code of Conduct

Participation in this project is governed by the project
[Code of Conduct](CODE_OF_CONDUCT.md). By contributing, you agree to
abide by its terms.
