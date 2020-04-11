#include <iostream>
#include <vector>

using namespace std;

void findSolution(const vector<vector<int>>& resultMatrix, const vector<int>& weights) {
    int i = resultMatrix.size()-1;
    for (int j = resultMatrix[0].size() - 1; (j >= 0) && (i >= 1);) {
        if (resultMatrix[i][j] == resultMatrix[i-1][j]) {
            i--;
        } else {
            cout << "Item " << i << " weights " << weights[i] << endl;
            j -= weights[i];
            i--;
        }
    }
}

void maxBenifit(int totalWeight, const vector<int>& weights) {
    int totalInd = weights.size();
    vector<vector<int>> M(totalInd+1, vector<int>(totalWeight+1));

    // initialize the first row of result matrix as zeros
    for (int j = 0; j < totalWeight+1; j++)
        M[0][j] = 0;
    for (int i = 0; i < totalInd+1; i++)
        M[i][0] = 0;
    
    for (int i = 1; i <= totalInd; i++) {
        for (int j = 1; j <= totalWeight; j++) {
            if (j < weights[i-1])
                M[i][j] = M[i-1][j];
            else {
                M[i][j] = max(M[i-1][j], M[i-1][j-weights[i-1]] + weights[i-1]);
            }
        }
    }

    findSolution(M, weights);
    
    cout << "Max benifit is " << M[totalInd][totalWeight] << endl;
}

int main() {
    vector<int> weights = {2, 2, 3, 5, 8};
    int totalWeight = 10;

    maxBenifit(totalWeight, weights);

    return 0;
}