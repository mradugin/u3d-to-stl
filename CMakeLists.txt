cmake_minimum_required(VERSION 3.0)
project(u3d-to-stl)

find_package(LibXml2 REQUIRED)

set(SOURCES
    ./include/u3dthreadingdefs.h
    ./include/u3dbitencoder.h
    ./include/u3dbitdecoder.h
    ./include/u3dhistogram.h
    ./include/u3dblocktypes.h
    ./include/u3dfilestr.h
    ./include/u3ddefs.h
    ./include/u3dparser.h
    ./libraries/histogramdynamic/src/histogramdynamic.c
    ./libraries/histogramdynamic/src/histogramget.c
    ./libraries/histogramdynamic/src/histogramdynamic.h
    ./libraries/histogramdynamic/src/histogramadd.c
    ./libraries/bitencoder/src/encoderaddstaticcompu16.c
    ./libraries/bitencoder/src/encoderaddu8.c
    ./libraries/bitencoder/src/encoderaddu32.c
    ./libraries/bitencoder/src/encoderadddynamiccompu8.c
    ./libraries/bitencoder/src/encodercompctx.c
    ./libraries/bitencoder/src/encoderadddynamiccompu32.c
    ./libraries/bitencoder/src/encoderaddu16.c
    ./libraries/bitencoder/src/encoderaddarrayu32.c
    ./libraries/bitencoder/src/encodesymbol.c
    ./libraries/bitencoder/src/encoderaddstaticcompu32.c
    ./libraries/bitencoder/src/encoderctx.h
    ./libraries/bitencoder/src/encoderaddstaticcompu8.c
    ./libraries/bitencoder/src/encoderctx.c
    ./libraries/bitencoder/src/encoderadddynamiccompu16.c
    ./libraries/bitencoder/src/encoderaddstring.c
    ./libraries/bitencoder/src/encoderaddu64.c
    ./libraries/bitdecoder/src/decodergetdynamiccompu16.c
    ./libraries/bitdecoder/src/decodergetdynamiccompu32.c
    ./libraries/bitdecoder/src/decodergetu32.c
    ./libraries/bitdecoder/src/decodergetstaticcompu8.c
    ./libraries/bitdecoder/src/decodergetu8.c
    ./libraries/bitdecoder/src/decodergetstaticcompu16.c
    ./libraries/bitdecoder/src/decodergetu16.c
    ./libraries/bitdecoder/src/decodesymbol.c
    ./libraries/bitdecoder/src/decoderctx.c
    ./libraries/bitdecoder/src/decoderctx.h
    ./libraries/bitdecoder/src/decodergetarrayu32.c
    ./libraries/bitdecoder/src/decodergetdynamiccompu8.c
    ./libraries/bitdecoder/src/decodergetstaticcompu32.c
    ./libraries/bitdecoder/src/decodergetu64.c
    ./libraries/bitdecoder/src/decodercompctx.c
    ./libraries/parser/src/u3dfilestr.c
    ./libraries/parser/src/u3dctx.c
    ./libraries/parser/src/u3dpipeline.c
    ./libraries/parser/src/u3dpipeline.h
    ./libraries/parser/src/u3dctx.h
    ./samples/parsefile/block_0xFFFFFF53.c
    ./samples/parsefile/block_0xFFFFFF22.c
    ./samples/parsefile/block_0xFFFFFF3F.c
    ./samples/parsefile/block_0xFFFFFF5C.c
    ./samples/parsefile/block_0xFFFFFF52.c
    ./samples/parsefile/block_0xFFFFFF45.c
    ./samples/parsefile/block_0xFFFFFF16.c
    ./samples/parsefile/block_0xFFFFFF51.c
    ./samples/parsefile/u3dparsefile.c
    ./samples/parsefile/block_0xFFFFFF3E.c
    ./samples/parsefile/block_0xFFFFFF3B.c
    ./samples/parsefile/block_0xFFFFFF15.c
    ./samples/parsefile/block_0xFFFFFF36.c
    ./samples/parsefile/block_0xFFFFFF54.c
    ./samples/parsefile/block_0xFFFFFF46.c
    ./samples/parsefile/block_0xFFFFFF12.c
    ./samples/parsefile/block_0xFFFFFF14.c
    ./samples/parsefile/block_0xFFFFFF37.c
    ./samples/parsefile/block_0xFFFFFF56.c
    ./samples/parsefile/block_0xFFFFFF23.c
    ./samples/parsefile/block_0xFFFFFF21.c
    ./samples/parsefile/block_0x00443355.c
    ./samples/parsefile/block_0xFFFFFF31.c
    ./samples/parsefile/block_0xFFFFFF44.c
    ./samples/parsefile/block_0xFFFFFF43.c
    ./samples/parsefile/block_0xFFFFFF3C.c
    ./samples/parsefile/block_0xFFFFFF24.c
    ./samples/parsefile/block_0xFFFFFF55.c
    ./samples/parsefile/u3dparsefile.h
    ./samples/parsefile/block_0xFFFFFF42.c
    ./samples/parsefile/block_0xFFFFFF41.c
)

SET (INCLUDE_DIRS
    ./include
    ./libraries/histogramdynamic/src
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${LIBXML2_INCLUDE_DIR} ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${LIBXML2_LIBRARIES})
