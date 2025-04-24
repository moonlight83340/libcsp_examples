# 🌐 CSP Socket Options

CSP socket options allow you to configure additional parameters for connection management and security. These options can be set when establishing CSP connections to enable features like **RDP (Reliable Datagram Protocol)**, **HMAC** (Hash-based Message Authentication Codes), and **CRC32** for data integrity.

---

## ⚙️ CSP Socket Options

CSP socket options are used to configure parameters for socket communication, either when establishing connections or during packet transmission/reception. These options are applied via the connection or sending functions.

### General Socket Options

- **`CSP_SO_NONE`**: 
  No options. This is the default option if no other option is specified.

- **`CSP_SO_RDPREQ`**: 
  **Require RDP** (Reliable Datagram Protocol). This option ensures reliable communication by adding retransmission and acknowledgment mechanisms.

- **`CSP_SO_RDPPROHIB`**: 
  **Prohibit RDP**. Use this option if you do not need retransmissions or ACKs (typically for non-critical communications).

- **`CSP_SO_HMACREQ`**: 
  **Require HMAC** (Hash-based Message Authentication Code). This option ensures the integrity of messages exchanged by adding a validation code to the messages.

- **`CSP_SO_HMACPROHIB`**: 
  **Prohibit HMAC**. Use this option if you do not need HMAC authentication on your packets.

- **`CSP_SO_CRC32REQ`**: 
  **Require CRC32** for packet integrity checking. This option ensures that each packet is accompanied by a CRC32 checksum to detect transmission errors.

- **`CSP_SO_CRC32PROHIB`**: 
  **Prohibit CRC32**. Use this option if you do not want CRC32 checks on your packets.

- **`CSP_SO_CONN_LESS`**: 
  Enable **connectionless mode**. This mode allows you to send packets without establishing a prior connection, useful for quick communications where reliability is not a priority.

- **`CSP_SO_SAME`**: 
  **Apply the same options as the incoming packet**. This option is mainly used with the function `csp_sendto_reply()` to carry forward the options from the incoming packet to the reply.

---

## 🚀 CSP Connection Options

These options are used when establishing a CSP connection.

- **`CSP_O_NONE`**:
  No connection-specific options (default option).

- **`CSP_O_RDP`**: 
  **Enable RDP** on the connection. This option ensures that the connection uses RDP for packet retransmission with reliability control.

- **`CSP_O_NORDP`**: 
  **Disable RDP** for the connection. Use this option when you want fast connections without retransmission or acknowledgment.

- **`CSP_O_HMAC`**: 
  **Enable HMAC** for the connection. This ensures that each packet exchanged is validated using an HMAC for integrity and authenticity.

- **`CSP_O_NOHMAC`**: 
  **Disable HMAC** for the connection. Use this option if you do not want HMAC authentication on the packets.

- **`CSP_O_CRC32`**: 
  **Enable CRC32** for the connection. This option enables the integrity check of the packets through CRC32 calculation.

- **`CSP_O_NOCRC32`**: 
  **Disable CRC32** for the connection. If you do not need CRC32 checks for packet integrity, this option can be used.

- **`CSP_O_SAME`**: 
  Apply the same options as the incoming connection.

---

## 🎯 Practical Usage

Socket and connection options are used flexibly depending on the application's needs. For example:

### Example 1: Reliable Connection (RDP)  with CRC32

### Client-side: Modifiying connection options
```c
csp_conn_t * conn = csp_connect(CSP_PRIO_NORM, SERVER_ADDRESS, SERVER_PORT, 1000, CSP_O_RDP | CSP_O_CRC32);
```

### Server-Side: Modifying Socket Options

```c
csp_socket_t sock = {0};
/* Here we tell the server socket to accept only RDP flag packet */
sock.opts = CSP_SO_RDPREQ | CSP_SO_CRC32REQ;
```

---

## Important Notes

When creating connections, it’s crucial to carefully choose the options depending on your application’s needs.
For example, if you need reliable and secure communication, you should enable RDP, HMAC, and CRC32.
If latency is more critical than reliability, you might want to disable RDP and CRC32 to reduce transmission overhead.

---

## 📘 References

- [CSP on GitHub](https://github.com/libcsp/libcsp)