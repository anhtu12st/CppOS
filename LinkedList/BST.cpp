#include <bits/stdc++.h>
using namespace std;

template <class K, class V>
class BinaryTree
{
public:
  class Node;

private:
  Node *root;

public:
  BinaryTree() : root(nullptr) {}
  ~BinaryTree()
  {
    // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
  }
  class Node
  {
  private:
    K key;
    V value;
    Node *pLeft, *pRight;
    friend class BinaryTree<K, V>;

  public:
    Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
    ~Node() {}
  };
  void addNode(string posFromRoot, K key, V value)
  {
    if (posFromRoot == "")
    {
      this->root = new Node(key, value);
      return;
    }
    Node *walker = this->root;
    int l = posFromRoot.length();
    for (int i = 0; i < l - 1; i++)
    {
      if (!walker)
        return;
      if (posFromRoot[i] == 'L')
        walker = walker->pLeft;
      if (posFromRoot[i] == 'R')
        walker = walker->pRight;
    }
    if (posFromRoot[l - 1] == 'L')
      walker->pLeft = new Node(key, value);
    if (posFromRoot[l - 1] == 'R')
      walker->pRight = new Node(key, value);
  }
  // STUDENT ANSWER BEGIN

  int height(Node *pNode)
  {
    if (pNode == nullptr)
      return -1;
    return 1 + max(height(pNode->pLeft), height(pNode->pRight));
  }
  int getHeight()
  {
    // TODO: return height of the binary tree.
    return height(this->root);
  }

  string preOrder()
  {
    // TODO: return the sequence of values of nodes in pre-order.
    string s;
    pre(this->root, s);
    if (s.length() != 0)
      s.pop_back();
    return s;
  }

  void pre(Node *root, string &s)
  {
    if (root != NULL)
    {
      ostringstream convert;
      convert << root->value;
      s += convert.str();
      s += " ";
      pre(root->pLeft, s);
      pre(root->pRight, s);
    }
  }
  string inOrder()
  {
    // TODO: return the sequence of values of nodes in in-order.
    string s;
    in(this->root, s);
    if (s.length() != 0)
      s.pop_back();
    return s;
  }
  void in(Node *root, string &s)
  {
    if (root != NULL)
    {
      in(root->pLeft, s);
      ostringstream convert;
      convert << root->value;
      s += convert.str();
      s += " ";
      in(root->pRight, s);
    }
  }
  string postOrder()
  {
    // TODO: return the sequence of values of nodes in post-order.
    string s;
    post(this->root, s);
    if (s.length() != 0)
      s.pop_back();
    return s;
  }
  void post(Node *root, string &s)
  {
    if (root != NULL)
    {
      post(root->pLeft, s);
      post(root->pRight, s);
      ostringstream convert;
      convert << root->value;
      s += convert.str();
      s += " ";
    }
  }
  int countTwoChild(Node *pNode)
  {
    if (pNode == nullptr || pNode->pLeft == nullptr || pNode->pRight == nullptr)
      return 0;
    else
      return 1 + countTwoChild(pNode->pLeft) + countTwoChild(pNode->pRight);
  }
  int countTwoChildrenNode()
  {
    return countTwoChild(this->root);
  }
  int sumLeafs(Node *pNode)
  {
    if (pNode == nullptr)
      return 0;
    if (pNode->pLeft == nullptr && pNode->pRight == nullptr)
      return pNode->value;
    return sumLeafs(pNode->pLeft) + sumLeafs(pNode->pRight);
  }
  int sumOfLeafs()
  {
    //TODO
    return sumLeafs(this->root);
  }
  void BFS()
  {
    queue<Node *> qe;
    Node *p = this->root;

    while (p != nullptr)
    {
      if (p->pLeft != nullptr)
        qe.push(p->pLeft);
      if (p->pRight != nullptr)
        qe.push(p->pRight);
      cout << p->value;
      if (qe.empty())
        p = nullptr;
      else
      {
        cout << ' ';
        p = qe.front();
        qe.pop();
      }
    }
  }
  bool isBinary(Node *pNode)
  {
    if (pNode == nullptr)
      return true;
    if (pNode->pRight != nullptr && pNode->pRight->value < pNode->value)
      return false;
    if (pNode->pLeft != nullptr && pNode->pLeft->value >= pNode->value)
      return false;
    return isBinary(pNode->pRight) && isBinary(pNode->pLeft);
  }
  bool isBST()
  {
    // TODO: return true if a tree is a BST; otherwise, return false.
    return isBinary(this->root);
  }
  // STUDENT ANSWER END
};

