#include "vector"
#include <iostream>
#include <fstream>
#include <string>
#include <float.h>
#include <queue>
using namespace std;

struct Edge
{
  int _v, _w;
  double _weight;
  Edge() {
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

struct CompareEdge {
  Edge e;
  double distTo;
  CompareEdge(Edge _e, double _distTo) {
    e = _e;
    distTo = _distTo; 
  }
   bool operator<(CompareEdge e) const
  {
    return this-> distTo > e.distTo;
  }
};

struct SP
{
  vector<Edge> _edgeTo;
  vector<double> _distTo;
  priority_queue<CompareEdge> pq;
  int _s;
  SP(WeightedDigraph G, int s)
  {
    int size = G.V();
    _s = s;
    _edgeTo = vector<Edge>(size);
    _distTo = vector<double>(size, DBL_MAX_EXP);
    _distTo[s] = 0;
    vector<Edge> adj = G.adj(s);
    for (Edge e : adj)
    {
      pq.push(CompareEdge(e, e.weight()));
    }
    while (!pq.empty())
    {
      CompareEdge ce = pq.top();
      Edge e = ce.e;
      pq.pop();
      double d1 = _distTo[e.to()];
      double d2 = _distTo[e.from()] + e.weight();
      if (d2 < d1)
      {
        _distTo[e.to()] = d2;
        _edgeTo[e.to()] = e;
        for (Edge _e : G.adj(e.to()))
        {
          if (_distTo[_e.to()] - DBL_MAX_EXP >= 0)
          {
            pq.push(CompareEdge(_e, _distTo[e.to()] + _e.weight()));
          }
        }
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
  fp = freopen("algorithm/graph/directed_graph/tinyEWG.txt", "r", stdin);
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
  int s = 0;
  SP sp = SP(DG, s);
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
