"""
Creates picture with number of lines of code.
Usage: python3 lines_of_code.py

The command should be executed in the directory where lines_of_code.py is located
(i.e. in <BornAgain>/dev-tools/analyze)
"""
import sys
if sys.version_info < (3, 0):
    exit("Requires python3, exiting ...")
import os
from baloc import HistoryCollector
from baloc import history_plot
import matplotlib.pyplot as plt


gitlog_filename = "gitlog.tmp"


def process_loc_number(targetfolder="../..", gitlog=gitlog_filename):
    prevfolder = os.getcwd()
    os.chdir(targetfolder)

    collector = HistoryCollector()
    collector.run()
    collector.save_report(os.path.join(prevfolder, gitlog))

    os.chdir(prevfolder)


def plot_loc_number(gitlog=gitlog_filename):
    history_plot(gitlog)
    plt.show()


if __name__ == '__main__':
    print('-' * 80)
    print("Generating picture for number of lines of code")
    print('-' * 80)
    print(" ")
    print("Possible options:")
    print("[0] - Generate {0} and picture.".format(gitlog_filename))
    print("[1] - Generate only {0}.".format(gitlog_filename))
    print("[2] - Generate picture using existing {0}.".format(gitlog_filename))
    print("[3] - Exit")

    var = int(input("Enter your choice [0]: ") or "0")

    if var == 0:
        process_loc_number()
        plot_loc_number()
    elif var == 1:
        process_loc_number()
    elif var == 2:
        plot_loc_number()
    else:
        exit("Good bye")


