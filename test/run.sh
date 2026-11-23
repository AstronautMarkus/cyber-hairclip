#!/usr/bin/env sh
# Builds the firmware for the host against test/mock and runs the simulation under ASan + UBSan.
set -eu
cd "$(dirname "$0")/.."
mkdir -p build
SRC=$(find cyber_hairclip/src -name '*.cpp' | sort)
for BOARD in ESP8266 ESP32; do
  # shellcheck disable=SC2086 # $SRC is a list of paths without spaces
  ${CXX:-c++} -std=gnu++17 -D"$BOARD" -Itest/mock -include Arduino.h -O1 -g \
    -fsanitize=address,undefined -fno-sanitize-recover=all -Wall -Wno-sign-compare \
    -x c++ cyber_hairclip/cyber_hairclip.ino -x none $SRC test/sim.cpp -o "build/sim_$BOARD"
  printf '%s: ' "$BOARD"
  "./build/sim_$BOARD"
done
