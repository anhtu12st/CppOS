#include <bits/stdc++.h>

using namespace std;

template <class T>
class SLinkedList
{
public:
  class Node; // Forward declaration
protected:
  Node *head;
  Node *tail;
  int count;

public:
  SLinkedList() : head(NULL), tail(NULL), count(0){};
  ~SLinkedList(){};
  void add(const T &e);
  void add(int index, const T &e);
  int size();
  bool empty();
  void clear();
  T get(int index);
  void set(int index, const T &e);
  int indexOf(const T &item);
  bool contains(const T &item);
  T removeAt(int index);
  bool removeItem(const T &removeItem);
  string toString()
  {
    stringstream ss;
    ss << "[";
    Node *ptr = head;
    while (ptr != tail)
    {
      ss << ptr->data << ",";
      ptr = ptr->next;
    }

    if (count > 0)
      ss << ptr->data << "]";
    else
      ss << "]";
    return ss.str();
  }

public:
  class Node
  {
  private:
    T data;
    Node *next;
    friend class SLinkedList<T>;

  public:
    Node()
    {
      next = 0;
    }
    Node(Node *next)
    {
      this->next = next;
    }
    Node(T data, Node *next = NULL)
    {
      this->data = data;
      this->next = next;
    }
  };
};

template <class T>
void SLinkedList<T>::add(const T &e)
{
  Node *tmp = new Node(e, NULL);
  if (this->count == 0)
  {
    this->tail = tmp;
    this->head = tmp;
    this->count++;
    return;
  }
  this->tail->next = tmp;
  this->tail = tmp;
  this->count++;
}

template <class T>
void SLinkedList<T>::add(int index, const T &e)
{
  /* Insert an element into the list at given index. */
  Node *p = this->head;
  if (index >= this->count)
  {
    add(e);
    return;
  }
  for (int i = 0; i < index - 1; i++)
  {
    p = p->next;
  }
  if (index == 0)
  {
    Node *tmp = new Node(e, p);
    this->head = tmp;
    this->count++;
    return;
  }
  Node *tmp = new Node(e, p->next);
  p->next = tmp;
  this->count++;
}

template <class T>
int SLinkedList<T>::size()
{
  /* Return the length (size) of list */
  return this->count;
}

template <class T>
T SLinkedList<T>::get(int index)
{
  /* Give the data of the element at given index in the list. */
  if (index < 0 || index >= this->count)
  {
    throw std::out_of_range("Index_is_out_of_range");
  }
  Node *p = this->head;
  while (index--)
  {
    p = p->next;
  }
  return p->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T &e)
{
  /* Assign new value for element at given index in the list */
  if (index < 0 || index >= this->count)
  {
    throw std::out_of_range("Index_is_out_of_range");
  }
  Node *p = this->head;
  while (index--)
  {
    p = p->next;
  }
  p->data = e;
}

template <class T>
bool SLinkedList<T>::empty()
{
  /* Check if the list is empty or not. */
  return !this->count;
}

template <class T>
int SLinkedList<T>::indexOf(const T &item)
{
  /* Return the first index wheter item appears in list, otherwise return -1 */
  Node *p = this->head;
  int n = 0;
  while (p != NULL && p->data != item)
  {
    n++;
    p = p->next;
  }
  if (p != NULL)
  {
    return n;
  }
  else
  {
    return -1;
  }
}

template <class T>
bool SLinkedList<T>::contains(const T &item)
{
  /* Check if item appears in the list */
  Node *p = this->head;
  while (p != NULL && p->data != item)
  {
    p = p->next;
  }
  if (p)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
  if (index < 0 || index >= this->count)
  {
    throw std::out_of_range("Index_is_out_of_range");
  }
  Node *p = this->head;
  if (this->count == 1)
  {
    this->head = NULL;
    this->tail = NULL;
    this->count--;
    T x = p->data;
    delete p;
    return x;
  }
  if (index == 0)
  {
    this->head = p->next;
    T x = p->data;
    delete p;
    this->count--;
    return x;
  }
  for (int i = 1; i < index; i++)
  {
    p = p->next;
  }
  if (index == this->count - 1)
  {
    this->tail = p;
    Node *tmp = p->next;
    p->next = NULL;
    T x = tmp->data;
    delete tmp;
    this->count--;
    return x;
  }
  Node *tmp = p->next;
  T x = tmp->data;
  p->next = tmp->next;
  delete tmp;
  this->count--;
  return x;
}

