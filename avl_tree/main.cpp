#include <iostream>

using namespace std;

class Node
{
    public:
    int _data;
    Node* _left;
    Node* _right;
    int _height = 0;

    // int getHeight()
    // {
    //     if()
    // }
};

class Tree
{
    private:
    Node* _root;

    void inOrderPrint(Node* root)
    {
        if(root == nullptr) return;

        inOrderPrint(root->_left);
        cout << root->_data << ": bf: " << balanceFactor(root) << ", h: " << getHeight(root) << " " << endl;
        inOrderPrint(root->_right);
    }

    int getHeight(Node* root)
    {
        if(root == nullptr) return -1;
        return root->_height;
    }

    void updateHeight(Node* root)
    {
        if(root == nullptr) return;
        root->_height = 1 + max(getHeight(root->_left), getHeight(root->_right));
    }

    int balanceFactor(Node* root)
    {
        if(root == nullptr) return -1;
        return getHeight(root->_left) - getHeight(root->_right);
    }

    Node* rightRotate(Node* root)
    {
        Node* newRoot = root->_left;
        Node* temp = newRoot->_right;

        newRoot->_right = root;
        root->_left = temp;

        updateHeight(root);
        updateHeight(newRoot);
        

        return newRoot;
    }

    Node* leftRotate(Node* root)
    {
        Node* newRoot = root->_right;
        Node* temp = newRoot->_left;

        newRoot->_left = root;
        root->_right = temp;

        updateHeight(root);
        updateHeight(newRoot);
        

        return newRoot;
    }
    
    Node* rebalance(Node* root)
    {
        if(root == nullptr) return nullptr;
        updateHeight(root);

        // left heavy
        if(balanceFactor(root) > 1)
        {
            if(balanceFactor(root->_left) < 0)
            {
                cout << "right heavy, do left rotate" << endl;
                root->_left = leftRotate(root->_left);
            }
            cout << "left heavy, do right rotate" << endl;
            //right rotate
            return rightRotate(root);
        }
        // right heavy
        else if(balanceFactor(root) < -1)
        {
            if(balanceFactor(root->_right) > 0)
            {
                cout << "left heavy, do right rotate" << endl;
                root->_right = rightRotate(root->_right);
            }
            cout << "right heavy, do left rotate" << endl;
            return leftRotate(root);
        }
        return root;
    }

    Node* insertNode(int data, Node* root)
    {
        if(root == nullptr)
        {
            Node* newNode = new Node;
            newNode->_data = data;
            return newNode;
        }

        if(data < root->_data)
        {
            root->_left = insertNode(data, root->_left);
        }
        else
        {
            root->_right = insertNode(data, root->_right);
        }

        return rebalance(root);
        
        // if(root->_left == nullptr && root->_right == nullptr) root->_height = 0;
        // else if(root->_left == nullptr) root->_height = 1 + root->_right->_height;
        // else if(root->_right == nullptr) root->_height = 1 + root->_left->_height;
        // else root->_height = 1 + max(root->_left->_height, root->_right->_height);

        // return root;
    }

    public:
    Tree()
    {
        _root = nullptr;
    }

    void inOrder()
    {
        inOrderPrint(_root);
        cout << endl;
    }

    void insert(int data)
    {
        _root = insertNode(data, _root);
    }

    // friend ostream& operator<<(ostream os, const Tree t1)
    // {

    // }
};

int main(int argc, char* argv[])
{
    Tree t1;

    t1.insert(42);
    t1.insert(15);
    t1.insert(23);
    t1.inOrder();
    // t1.inOrder();
    // t1.insert(100);
    // // t1.inOrder();
    // t1.insert(200);
    // // t1.insert(100);

    // t1.inOrder();
    // t1.insert(300);
    // t1.insert(400);
    // t1.insert(500);
    // t1.inOrder();

    // t1.insert(12);
    // t1.insert(11);
    // t1.inOrder();
    // t1.insert(10);
    // t1.inOrder();
    // cout << t1 << endl;
    return 0;
}