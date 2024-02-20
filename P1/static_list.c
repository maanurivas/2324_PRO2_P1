/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 15 / 02 / 2024
 */

#include <string.h>
#include "static_list.h"

void createEmptyList (tList *L){
    L->lastPos = LNULL;
}

bool isEmptyList(tList L) {
    return L.lastPos == LNULL;
}

tPosL first(tList L){
    return 0;
}

tPosL last(tList L){
    return L.lastPos;
}

tPosL next(tPosL p, tList L){
    if(p==L.lastPos)
        return LNULL;
    else
        return ++p;
}

tPosL previous(tPosL p, tList L){
    return --p;
}

bool insertItem(tItemL ITEM, tPosL p, tList *L){
    tPosL i;
    if(L->lastPos==MAX-1){
        return false;
    }else{
        L->lastPos ++;
        if(p==LNULL){       //Vamos a insertar al final, por lo que vamos a recorrer la lista desde el final.
            L->data[L->lastPos] = ITEM;
        } else{
            for (i=L->lastPos; i >= p+1; i--){
                L->data[i]= L->data[i-1];
            }
            L->data[p]= ITEM;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L){
    tPosL i;
    L->lastPos--;
    for(i = p; i <= L->lastPos; i++){ //Recorre la lista desde p hatsa la ultima posición.
        L->data[i] = L->data[i+1]; //Cambia el contenido de la posición i por el de la siguiente posición
    }
}

tItemL getItem(tPosL p, tList L){
    return L.data[p];
}


void updateItem(tItemL ITEM, tPosL p, tList * L){
    (* L).data[p]=ITEM;
}


tPosL findItem(tUserName name, tList L) {
    tPosL i;
    if (isEmptyList(L)) {
        return LNULL;
    }
    else {
        for (i = 0; (i < L.lastPos) && (strcmp(name, L.data[i].userName) != 0); i++); //Recorre la lista hasta que llegue al final o encuentre el nombre.
        if (strcmp(name, L.data[i].userName) == 0) { // Comprobamos si encontro el nombre con string compare
            return i;
        } else {
            return LNULL;
        }
    }
}
