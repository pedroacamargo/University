from nfstream import NFStreamer
import json

my_streamer = NFStreamer(source="/tmp/4.pcap")

packets = []

for flow in my_streamer:
    print(flow)
    packet = {"duration": flow.bidirectional_duration_ms, "packets": flow.bidirectional_packets, "bytes": flow.bidirectional_bytes}
    packets.append(packet)

json_str = json.dumps(packets, indent=4)

with open("nfstream.json", "w") as f:
    f.write(json_str)