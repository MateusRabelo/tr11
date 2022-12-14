// incluindo biblioteca que será usada
#include "ordvetor.h"

// criamos uma função do tipo VETORORD (que foi definido no .h)

// a função vai basicamente definir os valores e alocar na memória tudo o que for necessário, 
// limpando os lixos necessários de serem limpos para não dar nenhum problema de memory trash
VETORORD* VETORD_create(int n, COMP* compara) {
	VETORORD* vetor = malloc(sizeof(VETORORD));
	vetor->N = n;
	vetor->P = 0;
	vetor->elems = malloc(n * sizeof(void*));
	vetor->comparador = compara;
	return vetor;
}

// aqui a função vai adicionar os valores pedidos, utilizando de técnicas de ordenação de valores
// para adicionar valores e já ordenar nos devidos índices
void VETORD_add(VETORORD* vetor, void* newelem) {
	if (vetor->P < vetor->N) {
        //definindo o que será a posição do vetor atual
		int posicao = vetor->P;

        //adicionando o valor no vetor
		for (int i = 0; i < vetor->P; i++) {
			if (vetor->comparador(vetor->elems[i], newelem) == -1) {
				posicao = i;
				break;
			}
		}

        // organizando/ordenando os valores nos índices do vetor
		for (int i = vetor->P; i > posicao; i--) {
			vetor->elems[i] = vetor->elems[i - 1];
		}

        //definindo a nova posição do vetor
		vetor->elems[posicao] = newelem;
		vetor->P++;
	}	
}

// VETORD_remove vai justamente remover os valores do vetor, e novamente reorganizar os valores no índice
void* VETORD_remove(VETORORD* vetor) {
	void* menor = vetor->elems[0];

    // reorganizando os valores nos índices do vetor
	for (int i = 0; i < vetor->P - 1; i++) {
		vetor->elems[i] = vetor->elems[i + 1];
	}
	
	vetor->P--;

	return menor;
}

// função para comparar os respectivos valores
int comparar(void* x, void* y) {
	int xx = *((int*) x);
	int yy = *((int*) y);

	return xx < yy ? 1 : xx == yy ? 0 : -1;
}	

// e aqui temos a função principal, que irá rodar todo o programa
int main() {
    // definindo valores iniciais
	const int VETOR_SIZE = 10;
	const int VETOR_REMOVE = 2;

    // definindo comportamento da variável vetor
	VETORORD* vetor = VETORD_create(VETOR_SIZE, comparar);

    // vetor em us[tamanho do vetor]
	int meuVetor[VETOR_SIZE];

    // apresentação do vetor inicial
	printf("VETOR INICIALIZADO: ");
	for (int i = 0; i < VETOR_SIZE; i++) {
        // definindo o tamanho do vetor, imprimindo o vetor e sí
		meuVetor[i] = rand() % VETOR_SIZE;
		printf("%d - ", meuVetor[i]);
	}
	printf("FIM\n\n");

    // calcula a adição de valores nos indíves do vetor
	for (int i = 0; i < VETOR_SIZE; i++) {
		VETORD_add(vetor, &meuVetor[i]);
	}

    // imprimindo os itens removidos
	printf("ITENS REMOVIDOS: ");
    // calcula para imprimir os itens removidos
	for (int i = 0; i < VETOR_REMOVE; i++) {
		printf("%d - ", *((int*) VETORD_remove(vetor)));
	}
	printf("FIM\n\n");

    // imprimi o vetor final
	printf("VETOR FINAL: ");
    // calculando os valores do vetor depois de todas as alterações
	for (int i = 0; i < vetor->P; i++) {
		printf("%d - ", *((int*) vetor->elems[i]));
	}
	printf("FIM\n");

	return 0;
}