template <class T>
bool SLinkedList<T>::removeItem(const T &item)
{
  /* Remove the first appearance of item in list and return true, otherwise return false */
  int x = 0;
  Node *p = this->head;
  while (p != NULL && p->data != item)
  {
    p = p->next;
    x++;
  }
  if (p == NULL)
  {
    return false;
  }
  else
  {
    removeAt(x);
    return true;
  }
}

template <class T>
void SLinkedList<T>::clear()
{
  /* Remove all elements in list */
  Node *p = this->head;
  Node *px = this->head;
  while (this->count--)
  {
    px = p;
    p = p->next;
    delete px;
  }
  this->head = NULL;
  this->tail = NULL;
  this->count = 0;
}

int main()
{

  return 0;
}

bool isValidParentheses(string s)
{
  /*TODO*/
  stack<char> st;
  st.push('T');
  for (unsigned int i = 0; i < s.length(); i++)
  {
    if (s[i] == '(' || s[i] == '{' || s[i] == '[')
      st.push(s[i]);

    else if (
        (st.top() == '(' && s[i] == ')') ||
        (st.top() == '{' && s[i] == '}') ||
        (st.top() == '[' && s[i] == ']'))
      st.pop();
    else
      st.push(s[i]);
  }
  if (st.size() == 1)
    return true;
  return false;
}

int baseballScore(string ops)
{
  /*TODO*/
  vector<char> vt;
  for (unsigned int i = 0; i < ops.length(); i++)
  {
    switch (ops[i])
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      vt.push_back(int(ops[i]) - 48);
      break;
    case '+':
      vt.push_back(vt[vt.size() - 1] + vt[vt.size() - 2]);
      break;
    case 'D':
      vt.push_back(vt[vt.size() - 1] * 2);
      break;
    case 'C':
      vt.pop_back();
      break;

    default:
      break;
    }
  }
  int sum = 0;
  while (!vt.empty())
  {
    sum += vt.back();
    vt.pop_back();
  }
  return sum;
}

string removeDuplicates(string S)
{
  /*TODO*/
  stack<char> st;
  st.push(S[0]);
  for (unsigned int i = 1; i < S.length(); i++)
  {
    if ((!st.empty()) && st.top() == S[i])
    {
      st.pop();
    }
    else
    {
      st.push(S[i]);
    }
  }
  string out = "";
  while (!st.empty())
  {
    out.push_back(st.top());
    st.pop();
  }
  string rs = "";
  for (int i = out.length() - 1; i >= 0; i--)
  {
    rs.push_back(out[i]);
  }
  return rs;
}

void bfs(vector<vector<int>> graph, int start)
{
  queue<int> qe;
  bool pass[10001] = {false};
  qe.push(start);
  pass[start] = true;
  cout << start;
  while (!qe.empty())
  {
    int vertex = qe.front();

    while (!graph[vertex].empty())
    {
      int front = graph[vertex].front();
      if (pass[front])
      {
        graph[vertex].erase(graph[vertex].begin());
        continue;
      }
      cout << ' ' << front;
      qe.push(front);
      pass[front] = true;
      graph[vertex].erase(graph[vertex].begin());
    }

    qe.pop();
  }
}

bool isBipartite(vector<vector<int>> graph)
{
  if (graph.empty())
    return false;
  int size = int(graph.size());
  for (int n = 0; n < size; n++)
  {
    int color[10001] = {0};
    color[n] = 1;
    queue<int> q;
    q.push(n);
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      for (int i = 0; i < int(graph[u].size()); i++)
      {
        int v = graph[u][i];
        if (v == u)
          return false;
        if (color[v] == 0)
        {
          color[v] = color[u] == 1 ? 2 : 1;
          q.push(v);
        }
        else if (color[v] == color[u])
          return false;
      }
    }
  }
  return true;
}

vector<int> topologicalSorting(vector<vector<int>> graph)
{
  int size = graph.size();
  vector<int> v;
  vector<int> id(size, 0);
  for (int i = 0; i < size; i++)
    for (int j = 0; j < int(graph[i].size()); j++)
    {
      id[graph[i][j]]++;
    }
  queue<int> qe;
  for (int i = 0; i < size; i++)
  {
    if (id[i] == 0)
      qe.push(i);
  }
  int count = 0;
  while (!qe.empty())
  {
    int u = qe.front();
    qe.pop();
    v.push_back(u);
    for (int i = 0; i < int(graph[u].size()); i++)
    {
      if (--id[graph[u][i]] == 0)
      {
        qe.push(graph[u][i]);
      }
    }
    count++;
  }
  if (count != size)
    v.clear();
  return v;
}