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
import click


WEBSITE_DIR = "~/development/BornAgain/BornAgain-website"
BORNAGAIN_SOURCE = "~/development/BornAgain/BornAgain"
BUILD_DIR = "~/development/BornAgain/build-release/"


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


def update_example_images(website_dir, example_images):
    """
    Copies example intensity images from build directory to website directory
    """
    website = os.path.join(website_dir, "content/documentation/examples")
    source = example_images
    website_files = get_files(website, ".png")
    source_files = get_files(source, ".png")

    copy_files(source_files, website_files)


def update_example_scripts(website_dir, bornagain_source):
    """
    Copies example scripts from BornAgain directory to website directory
    """
    website = os.path.join(website_dir, "static/files/python")
    source = os.path.join(bornagain_source, "Examples/python")
    website_files = get_files(website, ".py")
    source_files = get_files(source, ".py")
    print(website_files)

    copy_files(source_files, website_files)


@click.command()
@click.argument("website_dir", required=False, type=str, default=WEBSITE_DIR)
@click.argument("bornagain_source", required=False, type=str, default=BORNAGAIN_SOURCE)
@click.argument("build_dir", required=False, type=str, default=BUILD_DIR)
def update_website(website_dir, bornagain_source, build_dir):
    user_website_dir = os.path.expanduser(website_dir)
    user_bornagain_source = os.path.expanduser(bornagain_source)
    user_build_dir = os.path.expanduser(build_dir)
    user_example_images = os.path.join(user_build_dir, "test_output/Functional/Python/PyExamples")

    print("website_dir      : '{}'".format(user_website_dir))
    print("bornagain_source      : '{}'".format(user_bornagain_source))
    print("build_dir      : '{}'".format(user_build_dir))
    print("example_images      : '{}'".format(user_example_images))

    update_example_images(user_website_dir, user_example_images)
    update_example_scripts(user_website_dir, user_bornagain_source)


if __name__ == '__main__':
    update_website()

