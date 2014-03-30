#include <iostream>
#include <iomanip>

using namespace std;
//                        A    B a goes first 
long double probability1[505][505];
long double probability2[505][505];

int values[] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 
    20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};

int main() {
    for (int i = 0; i < 505; i++) {
        for (int j = 0; j < 505; j++) {
            probability1[i][j] = 0.0L;
            probability2[i][j] = 0.0L;
        }
    }
    for (int i = 0; i < 505; i++) {
        probability1[0][i] = 1.0L;
        probability2[i][0] = 1.0L;
    }
    for (int i = 1; i < 200; i++) {
        for (int j = 1; j < 200; j++) {
            probability1[i][j] = 0.0L;
            probability2[i][j] = 0.0L;
            long double cumul1 = 99999999999.0L;
            long double cumul2 = 0.0L;
            for (int b = 3; b <= 23; b++) {
                long double tmpc1 = 0.0L;
                long double tmpc2 = 0.0L;
                int tmpcc1 = 0; int tmpcc2 = 0;
                for (int a = 0; a < 20; a++) {
                    for (int b2 = -1; b2 <= 1; b2++) {
                        int newi1 = i - values[a] < 0 ? i : i - values[a];
                        int newj1 = j - values[b + b2] < 0 ? j : j - values[b + b2];
                        if (i == newi1 && j == newj1) tmpcc1++;
                        tmpc1 += probability1[newi1][newj1];
                        tmpc2 += probability2[newi1][newj1];
                    }
                }
                tmpc1 *= 1.0L / (long double)(60 - tmpcc1);
                tmpc2 *= 1.0L / (long double)(60 - tmpcc1);
                if (cumul1 > tmpc1) {cumul1 = tmpc1;}
                if (cumul2 < tmpc2) {cumul2 = tmpc2;}
            }
            probability1[i][j] = cumul1;
            probability2[i][j] = cumul2;
        }
    }
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 2; j++) {
            cout << probability1[i][j] << " ";
        }
        cout << endl;
    }
    int n;
    while (cin >> n) {
        if (n == 0) break;
        cout << setprecision(15) << probability1[n][n] << " " << setprecision(15) << probability2[n][n] << endl;
    }
}