# run GISASFW functional tests with 'gperftools'
# see README for more explanation

mkdir -p ./output


application=../../App/App
#arguments="isgisaxs9 profile"
#arguments="isgisaxs10 batch"
#arguments="isgisaxs9 batch"
#arguments="isgisaxs2 batch profile"
#arguments="--isgisaxs09 --batch"
arguments="--testbugs --batch"
focuson=GISASExperiment

# ------------------------------------------- #
# profiling cpu usage
# ------------------------------------------- #
profile_cpu=no
if [ $profile_cpu = "yes" ]
then
#  valgrind --tool=callgrind -v --dump-every-bb=10000000 --dump-instr=yes --trace-jump=yes ./App commandline
  valgrind  --tool=callgrind --dsymutil=yes --callgrind-out-file=./output/callgrind.output  --log-file=./output/tmplog.output --dump-instr=yes --trace-jump=yes $application $arguments
# --zero-before=GISASExperiment
fi


# ------------------------------------------- #
# profiling HEAP usage
# ------------------------------------------- #
profile_memory=yes
if [ $profile_memory = "yes" ]
then
  valgrind --log-file=./output/valgrind.output  --dsymutil=yes --num-callers=6 --track-origins=yes --leak-check=yes $application $arguments
fi

#valgrind --log-file=valgrind.output --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./App/App mesocrystal
