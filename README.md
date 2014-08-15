project
======

#### Dependency list (may be incomplete):
* GLEW
* `libglu1-mesa-dev`, `xorg-dev`, `liblua5.1-dev`
* FreeType

#### Build instructions (may not work):

1. `git clone https://github.com/aszkid/glengine`
2. `cd glengine`
3. `mkdir build/arch_gentype_compiler/buildtype`, e.g: `build/64makegcc/debug_static`
4. `cd build/etc...`
5. `cmake ../../../ -DBUILD_SHARED_LIBS=true/false -DCMAKE_BUILD_TYPE=debug/release`
6. `make` (you may want to add `-jX`, where X = number of cores x 1.5)
