#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <general_part.h>
#include <utils.h>
#include <general.h>

void general_part(int cut, char *len_sp, data_t *data, int *count) {
    char *cmem = (char*)malloc((strlen(len_sp)-cut + 1)*sizeof(char));
            strncpy(cmem, len_sp + cut, strlen(len_sp) - cut + 1);
    if (data->boundary != NULL) {
        while (cmem != NULL) {
            char *str;
            char *trade = adj("\n", data->boundary);
            str = scans(trade, cmem);
            free(trade);
            if (str != NULL) {
                trade = (char*)malloc((strlen(strstr(cmem, str))- strlen(str)+1)*sizeof(char));
                strncpy(trade, strstr(cmem, str) + strlen(str), strlen(strstr(cmem, str)) - strlen(str) + 1);
                free(cmem);
                cmem = trade;
                if (strstr((str), data->boundary)) {
                    char *ch = clear(str);
                    if (!strncmp(ch, data->boundary, strlen(data->boundary))) {
                        char *in = (char *) malloc((3 + strlen(str)) * sizeof(char));
                        char *trade_1 = strdup(data->boundary);
                        snprintf(in, strlen(trade_1) + 1, "%s", trade_1);
                        free(trade_1);
                        char *trade_2 = adj(in, "--");
                        free(in);
                        in = trade_2;
                        if (strcmp(ch, in)) {
                             *count = *count + 1;
                        }
                        free(in);
                    }
                    free(str);
                    free(ch);
                }
            } else {
                free(cmem);
                cmem = NULL;
            }
        }
         *count = *count - 1;
    }
    free(cmem);
}
