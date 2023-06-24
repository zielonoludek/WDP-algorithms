#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>

int randomInt(int max) {
    srand(time(nullptr));
    return rand() % (max - 1);
}

std::vector<std::vector<int>> multiply(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b) {
    int rowsA = a.size();
    int colsA = a[0].size();
    int rowsB = b.size();
    int colsB = b[0].size();

    if (colsA != rowsB) {
        std::cout << "Nie mozna pomnozyc tych macierzy" << std::endl;
        return {};
    }

    std::vector<std::vector<int>> result(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {  result[i][j] += (a[i][k] * b[k][j]); }
        }
    }

    for (int i = 0; i < rowsA; i++) { for (int j = 0; j < colsB; j++) { result[i][j] = result[i][j] % 2; }}

    return result;
}

void zaszuminie(std::vector<std::vector<int>> &matrix) {
    int rows = matrix.size();
    int num = randomInt(rows);

    matrix[num][0] = (matrix[num][0] + 1) % 2;
};

std::vector<std::vector<int>> kodowanie( std::vector<std::vector<int>> matrix) {
    const std::vector<std::vector<int>> G = { {1,1,0,1}, {1,0,1,1}, {1,0,0,0}, {0,1,1,1}, {0,1,0,0}, {0,0,1,0},{0,0,0,1} };
    std::vector<std::vector<int>> result = multiply(G, matrix);
    return result;
};

void view(std::vector<std::vector<int>> matrix) {
    for (std::vector<int> row : matrix) {
        for (int el : row) { std::cout << el << " " << std::endl; }
    }
    std::cout << std::endl;
}

int blad(std::vector<std::vector<int>> matrix) {
    const std::vector<std::vector<int>> H = { {1,0,1,0,1,0,1}, {0,1,1,0,0,1,1}, {0,0,0,1,1,1,1} };
    std::vector<std::vector<int>> result = multiply(H, matrix);
    int blad = 0;

    view(result);

    for (int i = 0; i < result.size(); i++) { if (result[i][0] == 1) blad += pow(2, i); }
    return blad;
}

void naprawa(std::vector<std::vector<int>>& matrix, int blad) {
    matrix[blad-1][0] = (matrix[blad - 1][0] + 1) % 2;
}

void a() {
    std::vector<std::vector<int>> a = { {1}, {1}, {1}, {1} };
    std::vector<std::vector<int>> kodA = kodowanie(a);

    view(kodA);
    zaszuminie(kodA);
    view(kodA);
    int bladA = blad(kodA);
    std::cout << bladA << std::endl << std::endl;
    naprawa(kodA, bladA);
    view(kodA);
}

void b() {
    std::vector<std::vector<int>>  b = { {1}, {1}, {1}, {1},{1}, {1}, {1}, {1}, {1}, {1}, {1}, {1},{1}, {1}, {1}, {1},{1}, {1}, {1}, {1},{1}, {1}, {1}, {1},{1}, {1}, {1}, {1},{1}, {1}, {1}, {1},{1}, {1}, {1}, {1},{1}, {1}, {1}, {1} };
    std::vector<std::vector<int>> subB = {};
    std::vector<std::vector<int>> c = {};
    std::vector<std::vector<int>> outB = {};
    
    int a = 0;
    while (a < b.size()) {
        subB = { b.begin() + a, b.begin() + a + 4 };
        view(subB);
        subB = kodowanie(subB);
        zaszuminie(subB);
        view(subB);

        for (int i = 0; i < subB.size(); i++) { c.push_back(subB[i]); }
        
        int bladB = blad(subB);
        std::cout << bladB << std::endl << std::endl;
        naprawa(subB, bladB);
        view(subB);

        for (int i = 0; i < subB.size(); i++) { outB.push_back(subB[i]); }
        a += 4;
    }
    view(c);
    view(outB);
}

int main(){
    a();
    b();
   
    return 0;
}