#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool allowBase(char base1, char base2) {
    if (base1 == 'A' && base2 == 'U')
        return true;
    else if (base1 == 'G' && base2 == 'C')
        return true;
    else if (base1 == 'G' && base2 == 'C')
        return true;
    else if (base1 == 'U' && base2 == 'A')
        return true;
    else
        return false;
}

void maxRNA(const string& RNAseq) {
    int length = RNAseq.size();
    // build up and initialize opt table
    vector<vector<int>> opt(length+1, vector<int>(length+1));
    // in the real application, we do not need to do that
    // because the initial value will be zero
    for (int j = 0; j < length+1; j++) {
        opt[0][j] = 0;
        opt[j][0] = 0;
    }

    for (int i = 1; i < length+1; i++) {
        for (int j = 1; j < length+1; j++) {
            if (j - i <= 4)
                opt[i][j] = 0;
        }
    }

    // start iteration
    for (int k = 5; k < length; k++) {
        for (int i = 1; i <= length - k; i++) {
            int j = i + k;
            // use the recurrence 
            int notInvolved = opt[i][j-1];
            int maxInvolved = 0;
            for (int t = i; t < j - 4; t++) {
                if (allowBase(RNAseq[j-1], RNAseq[t-1])) { // we should note that the index starts from zero
                    maxInvolved = max(maxInvolved, 1 + opt[i][t-1] + opt[t+1][j-1]);
                }
            }
            opt[i][j] = max(notInvolved, maxInvolved);
        }
    }

    for (int i = 0; i < length+1; i++) {
        for (int j = 0; j < length+1; j++)
            cout << opt[i][j] << " ";
        cout << endl;
    }

    cout << "Minimum cost is " << opt[1][length] << endl;
}

int main() {
    string RNAseq = "ACCGGUAGU";
    maxRNA(RNAseq);

    return 0;
}