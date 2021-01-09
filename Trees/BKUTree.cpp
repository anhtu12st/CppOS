#include <iostream>
#include <deque>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Delete later
#include <bits/stdc++.h>
void printKey(int key, int value)
{
    cout << key << ' ';
}
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}
void printInteger(int &n)
{
    cout << n << " ";
}

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};
template <class K, class V>
class BKUTree
{
public:
    class AVLTree;
    class SplayTree;

    class Entry
    {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

private:
    AVLTree *avl;
    SplayTree *splay;
    deque<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5)
    {
        this->maxNumOfKeys = maxNumOfKeys;
        avl = new AVLTree;
        splay = new SplayTree;
    }
    ~BKUTree()
    {
        this->clear();
        delete avl;
        delete splay;
    }

    void add(K key, V value)
    {
        // Add key to deque<K> keys
        if (int(keys.size()) < maxNumOfKeys)
        {
            keys.push_back(key);
        }
        else
        {
            keys.pop_front();
            keys.push_back(key);
        }

        // Add newEntry to avl and splay, connect those node
        // Entry *entry = new Entry(key, value);
        // entries.push_back(entry);
        // typename AVLTree::Node *nodeSplay = avl->add(entry);
        typename AVLTree::Node *nodeAVL = avl->add(key, value);
        // typename SplayTree::Node *nodeAVL = splay->add(entry);
        typename SplayTree::Node *nodeSplay = splay->add(key, value);
        nodeSplay->corr = nodeAVL;
        nodeAVL->corr = nodeSplay;
    }
    void remove(K key)
    {
        avl->remove(key);
        typename deque<K>::iterator it = find(keys.begin(), keys.end(), key);
        if (it != keys.end())
        {
            // Remove key in queue and push top key of splay to queue
            while (it != keys.end())
            {
                keys.erase(it);
                it = find(keys.begin(), keys.end(), key);
            }

            keys.push_back(splay->remove(key));
        }
        else
        {
            splay->remove(key);
        }
    }
    V search(K key, vector<K> &traversedList)
    {
        // To do: Implement traversedList && When not found key
        if (int(keys.size()) <= 0)
            throw "Not found";
        V out;
        if (splay->root->entry->key == key)
            out = splay->root->entry->value;
        else
        {
            typename deque<K>::iterator it = find(keys.begin(), keys.end(), key);
            if (it != keys.end())
            {
                typename SplayTree::Node *node = splay->findOneTime(key, traversedList);
                out = node->entry->value;
            }
            else
            {
                typename AVLTree::Node *_r = splay->root->corr;
                typename AVLTree::Node *_f = avl->search(_r, key, traversedList);
                if (_f == NULL)
                    _f = avl->search(avl->root, _r, key, traversedList);
                if (_f == NULL)
                    throw "Not found";
                else
                {
                    typename SplayTree::Node *f = _f->corr;
                    splay->splayOneTime(f);
                    out = f->entry->value;
                }
            }
        }

        if (int(keys.size()) < maxNumOfKeys)
        {
            keys.push_back(key);
        }
        else
        {
            keys.push_back(key);
            keys.pop_front();
        }
        return out;
    }

    void traverseNLROnAVL(void (*func)(K key, V value))
    {
        avl->traverseNLR(func);
    }
    void traverseNLROnSplay(void (*func)(K key, V value))
    {
        splay->traverseNLR(func);
    }

    void clear()
    {
        // avl->clearFake();
        avl->clear();
        // splay->clearFake();
        splay->clear();
        while (!keys.empty())
            keys.pop_front();
        // for (int i = 0; i < int(entries.size()); i++)
        //     delete entries[i];
    }

    class SplayTree
    {
    public:
        class Node
        {
            Entry *entry;
            Node *parent;
            Node *left;
            Node *right;
            typename AVLTree::Node *corr;
            friend class BKUTree::SplayTree;
            friend class BKUTree;
            Node(Entry *entry = NULL)
            {
                this->entry = entry;
                this->parent = NULL;
                this->left = NULL;
                this->right = NULL;
                this->corr = NULL;
            }
            ~Node()
            {
                delete this->entry;
            }
        };

