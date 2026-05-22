from pathlib import Path
import hashlib
import random
import os
import pandas as pd
import subprocess

NORMAL_DIR  = "pcaps/normal"
VPN_DIR     = "pcaps/vpn"
OUTPUT_CSV  = "csvs/merged_flows.csv"


def run_zeek(pcap_path: str) -> None:
    log_dir = f"zeek_logs/{os.path.basename(pcap_path).replace('.pcap','')}"
    os.makedirs(log_dir, exist_ok=True)

    if not os.path.exists(pcap_path):
        print(f"File not found: {pcap_path}")
        return 
    
    result = subprocess.run(
        ["zeek", "-C", "-r", pcap_path, f"Log::default_logdir={log_dir}"],
        check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL
    )
    if result.returncode != 0:
        print(f"[WARN] Zeek error on {pcap_path}:\n{result.stderr}")


def load_conn_log(log_dir: str) -> pd.DataFrame:
    log_path = Path(log_dir) / "conn.log"
    if not log_path.exists():
        return pd.DataFrame()

    headers = []
    rows = []

    with open(log_path) as f:
        for line in f:
            line = line.rstrip("\n")
            if line.startswith("#fields"):
                headers = line.split("\t")[1:]
            elif line.startswith("#"):
                continue
            else:
                rows.append(line.split("\t"))

    if not headers or not rows:
        return pd.DataFrame()

    df = pd.DataFrame(rows, columns=headers)
    return df


def process_directory(pcap_dir: str, label: str) -> pd.DataFrame:
    frames = []
    pcap_dir_path = Path(pcap_dir)

    for pcap_file in sorted(pcap_dir_path.glob("*.pcap")):
        print(f"[{label}] Processing {pcap_file.name} …")
        run_zeek(str(pcap_file))

        df = load_conn_log(f"zeek_logs/{os.path.basename(pcap_file).replace('.pcap','')}")
        if df.empty:
            print(f"  ↳ no conn.log produced, skipping")
            continue

        df["source_file"] = pcap_file.name
        df["traffic_label"] = label
        frames.append(df)
        print(f"  ↳ {len(df):,} connections loaded")

    return pd.concat(frames, ignore_index=True) if frames else pd.DataFrame()


def load_pd():
    vpn_df    = process_directory(VPN_DIR,    label="vpn")
    normal_df = process_directory(NORMAL_DIR, label="normal")

    merged = pd.concat([vpn_df, normal_df], ignore_index=True)

    if merged.empty:
        print("No data collected – check your Zeek installation and pcap paths.")
        return

    merged.replace("-", pd.NA, inplace=True)
    merged.drop_duplicates(inplace=True)
    merged.reset_index(drop=True, inplace=True)

    merged.to_csv(OUTPUT_CSV, index=False)
    print(f"\n✓ Merged {len(merged):,} rows → {OUTPUT_CSV}")
    print(merged[["ts", "id.orig_h", "id.resp_h", "proto",
                  "traffic_label", "source_file"]].head(10).to_string(index=False))

load_pd()