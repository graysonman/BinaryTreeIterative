
#include "TreeT.h"


template<class T>
TreeT<T>::TreeT() {
    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {
    if (node == nullptr)
        return;

    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
}


template<class T>
void TreeT<T>::Add(T value) {

    Node* newNode = new Node;
    newNode->value = value;

    if (root == nullptr) {
        root = newNode;
        numNodes++;
        return;
    }

    Node* curr = root;
    while(true) {
        if (value < curr->value) {
            if (curr->left == nullptr){
                curr->left = newNode;
                break;
            }
            curr = curr->left;
        }
        else if (value > curr->value) {
            if (curr->right == nullptr){
                curr->right = newNode;
                break;
            }
            curr = curr->right;
        }
        else {
            delete newNode;
            return;
        }
    }
    numNodes++;
}

template<class T>
void TreeT<T>::Remove(T item) {
    RemoveHelper(root, item);
}

template<class T>
void TreeT<T>::RemoveHelper(Node*& subtree, T value) {

    if (value == subtree->value) {
        DeleteNode(subtree);  // Found the node. Now delete it.
    }
    else if (value < subtree->value) {
        subtree = subtree->left;    // go left
    }
    else {
        subtree = subtree->right;   // go right
    }
}

template<class T>
void TreeT<T>::DeleteNode(Node *&subtree) {

    T item;
    Node* tempPtr;

    tempPtr = subtree;
    if (subtree->right == NULL && subtree->left == NULL)
    {
        delete tempPtr;
        subtree = NULL;
    }
    else if (subtree->left == NULL)
    {
        subtree = subtree->right;
        delete tempPtr;
    }
    else if (subtree->right == NULL)
    {
        subtree = subtree->left;
        delete tempPtr;
    }
    else {
        GetPredecessor(subtree->left, item);
        subtree->info = item;
        RemoveHelper(subtree->left, item);
    }
}


template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T& value) {
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    value = curr->value;
}

template<class T>
bool TreeT<T>::Contains(T value) {
    Node* curr = root;

    while(curr != nullptr) {
        if (value == curr->value) {
            return true;
        }
        else if (value < curr->value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return false;
}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
    printQueue.empty();

    if (traverseOrder == IN_ORDER)
        PlaceInOrder(root);
    else if (traverseOrder == POST_ORDER)
        PlacePostOrder(root);
    else if (traverseOrder == PRE_ORDER)
        PlacePreOrder(root);
}

template<class T>
T TreeT<T>::GetNextItem() {
    T value = printQueue.front();  // Top, peek, front
    printQueue.pop();
    return value;
}

template<class T>
void TreeT<T>::PlacePreOrder(Node *node) {
    if (node == nullptr)
        return;

    printQueue.push(node->value);
    PlacePreOrder(node->left);
    PlacePreOrder(node->right);
}

template<class T>
void TreeT<T>::PlacePostOrder(Node *node) {
    if (node == nullptr)
        return;

    PlacePostOrder(node->left);
    PlacePostOrder(node->right);
    printQueue.push(node->value);
}

template<class T>
void TreeT<T>::PlaceInOrder(Node *node) {
    if (node == nullptr)
        return;

    PlaceInOrder(node->left);
    printQueue.push(node->value);
    PlaceInOrder(node->right);
}

template<class T>
TreeT<T>& TreeT<T>::operator=(const TreeT &otherTree) {

    CopyHelper(root, otherTree.root);
    numNodes = otherTree.numNodes;

    return *this;
}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node*& thisTree, TreeT::Node *otherTree) {
    if (otherTree == nullptr) {
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->value = otherTree->value;
    CopyHelper(thisTree->left, otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
}




