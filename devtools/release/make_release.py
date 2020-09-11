#!/usr/bin/env python

import os
import sys

from utils.common import *
from utils.prepare_release import *
from utils.finalize_release import *


def main():

    if len(sys.argv) != 2:
        print "Please specify the name of the release branch."
        print "Usage: python make_release.py release-0.9.3"
        exit()

    set_branch_name(sys.argv[1])
    set_working_dir(os.getcwd() + "/" + get_branch_name())

    if os.path.exists(get_working_dir()):
        print "Directory %s exists, continuing release process." % get_working_dir()
        finalize_release()
    else:
        prepare_release()


if __name__ == '__main__':
    main()
