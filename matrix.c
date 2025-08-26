#include <stdio.h>


void normal2x2(int A[10][10], int B[10][10], int C[10][10]) {
    C[1][1] = A[1][1] * B[1][1] + A[1][2] * B[2][1];
    C[1][2] = A[1][1] * B[1][2] + A[1][2] * B[2][2];
    C[2][1] = A[2][1] * B[1][1] + A[2][2] * B[2][1];
    C[2][2] = A[2][1] * B[1][2] + A[2][2] * B[2][2];
}

void strassen2x2(int A[10][10], int B[10][10], int C[10][10]) {
    int p, q, r, s, t, u, v;

    p = (A[1][1] + A[2][2]) * (B[1][1] + B[2][2]);
    q = (A[2][1] + A[2][2]) * B[1][1];
    r = A[1][1] * (B[1][2] - B[2][2]);
    s = A[2][2] * (B[2][1] - B[1][1]);
    t = (A[1][1] + A[1][2]) * B[2][2];
    u = (A[2][1] - A[1][1]) * (B[1][1] + B[1][2]);
    v = (A[1][2] - A[2][2]) * (B[2][1] + B[2][2]);

    C[1][1] = p + s - t + v;
    C[1][2] = r + t;
    C[2][1] = q + s;
    C[2][2] = p + r - q + u;
}

void normalMultiply(int n, int A[10][10], int B[10][10], int C[10][10]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = 0;
            for (int k = 1; k <= n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n;
    printf("Enter matrix size (n x n): ");
    scanf("%d", &n);

    int A[10][10], B[10][10], C[10][10];

    printf("Enter matrix A:\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &B[i][j]);

    if (n == 2) {

        normal2x2(A, B, C);
    } else {
        normalMultiply(n, A, B, C);
    }

    printf("Result matrix C:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}