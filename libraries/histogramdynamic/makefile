#***************************************************************************
#
#  Copyright (c) 2006 Intel Corporation
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#***************************************************************************

include ../../makefile.def

Obj_Path_l := ../../$(Obj_Path)/lib
Bin_Path_l := ../../$(Bin_Path)
Binary     := libu3dhistogramdynamic$(Platform)
Objs       := $(Obj_Path_l)/histogramdynamic.o $(Obj_Path_l)/histogramget.o \
              $(Obj_Path_l)/histogramadd.o

Opts_i32   := -DLINUX32 -D_LINUX32 -D_LINUX -D_PPF
Opts_i32em := -DLINUX32E -D_LINUX32E -D_LINUX -D_EM64T
Opts_i64   := D_LINUX -DLINUX64 -D_LINUX64 -D_IA64 -D_IPF
Include    := -I../../include -I./

.SUFFIXES: .c

all: $(Binary)

$(Bin_Path_l):
	mkdir -p $(Bin_Path_l)

$(Obj_Path_l):
	mkdir -p $(Obj_Path_l)

$(Objs): $(Obj_Path_l) ./src/histogramdynamic.c ./src/histogramget.c ./src/histogramadd.c
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/histogramdynamic.c -o $(Obj_Path_l)/histogramdynamic.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/histogramget.c -o $(Obj_Path_l)/histogramget.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/histogramadd.c -o $(Obj_Path_l)/histogramadd.o

$(Binary): $(Bin_Path_l) $(Objs)
	ar scr $(Bin_Path_l)/$(Binary).a $(Objs)
#	gcc -shared -o $(Bin_Path_l)/$(Binary).so $(Objs)

clean:
	echo ...Cleaning dynamic histogram...
	-rm -f $(Objs) $(Bin_Path_l)/$(Binary).*
