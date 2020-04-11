#include <iostream>
#include <vector>
#include <string>

using namespace std;

void getMinimumPenalty(const string& seq1, const string& seq2, int penaltyXY, int penaltyGap) {
    int length1 = seq1.size();
    int length2 = seq2.size();

    vector<vector<int>> dp(length1+1, vector<int>(length2+1));

    // initialize the dynamic programming table
    for (int i = 0; i <= length1; i++) {
        dp[i][0] = i * penaltyGap;
    }

    for (int j = 0; j <= length2; j++) {
        dp[0][j] = j * penaltyGap;
    }

    for (int i = 1; i <= length1; i++) {
        for (int j = 1; j <= length2; j++) {
            if (seq1[i-1] == seq2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = min({dp[i-1][j-1] + penaltyXY, 
                                dp[i-1][j] + penaltyGap,
                                dp[i][j-1] + penaltyGap});
            }
        }
    }

    // create the alignment array
    string seq1Alig(length1+length2, '_');
    string seq2Alig(length1+length2, '_');

    int seq1pos = length1 + length2;
    int seq2pos = length1 + length2;

    int i = length1 + 1;
    int j = length2 + 1;

    while (!(i == 0 || j == 0)) {
        if (seq1[i-1] == seq2[j-1]) {
            seq1Alig[seq1pos--] = seq1[i-1];
            seq2Alig[seq2pos--] = seq2[j-1];
            i--;
            j--;
        } else if (dp[i-1][j-1] + penaltyXY == dp[i][j]) {
            seq1Alig[seq1pos--] = seq1[i-1];
            seq2Alig[seq2pos--] = seq2[j-1];
            i--;
            j--;
        } else if (dp[i-1][j] + penaltyGap == dp[i][j]) {
            seq1Alig[seq1pos--] = seq1[i-1]; 
            seq2Alig[seq2pos--] = '_';
            i--;
        } else if (dp[i][j-1] + penaltyGap == dp[i][j]) {
            seq1Alig[seq1pos--] = '_';
            seq2Alig[seq2pos--] = seq2[j-1];
            j--;
        }
    }

    while (seq1pos > 0) {
        if (i > 0) seq1Alig[seq1pos--] = seq1[--i];
        else seq1Alig[seq1pos--] = '_';
    }

    while (seq2pos > 0) {
        if (j > 0) seq2Alig[seq2pos--] = seq2[--j];
        else seq2Alig[seq2pos--] = '_';
    }

    int id = 0;
    for (int i = 0; i < length1 + length2; i++) {
        if ((seq1Alig[i] == seq2Alig[i]) && (seq2Alig[i] == '_'))
            id++;
    }

    cout << "Alignment sequence 1: " << seq1Alig.substr(id) << endl;
    cout << "Alignment sequence 2: " << seq2Alig.substr(id) << endl;

}

int main() {
    // input strings 
    string gene1 = "AGGGCTAGCTGTACC"; 
    string gene2 = "AGGCATCAGTCAC"; 
      
    // intialsing penalties of different types 
    int misMatchPenalty = 3; 
    int gapPenalty = 2; 

    getMinimumPenalty(gene1, gene2, misMatchPenalty, gapPenalty);

    return 0;
}