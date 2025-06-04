#!/usr/bin/env python3

import os
import subprocess
from datetime import datetime, timezone

# Get current UTC timestamp in a safe format
timestamp = datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M:%S")

# Try to get the latest Git tag (e.g., v2.1.3)
try:
    version = subprocess.check_output(
        ["git", "describe", "--tags", "--abbrev=0"],
        stderr=subprocess.DEVNULL
    ).decode().strip()
except Exception:
    version = "v0.0.0"

# Try to get the short Git commit hash (e.g., a1b2c3d)
try:
    commit = subprocess.check_output(
        ["git", "rev-parse", "--short", "HEAD"],
        stderr=subprocess.DEVNULL
    ).decode().strip()
except Exception:
    commit = "unknown"

# Generate the build_info.h file
output_path = os.path.join(os.path.dirname(__file__), "../build_info.h")

with open(output_path, "w") as f:
    f.write(f"""\
#ifndef BUILD_INFO_H
#define BUILD_INFO_H

#define BUILD_TIMESTAMP  "{timestamp}"
#define BUILD_COMMIT     "{commit}"
#define BUILD_VERSION    "{version}"

#endif // BUILD_INFO_H
""")

print(f"[build_info] Wrote build_info.h with version {version}, commit {commit}, timestamp {timestamp}")
