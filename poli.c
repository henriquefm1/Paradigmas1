#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    // Aloca o espaço para a estrutura do polinômio
    polinomio *p = (polinomio *) malloc(sizeof(polinomio));
    
    //Se a alocação falhar, retorna NULL
    if (p == NULL) return NULL;

    //Guarda o grau no campo correto da struct
    p->grau = grau;
    p->termos = 0;

    //Aloca o vetor de coeficientes (grau + 1 posições)
    p->coeficientes = (int *) calloc((grau + 1), sizeof(int));

    //Verifica se a alocação do vetor funcionou
    if (p->coeficientes == NULL) {
        free(p); // Se falhou o vetor, libera a struct antes de sair
        return NULL;
    }

    return p;
}

void poli_destroy(polinomio **p){
    // Verifica se o ponteiro e é nulo
    if (p == NULL || *p == NULL) return;

    // Libera o vetor que está dentro da struct
    free((*p)->coeficientes);

    //  Libera a struct 
    free(*p);

    // Faz o ponteiro original apontar para NULL 
    *p = NULL;

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
    int resultado = 0;
    int pot = 1;
    for(int i = 0; i <= p->grau; i++){
        resultado = resultado + (p->coeficientes[i] * pot);
        pot = pot * x;
    }
    
    return resultado;
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
