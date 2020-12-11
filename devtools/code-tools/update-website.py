#!/usr/bin/env python3
"""
To update examples on website:

1) Run in your build directory
ctest -R PyExamples
This will run all existing examples and generate intensity images for web site.

2) Run this script
python update-examples.py <website-source-dir> <examples_root> <img-dir>
"""

import argparse, datetime, filecmp, os, shutil


def log(msg):
    flog.write(msg+"\n")


def log2(msg):
    print(msg)
    log(msg)


def find_files(dir_name):
    """
    Return recursive list of files in given dir_name.
    """
    for subdir, dirs, files in os.walk(dir_name):
        for filename in files:
            yield subdir, filename


def get_files(dir_name, extension):
    """
    Return list of all files in subdirectories of dir_name with given extension
    """
    result = []
    for subdir, filename in find_files(dir_name):
        if os.path.basename(subdir)=="utils":
            continue
        name, ext = os.path.splitext(filename)
        if ext in extension:
            result.append(os.sep.join([subdir, filename]))
    return result


def find_files_with_same_name(filename_list, name_to_find):
    same_names = []
    for filename in filename_list:
        if os.path.basename(filename) == name_to_find:
            same_names.append(filename)

    return same_names


def update_one_file(source_list, dest):
    """
    Update destination file 'dest', using a suitable source file from 'example_root'.
    Returns 2=error, 1=modified, 0=unchanged.
    On succes (0 or 1), the source file is removed from source_list.
    """
    likely_sources = find_files_with_same_name(source_list, os.path.basename(dest))
    if len(likely_sources) == 0:
        log2(f'! file {dest}\n    not found in source dir (ERROR)')
        return 2
    if len(likely_sources) > 1:
        log2(f'! {dest}\n    has {len(likely_sources)} possible sources (ERROR):')
        for f in likely_sources:
            log2(f'  - {f}')
        return 2
    src = likely_sources[0]
    source_list.remove(src)
    if filecmp.cmp(src, dest):
        log(f'. {dest}\n    is same as {src}')
        return 0
    shutil.copyfile(src, dest)
    log2(f'< {dest}\n    updated from {src}')
    return 1


def update_all_files_of_one_type(example_root, dest_dir, extension):
    """
    Every file in dest_list will be replaced by the file with the same
    basename found in source_list
    """

    source_list = get_files(example_root, extension)
    dest_list = get_files(dest_dir, extension)

    log2(f'Update {len(dest_list)} {extension} files')
    log2(f'  from {example_root}')
    log2(f'    to {dest_dir}')
    log(f'     with source list {source_list}')

    nError = 0
    nModified = 0
    nUnchanged = 0
    for dest in dest_list:
        ret = update_one_file(source_list, dest)
        if ret == 0:
            nUnchanged += 1
        elif ret == 1:
            nModified += 1
        elif ret == 2:
            nError += 1

    log2(f'=> {nUnchanged} files unchanged, {nModified} files updated, {nError} errors')

    if len(source_list)>0:
        log2(f'!! WARNING: {len(source_list)} source files are unused')
        for src in source_list:
            log(f'  unused: {src}')


def update_website(website_example_root, ba_example_root, ba_img_dir):
    """
    Updates example scripts and images on website.
    """

    # Start logging
    website_dirpath = os.path.expanduser(website_example_root)
    log_path = os.path.join(website_dirpath, "update.examples.log")
    global flog
    flog = open(log_path, "a")
    print(f'Appending log to {log_path}')
    log(f'\n===\n{datetime.datetime.now().strftime("%d%b%y %H:%M:%S")}')

    # Update scripts
    update_all_files_of_one_type(
        ba_examples_root,
        os.path.join(website_dirpath, "static/files/python"),
        '.py')

    # Update images
    update_all_files_of_one_type(
        ba_img_dir
        os.path.join(website_dirpath, "static/files/simulated"),
        '.png')


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("website_example_root", type=str)
    parser.add_argument("ba_example_root", type=str)
    parser.add_argument("ba_img_dir", type=str)
    args = parser.parse_args()

    update_website(args.website_example_root, args.ba_example_root, args.ba_img_dir)
