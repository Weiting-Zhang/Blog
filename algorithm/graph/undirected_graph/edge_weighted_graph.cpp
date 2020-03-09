#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string>

using namespace std;

struct Edge
{
  int w;
  int v;
  double __weight;
  Edge(int _w, int _v, double _weight)
  {
    w = _w;
    v = _v;
    __weight = _weight;
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

  vector<Edge> edges() {
    return _edges;
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
    cout << v << " " << w << " " << weight << endl;
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

  for (Edge e : G.edges())
  {
    int v = e.either();
    int w = e.other(v);
    cout << v << " " << w << endl;
  }
}