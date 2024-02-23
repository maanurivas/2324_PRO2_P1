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
/*
Objetivo: Crea un nuevo usuario en la lista de usuarios de la plataforma MUSFIC, con su nombre,
          contador de reproducciones a cero y categoría.
Entrada: Un nombre(tipo tUserName), una categoría (tipo tUserCategory) y la lista (tListL).
Salida:  La confirmación de que se ha creado correctamente el nuevo elemento, o en su defecto,
         la confirmación de que no se ha podido crear o que el usuario no existe.
Precondiciones: -
Postcondiciones: -
*/

void delete(tUserName name, tList *L);
/*
Objetivo: Eliminar a un usuario de la lista, eliminando también todas sus reproducciones.
Entrada:  Un nombre de usuario (tipo tUserName) y la lista (tipo tListL).
Salida:   La confirmación de que se ha eliminado al usuario introducido, o en su defecto,
          (si el usuario no estaba en la lista) un error de eliminacion.
Precondiciones: -
Postcondiciones: -
*/

void upgrade(tUserName name, tList *L);
/*
 * Objetivo:  Cambiar la categoria del participante, de basic a pro.
 * Entrada:   Un nombre de usuario (tipo tUserName) y la lista (tipo tListL).
 * Salida:    La confirmación de que se ha cambiado la categoría, o en su defecto,
 *            La confirmación de que no se ha encontrado el usuario en la lista.
 * Precondiciones: -
 * Postcondiciones: -
 */


void play(tUserName name, tSongTitle  title, tList *L);
/*
Objetivo:  Añadir una reproduccion del participante a la canción indicada, además de añadirlo al numero total de reproducciones y tenerlo en cuenta para la media de reproducciones de cada categoria.
Entrada:   Un nombre de usuario (tipo tUserName), un nombre de cancion (tipo tSongTitle) y la lista(tipo tListL).
Salida:    La confirmación de que se ha reproducido la canción, o en su defecto,
           la confirmación de que no se ha encontrado el usuario en la lista.
Precondiciones: -
Postcondiciones: -
*/

void stats(tList *L);
/*
Objetivo: Muestra todos los usuarios de la lista con su categoría correspondiente y sus reproducciones,
          su número de reproducciones y media de reproducciones estos dos ultimos en función de la categoría.
Entrada:  Una lista (tipo tListL)
Salida:   Todos los datos que se requiere mostrar, o error en caso de que no se puedan mostrar estadisticas.
Precondiciones: -
Postcondiciones: -
*/

char *UserCategory_to_char(tUserCategory category);
/*
Objetivo: Convierte el parametro introducido al programa (basic/pro) a tipo char
Entrada: Un elemento tUserCategory
Salida: Devuelve true en caso de que el parametro introducido sea "basic" o false en caso contrario
Precondiciones: Recibe basic o pro
Postcondiciones: -
*/

tUserCategory char_to_UserCategory(char param[]);
/*
Objetivo: Convierte el parametro introducido al programa ("basic"/"pro") a tipo tUserCategory
Entrada: Un elemento char
Salida: Devuelve true en caso de que el parametro introducido sea "basic" o false en caso contrario
Precondiciones: Recibe "basic" o "pro"
Postcondiciones: -
*/

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *L) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);
            new(param1, char_to_UserCategory(param2), L);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);
            upgrade(param1, L);
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);
            play(param1,param2, L);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);
            stats(L);
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

char *UserCategory_to_char(tUserCategory category){
    return category ? "basic" : "pro";
}


tUserCategory char_to_UserCategory(char param[]){
    return (strcmp(param, "basic") == 0);
}


void new(tUserName name, tUserCategory category, tList *L){
    tItemL ITEM;
    bool insertado;
    char* UserCategory;//variables auxiliares para trabajar sobre ellas

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
    int auxPlays;//variables auxiliares para trabajar sobre ellas

    p = findItem(name, *L);//Buscamos el nombre
    if(p==LNULL){//No esta en la lista o está vacía
        printf("+ Error: Delete not possible\n");
    } else{//Está en la lista
        auxITEM = getItem(p, *L);//Obtenemos el user
        auxPlays=auxITEM.numPlay;
        if(auxITEM.userCategory){//comprobamos la categoria del usuario
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
    tItemL auxITEM;//variables auxiliares para trabajar sobre ellas

    p = findItem(name, *L);//buscamos el item
    if(p==LNULL){//comprobamos si está en la lista
        printf("+ Error: Upgrade not possible\n");
    } else{
        auxITEM = getItem(p, *L);//caso en el que la categoría ya es pro
        if (UserCategory_to_char(auxITEM.userCategory) == "pro") {//comprobamos que su categoría no es pro usando una función auxiliar para pasar a char los userCategory
            printf("+ Error: Upgrade not possible\n");
        } else{//está en la lista
            auxITEM.userCategory= char_to_UserCategory("pro"); // Pasamos la categoría a "pro"
            updateItem(auxITEM, p, L); // Actualiza el usuario en la lista
            printf("* Upgrade: user %s category %s\n", name, UserCategory_to_char(auxITEM.userCategory));//Imprimimos por pantalla
        }
    }
}


void play(tUserName name, tSongTitle  title, tList *L){
    tPosL p;
    tItemL auxITEM;//variables auxiliares para trabajar sobre ellas

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

void stats(tList *L){
    tPosL p;
    tItemL auxITEM;
    char *UserCategory;
    int cntBasic=0, cntPro=0, playBasic=0, playPro=0;
    float mediaBasic=0.0f, mediaPro=0.0f;
    if(isEmptyList(*L)){
        printf("+ Error: Stats not possible\n");
    } else{
        for(p = first(*L); p != LNULL; p = next(p, *L)){
            auxITEM = getItem(p, *L);
            if(UserCategory_to_char(auxITEM.userCategory) != "pro"){
                UserCategory = "basic";
                cntBasic=cntBasic+1;
                playBasic+=auxITEM.numPlay;
            } else{
                UserCategory = "pro";
                cntPro=cntPro+1;
                playPro+=auxITEM.numPlay;
            }
            printf("User %s category %s numplays %d\n", auxITEM.userName, UserCategory, auxITEM.numPlay);
        }
        if((playBasic==0)||(cntBasic==0)){
            mediaBasic = 0.0f;
        } else{
            mediaBasic= (float) playBasic/cntBasic;
        }
        if((playPro==0)||(cntPro==0)){
            mediaPro = 0.0f;
        } else{
            mediaPro= (float) playPro/cntPro;
        }

        printf("Category  Users  Plays  Average\n");
        printf("Basic     %5d %6d %8.2f\n", cntBasic,playBasic,mediaBasic);
        printf("Pro       %5d %6d %8.2f\n", cntPro,playPro,mediaPro);
    }
}









