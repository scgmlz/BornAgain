# Setup for BornAgain compilation at SuperMUC LRZ cluster


module load git
module load gcc/4.7
module load cmake/2.8
module load fftw/mpi/3.3
module load gsl
#module load python/2.7_anaconda

export LD_LIBRARY_PATH=/home/hpc/pr87me/di29sok/software/boost_1_55_0.gcc47/lib:$LD_LIBRARY_PATH

export FFTW3=$FFTW_BASE
export GSL_DIR=$GSL_BASE
export BOOST_ROOT=/home/hpc/pr87me/di29sok/software/boost_1_55_0.gcc47


