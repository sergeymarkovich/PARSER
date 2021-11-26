#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <print.h>
#include <utils.h>

void print(data_t *data, int count) {
     if (data->from != NULL) {
        if (data->from[0] == ' ') {
            char *trade = (char*)malloc((strlen(data->from)+1)*sizeof(char));
            strncpy(trade, data->from+1, strlen(data->from)+1);
            free(data->from);
            data->from = trade;
        }
        printf("%s", data->from);
    }
    printf("|");
    if (data->to != NULL) {
        if (data->to[0] == ' ') {
            char *trade = (char*)malloc((strlen(data->to) + 1)*sizeof(char));
            strncpy(trade, data->to + 1, strlen(data->to) + 1);
            free(data->to);
            data->to = trade;
        }
        printf("%s", data->to);
    }
    printf("|");
    if (data->date != NULL) {
        if (data->date[0] == ' ') {
            char *trade = (char*)malloc((strlen(data->date)+1)*sizeof(char));
            strncpy(trade, data->date+1, strlen(data->date)+1);
            free(data->date);
            data->date = trade;
        }
        printf("%s", data->date);
    }
    printf("|");
    printf("%d", count);
    free(data->from);
    free(data->to);
    free(data->boundary);
    free(data->date);
}
