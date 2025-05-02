# CSP Example : Client / Server Communication over vcan0

This example demonstrates a simple client/server interaction using **CSP (CubeSat Space Protocol)** over a virtual CAN interface (`vcan0`), implemented with **libcsp**.

The communication uses a **connection-oriented** model:
- The **client** (node1) connects to the **server** (node2).
- It sends a message with an incrementing character (e.g., "Hello world A").
- The **server** replies with an acknowledgment message that includes the number of packets received so far.

---

## 🛰 Protocol

This project uses the [libcsp](https://github.com/libcsp/libcsp) library, the C implementation of **CubeSat Space Protocol (CSP)**, originally designed for CubeSats and embedded systems communication.

CSP supports various transports (CAN, UART, I2C, UDP, etc.) and includes routing, connections, reliability (via RDP), and more.

In this example, communication is done over **CAN** using the Linux **SocketCAN** subsystem (`vcan0`).

---

## 💡 Requirements

- Linux system with `vcan` module
- `libcsp` built with `can_socketcan` support
- SocketCAN tools (`ip`, `can-utils`)
- `gcc` or any C compiler

---

## 🔧 Setup vcan0 Interface

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```

## 🧩 Node Descriptions

### 🟢 Node 1: Client

**File:** `csp_can_node1.c`

- Connects to the server at `SERVER_ADDRESS` (Node 2)
- Sends a `Hello world <char>` message every 1 second
- Waits for a reply from the server
- Prints the received response

### 🔵 Node 2: Server

**File:** `csp_can_node2.c`

- Binds and listens on `SERVER_PORT`
- Accepts incoming connections from clients
- Reads incoming packets
- Sends back a reply in the format: `"ACK <count>"`, where `<count>` is the number of received messages so far
