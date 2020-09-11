[JWu 6jul20]

These two demo programs were previous located in
- GUI/ba3d/demo,
- GUI/ba3d/showcase.

I moved them out of the BornAgain source tree in order to comply
with general practice, to accelerate compilation, and to prepare
for tighter integration of the real-space viewer.

I did not adapt the CMakeLists.txt files. Therefore, the two demo
programs will not build without extra configuration effort.

TODO:
- Either make them build again;
- Or remove them for good.
