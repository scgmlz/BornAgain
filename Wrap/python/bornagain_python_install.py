"""
Installs BornAgain libraries into user Python (Mac only).

Usage: python bornagain_python_install.py

The script generates BornAgain python package in temporary directory and then 
installs it into user's Python site_packages.

Requirements: BornAgain.app has to be installed on the system using .dmg installer.

During generation of Python package
1) The script copies BornAgain libraries from the GUI installation directory (normally 
   it is /Applications/BornAgain.app) into temporary bundle directory
2) Adjusts libraries using Mac's install_name_tool to rely on Python's own libpython2.7.dylib.
   The exact site-packages library location is deduced from the interpreter itself.
3) Generates other files necessary for Python packaging (setup.py, __init__.py)

During installation of Python package
1) The script just runs standard 'python setup.py install' command from the temporary bundle directory
"""

from __future__ import print_function
import os
import sys
import sysconfig
import glob
import tempfile
import shutil
import platform
import site
import subprocess
from distutils.sysconfig import get_python_lib


BORNAGAIN_VERSION = "0.0"

def is_python3():
    if (sys.version_info > (3, 0)):
        return True
    else:
        return False

def python_version_string():
    return str(sys.version_info[0]) + "." + str(sys.version_info[1])


def add_rpath(newpath, filename):
    print("add_rpath ", newpath, filename)
    p = subprocess.Popen(['install_name_tool', '-add_rpath', newpath, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def change_rpath(oldpath, newpath, filename):
    print("change_rpath ", oldpath, newpath, filename)
    p = subprocess.Popen(['install_name_tool', '-change', oldpath, newpath, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def delete_rpath(todelete, filename):
    print("delete_rpath ", todelete, filename)
    p = subprocess.Popen(['install_name_tool', '-delete_rpath', todelete, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def exec_full(filepath):
    """
    Executes embedded python script.
    http://stackoverflow.com/questions/436198/what-is-an-alternative-to-execfile-in-python-3
    """
    import os
    global_namespace = {
        "__file__": filepath,
        "__name__": "__main__",
    }
    with open(filepath, 'rb') as file:
        exec(compile(file.read(), filepath, 'exec'), global_namespace)


def get_python_shared_library():
    """
    Returns full path to the python shared library on which current interpreter is relying
    """
    prefix = sys.prefix
    suffix = sysconfig.get_config_var('LDVERSION') or sysconfig.get_config_var('VERSION')
    result = sys.prefix+"/lib/libpython"+suffix+".dylib"
    return result


def get_script_path():
    """
    Returns the full path to the directory where given scripts resides
    """
    return os.path.dirname(os.path.realpath(sys.argv[0]))


def get_application_dir():
    """
    Returns BornAgain.app directory location, determines BornAgain version number
    """
    global BORNAGAIN_VERSION
    app_dir = ""
    if len(sys.argv) == 2:
        app_dir = sys.argv[1]
    else:
        script_dir = get_script_path()
        app_dir = os.path.abspath(os.path.join(script_dir, "..", "..", ".."))
        
    # getting version number
    lib_dir = glob.glob( os.path.join(app_dir, "Contents", "lib", "BornAgain-*"))
    if len(lib_dir) != 1:
        exit("Can't find BornAgain libraries in "+app_dir)
    
    BORNAGAIN_VERSION = lib_dir[0].split("BornAgain-")[1]
    return app_dir

    
def create_bundle_temp_dir():
    """
    Creates temporary directory for BornAgain package bundle
    """
    tmpdir = os.path.join(tempfile.gettempdir(), "bornagain_bundle")
    if os.path.exists(tmpdir):
        shutil.rmtree(tmpdir)
    os.makedirs(tmpdir)
    return tmpdir


def create_package_dir(destination_dir):
    """
    Create package directory in bundle directory
    """
    packagedir = os.path.join(destination_dir, "bornagain")
    os.makedirs(packagedir)
    return packagedir


def create_library_dir(destination_dir):
    """
    Create library directory in bundle directory
    """
    librarydir = os.path.join(destination_dir, "lib")
    os.makedirs(librarydir)
    return librarydir


def generate_setup_py(destination_dir):
    """
    Generates setup.py file in BornAgain's bundle directory
    """
    text = '''\
# BornAgain setup.py to install BornAgain libraries into Python's site-packages             
# Usage: python setup.py install

import os
import glob
from setuptools import setup


datadir = os.path.join('bornagain', 'lib','BornAgain-{0}')
datafiles = [(datadir, [f for f in glob.glob(os.path.join(datadir, '*'))])]

datadir = os.path.join('bornagain', 'lib','Frameworks')
datafiles += [(datadir, [f for f in glob.glob(os.path.join(datadir, '*'))])]

setup(name='bornagain',
    version='{0}',
    description='Simulate and fit grazing-incidence small-angle scattering',
    url='www.bornagainproject.org',
    author='Scientific Computing Group at MLZ',
    author_email='contact@bornagainproject.org',
    license='GPL',
    packages=['bornagain'],
    data_files = datafiles,
    zip_safe=False,
    )
'''.format(BORNAGAIN_VERSION)
    with open(os.path.join(destination_dir, "setup.py"), "w") as fout:
        fout.write(text)
        fout.close()
    pass


def prepare_init_module(app_dir, bundle_dir):
    source_dir = os.path.join(app_dir, "Contents", "libexec")
    libexec_dir = os.path.join(source_dir, "BornAgain-"+BORNAGAIN_VERSION, "bornagain")    
    package_dir = os.path.join(bundle_dir, "bornagain")
    print("--> Copying modules from '{0}' to '{1}'".format(libexec_dir, package_dir))
    shutil.copytree(libexec_dir, package_dir)
    return package_dir
    

def copy_libraries(app_dir, destination_dir):
    """
    Copy libraries from BornAgain.app into corresponding BornAgain Python package directory
    """
    print("--> Copying libraries from '{0}'".format(app_dir))
    app_bornagainlib_dir = os.path.join(app_dir, "Contents", "lib", "BornAgain-"+BORNAGAIN_VERSION)
    app_frameworks_dir = os.path.join(app_dir, "Contents", "Frameworks")

    # copying BornAgain libraries
    shutil.copytree(app_bornagainlib_dir, os.path.join(destination_dir, "BornAgain-"+BORNAGAIN_VERSION))

    # cleaning unnecessary files
    libfiles = glob.glob(os.path.join(destination_dir, '*/libBornAgainGUI*'))
    for f in libfiles:
        os.remove(f)
    pass

    # copying libraries from Frameworks
    frameworks_libs = glob.glob(os.path.join(app_frameworks_dir, 'lib*'))
    frameworks_dest = os.path.join(destination_dir, "Frameworks")
    if not os.path.exists(frameworks_dest):
        os.makedirs(frameworks_dest)
    for lib in frameworks_libs:
        shutil.copyfile(lib, os.path.join(frameworks_dest, os.path.basename(lib)))


def patch_libraries(dir_name):
    """
    Patches libraries depending on Python to point on the same shared libpython2.7.dylib which current interpreter is using
    """
    print("--> Patching libraries to rely on '{0}'".format(get_python_shared_library()))
    libfiles = glob.glob(os.path.join(dir_name, '*/_libBornAgain*'))
    for f in libfiles:
        if "libBornAgainCore" in f or "libBornAgainFit" in f:
            #cmd = "install_name_tool -delete_rpath  @loader_path/../../Frameworks " + f
            delete_rpath("@loader_path/../../Frameworks", f)
        #cmd = "install_name_tool -add_rpath  @loader_path/../Frameworks " + f
        add_rpath("@loader_path/../Frameworks", f)
        if "libBornAgainCore" in f:
            #cmd = "install_name_tool -add_rpath  @loader_path/. " + f
            add_rpath("@loader_path/.", f)

    libfiles += glob.glob(os.path.join(dir_name, '*/libboost_python*'))
    for f in libfiles:
        #cmd = "install_name_tool -change @rpath/Python.framework/Versions/2.7/Python " + get_python_shared_library() + " " + f
        change_rpath("@rpath/Python.framework/Versions/"+python_version_string()+"/Python", get_python_shared_library(), f)


    pass

    
def create_bundle(app_dir):
    """
    Creates ready to install BornAgain Python bundle package
    """
    bundle_dir = create_bundle_temp_dir()
    print('-'*80)
    print("Generating Python bundle in temporary '{0}'".format(bundle_dir))
    print('-'*80)

    print("--> Generating bundle setup files")
    
    generate_setup_py(bundle_dir)
    
    package_dir = prepare_init_module(app_dir, bundle_dir)
    
    library_dir = create_library_dir(package_dir)
    copy_libraries(app_dir, library_dir)
    
    patch_libraries(library_dir)
    
    print("\nBornAgain Python bundle is successfully created in temporary directory '{0}'".format(bundle_dir))
    print("Run 'python setup.py install' from there to install it into your Python's site-packages")
    return bundle_dir
        

def install_bundle(dir_name):
    """
    Installs BornAgain Python bundle previously generated in the directory dir_name
    """
    print('-'*80)
    print("Installing bundle in Python site-packages '{0}'".format(get_python_lib()))
    print('-'*80)
    
    os.chdir(bundle_dir)
    sys.argv = ['setup.py', 'install']
    exec_full('setup.py')
    print("\nBornAgain Python bundle is successfully installed in '{0}'".format(get_python_lib()))
    print("Congratulations!")
    
    
if __name__ == '__main__':
    if not platform.system() == 'Darwin':
        exit("This script is intended for MacOs systems. Exiting...")
        
    app_dir = get_application_dir()
    
    print('-'*80)
    print("Installation of BornAgain-{0} libraries into site-packages of your Python".format(BORNAGAIN_VERSION))
    print('-'*80)
    print("From :", app_dir)
    print("To   :", get_python_lib())
    print(" ")
    print("Possible options:")
    print("[0] - Generate bundle with BornAgain libraries, do not install it.")
    print("[1] - Generate bundle and install it into site-packages of your Python.")
    print("[2] - Exit")

    var = 0
    if is_python3():
        var = int(input("Enter your choice [1]: ") or "1")
    else:
        var = int(raw_input("Enter your choice [1]: ") or "1")

    if var == 0:
        create_bundle(app_dir)
    elif var == 1:
        bundle_dir = create_bundle(app_dir)
        install_bundle(bundle_dir)
    else:
        exit("Good bye")
        



