#ifndef STL_H
#define STL_H

#include "u3ddefs.h"

typedef struct
{
    F32 pos[3];
    F32 normal[3];
} Corner;

typedef struct
{
    Corner corners[3];
} Face;

void STL_SaveFacesToFile(Face* faces, U32 count, const char *filename, const char *name);
char* STL_GetFilename(char* dest, size_t size, const char* u3d_filename, const char* body_name);

#endif
