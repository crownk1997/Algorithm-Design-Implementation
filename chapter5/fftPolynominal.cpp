#include <iostream>
#include <vector>

using namespace std;

typedef complex<double> cd;

vector<cd> fft(vector<cd>& a) {
    int length = a.size();

    if (length == 1)
        return vector<cd>(1, a[0]);
    
    vector<cd> w(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        w[i] = cd(cos(alpha), sin(alpha));
    }

    vector<cd> Aeven(n/2), Aodd(n/2);
    for (int i = 0; i < n / 2; i++) {
        Aeven[i] = a[i*2];
        Aodd[i] = a[i*2 + 1];
    }

    vector<cd> y0 = fft(Aeven);
    vector<cd> y1 = fft(Aodd);

    vector<cd> result(n);

    for (int k = 0; k < n / 2; k++) {
        result[k] = result[0] + w[k] * y1[k];
        result[k + n/2] = y0[k] - w[k] * y1[k];
    }

    return result;
}

int main() {
    vector<cd> a{1, 2, 3, 4};
    vector<cd> b = fft(a);

    return 0;
}