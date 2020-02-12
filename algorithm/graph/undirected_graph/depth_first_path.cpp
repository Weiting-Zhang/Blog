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

// depth first find a path
struct DepthFirstPaths
{
  vector<int> edgeTo;
  vector<bool> marked;
  int source;
  int sz;
  DepthFirstPaths(Graph G, int s)
  {
    edgeTo = vector<int>(G.vSize());
    marked = vector<bool>(G.vSize(), false);
    source = s;
    sz = G.vSize();
    dfs(G, s);
  }

  void dfs(Graph G, int w)
  {
    // visit root
    marked[w] = true;
    for (int v : G.adjacent(w))
    {
      if (!marked[v])
      {
        // visit child
        edgeTo[v] = w;
        dfs(G, v);
      }
    }
  }

  bool hasPathTo(int w)
  {
    return marked[w];
  }

  vector<int> pathTo(int v)
  {
    vector<int> path;
    for (int x = v; x != source; x = edgeTo[x])
    {
      path.push_back(x);
    }
    path.push_back(source);
    return path;
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
  int s = 0;
  DepthFirstPaths path = DepthFirstPaths(gh, 0);
  for (int i = 0; i < gh.vSize(); i++)
  {
    if (path.hasPathTo(i))
    {
      cout << "path to " << i << endl;
      for (int x : path.pathTo(i))
      {
        cout << x << " ";
      }
      cout << endl;
    }
  }
}