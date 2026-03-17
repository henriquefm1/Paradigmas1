#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    // TODO: Implemente aqui a solucao para operacao create

    return NULL;
}

void poli_destroy(polinomio **p){
    // TODO: Implemente aqui a solucao para operacao destroy


    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente
    if(exp < 0 || exp > p->grau){
        return 0;
    }
    if(coef == 0 && p->coeficientes[exp] != 0){
        p->termos--;
    }else if (coef != 0 && p->coeficientes[exp] == 0) {
        p->termos++;
    }

    p->coeficientes[exp] = coef;

    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // TODO: Implemente aqui a solucao para operacao get coeficiente
    if(exp < 0 || exp > p->grau){
        return 0;
    }
    if(p->coeficientes[exp] == 0){
        return 0;
    }else{
        *coef = p->coeficientes[exp];
    }
    return 1;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)     
    
    return 0;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}


