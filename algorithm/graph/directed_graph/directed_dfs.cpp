#include "vector"
#include <iostream>
#include <fstream>
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

class DirectedDFS
{
private:
  vector<bool> _marked;
  void dfs(Digraph G, int s);

public:
  DirectedDFS(Digraph G, int s);
  bool marked(int v);
};

DirectedDFS::DirectedDFS(Digraph G, int s)
{
  _marked = vector<bool>(G.V());
  dfs(G, s);
}

bool DirectedDFS::marked(int v)
{
  return _marked[v];
}

void DirectedDFS::dfs(Digraph G, int s)
{
    _marked[s] = true;
    for (int w : G.adjacent(s))
    {
      if (!_marked[w])
      {
        dfs(G, w);
      }
    }
  
}

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/directed_graph/tinyDG.txt", "r", stdin);
  int N;
  cin >> N;
  Digraph DG = Digraph(N);
  while (cin)
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

 int source = 0;
 DirectedDFS reachable = DirectedDFS(DG, source);
 cout << endl;
 cout << source << " marked: ";
 for (int i = 0; i < DG.V(); i++)
 {
   if(reachable.marked(i)) {
     cout << i << " ";
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


