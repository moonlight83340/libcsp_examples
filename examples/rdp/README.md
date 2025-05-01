# 📡 CSP Example with RDP over SocketCAN

This example demonstrates a reliable client-server communication using **CSP with RDP (Reliable Datagram Protocol)** over a **virtual CAN interface (vcan0)**.

---

## 🔧 Requirements

Make sure you have:

- `libcsp` compiled with CAN support (`can_socketcan`)
- A Linux kernel with the `vcan` module
- A POSIX-compatible environment

---

## 🖧 Set up `vcan0` interface

Before running the programs, set up the virtual CAN interface:

```bash
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
```

---

## 🧪 Running

### 1. Run the server:

```bash
./csp_can_node2_rdp
```

- Uses CSP address `2`
- Listens on port `10`
- Accepts only **RDP** connections (`CSP_SO_RDPREQ`)

### 2. Run the client:

```bash
./csp_can_node1_rdp
```

- Uses CSP address `1`
- Connects to server with **RDP** (`CSP_O_RDP`)
- Sends `Hello world A`, `Hello world B`, etc.
- Awaits an **ACK** from the server

---

## ✅ What this shows

- **Reliable connection** using RDP
- **Automatic ACK and retransmission handling**
- Clear **client/server** logic
- Communication over a **simulated CAN bus (vcan)**

---

## 📁 File Structure

```text
csp_can_node1_rdp.c   → sends messages using RDP
csp_can_node2_rdp.c   → receives messages and replies with ACKs
```

---

## 📘 References

- [CSP on GitHub](https://github.com/libcsp/libcsp)
- [Setup RDP on libcsp] (https://github.com/libcsp/libcsp/issues/596)
- [Linux SocketCAN](https://www.kernel.org/doc/html/latest/networking/can.html)
