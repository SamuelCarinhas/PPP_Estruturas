#include <stdio.h>

/*
 * Lista ligada normal,
 *      estrutura tipo FIFO (First In First Out)
 *
 * Estrutura do elemento da lista:
 *      valor: valor inteiro do elemento
 *      validade: variável adicional para verificar se o elemento ainda está presente na lista, 0 -> False, 1 -> True
 *      elemento_anterior: índicie do elemento anterior
 */

#define TAMANHO_LISTA 10
#define tamanhoVetor(vetor) (int) (sizeof(vetor)/sizeof(vetor[0]))

int saida_lista;

struct elemento_lista {
    int valor;
    int validade;
    int elemento_anterior;
} lista[TAMANHO_LISTA];

void percorrer_lista(void);
void inicializar_lista(void);
int remover_elemento(void);
int adicionar_elemento(int);
int posicao_livre(void);


int main(void) {
    inicializar_lista();

    int valores[4] = {1, 2, 5, 7};
    for(int i = 0; i < tamanhoVetor(valores); i++) {
        int resultado = adicionar_elemento(valores[i]);
        if(resultado == -1)
            printf("Lista cheia\n");
        else
            printf("Valor %d adicionado.\n", valores[i]);
    }

    percorrer_lista();
    int valor_removido = remover_elemento();
    printf("Valor %d removido\n", valor_removido);
    percorrer_lista();

}

void percorrer_lista(void) {
    int i = saida_lista;
    if(i == -1)
        return; // Lista vazia
    while(1) {
        printf("Valor: %d\n", lista[i].valor);
        i = lista[i].elemento_anterior;
        if(i == -1)
            break; // Fim da Fila
    }
}

void inicializar_lista(void) {
    saida_lista = -1;
    struct elemento_lista vazio = {0, 0, -1};
    for(int i = 0; i < TAMANHO_LISTA; i++) {
        lista[i] = vazio;
    }
}

int posicao_livre(void) {
    for(int i = 0; i < TAMANHO_LISTA; i++)
        if(!lista[i].validade) // Se a validade == 0 (=) if(lista[i].validade == 0)
            return i;
    return -1; // Lista cheia
}

int adicionar_elemento(int valor) {
    int posicao = posicao_livre();
    if(posicao == -1)
        return -1; // ERRO -> LISTA CHEIA, elemento não pode ser adicionado
    struct elemento_lista adicionar = {valor, 1, saida_lista};
    lista[posicao] = adicionar;
    saida_lista = posicao;
    return 1; // Elemento adicionado
}

int remover_elemento(void) {
    int primeiro_elemento = saida_lista, segundo_elemento = -1;
    if(primeiro_elemento == -1)
        return -1; // Lista vazia
    while(1) {
        if(lista[primeiro_elemento].elemento_anterior == -1) break;
        segundo_elemento = primeiro_elemento;
        primeiro_elemento = lista[primeiro_elemento].elemento_anterior;
    }
    lista[primeiro_elemento].validade = 0; // Elemento vazio
    if(segundo_elemento == -1)
        saida_lista = -1; // A lista só tinha um elemento, logo vai ficar vazia
    else
        lista[segundo_elemento].elemento_anterior = -1; // O segundo elemento vai passar a ser o primeiro
    return lista[primeiro_elemento].valor;
}
