#include <bits/stdc++.h>
using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;

private:
    Node *leftRotate(Node *root)
    {
        Node *tmp = root->pRight;
        root->pRight = tmp->pLeft;
        tmp->pLeft = root;
        return tmp;
    }
    Node *rightRotate(Node *root)
    {
        Node *tempPtr = root->pLeft;
        root->pLeft = tempPtr->pRight;
        tempPtr->pRight = root;
        return tempPtr;
    }
    Node *AVLInsert(Node *root, int data, bool &taller)
    {
        if (root == NULL)
        {
            taller = true;
            return (new Node(data));
        }

        if (data < root->data)
        {
            root->pLeft = AVLInsert(root->pLeft, data, taller);
            // Left subtree is taller
            if (taller)
            {
                if (root->balance == LH)
                    root = leftBalance(root, taller);
                else if (root->balance == EH)
                    root->balance = LH;
                else
                {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        else
        {
            root->pRight = AVLInsert(root->pRight, data, taller);
            // Right subtree is taller
            if (taller)
            {
                if (root->balance == LH)
                {
                    root->balance = EH;
                    taller = false;
                }
                else if (root->balance == EH)
                    root->balance = RH;
                else
                    root = rightBalance(root, taller);
            }
        }

        return root;
    }
    Node *leftBalance(Node *&root, bool &taller)
    {
        Node *leftTree = root->pLeft;
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
            Node *rightTree = leftTree->pRight;
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
            root->pLeft = leftRotate(leftTree);
            root = rightRotate(root);
            taller = false;
        }

        return root;
    }
    Node *rightBalance(Node *root, bool &taller)
    {
        Node *rightTree = root->pRight;
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
            Node *leftTree = rightTree->pLeft;
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
            root->pRight = rightRotate(rightTree);
            root = leftRotate(root);
            taller = false;
        }

        return root;
    }

    Node *AVLDelete(Node *root, int deleteKey, bool &shorter, bool &success)
    {
        if (root == nullptr)
        {
            shorter = false;
            success = false;
            return root;
        }

        if (deleteKey < root->data)
        {
            root->pLeft = AVLDelete(root->pLeft, deleteKey, shorter, success);
            if (shorter)
                root = deleteRightBalance(root, shorter);
        }
        else if (deleteKey > root->data)
        {
            root->pRight = AVLDelete(root->pRight, deleteKey, shorter, success);
            if (shorter)
                root = deleteLeftBalance(root, shorter);
        }
        // Delete node found – test for leaf node
        else
        {
            Node *deleteNode = root;
            if (root->pRight == nullptr)
            {
                Node *newRoot = root->pLeft;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else if (root->pLeft == nullptr)
            {
                Node *newRoot = root->pRight;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else
            {
                Node *exchPtr = root->pLeft;
                while (exchPtr->pRight != nullptr)
                    exchPtr = exchPtr->pRight;
                root->data = exchPtr->data;
                root->pLeft = AVLDelete(root->pLeft, exchPtr->data, shorter, success);
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
            Node *rightTree = root->pRight;
            if (rightTree->balance == LH)
            {
                Node *leftTree = rightTree->pLeft;
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
                root->pRight = rightRotate(rightTree);
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
            Node *leftTree = root->pLeft;
            if (leftTree->balance == RH)
            {
                Node *rightTree = leftTree->pRight;
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
                root->pLeft = leftRotate(leftTree);
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

    void inorder(Node *root)
    {
        if (root == nullptr)
            return;
        if (root->pLeft != nullptr)
            inorder(root->pLeft);
        cout << root->data << ' ';
        if (root->pRight != nullptr)
            inorder(root->pRight);
    }

    // OLD Function
    bool checkAVL(Node *t)
    {
        if (t == NULL)
        {
            return true;
        }
        if (abs(getHeightRec(t->pLeft) - getHeightRec(t->pRight)) > 1)
        {
            return false;
        }
        return checkAVL(t->pLeft) && checkAVL(t->pRight);
    }
    Node *update(Node *t)
    {
        if (t->pLeft != NULL)
            t->pLeft = update(t->pLeft);
        if (t->pRight != NULL)
            t->pRight = update(t->pRight);
        if (abs(getHeightRec(t->pLeft) - getHeightRec(t->pRight)) > 1)
        {
            if (getHeightRec(t->pLeft) > getHeightRec(t->pRight))
            {
                Node *p = t->pLeft;
                if (getHeightRec(p->pLeft) > getHeightRec(p->pRight))
                {
                    t = rightRotate(t);
                }
                else
                {
                    t->pLeft = leftRotate(t->pLeft);
                    t = rightRotate(t);
                }
            }
            else
            {
                Node *p = t->pRight;
                if (getHeightRec(p->pRight) > getHeightRec(p->pLeft))
                {
                    t = leftRotate(t);
                }
                else
                {
                    t->pRight = rightRotate(t->pRight);
                    t = leftRotate(t);
                }
            }
        }
        return t;
    }

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
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
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
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
    void printTreeBalance()
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
                cout << temp->balance;
                q.push(temp->pLeft);
                q.push(temp->pRight);
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

    void insert(const T &value)
    {
        bool taller = false;
        this->root = AVLInsert(this->root, value, taller);
    }
    void remove(const T &value)
    {
        bool shorter = false;
        bool success = false;
        this->root = AVLDelete(this->root, value, shorter, success);
    }
    void printInorder()
    {
        this->inorder(this->root);
    }
    bool search(const T &value)
    {
        Node *ptr = this->root;
        if (ptr == nullptr)
            return false;

        while (ptr != nullptr)
        {
            if (ptr->data == value)
                return true;
            else if (value < ptr->data)
                ptr = ptr->pLeft;
            else
                ptr = ptr->pRight;
        }
        return false;
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main()
{
    AVLTree<int> avl;
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6};
    for (int i = 0; i < 8; i++)
    {
        avl.insert(arr[i]);
    }

    avl.printTreeStructure();
    cout << endl;
    avl.printTreeBalance();
    cout << endl;

    avl.remove(1);

    avl.printTreeStructure();
    cout << endl;
    avl.printTreeBalance();
    cout << endl;

    return 0;
}