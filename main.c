#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 10
#define MAX_CARGOS 6

// Estrutura de um candidato
typedef struct {
    char* nome;
    int votos;
} Candidato;

// Estrutura de um cargo eletivo
typedef struct {
    char* cargo;
    Candidato candidatos[MAX_CANDIDATOS];
    int numCandidatos;
} CargoEletivo;

// Função para criar um novo candidato
Candidato criarCandidato() {
    Candidato candidato;
    candidato.nome = (char*)malloc(50 * sizeof(char));
    printf("Digite o nome do candidato: ");
    scanf(" %[^\n]s", candidato.nome);
    candidato.votos = 0;
    return candidato;
}

// Função para criar um novo cargo eletivo
CargoEletivo criarCargoEletivo(char* cargo) {
    CargoEletivo cargoEletivo;
    cargoEletivo.cargo = (char*)malloc(50 * sizeof(char));
    strcpy(cargoEletivo.cargo, cargo);
    cargoEletivo.numCandidatos = 0;
    return cargoEletivo;
}

// Função para adicionar um candidato a um cargo eletivo
void adicionarCandidato(CargoEletivo* cargo, Candidato candidato) {
    if (cargo->numCandidatos < MAX_CANDIDATOS) {
        cargo->candidatos[cargo->numCandidatos] = candidato;
        cargo->numCandidatos++;
    }
}

// Função para realizar a votação
void votar(CargoEletivo* cargos, int numCargos) {
    for (int i = 0; i < numCargos; i++) {
        printf("Cargo: %s\n", cargos[i].cargo);
        printf("Candidatos:\n");
        for (int j = 0; j < cargos[i].numCandidatos; j++) {
            printf("%d. %s\n", j + 1, cargos[i].candidatos[j].nome);
        }
        int voto;
        printf("Digite o número correspondente ao candidato escolhido: ");
        scanf("%d", &voto);
        if (voto >= 1 && voto <= cargos[i].numCandidatos) {
            cargos[i].candidatos[voto - 1].votos++;
            printf("Voto registrado com sucesso!\n");
        } else {
            printf("Opção inválida!\n");
            i--; // Decrementa o contador do cargo para votar novamente
        }
        printf("\n");
    }
}

// Função para gerar o relatório de votação
void relatorioVotacao(CargoEletivo* cargos, int numCargos) {
    printf("Relatório de Votação:\n");
    for (int i = 0; i < numCargos; i++) {
        printf("Cargo: %s\n", cargos[i].cargo);
        printf("Candidatos:\n");
        for (int j = 0; j < cargos[i].numCandidatos; j++) {
            printf("%s: %d votos\n", cargos[i].candidatos[j].nome, cargos[i].candidatos[j].votos);
        }
        printf("\n");
    }
}

int main() {
    CargoEletivo cargos[MAX_CARGOS];

    // Definindo os cargos predefinidos
    cargos[0] = criarCargoEletivo("Presidente");
    cargos[1] = criarCargoEletivo("Governador");
    cargos[2] = criarCargoEletivo("Prefeito");
    cargos[3] = criarCargoEletivo("Senador");
    cargos[4] = criarCargoEletivo("Deputado Federal");
    cargos[5] = criarCargoEletivo("Deputado Estadual");

    // Criando os candidatos para cada cargo
    for (int i = 0; i < MAX_CARGOS; i++) {
        int numCandidatos;

        printf("\nDigite o número de candidatos para o cargo %s: ", cargos[i].cargo);
        scanf("%d", &numCandidatos);
        getchar();

        for (int j = 0; j < numCandidatos; j++) {
            printf("Candidato %d do cargo %s:\n", j + 1, cargos[i].cargo);
            Candidato candidato = criarCandidato();
            adicionarCandidato(&cargos[i], candidato);
        }
    }

    printf("\n=== Início da Votação ===\n");
    votar(cargos, MAX_CARGOS);

    printf("\n=== Fim da Votação ===\n");
    printf("\n=== Resultado da Votação ===\n");
    relatorioVotacao(cargos, MAX_CARGOS);

    // Liberar memória alocada para os nomes dos cargos e candidatos
    for (int i = 0; i < MAX_CARGOS; i++) {
        free(cargos[i].cargo);
        for (int j = 0; j < cargos[i].numCandidatos; j++) {
            free(cargos[i].candidatos[j].nome);
        }
    }

    return 0;
}