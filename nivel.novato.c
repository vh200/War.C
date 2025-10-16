#include <stdio.h>
#include <string.h>

// -------------------------------------------------------------
// Estrutura de dados: Território
// Esta struct armazena informações sobre cada território:
// nome, cor do exército e número de tropas.
// -------------------------------------------------------------
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Vetor que armazenará 5 territórios
    struct Territorio territorios[5];

    printf("=== CONSTRUÇÃO DOS TERRITÓRIOS ===\n\n");

    // -------------------------------------------------------------
    // Entrada de dados: o usuário cadastra 5 territórios
    // -------------------------------------------------------------
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        printf("→ Nome do território: ");
        scanf(" %29[^\n]", territorios[i].nome); // lê string com espaços

        printf("→ Cor do exército: ");
        scanf(" %9s", territorios[i].cor); // lê até 9 caracteres

        printf("→ Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // -------------------------------------------------------------
    // Exibição dos dados: mostra todas as informações cadastradas
    // -------------------------------------------------------------
    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    printf("\nCadastro concluído com sucesso!\n");

    return 0;
}
