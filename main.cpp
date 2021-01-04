#include <iostream>
using namespace std;

//Node structure
struct Node {
   int data;
   struct Node *lchild;
   struct Node *rchild;
   struct Node *parent;
};

//Class for node functions and root initialization
class bst {
private:
    Node *root;
public:
    bst() {
        root = NULL;
    }
    
    //Function to get the root node
    struct Node *getroot(){
        return root;
    }
    
    //Function to create new node
    //Takes the integer value to be stored as a parameter
    void newnode (int new_data) {
        Node *tmp = new Node;
        tmp->data = new_data;
        tmp->lchild = tmp->rchild =NULL;
        
        if (root == NULL) {
            root = tmp;
        }
        else {
            //Inserts new node and passes root node
            insertnode(root, tmp);
        }
    }
    
    //Function to insert new node
    //Takes two node pointers as parameters
    void insertnode(struct Node *tmp1, struct Node *tmp2) {
        //If tmp1 is greater insert on left side
        if(tmp1->data > tmp2->data) {
            //If tmp1 has no left child insert as tmp1 lchild
            if(tmp1->lchild == NULL) {
                tmp1->lchild = tmp2;
                tmp2->parent = tmp1;
                }
            else {
                //Recursive call if tmp1 has lchild already
                return insertnode(tmp1->lchild, tmp2);
            }
        }
        //If tmp1 is less insert on right side
        if(tmp1->data <= tmp2->data) {
            if(tmp1->rchild == NULL) {
                tmp1->rchild = tmp2;
                tmp2->parent = tmp1;
                }
            else {
                //Recursive call if tmp1 has rchild already
                return insertnode(tmp1->rchild, tmp2);
            }
        }
    }
        
    //Function to traverse bst inorder
    //Takes node pointer as parameter
    void inordertraverse(struct Node *tmp) {
        if(tmp != NULL ) {
            inordertraverse(tmp->lchild);
            cout << tmp->data << " ";
            inordertraverse(tmp->rchild);
        }
    }
    
    //Function to find max
    //Takes node pointer as parameter
    //Returns max node pointer
    struct Node *maxnode(struct Node *tmp) {
        struct Node *tl; 
        struct Node *tr;
        
        if(tmp->lchild == NULL && tmp->rchild == NULL) {
            return tmp;
        }
        
        if(tmp->lchild == NULL) {
            tl = tmp;
        }
        else {
            tl = maxnode(tmp->lchild);
        }
        
        if (tmp->rchild == NULL) {
            tr = tmp;
        }
        else {
            tr = maxnode(tmp->rchild);
        }
        
        if (tl->data > tr->data && tl->data > tmp->data) {
            return tl;
        }
        if (tr->data > tl->data && tr->data > tmp->data) {
            return tr;
        }
        else {
            return tmp;
        }
    }
    
    //Fuction to delete node using predecessor
    //Takes node pointer as a parameter
    void deletenode (struct Node *tmp) {
        //Check if tmp is a leaf or only node
        if(tmp->lchild == NULL && tmp->rchild == NULL) {
            if (tmp->parent->lchild == tmp) {
                    tmp->parent->lchild = NULL;
                }
                else {
                    tmp->parent->rchild = NULL;
                }
                tmp->parent = NULL;
        }
        
        //Check if tmp has a left child
        else if(tmp->lchild != NULL) {
            struct Node *max = maxnode(tmp->lchild);
            tmp->data = max->data;
            
            //If max has a left child
            if(max->lchild != NULL && max->rchild == NULL) {
                max->lchild->parent = max->parent;
                max->parent->rchild = max->lchild;
            }
            
            //If max has no children
            if (max->lchild == NULL && max->rchild == NULL) {
                if (max->parent->lchild == max) {
                    max->parent->lchild = NULL;
                }
                else {
                    max->parent->rchild = NULL;
                }
                max->parent = NULL;
            }
        }
        
        //If tmp only has a right child
        else {
            tmp->rchild->parent = tmp->parent;
            tmp->parent->lchild = tmp->rchild;
            tmp = NULL;
        }
    }
    
    //Function to find node
    //Takes starting node pointer and integer value of interest as parameters
    //Returns the pointer to the node of interest
    struct Node *findnode(struct Node *tmp, int val) {
        if(val > tmp->data) {
            return findnode(tmp->rchild, val);
        }
        if (val < tmp->data) {
            return findnode(tmp->lchild, val);
        }
        else {
            return tmp;
        }
    }

};

int main() {
    
    //Initialize class with root pointer set to null
    bst bst1;
    
    //Create 15 node (50, 40, 80, 20, 45, 60, 100, 70, 65, 42, 44, 30, 25, 35, 33) bst
    bst1.newnode(50);
    bst1.newnode(40);
    bst1.newnode(80);
    bst1.newnode(20);
    bst1.newnode(45);
    bst1.newnode(60);
    bst1.newnode(100);
    bst1.newnode(70);
    bst1.newnode(65);
    bst1.newnode(42);
    bst1.newnode(44);
    bst1.newnode(30);
    bst1.newnode(25);
    bst1.newnode(35);
    bst1.newnode(33);
        
    //Get root node
    struct Node *root = bst1.getroot();

    //Inorder traversal
    cout << "Inorder traversal: " << endl;
    bst1.inordertraverse(root);
    cout << endl;
    cout << endl;

    //Delete root
    cout << "Inorder traversal after deleting root (50): " << endl;
    bst1.deletenode(root);    
    bst1.inordertraverse(root);
    cout << endl;
    cout << endl;
    
    //Find node and delete
    struct Node *delete40 = bst1.findnode(root, 40);
    cout << "Node to be deleted: " << delete40->data << endl;
    bst1.deletenode(delete40);
    cout << "Inorder traversal after deleting node 40: " << endl;
    bst1.inordertraverse(root);
    cout << endl;
    cout << endl;       
    
    //Find node and delete
    struct Node *delete65 = bst1.findnode(root, 65);
    cout << "Node to be deleted: " << delete65->data << endl;
    bst1.deletenode(delete65);
    cout << "Inorder traversal after deleting node 65: " << endl;
    bst1.inordertraverse(root);
    cout << endl;
    cout << endl;  
    
    //Find node and delete
    struct Node *delete35 = bst1.findnode(root, 35);
    cout << "Node to be deleted: " << delete35->data << endl;
    bst1.deletenode(delete35);
    cout << "Inorder traversal after deleting node 35: " << endl;
    bst1.inordertraverse(root);
    cout << endl;
    cout << endl;  

   return 0;
}

