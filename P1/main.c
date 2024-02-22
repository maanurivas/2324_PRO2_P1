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

void delete(tUserName name, tList *L);

void upgrade(tUserName name, tList *L);

void play(tUserName name, tSongTitle  title, tList *L);

//void stats(tList L);

char *bool_to_char(tUserCategory category);

tUserCategory char_to_bool(char param[]);


void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *L) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);
            new(param1, char_to_bool(param2), L);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: participant %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'U':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);
            upgrade(param1, L);
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);
            play(param1,param2, L);
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
        printf("+ Error: New not possible\n");//Error al realizar New, participante ya dado de alta
    } else{
        strcpy(ITEM.userName,name);//copiamos el dato del nombre en el nombre del nuevo
        ITEM.numPlay = 0;//asignamos su numero de reproducciones a 0
        ITEM.userCategory=category;//asignamos su categoria a la variable correspondiente
        insertado = insertItem(ITEM, LNULL, L);//insertamos el usuario
        if(!insertado){
            printf("+ Error: New not possible\n");
        } else{//con el usuario ya insertado
            if(ITEM.userCategory){//comprobamos la categoría del usuario para imprimir correctamente la categoría del usuario
                UserCategory = "basic";
            } else{
                UserCategory = "pro";
            }
            printf("* New: user %s category %s\n", ITEM.userName, UserCategory);//impresion por pantalla
        }
    }
}

void delete(tUserName name, tList *L){
    tPosL p;
    tItemL auxITEM;
    char *UserCategory;
    int auxPlays;

    p = findItem(name, *L);//Buscamos el nombre
    if(p==LNULL){//No esta en la lista o está vacía
        printf("+ Error: Delete not possible\n");
    } else{//Está en la lista
        auxITEM = getItem(p, *L);//Obtenemos el user
        auxPlays=auxITEM.numPlay;
        if(auxITEM.userCategory){
            UserCategory = "basic";
        } else{
            UserCategory = "pro";
        }
        deleteAtPosition(p, L);//lo eliminamos
        printf("* Delete: user %s category %s numplays %d\n", name, UserCategory, auxPlays);//imprimimos lo solicitado
    }
}

void upgrade(tUserName name, tList *L){
    tPosL p;
    tItemL auxITEM;
    char *UserCategory;

    p = findItem(name, *L);
    if(p==LNULL){
        printf("+ Error: Upgrade not possible\n");
    } else{
        auxITEM = getItem(p, *L);
        if (auxITEM.userCategory == basic) {
            printf("* Upgrade: user %s category pro\n", name);
            auxITEM.userCategory = pro; // Actualiza la categoría a "pro"
            updateItem(auxITEM, p, L); // Actualiza el usuario en la lista
        } else{
            printf("+ Error: Upgrade not possible\n");
        }
    }

}

void play(tUserName name, tSongTitle  title, tList *L){
    tPosL p;
    tItemL auxITEM;

    p = findItem(name,*L);//Buscamos el usuario
    if(p==LNULL){//El participante no está en la lista
        printf("+ Error: Play not possible\n");
    } else{//Está en la lista
        auxITEM = getItem(p, *L);//obtenemos el usuario
        auxITEM.numPlay++;//sumamos 1 en las reproducciones

        updateItem(auxITEM, p, L);//actualizamos el numero de reproducciones

        printf("* Play: user %s plays song %s numplays %d\n",name,title,auxITEM.numPlay);//imprimimos lo solicitado
    }
}









