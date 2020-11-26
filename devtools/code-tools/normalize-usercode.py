#!/usr/bin/env python3
"""
Reads a BornAgain simulation script, and converts into normal form.

Export to normal form is done by BornAgain's ExportToPython function.
"""

import argparse
import bornagain as ba

def normalize_text(ti, fname):
    c=compile(ti, fname, 'exec')
    ns = {}
    exec(c,ns)
    globals().update(ns)
    s = get_simulation()
    s.setSample(get_sample())
    t = ba.generateSimulationCode(s)
    return t

def normalize_file(fname, inplace):
    try:
        print(f'FILE {fname}:')

        # read file, normalize
        with open(fname, 'r') as f:
            ti = f.read()
            if verbose:
                print(f'.. read {len(ti.split())} lines')
        t = normalize_text(ti, fname)
        if verbose:
            print(f'.. normalized')
        if t == ti:
            if verbose:
                print(f'.. nothing changed')
            return 0

        # output
        if inplace:
            with open(fname, 'w') as f:
                f.write(t)
            print(f'=> NORMALIZED')
        else:
            print(t)

        # check invariance under second normalization
        t2 = normalize_text(t, fname)
        if verbose:
            print(f'.. re-normalized')
        if t2 != t:
            with open('reno.py', 'w') as f:
                f.write(t2)
            exit(f'=> BUG - changed under second normalization, see reno.py')

        return 1

    except Exception as e:
        print(f'=> FAILED - {e}')
        return 2


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("input_files", nargs='+', type=str)
    parser.add_argument("-i", "--in-place", action="store_true")
    parser.add_argument("-v", "--verbose", action="store_true")
    args = parser.parse_args()
    verbose = args.verbose

    count = [0, 0, 0]
    for f in args.input_files:
        ret = normalize_file(f, args.in_place)
        count[ret] += 1

    print(f'TOTAL: {count[0]} unchanged, {count[1]} normalized, {count[2]} failed')