template <class T>
class BinarySearchTree
{
public:
  class Node;

private:
  Node *root;

public:
  BinarySearchTree() : root(nullptr) {}
  ~BinarySearchTree()
  {
    // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
  }

  //Helping function

  void ad(Node *&root, T value)
  {
    if (root == NULL)
    {
      root = new Node(value);
    }
    else
    {
      if (value <= root->value)
        ad(root->pLeft, value);
      else
        ad(root->pRight, value);
    }
  }

  void add(T value)
  {
    //TODO
    ad(this->root, value);
  }

  void del(Node *&root, T value)
  {
    if (root == NULL)
    {
      return;
    }
    if (value < root->value)
    {
      del(root->pLeft, value);
    }
    else if (value > root->value)
    {
      del(root->pRight, value);
    }
    else
    {
      if (root->pLeft == NULL)
      {
        Node *delPtr = root;
        root = root->pRight;
        delete delPtr;
      }
      else if (root->pRight == NULL)
      {
        Node *delPtr = root;
        root = root->pLeft;
        delete delPtr;
      }
      else
      {
        Node *dltPtr = root->pLeft;
        while (dltPtr->pRight != NULL)
          dltPtr = dltPtr->pRight;
        root->value = dltPtr->value;
        del(root->pLeft, dltPtr->value);
      }
    }
  }

  void deleteNode(T value)
  {
    //TODO
    del(this->root, value);
  }
  int getHeight(Node *root)
  {
    if (root == NULL)
    {
      return 0;
    }
    else
    {
      int l = getHeight(root->pLeft);
      int r = getHeight(root->pRight);
      if (l > r)
        return 1 + l;
      else
        return 1 + r;
    }
  }
  int getDiameter()
  {
    //TODO
    if (this->root == NULL)
      return 0;
    return 1 + getHeight(this->root->pLeft) + getHeight(this->root->pRight);
  }

  bool findI(Node *root, T value)
  {
    if (root == NULL)
      return false;
    if (root->value == value)
      return true;
    return findI(root->pLeft, value) || findI(root->pRight, value);
  }
  bool find(T i)
  {
    // TODO: return true if value i is in the tree; otherwise, return false.
    return findI(this->root, i);
  }

  T sumI(Node *root, T l, T r)
  {

    if (root == NULL)
      return 0;
    else if (root->value < l || root->value > r)
      return sumI(root->pLeft, l, r) + sumI(root->pRight, l, r);
    else
      return root->value + sumI(root->pLeft, l, r) + sumI(root->pRight, l, r);
  }
  T sum(T l, T r)
  {
    // TODO: return the sum of all element in the tree has value in range [l,r].
    return sumI(this->root, l, r);
  }
  T getMin()
  {
    //TODO: return the minimum values of nodes in the tree.
    Node *ptr = this->root;
    while (ptr->pLeft != NULL)
      ptr = ptr->pLeft;
    return ptr->value;
  }

  T getMax()
  {
    //TODO: return the maximum values of nodes in the tree.
    Node *ptr = this->root;
    while (ptr->pRight != NULL)
      ptr = ptr->pRight;
    return ptr->value;
  }
  string inOrderRec(Node *root)
  {
    stringstream ss;
    if (root != nullptr)
    {
      ss << inOrderRec(root->pLeft);
      ss << root->value << " ";
      ss << inOrderRec(root->pRight);
    }
    return ss.str();
  }

  string inOrder()
  {
    return inOrderRec(this->root);
  }

  class Node
  {
  private:
    T value;
    Node *pLeft, *pRight;
    friend class BinarySearchTree<T>;

  public:
    Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
    ~Node() {}
  };
};

int main()
{
  return 0;
}