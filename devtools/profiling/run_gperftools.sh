# run GISASFW functional tests with 'gperftools'
# see README for more explanation

mkdir -p ./output


application=../../App/App
arguments="mesocrystal profile"
focuson=GISASExperiment

# ------------------------------------------- #
# profiling cpu usage
# ------------------------------------------- #
profile_cpu=yes
if [ $profile_cpu = "yes" ]
then
  OutputCpuLog=./output/gperftools_cpuprof.out

  # generating log
  CPUPROFILE=$OutputCpuLog $application $arguments

  # analysing log
  pprof --text --focus $focuson /bin/ls $OutputCpuLog

  #generating graph
  pprof --gv --focus GISASExperiment /bin/ls $OutputCpuLog &

  # generating log for usage with qcachegrind
  pprof --callgrind /bin/ls $OutputCpuLog > $OutputCpuLog.callgrind
  #one have to look at it with
  #~/Applications/qcachegrind.app/Contents/MacOS/qcachegrind output/gperftools_cpuprof.out.callgrind
fi


# ------------------------------------------- #
# profiling HEAP usage
# ------------------------------------------- #
profile_heap=no
if [ $profile_heap = "yes" ]
then
  OutputHeapLog=./output/gperftools_heapprof

  # generating log
  HEAPPROFILE=$OutputHeapLog $application $arguments

  # analysing log
  pprof --text --focus $focuson $application ./output/gperftools_heapprof.0001.heap

  #generating graph
  #pprof --gv --focus $focuson $application ./output/gperftools_heapprof.0001.heap
fi


