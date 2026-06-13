#include <bits/stdc++.h>
using namespace std;

template<typename Key, typename Value, typename Compare = std::less<Key>>
class RBTree {

    enum Color { RED, BLACK };

    class Node {
        Key key;
        Value val;
        Color color;
        Node *left, *right, *parent;

        Node(Key k, Value v)
            : key(k), val(v), color(RED),
              left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;
    Compare comp;

public:

    RBTree() : root(nullptr) {}

   //rot

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;

        if (y->left) y->left->parent = x;
        y->parent = x->parent;

        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;

        if (x->right) x->right->parent = y;
        x->parent = y->parent;

        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

     //INSERT

    void insert(Key key, Value val) {

        Node* z = new Node(key, val);
        Node* y = nullptr;
        Node* x = root;

        while (x) {
            y = x;
            if (comp(z->key, x->key)) x = x->left;
            else x = x->right;
        }

        z->parent = y;

        if (!y) root = z;
        else if (comp(z->key, y->key)) y->left = z;
        else y->right = z;

        insertFix(z);
    }

private:

    void insertFix(Node* z) {

        while (z->parent && z->parent->color == RED) {

            if (z->parent == z->parent->parent->left) {

                Node* y = z->parent->parent->right; // uncle

                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {

                Node* y = z->parent->parent->left;

                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        root->color = BLACK;
    }

public:

    //find

    bool contains(Key key) {
        Node* cur = root;
        while (cur) {
            if (key == cur->key) return true;
            if (comp(key, cur->key)) cur = cur->left;
            else cur = cur->right;
        }
        return false;
    }

    /* ================= INORDER (DEBUG) ================= */

    void inorder() {
        inorder(root);
        cout << endl;
    }

private:

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
};
