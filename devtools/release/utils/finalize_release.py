import os
import sys
import time

from common import *
from check_release import *

def upload_release():
    print "Uploading to the app server ..."
    cmd = "rsync --delete -avzhe ssh %s/ apps@apps.jcns.fz-juelich.de:/www/apps/src/BornAgain/" % get_upload_dir()
    run_command(cmd)


def finalize_git():
    print "Finalizing git ..."
    cmd = "cd %s; git commit -a -m \"Release %s\"" % (get_source_dir(), get_version())
    run_command(cmd)

    cmd = "cd %s; git push" % get_source_dir()
    run_command(cmd)

    # master branch
    cmd = "cd %s; git checkout master; git pull" % get_source_dir()
    run_command(cmd)

    cmd = "cd %s; git merge --no-ff %s -m \"Merge %s\"" % (get_source_dir(), get_branch_name(), get_version())
    run_command(cmd)

    cmd = "cd %s; git push" % get_source_dir()
    run_command(cmd)

    cmd = "cd %s; git tag -a v%s -m \"Release %s\"" % (get_source_dir(), get_version(), get_version())
    run_command(cmd)

    cmd = "cd %s; git push --tags" % get_source_dir()
    run_command(cmd)

    # develop branch
    cmd = "cd %s; git checkout develop; git pull" % get_source_dir()
    run_command(cmd)

    cmd = "cd %s; git merge --no-ff %s -m \"Merge %s\"" % (get_source_dir(), get_branch_name(), get_version())
    run_command(cmd)

    cmd = "cd %s; git push" % get_source_dir()
    run_command(cmd)

    # deleting branch

    cmd = "cd %s; git push origin --delete %s" % (get_source_dir(), get_branch_name())
    run_command(cmd)

def get_menu_option():
    print "\nFinalizing release %s in working directory '%s'." % (get_version(), get_working_dir())

    print "Please select what you want to do:"
    print ""
    print "1. Upload release to the apps server"
    print "2. Finalize git"
    print "3. Check release"
    print "4. Quit"

    choice = 0
    is_valid = 0

    while not is_valid:
        try:
            choice = int(raw_input('Enter your choice [1-4] : '))
            is_valid = 1
        except ValueError, e:
            print ("'%s' is not a valid integer." % e.args[0].split(": ")[1])
    return choice

def finalize_release():
    choice = get_menu_option()

    while choice != 4:
        if choice == 1:
            upload_release()
        elif choice == 2:
            finalize_git()
        elif choice == 3:
            check_release()
        else:
            print ("Invalid number. Try again...")
        choice = get_menu_option()
    exit("Good bye")

