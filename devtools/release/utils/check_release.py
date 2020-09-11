import os
import sys
from common import *
import subprocess



def check_manual():
    cmd = "cd %s; wget http://apps.jcns.fz-juelich.de/src/BornAgain/%s" % (get_checkrelease_dir(), get_manual_name())
    run_command(cmd)
    if not os.path.exists(get_checkrelease_dir()+"/"+get_manual_name()):
        exit("Error! Can't access user manual")


def check_tarball():
    print "Checking tarball ..."
    cmd = "cd %s; wget http://apps.jcns.fz-juelich.de/src/BornAgain/BornAgain-%s.tar.gz" % (get_checktarball_dir(), get_version())
    run_command(cmd)
    cmd = "cd %s; tar zxf BornAgain-%s.tar.gz" % (get_checktarball_dir(), get_version())
    run_command(cmd)
    cmd = "cd %s; mkdir build; mkdir installed" % get_checktarball_dir()
    run_command(cmd)
    cmd = "cd %s/build; cmake -DCMAKE_INSTALL_PREFIX=../installed ../BornAgain-%s; make -j8; make check; make install" % (get_checktarball_dir(), get_version())
    run_command(cmd)
    cmd = "cd %s/installed/lib; python -c \"from libBornAgainCore import *; print GetVersionNumber()\"" % (get_checktarball_dir())
    print cmd
    result = subprocess.check_output(cmd, shell=True)
    received_version = result.split("\n")[0]
    if not received_version == get_version():
        exit("Error! Can't get correct version from tarball. Received '"+received_version+"', expected '"+get_version()+"'")


def check_master_branch():
    print "Checking master branch ..."
    cmd = "cd %s; mkdir build; mkdir installed" % get_checkmaster_dir()
    run_command(cmd)
    cmd = "cd %s; git clone git://apps.jcns.fz-juelich.de/BornAgain.git " % get_checkmaster_dir()
    run_command(cmd)
    cmd = "cd %s/build; cmake -DCMAKE_INSTALL_PREFIX=../installed ../BornAgain; make -j8; make check; make install" % (get_checkmaster_dir())
    run_command(cmd)
    cmd = "source %s/installed/bin/thisbornagain.sh; python -c \"from libBornAgainCore import *; print GetVersionNumber()\"" % (get_checkmaster_dir())
    print cmd
    result = subprocess.check_output(cmd, shell=True)
    received_version = result.split("\n")[0]
    if not received_version == get_version():
        exit("Error! Can't get correct version from master branch. Received '"+received_version+"', expected '"+get_version()+"'")


def check_release():
    print "Checking release"
    check_manual()
    check_tarball()
    check_master_branch()
    print "\n"
    print "Congratulations! New %s release was successfully validated. " % (get_version())
    print "Don't forget to post news items."
    print "And yes, this was very productive."