    private:
        void zig(Node *node)
        {
            Node *p = node->parent;
            if (p->left == node)
            {
                Node *T2 = node->right;

                node->parent = NULL;
                node->right = p;

                p->parent = node;
                p->left = T2;

                if (T2 != NULL)
                    T2->parent = p;
            }
            else
            {
                Node *T2 = node->left;

                node->parent = NULL;
                node->left = p;

                p->parent = node;
                p->right = T2;

                if (T2 != NULL)
                    T2->parent = p;
            }
        }
        void zig_zig(Node *n)
        {
            Node *p = n->parent;
            Node *g = p->parent;
            if (p->left == n)
            {
                Node *t2 = n->right;
                Node *t3 = p->right;

                n->parent = g->parent;
                n->right = p;

                p->parent = n;
                p->left = t2;
                p->right = g;

                g->parent = p;
                g->left = t3;

                if (n->parent != NULL)
                {
                    if (n->parent->left == g)
                        n->parent->left = n;
                    else
                        n->parent->right = n;
                }
                if (t2 != NULL)
                    t2->parent = p;
                if (t3 != NULL)
                    t3->parent = g;
            }
            else
            {
                Node *t2 = p->left;
                Node *t3 = n->left;

                n->parent = g->parent;
                n->left = p;

                p->parent = n;
                p->left = g;
                p->right = t3;

                g->parent = p;
                g->right = t2;

                if (n->parent != NULL)
                {
                    if (n->parent->left == g)
                        n->parent->left = n;
                    else
                        n->parent->right = n;
                }
                if (t2 != NULL)
                    t2->parent = g;
                if (t3 != NULL)
                    t3->parent = p;
            }
        }
        void zig_zag(Node *n)
        {
            Node *p = n->parent;
            Node *g = p->parent;
            if (p->right == n)
            {
                Node *t2 = n->left;
                Node *t3 = n->right;

                n->parent = g->parent;
                n->left = p;
                n->right = g;

                p->parent = n;
                p->right = t2;

                g->parent = n;
                g->left = t3;

                if (n->parent != NULL)
                {
                    if (n->parent->left == g)
                        n->parent->left = n;
                    else
                        n->parent->right = n;
                }
                if (t2 != NULL)
                    t2->parent = p;
                if (t3 != NULL)
                    t3->parent = g;
            }
            else
            {
                Node *t2 = n->left;
                Node *t3 = n->right;

                n->parent = g->parent;
                n->left = g;
                n->right = p;

                p->parent = n;
                p->left = t3;

                g->parent = n;
                g->right = t2;

                if (n->parent != NULL)
                {
                    if (n->parent->left == g)
                        n->parent->left = n;
                    else
                        n->parent->right = n;
                }
                if (t2 != NULL)
                    t2->parent = g;
                if (t3 != NULL)
                    t3->parent = p;
            }
        }
        void splay(Node *n)
        {
            while (n->parent != NULL)
            {
                Node *p = n->parent;
                Node *g = p->parent;
                if (g == NULL)
                    zig(n);
                else if (g->left == p && p->left == n)
                    zig_zig(n);
                else if (g->right == p && p->right == n)
                    zig_zig(n);
                else
                    zig_zag(n);
            }
            this->root = n;
        }
        Node *find(const K &data)
        {
            Node *curr = this->root;
            while (curr != NULL)
            {
                if (data < curr->entry->key)
                    curr = curr->left;
                else if (data > curr->entry->key)
                    curr = curr->right;
                else
                    break;
            }
            if (curr != NULL)
            {
                splay(curr);
            }

            return curr;
        }
        Node *subtreeMax(Node *subtree)
        {
            Node *curr = subtree;
            while (curr->right != NULL)
                curr = curr->right;
            return curr;
        }

    public:
        Node *root;

        SplayTree() : root(NULL){};
        ~SplayTree() { this->clear(); };

