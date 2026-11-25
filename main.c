#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10

typedef struct {
    int linhas;
    int colunas;
    double dados[MAX][MAX];
} Matriz;

// --- PROTÓTIPOS ---
Matriz criarMatriz();
void exibirMatriz(Matriz m, char *nome);
int validarSomaSub(Matriz a, Matriz b);
int validarMultiplicacao(Matriz a, Matriz b);
Matriz somarMatrizes(Matriz a, Matriz b);
Matriz subtrairMatrizes(Matriz a, Matriz b);
Matriz multiplicarMatrizes(Matriz a, Matriz b);
int calcularInversa(Matriz m, Matriz *inv);
Matriz dividirMatrizes(Matriz a, Matriz b, int *sucesso);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    int qtdMatrizes, escolha;
    
    printf("=== CALCULADORA DE MATRIZES ===\n");
    printf("Quantidade de matrizes (minimo 2): ");
    scanf("%d", &qtdMatrizes);

    while (qtdMatrizes < 2) {
        printf("Valor invalido! Digite novamente (minimo 2): ");
        scanf("%d", &qtdMatrizes);
    }

    Matriz *matrizes = (Matriz *) malloc(qtdMatrizes * sizeof(Matriz));

    for (int i = 0; i < qtdMatrizes; i++) {
        printf("\n--- Cadastro da Matriz %d ---\n", i + 1);
        matrizes[i] = criarMatriz();
    }

    do {
        printf("\n========= MENU =========\n");
        printf("1. Exibir matrizes\n");
        printf("2. Adicao\n");
        printf("3. Subtracao\n");
        printf("4. Multiplicacao\n");
        printf("5. Divisao matricial (A * B^-1)\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                for (int i = 0; i < qtdMatrizes; i++) {
                    char nome[20];
                    sprintf(nome, "Matriz %d", i + 1);
                    exibirMatriz(matrizes[i], nome);
                }
                break;

            case 2: {
                Matriz res = matrizes[0];
                int ok = 1;
                for (int i = 1; i < qtdMatrizes; i++) {
                    if (validarSomaSub(res, matrizes[i])) {
                        res = somarMatrizes(res, matrizes[i]);
                    } else {
                        printf("\n[ERRO] Dimensoes incompativeis na Adicao!\n");
                        ok = 0;
                        break;
                    }
                }
                if (ok) exibirMatriz(res, "Resultado da Adicao");
                break;
            }

            case 3: {
                Matriz res = matrizes[0];
                int ok = 1;
                for (int i = 1; i < qtdMatrizes; i++) {
                    if (validarSomaSub(res, matrizes[i])) {
                        res = subtrairMatrizes(res, matrizes[i]);
                    } else {
                        printf("\n[ERRO] Dimensoes incompativeis na Subtracao!\n");
                        ok = 0;
                        break;
                    }
                }
                if (ok) exibirMatriz(res, "Resultado da Subtracao");
                break;
            }

            case 4: {
                Matriz res = matrizes[0];
                int ok = 1;
                for (int i = 1; i < qtdMatrizes; i++) {
                    if (validarMultiplicacao(res, matrizes[i])) {
                        res = multiplicarMatrizes(res, matrizes[i]);
                    } else {
                        printf("\n[ERRO] Dimensoes incompativeis na Multiplicacao!\n");
                        ok = 0;
                        break;
                    }
                }
                if (ok) exibirMatriz(res, "Resultado da Multiplicacao");
                break;
            }

            case 5: {
                Matriz res = matrizes[0];
                int ok = 1;
                for (int i = 1; i < qtdMatrizes; i++) {
                    int sucesso = 0;
                    res = dividirMatrizes(res, matrizes[i], &sucesso);
                    if (!sucesso) {
                        printf("\n[ERRO] Divisao falhou (matriz nao quadrada ou singular)!\n");
                        ok = 0;
                        break;
                    }
                }
                if (ok) exibirMatriz(res, "Resultado da Divisao");
                break;
            }

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (escolha != 0);

    free(matrizes);
    return 0;
}

// --- FUNÇÕES AUXILIARES E MATEMÁTICAS ---

Matriz criarMatriz() {
    Matriz m;
    printf("Linhas (max %d): ", MAX);
    scanf("%d", &m.linhas);
    printf("Colunas (max %d): ", MAX);
    scanf("%d", &m.colunas);

    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &m.dados[i][j]);
        }
    }
    return m;
}

void exibirMatriz(Matriz m, char *nome) {
    printf("\n--- %s (%dx%d) ---\n", nome, m.linhas, m.colunas);
    for (int i = 0; i < m.linhas; i++) {
        printf("| ");
        for (int j = 0; j < m.colunas; j++) {
            printf("%8.2lf ", m.dados[i][j]);
        }
        printf("|\n");
    }
}

int validarSomaSub(Matriz a, Matriz b) {
    return (a.linhas == b.linhas && a.colunas == b.colunas);
}

int validarMultiplicacao(Matriz a, Matriz b) {
    return (a.colunas == b.linhas);
}

Matriz somarMatrizes(Matriz a, Matriz b) {
    Matriz res = {a.linhas, a.colunas, {{{0}}}};
    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            res.dados[i][j] = a.dados[i][j] + b.dados[i][j];
    return res;
}

Matriz subtrairMatrizes(Matriz a, Matriz b) {
    Matriz res = {a.linhas, a.colunas, {{{0}}}};
    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            res.dados[i][j] = a.dados[i][j] - b.dados[i][j];
    return res;
}

Matriz multiplicarMatrizes(Matriz a, Matriz b) {
    Matriz res = {a.linhas, b.colunas, {{{0}}}};
    for (int i = 0; i < res.linhas; i++) {
        for (int j = 0; j < res.colunas; j++) {
            res.dados[i][j] = 0.0;
            for (int k = 0; k < a.colunas; k++) {
                res.dados[i][j] += a.dados[i][k] * b.dados[k][j];
            }
        }
    }
    return res;
}

int calcularInversa(Matriz m, Matriz *inv) {
    if (m.linhas != m.colunas) return 0;
    int n = m.linhas;
    double a[MAX][MAX*2];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = m.dados[i][j];
            a[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        double pivo = a[i][i];
        int pivotRow = i;
        for (int r = i + 1; r < n; r++) {
            if (fabs(a[r][i]) > fabs(pivo)) {
                pivo = a[r][i];
                pivotRow = r;
            }
        }

        if (fabs(pivo) < 1e-9) return 0;

        if (pivotRow != i) {
            for (int j = 0; j < 2 * n; j++) {
                double temp = a[i][j];
                a[i][j] = a[pivotRow][j];
                a[pivotRow][j] = temp;
            }
        }

        for (int j = i; j < 2 * n; j++) a[i][j] /= pivo;

        for (int r = 0; r < n; r++) {
            if (r != i) {
                double fator = a[r][i];
                for (int j = i; j < 2 * n; j++) a[r][j] -= fator * a[i][j];
            }
        }
    }

    inv->linhas = n;
    inv->colunas = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv->dados[i][j] = a[i][j + n];

    return 1;
}

Matriz dividirMatrizes(Matriz a, Matriz b, int *sucesso) {
    Matriz bInv, vazia = {0, 0, {{{0}}}};
    *sucesso = 0;

    if (b.linhas != b.colunas || !calcularInversa(b, &bInv)) return vazia;
    if (!validarMultiplicacao(a, bInv)) return vazia;

    *sucesso = 1;
    return multiplicarMatrizes(a, bInv);
}