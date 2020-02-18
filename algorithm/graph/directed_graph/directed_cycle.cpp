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

class DirectedCycle
{
private:
  vector<bool> _marked;
  vector<int> edgeTo;
  vector<bool> onStack;
  vector<int> _cycle;
  bool _hasCycle;
  void dfs(Digraph G, int s, int parent);

public:
  DirectedCycle(Digraph G);
  bool hasCycle();
  vector<int> cycle();
};

DirectedCycle::DirectedCycle(Digraph G)
{
  _marked = vector<bool>(G.V());
  onStack = vector<bool>(G.V());
  edgeTo = vector<int>(G.V());
  for (int i = 0; i < G.V(); i++)
  {
    if (_hasCycle) {
      break;
    }
    if (!_marked[i])
    {
      dfs(G, i, i);
    }
  }
}

bool DirectedCycle::hasCycle()
{
  return _hasCycle;
}

void DirectedCycle::dfs(Digraph G, int s, int parent)
{
  _marked[s] = true;
  edgeTo[s] = parent;
  onStack[s] = true;
  for (int w : G.adjacent(s))
  {
    if (_hasCycle) {
      return;
    }
    if (!_marked[w])
    {
      dfs(G, w, s);
    }
    else if (onStack[w])
    {
      _hasCycle = true;
      for (int i = s; i != w; i = edgeTo[i]) {
        _cycle.push_back(i);
      }
      _cycle.push_back(w);
      _cycle.push_back(s);
    }
  }
  onStack[s] = false;
}

vector<int> DirectedCycle::cycle()
{
  return _cycle;
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

  DirectedCycle cycle = DirectedCycle(DG);
  cout << "has cycle: " << cycle.hasCycle() << endl;

  cout << "cycle: ";
  vector<int> _cycle = cycle.cycle();
  for (int i : _cycle) {
    cout << i << " ";
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
