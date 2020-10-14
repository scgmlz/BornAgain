"""
Usage: python check_functionality.py <path-to-example>/<example>.py

Checks functionality of BornAgain Python example by running it in 'embedded' way.

The check passes successfully if the example runs without exceptions thrown and
generates non-zero-size intensity image.
"""

import sys
import os
import matplotlib
matplotlib.use('Agg')
from matplotlib import pyplot as plt

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")

output_dir = "@output_dir@"

def get_figure(filename):
    """
    Returns pyplot figure of appropriate size
    """
    if "AllFormFactorsAvailable" in filename:
        xsize, ysize = 1024, 768
    else:
        xsize, ysize = 640, 480

    dpi = 72.
    return plt.figure(figsize=(xsize/dpi, ysize/dpi))


def exec_full(filepath):
    """
    Executes embedded python script.
    http://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3
    """
    import os
    global_namespace = {
        "__file__": filepath,
        "__name__": "__main__",
    }
    sys.argv = []  # FIXME after cleanup in plot_utils
    with open(filepath, 'rb') as file:
        exec(compile(file.read(), filepath, 'exec'), global_namespace)


def run_example(filename):
    """
    Tries to run python example and produce a *.png image
    """
    if not os.path.exists(filename):
        raise Exception("Example script '"+filename+"' not found")

    print("Input script: "+filename)

    fig = get_figure(filename)

    exec_full(filename)

    plot_file_name = os.path.join(output_dir,
                                  os.path.splitext(os.path.basename(filename))[0] + ".png")
    print("Output image: "+plot_file_name)
    plt.savefig(plot_file_name, bbox_inches='tight')
    plt.close(fig)

    imgSize = os.path.getsize(plot_file_name)
    if imgSize == 0:
        raise Exception("Image file is empty")
    if imgSize < 20000:
        raise Exception("Image file is unplausibly small")


if __name__ == '__main__':

    if len(sys.argv) != 2:
        exit("Auxiliary script check_functionality called with wrong number of arguments")

    run_example(sys.argv[1])
