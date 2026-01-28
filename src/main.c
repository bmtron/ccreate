#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "templates.h"

#define NEW_PROJECT_CMD "new"
#define MAX_PROJECT_NAME_SIZE 128 - 6 - 9

int main(int argc, char** argv) {
        if (argc > 1 && strcmp(argv[1], NEW_PROJECT_CMD) == 0) {
                if (argc < 3) {
                        printf("Usage: ccreate new <project_name>\n");
                        return 1;
                }
                char* project_name = argv[2];
                char src_path[128];
                int str_end = strlen(project_name);
                if (str_end >= MAX_PROJECT_NAME_SIZE) {
                        printf(
                            "Project name too long. Why are you making your "
                            "project name more than 113 characters??\n");
                        return 1;
                }

                int dir_success = mkdir(project_name, 0755);
                if (dir_success != 0) {
                        printf("Error making dir: %s\n", project_name);
                        perror("mkdir");
                        return 1;
                }

                char makefile_buf[256];
                sprintf(makefile_buf, "%s/Makefile", project_name);
                FILE* makef = fopen(makefile_buf, "w");
                if (makef == NULL) {
                        printf("Error creating file: %s\n", makefile_buf);
                        perror("fopen");
                        return -1;
                }
                int file_write_success =
                    fprintf(makef, getMakefileTemplate(), project_name);
                if (file_write_success < 0) {
                        printf("Error writing file: %s\n", makefile_buf);
                        perror("fprintf");
                        return -1;
                }

                sprintf(src_path, "%s/src", project_name);

                dir_success = mkdir(src_path, 0755);
                if (dir_success != 0) {
                        printf("Error making dir: %s\n", src_path);
                        perror("mkdir");
                        return 1;
                }

                char mainfile_buf[256];
                sprintf(mainfile_buf, "%s/main.c", src_path);
                FILE* mainf = fopen(mainfile_buf, "w");
                if (mainf == NULL) {
                        printf("Error creating file: %s\n", src_path);
                        perror("fopen");
                        return -1;
                }
                file_write_success = fputs(getMainTemplate(), mainf);
                if (file_write_success < 0) {
                        printf("Error writing file: %s\n", src_path);
                        perror("fprintf");
                        return -1;
                }
                fclose(makef);
                fclose(mainf);
        }

        printf("CCREATOR\n");
        return 0;
}
