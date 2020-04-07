#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int MergeCount(vector<int>& input, vector<int>& temp, int left, int mid, int right);
int SortCount(vector<int>& input, vector<int>& temp, int left, int right) {
    int mid, invCount = 0;
    if (left < right) {
        mid = ((right - left) >> 1) + left;
        invCount += SortCount(input, temp, left, mid);
        invCount += SortCount(input, temp, mid+1, right);
        invCount += MergeCount(input, temp, left, mid+1, right);
    }

    return invCount;
}

int MergeCount(vector<int>& input, vector<int>& temp, int left, int mid, int right) {
    int invCount = 0;
    int index1 = left;
    int index2 = mid;
    int storeIndex = left;
    while ((index1 <= mid) && (index2 <= right)) {
        if (input[index1] <= input[index2]) {
            temp[storeIndex++] = input[index1++];
        } else {
            temp[storeIndex++] = input[index2++];
            invCount += mid - index1;
        }
    }

    while (index1 <= mid) {
        temp[storeIndex++] = input[index1++];
    }

    while (index2 <= right) {
        temp[storeIndex++] = input[index2++];
    }

    copy(&input[left], &input[right], &temp[left]);

    return invCount;    
}

int main() {
    vector<int> input = {8, 4, 3, 1};
    vector<int> temp(input.size());

    cout << "The number of inversion is " << SortCount(input, temp, 0, input.size() - 1) << endl;

    return 0;
}