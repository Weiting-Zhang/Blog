#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string>
#include <queue>

using namespace std;

struct Edge
{
  int w;
  int v;
  double __weight;
  Edge(){}
  Edge(int _w, int _v, double _weight)
  {
    w = _w;
    v = _v;
    __weight = _weight;
  }

  bool operator < (Edge ee) const
	{
		return this -> __weight > ee.__weight;
	}

  double weight()
  {
    return __weight;
  }

  int either()
  {
    return v;
  }

  int other(int vertex)
  {
    if (vertex == v)
    {
      return w;
    }
    return v;
  }
};

struct EdgeWeightedGraph
{
  vector<vector<Edge> > adjList;
  int size;
  vector<Edge> _edges;
  EdgeWeightedGraph(int N)
  {
    adjList = vector<vector<Edge> >(N);
    size = N;
  }

  void addEdge(Edge edge)
  {
    int v = edge.either();
    int w = edge.other(v);
    adjList[v].push_back(edge);
    adjList[w].push_back(edge);
    _edges.push_back(edge);
  }

  vector<Edge> adjacent(int v)
  {
    return adjList[v];
  }

  int vSize()
  {
    return size;
  }

  vector<Edge> edges()
  {
    return _edges;
  }
};

struct PrimMST
{
  vector<Edge> _edges;
  vector<bool> _marked;
  double _weight;
  priority_queue<Edge> pq;
  PrimMST(EdgeWeightedGraph G)
  {
    vector<Edge> es = G.edges();
    _marked = vector<bool>(G.vSize(), false);
    int v = es[0].either();
    _marked[v] = true;
    visit(G, v);
    while (!pq.empty())
    {
      Edge e = pq.top();
      pq.pop();
      int v = e.either();
      int w = e.other(v);
      if (_marked[v] && _marked[w])
      {
        continue;
      }
      _edges.push_back(e);
      _weight += e.weight();
      if (!_marked[v]) {
        _marked[v] = true;
        visit(G, v);
      }
      if (!_marked[w]) {
        _marked[w] = true;
        visit(G, w);
      }
    }
  }

  vector<Edge> edges()
  {
    return _edges;
  }

  double weight()
  {
    return _weight;
  }

  void visit(EdgeWeightedGraph G, int v)
  {
    for (Edge e : G.adjacent(v))
    {
      int other = e.other(v);
      if (!_marked[other])
      {
        pq.push(e);
      }
    }
  }
};

int main()
{
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/graph/undirected_graph/tinyEWG.txt", "r", stdin);
  int N;
  cin >> N;
  EdgeWeightedGraph G = EdgeWeightedGraph(N);
  string str;
  while (getline(cin, str))
  {
    int v, w;
    double weight;
    cin >> v;
    cin >> w;
    cin >> weight;
    G.addEdge(Edge(v, w, weight));
  }
  fclose(fp);
  cout << endl;
  for (int i = 0; i < N; i++)
  {
    vector<Edge> adj = G.adjacent(i);
    for (int j = 0; j < adj.size(); j++)
    {
      cout << i << "-" << adj[j].other(i) << " : " << adj[j].weight() << endl;
    }
  }

  cout << "MST: " << endl;
  PrimMST MST = PrimMST(G);
  for (Edge e : MST.edges())
  {
    cout << e.either() << " " << e.other(e.either()) << endl;
  }
  cout << "weighted: " << MST.weight() << endl;
}