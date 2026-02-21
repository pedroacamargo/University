import sys

# Use command line: tshark -r 4.pcap -T fields -e ip.src -e ip.dst | python3 pipe.py

for line in sys.stdin:
    line = line.strip()
    if not line:
        continue
    src, dst = line.split("\t")
    print(f"{src} -> {dst}")