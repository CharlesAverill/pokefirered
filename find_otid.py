#! /home/charlesaverill/anaconda3/bin/python3

def get_otid(personality):
    p1 = personality & 0xFFFF
    p2 = personality & 0xFFFF0000
    for otid in range(0, 2 ** 32):
            tid = otid & 0xFFFF
            sid = otid & 0xFFFF0000
            val = tid ^ sid ^ p1 ^ p2
            if val < 8:
                    print(otid)

import sys
get_otid(int(sys.argv[1], base=16))