        void splayOneTime(Node *n)
        {
            if (n->parent != NULL)
            {
                Node *p = n->parent;
                Node *g = p->parent;
                if (g == NULL)
                    zig(n);
                else if (g->left == p && p->left == n)
                    zig_zig(n);
                else if (g->right == p && p->right == n)
                    zig_zig(n);
                else
                    zig_zag(n);
            }
            if (n->parent == NULL)
                this->root = n;
        }
        Node *findOneTime(const K &key, vector<K> &traversedList)
        {
            Node *curr = this->root;
            while (curr != NULL)
            {
                if (key == curr->entry->key)
                    break;
                traversedList.push_back(curr->entry->key);
                if (key < curr->entry->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            if (curr == NULL)
                throw "Not found";
            splayOneTime(curr);
            return curr;
        }

        Node *add(const K &key, const V &value)
        {
            return add(new Entry(key, value));
        }
        Node *add(Entry *entry)
        {
            if (root == NULL)
            {
                root = new Node(entry);
                return root;
            }
            Node *curr = this->root;
            while (curr != NULL)
            {
                if (entry->key < curr->entry->key)
                {
                    if (curr->left == NULL)
                    {
                        Node *newNode = new Node(entry);
                        curr->left = newNode;
                        newNode->parent = curr;
                        splay(newNode);
                        return newNode;
                    }
                    else
                        curr = curr->left;
                }
                else if (entry->key > curr->entry->key)
                {
                    if (curr->right == NULL)
                    {
                        Node *newNode = new Node(entry);
                        curr->right = newNode;
                        newNode->parent = curr;
                        splay(newNode);
                        return newNode;
                    }
                    else
                        curr = curr->right;
                }
                else
                {
                    throw "Duplicate key";
                }
            }
            return curr;
        }
        K remove(const K &key)
        {
            Node *del = find(key);
            if (del == NULL)
                throw "Not found";
            Node *L = del->left;
            Node *R = del->right;
            if (L == NULL)
            {
                this->root = R;
                R->parent = NULL;
            }
            else if (R == NULL)
            {
                this->root = L;
                L->parent = NULL;
            }
            else
            {
                Node *M = subtreeMax(L);
                splay(M);
                M->right = R;
                R->parent = M;
            }

            delete del;
            return this->root->entry->key;
        }
        V search(const K &key)
        {
            Node *curr = this->root;
            while (curr != NULL)
            {
                if (key < curr->entry->key)
                    curr = curr->left;
                else if (key > curr->entry->key)
                    curr = curr->right;
                else
                    break;
            }
            if (curr != NULL)
                splay(curr);
            else
                throw "Not found";

            return curr->entry->value;
        }

        void traverseNLR(void (*func)(K key, V value))
        {
            stack<Node *> st;
            Node *node = this->root;
            st.push(node);
            while (!st.empty())
            {
                node = st.top();
                st.pop();
                func(node->entry->key, node->entry->value);
                if (node->right != NULL)
                    st.push(node->right);
                if (node->left != NULL)
                    st.push(node->left);
            }
        }

        // Delete later
        int getHeightRec(Node *node)
        {
            if (node == NULL)
                return 0;
            int lh = this->getHeightRec(node->left);
            int rh = this->getHeightRec(node->right);
            return (lh > rh ? lh : rh) + 1;
        }
        int getHeight()
        {
            return this->getHeightRec(this->root);
        }
        void printTreeStructure()
        {
            int height = this->getHeight();
            if (this->root == NULL)
            {
                cout << "NULL\n";
                return;
            }
            queue<Node *> q;
            q.push(root);
            Node *temp;
            int count = 0;
            int maxNode = 1;
            int level = 0;
            int space = pow(2, height);
            printNSpace(space / 2);
            while (!q.empty())
            {
                temp = q.front();
                q.pop();
                if (temp == NULL)
                {
                    cout << " ";
                    q.push(NULL);
                    q.push(NULL);
                }
                else
                {
                    cout << temp->entry->key;
                    q.push(temp->left);
                    q.push(temp->right);
                }
                printNSpace(space);
                count++;
                if (count == maxNode)
                {
                    cout << endl;
                    count = 0;
                    maxNode *= 2;
                    level++;
                    space /= 2;
                    printNSpace(space / 2);
                }
                if (level == height)
                    return;
            }
        }

        void clear()
        {
            if (root == NULL)
                return;
            deque<Node *> qe;
            Node *curr = this->root;
            if (curr->left != NULL)
                qe.push_back(curr->left);
            if (curr->right != NULL)
                qe.push_back(curr->right);
            // delete curr->entry;
            delete curr;
            while (!qe.empty())
            {
                curr = qe.front();
                qe.pop_front();
                if (curr->left != NULL)
                    qe.push_back(curr->left);
                if (curr->right != NULL)
                    qe.push_back(curr->right);
                // delete curr->entry;
                delete curr;
            }
            root = NULL;
        }
    };

    class AVLTree
    {
    public:
        class Node
        {
            Entry *entry;
            Node *left;
            Node *right;
            BalanceValue balance;
            typename SplayTree::Node *corr;
            friend class BKUTree::AVLTree;
            friend class BKUTree;
            Node(Entry *entry = NULL)
            {
                this->entry = entry;
                this->left = NULL;
                this->right = NULL;
                this->balance = EH;
                this->corr = NULL;
            }
            ~Node()
            {
                delete this->entry;
            }
        };

    private:
        Node *leftRotate(Node *root)
        {
            Node *tmp = root->right;
            root->right = tmp->left;
            tmp->left = root;
            return tmp;
        }
        Node *rightRotate(Node *root)
        {
            Node *tempPtr = root->left;
            root->left = tempPtr->right;
            tempPtr->right = root;
            return tempPtr;
        }
        Node *AVLInsert(Node *node, Entry *data, bool &taller, Node *&curr)
        {
            if (node == NULL)
            {
                taller = true;
                curr = new Node(data);
                return (curr);
            }

            if (data->key < node->entry->key)
            {
                node->left = AVLInsert(node->left, data, taller, curr);
                // Left subtree is taller
                if (taller)
                {
                    if (node->balance == LH)
                        node = leftBalance(node, taller);
                    else if (node->balance == EH)
                        node->balance = LH;
                    else
                    {
                        node->balance = EH;
                        taller = false;
                    }
                }
            }
            else if (data->key > node->entry->key)
            {
                node->right = AVLInsert(node->right, data, taller, curr);
                // Right subtree is taller
                if (taller)
                {
                    if (node->balance == LH)
                    {
                        node->balance = EH;
                        taller = false;
                    }
                    else if (node->balance == EH)
                        node->balance = RH;
                    else
                        node = rightBalance(node, taller);
                }
            }
            else
                throw "Duplicate key";

            return node;
        }
        Node *leftBalance(Node *root, bool &taller)
        {
            Node *leftTree = root->left;
            // Case: Left of Left
            if (leftTree->balance == LH)
            {
                root->balance = EH;
                root = rightRotate(root);
                leftTree->balance = EH;
                taller = false;
            }
            // Case: Right of Left
            else
            {
                Node *rightTree = leftTree->right;
                if (rightTree->balance == LH)
                {
                    root->balance = RH;
                    leftTree->balance = EH;
                }
                else if (rightTree->balance == EH)
                    root->balance = leftTree->balance = EH;
                else
                {
                    root->balance = EH;
                    leftTree->balance = LH;
                }
                rightTree->balance = EH;
                root->left = leftRotate(leftTree);
                root = rightRotate(root);
                taller = false;
            }

            return root;
        }
        Node *rightBalance(Node *root, bool &taller)
        {
            Node *rightTree = root->right;
            // Case: Right of Right
            if (rightTree->balance == RH)
            {
                root->balance = EH;
                root = leftRotate(root);
                rightTree->balance = EH;
                taller = false;
            }
            // Case: Left of Right
            else
            {
                Node *leftTree = rightTree->left;
                if (leftTree->balance == RH)
                {
                    root->balance = LH;
                    rightTree->balance = EH;
                }
                else if (leftTree->balance == EH)
                    root->balance = rightTree->balance = EH;
                else
                {
                    root->balance = EH;
                    rightTree->balance = RH;
                }
                leftTree->balance = EH;
                root->right = rightRotate(rightTree);
                root = leftRotate(root);
                taller = false;
            }

            return root;
        }

        Node *AVLDelete(Node *root, const int &deleteKey, bool &shorter, bool &success)
        {
            if (root == NULL)
            {
                shorter = false;
                success = false;
                throw "Not found";
                return root;
            }

            if (deleteKey < root->entry->key)
            {
                root->left = AVLDelete(root->left, deleteKey, shorter, success);
                if (shorter)
                    root = deleteRightBalance(root, shorter);
            }
            else if (deleteKey > root->entry->key)
            {
                root->right = AVLDelete(root->right, deleteKey, shorter, success);
                if (shorter)
                    root = deleteLeftBalance(root, shorter);
            }
            // Delete node found – test for leaf node
            else
            {
                Node *deleteNode = root;
                if (root->right == NULL)
                {
                    Node *newRoot = root->left;
                    success = true;
                    shorter = true;
                    delete deleteNode;
                    return newRoot;
                }
                else if (root->left == NULL)
                {
                    Node *newRoot = root->right;
                    success = true;
                    shorter = true;
                    delete deleteNode;
                    return newRoot;
                }
                else
                {
                    Node *exchPtr = root->left;
                    while (exchPtr->right != NULL)
                        exchPtr = exchPtr->right;
                    root->entry->key = exchPtr->entry->key;
                    root->entry->value = exchPtr->entry->value;
                    root->corr = exchPtr->corr;
                    exchPtr->corr->corr = root;
                    root->left = AVLDelete(root->left, exchPtr->entry->key, shorter, success);
                    if (shorter)
                        root = deleteRightBalance(root, shorter);
                }
            }

            return root;
        }
        Node *deleteRightBalance(Node *root, bool &shorter)
        {
            if (root->balance == LH)
                root->balance = EH;
            else if (root->balance == EH)
            {
                root->balance = RH;
                shorter = false;
            }
            else
            {
                Node *rightTree = root->right;
                if (rightTree->balance == LH)
                {
                    Node *leftTree = rightTree->left;
                    if (leftTree->balance == LH)
                    {
                        rightTree->balance = RH;
                        root->balance = EH;
                    }
                    else if (leftTree->balance == EH)
                    {
                        root->balance = LH;
                        rightTree->balance = EH;
                    }
                    else
                    {
                        root->balance = LH;
                        rightTree->balance = EH;
                    }
                    leftTree->balance = EH;
                    root->right = rightRotate(rightTree);
                    root = leftRotate(root);
                }
                else
                {
                    if (rightTree->balance != EH)
                    {
                        root->balance = EH;
                        rightTree->balance = EH;
                    }
                    else
                    {
                        root->balance = RH;
                        rightTree->balance = LH;
                        shorter = false;
                    }
                    root = leftRotate(root);
                }
            }

            return root;
        }
        Node *deleteLeftBalance(Node *root, bool &shorter)
        {
            if (root->balance == RH)
                root->balance = EH;
            else if (root->balance == EH)
            {
                root->balance = LH;
                shorter = false;
            }
            else
            {
                Node *leftTree = root->left;
                if (leftTree->balance == RH)
                {
                    Node *rightTree = leftTree->right;
                    if (rightTree->balance == RH)
                    {
                        leftTree->balance = LH;
                        root->balance = EH;
                    }
                    else if (rightTree->balance == EH)
                    {
                        root->balance = RH;
                        leftTree->balance = EH;
                    }
                    else
                    {
                        root->balance = RH;
                        leftTree->balance = EH;
                    }
                    rightTree->balance = EH;
                    root->left = leftRotate(leftTree);
                    root = rightRotate(root);
                }
                else
                {
                    if (leftTree->balance != EH)
                    {
                        root->balance = EH;
                        leftTree->balance = EH;
                    }
                    else
                    {
                        root->balance = LH;
                        leftTree->balance = RH;
                        shorter = false;
                    }
                    root = rightRotate(root);
                }
            }

            return root;
        }

    public:
        Node *root;

        AVLTree() : root(NULL){};
        ~AVLTree() { this->clear(); };

        Node *add(const K &key, const V &value)
        {
            return add(new Entry(key, value));
        }
        Node *add(Entry *entry)
        {
            bool taller = false;
            Node *curr = NULL;
            this->root = AVLInsert(this->root, entry, taller, curr);
            return curr;
        }
        void remove(const K &key)
        {
            bool shorter = false;
            bool success = false;
            this->root = AVLDelete(this->root, key, shorter, success);
        }
        V search(const K &key)
        {
            Node *curr = this->root;
            while (curr != NULL)
            {
                if (key < curr->entry->key)
                    curr = curr->left;
                else if (key > curr->entry->key)
                    curr = curr->right;
                else
                    break;
            }
            if (curr == NULL)
                throw "Not found";

            return curr->entry->value;
        }
        Node *search(Node *node, const K &key, vector<K> &traversedList)
        {
            Node *curr = node;
            while (curr != NULL)
            {
                if (key == curr->entry->key)
                    break;
                traversedList.push_back(curr->entry->key);
                if (key < curr->entry->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return curr;
        }
        Node *search(Node *root, Node *node, const K &key, vector<K> &traversedList)
        {
            Node *curr = root;
            while (curr != NULL && curr != node)
            {
                if (key == curr->entry->key)
                    break;
                traversedList.push_back(curr->entry->key);
                if (key < curr->entry->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            if (curr == node || curr == NULL)
                return NULL;
            else
                return curr;
        }
        void traverseNLR(void (*func)(K key, V value))
        {
            stack<Node *> st;
            Node *node = this->root;
            st.push(node);
            while (!st.empty())
            {
                node = st.top();
                st.pop();
                func(node->entry->key, node->entry->value);
                if (node->right != NULL)
                    st.push(node->right);
                if (node->left != NULL)
                    st.push(node->left);
            }
        }

        // Delete later
        void checkCorr()
        {
            stack<Node *> st;
            Node *node = this->root;
            st.push(node);
            while (!st.empty())
            {
                node = st.top();
                st.pop();
                cout << node->entry->key << '-' << node->corr->entry->key << '-' << node->corr->corr->entry->key << '\t';
                if (node->right != NULL)
                    st.push(node->right);
                if (node->left != NULL)
                    st.push(node->left);
            }
        }
        int getHeightRec(Node *node)
        {
            if (node == NULL)
                return 0;
            int lh = this->getHeightRec(node->left);
            int rh = this->getHeightRec(node->right);
            return (lh > rh ? lh : rh) + 1;
        }
        int getHeight()
        {
            return this->getHeightRec(this->root);
        }
        void printTreeStructure()
        {
            int height = this->getHeight();
            if (this->root == NULL)
            {
                cout << "NULL\n";
                return;
            }
            queue<Node *> q;
            q.push(root);
            Node *temp;
            int count = 0;
            int maxNode = 1;
            int level = 0;
            int space = pow(2, height);
            printNSpace(space / 2);
            while (!q.empty())
            {
                temp = q.front();
                q.pop();
                if (temp == NULL)
                {
                    cout << " ";
                    q.push(NULL);
                    q.push(NULL);
                }
                else
                {
                    cout << temp->entry->key;
                    q.push(temp->left);
                    q.push(temp->right);
                }
                printNSpace(space);
                count++;
                if (count == maxNode)
                {
                    cout << endl;
                    count = 0;
                    maxNode *= 2;
                    level++;
                    space /= 2;
                    printNSpace(space / 2);
                }
                if (level == height)
                    return;
            }
        }

        void clear()
        {
            if (root == NULL)
                return;
            deque<Node *> qe;
            Node *curr = this->root;
            if (curr->left != NULL)
                qe.push_back(curr->left);
            if (curr->right != NULL)
                qe.push_back(curr->right);
            delete curr;
            while (!qe.empty())
            {
                curr = qe.front();
                qe.pop_front();
                if (curr->left != NULL)
                    qe.push_back(curr->left);
                if (curr->right != NULL)
                    qe.push_back(curr->right);
                delete curr;
            }
            root = NULL;
        }
    };

    // Delete later
public:
    void printDetail()
    {
        cout << endl
             << "List keys: ";
        for (unsigned int i = 0; keys[i]; i++)
            cout << keys[i] << ' ';
        cout << endl;

        cout << "Print NLR of AVL: ";
        avl->traverseNLR(printKey);
        cout << "\nPrint NLR of Splay: ";
        splay->traverseNLR(printKey);

        cout << "\nCheck corr: ";
        avl->checkCorr();

        cout << "\n\nAVL:";
        avl->printTreeStructure();

        cout << "\n\nSPLAY:";
        splay->printTreeStructure();
    }
};

int main()
{
    //     BKUTree<int, int>::AVLTree avl;
    BKUTree<int, int>::SplayTree splay;
    //     BKUTree<int, int> bku;

    //     // TEST CASE AVLTREE

    //     // int arr[] = {20, 4};
    //     // int arr[] = {20, 4, 26, 3, 9};
    //     int arr[] = {20, 4, 26, 3, 9, 21, 30, 2, 7, 11};
    //     for (int i = 0; i < 10; i++)
    //         avl.add(arr[i], arr[i]);

    //     avl.add(15, 15);
    //     avl.add(8, 8);
    //     avl.clear();

    //     // int arr[] = {2, 1, 4, 3, 5};
    //     // int arr[] = {6, 2, 9, 1, 4, 8, 22, 3, 5, 7, 21, 23, 24};
    //     int arr2[] = {5, 2, 8, 1, 3, 7, 21, 4, 6, 9, 22, 23};

    //     for (int i = 0; i < 12; i++)
    //         avl.add(arr2[i], arr2[i]);

    //     avl.remove(1);

    //     avl.traverseNLR(printKey);

    //     // TEST CAST SPLAYTREE

    // int arr1[] = {10, 12, 11, 19, 13, 123, 7, 15, 14};
    // for (int x : arr1)
    // {
    //     cout << "\nADD: " << x << endl;
    //     splay.add(x, x);
    //     splay.printTreeStructure();
    // }

    // int arr2[] = {123, 15, 7, 14, 19, 10};
    // for (int x : arr2)
    // {
    //     cout << "\nREMOVE: " << x << endl;
    //     splay.remove(x);
    //     splay.printTreeStructure();
    // }
    // splay.remove(123);
    // splay.search(15);
    // splay.printTreeStructure();

    //     splay.traverseNLR(printKey);

    //     BKUTree<int, int> *tree = new BKUTree<int, int>();
    //     int keys[] = {1, 3, 5, 7, 9, 2, 4};
    //     for (int i = 0; i < 7; i++)
    //         tree->add(keys[i], keys[i]);
    //     tree->traverseNLROnSplay(printKey);
    //     tree->traverseNLROnAVL(printKey);

    //     delete tree;

    vector<int> traverlist;
    BKUTree<int, int> *tree = new BKUTree<int, int>();
    int arr[30] = {79, 128, 64, 114, 137, 34, 47, 131, 88, 123, 89, 76, 114, 38, 12, 142, 123, 44, 114, 12, 110, 75, 27, 104, 13, 120, 113, 44, 64, 18};
    for (int i = 0; i < 30; i++)
    {
        try
        {
            tree->add(arr[i], arr[i] * 2);
        }
        catch (const char *msg)
        {
            cerr << msg << endl;
        }
    }

    int arr1[15] = {3, 44, 38, 132, 79, 114, 150, 34, 113, 89, 149, 110, 27, 137, 137};
    for (int i = 0; i < 15; i++)
    {
        try
        {
            tree->remove(arr1[i]);
        }
        catch (const char *msg)
        {
            cerr << msg << endl;
        }
    }
    int arr2[10] = {6, 42, 34, 99, 145, 19, 116, 7, 15, 24};
    for (int i = 0; i < 10; i++)
    {
        try
        {
            tree->add(arr2[i], arr[i] * 2);
        }
        catch (const char *msg)
        {
            cerr << msg << endl;
        }
    }

    int arr3[10] = {18, 150, 49, 78, 67, 110, 104, 40, 75, 82};
    for (int i = 0; i < 10; i++)
    {
        // cout << "\n\n\nSearching for: " << arr3[i] << endl;
        // tree->printDetail();
        try
        {
            tree->search(arr3[i], traverlist);
            cout << "traverlist:";
            for (unsigned int i = 0; i < traverlist.size(); i++)
            {
                cout << traverlist[i] << " ";
            }
        }
        catch (const char *msg)
        {
            cout << "traverlist:";
            for (unsigned int i = 0; i < traverlist.size(); i++)
            {
                cout << traverlist[i] << " ";
            }
            cout << endl;
            cerr << msg << endl;
        }
        traverlist.clear();
    }
    delete tree;

    return 0;
}