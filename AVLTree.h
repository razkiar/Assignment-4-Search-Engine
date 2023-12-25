#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <string>
#include "document.h"

using namespace std;

template <typename Key, typename Value>
class AvlTree
{
private:
    // Struct to represent a node in the AVL tree
    struct AvlNode
    {
        Key k;          // key of the node
        Value v;        // value associated with the key
        AvlNode *left;  // pointer to the left child
        AvlNode *right; // pointer to the right child
        int height;     // height of the node in the AVL tree

        // constructors for creating nodes
        AvlNode(const Key &k, const Value &v, AvlNode *lt, AvlNode *rt, int h = 0)
            : k{k}, v{v}, left{lt}, right{rt}, height{h} {}

        AvlNode(const Key &k, AvlNode *lt, AvlNode *rt, int h = 0)
            : k{k}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root; // pointer to the top of the node

    // Function to insert a new node into the AVL tree
    void insert(const Key &x, const Value &value, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode(x, value, nullptr, nullptr);
            return;
        }

        if (x < t->k)
        {
            insert(x, value, t->left);
        }
        else if (t->k < x)
        {
            insert(x, value, t->right);
        }
        else
        {
            // Update the value for the duplicate key
            t->v = value; // Or merge the existing value with the new value, depending on your requirements
        }

        // Balance the tree after inserting a new node
        balance(t);
    }
    // Public method definitions
public:
    // Constructor
    AvlTree() : root{nullptr} {};

    // Copy constructor
    AvlTree(const AvlTree &rhs);

    // Destructor
    ~AvlTree();

    // Assignment operator
    AvlTree &operator=(const AvlTree &rhs);

    // Inserts a key-value pair into the tree
    void insert(const Key &key, const Value &value)
    {
        insert(key, value, root);
    }

    // Checks if a key is present in the tree
    bool contains(const Key &k) const;

    // Checks if the tree is empty
    bool isEmpty() const;

    // Prints out the tree in preorder traversal
    void printTree() const;

    // Pretty prints out the tree
    void prettyPrintTree() const;

    // Empties the tree
    void makeEmpty();

    // Removes a key from the tree
    void remove(const Key &k);

    // Gets the values associated with the given key
    Value &getValues(Key K);

    // Overloaded subscript operator to get the values associated with the given key
    Value &operator[](const Key &K);

    // Checks the balance of the tree
    void check_balance() const;

    // Gets all the keys in the tree
    vector<Key> getKeys();

    // Helper function for getKeys()
    void getKeys(vector<Key> &keys, AvlNode *node, int level);

    // Get the size of the tree
    int size();

    // Helper function for size()
    int size(AvlNode *node);

    // Writes the contents of the tree to a file
    void writeIndex(string &, AvlTree<string, map<string, int>> &);
    void writeIndex(string &, AvlTree<string, set<string>> &);
    void writeIndex(string &, AvlTree<string, document> &);

    // Private method definitions
private:
    // Root node of the tree
    AvlNode *root;

    // Get the size of the tree
    int size(AvlNode *node) const;

    // Check the balance of the tree
    int check_balance(AvlNode *node) const;

    // Get the values associated with the given key
    Value &getValues(Key K, AvlNode *t);

    // Overloaded subscript operator helper function
    Value &bracketHelper(Key x, AvlNode *&t);

    // Inserts a key-value pair into the tree
    void insert(const Key &x, AvlNode *&t);

    // Removes a key from the tree
    void remove(const Key &x, AvlNode *&t);

    // Removes the minimum node from the tree
    AvlNode *removeMin(AvlNode *&t);

    // Finds the minimum node in the tree
    AvlNode *findMin(AvlNode *t) const;

    // Checks if a key is present in the tree
    bool contains(const Key &x, AvlNode *t) const;

    // Empties the tree
    void makeEmpty(AvlNode *&t);

    // Clones a tree
    AvlNode *clone(AvlNode *t) const;

    // Pretty prints the tree
    void prettyPrintTree(const string &prefix, const AvlNode *node, bool isRight) const;

    // Get the height of the tree
    int height(AvlNode *t) const;

    // Balance the tree
    void balance(AvlNode *&t);

    // Returns the maximum of two integers
    int max(int lhs, int rhs) const;

    // Rotates the tree left
    void rotateLeft(AvlNode *&k2);

    // Rotates the tree right
    void rotateRight(AvlNode *&k1);

    // Double rotates the tree left
    void doubleLeft(AvlNode *&k3);

    // Double rotates the tree right
    void doubleRight(AvlNode *&k1);

