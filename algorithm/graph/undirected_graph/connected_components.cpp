#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// copy from graph.cpp
struct Graph
{
  vector<vector<int> > adjList;
  int size;
  Graph(int N)
  {
    adjList = vector<vector<int> >(N);
    size = N;
  }

  void addEdge(int v, int w)
  {
    adjList[v].push_back(w);
    adjList[w].push_back(v);
  }

  vector<int> adjacent(int v)
  {
    return adjList[v];
  }

  int vSize()
  {
    return size;
  }
};

// CC: connected compontents
struct CC
{
  vector<int> ids;
  vector<bool> marked;
  int _count = 0;
  CC(Graph G)
  {
    int sz = G.vSize();
    ids = vector<int>(sz);
    marked = vector<bool>(sz);
    for (int i = 0; i < sz; i++)
    {
      if (!marked[i])
      {
        dfs(G, i);
        _count++;
      }
    }
  }

  void dfs(Graph G, int w)
  {
    // visit root
    marked[w] = true;
    ids[w] = _count;
    for (int adj : G.adjacent(w))
    {
      if (!marked[adj])
      {
        // visit child
        dfs(G, adj);
      }
    }
  }

  bool connected(int v, int w)
  {
    return ids[v] == ids[w];
  }

  int count()
  {
    return _count;
  }

  int id(int w)
  {
    return ids[w];
  }
};

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/undirected_graph/tinyG.txt", "r", stdin);
  int N;
  cin >> N;
  Graph gh = Graph(N);
  while (cin)
  {
    int v, w;
    cin >> v;
    cin >> w;
    gh.addEdge(v, w);
  }
  fclose(fp);
  cout << endl;

  CC cc = CC(gh);
  int count = cc.count();
  cout << count << " components" << endl;
  vector<vector<int>> counts;
  counts = vector<vector<int>>(count);
  for (int i = 0; i < gh.vSize(); i++)
  {
    counts[cc.id(i)].push_back(i);
  }
  for (int i = 0; i < counts.size(); i++)
  {
    cout << "id = " << i << ": ";
    for (int v : counts[i])
    {
      cout << v << " ";
    }
    cout << endl;
  }
}