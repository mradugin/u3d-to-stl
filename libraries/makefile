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

all: u3dhistogramdynamic u3dbitdecoder u3dbitencoder u3dparser

clean:
	@echo Cleaning libraries...
	@make -s -C ./parser $@
	@make -s -C ./bitdecoder $@
	@make -s -C ./bitencoder $@
	@make -s -C ./histogramdynamic $@

u3dparser:
	@echo ...build parser...
	@make -s -C ./parser

u3dbitdecoder:
	@echo ...build bitdecoder...
	@make -s -C ./bitdecoder

u3dbitencoder:
	@echo ...build bitencoder...
	@make -s -C ./bitencoder

u3dhistogramdynamic:
	@echo ...build dynamic histogram...
	@make -s -C ./histogramdynamic
