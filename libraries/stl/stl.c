#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <libgen.h>

#include "stl.h"

void STL_SaveFacesToFile(Face* faces, U32 count, const char* filename, const char* name)
{
    FILE* f = fopen(filename, "w+");
    if (f)
    {
        fprintf(f, "solid %s\n", name);
        for (U32 index = 0; index < count; ++index)
        {
            F32 face_normal[3] = {};
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    face_normal[i] += faces[index].corners[j].normal[i];
                }
                face_normal[i] /= 3.0f;
            }

            fprintf(f, "\tfacet normal %f %f %f\n",
                    face_normal[0], face_normal[1], face_normal[2]);


            fprintf(f, "\t\touter loop\n");

            for (int i = 0; i < 3; ++i)
            {
                fprintf(f, "\t\t\tvertex %f %f %f\n",
                        faces[index].corners[i].pos[0],
                        faces[index].corners[i].pos[1],
                        faces[index].corners[i].pos[2]
                        );
            }

            fprintf(f, "\t\tendloop\n");
            fprintf(f, "\tendfacet\n");
        }
        fclose(f);
    }
}

char *STL_GetFilename(char *dest, size_t size, const char *u3d_filename, const char *body_name)
{
    char temp[PATH_MAX] = {};
    strncpy(temp, u3d_filename, sizeof(temp) - 1);

    char* bn = basename(temp);
    char* dir = dirname(temp);
    char* ext = strchr(bn, '.');
    if (ext != NULL)
    {
        *ext = 0;
    }
    snprintf(dest, size, "%s/%s_%s.stl", dir, bn, body_name);
    return dest;
}
