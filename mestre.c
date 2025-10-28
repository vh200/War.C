#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------------------------
// Estrutura de dados: Território
// -------------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -------------------------------------------------------------
// Estrutura de dados: Jogador
// Contém a missão individual de cada jogador
// -------------------------------------------------------------
typedef struct {
    char nome[30];
    char* missao; // armazenada dinamicamente
} Jogador;

// -------------------------------------------------------------
// Vetor global de missões estratégicas
// -------------------------------------------------------------
char* missoes[] = {
    "Conquistar 3 territórios seguidos",
    "Eliminar todas as tropas vermelhas",
    "Controlar metade do mapa",
    "Ter pelo menos 50 tropas no total",
    "Dominar todos os territórios azuis"
};
int totalMissoes = 5;

// -------------------------------------------------------------
// Função: atribuirMissao
// Sorteia e copia missão para o jogador
// -------------------------------------------------------------
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// -------------------------------------------------------------
// Função: cadastrarTerritorios
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
// Função: verificarMissao
// Verifica se o jogador cumpriu sua missão (simples exemplo inicial)
// -------------------------------------------------------------
int verificarMissao(char* missao, Territorio* mapa, int n) {
    if (strcmp(missao, "Controlar metade do mapa") == 0) {
        int contAzul = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0)
                contAzul++;
        }
        if (contAzul >= n / 2)
            return 1;
    }

    // outras missões podem ser adicionadas aqui
    return 0;
}

// -------------------------------------------------------------
// Função: liberarMemoria
// -------------------------------------------------------------
void liberarMemoria(Territorio* mapa, Jogador* jogadores, int qtdJogadores) {
    for (int i = 0; i < qtdJogadores; i++) {
        free(jogadores[i].missao);
    }
    free(jogadores);
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

// -------------------------------------------------------------
// Função principal (main)
// -------------------------------------------------------------
int main() {
    srand(time(NULL));

    int n, qtdJogadores;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    printf("Quantos jogadores participarão? ");
    scanf("%d", &qtdJogadores);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*)malloc(n * sizeof(Territorio));
    Jogador* jogadores = (Jogador*)malloc(qtdJogadores * sizeof(Jogador));

    if (mapa == NULL || jogadores == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Atribui missões a cada jogador
    for (int i = 0; i < qtdJogadores; i++) {
        printf("\nDigite o nome do jogador %d: ", i + 1);
        scanf(" %29[^\n]", jogadores[i].nome);

        jogadores[i].missao = (char*)malloc(100 * sizeof(char));
        atribuirMissao(jogadores[i].missao, missoes, totalMissoes);

        printf("🎯 Missão de %s: %s\n", jogadores[i].nome, jogadores[i].missao);
    }

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

        // Verifica se algum jogador venceu
        for (int i = 0; i < qtdJogadores; i++) {
            if (verificarMissao(jogadores[i].missao, mapa, n)) {
                printf("\n🏆 Parabéns! %s cumpriu sua missão e venceu o jogo!\n", jogadores[i].nome);
                liberarMemoria(mapa, jogadores, qtdJogadores);
                return 0;
            }
        }

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &opcao);

    } while (opcao == 's' || opcao == 'S');

    liberarMemoria(mapa, jogadores, qtdJogadores);
    return 0;
}
