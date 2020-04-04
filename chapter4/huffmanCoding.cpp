#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

struct Node {
    Node* parent;
    Node* leftChild;
    Node* rightChild;

    string chars;
    float freq;
};

void HuffmanCode(const vector<char>& characters, const vector<float>& frequency) {
    // first build heap 
    auto cmpNode = [](Node* node1, Node* node2) {
        return node1->freq < node2->freq;
    }
    pirority_queue<Node, vector<Node>, decltype(cmpNode)> pq;

    int size1 = characters.size();
    int size2 = frequency.size();
    assert(size1 == size2);
    for (int i = 0; i < size1; i++) {
        Node* temp = new Node();
        temp->parent = nullptr;
        temp->leftChild = nullptr;
        temp->rightChild = nullptr;
        temp->chars = characters[i];
        temp->freq = frequency[i];
        pq.insert(temp);
    }

    while (pq.size() != 1) {
        leftNode = pq.top();
        pq.pop();
        rightNode = pq.top();
        pq.pop();

        Node* topNode = new Node();
        topNode->parent = nullptr;
        topNode->leftChild = leftNode;
        topNode->rightChild = rightNode;
        topNode->chars = leftNode->chars + rightNode->chars;
        topNode->freq = leftNode->freq + rightNode->freq;

        pq.insert(topNode);
    }

    Node* head = pq.top();


}

void printCode(Node* head, vector<int>& coding, int level) {
    if (head == nullptr)
        return;
    
    if (head->leftChild) {
        coding[level] = 0;
        printCode(head->leftChild, coding, ++level);
    }

    if (head->rightChild) {
        coding[level] = 1;
        printCode(head->rightChild, coding, ++level);
    }

    if (head->rightChild == nullptr && head->leftChild == nullptr) {
        cout << "Character: " << head->chars << " Coding: ";
        printVec(coding); 
    }
}

void printVec(const vector<int>& input) {
    copy(input.begin(). input.end(),
    ostream_iterator<int>(cout, ""));
    cout << endl;
}