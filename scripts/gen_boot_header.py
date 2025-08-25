#!/usr/bin/env python3
import sys
import zlib
import hashlib
import struct

# Usage: python update_boot_header.py app.bin boot_header.h

if len(sys.argv) != 3:
    print("Usage: python update_boot_header.py <app_bin> <boot_header_h>")
    sys.exit(1)

app_bin_file = sys.argv[1]
boot_header_file = sys.argv[2]

# Read app binary
with open(app_bin_file, "rb") as f:
    app_data = f.read()

app_size = len(app_data)
crc32 = zlib.crc32(app_data) & 0xFFFFFFFF
sha256 = hashlib.sha256(app_data).digest()  # 32 bytes

# Convert SHA-256 to 8x uint32 array for boot_header
hash_words = struct.unpack(">8I", sha256)

# Prepare boot header in binary form (same layout as struct)
boot_header_bin = struct.pack(
    "<6I8I",                # 6 uint32 fields + 8x uint32 hash
    0xB00710AD,             # magic
    app_size,               # img_size
    crc32,                  # crc32
    1,                      # version
    0x08010000,             # load_addr
    0x08010000 + 56,        # entry (sizeof boot_header_t = 56 bytes)
    *hash_words             # SHA256 hash
)

# Prepend boot header to .bin
with open(app_bin_file, "r+b") as f:  # read/write binary
    f.seek(0)  # go to start
    f.write(boot_header_bin)

print(f"[boot_header] Prepended boot header to {app_bin_file}")
print(f"App size: {app_size} bytes, CRC32: 0x{crc32:08X}")
