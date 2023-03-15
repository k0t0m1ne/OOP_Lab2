#pragma once
#include <functional>
#include <iostream>
#include <fstream>
#include <list>
using namespace std;
template<typename K, typename V>
class BinaryTree
{
    struct Node {
        K key;
        V data;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(K key, V data, Node* l = nullptr, Node* r = nullptr) :
            key(key), data(data), left(l), right(r) {}
        Node(Node* other) :
            key(other->key), data(other->data) {}
    };
    int size;
    Node* tree;
    void copy(Node*, Node*);
    void del(Node*);
    void writeNode(Node*, std::ofstream&) const;
    bool findNodes(Node*) const;
    list <V> listNode(Node* tree) const;
    list <K> listKeys(Node* tree) const;
public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    void clear();
    void insertItem(K key, V data);
    void deleteItem(K key);
    bool find(K key) const;
    void write(const std::string& path) const;
    void read(const std::string& path);
    V& operator[](K key) const;
    list <V> lst() const;
    list <K> getKeys() const;
    bool operator==(const BinaryTree& other)const;
    bool operator!=(const BinaryTree& other)const { return not ((*this) == other); }
    int getSize() const { return size; }
    bool empty();
};

template<typename K, typename V>
inline void BinaryTree<K, V>::copy(Node* initialTree, Node* copyTree)
{
    initialTree = new Node(copyTree);
    if (copyTree->left) copy(initialTree->left, copyTree->left);
    if (copyTree->right) copy(initialTree->right, copyTree->right);
}

template<typename K, typename V>
inline void BinaryTree<K, V>::del(Node* delTree)
{
    if (delTree != nullptr) {
        if (delTree->left) del(delTree->left);
        if (delTree->right) del(delTree->right);
        delete delTree;
    }
}

template<typename K, typename V>
inline void BinaryTree<K, V>::
writeNode(Node* tree, std::ofstream& fout) const
{
    if (tree->left) writeNode(tree->left, fout);
    fout << tree->key << " " << tree->data << "\n";
    if (tree->right) writeNode(tree->right, fout);
}

template<typename K, typename V>
inline bool BinaryTree<K, V>::findNodes(Node* other) const
{
    if (not find(other->key) or (*this)[other->key] != other->data)
        return false;
    if (other->left and not findNodes(other->left))
        return false;
    if (other->right and not findNodes(other->right))
        return false;
    return true;

}


template<typename K, typename V>
inline bool BinaryTree<K, V>::empty()
{
    return (size == 0);
}
template<typename K, typename V>
inline BinaryTree<K, V>::BinaryTree()
{
    size = 0;
    tree = nullptr;
}

template<typename K, typename V>
inline BinaryTree<K, V>::BinaryTree(const BinaryTree& other)
{
    copy(tree, other.tree);
}

template<typename K, typename V>
inline BinaryTree<K, V>::~BinaryTree()
{
    clear();
}

template<typename K, typename V>
inline void BinaryTree<K, V>::clear()
{
    size = 0;
    del(tree);
    tree = nullptr;
}

template<typename K, typename V>
inline void BinaryTree<K, V>::insertItem(K key, V data)
{
    if (find(key)) {
        (*this)[key] = data;
        return;
    }
    bool isReady = false;
    if (tree == nullptr) {
        isReady = true;
        tree = new Node(key, data);
    }
    Node* curr = tree;
    while (not isReady) {
        if (curr->key >= key) {
            isReady = curr->left == nullptr;
            if (isReady)
                curr->left = new Node(key, data);
            else
                curr = curr->left;
        }
        else {
            isReady = curr->right == nullptr;
            if (isReady)
                curr->right = new Node(key, data);
            else
                curr = curr->right;
        }
    }
    ++size;
}

template<typename K, typename V>
inline void BinaryTree<K, V>::deleteItem(K key)
{
    if (not find(key)) {
        return;
    }
    bool isReady = false;
    if (tree->key == key) {
        isReady = true;
        delete tree;
    }
    Node* curr = tree;
    while (not isReady) {
        if (curr->key > key) {
            if (curr->left == nullptr)
                throw "key Error";
            isReady = curr->left->key == key;
            if (isReady) {
                Node* temp = curr->left;
                curr->left = temp->right;
                while (curr->left)curr = curr->left;
                curr->left = temp->left;
                delete temp;
            }
            else {
                curr = curr->left;
            }
        }
        else if (curr->key < key) {
            if (curr->right == nullptr)
                throw "key Error";
            isReady = curr->right->key == key;
            if (isReady) {
                Node* temp = curr->right;
                curr->right = temp->left;
                while (curr->right)curr = curr->right;
                curr->right = temp->right;
                delete temp;
            }
            else {
                curr = curr->right;
            }
        }
    }
    --size;
}


template<typename K, typename V>
inline bool BinaryTree<K, V>::find(K key) const
{
    Node* curr = tree;
    while (curr != nullptr and curr->key != key) {
        if (curr->key > key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr != nullptr;
}

template<typename K, typename V>
inline void BinaryTree<K, V>::write(const std::string& path) const
{
    std::ofstream fout(path);
    writeNode(tree, fout);
    fout.close();
}

template<typename K, typename V>
inline void BinaryTree<K, V>::read(const std::string& path)
{
    clear();
    std::ifstream fin(path);
    K key;
    V data;
    while (fin >> key >> data) {
        insertItem(key, data);
    }
    fin.close();
}

template<typename K, typename V>
inline V& BinaryTree<K, V>::operator[](K key) const
{
    Node* curr = tree;
    while (curr != nullptr and curr->key != key) {
        if (curr->key > key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (curr != nullptr)
        return curr->data;
    throw "key Error";
}

template<typename K, typename V>
inline list<V> BinaryTree<K, V>::lst() const
{
    return listNode(tree);
}

template<typename K, typename V>
inline list<K> BinaryTree<K, V>::getKeys() const
{
    return listKeys(tree);
}

template<typename K, typename V>
inline list<K> BinaryTree<K, V>::listKeys(Node* tree) const
{
    list<K> values1, values2;
    if (tree->left != nullptr) values1 = listKeys(tree->left);
    values1.push_back(tree->key);
    if (tree->right != nullptr)
        values2 = listKeys(tree->right);
    values1.insert(values1.end(),
                   values2.begin(), values2.end());
    return *(new list<K>(values1));
}

template<typename K, typename V>
inline list<V> BinaryTree<K, V>::listNode(Node* tree) const
{
    list<V> values1, values2;
    if (tree->left != nullptr) values1 = listNode(tree->left);
    values1.push_back(tree->data);
    if (tree->right != nullptr)
        values2 = listNode(tree->right);
    values1.insert(values1.end(),
                   values2.begin(), values2.end());
    return *(new list<V>(values1));
}

template<typename K, typename V>
inline bool BinaryTree<K, V>::operator==(const BinaryTree& other) const
{
    if (size != other.size)
        return false;
    if (other.size == 0)
        return true;
    return findNodes(other.tree);
}

