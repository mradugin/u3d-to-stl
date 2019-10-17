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
Binary     := libu3ddecoder$(Platform)
Objs       := $(Obj_Path_l)/decoderctx.o $(Obj_Path_l)/decodercompctx.o \
	      $(Obj_Path_l)/decodergetu64.o $(Obj_Path_l)/decodergetu32.o \
	      $(Obj_Path_l)/decodergetu16.o $(Obj_Path_l)/decodergetu8.o \
	      $(Obj_Path_l)/decodergetdynamiccompu32.o \
	      $(Obj_Path_l)/decodergetdynamiccompu16.o \
	      $(Obj_Path_l)/decodergetdynamiccompu8.o \
	      $(Obj_Path_l)/decodergetstaticcompu32.o \
	      $(Obj_Path_l)/decodergetstaticcompu16.o \
	      $(Obj_Path_l)/decodergetstaticcompu8.o \
	      $(Obj_Path_l)/decodergetarrayu32.o $(Obj_Path_l)/decodesymbol.o


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

$(Objs): $(Obj_Path_l) ./src/decoderctx.c ./src/decodercompctx.c \
		./src/decodergetu64.c ./src/decodergetu32.c \
		./src/decodergetu16.c ./src/decodergetu8.c \
        ./src/decodergetdynamiccompu32.c ./src/decodergetdynamiccompu16.c ./src/decodergetdynamiccompu8.c \
        ./src/decodergetstaticcompu32.c ./src/decodergetstaticcompu16.c ./src/decodergetstaticcompu8.c \
		./src/decodesymbol.c
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decoderctx.c -o $(Obj_Path_l)/decoderctx.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodercompctx.c -o $(Obj_Path_l)/decodercompctx.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetu64.c -o $(Obj_Path_l)/decodergetu64.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetu32.c -o $(Obj_Path_l)/decodergetu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetu16.c -o $(Obj_Path_l)/decodergetu16.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetu8.c -o $(Obj_Path_l)/decodergetu8.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetdynamiccompu32.c -o $(Obj_Path_l)/decodergetdynamiccompu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetdynamiccompu16.c -o $(Obj_Path_l)/decodergetdynamiccompu16.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetdynamiccompu8.c -o $(Obj_Path_l)/decodergetdynamiccompu8.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetstaticcompu32.c -o $(Obj_Path_l)/decodergetstaticcompu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetstaticcompu16.c -o $(Obj_Path_l)/decodergetstaticcompu16.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetstaticcompu8.c -o $(Obj_Path_l)/decodergetstaticcompu8.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodergetarrayu32.c -o $(Obj_Path_l)/decodergetarrayu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/decodesymbol.c -o $(Obj_Path_l)/decodesymbol.o

$(Binary): $(Objs) $(Bin_Path_l)
	ar -scr $(Bin_Path_l)/$(Binary).a $(Objs)
#	gcc -shared -o $(Bin_Path_l)/$(Binary).so $(Objs) -L $(Bin_Path_l) -l u3dhistogramdynamic$(Platform)

clean:
	echo ...Cleaning bitdecoder...
	-rm -f $(Objs) $(Bin_Path_l)/$(Binary).*
