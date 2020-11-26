#!/usr/bin/env python3
"""
Reads a BornAgain simulation script, and converts into normal form.

Export to normal form is done by BornAgain's ExportToPython function.
"""

import argparse, os, re
import bornagain as ba

def substitute_sample(ti, tc):
    """
    Returns script ti, except for the get_sample function which is taken from script tc.
    """
    pat = re.compile(r'(\ndef get_sample\(.+?:\n)(\s*""".+?"""\n)?\n*(((\s{4}.*?)?\n)+?\n)(\w|$)',
                     flags = re.S)

    mi = re.search(pat, ti)
    if not mi:
        raise Exception("Input code has no function get_sample")
    header = mi.group(1)

    mn = re.search(pat, tc)
    if not mn:
        raise Exception("Normalized code has no function get_sample")
    if mn.group(1)!=header:
        raise Exception(f'Signature of function get_sample has changed from "{header}" to "{mn.group(1)}"')

    if mi.group(2):
        header += mi.group(2)+'\n'

    t = re.sub(pat, header+mn.group(3)+mi.group(6), ti)
    return t

def cycle_text(ti, fname):
    """
    Returns normalized version of script ti as obtained from BornAgain's export-to-Python function.
    """
    c=compile(ti, fname, 'exec')
    ns = {}
    exec(c,ns)
    globals().update(ns)
    s = get_simulation()
    s.setSample(get_sample())
    return ba.generateSimulationCode(s)

def normalize_text(ti, fname):
    tc = cycle_text(ti, fname)
    if verbose:
        print(f'.. cycled through BA, {len(ti.split())} -> {len(tc.split())} lines')
    tf = substitute_sample(ti, tc)
    if verbose:
        print(f'.. normalized, {len(ti.split())} -> {len(tf.split())} lines')
    return tf

def normalize_file(fname, inplace):
    try:
        print(f'FILE {fname}:')

        # read file
        with open(fname, 'r') as f:
            ti = f.read()
            if verbose:
                print(f'.. read {len(ti.split())} lines')

        # normalize
        t = normalize_text(ti, fname)
        if verbose:
            print(f'.. obtained normalized text')
        if t == ti:
            if verbose:
                print(f'.. nothing changed')
            return 0
        with open('out1.py', 'w') as f:
            f.write(t)
        if verbose:
            print(f'.. saved to out1.py')

        # check invariance under second normalization
        t2 = normalize_text(t, fname)
        if verbose:
            print(f'.. re-normalized')
        if t2 != t:
            with open('out2.py', 'w') as f:
                f.write(t2)
            exit(f'=> BUG - changed under second normalization, see out2.py vs out1.py')

        # check invariance of simulation result:

        # output
        if inplace:
            os.rename('out1.py', fname)
            print(f'=> NORMALIZED')
        else:
            print(t)

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
    files = args.input_files

    count = [0, 0, 0]
    for f in files:
        ret = normalize_file(f, args.in_place)
        count[ret] += 1

    if (len(files)<=1):
        exit(0)

    out = []
    if count[0]>0:
        out.append(f'{count[0]} unchanged')
    if count[1]>0:
        out.append(f'{count[1]} normalized')
    if count[2]>0:
        out.append(f'{count[2]} failed')
    print(f'TOTAL of {len(args.input_files)} files: {", ".join(out)}')
