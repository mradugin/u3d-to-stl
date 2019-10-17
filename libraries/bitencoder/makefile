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
Binary     := libu3dencoder$(Platform)
Objs       := $(Obj_Path_l)/encoderctx.o $(Obj_Path_l)/encodercompctx.o \
	      $(Obj_Path_l)/encoderaddu64.o $(Obj_Path_l)/encoderaddu32.o \
	      $(Obj_Path_l)/encoderaddu16.o $(Obj_Path_l)/encoderaddu8.o \
	      $(Obj_Path_l)/encoderadddynamiccompu32.o \
	      $(Obj_Path_l)/encoderadddynamiccompu16.o \
	      $(Obj_Path_l)/encoderadddynamiccompu8.o \
	      $(Obj_Path_l)/encoderaddstaticcompu32.o \
	      $(Obj_Path_l)/encoderaddstaticcompu16.o \
	      $(Obj_Path_l)/encoderaddstaticcompu8.o \
	      $(Obj_Path_l)/encoderaddstring.o \
	      $(Obj_Path_l)/encoderaddarrayu32.o \
	      $(Obj_Path_l)/encodesymbol.o

Opts_i32   := -DLINUX32 -D_LINUX32 -D_LINUX -D_PPF
Opts_i32em := -DLINUX32E -D_LINUX32E -D_LINUX -D_EM64T
Opts_i64   := -D_LINUX -DLINUX64 -D_LINUX64 -D_IA64 -D_IPF
Include    := -I../../include -I./

.SUFFIXES: .c

all: $(Binary)

$(Bin_Path_l):
	mkdir -p $(Bin_Path_l)

$(Obj_Path_l):
	mkdir -p $(Obj_Path_l)

$(Objs): $(Obj_Path_l) ./src/encoderctx.c ./src/encodercompctx.c \
	./src/encoderaddu64.c ./src/encoderaddu32.c ./src/encoderaddu16.c \
	./src/encoderaddu8.c ./src/encoderaddstring.c \
	./src/encoderadddynamiccompu32.c \
	./src/encoderadddynamiccompu16.c \
	./src/encoderadddynamiccompu8.c \
	./src/encoderaddstaticcompu32.c \
	./src/encoderaddstaticcompu16.c \
	./src/encoderaddstaticcompu8.c \
	./src/encoderaddarrayu32.c \
	./src/encodesymbol.c
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderctx.c -o $(Obj_Path_l)/encoderctx.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encodercompctx.c -o $(Obj_Path_l)/encodercompctx.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddu64.c -o $(Obj_Path_l)/encoderaddu64.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddu32.c -o $(Obj_Path_l)/encoderaddu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddu16.c -o $(Obj_Path_l)/encoderaddu16.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddu8.c -o $(Obj_Path_l)/encoderaddu8.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderadddynamiccompu32.c -o $(Obj_Path_l)/encoderadddynamiccompu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderadddynamiccompu16.c -o $(Obj_Path_l)/encoderadddynamiccompu16.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderadddynamiccompu8.c -o $(Obj_Path_l)/encoderadddynamiccompu8.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddstaticcompu32.c -o $(Obj_Path_l)/encoderaddstaticcompu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddstaticcompu16.c -o $(Obj_Path_l)/encoderaddstaticcompu16.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddstaticcompu8.c -o $(Obj_Path_l)/encoderaddstaticcompu8.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddstring.c -o $(Obj_Path_l)/encoderaddstring.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encoderaddarrayu32.c -o $(Obj_Path_l)/encoderaddarrayu32.o
	$(CC) -c $(Include) $(Opts_$(Platform)) ./src/encodesymbol.c -o $(Obj_Path_l)/encodesymbol.o

$(Binary): $(Objs) $(Bin_Path_l)
	ar scr $(Bin_Path_l)/$(Binary).a $(Objs)
#	gcc -shared -o $(Bin_Path_l)/$(Binary).so -L../../bin $(Objs) -lu3dhistogramdynamic$(Platform)

clean:
	echo ...Cleaning bitencoder...
	-rm -f $(Objs) $(Bin_Path_l)/$(Binary).*