    // Helper function for getKeys()
    void getKeys(vector<Key> &keys, AvlNode *node, int level) const;

    // Helper function for writeIndex()
    void writeIndex(ostream &file, AvlTree<string, map<string, int>> &tree, AvlNode *t);
    void writeIndex(ostream &file, AvlTree<string, set<string>> &tree, AvlNode *t);
    void writeIndex(ostream &file, AvlTree<string, document> &tree, AvlNode *t);

    // Copy Constructor
    template <typename Key, typename Value>
    AvlTree<Key, Value>::AvlTree(const AvlTree &rhs) : root(nullptr)
    {
        *this = rhs;
    }

    // Destructor
    template <typename Key, typename Value>
    AvlTree<Key, Value>::~AvlTree()
    {
        makeEmpty();
    }

    // Assignment operator
    template <typename Key, typename Value>
    AvlTree<Key, Value> &AvlTree<Key, Value>::operator=(const AvlTree &rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    // Accessor methods

    // Returns true if the tree contains the given key
    template <typename Key, typename Value>
    bool AvlTree<Key, Value>::contains(const Key &k) const
    {
        return contains(k, root);
    }

    // Returns true if the tree is empty
    template <typename Key, typename Value>
    bool AvlTree<Key, Value>::isEmpty() const
    {
        return root == nullptr;
    }

    // Prints the keys in the tree in ascending order
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::printTree() const
    {
        if (isEmpty())
        {
            std::cout << "Empty tree" << std::endl;
        }
        else
        {
            printTree(root);
        }
    }

    // Prints the keys and structure of the tree in a pretty format
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::prettyPrintTree() const
    {
        if (isEmpty())
        {
            std::cout << "Empty tree" << std::endl;
        }
        else
        {
            prettyPrintTree(root, "", true);
        }
    }

    // Modifier methods (Implementation for methods like insert, remove, makeEmpty, etc.)

    // Makes the tree empty
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::makeEmpty()
    {
        makeEmpty(root);
    }

    // Inserts a key into the tree

    // Removes a key from the tree
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::remove(const Key &k)
    {
        remove(k, root);
    }

    // Writes an index to a file based on the type of the AVL Tree
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::writeIndex(string &filename, AvlTree<string, map<string, int>> &index)
    {
        ofstream file(filename); // Open a file with the given filename
        if (!file.is_open())
        {                                         // Check if the file is open
            cerr << "Error opening file" << endl; // If not, display an error message
            exit(1);                              // Exit the program
        }
        writeIndex(file, index, root); // Write the index to the file
        file.close();                  // Close the file
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::writeIndex(string &filename, AvlTree<string, set<string>> &index)
    {
        ofstream file(filename); // Open a file with the given filename
        if (file.is_open() == false)
        {                                         // Check if the file is open
            cerr << "Error opening file" << endl; // If not, display an error message
            exit(1);                              // Exit the program
        }
        writeIndex(filename, index); // Write the index to the file
        file.close();                // Close the file
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::writeIndex(string &filename, AvlTree<string, document> &index)
    {
        ofstream file(filename); // Open a file with the given filename
        if (file.is_open() == false)
        {                                         // Check if the file is open
            cerr << "Error opening file" << endl; // If not, display an error message
            exit(1);                              // Exit the program
        }
        writeIndex(filename, index); // Write the index to the file
        file.close();                // Close the file
    }

    // rotateLeft() performs a left rotation on the tree, swapping two nodes and updating their heights.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::rotateLeft(AvlNode *&k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    // rotateRight() performs a right rotation on the tree, swapping two nodes and updating their heights.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::rotateRight(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    // doubleLeft() performs a double left rotation on the tree, swapping three nodes and updating their heights.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::doubleLeft(AvlNode *&k3)
    {
        rotateRight(k3->left);
        rotateLeft(k3);
    }

    // doubleRight() performs a double right rotation on the tree, swapping three nodes and updating their heights.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::doubleRight(AvlNode *&k1)
    {
        rotateLeft(k1->right);
        rotateRight(k1);
    }

    // balance() balances the tree by checking the difference in heights of each node's left and right subtrees.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateRight(t); // case 1 (outside)
            else
                doubleRight(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateLeft(t); // case 4 (outside)
            else
                doubleLeft(t); // case 3 (inside)
        }

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    // findMin() finds the minimum value in the tree.
    template <typename Key, typename Value>
    typename AvlTree<Key, Value>::AvlNode *AvlTree<Key, Value>::findMin(AvlTree<Key, Value>::AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    // remove() removes a node from the tree and balances the tree afterwards.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::remove(const Key &x, AvlNode *&t)
    {
        if (t == nullptr)
            throw std::runtime_error("Key not found"); // Throw exception if item not found

        if (x < t->k)
        {
            remove(x, t->left);
        }
        else if (t->k < x)
        {
            remove(x, t->right);
        }
        else
        { // Node found
            if (t->left != nullptr && t->right != nullptr)
            { // Two children
                AvlNode *replacement = removeMin(t->right);
                replacement->left = t->left;
                if (replacement != t->right)
                {
                    replacement->right = t->right;
                }

                delete t;
                t = replacement;
            }
            else
            { // One or no children
                AvlNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;

                delete oldNode;
            }
        }

        if (t != nullptr)
        {
            balance(t); // Rebalance the tree
        }
    }

    // removeMin() removes the minimum value from the tree and returns it.
    template <class Key, class Value>
    typename AvlTree<Key, Value>::AvlNode *AvlTree<Key, Value>::removeMin(AvlTree<Key, Value>::AvlNode *&t)
    {
        if (t == nullptr)
        {
            return nullptr; // No root node
        }

        if (t->left == nullptr)
        {
            AvlNode *findMin = t;
            t = t->right;
            balance(t); // Balance the tree after removal
            return findMin;
        }

        AvlNode *findMin = removeMin(t->left);
        balance(t); // Balance the tree after removal
        return findMin;
    }

    template <typename Key, typename Value>
    bool AvlTree<Key, Value>::contains(const Key &x, AvlNode *t) const
    {
        if (t == nullptr) // Return false if node is null
            return false;
        else if (x < t->k) // If x is less than key of node, search left subtree
            return contains(x, t->left);
        else if (t->k < x) // If x is greater than key of node, search right subtree
            return contains(x, t->right);
        else // Match found
            return true;
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::makeEmpty(AvlNode *&t)
    {
        if (t == nullptr) // Return if node is null
            return;

        makeEmpty(t->left);  // Recursively delete nodes from left subtree
        makeEmpty(t->right); // Recursively delete nodes from right subtree
        delete t;            // Delete node
        t = nullptr;         // Set node to null
    }

    template <typename Key, typename Value>
    typename AvlTree<Key, Value>::AvlNode *AvlTree<Key, Value>::clone(AvlNode *t) const
    {
        if (t == nullptr) // Return null if node is null
            return nullptr;

        return new AvlNode{t->k, t->v, clone(t->left), clone(t->right), t->height}; // Create a new node with same key, value, left subtree, right subtree and height
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::prettyPrintTree(const string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr) // Return if node is null
            return;

        cout << prefix;
        cout << (isRight ? "├──" : "└──");
        // print the key of the node
        cout << node->k << endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true); // Recursively traverse right subtree
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false); // Recursively traverse left subtree
    }

    template <typename Key, typename Value>
    int AvlTree<Key, Value>::height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height; // Return -1 if node is null, else return height of node
    }

    template <typename Key, typename Value>
    int AvlTree<Key, Value>::max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs; // Return maximum of two integers
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::check_balance() const
    {
        if (root != nullptr)
        { // Check balance only if root is not null
            check_balance(root);
        }
    }

    template <typename Key, typename Value>
    int AvlTree<Key, Value>::check_balance(AvlNode *node) const
    {
        if (node == nullptr)
        { // Return -1 if node is null
            return -1;
        }

        int lHeight = check_balance(node->left) + 1;  // Calculate height of left subtree
        int rHeight = check_balance(node->right) + 1; // Calculate height of right subtree

        int balanceFactor = lHeight - rHeight; // Calculate balance factor

        // Check for left-heavy or right-heavy imbalance
        if (abs(balanceFactor) > 1)
        {
            throw std::invalid_argument("Tree is unbalanced at node with key " + std::to_string(node->k) +
                                        ". Balance factor: " + std::to_string(balanceFactor));
        }

        int calculatedNodeHeight = std::max(lHeight, rHeight); // Calculate the height of the node

        // Check if the node's height matches the calculated height
        if (calculatedNodeHeight != node->height)
        {
            throw std::invalid_argument("Node with key " + std::to_string(node->k) +
                                        " has incorrect height. Expected: " + std::to_string(calculatedNodeHeight) +
                                        ", Found: " + std::to_string(node->height));
        }

        return calculatedNodeHeight; // Return calculated height of node
    }

    // getValues() function to retrieve a value associated with the given key from the tree.
    template <typename Key, typename Value>
    Value &AvlTree<Key, Value>::getValues(Key K)
    {
        return getValues(K, root);
    }

    // Overloaded operator [] to retrieve a value associated with the given key from the tree.
    template <typename Key, typename Value>
    Value &AvlTree<Key, Value>::operator[](const Key &K)
    {
        return bracketHelper(K, root);
    }

    // Helper function for getValues() to traverse the tree and find the value associated with the given key.
    template <typename Key, typename Value>
    Value &AvlTree<Key, Value>::getValues(Key x, AvlNode *t)
    {
        if (t == nullptr)
        {
            throw std::runtime_error("Key not found in the tree.");
        }

        if (x < t->k)
            return getValues(x, t->left);
        else if (t->k < x)
            return getValues(x, t->right);
        else
            return t->v; // Match found
    }

    // Helper function for operator[] to traverse the tree and find the value associated with the given key.
    template <typename Key, typename Value>
    Value &AvlTree<Key, Value>::bracketHelper(Key x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, Value{}, nullptr, nullptr, 0};
            return t->v; // New node created
        }
        if (x < t->k)
            return bracketHelper(x, t->left);
        else if (t->k < x)
            return bracketHelper(x, t->right);
        else
            return t->v; // Key found
    }

