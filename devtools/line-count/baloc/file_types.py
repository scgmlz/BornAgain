"""
Contains machinery to convert BornAgain filename to the type of the content
"""

class FileTypes:
    """
    Enumerator class to hold file types
    """
    CORE, FTEST, UTEST, PYCODE, MACROS, GUI, PYAPI, THIRD, UNDEF, TOTAL = range(10)
    descr=["Core", "Functional Tests", "Unit Tests", "*.py", "macros", "GUI", "PythonAPI", "Third", "Undef"]
    @staticmethod
    def loc_for_type():
        result = []
        for i in range(FileTypes.TOTAL):
            result.append(0)
        return result


def filePython(x):
    if ".py" in x and not ".pypp." in x: return True
    return False


def fileCpp(x):
    if ".h" in x or ".cpp" in x: return True
    return False


def dirCore(x):
    # if "/Core/Algorithms" in x: return True
    # if "/Core/FormFactors" in x: return True
    # if "/Core/Samples" in x: return True
    # if "/Core/StandardSamples" in x: return True
    # if "/Core/Tools" in x: return True
    # if "/Core/Fitting" in x: return True
    # if "/Core/inc" in x: return True
    # if "/Core/src" in x: return True
    # if "/Core/InputOutput" in x: return True
    # if "/Core/Geometry" in x: return True
    # if "/Fit/Factory" in x: return True
    # if "/Fit/FitKernel" in x: return True
    # if "/Fit/StandardFits" in x: return True
    # if "/Core/Geometry" in x: return True
    if "/Core/" in x: return True
    if "/Fit/" in x: return True

    return False


def dirPyAPI(x):
    if "/Core/PythonAPI" in x: return True
    if "/Fit/PythonAPI" in x: return True
    return False


def dirFuncTest(x):
    # if "/App/" in x: return True
    if "/Tests/Functional" in x: return True
    if "/Tests/PerformanceTests" in x: return True
    if "/Tests/FunctionalTests/TestCore" in x: return True
    if "/Tests/FunctionalTests/TestFit" in x: return True
    if "/Tests/FunctionalTests/TestPyCore" in x: return True
    if "/Tests/FunctionalTests/TestPyFit" in x: return True
    if "/Core/TestMachinery" in x: return True
    return False


def dirGUI(x):
    if "/GUI/coregui" in x  and not "widgetbox" in x and not "qttools" in x: return True
    if "/GUI/main" in x: return True
    if "/AppGUI/coregui" in x: return True
    if "/BASuite" in x: return True
    return False


def dirThirdParty(x):
    if "/ThirdParty" in x: return True
    return False


def dirSkip(x):
    if "/pub/core" in x: return True
    return False


def dirUnitTests(x):
    if "/UnitTests/" in x: return True
    if "/Tests/UnitTests/TestCore/" in x: return True
    if "/Tests/UnitTests/TestFit/" in x: return True
    if "/Tests/UnitTests/" in x: return True
    return False


def filetype(x):
    """
    Returns type of file
    """
    result = FileTypes.UNDEF

    if dirSkip(x):
        return result

    if dirPyAPI(x):
        result = FileTypes.PYAPI

    elif dirThirdParty(x):
        result = FileTypes.THIRD

    elif (fileCpp(x) or filePython(x)) and dirFuncTest(x):
        result = FileTypes.FTEST

    elif fileCpp(x) and dirCore(x):
        result = FileTypes.CORE

    elif dirUnitTests(x):
        result = FileTypes.UTEST

    elif dirGUI(x):
        result = FileTypes.GUI

    return result

