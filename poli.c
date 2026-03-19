//Henrique Ferreira Marciano - RA: 10439797

#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    //Aloca o espaço para a estrutura do polinômio
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
        free(p); //Se falhou o vetor, libera a struct antes de sair
        return NULL;
    }

    return p;
}

void poli_destroy(polinomio **p){
    //Verifica se o ponteiro e é nulo
    if (p == NULL || *p == NULL) return;

    //Libera o vetor que está dentro da struct
    free((*p)->coeficientes);

    //Libera a struct 
    free(*p);

    //Faz o ponteiro original apontar para NULL 
    *p = NULL;

    return;

}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    //caso base, se expoente for menor que 0 ou maior que o grau, retorna 0
    if(exp < 0 || exp > p->grau){
        return 0;
    }
    //se coeficiente não era 0 e o novo é 0, perde um termo
    if(coef == 0 && p->coeficientes[exp] != 0){
        p->termos--;
    //se coeficiente era 0 e o novo não, ganha um termo
    }else if (coef != 0 && p->coeficientes[exp] == 0) {
        p->termos++;
    }

    p->coeficientes[exp] = coef;

    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    //caso base, se expoente for menor que zero ou maior que o grau maximo, retorna 0
    if(exp < 0 || exp > p->grau){
        return 0;
    }
    //verifica se o termo for igual a 0, retorna 0
    if(p->coeficientes[exp] == 0){
        return 0;
    //valor volta para a função que o chamou por passagem de referencia
    }else{
        *coef = p->coeficientes[exp];
    }
    return 1;
}

int calcula_px(polinomio *p, int x){
    int resultado = 0;
    int pot = 1;
    
    for(int i = 0; i <= p->grau; i++){
        //multiplica o coeficiente atual pela potencia atual e soma no total
        resultado = resultado + (p->coeficientes[i] * pot);
        //a multiplicação por x faz com que as contas continuem sendo inteiras e exatas
        pot = pot * x;
    }
    
    return resultado;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    int grau_max = (p->grau > q->grau) ? p->grau : q->grau;
    polinomio *s = poli_create(grau_max);
    if(s == NULL) return NULL;

    for(int i=0; i<= grau_max; i++){
        int coef_p =0, coef_q = 0;

        if(i <= p->grau) coef_p = p->coeficientes[i];

        if(i <= q->grau) coef_q = q->coeficientes[i];

        poli_ins_termo(s, i, coef_p + coef_q);
    }

    return s;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    //faz a soma dos graus maximos dos polinomios, pois o grau do polinomio resultante da multiplicação é sempre o resultado dessa soma
    polinomio *m = poli_create(p->grau + q->grau);
    //logica do chuveirinho, faz com que todo termo p multiplica todo termo q
    for(int i = 0; i <= p->grau; i++){
        for(int j = 0; j <= q->grau; j++){
            //soma os expoentes e multiplica os coeficientes
            int soma = i + j;
            int multiplicacao = p->coeficientes[i] * q->coeficientes[j];
            //soma o novo calculo com o valor que ja existe em m
            int resultado = m->coeficientes[soma] + multiplicacao;
            //chama a função de inserir termo para contabilizar a quantidade de termos validos
            poli_ins_termo(m, soma, resultado);
        }
    }

    return m;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    if (p == NULL || q == NULL || q->grau > p->grau) return NULL;
    if (q->coeficientes[q->grau] == 0) return NULL;

    int grau_q = p->grau - q->grau;
    polinomio *quociente = poli_create(grau_q);
    if (quociente == NULL) return NULL;

    polinomio *temp_p = poli_create(p->grau);
    if (temp_p == NULL) {
        poli_destroy(&quociente);
        return NULL;
    }
    for (int i = 0; i <= p->grau; i++) {
        temp_p->coeficientes[i] = p->coeficientes[i];
    }
    while (temp_p->grau >= q->grau) {
        int expoente_atual = temp_p->grau - q->grau;
        int coef_atual = temp_p->coeficientes[temp_p->grau] / q->coeficientes[q->grau];

        poli_ins_termo(quociente, expoente_atual, coef_atual);

        for (int i = 0; i <= q->grau; i++) {
            temp_p->coeficientes[i + expoente_atual] -= coef_atual * q->coeficientes[i];
        }
        while (temp_p->grau > 0 && temp_p->coeficientes[temp_p->grau] == 0) {
            temp_p->grau--;
        }
        if (temp_p->grau == 0 && temp_p->coeficientes[0] == 0) break;
    }

    poli_destroy(&temp_p);

    return quociente;

    return NULL;
}

