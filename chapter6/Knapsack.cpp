#include <iostream>
#include <vector>

using namespace std;

void findSolution(const vector<vector<int>>& resultMatrix, const vector<int>& weights) {
    int i = resultMatrix.size()-1;
    for (int j = resultMatrix[0].size() - 1; j >= 0;) {
        if (resultMatrix[i][j] == resultMatrix[i][j-1])
            j--;
        else {
            if (i == 0)
                break;
            j -= weights[i-1];
            cout << "Item: " << i << " Weight: " << weights[i-1] << endl;
            i--;
        }
    }
}

int maxBenifit(int totalWeight, const vector<int>& weights) {
    int totalInd = weights.size();
    vector<vector<int>> M(totalInd+1, vector<int>(totalWeight+1));

    // initialize the first row of result matrix as zeros
    for (int j = 0; j < totalWeight+1; j++)
        M[0][j] = 0;
    for (int i = 0; i < totalInd+1; i++)
        M[i][0] = 0;
    
    for (int i = 1; i <= totalInd; i++) {
        for (int j = 0; j < totalWeight; j++) {
            if (j < weights[i-1])
                M[i][j] = M[i-1][j];
            else {
                M[i][j] = max(M[i-1][j], M[i-1][j-weights[i-1]] + weights[i-1]);
            }
        }
    }

    findSolution(M, weights);
    
    return M[totalInd][totalWeight-1];    
}

int main() {
    vector<int> weights = {2, 2, 3, 5, 8};
    int totalWeight = 10;

    cout << "Max benifit is: " << maxBenifit(totalWeight, weights) << endl;

    return 0;
}