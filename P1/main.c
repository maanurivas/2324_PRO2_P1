/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 15 / 02 / 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

void new(tUserName name, tUserCategory category, tList *L);

void delete(tUserName name);

void upgrade(tUserName name);

void play(tUserName name, tSongTitle  title);

void stats(tList L);

char *bool_to_char(tUserCategory category);

tUserCategory char_to_bool(char param[]);


void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *L) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category/song %s", commandNumber, command, param1, param2);
            new(param1, char_to_bool(param2), L);
            break;
        case 'D':
            break;
        case 'U':
            break;
        case 'P':
            break;
        case 'S':
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    tList L;
    createEmptyList(&L);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}

char *bool_to_char(tUserCategory category){
    return category ? "basic" : "pro";
}

tUserCategory char_to_bool(char param[]){
    return (strcmp(param, "basic") == 0);
}

void new(tUserName name, tUserCategory category, tList *L){
    tItemL ITEM;
    bool insertado;
    char* UserCategory;

    if(findItem(name, *L) != LNULL){//comprobamos si el participante ya está en la lista
        printf("Error al realizar New, participante ya dado de alta\n");
    } else{
        strcpy(ITEM.userName,name);//copiamos el dato del nombre en el nombre del nuevo
        ITEM.numPlay = 0;//asignamos su numero de reproducciones a 0
        ITEM.userCategory=category;//
        insertado = insertItem(ITEM, LNULL, L);
        if(!insertado){
            printf("+ Error: New not possible\n");
        } else{
            if(ITEM.userCategory){
                UserCategory = "basic";
            } else{
                UserCategory = "pro";
            }
            printf("* New: participant %s location %s\n", ITEM.userName, UserCategory);
        }
    }
}





