#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <algorithm>
#include <cmath>
template <class Type>
struct Node {
    Type item;
    Node<Type> *left = nullptr;
    Node<Type> *right = nullptr;
    Node<Type> *parent = nullptr;
};

template <class Type>
class BinaryTree
{
    public:
        BinaryTree();
        ~BinaryTree();
        void insert(Type item);
        void preOrder();
        void inOrder();
        void postOrder();
        int nodeCount();
        Node<Type>*find(Type item);
        Node<Type>*findRightMostNode(Node<Type> *curr);
        void remove(Type item);
        int  height();
        int leavesCount();


    protected:
        Node<Type> *root;

    private:
        void destroy(Node<Type> * curr);
        void insert(Type item, Node<Type> * curr);
        void preOrder(Node<Type> *curr);
        void postOrder(Node<Type> *curr);
        void inOrder(Node<Type> * curr);
        int nodeCount(Node<Type> * curr);
        int leavesCount(Node<Type> * curr);
        Node<Type>*find(Type item, Node<Type> *curr);
        void remove(Type& item, Node<Type>*curr);
        int height(Node<Type>*curr);
};

/**
 * @brief- this is the default constructor that sets root node to nullptr
 * @tparam Type
 */

template <class Type>
BinaryTree<Type>::BinaryTree(){
    root = nullptr;
}

/**
 * this is the destructor function that simply calls the recursive destroy function
 * @tparam Type
 */

template <class Type>
BinaryTree<Type>::~BinaryTree(){
    destroy(root);
}

/**
 * @brief - this is the destroy function. It recursively goes through every node in the tree and deallocates memory
 * @tparam Type
 * @param curr
 */

template <class Type>
void BinaryTree<Type>::destroy(Node<Type> * curr){
    if(curr) {
        if(curr->left) {
            destroy(curr->left);
        }
        if(curr->right) {
            destroy(curr->right);
        }
        // checks if there is a root first so that the next statements do not crash the program
        if (curr == root) {
            delete curr;
            root = nullptr;
        }
        else if(curr == curr->parent->left) {
            curr->parent->left = nullptr;
            delete curr;
        }
        else if(curr == curr->parent->right) {
            curr->parent->right = nullptr;
            delete curr;
        }
    }
}

/**
 * @brief - this is the starter for the recursive insert method
 * @tparam Type
 * @param item
 */

template <class Type>
void BinaryTree<Type>::insert(Type item){
    // if there is not a root, create one
    if(!root) {
        root = new Node<Type>;
        root->item = item;
        root->left = nullptr;
        root->right = nullptr;
    }
    else {
        insert(item, root);
    }
}

/**
 * @brief - this is the recursive insert method that recursively finds the next available location to add the next
 * leaf or branch into
 * @tparam Type
 * @param item
 * @param curr
 */

template <class Type>
void BinaryTree<Type>::insert(Type item, Node<Type> * curr){
    if(item < curr->item) {
        if(curr->left == nullptr) {
            // if there is nothing in the left branch, create new node with item and place it there
            auto temp = new Node<Type>;
            temp->item = item;
            temp->parent = curr;
            curr->left = temp;
        }
        else {
            insert(item, curr->left);
        }
    }
    if(item > curr->item) {
        if(curr->right == nullptr) {
            // if there is nothing in right branch, create new node with item and place it there
            auto temp = new Node<Type>;
            temp->item = item;
            temp->parent = curr;
            curr->right = temp;
        }
        else {
            insert(item, curr->right);
        }
    }
}

/**
 * @brief - preOrder starter helper function
 * @tparam Type
 */

template <class Type>
void BinaryTree<Type>::preOrder(){
    preOrder(root);
}

/**
 * @brief - preOrder recursive function that recursively prints the node in the order it was added in
 * @tparam Type
 * @param curr
 */

