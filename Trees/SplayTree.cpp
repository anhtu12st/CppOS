#include <bits/stdc++.h>
using namespace std;

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
class SplayTree
{
public:
  class Node;

private:
  Node *root;

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
  Node *subtreeMax(Node *subtree)
  {
    Node *curr = subtree;
    while (curr->right != NULL)
      curr = curr->right;
    return curr;
  }

  void inorder(Node *root)
  {
    if (root == nullptr)
      return;
    if (root->left != nullptr)
      inorder(root->left);
    cout << root->data << ' ';
    if (root->right != nullptr)
      inorder(root->right);
  }

protected:
  int getHeightRec(Node *node)
  {
    if (node == NULL)
      return 0;
    int lh = this->getHeightRec(node->left);
    int rh = this->getHeightRec(node->right);
    return (lh > rh ? lh : rh) + 1;
  }

public:
  SplayTree() : root(nullptr) {}
  ~SplayTree() {}

  void insert(const T &data)
  {
    if (root == NULL)
    {
      root = new Node(data);
      return;
    }
    Node *curr = this->root;
    while (curr != NULL)
    {
      if (data < curr->data)
      {
        if (curr->left == NULL)
        {
          Node *newNode = new Node(data);
          curr->left = newNode;
          newNode->parent = curr;
          splay(newNode);
          return;
        }
        else
          curr = curr->left;
      }
      else if (data > curr->data)
      {
        if (curr->right == NULL)
        {
          Node *newNode = new Node(data);
          curr->right = newNode;
          newNode->parent = curr;
          splay(newNode);
          return;
        }
        else
          curr = curr->right;
      }
      else
      {
        splay(curr);
        return;
      }
    }
  }
  Node *find(const T &data)
  {
    Node *curr = this->root;
    while (curr != NULL)
    {
      if (data < curr->data)
        curr = curr->left;
      else if (data > curr->data)
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
  void remove(const T &data)
  {
    Node *del = find(data);
    if (del == NULL)
      return;
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
  }

  void printInorder()
  {
    this->inorder(this->root);
  }
  bool search(const T &data)
  {
    Node *ptr = this->root;
    if (ptr == nullptr)
      return false;

    while (ptr != nullptr)
    {
      if (ptr->data == data)
        return true;
      else if (data < ptr->data)
        ptr = ptr->left;
      else
        ptr = ptr->right;
    }
    return false;
  }

  string visualNode(Node *n)
  {
    stringstream ss;
    ss << "{\"id\":\"" << n->data << "\"}";
    return ss.str();
  }
  string visualPath(Node *n)
  {
    stringstream ss;

    if (n->left != NULL && n->right != NULL)
    {
      ss << "{ \"from\": \"" << n->data << "\", \"to\": \"" << n->left->data << "\" },"
         << "{ \"from\": \"" << n->data << "\", \"to\": \"" << n->right->data << "\" }";
    }
    else if (n->left != NULL)
    {
      ss << "{ \"from\": \"" << n->data << "\", \"to\": \"" << n->left->data << "\" }";
    }
    else if (n->right != NULL)
    {
      ss << "{ \"from\": \"" << n->data << "\", \"to\": \"" << n->right->data << "\" }";
    }
    else
      return "";
    return ss.str();
  }
  string visualNodes()
  {
    if (this->root == NULL)
      return "";
    stringstream ss;
    list<Node *> qe;
    Node *curr = this->root;

    ss << visualNode(curr);
    if (curr->left != NULL)
      qe.push_back(curr->left);
    if (curr->right != NULL)
      qe.push_back(curr->right);

    while (!qe.empty())
    {
      curr = qe.front();
      qe.pop_front();
      if (visualNode(curr) != "")
      {
        ss << "," << visualNode(curr);
        if (curr->left != NULL)
          qe.push_back(curr->left);
        if (curr->right != NULL)
          qe.push_back(curr->right);
      }
    }
    return ss.str();
  }
  string visualPaths()
  {
    if (this->root == NULL)
      return "";
    stringstream ss;
    list<Node *> qe;
    Node *curr = this->root;

    ss << visualPath(curr);
    if (curr->left != NULL)
      qe.push_back(curr->left);
    if (curr->right != NULL)
      qe.push_back(curr->right);

    while (!qe.empty())
    {
      curr = qe.front();
      qe.pop_front();
      if (visualPath(curr) != "")
      {
        ss << "," << visualPath(curr);
        if (curr->left != NULL)
          qe.push_back(curr->left);
        if (curr->right != NULL)
          qe.push_back(curr->right);
      }
    }
    return ss.str();
  }
  string visualize()
  {
    stringstream ss;
    ss << "{\"kind\":{\"graph\":true},"
          "\"nodes\":["
       << visualNodes()
       << "],\"edges\":["
       << visualPaths()
       << "]}";

    return ss.str();
  }

  void printKey(int key, int value)
  {
    cout << key << endl;
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

  class Node
  {
  private:
    T data;
    Node *left, *right, *parent;

    friend class SplayTree<T>;

  public:
    Node(T data) : data(data), left(NULL), right(NULL), parent(NULL) {}
    ~Node() {}
  };
};

int main()
{
  SplayTree<int> Splay;
  int arr[] = {1, 3, 5, 7, 9, 2, 4};
  for (int i = 0; i < 7; i++)
  {
    Splay.insert(arr[i]);
  }

  Splay.printTreeStructure();
  Splay.remove(4);
  Splay.printTreeStructure();
  return 0;
}