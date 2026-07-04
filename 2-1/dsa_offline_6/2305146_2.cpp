#include <bits/stdc++.h>
using namespace std;
template <class Key, class Value>
class AvlBST
{
    class Node
    {
    public:
        Key k;
        Value val;
        int height;
        Node *left, *right;
        Node(Key key) : k(key), val(key), left(nullptr), right(nullptr), height(1) {}
    };

public:
    Node *root;
    AvlBST() : root(nullptr) {}
    void insert(Key key)
    {
        if (contains(key))
            cout << " 0" << endl;
        else
            cout << " 1" << endl;
        root = insertHelper(root, key);
    }

    Node *rightRotate(Node *node)
    {
        Node *newRoot = node->left;
        Node *rightOfNewRoot = newRoot->right;

        newRoot->right = node;
        node->left = rightOfNewRoot;

        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    Node *leftRotate(Node *node)
    {
        Node *newRoot = node->right;
        Node *leftOfNewRoot = newRoot->left;
        newRoot->left = node;
        node->right = leftOfNewRoot;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    int balanceFactor(Node *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }
    int getHeight(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    void updateHeight(Node *node)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node *insertHelper(Node *node, Key key)
    {
        // 1. Normal BST insertion
        if (node == nullptr)
            return new Node(key);
        if (key < node->k)
            node->left = insertHelper(node->left, key);
        else if (key > node->k)
            node->right = insertHelper(node->right, key);
        else
            return node; // duplicate

        // 2. Update height
        updateHeight(node);

        // 3. Check balance and rotate HERE at each level
        int bf = balanceFactor(node);

        // Left-Left case
        if (bf > 1 && node->left != nullptr && key < node->left->k)
            return rightRotate(node);

        // Left-Right case
        if (bf > 1 && node->left != nullptr && key > node->left->k)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right-Right case
        if (bf < -1 && node->right != nullptr && key > node->right->k)
            return leftRotate(node);

        // Right-Left case
        if (bf < -1 && node->right != nullptr && key < node->right->k)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    bool contains(Key key)
    {
        return containsHelper(root, key);
    }
    bool containsHelper(Node *node, Key key)
    {
        if (node == nullptr)
            return false;
        if (node->k == key)
            return true;
        else if (key < node->k)
            return containsHelper(node->left, key);
        else
            return containsHelper(node->right, key);
    }

    void remove(Key key)
    {
        bool existed = contains(key);
        root = removeHelper(root, key);
        if (existed)
            cout << " 1" << endl;
        else
            cout << " 0" << endl;
    }
    Node *removeHelper(Node *node, Key key)
    {
        if (node == nullptr)
            return nullptr;
        if (key < node->k)
            node->left = removeHelper(node->left, key);
        else if (key > node->k)
            node->right = removeHelper(node->right, key);
        else
        {
            if (node->left == nullptr)
            {
                Node *aux = node->right;
                delete node;
                return aux;
            }
            if (node->right == nullptr)
            {
                Node *aux = node->left;
                delete node;
                return aux;
            }
            Node *succ = findMin(node->right);
            node->k = succ->k;
            node->val = succ->val;
            node->right = removeHelper(node->right, succ->k);
        }
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);
        if (bf < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        if (bf > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);
        if (bf > 1 && balanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        return node;
    }
    Node *findMin(Node *node)
    {
        if (node->left == nullptr)
            return node;
        return findMin(node->left);
    }
    void preOrder(Node *node)
    {
        if (node == nullptr)
            return;
        cout << node->k << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    void inOrder(Node *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->k << " ";
        inOrder(node->right);
    }
    void postOrder(Node *node)
    {
        if (node == nullptr)
            return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->k << " ";
    }
    void levelOrder(Node *node)
    {
        if (node == nullptr)
            return;
        queue<Node *> q;
        q.push(node);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            cout << temp->k << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N;
    cin >> N;
    cout << N << endl;
    AvlBST<int, int> tree;
    for (int i = 0; i < N; i++)
    {
        int e;
        cin >> e;
        if (e == 0)
        {
            int x;
            cin >> x;
            cout << e << " " << x;
            tree.remove(x);
        }
        else if (e == 1)
        {
            int x;
            cin >> x;
            cout << e << " " << x;
            tree.insert(x);
        }
        else if (e == 2)
        {
            int x;
            cin >> x;

            if (x == 1)
                tree.preOrder(tree.root);
            else if (x == 2)
                tree.inOrder(tree.root);
            else if (x == 3)
                tree.postOrder(tree.root);
            else if (x == 4)
                tree.levelOrder(tree.root);

            cout << endl;
        }
    }
    return 0;
}