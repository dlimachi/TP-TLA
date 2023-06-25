#include "listUtils.h"
#include <stdio.h>
#include <stdlib.h>

stringList createList(){
    stringList toReturn = malloc(sizeof(stringNode));
    toReturn->next = NULL;
    toReturn->string = calloc(128, sizeof(void *));
    return toReturn;
}

stringList addToList( stringList list, char * string ){

    if (list == NULL)
        return NULL;

    if ( list->next == NULL )
    {
        stringList newNode = malloc(sizeof(stringNode));
        newNode->next = NULL;
        newNode->string = malloc(strlen(string)+1);
        strcpy(newNode->string, string);

        list->next = newNode;
        return list;
    }

    return addToList(list->next, string);
}

void freeList( stringList list ){
    if ( list == NULL )
        return;

    freeList(list->next);

    free(list->string);
    free(list);

    return;
}

// thanks chatGPT!
char* remover_comillas_extremos(char* input) {
    int length = strlen(input);
    if(length < 2) {
        return NULL; // Si el string es demasiado corto, retornamos NULL.
    }

    // Verificamos si la primera y última caracter son comillas (simples o dobles)
    if((input[0] == '\"' && input[length-1] == '\"') || (input[0] == '\'' && input[length-1] == '\'')) {
        char* new_str = malloc(length - 1); // Creamos una nueva cadena con espacio para la nueva cadena sin las comillas.
        if(new_str == NULL) {
            return NULL; // Si no se pudo asignar la memoria, retornamos NULL.
        }
        strncpy(new_str, input + 1, length - 2); // Copiamos la cadena original sin las comillas.
        new_str[length - 2] = '\0'; // Aseguramos que la cadena es nula terminada.
        return new_str;
    } else {
        return strdup(input); // Si la cadena original no comienza y termina con comillas, la retornamos tal cual.
    }
}

char* modificar_comillas(char* input) {
    int length = strlen(input);
    if(length < 2) {
        return NULL; // Si el string es demasiado corto, retornamos NULL.
    }

    char* new_str;

    // Si la cadena comienza y termina con comillas dobles, las cambiamos por simples.
    if(input[0] == '\"' && input[length-1] == '\"') {
        new_str = malloc(length + 1); // Creamos una nueva cadena con espacio para la nueva cadena.
        if(new_str == NULL) {
            return NULL; // Si no se pudo asignar la memoria, retornamos NULL.
        }
        new_str[0] = new_str[length-1] = '\''; // Cambiamos las comillas dobles por simples en los extremos.
        strncpy(new_str + 1, input + 1, length - 2); // Copiamos el resto de la cadena.
        new_str[length] = '\0'; // Aseguramos que la cadena es nula terminada.
    }
    // Si la cadena no comienza y termina con comillas, añadimos comillas simples al principio y al final.
    else if(input[0] != '\'' && input[length-1] != '\'' && input[0] != '\"' && input[length-1] != '\"') {
        new_str = malloc(length + 3); // Creamos una nueva cadena con espacio para la nueva cadena y las comillas adicionales.
        if(new_str == NULL) {
            return NULL; // Si no se pudo asignar la memoria, retornamos NULL.
        }
        new_str[0] = new_str[length+1] = '\''; // Añadimos las comillas simples en los extremos.
        strncpy(new_str + 1, input, length); // Copiamos el resto de la cadena.
        new_str[length+2] = '\0'; // Aseguramos que la cadena es nula terminada.
    }
    // Si no se cumplen ninguna de las condiciones anteriores, retornamos la cadena original.
    else {
        return strdup(input);
    }

    return new_str;
}

