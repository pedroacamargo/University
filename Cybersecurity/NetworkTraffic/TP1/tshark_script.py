#import pandas as pd
import subprocess

tsharkCall = [
    "sudo",
    "tshark",
    "-r", "/tmp/4.pcap",
    "-T", "fields",
    "-e", "frame.time",
    "-e", "ip.src",
    "-e", "ip.dst",
    "-e", "ip.ttl",
    "-e", "tcp.srcport",
    "-e", "tcp.dstport",
    "-e", "tcp.window_size_value"
]

with subprocess.Popen(tsharkCall, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True) as proc:
    for line in proc.stdout:
        print(line.strip())
