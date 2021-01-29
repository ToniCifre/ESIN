#!/usr/bin/python
import sys

error = False

with open(sys.argv[1]) as fp:
    lines = fp.readlines()
    for l in range(len(lines)):
        if lines[l][:3].count('#') == 2:
            if lines[l][2:] != lines[l - 1]:
                print(f'\n----- ERROR IN LINE {l} -----')
                print(f'-result: {lines[l - 1]}-real:{lines[l][2:]}')
                error = True

    if not error and len(lines) > 10:
        print("\n------------------------------------")
        print("----- No s'ha trobat cap error -----")
        print("------------------------------------\n")
