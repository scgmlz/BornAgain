We support different flavors of Doxygen documentation:

- "user", the BornAgain user API
- "long", full C++ source documentation for developers

To build the documentation,
```
cd build
# configure:
cmake -DBORNAGAIN_CONFIGURE_DOXY=ON ..
# make:
make doxyuser
make doxylong
make doxy     # to build both flavors
```

The configure step writes Doxyfiles to the directory
`<build>/doxygen`. Do not edit these files.

The make step writes the documentation to directories
`<build>/html/user`, `<build>/html/long`.
