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

struct Cycle

{
  vector<int> marked;
  bool _hasCycle;

  Cycle(Graph G)
  {
    marked = vector<int>(G.vSize());
    for (int i = 0; i < G.vSize(); i++)
    {
      if (!marked[i])
      {
        dfs(G, i, i);
      }
    }
  }

  void dfs(Graph G, int w, int parent)
  {
    marked[w] = true;
    for (int v : G.adjacent(w))
    {
      if (!marked[v])
      {
        dfs(G, v, w);
      }
      else if (v != parent)
      {
        _hasCycle = true;
      }
    }
  }

  bool hasCycle()
  {
    return _hasCycle;
  }
};

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/undirected_graph/tinyGG.txt", "r", stdin);
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
  for (int i = 0; i < N; i++)
  {
    vector<int> adj = gh.adjacent(i);
    for (int j = 0; j < adj.size(); j++)
    {
      cout << i << "-" << adj[j] << endl;
    }
  }
  Cycle cycle = Cycle(gh);
  cout << "hasCycle: " << cycle.hasCycle() << endl;
}