template <class Type>
void BinaryTree<Type>::preOrder(Node<Type> *curr){
    if(curr) {
        // print out current item before going to next one
        std::cout << curr->item << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

/**
 * @brief - inOrder starter helper function
 * @tparam Type
 */

template <class Type>
void BinaryTree<Type>::inOrder(){
    inOrder(root);
}

/**
 * @brief - inOrder recursive function that recursively prints the node in the order that it is in the binary tree
 * @tparam Type
 * @param curr
 */

template <class Type>
void BinaryTree<Type>::inOrder(Node<Type> *curr){
    if(curr) {
        inOrder(curr->left);
        std::cout << curr->item << " ";
        inOrder(curr->right);
    }
}

/**
 * @brief - postOrder starter helper function
 * @tparam Type
 */

template <class Type>
void BinaryTree<Type>::postOrder(){
    postOrder(root);
}

/**
 * @brief - postOrder recursive function that recursively prints the nodes in the binary tree
 * @tparam Type
 * @param curr
 */

template <class Type>
void BinaryTree<Type>::postOrder(Node<Type> *curr){
    if(curr) {
        postOrder(curr->left);
        postOrder(curr->right);
        std::cout << curr->item << " ";
    }
}

/**
 * @brief - helper function that starts off the recursive nodeCount function
 * @tparam Type
 * @return
 */

template <class Type>
int BinaryTree<Type>::nodeCount(){
    return nodeCount(root);
}

/**
 * @brief - recursive function that returns the amount of nodes in the binary tree
 * @tparam Type
 * @param curr
 * @return
 */

template <class Type>
int BinaryTree<Type>::nodeCount(Node<Type> *curr){
    if(curr) {
        return 1 + nodeCount(curr->left) + nodeCount(curr->right);
    }
}

/**
 * @brief - helper function that starts off the recursive leavesCount function
 * @tparam Type
 * @return
 */

template <class Type>
int BinaryTree<Type>::leavesCount(){
    return leavesCount(root);
}

/**
 * @brief - recursive function that returns the amount of leaves in the binary tree
 * @tparam Type
 * @param curr
 * @return
 */

template <class Type>
int BinaryTree<Type>::leavesCount(Node<Type> *curr){
    if(!curr) {
        return 0;
    }
    else if(!curr->left && !curr->right) {
        return 1;
    }
    else {
        return leavesCount(curr->left) + leavesCount(curr->right);
    }
}

/**
 * @brief - helper function that starts off the recursive find function
 * @tparam Type
 * @param item
 * @return
 */

template <class Type>
Node<Type>*BinaryTree<Type>::find(Type item){
    return find(item, root);
}

/**
 * @brief - recursive function that recursively traverses through the binary tree until it finds the sought value and
 *          returns the pointer to the node that contains the value
 * @tparam Type
 * @param item
 * @param curr
 * @return
 */

template <class Type>
Node<Type>*BinaryTree<Type>::find(Type item, Node<Type>*curr){
    if(curr) {
        if(curr->item == item) {
            return curr;
        }
        else if (item < curr->item) {
            return find(item, curr->left);
        }
        else {
            return find(item, curr->right);
        }
    }
    return nullptr;
}

/**
 * @brief - recursive function that traverses to the farthest right node from the starting branch and returns
 *          pointer to the node that is at the far right of the branch
 * @tparam Type
 * @param curr
 * @return
 */

template <class Type>
Node<Type>*BinaryTree<Type>::findRightMostNode(Node<Type> *curr){
    if(!root || !root->right) {
        return nullptr;
    }
    if(curr) {
        if(curr->right == nullptr) {
            return curr;
        }
       return findRightMostNode(curr->right);
    }

}

/**
 * @brief - helper function that starts the recursive remove function
 * @tparam Type
 * @param item
 */

template <class Type>
void BinaryTree<Type>::remove(Type item){
    remove(item, root);
}

/**
 * @brief - recursive function that traverses through the binary tree and removes the value from the tree
 * @tparam Type
 * @param item
 * @param curr
 */

template <class Type>
void BinaryTree<Type>::remove(Type& item, Node<Type>* curr){
    if(curr->item == item) {
        // if current node does not have a right or left child
        if(!curr->left && !curr->right) {
            // if the current node is the parent node's left child
            if(curr == curr->parent->left) {
                curr->parent->left = nullptr;
            }
            // if the current node is the parent node's right child
            else if (curr == curr->parent->right) {
                curr->parent->right = nullptr;
            }
            delete curr;
            curr = nullptr;
            return;
        }
        // if the current node does not have a left child but does have a right
        else if(!curr->left && curr->right) {
            auto parentNode = curr->parent;
            auto rightNode = curr->right;
            // if the current node is the parent node's left child
            if(curr == parentNode->left) {
                parentNode->left = rightNode;
                rightNode->parent = parentNode;
                delete curr;
                curr = nullptr;
                return;
            }
                // if the current node is the parent node's right child
            else if(curr == parentNode->right) {
                parentNode->right = rightNode;
                rightNode->parent = parentNode;
                delete curr;
                curr = nullptr;
                return;
            }
        }
        // if the current node has a left child but no right child
        else if (curr->left && !curr->right) {
            auto parentNode = curr->parent;
            auto leftNode = curr->left;
            // if the current node is the parent node's left child
            if(curr == parentNode->left) {
                parentNode->left = leftNode;
                leftNode->parent = parentNode;
                delete curr;
                curr = nullptr;
                return;
            }
            // if the current node is the parent node's right child
            else if(curr == parentNode->right) {
                parentNode->right = leftNode;
                leftNode->parent = parentNode;
                delete curr;
                curr = nullptr;
                return;
            }
        }
        // if the current node has both a left and a right child
        else if(curr->left && curr->right) {
            auto leftNode = curr->left;
            auto rightMostNode = findRightMostNode(leftNode);
            // set current node value to the farthest right node of left branch value
            curr->item = rightMostNode->item;
            auto rightMostNodeParent = rightMostNode->parent;
            rightMostNodeParent->right = nullptr;
            delete rightMostNode;
            rightMostNode = nullptr;
        }
    }
    else if(item < curr->item) {
        remove(item, curr->left);
    }
    else if(item > curr->item) {
        remove(item, curr->right);
    }
}

/**
 * @brief - helper function that starts the recursive height function
 * @tparam Type
 * @return
 */

template <class Type>
int BinaryTree<Type>::height(){
    int theHeight = height(root);
    return theHeight;
}

/**
 * @brief - recursive height function that returns the height of the binary tree
 * @tparam Type
 * @param curr
 * @return
 */

template <class Type>
int BinaryTree<Type>::height( Node<Type>*curr){
    if(!curr) {
        return -1;
    }
    int leftHeight = height(curr->left);
    int rightHeight = height(curr->right);
    // returns 1 + the max of each two sides per recursive call 
    return 1 + std::max(leftHeight, rightHeight);
}

#endif // BINARY_TREE_H
