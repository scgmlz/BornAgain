// unproblematic warnings, keep them permanently disabled:
#pragma SWIG nowarn=314 // print conflicts with Python, renamed to _print
#pragma SWIG nowarn=315 // nothing known about std::size_t
#pragma SWIG nowarn=362 // operator= ignored
#pragma SWIG nowarn=389 // operator[] ignored, consider %extend
#pragma SWIG nowarn=503 // operator= ignored, consider renaming to valid identifier

// questionable warnings, complicated machinery -> reinvestigate later
#pragma SWIG nowarn=473 // return pointer from director
#pragma SWIG nowarn=509 // overloaded method shadowed
#pragma SWIG nowarn=520 // base class not marked as shared_ptr (allow for ISampleBuilder)
