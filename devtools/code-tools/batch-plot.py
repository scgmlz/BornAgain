#!/usr/bin/env python3
"""
Run plotting code in batch mode: generate figure, but don't plot to terminal.

This script is used in BornAgain:
- with option -s in PyExamples tests, to check functionality of Python examples;
- with option -l to remake full-size images.
"""

import matplotlib, os, re, sys
matplotlib.use('Agg')
from matplotlib import pyplot as plt


def exec_full(script, filename):
    """
    Executes embedded python script.
    http://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3
    """
    import os
    global_namespace = {
        "__file__": filename,
        "__name__": "__main__",
        "__no_terminal__": True
    }
    sys.argv = [filename, 'noshow']
    exec(compile(script, filename, 'exec'), global_namespace)

def reduce_nbin(t):
    """
    Overwrites script lines that set nbin, nx, ny
    """
    pat = re.compile(r'(^\s+(nbin|nx|ny) = )(\d+)$')
    ret = []
    for l in t.split('\n'):
        m = re.match(pat, l)
        if m:
            oldsize = int(m.group(3))
            newsize = min(10, oldsize)
            lout = re.sub(pat, m.group(1)+f'{newsize}', l)
        else:
            lout = l
        ret.append(lout)
    return '\n'.join(ret)


def run_example(mode_short, filename, output_dir):
    """
    Tries to run python example and produce a *.png image
    """
    # Read script from file.
    if not os.path.exists(filename):
        raise Exception("Example script '" + filename + "' not found")
    print("Input script: " + filename, flush=True)
    with open(filename, 'r') as file:
        script = file.read()

    # Detect or impose figure size.
    m = re.search(r'plt\.figure\(.+?figsize=\((.+?),(.+?)\)', script)
    if m: # set figure size as in script
        figsize = (float(m.group(1)), float(m.group(2)))
    else: # script does not specify figure size
        figsize = (640/72, 480/72)
    fig = plt.figure(figsize=(figsize[0], figsize[1]))

    if mode_short:
        script = reduce_nbin(script)

    # Run modified script.
    exec_full(script, filename)
    print("Input script completed.", flush=True)

    # Generate output figure.
    plot_file_name = os.path.join(
        output_dir,
        os.path.splitext(os.path.basename(filename))[0] + ".png")
    print("Output image: " + plot_file_name)
    plt.savefig(plot_file_name, bbox_inches='tight')
    plt.close(fig)

    # Check obtained figure.
    imgSize = os.path.getsize(plot_file_name)
    if imgSize == 0:
        raise Exception("Image file is empty")
    if imgSize < 20000:
        raise Exception("Image file is unplausibly small")


if __name__ == '__main__':

    if len(sys.argv) != 4:
        exit("Usage: check_functionality -s|-f <script_to_test> <output_dir>")
    if sys.argv[1]=='-s':
        mode_short = True
    elif sys.argv[1]=='-f':
        mode_short = False
    else:
        exit("Use flag -s|-f for short or long runs")

    run_example(mode_short, sys.argv[2], sys.argv[3])
