"""
The script compares BornAgain/ThirdParty/RootMinimizers with original ROOT installation to propagate code modifications
from ROOT to our source tree.
"""
import os
import filecmp
import shutil

ROOT_SOURCE = "/home/pospelov/software/source/root"
BORNAGAIN_SOURCE = "/home/pospelov/development/BornAgain/BornAgain/ThirdParty/Fit/RootMinimizers"


def copy_file_to_file(source, destination):
    """
    Copies file to another.
    """
    shutil.copyfile(source, destination)


def find_files(rootdir):
    """
    Yield recursive list of files in given rootdir
    """
    for subdir, dirs, files in os.walk(rootdir):
        for filename in files:
            #yield os.sep.join([subdir, filename])
            yield subdir, filename


def get_source_files(rootdir):
    """
    Return list of *.cxx *.cpp *.h files in given rootdir
    """
    extensions = [".h", ".cpp", ".cxx"]
    result = []
    for subdir, filename in find_files(rootdir):
            name, ext = os.path.splitext(filename)
            if ext in extensions:
                result.append(os.sep.join([subdir, filename]))
    return result


#def find_files_with_same_name(rootdir, name_to_find):
#    """
#    Returns recursive list of files in rootdir with given name
#    """
#    result = []
#    for file in find_files(rootdir):
#        if os.path.basename(file) == name_to_find:
#            result.append(file)
#    return result


def find_files_with_same_name(filename_list, name_to_find):
    same_names = []
    for filename in filename_list:
        if os.path.basename(filename) == name_to_find:
            same_names.append(filename)

    result = []
    if len(same_names) > 1:
        for name in same_names:
            if "Math" in name or "TMVA" in name:
                result.append(name)
    else:
        result = same_names

    return result


def build_difference_map():
    ba_files = get_source_files(BORNAGAIN_SOURCE)
    root_files = get_source_files(ROOT_SOURCE)

    for ba_file in ba_files:
        found_files = find_files_with_same_name(root_files, os.path.basename(ba_file))
        if len(found_files) == 1:
            if filecmp.cmp(ba_file, found_files[0]) == False:
                cmd = "cp " + found_files[0] + " " + os.path.dirname(ba_file)
                print(len(found_files), found_files[0], ba_file)
                copy_file_to_file(found_files[0], ba_file)
        else:
            print(len(found_files), found_files, ba_file)


if __name__ == '__main__':
    build_difference_map()
