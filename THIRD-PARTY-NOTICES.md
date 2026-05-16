# Third-Party Notices

OpenBench is built on top of the following open-source projects. Their
licenses and attributions are reproduced here so that downstream users
and redistributors can satisfy their obligations.

OpenBench itself is licensed under the **GNU Affero General Public
License, version 3 or later (AGPL-3.0-or-later)**. See the `LICENSE`
file at the root of this repository for the full text.

---

## open62541

- **Project:** open62541 — Open source implementation of OPC UA (IEC 62541)
- **Homepage:** https://open62541.org/
- **Repository:** https://github.com/open62541/open62541
- **License:** Mozilla Public License Version 2.0 (MPL-2.0)
- **Source:** included as a git submodule under `third_party/open62541`

**License compatibility note.** MPL-2.0 is explicitly GPL-compatible
(including with AGPL-3.0) — see Mozilla's MPL-in-GPL guidelines at
<https://www.mozilla.org/en-US/MPL/2.0/combining-mpl-and-gpl/> and the
Free Software Foundation announcement at
<https://www.fsf.org/blogs/licensing/mpl-2.0-release>. When OpenBench
(AGPL-3.0-or-later) is combined with open62541 (MPL-2.0), the
program as a whole is licensed under AGPL-3.0-or-later, while the
MPL-licensed files inside `third_party/open62541` remain available
under MPL-2.0.

Some open62541 plugins, examples, and helper files are dual-licensed
under MPL-2.0 and CC0-1.0 (public-domain dedication). See
`third_party/open62541/LICENSE` and individual source-file headers in
that subtree for per-file licensing.

OpenBench links against open62541 as a static library. No
modifications are made to open62541 source files by OpenBench; any
patches required upstream are submitted to the open62541 project
directly.

---

## Build & development dependencies

The following tools are required to build or develop OpenBench but
are **not** bundled in the runtime binary:

- **CMake** (≥ 3.10) — BSD-3-Clause — https://cmake.org/
- **GCC / Clang** with C++17 support — GPL/LLVM — system-provided
- **clang-format** (LLVM) — Apache 2.0 with LLVM Exceptions — used by
  the pre-commit hook for C++ formatting
- **pre-commit** — MIT — https://pre-commit.com/
- **black** — MIT — https://github.com/psf/black
- **flake8** — MIT — https://github.com/PyCQA/flake8

## Test & simulation dependencies (development only)

The benchmark suite and the legacy-device simulator depend on the
following Python packages, declared in `benchmark/requirements.txt`.
These run only during development and CI; they are not part of the
shipped OpenBench binary.

- **pytest** — MIT
- **pytest-asyncio** — Apache-2.0
- **asyncua** — LGPL-3.0

---

If you redistribute OpenBench, ensure that the corresponding license
texts for any libraries you bundle are also included.
