/**      @file: lista_encadeada_char.c
 *     @author: Guilherme N. Ramos (gnramos@unb.br)
 * @disciplina: Estruturas de Dados
 *
 * Implementação das funções para lidar com lista duplamente encadeada contendo
 * um caractere. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_encadeada_char.h"

elemento_t* elemento(const info_t* info, elemento_t* ant, elemento_t* prox) {
    elemento_t *aux;
    aux = malloc(sizeof(elemento_t));
    aux->info = *info;
    aux->ant = prox;
    aux->prox = ant;
    return(aux);
}

void libera(elemento_t** ptr) {
    free(*ptr);
    *ptr = NULL;
}

int infocmp(const info_t* e1, const info_t* e2) {
    if (e1 == e2) return 0;
    if (!e1) return -1;
    if (!e2) return 1;
    return (*e1) - (*e2);
}

int elementocmp(const elemento_t* e1, const elemento_t* e2) {
    if (e1 == e2) return 0;
    if (!e1) return -1;
    if (!e2) return 1;
    return infocmp(&(e1->info), &(e2->info));
}

_Bool insere(elemento_t* e, unsigned int pos, lista_t** ptr_lista) {
    if(ptr_lista == NULL) return false;
    if(e == NULL) return false;
    if(pos < 0) return false;
    if((*ptr_lista == NULL)){
        if(pos == 0){
            if(e == NULL) return false;
            (*ptr_lista) = e;
            (*ptr_lista)->ant = NULL;
            (*ptr_lista)->prox = NULL;
            return true;
        }
        return false;
    }
    if(pos > 0 && (*ptr_lista)->prox){
        return insere(e,pos-1,&((*ptr_lista)->prox));
    }
    if(pos == 1){
        if((*ptr_lista)->prox == NULL){
            (*ptr_lista)->prox = e;
            e->ant = (*ptr_lista);
            e->prox = NULL;
            return true;
        }
        (*ptr_lista)->prox->ant = e;
        e->prox = (*ptr_lista)->prox;
        e->ant = (*ptr_lista);
        (*ptr_lista)->prox = e;
        return true;
    }
    if(pos == 0){
        e->ant =(*ptr_lista)->ant;
        (*ptr_lista)->ant = e;
        e->prox = (*ptr_lista);
        (*ptr_lista) = e;
        return true;
    }
    return false;
}

_Bool insere_em_ordem(elemento_t* e, lista_t** ptr_lista){
    if(ptr_lista == NULL) return false;
    if(e == NULL) return false;
    if((*ptr_lista == NULL)){
        if(e == NULL) return false;
        (*ptr_lista) = e;
        (*ptr_lista)->ant = NULL;
        (*ptr_lista)->prox = NULL;
        return true;
    }
    if(infocmp(&(e->info),&((*ptr_lista)->info)) > 0){
        if((*ptr_lista)->prox == NULL){
            (*ptr_lista)->prox = e;
            e->ant = (*ptr_lista);
            e->prox = NULL;
            return true;
        }
        if(infocmp(&(e->info),&((*ptr_lista)->prox->info)) < 0){
            (*ptr_lista)->prox->ant = e;
            e->prox = (*ptr_lista)->prox;
            e->ant = (*ptr_lista);
            (*ptr_lista)->prox = e;
            return true;
        }
        return insere_em_ordem(&(*e),&((*ptr_lista)->prox));
    }
    if(infocmp(&(e->info),&((*ptr_lista)->info)) < 0){
        e->ant =(*ptr_lista)->ant;
        (*ptr_lista)->ant = e;
        e->prox = (*ptr_lista);
        (*ptr_lista) = e;
        return true;
    }
    return false;
}

elemento_t* retira(unsigned int pos, lista_t** ptr_lista) {
    elemento_t *aux;
    if(ptr_lista == NULL) return NULL;
    if(pos < 0) return NULL;
    if((*ptr_lista == NULL)) return NULL;
    if(pos > 1 && (*ptr_lista)->prox){
        return retira(pos-1,&((*ptr_lista)->prox));
    }
    if(pos == 0){
        if((*ptr_lista)->prox == NULL){
            aux = (*ptr_lista);
            (*ptr_lista) = NULL;
            return(aux);
        }
        aux = (*ptr_lista);
        (*ptr_lista) = (*ptr_lista)->prox;
        (*ptr_lista)->ant = NULL;
        
        return(aux);
    }
    if(pos == 1){
        if((*ptr_lista)->prox->prox == NULL){
            aux = (*ptr_lista)->prox;
            (*ptr_lista)->prox = NULL;
            return(aux);
        }
        aux = (*ptr_lista)->prox;
        (*ptr_lista)->prox->prox->ant = (*ptr_lista);
        (*ptr_lista)->prox = (*ptr_lista)->prox->prox;
        return (aux);
    }
    return NULL;
}

elemento_t* retira_em_ordem(info_t* info, lista_t** ptr_lista) {
    if(ptr_lista == NULL) return NULL;
    if((*ptr_lista == NULL)) return NULL;
    elemento_t *aux;
    if(infocmp(info,&((*ptr_lista)->info)) == 0){
        if((*ptr_lista)->prox == NULL){
            aux = (*ptr_lista);
            (*ptr_lista) = NULL;
            return(aux);
        }
        aux = (*ptr_lista);
        (*ptr_lista)->prox->ant = (*ptr_lista)->ant;
        (*ptr_lista)->ant->prox = (*ptr_lista)->prox;
        return (aux);
    }
    return retira_em_ordem(info,&(*ptr_lista)->prox);
}

void esvazia(lista_t** ptr_lista) {
    elemento_t *aux;
    unsigned int i = 0, tam;
    tam = tamanho((*ptr_lista));
    for(i = 0; i < tam; i++){
        aux = (*ptr_lista)->prox;
        (*ptr_lista)->ant = NULL;
        (*ptr_lista)->prox = NULL;
        (*ptr_lista) = aux;
    }
}

elemento_t* busca(const info_t *info, lista_t* lista) {
    if(lista == NULL){
        return (NULL);
    }
    if (lista->info == *info){
        return (lista);
    }
    return busca(info,lista->prox);  
}

unsigned int tamanho(const lista_t* lista) {
    int i = 0;
    while (lista != NULL){
        lista = lista->prox;
        i++;
    }
    return(i);
}

_Bool vazia(const lista_t *lista) {
    if(lista == NULL) return true;
    return false;
}

void print_i(const info_t* info) {
    if(info)
        printf("%c", *info);
}

void print_e(const elemento_t* e) {
    if(e) {
        printf("\tinfo: ");
        print_i(&(e->info));
        printf("\n\tprox: %p\n", e->prox);
        printf("\n\t ant: %p\n", e->ant);
    }
}

void print_l(const lista_t* lista) {
    int i = 0;
    while(lista) {
        printf("\n%d-esimo elemento:\n", i);
        print_e(lista);
        lista = lista->prox;
        ++i;
    }
}
