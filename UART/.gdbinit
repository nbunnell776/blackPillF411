# Simple .gdbinit for connecting to Blue Pill boards w/ Black Magic Probe

# Connect to BMP
echo Executing ./.gdbinit to connect to target /dev/ttyACM0\n
target extended-remote /dev/ttyACM0

# Power dev board
echo Enabling target power...\n
monitor tpwr enable

# Scan for dev board
echo Scanning for SWD target...\n
monitor swdp_scan
