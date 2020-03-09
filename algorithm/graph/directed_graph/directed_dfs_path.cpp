#include "vector"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// declaration of Digraph
// copy from digraph.cpp
class Digraph
{
private:
  vector<vector<int> > adjList;
  int _E;
  int _V;

public:
  Digraph(int N);
  void addEdge(int v, int w);
  vector<int> adjacent(int v);
  int E();
  int V();
  Digraph reverse();
};

struct dfsPath
{
  vector<bool> marked;
  vector<int> parents;
  int source;
  dfsPath(Digraph G, int s)
  {
    source = s;
    marked = vector<bool>(G.V());
    parents = vector<int>(G.V());
    dfs(G, s, s);
  }

  bool hasPathTo(int w)
  {
    return marked[w];
  }

  vector<int> pathTo(int w)
  {
    vector<int> path;
    for (int i = w; i != source; i = parents[i])
    {
      path.push_back(i);
    }
    path.push_back(source);
    return path;
  }

  void dfs(Digraph G, int s, int parent)
  {
    marked[s] = true;
    parents[s] = parent;
    for (int i : G.adjacent(s))
    {
      if (!marked[i])
      {
        dfs(G, i, s);
      }
    }
  }
};

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/directed_graph/tinyDG.txt", "r", stdin);
  int N;
  cin >> N;
  Digraph DG = Digraph(N);
  string str;
  while (getline(cin, str))
  {
    int v, w;
    cin >> v;
    cin >> w;
    DG.addEdge(v, w);
  }
  fclose(fp);
  cout << endl;
  for (int i = 0; i < N; i++)
  {
    vector<int> adj = DG.adjacent(i);
    for (int j = 0; j < adj.size(); j++)
    {
      cout << i << "->" << adj[j] << endl;
    }
  }

  int s = 0;
  dfsPath path = dfsPath(DG, 0);
  for (int i = 0; i < DG.V(); i++)
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

// definition of Digraph
// copy from digraph.cpp
Digraph::Digraph(int N)
{
  adjList = vector<vector<int> >(N);
  _V = N;
}

void Digraph::addEdge(int v, int w)
{
  adjList[v].push_back(w);
  _E++;
}

vector<int> Digraph::adjacent(int w)
{
  return adjList[w];
}

int Digraph::E()
{
  return _E;
}

int Digraph::V()
{
  return _V;
}

Digraph Digraph::reverse()
{
  Digraph R = Digraph(_V);
  for (int v = 0; v < _V; v++)
  {
    for (int w : adjacent(v))
    {
      R.addEdge(w, v);
    }
  }
  return R;
}