    // getKeys() function to retrieve all the keys stored in the tree in level order.
    template <typename Key, typename Value>
    vector<Key> AvlTree<Key, Value>::getKeys()
    {
        vector<Key> keys;
        int h = height(root);
        for (int i = 1; i <= h; i++)
        {
            getKeys(keys, root, i);
        }
        return keys;
    }

    // Helper function for getKeys() to traverse the tree and store the keys in the vector.
    template <typename Key, typename Value>
    void AvlTree<Key, Value>::getKeys(vector<Key> &keys, AvlNode *node, int level)
    {
        if (node == nullptr)
        {
            return;
        }
        if (level == 1)
        {
            keys.emplace_back(node->k);
        }
        else if (level > 1)
        {
            getKeys(keys, node->left, level - 1);
            getKeys(keys, node->right, level - 1);
        }
    }

    // size() function to calculate the size of the tree.
    template <typename Key, typename Value>
    int AvlTree<Key, Value>::size()
    {
        return size(root);
    }

    // Helper function for size() to traverse the tree and count the number of nodes.
    template <typename Key, typename Value>
    int AvlTree<Key, Value>::size(AvlNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        else
        {
            return (size(node->left) + 1 + size(node->right));
        }
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::writeIndex(ostream &file, AvlTree<string, map<string, int>> &tree, AvlNode *t)
    {
        // Recursively traverse the tree and write the node values to the output stream
        if (t == nullptr)
        {
            return;
        }
        // print current node
        file << t->k << " ";
        for (auto &p : t->v)
        {
            file << p.first << " ";  // Write the key of the pair
            file << p.second << " "; // Write the value of the pair
        }
        file << "; ";

        writeIndex(file, tree, t->left);  // Traverse left subtree
        writeIndex(file, tree, t->right); // Traverse right subtree
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::writeIndex(ostream &file, AvlTree<string, set<string>> &tree, AvlNode *t)
    {
        // Recursively traverse the tree and write the node values to the output stream
        if (t == nullptr)
        {
            return;
        }
        // print current node
        file << t->k << " ";
        for (auto &p : t->v)
        {
            file << p << " "; // Write the element of the set
        }
        file << "; ";

        writeIndex(file, tree, t->left);  // Traverse left subtree
        writeIndex(file, tree, t->right); // Traverse right subtree
    }

    template <typename Key, typename Value>
    void AvlTree<Key, Value>::writeIndex(ostream &file, AvlTree<string, document> &tree, AvlNode *t)
    {
        // Recursively traverse the tree and write the node values to the output stream
        if (t == nullptr)
        {
            return;
        }
        // print current node
        file << t->k << " ";
        file << t->v.title << endl;          // Write the title of the document
        file << t->v.identifier << ' ';      // Write the identifier of the document
        file << t->v.publicationDate << ' '; // Write the publication date of the document
        file << t->v.authorName << endl;     // Write the author name of the document

        // Replace all whitespace characters in the content with a space
        for (auto &ch : t->v.content)
        {
            if (isspace(ch))
            {
                ch = ' ';
            }
        }

        file << t->v.content << endl; // Write the content of the document

        writeIndex(file, tree, t->left);  // Traverse left subtree
        writeIndex(file, tree, t->right); // Traverse right subtree
    }
}

#endif // AVLTREE_