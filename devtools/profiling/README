# maintainers, attention: if this page is moved, then update the link at
# http://apps.jcns.fz-juelich.de/redmine/projects/bornagain/wiki

This directory contains different scripts for running code profiling utilities.

The goal of these utilities is to determine the speed of a particular
operation/function/algorithm, and to find bottlenecks in program flow.

There are several ways of code profiling:

----------------------------------------------------------
Profiling with valgrind
----------------------------------------------------------

1) Compile BornAgain as usuall and simply run
./run_valgrind.sh

* Compile your application in debug mode
* Generate log file with performance information using valgrind
> valgrind --tool=callgrind -v --dump-every-bb=10000000 --dump-instr=yes --trace-jump=yes ./App commandline
> valgrind --logfile=valgrind.output --num-callers=6 --leak-check=yes  ./App commandline
>>where 'App' is the name of executable, 'commandline' is command line parameters

* Use _kcachegrind_ (from KDE distro) to visualize obtained log file
_kcachegrind_ exists in Linux, for Mac _kcachegrind_ (KDE based) or _qcachegrind_ (pure Qt based) can be installed/compiled as described in
http://langui.sh/2011/06/16/how-to-install-qcachegrind-kcachegrind-on-mac-osx-snow-leopard/

  In my case I was able to compile, but the program is not stable and sometime crashes.

  See also http://kcachegrind.sourceforge.net/html/Usage.html

----------------------------------------------------------
Profiling with gperftool
----------------------------------------------------------

1) gperftool should be installed
download code from http://code.google.com/p/gperftools/
./configure --prefix=/opt/local; make; make install

2) BornAgain should be compiled with GPERFTOOLS in config
make distclean
qmake CONFIG+=GPERFTOOLS
make

3) run profiling
run_gperftools.sh

*) When compiled with GPERFTOOLS option, profiling with valgrind (callgrind) wont work.

----------------------------------------------------------
Profiling with perf
----------------------------------------------------------

Under Linux.

Install Debian package linux-perf.

echo "-1" >/proc/sys/kernel/perf_event_paranoid

perf stat <any performance test>

perf record -o /tmp/perf.out <any performance test>
perf report -i /tmp/perf.out
