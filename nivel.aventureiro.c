#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------------------------
// Estrutura de dados: Território
// Representa um território com nome, cor do exército e número de tropas.
// -------------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -------------------------------------------------------------
// Função: cadastrarTerritorios
// Lê os dados de N territórios e armazena dinamicamente.
// -------------------------------------------------------------
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("=== CONSTRUÇÃO DOS TERRITÓRIOS ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);

        printf("→ Nome do território: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("→ Cor do exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("→ Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// -------------------------------------------------------------
// Função: exibirTerritorios
// Mostra todos os territórios cadastrados.
// -------------------------------------------------------------
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n\n");
    for (int i = 0; i < n; i++) {
        printf("ID %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("---------------------------\n");
    }
}

// -------------------------------------------------------------
// Função: atacar
// Simula um ataque entre dois territórios usando dados aleatórios.
// -------------------------------------------------------------
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Um território não pode atacar outro da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("\n⚠️ O atacante precisa de pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("✅ O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        atacante->tropas--;
    }
}

// -------------------------------------------------------------
// Função: liberarMemoria
// Libera o vetor alocado dinamicamente.
// -------------------------------------------------------------
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

// -------------------------------------------------------------
// Função principal (main)
// -------------------------------------------------------------
int main() {
    srand(time(NULL)); // garante aleatoriedade dos dados

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*)malloc(n * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    char opcao;
    do {
        int idAtacante, idDefensor;

        printf("\nEscolha o ID do território atacante: ");
        scanf("%d", &idAtacante);
        printf("Escolha o ID do território defensor: ");
        scanf("%d", &idDefensor);

        if (idAtacante < 1 || idAtacante > n || idDefensor < 1 || idDefensor > n) {
            printf("❌ IDs inválidos!\n");
        } else {
            atacar(&mapa[idAtacante - 1], &mapa[idDefensor - 1]);
            exibirTerritorios(mapa, n);
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    liberarMemoria(mapa);
    return 0;
}
