#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class Node {
    public :
    T *keys;
    int t;
    Node **C;
    int n;
    bool leaf;
    
    Node (int _t, bool _leaf);
    
    void traverse();
    
    Node<T> *search(T k);
    
    void search(T k, bool(* cmp)(T a, T b), vector<T> &result);
    
    void insertNonFull(T k);
    
    void splitChild(int i, Node<T> *y);
};

template<typename T>
Node<T>::Node (int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
    
    keys = new T[2*t-1];
    C = new Node<T>*[2*t-1];
    
    n = 0;
}

template<typename T>
void Node<T>::traverse() {
    cout<<" << ";
    int i;
    for(i=0;i<n;i++) {
        if(leaf == false)
            C[i]->traverse();
        cout<<keys[i]<<' ';
    }
    if(leaf == false)
        C[i]->traverse();
    cout<<" >> "<<endl;
}

template<typename T>
Node<T> *Node<T>::search(T k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    
    if (keys[i] == k)
        return this;
    
    if (leaf == true)
        return NULL;
    
    return C[i]->search(k);
}

template<typename T>
void Node<T>::search(T k, bool(* cmp)(T a, T b), vector<T> &answer) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;
    
    if (leaf == true) {
        while(i < n && cmp(k, keys[i])) {
            answer.push_back(keys[i]);
            i++;
        }
        return ;
    }
    
    while(i < n && cmp(k, keys[i])) {
        C[i]->search(k, cmp, answer);
        answer.push_back(keys[i]);
        i++;
    }
    C[i]->search(k, cmp, answer);
}

template<typename T>
void Node<T>::insertNonFull(T k) {
    int i = n-1;
    
    if(leaf == true) {
        while(i >= 0 && keys[i] > k) {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n++;
    }
    else {
        while(i >= 0 && keys[i] > k)
            i--;
        
        if(C[i+1]->n == 2*t-1) {
            splitChild(i+1, C[i+1]);
            
            if(keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

template<typename T>
void Node<T>::splitChild(int i, Node<T> *y) {
    
    Node<T> *z = new Node<T>(y->t, y->leaf);
    z->n = t-1;
    
    for(int j=0; j<t-1; j++)
        z->keys[j] = y->keys[j+t];
    
    if(y->leaf == false) {
        for(int j=0; j<t; j++)
            z->C[j] = y->C[j+t];
    }
    
    y->n = t - 1;
    
    for(int j = n; j>=i+1; j--)
        C[j+1] = C[j];
    
    C[i+1] = z;
    
    for(int j=n-1; j>=i; j--)
        keys[j+1] = keys[j];
    
    keys[i] = y->keys[t-1];
    
    n++;
}
