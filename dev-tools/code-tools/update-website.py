"""
To update examples on website:

1) Run in your build directory
ctest -R PyExamples
This will run all existing examples and generate intensity images for web site.

2) Modify variables in this script
WEBSITE_DIR, BORNAGAIN_SOURCE, EXAMPLE_IMAGES

3) Run this script
python update-examples.py

TODO: move the script under ctest control
"""
import os
import shutil

WEBSITE_DIR = "/home/pospelov/development/BornAgain-website"
BORNAGAIN_SOURCE = "/home/pospelov/development/BornAgainHub/BornAgain"
EXAMPLE_IMAGES = "/home/pospelov/development/BornAgainHub/build/test_output/Functional/Python/PyExamples"


def copy_file_to_file(source, destination):
    """
    Copies file to another.
    """
    shutil.copyfile(source, destination)


def find_files(dir_name):
    """
    Yield recursive list of files in given dir_name
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


def copy_files(source_list, destination_list):
    """
    Every file in destination_list will be replaced by the file with the same
    basename found in source_list
    """
    missed_files = []
    updated_files = []
    for f in destination_list:
        found_source = find_files_with_same_name(source_list, os.path.basename(f))
        if len(found_source) == 1:
            updated_files.append(f)
            copy_file_to_file(found_source[0], f)
        else:
            print(len(found_source), "Problem with ", f)
            missed_files.append(f)

    print("Summary:")

    print("Following files have been updated on website:")
    for f in updated_files:
        print(f)

    if len(missed_files):
        print("Following files exist on website but not in source dir:")
        for f in missed_files:
            print(f)


def update_example_images():
    """
    Copies example intensity images from build directory to website directory
    """
    website = os.path.join(WEBSITE_DIR, "content/documentation/sample-models")
    source = EXAMPLE_IMAGES
    website_files = get_files(website, ".png")
    source_files = get_files(source, ".png")

    copy_files(source_files, website_files)


def update_example_scripts():
    """
    Copies example scripts from BornAgain directory to website directory
    """
    website = os.path.join(WEBSITE_DIR, "static/files/python")
    source = os.path.join(BORNAGAIN_SOURCE, "Examples/python")
    website_files = get_files(website, ".py")
    source_files = get_files(source, ".py")

    copy_files(source_files, website_files)


def update_website():
    update_example_images()
    update_example_scripts()


if __name__ == '__main__':
    update_website()

