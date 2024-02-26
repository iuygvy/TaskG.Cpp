// Bartosz Bugajski

template <typename KEY_TYPE, typename DATA_TYPE>
class Node
{
public:
    DATA_TYPE data;
    KEY_TYPE key;
    Node* left;
    Node* right;

    Node(KEY_TYPE k, DATA_TYPE d)
    {
        data = d;
        key = k;
        left = NULL;
        right = NULL;
    }

    void Display()
    {
        cout << key << data;
    }
};

template <typename KEY_TYPE, typename DATA_TYPE>
class BST
{
private:
    Node<KEY_TYPE, DATA_TYPE>* root;

    void preDisplay(Node<KEY_TYPE, DATA_TYPE>* n)
    {
        if(n != NULL)
        {
            n->Display();
            preDisplay(n->left);
            preDisplay(n->right);
        }
    }

    void inDisplay(Node<KEY_TYPE, DATA_TYPE>* n)
    {
        if(n != NULL)
        {
            inDisplay(n->left);
            n->Display();
            inDisplay(n->right);
        }
    }

    void postDisplay(Node<KEY_TYPE, DATA_TYPE>* n)
    {
        if(n != NULL)
        {
            postDisplay(n->left);
            postDisplay(n->right);
            n->Display();
        }
    }

    void levelDisplay(Node<KEY_TYPE, DATA_TYPE>* n, int level)
    {
        if(n != NULL)
        {
            if(level == 0) n->Display();
            else if(level > 0)
            {
                levelDisplay(n->left, --level);
                levelDisplay(n->right, level);
            }
        }
    }

    int nodeHeight(Node<KEY_TYPE, DATA_TYPE>* n)
    {
        if (n == NULL) return -1;
        else
        {
            int lheight = nodeHeight(n->left);
            int rheight = nodeHeight(n->right);

            if (lheight > rheight)
            {
                return (lheight + 1);
            }
            else
            {
                return (rheight + 1);
            }
        }
    }

public:
    BST()
    {
        root = NULL;
    }

    ~BST()
    {
        while(root != NULL) Delete(root->key);
    }

    bool Insert(KEY_TYPE k, DATA_TYPE d)
    {
        if(root == NULL)
        {
            root = new Node<KEY_TYPE, DATA_TYPE>(k, d);
            return true;
        }
        if(Search(k) == NULL)
        {
            Node<KEY_TYPE, DATA_TYPE>* n = root;
            Node<KEY_TYPE, DATA_TYPE>* prev = NULL;
            while(n != NULL)
            {
                prev = n;
                if(k < n->key) n = n->left;
                else n = n->right;
            }
            if(k < prev->key) prev->left = new Node<KEY_TYPE, DATA_TYPE>(k, d);
            else prev->right = new Node<KEY_TYPE, DATA_TYPE>(k, d);
            return true;
        }
        return false;
    }

    DATA_TYPE* Search(KEY_TYPE k)
    {
        Node<KEY_TYPE, DATA_TYPE>* n = root;
        while(n != NULL && (n->key < k || k < n->key))
        {
            if(k < n->key) n = n->left;
            else n = n->right;
        }
        if(n == NULL) return NULL;
        return &(n->data);
    }

    bool Delete(KEY_TYPE k)
    {
        Node<KEY_TYPE, DATA_TYPE>* n = root;
        Node<KEY_TYPE, DATA_TYPE>* prev = NULL;
        while(n != NULL && (n->key < k || k < n->key))
        {
            prev = n;
            if(k < n->key) n = n->left;
            else n = n->right;
        }
        if(n == NULL) return false;
        if(n->right == NULL && n->left == NULL)
        {
            if(prev == NULL)
            {
                root = NULL;
            }
            else if(prev->left == n)
            {
                prev->left = NULL;
            }
            else
            {
                prev->right = NULL;
            }
            delete n;
        }
        else if(n->right != NULL && n->left == NULL)
        {
            if(prev == NULL)
            {
                root = n->right;
            }
            else if(prev->left == n)
            {
                prev->left = n->right;
            }
            else
            {
                prev->right = n->right;
            }
            delete n;
        }
        else if(n->left != NULL && n->right == NULL)
        {
            if(prev == NULL)
            {
                root = n->left;
            }
            else if(prev->left == n)
            {
                prev->left = n->left;
            }
            else
            {
                prev->right = n->left;
            }
            delete n;
        }
        else
        {
            Node<KEY_TYPE, DATA_TYPE>* help = n->right;
            while(help->left != NULL)
            {
                help = help->left;
            }
            DATA_TYPE tempD = help->data;
            KEY_TYPE tempK = help->key;
            Delete(help->key);
            n->data = tempD;
            n->key = tempK;
        }
        return true;
    }

    void PreOrder()
    {
        preDisplay(root);
    }

    void InOrder()
    {
        inDisplay(root);
    }

    void PostOrder()
    {
        postDisplay(root);
    }

    void LevelOrder()
    {
        int h = Height();
        for(int i = 0; i <= h; i++)
        {
            levelDisplay(root, i);
        }
    }

    int Height()
    {
        return nodeHeight(root);
    }
};