#include "vector"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

struct Topological
{
  bool _isDAG;
  vector<int> _order;
  vector<int> _stack;
  vector<int> _degrees;
  Topological(Digraph G)
  {
    int size = G.V();
    _degrees = vector<int>(size, 0);
    for (int i = 0; i < G.V(); i++)
    {
      for (int v : G.adjacent(i))
      {
        _degrees[v]++;
      }
    }

    for (int i = 0; i < size; i++)
    {
      if (_degrees[i] == 0)
      {
        _stack.push_back(i);
      }
    }

    while (!_stack.empty())
    {
      int out = _stack[_stack.size() - 1];
      _stack.pop_back();
      _order.push_back(out);
      for (int v : G.adjacent(out))
      {
        _degrees[v]--;
        if (_degrees[v] == 0)
        {
          _stack.push_back(v);
        }
      }
    }

    _isDAG = size == _order.size();
  }

  bool isDAG()
  {
    return _isDAG;
  }

  vector<int> order()
  {
    return _order;
  }
};

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/directed_graph/tinyDG2.txt", "r", stdin);
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

  Topological topo = Topological(DG);
  if (topo.isDAG())
  {
    vector<int> order = topo.order();
    cout << "order: " << endl;
    for (int i : order)
    {
      cout << i << endl;
    }
  }
}
