# maintainers, attention: if this page is moved, then update the link at
# http://apps.jcns.fz-juelich.de/redmine/projects/bornagain/wiki

Example usage:

python2|3 test_performance.py ../../dev-tools/log/perf_history.txt

This will run the performance test suite, and append the outcome
to the file "perf_history.txt". If the filename argument is left
blank, the outcome will be written to stdout.

The script runs all of the performance tests in the old App, as well
as new performance test based on customformfactor.py, which specifically
measures overhead in the Python bindings. For this reason, the script
not only records the host operating system and architecture, but also
the Python version (in many situations, there is a noticeable difference
in performance between Python 2.7 and 3.x). This script depends only
on the core library and standard Python modules.
