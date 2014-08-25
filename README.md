project
======

#### Dependency list (may be incomplete):
* GLEW
* `libglu1-mesa-dev`, `xorg-dev`, `liblua5.2-dev`
* FreeType

#### Build instructions (may not work):

1. `git clone https://github.com/aszkid/glengine`
2. `cd glengine`
3. `mkdir build/arch_gentype_compiler/buildtype`, e.g: `build/64makegcc/debug_static`
4. `cd build/etc...`
5. `cmake ../../../ -DBUILD_SHARED_LIBS=true/false -DCMAKE_BUILD_TYPE=debug/release`
6. `make` (you may want to add `-jX`, where X = number of cores x 1.5)

#### Debugging tips:

First get in the compilation/bin directory.

To *DEBUG* the application: `valgrind --suppressions=../../../rundir/val.supp --leak-check=full ./milsim`.

To *PROFILE* the application `valgrind --tool=callgrind ./milsim` and then `kcachegrind` if you want nice GUI profiling result visualization.
