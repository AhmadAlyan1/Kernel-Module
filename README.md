# Linux Kernel Module: Block 8.8.8.8

## Description
This Linux kernel module blocks all network traffic from **8.8.8.8** (Google DNS) while allowing all other IP addresses. It uses Netfilter hooks to inspect incoming packets and drop those originating from 8.8.8.8.

## Features
✅ Blocks traffic from `8.8.8.8`  
✅ Allows all other IPs  
✅ Lightweight and efficient  
✅ Uses Netfilter (iptables-based filtering)  

## Requirements
- Linux system with kernel headers installed
- `make` and `gcc` installed

## Installation & Usage

### 1️⃣ **Compile the Kernel Module**
Run the following command to build the module:
```sh
make
```

### 2️⃣ **Load the Module**
Insert the kernel module into the system:
```sh
sudo insmod block_google.ko
```

### 3️⃣ **Verify It’s Running**
Check system logs to see if packets from `8.8.8.8` are being blocked:
```sh
dmesg | tail
```
Expected output:
```
IP Blocking Module Loaded (Blocking Only 8.8.8.8)
Blocked packet from 8.8.8.8
```

### 4️⃣ **Unload the Module**
To stop blocking `8.8.8.8`, remove the module:
```sh
sudo rmmod block_google
```

### 5️⃣ **Clean Up (Optional)**
To remove compiled files:
```sh
make clean
```

## Notes
- This module operates at the kernel level and requires root privileges.
- Make sure to recompile it if you update your kernel.

## License
This module is open-source and released under the **GPL-2.0 License**.

---
