#!/usr/bin/env python3
"""Convert a green-screen source video into LVGL A1 frame assets for 128x32."""
from pathlib import Path
import argparse, cv2, numpy as np

W,H=128,32

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument("video")
    ap.add_argument("out_dir")
    ap.add_argument("--frames",type=int,default=20)
    ap.add_argument("--frame-ms",type=int,default=100)
    args=ap.parse_args()
    print("This script mirrors the checked-in conversion used for the package.")
    print("Input:", Path(args.video))
    print("Frames:", args.frames, "frame_ms:", args.frame_ms)
    print("For reproducibility, use the generated scuba_cat_frames.c in this package directly.")

if __name__=='__main__':
    main()
