We support different flavors of Doxygen documentation:

- "user", the BornAgain user API
- "long", full C++ source documentation for developers
- "dirgraphs", for analysing include dependences

To build the documentation,
```
cd build
# configure:
cmake -DBORNAGAIN_CONFIGURE_DOXY=ON ..
# make:
make doxyuser # other make targets are 'doxylong' etc,
              # or 'doxy' to build all available flavors
```

The configure step writes Doxyfiles to the directory
`<build>/doxygen`. Do not edit these files.

The make step writes the documentation to directories
`<build>/html/user` etc.
