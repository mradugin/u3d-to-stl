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

Obj_path_l := ../../$(Obj_Path)/samples/parsefile
Bin_path_l := ../../$(Bin_Path)
Binary     := u3dparsefile$(Platform)
Objs       := $(Obj_path_l)/u3dparsefile.o \
	      $(Obj_path_l)/block_0x00443355.o \
	      $(Obj_path_l)/block_0xFFFFFF12.o \
	      $(Obj_path_l)/block_0xFFFFFF14.o \
	      $(Obj_path_l)/block_0xFFFFFF15.o \
	      $(Obj_path_l)/block_0xFFFFFF16.o \
	      $(Obj_path_l)/block_0xFFFFFF21.o \
	      $(Obj_path_l)/block_0xFFFFFF22.o \
	      $(Obj_path_l)/block_0xFFFFFF23.o \
	      $(Obj_path_l)/block_0xFFFFFF24.o \
	      $(Obj_path_l)/block_0xFFFFFF31.o \
	      $(Obj_path_l)/block_0xFFFFFF3B.o \
	      $(Obj_path_l)/block_0xFFFFFF3C.o \
	      $(Obj_path_l)/block_0xFFFFFF36.o \
	      $(Obj_path_l)/block_0xFFFFFF3E.o \
	      $(Obj_path_l)/block_0xFFFFFF37.o \
	      $(Obj_path_l)/block_0xFFFFFF3F.o \
	      $(Obj_path_l)/block_0xFFFFFF41.o \
	      $(Obj_path_l)/block_0xFFFFFF42.o \
	      $(Obj_path_l)/block_0xFFFFFF43.o \
	      $(Obj_path_l)/block_0xFFFFFF44.o \
	      $(Obj_path_l)/block_0xFFFFFF45.o \
	      $(Obj_path_l)/block_0xFFFFFF46.o \
	      $(Obj_path_l)/block_0xFFFFFF51.o \
	      $(Obj_path_l)/block_0xFFFFFF52.o \
	      $(Obj_path_l)/block_0xFFFFFF53.o \
	      $(Obj_path_l)/block_0xFFFFFF54.o \
	      $(Obj_path_l)/block_0xFFFFFF55.o \
	      $(Obj_path_l)/block_0xFFFFFF5C.o \
	      $(Obj_path_l)/block_0xFFFFFF56.o

Opts_i32   := -DLINUX32 -D_LINUX32 -D_LINUX -D_PPF
Opts_i32em := -DLINUX32E -D_LINUX32E -D_LINUX -D_EM64T
Opts_i64   := -D_LINUX -DLINUX64 -D_LINUX64 -D_IA64 -D_IPF
Include    := -I../../include -I../../dependencies/include

all: $(Binary)

$(Bin_Path_l):
	mkdir -p $(Bin_Path_l)

$(Obj_path_l):
	mkdir -p $(Obj_path_l)

$(Objs): $(Obj_path_l) u3dparsefile.c
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) u3dparsefile.c -o $(Obj_path_l)/u3dparsefile.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0x00443355.c -o $(Obj_path_l)/block_0x00443355.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF12.c -o $(Obj_path_l)/block_0xFFFFFF12.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF14.c -o $(Obj_path_l)/block_0xFFFFFF14.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF15.c -o $(Obj_path_l)/block_0xFFFFFF15.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF16.c -o $(Obj_path_l)/block_0xFFFFFF16.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF21.c -o $(Obj_path_l)/block_0xFFFFFF21.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF22.c -o $(Obj_path_l)/block_0xFFFFFF22.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF23.c -o $(Obj_path_l)/block_0xFFFFFF23.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF24.c -o $(Obj_path_l)/block_0xFFFFFF24.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF31.c -o $(Obj_path_l)/block_0xFFFFFF31.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF3B.c -o $(Obj_path_l)/block_0xFFFFFF3B.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF3C.c -o $(Obj_path_l)/block_0xFFFFFF3C.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF36.c -o $(Obj_path_l)/block_0xFFFFFF36.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF3E.c -o $(Obj_path_l)/block_0xFFFFFF3E.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF37.c -o $(Obj_path_l)/block_0xFFFFFF37.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF3F.c -o $(Obj_path_l)/block_0xFFFFFF3F.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF41.c -o $(Obj_path_l)/block_0xFFFFFF41.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF42.c -o $(Obj_path_l)/block_0xFFFFFF42.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF43.c -o $(Obj_path_l)/block_0xFFFFFF43.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF44.c -o $(Obj_path_l)/block_0xFFFFFF44.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF45.c -o $(Obj_path_l)/block_0xFFFFFF45.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF46.c -o $(Obj_path_l)/block_0xFFFFFF46.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF51.c -o $(Obj_path_l)/block_0xFFFFFF51.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF52.c -o $(Obj_path_l)/block_0xFFFFFF52.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF53.c -o $(Obj_path_l)/block_0xFFFFFF53.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF54.c -o $(Obj_path_l)/block_0xFFFFFF54.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF55.c -o $(Obj_path_l)/block_0xFFFFFF55.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF5C.c -o $(Obj_path_l)/block_0xFFFFFF5C.o
	$(CC) -shared -c $(Include) $(Opts_$(Platform)) block_0xFFFFFF56.c -o $(Obj_path_l)/block_0xFFFFFF56.o

$(Binary) : $(Objs)
	$(CC) $(Objs) -L../../dependencies/lib -lxml2 -L../../bin -lu3dparser$(Platform) -lu3ddecoder$(Platform) -lu3dhistogramdynamic$(Platform) -lc -lwsock32 -o $(Bin_path_l)/$(Binary)

clean:
	echo ...Cleaning File parser...
	-rm -f $(Objs) $(Bin_path_l)/$(Binary)*
