# CSP Examples

This repository contains a collection of examples demonstrating the use of the [libcsp](https://github.com/libcsp/libcsp) (CubeSat Space Protocol) library in different configurations and communication setups.

Each example focuses on a specific interface or feature of CSP, such as KISS over USART, CAN, ZMQ, or loopback, and is designed to be simple, minimal, and easy to understand.

## Contents

```
libcsp_examples/
│
├── .github/ # GitHub workflows and CI/CD configurations
├── examples/
│   ├── can/ # Example using SocketCAN interface with virtual CAN (`vcan`).
│   ├── usart/ # Example using KISS protocol over virtual USART (e.g., `socat`) on Linux.
│   ├── rdp/ # Example showing usage of rdp with csp. (The example is using can interface)
│   └── rdp_crc32/ # Example showing usage of rdp & crc32 with csp. (The example is using can interface)
├── libcsp # Sub-module git for libcsp
├── options/ # The repository contain only a file to explain different option that can be used with csp.
├── utils/ # Utils for examples (csp_posix_helper)
└──
```

## Requirements

- A Linux system with development tools (e.g., `gcc`, `make`, `cmake`)
- `libcsp` installed or available as a submodule
- For some examples:
  - [`socat`](https://linux.die.net/man/1/socat) (for USART/KISS)
  - Virtual CAN support (`modprobe vcan`)
  - Python 3 (for some test clients/servers if provided)
