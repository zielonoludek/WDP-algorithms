#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double sigmoid(double x) { return 1 / (1 + exp(-x)); }

double dS(double x) { return x * (1 - x); }

double init_weight() { return ((double)rand()) / ((double)RAND_MAX); }

int Normalize(double val) {
    if (val >= 0.5) return 1;
    return 0;
}

int main() {
    srand(time(NULL));

    static const int Inputs = 2;
    static const int HNodes = 2;
    static const int Outputs = 1;

    const double lr = 0.1;

    double Layer[2];
    double outLayer;

    double hLayerBias[2];
    double outLayerBias;

    double hWeights[2][2];
    double outWeights[2];

    static const int TSets = 4;
    int Tinputs[4][2] = { {0, 0}, {1, 0}, {0, 1}, {1, 1} };
    int Toutputs[4] = { 0, 1, 1, 0 };

    for (int i = 0; i < Inputs; i++) {
        for (int j = 0; j < HNodes; j++) { 
            hWeights[i][j] = init_weight();
            hLayerBias[i] = init_weight();
        }
        outWeights[i] = init_weight();
    }

    for (int i = 0; i < Outputs; i++) { outLayerBias = init_weight();}

    int TSetOrder[] = { 0,1,2,3 };
    int counter = 0;
    int t = 0;
    int f = 0;

    for (int n = 0; n < 10000; n++) {
        for (int i = 0; i < TSets; i++) {
            int x = TSetOrder[i];

            for (int j = 0; j < HNodes; j++) {
                double activation = hLayerBias[j];
                for (int k = 0; k < Inputs; k++) { activation += Tinputs[x][k] * hWeights[k][j]; }
                Layer[j] = sigmoid(activation);
            }

            double activation = outLayerBias;
            for (int j = 0; j < HNodes; j++) { activation += Layer[j] * outWeights[j]; }
            outLayer = sigmoid(activation);

            if (Normalize(outLayer) == Toutputs[i]) t += 1;
            else f += 1;

            //printf("Input: %d %d    Output: %f    Expected Output: %d\n", Tinputs[x][0], Tinputs[x][1], outLayer, Toutputs[i]);

            double deltaOut;
            double errorOut = (Toutputs[i] - outLayer);
            deltaOut = errorOut * dS(outLayer);

            double deltaH[2];
            for (int j = 0; j < HNodes; j++) {
                double errorHidden = 0.0;
                for (int k = 0; k < Outputs; k++) { errorHidden += deltaOut * outWeights[j]; } 
                deltaH[j] = errorHidden * dS(Layer[j]);
            }

            outLayerBias += deltaOut * lr;
            for (int j = 0; j < HNodes; j++) {
                outWeights[j] += Layer[j] * deltaOut * lr;
                hLayerBias[j] += deltaH[j] * lr;
                for (int k = 0; k < Inputs; k++) { hWeights[k][j] += Tinputs[i][k] * deltaH[j] * lr; }
            }

            counter += 1;
            if (counter % 1000 == 0) {
                printf("%d. t: %d     f: %d,       %d %% \n",counter, t, f, t/10);
                t = 0;
                f = 0;
            }
        }
    }
    return 0;
}
