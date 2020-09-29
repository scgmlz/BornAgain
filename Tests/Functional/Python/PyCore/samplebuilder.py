import sys, unittest, ctypes
import inspect

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba


initial_width = 42
initial_length = 42


class SampleBuilder(ba.ISampleBuilder):
    """
    Test class with one registered parameter and onChange() counter
    """
    def __init__(self):
        super(SampleBuilder, self).__init__()

        self.m_onchange_counter = 0

        self.m_width = ctypes.c_double(initial_width)
        self.registerParameter("width", ctypes.addressof(self.m_width))

    def onChange(self):
        self.m_onchange_counter += 1


class BuilderPrototype(ba.ISampleBuilder):
    """
    Prototype demonstrating new way of parameter registration
    """
    def __init__(self):
        super(BuilderPrototype, self).__init__()

        self.m_onchange_counter = 0

        self.m_length = 42
        self.register_prototype("length", "self.m_length")

    def onChange(self):
        self.m_onchange_counter += 1
        # update all class members with values from ctypes wrappers
        for key, value in self.__dict__.items():
            if "wrapper_" in key:
                original_key = key.split("wrapper_", 1).pop()
                self.__dict__[original_key] = value.value

    def register_prototype(self, par_name, var_key):
        var_key = var_key.split("self.", 1).pop()
        if not var_key in self.__dict__:
            raise Exception("Can't find variable self."+var_key+" in given class")
        # defining the name for new ctype variable and creating dynamic attribute
        wrapper_key = "wrapper_"+var_key
        setattr(self, wrapper_key, ctypes.c_double(self.__dict__.get(var_key)))
        # registering new attribute in BornAgain
        self.registerParameter(par_name, ctypes.addressof(getattr(self, wrapper_key)))


class SampleBuilderTest(unittest.TestCase):

    def test_registerParameters(self):
        """
        Checking parameter registration and setting the value.
        """
        builder = SampleBuilder()

        self.assertEqual(builder.m_width.value, initial_width)
        builder.setParameterValue("width", 43.0)
        self.assertEqual(builder.m_width.value, 43.0)

    def test_parameterString(self):
        """
        Checking that parameterString() function is correctly exposed to Python
        """
        par_str = SampleBuilder().parametersToString()
        self.assertEqual(par_str, "'/SampleBuilder/width':42\n\n")

    def test_onChange(self):
        """
        Checking that onChange is triggered once when parameter is changed
        """
        builder = SampleBuilder()
        self.assertEqual(builder.m_onchange_counter, 0)
        builder.setParameterValue("width", 43.0)
        self.assertEqual(builder.m_onchange_counter, 1)
        builder.setParameterValue("width", 44.0)
        self.assertEqual(builder.m_onchange_counter, 2)

        # setting same value, onChange shouldn't be triggered
        builder.setParameterValue("width", 44.0)
        self.assertEqual(builder.m_onchange_counter, 2)

    def test_registerPrototype(self):
        builder = BuilderPrototype()

        self.assertEqual(builder.m_onchange_counter, 0)
        self.assertEqual(builder.m_length, initial_length)

        builder.setParameterValue("length", 43.0)
        self.assertEqual(builder.m_length, 43.0)
        self.assertEqual(builder.m_onchange_counter, 1)


if __name__ == '__main__':
    unittest.main()
