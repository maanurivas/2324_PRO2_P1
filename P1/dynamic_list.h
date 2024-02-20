/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 15 / 02 / 2024
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"

#define LNULL NULL

typedef struct Node *tPosL;

struct Node{
    tItemL data;
    tPosL next;
};

typedef tPosL tList;

void createEmptyList(tList *L);
// objetivo: crear una lista vacía
// postcondiciones: la lista queda inicializada y no contiene elementos
// salida: lista vacía
// entrada: puntero a lista

bool isEmptyList(tList L);
// objetivo: determinar si la lista está vacia
// salida: false si no se cumple que esté vacía, sino true
// entrada: lista

tPosL first(tList L);
// objetivo: devolver la posición del primer elemento de la lista
// precondicion: la lista no está vacia
// salida: posicion
// entrada: lista

tPosL previous(tPosL p, tList L);
// objetivo: devolver la posicion en la lista del elemento anterior a la posicion indicada. Si no tiene posicion anterior devuelve LNULL
// entrada: lista
// salida: posicion
// precondicion: la posicion indicada es una posicion valida en la lista

tPosL next(tPosL p, tList L);
// objetivo: devuelve la posicion en la lista del elemento siguiente al indicado. Devuelve LNULL si la posicion que le pasamos es la última
// salida: posicion
// entrada: posicion actual y lista
// precondicion: la posicion indicada es una posicion valida en la lista

tPosL last(tList L);
// objetivo: devuelve la posicion del ultimo elemento de la lista
// entrada: lista
// salida: posicion
// precondicion: lista no vacía

bool insertItem(tItemL ITEM, tPosL p, tList *L);
// objetivo: insertar un elemento en la lista antes de la posición indicada. Si la posicion es LNULL, se añade al final. Devuelve el valor TRUE si el elemento fue insertado y FALSE en caso // contrario
// precondicion: la posicion indicada es una posicion o bien nula o bien valida en la lista
// postcondicion: las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden variar
// entrada: elemento a insertar, posicion de referencia, lista
// salida: lista con el elemnto insertado, true si se ha podido insertar o false en caso contrario

void deleteAtPosition(tPosL p, tList *L);
// objetivo: eliminar de la lista el elemento que ocupa la posicion indicada
// precondicion: la posicion indicada es una posicion valida en la lista
// postcondicion: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
// entrada: posicion a eliminar, lista
// salida: lista después de la eliminación

tItemL getItem(tPosL p, tList L);
// objetivo: devolver el contenido del elemento de la lista que ocupa la posicion indicada
// precondicion: la posicion indicada es una posicion valida en la lista
// entrada: posicion, lista
// salida: contenido de la posición indicada

void updateItem(tItemL ITEM, tPosL p, tList * L);
// objetivo: modificar el contenido de la posicion indicada de la lista
// precondicion: la posicion indicada es una posicion valida en la lista
// entrada: nuevo valor del elemento, posicion del elemento a sobrescribir, lista
// salida: lista con elemento actualizado

tPosL findItem(tUserName name, tList L);
// objetivo: devuelve la posicion del primer elemento de la lista cuyo contenido coincida con el indicado, o LNULL si no existe tal elemento
// entrada: contenido del elemento que se busca, lista
// salida: posición del elemento si se encuentra, nulo en caso contrario

#endif
