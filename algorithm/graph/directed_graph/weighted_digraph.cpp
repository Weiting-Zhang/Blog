#include "vector"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Edge
{
  int _v, _w;
  double _weight;
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
  for (int i = 0; i < N; i++)
  {
    vector<Edge> adj = DG.adj(i);
    for (Edge e : adj)
    {
      cout << e.from() << "->" << e.to() << " " << e.weight() << endl;
    }
  }
}
