# u3d-to-stl
[![Build Status](https://travis-ci.org/mradugin/u3d-to-stl.svg?branch=master)](https://travis-ci.org/mradugin/u3d-to-stl)

Simple U3D to STL converter based on sample u3d-parser from [Universal 3D Sample Software](https://sourceforge.net/projects/u3d/)

## Usage
Running `u3d-to-stl my_file.u3d` will produce `my_file_<u3d_mesh_name>.stl` for each CLOD_Mesh_Continuation (0xFFFFFF3B) block.

## Limitations

* Only meshes from CLOD_Mesh_Continuation (0xFFFFFF3B) are supported;
* Only meshes without materials are supported.
