#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

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

struct TwoColor
{
  vector<bool> colors;
  vector<bool> marked;
  bool isTwoColor;

  TwoColor(Graph G)
  {
    colors = vector<bool>(G.vSize());
    marked = vector<bool>(G.vSize());
    for (int i = 0; i < G.vSize(); i++)
    {
      if (!marked[i])
      {
        dfs(G, i, 1);
      }
    }
  }
  void dfs(Graph G, int w, bool color)
  {
    marked[w] = true;
    colors[w] = color;
    for (int adj : G.adjacent(w))
    {
      if (!marked[adj])
      {
        dfs(G, adj, !color);
      }
      else if (colors[adj] == color)
      {
        isTwoColor = false;
      }
    }
  }
  bool isBipartite()
  {
    return isTwoColor;
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
  for (int i = 0; i < N; i++)
  {
    vector<int> adj = gh.adjacent(i);
    for (int j = 0; j < adj.size(); j++)
    {
      cout << i << "-" << adj[j] << endl;
    }
  }
  TwoColor tc = TwoColor(gh);
  cout << "is two color: " << tc.isBipartite() << endl;
}