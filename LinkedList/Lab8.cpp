#include <bits/stdc++.h>
using namespace std;

int color[1001];
class Graph
{
private:
  int V;
  Adjacency *adj;

public:
  Graph(int V)
  {
    this->V = V;
    adj = new Adjacency[V];
  }

  void addEdge(int v, int w)
  {
    adj[v].push(w);
    adj[w].push(v);
  }
  void printGraph()
  {
    for (int v = 0; v < V; ++v)
    {
      cout << "\nAdjacency list of vertex " << v << "\nhead ";
      adj[v].print();
    }
  }
  void BFSvisit(int i, Adjacency *b, list<Adjacency> &c, list<int> &d)
  {
    color[i] = 1;
    c.push_back(adj[i]);
    d.push_back(i);
    while (!c.empty())
    {
      Adjacency temp = c.front();
      for (int k = 0; k < temp.getSize(); k++)
      {
        int u = temp.getElement(k);
        if (color[u] == 0)
        {
          color[u] = 1;
          c.push_back(adj[u]);
          d.push_back(u);
        }
      }
      color[d.front()] = -1;
      b->push(d.front());
      c.pop_front();
      d.pop_front();
    }
  }
  Adjacency *BFS(int v)
  {
    Adjacency *result = new Adjacency(this->V);
    list<Adjacency> queue1;
    list<int> queue2;
    for (int i = 0; i < this->V; i++)
    {
      color[i] = 0;
    }
    /*for(int i=v;i<this->V;i++){
            if(color[i]==0){
                queue1.push_back(adj[i]);
                queue2.push_back(i);
                BFSvisit(i,result,queue1,queue2);

            }
        }
        for(int i=0;i<v;i++){
            if(color[i]==0){
                queue1.push_back(adj[i]);
                queue2.push_back(i);
                BFSvisit(i,result,queue1,queue2);

            }
        }*/
    BFSvisit(v, result, queue1, queue2);
    return result;
    // v is a vertex we start BFS
  }

  void DFSvisit(int i, Adjacency a, Adjacency *rs)
  {
    color[i] = 1;
    rs->push(i);
    int u;
    for (int k = 0; k < a.getSize(); k++)
    {
      u = a.getElement(k);
      if (color[u] == 0)
      {
        DFSvisit(u, adj[u], rs);
      }
    }
  }
  Adjacency *DFS(int v)
  {
    Adjacency *rs = new Adjacency(this->V);
    for (int i = 0; i < this->V; i++)
    {
      color[i] = 0;
    }
    DFSvisit(v, adj[v], rs);
    return rs;
  }
  void topologicalSort()
  {
    int *f = new int(this->V);
    DFS(f);
    int temp[1001];
    int c = 0;
    int count = 0;
    int max = f[0];
    for (int i = 0; i < this->V; i++)
    {
      for (int k = 0; k < this->V; k++)
      {
        if (f[k] > max)
        {
          max = f[k];
          c = k;
        }
      }
      temp[count] = c;
      count++;
      f[c] = -2;
      max = -1;
    }
    for (int i = 0; i < this->V; i++)
    {
      cout << temp[i] << " ";
    }
  }
};

class DirectedGraph
{
  int V;
  list<int> *adj;
  bool isCyclicUtil(int v, bool visited[], bool *rs);

public:
  DirectedGraph()
  {
    V = 0;
    adj = NULL;
  }
  DirectedGraph(int V)
  {
    this->V = V;
    adj = new list<int>[V];
  }
  void addEdge(int v, int w)
  {
    adj[v].push_back(w);
  }
  void DFSVisit(int v, bool &cyclic, int *&color, int *&father, int *&d, int time)
  {
    color[v] = 0;
    d[v] = ++time;
    int n = this->adj[v].size();
    for (int i = 0; i < n; i++)
    {
      int u = adj[v].front();
      adj[v].pop_front();
      adj[v].push_back(u);
      if (color[u] == -1)
      {
        father[u] = v;
        DFSVisit(u, cyclic, color, father, d, time);
      }
      else
      {
        if (father[u] != v && color[u] == 0)
          cyclic = true;
      }
    }
    color[v] = 1;
  }
  bool isCyclic()
  {
    // v is a vertex we start DFS
    int *color = new int[10001];
    int *father = new int[10001];
    int *d = new int[10001];
    for (int i = 0; i < this->V; i++)
    {
      color[i] = -1;
      father[i] = -1;
      d[i] = -1;
    }
    int time = 0;
    bool cyclic = false;
    for (int i = 0; i < this->V; i++)
    {
      if (color[i] == -1)
      {
        DFSVisit(i, cyclic, color, father, d, time);
      }
    }
    return cyclic;
  }
};

int find(int *parent, int i)
{
  if (parent[i] == -1)
  {
    return i;
  }
  return find(parent, parent[i]);
}
void Union(int *parent, int x, int y)
{
  parent[x] = y;
}
int kruskalMST()
{
  // TODO: return weight of the minimum spanning tree.
  vector<pair<int, pair<int, int>>> result;
  int i = 0;
  int e = 0;
  int index = 0;
  int result1 = 0;
  for (unsigned int i = 0; i < edges.size(); i++)
  {
    index = i;
    for (unsigned int j = i + 1; j < edges.size(); j++)
    {
      if (edges[index].first > edges[j].first)
      {
        index = j;
      }
    }
    pair<int, pair<int, int>> temp = edges[index];
    edges[index] = edges[i];
    edges[i] = temp;
  }
  int *parent = new int(this->V);
  for (int i = 0; i < this->V; i++)
  {
    parent[i] = -1;
  }
  while (e < this->V - 1 && i < this->E)
  {
    pair<int, pair<int, int>> temp1 = edges[i];
    i++;
    int x = find(parent, temp1.second.first);
    int y = find(parent, temp1.second.second);
    if (x != y)
    {
      result1 += temp1.first;
      Union(parent, x, y);
      e++;
    }
    //Union(parent,x,y);
  }
  /*for(unsigned int i=0;i<result.size();i++){
            result1+=result[i].first;
        }*/
  return result1;
}

int minDistance(int n, int dist[], bool sptSet[])
{
  int min = INT_MAX, min_index;

  for (int v = 0; v < 6; v++)
    if (sptSet[v] == false && dist[v] <= min)
      min = dist[v], min_index = v;

  return min_index;
}
void printSolution(int dist[])
{
  printf("Vertex \t\t Distance from Source\n");
  for (int i = 0; i < 6; i++)
    printf("%d \t\t %d\n", i, dist[i]);
}
int Dijkstra(int **graph, int src, int dst)
{
  int n = 0;
  while (graph[n] != NULL && graph[n][n] == 0)
  {
    n++;
  }
  int result[1001];
  bool check[1001] = {false};
  for (int i = 0; i < 6; i++)
  {
    result[i] = INT_MAX;
  }
  result[src] = 0;
  for (int i = 0; i < 5; i++)
  {
    int u = minDistance(n, result, check);
    check[u] = true;
    for (int v = 0; v < 6; v++)
      if ((!check[v]) && (graph[u][v]) && (result[u] != INT_MAX) && (result[u] + graph[u][v] < result[v]))
        result[v] = result[u] + graph[u][v];
  }
  return result[dst];
}
int main()
{
  return 0;
}