# Changelog

All notable changes to OpenBench are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [0.1.0] — 2026-05-20

Initial public snapshot of **OpenBench**, formerly *LHIG*
(Legacy Hardware Integration Gateway). This release establishes the
legal, social, and documentation baseline before feature work begins
in 0.2.0.

### Added

- GNU Affero General Public License v3 or later
  (AGPL-3.0-or-later) at the repository root. Chosen for its strong
  copyleft semantics (any modified version exposed to users over a
  network must publish source) while remaining compatible with the
  open62541 OPC UA stack (MPL-2.0).
- SPDX-License-Identifier headers on every C++/Python source file.
- `NOTICE` and `THIRD-PARTY-NOTICES.md` attributing open62541 and the
  build/test toolchain, with an explicit AGPL/MPL compatibility note.
- `AUTHORS` file naming the original author and maintainer.
- `CITATION.cff` for academic-style citation; GitHub renders this as
  a "Cite this repository" widget on the sidebar.
- `CONTRIBUTING.md` documenting build, tests, coding style, branch
  naming, commit conventions, and the inbound = outbound
  AGPL-3.0-or-later contribution policy.
- `CODE_OF_CONDUCT.md` based on Contributor Covenant 2.1.
- `README.md` with positioning, 30-second pitch, persona section,
  honest competitor comparison, quickstart, architecture diagram, and
  roadmap.

### Existing functionality (carried forward from the prototype)

- C++17 daemon connecting to a legacy device over TCP and republishing
  a single `Voltage` node on an OPC UA server
  (`opc.tcp://0.0.0.0:4840`), built on the open62541 stack.
- State-aware reconnect loop with graceful disconnect handling so the
  OPC UA server stays up even when the device is unreachable.
- Python simulator (`sim/legacy_device.py`) speaking an SCPI-flavoured
  TCP protocol (`READ:VOLT`, `READ:CURRENT`, `READ:STATUS`,
  `READ:SENSORS`, `TRIGGER:ERROR`).
- pytest + asyncua benchmark suite asserting connectivity, sub-100 ms
  read latency, and >200 reads/sec throughput.
- Three-stage CI (`.github/workflows/ci.yml`): pre-commit + cppcheck
  static analysis, AddressSanitizer build, docker-compose integration
  benchmark.

### Coming in 0.2.0 — "Lab-first MVP"

- YAML config schema (devices, transports, commands, parse rules,
  sink mappings) replacing all hardcoded behavior.
- MQTT and REST output sinks alongside the existing OPC UA sink.
- Realistic Keysight 34461A simulator speaking real SCPI commands.
- End-to-end Grafana demo bundle under `examples/`.

### Coming in 0.3.0 — "Credible product"

- USBTMC, serial RS-232/RS-485, and Modbus TCP/RTU transports.
- Prometheus metrics endpoint as an additional sink.
- OPC UA authentication (username/password; x509 stretch).
- Plugin architecture so community-contributed transports and sinks
  can be added without forking the core.

[0.1.0]: https://github.com/KaranSinghDev/Legacy-Hardware-Integration-Gateway/releases/tag/v0.1.0
