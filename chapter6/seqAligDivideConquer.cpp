#include <iostream>
#include <vector>
#include <string>

using namespace std;

class seqAlignDivideConquer {
private:
    int misMatchPenalty = 3; 
    int gapPenalty = 2;

    vector<pair<int, int>> indexArray; // store the dp result and reconstruct the alignment sequence

    int findMinimumCost(const vector<int>& forward, const vector<int>& backward);
    vector<int> spaceEfficientForward(const char* seq1, const char* seq2);
    vector<int> spaceEfficientBackWard(const char* seq1, const char* seq2);

public:

    void seqAlignment(const char* seq1, const char* seq2);    
};

int seqAlignDivideConquer::findMinimumCost(const vector<int>& foward, const vector<int>& backward) {
    int minimumIndex = -1;
    int minimumValue = 100000;
    int length = forward.size();
    for (int i = 0; i < length; i++) {
        if (forward[i] + backward[i] < minimumValue) {
            minimumValue = forward[i] + backward[i];
            minimumIndex = i;
        }
    }
    return minimumINdex;
}

vector<int> seqAlignDivideConquer::spaceEfficientForward(const char* seq1, const char* seq2) {
    int length1 = strlen(seq1); // the last character is '0'
    int length2 = strlen(seq2);
    vector<vector<int>> B(2, vector<int>(length1+1));

    for (int i = 0; i <= length1; i++) {
        B[0][i] = i * gapPenalty;
    }

    for (int i = 1; i <= length2; i++) {
        B[1][0] = i * gapPenalty;
        for (int j = 1; j <= length1; j++) {
            if (seq1[j-1] == seq2[i-1]) {
                B[1][j] = B[0][j-1];
            } else {
                B[1][j] = min({misMatchPenalty + B[0][j-1],
                            gapPenalty + B[1][j-1],
                            gapPenalty + B[0][j]});
            }
        }
        // update our array B to store new value
        B[0] = B[1];
    }

    // find the minimum value of penalty

    cout << " the minimum penalty is " << B[1][length1] << endl;


    return B[1];
}

vector<int> seqAlignDivideConquer::spaceEfficientBackWard(const char* seq1, const char* seq2) {
    int length1 = strlen(seq1);
    int length2 = strlen(seq2);
    vector<vector<int>> B(2, vector<int>(length1 + 1));

    // initialize the gap penalty
    for (int i = 0; i <= length1; i++) {
        B[0][i] = i * gapPenalty;
    }

    for (int i = 1; i <= length2; i++) {
        B[1][0] = i * gapPenalty;
        for (int j = 1; j <= length1; j++) {
            if (seq1[length1-j] == seq2[length2-i]) {
                B[1][j] = B[0][j-1];
            } else {
                B[1][j] = min({misMatchPenalty + B[0][j-1],
                            gapPenalty + B[1][j-1],
                            gapPenalty + B[0][j]}); 
            }
        }
        B[0] = B[1];
    }

    cout << " The minimum penalty is " << B[1][length1] << endl; 
    
    return B[0];
}

void seqAlignDivideConquer::seqAlignment(const char* seq1, const char* seq2) {
    int length1 = strlen(seq1);
    int length2 = strlen(seq2);
    if (length1 <= 2 || length2 <= 2) {
        // in this case, we directly compute the optimal alignment
    }

    int middle = length2 >> 1;
    char* seq2Half = new char[middle+1];
    memcpy(seq2Half, seq2, sizeof(char) * middle);
    vector<int> forward = spaceEfficientForward(seq1, seq2Half);
    vector<int> backward = spaceEfficientBackWard(seq1, seq2+middle);

    // add the index into global solution
    int index = findMinimumCost(forward, backward);
    indexArray.push_back(make_pair(index, middle));

    // recursive call
    char* seq1Half = new char[index+1];
    memcpy(seq1Half, seq1, sizeof(char) * index);
    seqAlignment(seq1Half, seq2Half);
    seqAlignment(seq1+index, seq1+middle);
}

int main() {
    const char seq1[] = "AGGGCTAGCTGTACC";
    const char seq2[] = "AGGCATCAGTCAC";
    seqAlignDivideConquer solution;
    vector<int> result = solution.spaceEfficientForward(seq1, seq2);
    vector<int> result1 = solution.spaceEfficientBackWard(seq1, seq2);

    return 0;
}