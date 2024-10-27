#include <iostream>
#include <iomanip>
#include <math.h>
#include<vector>
 
using namespace std;

/*
    1. Preorder, Inorder, Postorder traversals using numbers
    2. Tree common operations (insert, search, traverse, delete node)
    3. Tree traversals (preorder, inorder, postorder, level order)
    4. Identify mistakes in using recursion where it can be avoided (no need for insertion, no need for node deletion).
    5. Tree Complexity
    6. Applications
    7. What about Heap Data Structure (DSA)?

    Tree Traversal Source:    https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
    Insert Node Source:       https://www.javatpoint.com/insertion-in-binary-search-tree
    Delete Node Source:       https://www.interviewbit.com/blog/delete-node-from-binary-search-tree/
    Binary Tree Applications: https://www.geeksforgeeks.org/applications-advantages-and-disadvantages-of-binary-tree/
*/


struct Node {
    int data;
    Node *left;
    Node *right;
    Node (int val) : data (val), left (nullptr), right (nullptr) {}
};


class BinaryTree {
    private:
        int height;

        // method utilities
        void printTree(const Node *node, int level) const { 
            if (node == nullptr) {
                return; 
            }
            printTree(node->right, level + 1); 
            for (int i = 0; i < level; i++) {
                cout << "    ";
            } 
            cout << node->data << endl; 
            printTree(node->left, level + 1); 
        } 
        void destroyTree(const Node *const root) {
            if (root == nullptr) {
                return;
            }
            destroyTree(root->left);
            destroyTree(root->right);
            cout << root->data << endl;
            delete root;
        }

    public:
        Node *root;
        BinaryTree() : root(nullptr), height (0) {}
        ~BinaryTree() {
            cout << "[call of destructor]" << endl;
            destroyTree(root);
        }

        BinaryTree& insert(const int &value) {
            Node *newNode = new Node (value);
            if (root == nullptr) {
                root = newNode;
                return *this;
            }
            else {
                Node *current = root;
                Node *prev = nullptr;
                while (current != nullptr) {
                    prev = current;
                    if (current->data < value) {
                        current = current->right;
                    }
                    else {
                        current = current->left;
                    }
                }
                if (value < prev->data) {
                    prev->left = newNode;
                }
                else {
                    prev->right = newNode;
                }

                return *this;
            }
        }

        void display() {
            if (root == nullptr) { 
                cout << "Tree is empty" << endl; 
                return; 
            } 
            cout << "Tree height: " << height << endl << endl; 
            printTree(root, 0); 
        }

        void preorder(const Node *node) const {
            if (node == nullptr) {
                return;
            }

            cout << node->data << " -> ";
            preorder(node->left);
            preorder(node->right);
        }
            // Root -> Left -> Right 
        void inorder(const Node *node) const {
            if (node == nullptr) {
                return;
            }

            inorder(node->left);
            cout << node->data << " -> ";
            inorder(node->right);

        }     // Left -> Root -> Right
        void postorder(const Node *node) const {
            if (node == nullptr) {
                return;
            }

            postorder(node->left);
            postorder(node->right);
            cout << node->data << " -> ";
        }  // Left -> Right -> Root

        void levelorder() const {
            if (root == nullptr) { 
                cout << "Tree is empty" << endl; 
                return; 
            }
            cout << "Tree height: " << height << endl << endl;
            printTree(root, 0); 
        }

        bool search(const int &val) const {
            Node *current = root;
            while (current != nullptr && current->data != val) {
                if (val > current->data) {
                    current = current->right;
                }
                else {
                    current = current->left;
                }
            }
            if (current != nullptr) {
                return true;
            }
            else {
                return false;
            }
        }
        void deleteNode(const int &val) {
            Node *current = root;
            Node *prev = nullptr;
            while (current != nullptr && current->data != val) {
                prev = current;
                if (val < current->data) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            if (current == nullptr) {
                cout << "Element not found..." << endl;
            }
            else {
                if (prev->left == current) {
                    prev->left = nullptr;
                }
                else if (prev->right->data == val) {
                    prev->right = nullptr;
                }
                cout << "Leaf Node: " << current->data << endl;
                delete current;
            }
        }
};

/* Your Solution */



int main() {

    BinaryTree tree = BinaryTree();

    cout << endl;
    tree.display();  

    // Ex-1: tree.insert(5).insert(3).insert(8).insert(6).insert(2).insert(4).insert(9).insert(7);
    // Ex-2: https://www.javatpoint.com/insertion-in-binary-search-tree
    tree.insert(50).insert(25).insert(75).insert(12).insert(30).insert(60).insert(85).insert(52).insert(70);
    // Ex-3: tree.insert(2).insert(1).insert(33).insert(0).insert(25).insert(40).insert(11).insert(34).insert(7).insert(12).insert(36).insert(13);

    cout << endl;
    tree.display();  
    cout << endl;

    cout << (tree.search(13) ? "[13 found]" : "[13 not found]") << endl << endl;

    tree.deleteNode(52);
    tree.deleteNode(70);

    cout << endl;
    tree.display();  
    cout << endl;

    // Tree traversals (preorder, inorder, postorder, levelorder)
    cout << "Preorder:   ";
    tree.preorder(tree.root);
    cout << endl;

    cout << "Inorder:    ";
    tree.inorder(tree.root);
    cout << endl;

    cout << "Postorder:  ";
    tree.postorder(tree.root);
    cout << endl;

    cout << "Levelorder: " << endl;
    tree.levelorder();
    cout << endl;
  
  
  	/*
    	------------------------ Output	------------------------
        
        Tree is empty

        Tree height: 3

                            50

                     25             75

               12       30       60       85

                               52   70          

        [13 not found]

        Leaf Node: 52
        Leaf Node: 70

        Tree height: 2

                       50

                 25         75

             12     30     60     85

        Preorder:   50 -> 25 -> 12 -> 30 -> 75 -> 60 -> 85
        Inorder:    12 -> 25 -> 30 -> 50 -> 60 -> 75 -> 85
        Postorder:  12 -> 30 -> 25 -> 60 -> 85 -> 75 -> 50
        Levelorder: 
        Tree height: 2

                       50

                 25         75

             12     30     60     85

        [call of destructor]
         Delete: 12
         Delete: 30
         Delete: 25
         Delete: 60
         Delete: 85
         Delete: 75
         Delete: 50
    */

    return 0;
}