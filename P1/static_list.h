/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 15 / 02 / 2024
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define LNULL -1
#define MAX 25

typedef int tPosL;

typedef struct{
    tItemL data[MAX];
    tPosL lastPos;
}tList;

void createEmptyList(tList *L);
// objetivo: crear una lista vacía
// postcondiciones: la lista queda inicializada y no contiene elementos.
// entrada: lista
// salida: lista

bool isEmptyList(tList L);
// objetivo: determinar si la lista está vacia
// entrada: lista
// salida: bool

tPosL first(tList L);
// objetivo: devuelve la posición del primer elemento de la lista
// precondiciones: la lista no puede estar vacía
// entrada: lista
// salida: posición

tPosL last(tList L);
// objetivo: devuelve la posición del último elemento de la lista
// precondiciones: la lista no puede estar vacía
// entrada: lista
// salida: posición

tPosL next(tPosL p, tList L);
// objetivo: devuelve la posicion en la lista del elemento siguiente al indicado. devuelve LNULL si la posicion no tiene siguiente
// salida: posicion
// entrada: lista
// precondicion: la posicion indicada es una posicion valida en la lista

tPosL previous(tPosL p, tList L);
// objetivo: devuelve la posición del elemento anterior al de la posición indicada en la lista
// si no tiene elemento anterior devuelve LNULL
// precondiciones: la posición indicada debe ser válida
// entrada: lista
// salida: posicion
// precondicion: la posicion indicada es una posicion valida en la lista

bool insertItem(tItemL ITEM, tPosL p, tList *L);
// objetivo: insertar un elemento en la lista antes de la posición indicada. si la posicion es LNULL, se añade al final devuelve el valor TRUE si el elemento fue isertado y FALSE en caso contrario
// precondicion: la posicion indicada es una posicion o bien nula o bien valida en la lista
// postcondicion: las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden variar
// entrada: item, posicion, lista
// salida lista, bool

void deleteAtPosition(tPosL p, tList *L);
// objetivo: elimiar de la lista el elemento que ocupa la posicion indicada
// precondicion: la posicion indicada es una posicion valida en la lista
// postcondicion: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
// entrada: posicion, lista
// salida: lista

tItemL getItem(tPosL p, tList L);
// objetivo: devolver el contenido del elemento de la lista que ocupa la posicion indicada
// precondicion: la posicion indicada es una posicion valida en la lista
// entrada: posicion, lista
// salida: item

void updateItem(tItemL ITEM, tPosL p, tList *L);
// objetivo: modificar el contenido del elemento situado en la posicion indicada
// precondicion: la posicion indicada es una posicion valida en la lista
// postcondicion: el orden de los elementos de la lista no se ven modificados
// entrada: item, posicion, lista
// salida: lista

tPosL findItem(tUserName name, tList L);
// objetivo: devuelve la posicion del primer elemento de la lista cuyo nombre se corresponda con el indicado, o LNULL si no existe tal elemento
// entrada: product, lista
// salida: lista

#endif
