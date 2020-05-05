#!/usr/bin/env bash

export QTDIR=/Users/vagrant/Qt/5.10.1/clang_64
export PATH=/Users/vagrant/.pyenv:/usr/local/bin:$QTDIR/bin/:$PATH
export WORKDIR=/Users/vagrant/build
rm -r -f $WORKDIR; mkdir -p $WORKDIR; cd $WORKDIR;

git clone --recurse-submodules -b develop https://github.com/scgmlz/BornAgain.git


pyversions[1]=2.7.15
pyversions[2]=3.6.7
pyversions[3]=3.7.1

pyadd[1]=2.7
pyadd[2]=3.6
pyadd[3]=3.7

for i in {1..3}
do
    cd $WORKDIR;
    export PYVER=${pyversions[$i]}
    export PYSHORT=${pyadd[$i]}
    echo "Building on" $PYVER $PYADD
    export BUILDDIR=build-$PYVER
    mkdir $BUILDDIR
    cd $BUILDDIR
    echo "PWD" $PWD "PYVER" $PYVER "PYSHORT" $PYSHORT
    eval "$(pyenv init -)"
    pyenv local $PYVER

    export PYEXE=/Users/vagrant/.pyenv/versions/${PYVER}/bin/python
    export PYLIB=/Users/vagrant/.pyenv/versions/${PYVER}/lib/libpython${PYSHORT}m.dylib
    echo "PYEXE" $PYEXE
    echo "PYLIB" $PYLIB

    cmake -DCMAKE_C_COMPILER=/usr/local/opt/llvm/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm/bin/clang++ -DPython_ADDITIONAL_VERSIONS=$PYSHORT -DBORNAGAIN_APPLE_BUNDLE=ON  -DPython_LIBRARIES=$PYLIB -DPython_EXECUTABLE=$PYEXE -DCMAKE_PREFIX_PATH=/usr/local ../BornAgain
    make -j4
    cpack -V
    echo 'Copying dmg installer back to build server'
    echo 'scp /Users/vagrant/build/BornAgain-build-python2/*.dmg scg@scgmini:./deployment/results/.'
    scp /Users/vagrant/build/$BUILDDIR/*.dmg scg@scgmini:./deployment/results/.
done
