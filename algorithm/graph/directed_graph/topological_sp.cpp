#include "vector"
#include <iostream>
#include <fstream>
#include <string>
#include <float.h>
using namespace std;

struct Edge
{
  int _v, _w;
  double _weight;
  Edge()
  {
  }
  Edge(int v, int w, double weight)
  {
    _v = v;
    _w = w;
    _weight = weight;
  }

  double weight()
  {
    return _weight;
  }
  int from()
  {
    return _v;
  }
  int to()
  {
    return _w;
  }
};

struct WeightedDigraph
{
  vector<vector<Edge> > _adjList;
  int _E;
  int _V;
  WeightedDigraph(int v)
  {
    _V = v;
    _adjList = vector<vector<Edge> >(v);
  }

  void addEdge(Edge e)
  {
    _adjList[e.from()].push_back(e);
    _E++;
  }

  vector<Edge> adj(int v)
  {
    return _adjList[v];
  }

  int V()
  {
    return _V;
  }

  int E()
  {
    return _E;
  }

  vector<Edge> edges()
  {
    vector<Edge> _edges;
    for (int i = 0; i < _adjList.size(); i++)
    {
      for (Edge e : _adjList[i])
      {
        _edges.push_back(e);
      }
    }
    return _edges;
  }
};

struct Topological
{
  bool _isDAG;
  vector<int> _order;
  vector<int> _stack;
  vector<int> _degrees;
  Topological(WeightedDigraph G)
  {
    int size = G.V();
    _degrees = vector<int>(size, 0);
    for (int i = 0; i < G.V(); i++)
    {
      for (Edge e : G.adj(i))
      {
        _degrees[e.to()]++;
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
      for (Edge e : G.adj(out))
      {
        _degrees[e.to()]--;
        if (_degrees[e.to()] == 0)
        {
          _stack.push_back(e.to());
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

struct AsyclicSP
{
  vector<Edge> _edgeTo;
  vector<double> _distTo;
  int _s;

  AsyclicSP(WeightedDigraph G, int s)
  {
    int size = G.V();
    _s = s;
    _edgeTo = vector<Edge>(size);
    _distTo = vector<double>(size, DBL_MAX_EXP);
    _distTo[s] = 0;
    Topological topo = Topological(G);
    if (topo.isDAG())
    {
      for (int v : topo.order())
      {
        this->relax(G, v);
      }
    }
  }

  void relax(WeightedDigraph G, int v)
  {
    for (Edge e : G.adj(v))
    {
      double d1 = _distTo[e.from()] + e.weight();
      double d2 = _distTo[e.to()];
      if (d1 < d2)
      {
        _distTo[e.to()] = d1;
        _edgeTo[e.to()] = e;
      }
    }
  }

  double distTo(int v)
  {
    return _distTo[v];
  }

  bool hasPathTo(int v)
  {
    return _distTo[v] < DBL_MAX_EXP;
  }

  vector<Edge> pathTo(int v)
  {
    vector<Edge> ans;
    for (Edge e = _edgeTo[v];; e = _edgeTo[e.from()])
    {
      ans.push_back(e);
      if (e.from() == _s)
      {
        break;
      }
    }
    return ans;
  }
};

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/directed_graph/tinyEWDAG.txt", "r", stdin);
  int N;
  cin >> N;
  WeightedDigraph DG = WeightedDigraph(N);
  string str;
  while (getline(cin, str))
  {
    int v, w;
    double weight;
    cin >> v;
    cin >> w;
    cin >> weight;
    DG.addEdge(Edge(v, w, weight));
  }
  fclose(fp);
  cout << endl;
  int s = 5;
  AsyclicSP sp = AsyclicSP(DG, s);
  for (int t = 0; t < DG.V(); t++)
  {
    cout << s << " to " << t << endl;

    if (sp.hasPathTo(t))
    {
      for (Edge e : sp.pathTo(t))
      {
        cout << e.from() << "->" << e.to() << "   " << endl;
      }
      cout << "weighted: " << sp.distTo(t) << endl;
    }
  }
}
