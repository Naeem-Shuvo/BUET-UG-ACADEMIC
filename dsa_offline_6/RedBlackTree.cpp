#include <bits/stdc++.h>
using namespace std;

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
    
    // Rotleft 
    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        
        if (y->left != nullptr)
            y->left->parent = x;
        
        y->parent = x->parent;
        
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        
        y->left = x;
        x->parent = y;
    }
    
    // Rotright 
    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        
        if (y->right != nullptr)
            y->right->parent = x;
        
        y->parent = x->parent;
        
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        
        y->right = x;
        x->parent = y;
    }
    
    // fix  after insertion
    void fixInsert(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                
                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    // Case 2: Node is right child
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    // Case 3: Node is left child
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            }
            else {
                Node* uncle = node->parent->parent->left;
                
                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else {
                    // Case 2: Node is left child
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    // Case 3: Node is right child
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    // Fix Red-Black Tree properties after deletion
    void fixDelete(Node* node) {
        while (node != root && (node == nullptr || node->color == BLACK)) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;
                
                // Case 1: Sibling is RED
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }
                
                // Case 2: Sibling's children are BLACK
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    // Case 3: Sibling's right child is BLACK
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }
                    // Case 4: Sibling's right child is RED
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            }
            else {
                Node* sibling = node->parent->left;
                
                // Case 1: Sibling is RED
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }
                
                // Case 2: Sibling's children are BLACK
                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    // Case 3: Sibling's left child is BLACK
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }
                    // Case 4: Sibling's left child is RED
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        if (node != nullptr)
            node->color = BLACK;
    }
    
    // Find node with minimum value
    Node* minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    
    // Replace node u with node v
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        
        if (v != nullptr)
            v->parent = u->parent;
    }
    
    // Delete node from tree
    void deleteNode(Node* node) {
        Node* y = node;
        Node* x;
        Color originalColor = y->color;
        
        if (node->left == nullptr) {
            x = node->right;
            transplant(node, node->right);
        }
        else if (node->right == nullptr) {
            x = node->left;
            transplant(node, node->left);
        }
        else {
            y = minimum(node->right);
            originalColor = y->color;
            x = y->right;
            
            if (y->parent == node) {
                if (x != nullptr)
                    x->parent = y;
            }
            else {
                transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            
            transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
        
        delete node;
        
        if (originalColor == BLACK && x != nullptr)
            fixDelete(x);
    }
    
    // Search for a node
    Node* searchNode(Node* node, T data) {
        if (node == nullptr || node->data == data)
            return node;
        
        if (data < node->data)
            return searchNode(node->left, data);
        else
            return searchNode(node->right, data);
    }
    
    // Inorder traversal
    void inorderHelper(Node* node) {
        if (node == nullptr)
            return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
    
    // Count nodes less than value
    int countLessHelper(Node* node, T value) {
        if (node == nullptr)
            return 0;
        
        if (node->data < value)
            return 1 + countLessHelper(node->left, value) + countLessHelper(node->right, value);
        else
            return countLessHelper(node->left, value);
    }

public:
    RedBlackTree() : root(nullptr) {}
    
    // Insert a new value
    bool insert(T data) {
        // Check if already exists
        if (search(data))
            return false;
        
        Node* newNode = new Node(data);
        Node* parent = nullptr;
        Node* current = root;
        
        // Find position for new node
        while (current != nullptr) {
            parent = current;
            if (newNode->data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        
        newNode->parent = parent;
        
        if (parent == nullptr)
            root = newNode;
        else if (newNode->data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
        
        fixInsert(newNode);
        return true;
    }
    
    // Delete a value
    bool remove(T data) {
        Node* node = searchNode(root, data);
        if (node == nullptr)
            return false;
        
        deleteNode(node);
        return true;
    }
    
    // Search for a value
    bool search(T data) {
        return searchNode(root, data) != nullptr;
    }
    
    // Count elements less than value
    int countLess(T value) {
        return countLessHelper(root, value);
    }
    
    // Print inorder traversal
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
    
    // Check if tree is empty
    bool isEmpty() {
        return root == nullptr;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N;
    cin >> N;
    cout << N << endl;
    
    RedBlackTree<int> tree;
    
    for (int i = 0; i < N; i++) {
        int command;
        cin >> command;
        
        if (command == 0) {
            // Terminate program with priority X
            int x;
            cin >> x;
            cout << command << " " << x << " ";
            if (tree.remove(x))
                cout << "1" << endl;
            else
                cout << "0" << endl;
        }
        else if (command == 1) {
            // Initiate a program with priority X
            int x;
            cin >> x;
            cout << command << " " << x << " ";
            if (tree.insert(x))
                cout << "1" << endl;
            else
                cout << "0" << endl;
        }
        else if (command == 2) {
            // Search the program with priority X
            int x;
            cin >> x;
            cout << command << " " << x << " ";
            if (tree.search(x))
                cout << "1" << endl;
            else
                cout << "0" << endl;
        }
        else if (command == 3) {
            // Find the number of programs with priority less than X
            int x;
            cin >> x;
            cout << command << " " << x << " " << tree.countLess(x) << endl;
        }
    }
    
    return 0;
}
