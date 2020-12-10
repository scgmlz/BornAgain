%pythoncode %{
import warnings
def deprecated(message):
  def deprecated_decorator(func):
      def deprecated_func(*args, **kwargs):
          warnings.simplefilter('always', DeprecationWarning)  # turn off filter
          warnings.warn("{} is a deprecated function. {}".format(func.__name__, message),
                        category=DeprecationWarning,
                        stacklevel=2)
          warnings.simplefilter('default', DeprecationWarning)  # reset filter
          return func(*args, **kwargs)
      return deprecated_func
  return deprecated_decorator
%}
