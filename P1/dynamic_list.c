/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 15 / 02 / 2024
 */
#include <stdlib.h>
#include <string.h>
#include "dynamic_list.h"

void createEmptyList(tList *L){
    *L = LNULL;
}

bool createNode(tPosL *p){
    *p = malloc(sizeof(struct Node));
    return *p != LNULL;
}

bool isEmptyList(tList L){
    return L == LNULL;
}

tPosL first(tList L){
    return L;
}

tPosL previous(tPosL p, tList L){
    tPosL q;
    if(p == L){//Si p es la primera posición se devolverá nulo
        return LNULL;
    }
    else{
        for (q = L; q->next != p; q = q->next);//Se recorre la lista hasta llegar a la posición anterior a la indicada
        return q;
    }
}

tPosL next(tPosL p, tList L){
    return p->next;
}

tPosL last(tList L){
    tPosL p;
    for (p = L; p->next != LNULL ; p = p->next);//Se recorre la lista hasta llegar al final
    return p;

}

bool insertItem(tItemL ITEM, tPosL p, tList * L){
    tPosL q, r;
    if (!createNode(&q)) {
        return false;
    }
    q->data = ITEM;
    q->next = LNULL;

    if(isEmptyList(*L)) {//Si la lista está vacía lo inserta al principio
        *L = q;
    }
    else if (p == LNULL) {//Si la posición de inserción es nulo se inserta al final
        for (r = *L; r->next != LNULL; r = r->next);
        r->next = q;
    }
    else if (p == *L){//Si la posición de inserción es la primera se inserta al principio
        *L = q;
        q->next = p;
    }
    else{//Si la inserción se realiza en una posición intermedia
        q->next = p->next;
        p->next = q;
        q->data = p->data;
        p->data= ITEM;
    }
    return true;
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL q;
    if (p == *L) {//La posición a eliminar es la primera
        *L = p->next;
        free(p);

    }
    else if (p->next == NULL) {//La posición a eliminar es la última
        previous(p, *L)->next = LNULL;
        free(p);
    }
    else {//Es una posición intermedia
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        free(q);
    }
}

void updateItem(tItemL ITEM, tPosL p, tList * L){
    p->data = ITEM;
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

tPosL findItem(tUserName name, tList L){
    tPosL p;
    if (isEmptyList(L)) {
        p = LNULL;
    }
    else{//Se recorre la lista hasta encontrar el elemento o hasta llegar llegar al final
        for (p = L; p != LNULL && strcmp(name, p->data.userName) != 0; p = p->next);
    }
    return p;
}