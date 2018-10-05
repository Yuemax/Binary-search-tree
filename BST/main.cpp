#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;

class BST
{
    struct node
    {
        int data;
        string words;
        node* left;
        node* right;
    };
    
    node* root;
    
    node* makeEmpty(node* t)
    {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }
    
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
    
    node* insertWords(string x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->words = x;
            t->left = t->right = NULL;
        }
        else if(x < t->words)
            t->left = insertWords(x, t->left);
        else if(x > t->words)
            t->right = insertWords(x, t->right);
        return t;
    }
    
    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
    
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
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        
        return t;
    }
    
    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    
    void inorder_word(node* t)
    {
        if(t == NULL)
            return;
        inorder_word(t->left);
        cout << t->words << " ";
        inorder_word(t->right);
    }
    
    node* find(node* t, string x)
    {
        if(t == NULL)
            return NULL;
        else if(x < t->words)
            return find(t->left, x);
        else if(x > t->words)
            return find(t->right, x);
        else
            return t;
    }
    int Height (node* t)
    {

        if(t==NULL) return 0;
        else
        {
            int m = Height(t->left);
            int n = Height(t->right);
            return (m > n) ? (m+1) : (n+1);
        }
    }
    
    int counter(node* t)
    {
        if(t == 0) return 0;
        return counter(t->left) + counter(t->right) + 1;
    }
    
public:
    BST()
    {
        root = NULL;
    }
    
    ~BST()
    {
        root = makeEmpty(root);
    }
    
    void insert(int x)
    {
        root = insert(x, root);
    }
    
    void insertWords(string x)
    {
        root = insertWords(x, root);
    }
    
    void remove(int x)
    {
        root = remove(x, root);
    }
    
    void display_word()
    {
        cout << "In-Order-Walk:  " <<endl;
        inorder_word(root);
        cout << endl;
    }
    
    void display()
    {
        cout << "In-Order-Walk:  " <<endl;
        inorder(root);
        cout << endl;
    }
    
    node* search(string x)
    {
        return  find(root, x);
    }
    
    int getHeight()
    {
        int h = 0;
        h = Height(root);
        cout <<"Height of Tree = " << h << endl;
        return h;
    }
    
    void getWordsNum()
    {
        int num = 0;
        num = counter(root);
        cout << "Number of words = " << num << endl;
    }
    
};

int main()
{
    BST t, wordT;
    int node = 0, aveHeight = 0;
    srand((unsigned)time(NULL));
//    for(int n = 0; n<1000; n++)
//    {
        for(int i = 0; i<1000; i++){
            node = rand() % 100000000;
            t.insert(node);
        }
    t.getHeight();
//    aveHeight = aveHeight + t.getHeight();
//    }
//    cout<< "Average Height = "<<aveHeight/1000<<endl;
        t.display();
//        t.remove(20);
//        t.display();
    
//*****************************************//
    
    
    string filename = "/Users/zhangyue/Downloads/The old man and the sea.txt";
    string out_word;
    ifstream i_file;
    i_file.open(filename);
    if(i_file.is_open())
    {
        while(i_file >> out_word)
        {
            if(wordT.search(out_word) == NULL)
                wordT.insertWords(out_word);
        }
    }
    wordT.getHeight();
    wordT.getWordsNum();
    wordT.display_word();

}
