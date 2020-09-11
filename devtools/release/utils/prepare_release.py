#!/usr/bin/env python

import sys
import os
import time

from common import *

def make_directories():
    print "\nCreating directory structure ... "
    os.makedirs(get_working_dir())
    os.makedirs(get_build_dir())
    os.makedirs(get_upload_dir())
    os.makedirs(get_install_dir())
    os.makedirs(get_checkrelease_dir())
    os.makedirs(get_checktarball_dir())
    os.makedirs(get_checkmaster_dir())


def git_clone():
    print "\nCloning BornAgain repository ... "
    cmd = "cd %s; git clone git@apps.jcns.fz-juelich.de:BornAgain.git" % get_working_dir()
    run_command(cmd)
    print "\nChecking out release branch ... "
    cmd = "cd %s; git checkout %s" % (get_source_dir(), get_branch_name())
    run_command(cmd)


def download_from_app_server():
    print "\nDownloading from application server ..."
    cmd = "rsync -avzhe ssh apps@apps.jcns.fz-juelich.de:/www/apps/src/BornAgain/ %s" %get_upload_dir()
    run_command(cmd)


def cmake_release():
    print "\nRunning cmake ...", get_build_dir()
    # cmd = "cd %s; cmake -DBORNAGAIN_USERMANUAL=ON -DBORNAGAIN_RELEASE=ON -DCMAKE_INSTALL_PREFIX=%s %s" % (get_build_dir(), get_install_dir(), get_source_dir() )
    cmd = "cd %s; cmake  -DCMAKE_INSTALL_PREFIX=%s %s" % (get_build_dir(), get_install_dir(), get_source_dir() )
    run_command(cmd)


def compile_release():
    print "\nCompiling ..."
    cmd = "cd %s; make -j8; make check; make install" % get_build_dir()
    run_command(cmd)


def measure_performance():
    print "\nMeasuring performance ..."
    perf_txt = get_source_dir()+"/dev-tools/log/perf_history.txt"
    run_command("cd %s; ./bin/App --performance --batch; " % get_build_dir())
    run_command("echo \"# Release %s\" >> %s" % (get_version(), perf_txt))
    run_command("cd %s; cat perf_history.txt >> %s" % (get_build_dir(), perf_txt))


def make_tarball():
    print "\nMaking tarball ..."
    run_command("cd %s; make package_source" % get_build_dir())


def update_upload_dir():
    print "\nUpdating directory for upload ..."
    run_command("mv %s/BornAgain*.tar.gz %s/old" % (get_upload_dir(), get_upload_dir()))
    run_command("mv %s/BornAgain*-win32.exe %s/old" % (get_upload_dir(), get_upload_dir()))
    run_command("mv %s/BornAgain-*-macosx64-*.dmg %s/old" % (get_upload_dir(), get_upload_dir()))
    run_command("mv %s/*Manual-*.pdf %s/old" % (get_upload_dir(), get_upload_dir()))
    run_command("cp %s/BornAgain-%s.tar.gz %s" % (get_build_dir(), get_version(), get_upload_dir()))
    run_command("cp %s/CHANGELOG %s" % (get_source_dir(), get_upload_dir()))
    #run_command("cp %s/Doc/UserManual/BornAgainManual.pdf %s/%s" % (get_build_dir(), get_upload_dir(), get_manual_name()) )


def prepare_release():
    print "\nPreparing release %s in working directory '%s'." % (get_version(), get_working_dir())

    make_directories()
    git_clone()
    download_from_app_server()
    cmake_release()
    compile_release()
    #measure_performance()
    make_tarball()
    update_upload_dir()

    print " "
    print "New %s release is successfully created in the %s. Please check it now ;-)" % (get_version(), get_working_dir())
    print "Things to do:"
    print "*) Copy windows installer to ", get_upload_dir()
    print "After your are done, run this script again."

