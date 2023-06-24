#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

int random(int min, int max) {
    return rand()%(max - min) + min;
}

int main() {
    srand(time(NULL));

    int array[10];
    for (int i = 0; i < 10; i++) { 
        array[i] = random(2,10); 
        printf("%d ", array[i]);
    }
    printf("\n\n");

    int a[4][10];
    int skalar[4];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j< 10; j++) { 
            a[i][j] = random(0,3); 
            skalar[i] += array[j] * a[i][j];
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i<4; i++) { printf("%d ", skalar[i]); }


    return 0;
}