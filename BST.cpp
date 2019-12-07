// created by Bartlomiej Binda on 07.12.2019

#include<iostream>

class BST 
{
    struct node 
    {
        int data;
        node* left;
        node* right;
    };

    node* root;

    // remove whole tree
    node* Empty(node* t) 
    {
        if(t == NULL)
            return NULL;
        {
            Empty(t->left);
            Empty(t->right);
            delete t;
        }
        return NULL;
    }

    // insert a node in the right place
    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    // find the furthest element on the left side (MIN)
    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    // find the furthest element on the right side (MAX)
    node* findMax(node* t) 
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) 
    {
        node* temp;
        if(t == NULL)
        {
          std::cout << x << " Value not in the tree!" << std::endl;
            return NULL;
        }
            
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)  // two children
        {
          // find smallest child of right child
          /* # tip # instead of using temp = findMin we could simply write while
          temp = t->right;
          while(temp->left)
          {
            temp = temp->left;
          }*/
          temp = findMin(t->right);
          // swap data
          t -> data = temp->data; 
          // remove the smallest child 
          t->right = remove(t->data, t->right); 
        }
        else // one or no child
        {
          temp = t;
          if(t->left)
          {
            t = t->left;
          }
          else
          {
            t = t->right;
          }
          delete temp;
        }
        return t;
    }

    void inorder(node* t) 
    {
        if(t == NULL)
            return;
        inorder(t->left);
        std::cout << t->data << " ";
        inorder(t->right);
    }

    bool find(node* t, int x) 
    {
        if(t == NULL)
            return false;
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
            return true;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = Empty(root);
    }

    void insert(int x) 
    {
        root = insert(x, root);
    }

    void remove(int x) 
    {
        root = remove(x, root);
    }

    void display() 
    {
        inorder(root);
        std::cout << std::endl;
    }

    void search(int x) 
    {
        find(root, x) ? std::cout << x << " found :)!" : std::cout << x << " not found! ";
    }
};

int main() {
    BST t;
    t.insert(200);
    t.insert(250);
    t.insert(150);
    t.insert(100);
    t.insert(300);
    t.insert(350);
    t.insert(290);
    t.display();
    t.remove(200); // removing root
    t.display();
    t.remove(300);
    t.display();
    t.remove(150);
    t.display();
    t.remove(230);
    t.display();
    return 0; 
}