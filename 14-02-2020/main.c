#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    int people_born;

}month;

int main(int argc, char *argv[]) {
    int flag = 0;
    int wanted_month = -1;

    if(argc == 4) {
        if(strcmp("-m", argv[2]) == 0 || strcmp("-M", argv[2]) == 0) {
            flag = 1;
            wanted_month = *argv[3] - '0';
        }
    }

    else if(argc != 2) {
        printf("Numero di argomenti non corretto");
        exit(-1);
    }

    month months[12];

    // Set months names
    strcpy(months[0].name, "Gennaio");
    strcpy(months[1].name, "Febbraio");
    strcpy(months[2].name, "Marzo");
    strcpy(months[3].name, "Aprile");
    strcpy(months[4].name, "Maggio");
    strcpy(months[5].name, "Giugno");
    strcpy(months[6].name, "Luglio");
    strcpy(months[7].name, "Agosto");
    strcpy(months[8].name, "Settembre");
    strcpy(months[9].name, "Ottobre");
    strcpy(months[10].name, "Novembre");
    strcpy(months[11].name, "Dicembre");

    for(int i = 0; i < 12; i++) {
        // Set default
        months[i].people_born = 0;
    }

    FILE* fp = fopen(argv[1], "r");

    if(fp == NULL) {
        exit(-1);
    }

    char name[29];
    char surname[29];
    char city[29];
    int date_month;
    int tmp_day;
    int tmp_year;

    FILE *fo;

    if(flag) {
        char filename[10];
        strcpy(filename, months[wanted_month - 1].name);
        fo = fopen(strcat(filename, ".txt"), "w");
    }

    int c = 0;
    while(!feof(fp)) {
        fscanf(fp, "%s %s %s %d/%d/%d", name, surname, city, &tmp_day, &date_month, &tmp_year);

        if(flag && (date_month == wanted_month)) {
            fprintf(fo, "%s %s %s\n", name, surname, city);
        }

        months[date_month - 1].people_born = months[date_month - 1].people_born + 1;
        c++;
    }
    fclose(fp);

    if(flag && (fo != NULL)) {
        fclose(fo);
    }

    int max_people_born = -1;
    char max_people_month[10];
    int tot = 0;

    for(int m = 11; m >= 0; m--){
        if(months[m].people_born > max_people_born) {
            max_people_born = months[m].people_born;
            strcpy(max_people_month, months[m].name);
        }
        tot = tot + months[m].people_born;
    }

    double media = (double) tot / 12.0;

    printf("Mese con numero massimo di nati: %s\n", max_people_month);
    printf("Numero medio mensile di nascite: %.2f\n", media);
    return 0;
}