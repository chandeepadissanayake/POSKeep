#include "fileutils.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Returns the number of the lines in the given file.
 */
int _poskeep_count_lines_file(char* file_path) {
    FILE *fp;
    fp = fopen(file_path, "r");

    if (fp != NULL) {
        int ch = 0;
        int lines_count = 1;
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '\n') {
                lines_count++;
            }
        }
        fclose(fp);

        return lines_count;
    }
    else {
        return 0;
    }
}
