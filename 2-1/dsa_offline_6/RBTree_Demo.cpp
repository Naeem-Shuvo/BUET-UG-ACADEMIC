#include <bits/stdc++.h>
using namespace std;

// Same Red-Black Tree implementation
enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        Color color;
        Node *left, *right, *parent;
        Node(T data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    Node* root;
    
    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }
    
    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }
    
    void fixInsert(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    Node* searchNode(Node* node, T data) {
        if (node == nullptr || node->data == data) return node;
        if (data < node->data) return searchNode(node->left, data);
        else return searchNode(node->right, data);
    }
    
    void inorderHelper(Node* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

public:
    RedBlackTree() : root(nullptr) {}
    
    bool insert(T data) {
        if (search(data)) return false;
        
        Node* newNode = new Node(data);
        Node* parent = nullptr;
        Node* current = root;
        
        while (current != nullptr) {
            parent = current;
            if (newNode->data < current->data) current = current->left;
            else current = current->right;
        }
        
        newNode->parent = parent;
        if (parent == nullptr) root = newNode;
        else if (newNode->data < parent->data) parent->left = newNode;
        else parent->right = newNode;
        
        fixInsert(newNode);
        return true;
    }
    
    bool search(T data) {
        return searchNode(root, data) != nullptr;
    }
    
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
};

int main() {
    // Example 1: Red-Black Tree with integers
    cout << "=== Integer Red-Black Tree ===" << endl;
    RedBlackTree<int> intTree;
    intTree.insert(10);
    intTree.insert(5);
    intTree.insert(15);
    intTree.insert(3);
    intTree.insert(7);
    cout << "Inorder: ";
    intTree.inorder();
    cout << "Search 7: " << (intTree.search(7) ? "Found" : "Not Found") << endl;
    cout << endl;
    
    // Example 2: Red-Black Tree with doubles
    cout << "=== Double Red-Black Tree ===" << endl;
    RedBlackTree<double> doubleTree;
    doubleTree.insert(3.14);
    doubleTree.insert(2.71);
    doubleTree.insert(1.41);
    doubleTree.insert(1.73);
    cout << "Inorder: ";
    doubleTree.inorder();
    cout << endl;
    
    // Example 3: Red-Black Tree with strings
    cout << "=== String Red-Black Tree ===" << endl;
    RedBlackTree<string> stringTree;
    stringTree.insert("apple");
    stringTree.insert("banana");
    stringTree.insert("cherry");
    stringTree.insert("date");
    cout << "Inorder: ";
    stringTree.inorder();
    cout << "Search 'banana': " << (stringTree.search("banana") ? "Found" : "Not Found") << endl;
    
    return 0;
}
