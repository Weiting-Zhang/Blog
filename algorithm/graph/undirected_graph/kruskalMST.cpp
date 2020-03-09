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

bool Compare(Edge &e1, Edge &e2)
{
  return e1.weight() < e2.weight();
}


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

struct UF
{
  vector<int> ids;
  vector<int> sizes;
  int ct;
  UF(int len)
  {
    ids = vector<int>(len, 0);
    sizes = vector<int>(len, 0);
    ct = len;
    for (int i = 0; i < len; i++)
    {
      ids[i] = i;
      sizes[i] = 1;
    }
  }

  void connect(int p, int q)
  {
    int fp = find(p);
    int fq = find(q);
    if (fp == fq)
    {
      return;
    }
    int sizep = sizes[fp];
    int sizeq = sizes[fq];
    if (sizep < sizeq)
    {
      ids[fp] = ids[fq];
      sizes[fq] = sizep + sizeq;
    }
    else
    {
      ids[fq] = ids[fp];
      sizes[fp] = sizep + sizeq;
    }
    ct--;
  }

  int find(int p)
  {
    if (ids[p] != p)
    {
      return find(ids[p]);
    }
    return p;
  }

  bool isConnected(int p, int q)
  {
    return find(p) == find(q);
  }

  int count()
  {
    return ct;
  }
};

struct KruskalMST
{
  vector<Edge> _edges;
  double _weight;
  KruskalMST(EdgeWeightedGraph G)
  {
    vector <Edge> es = G.edges();
    sort(es.begin(), es.end(), Compare);
    UF uf = UF(G.vSize());
    for (Edge e : es)
    {
      int v = e.either();
      int w = e.other(v);
      if (!uf.isConnected(v, w))
      {
        uf.connect(v, w);
        _edges.push_back(e);
        _weight += e.weight();
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
  KruskalMST MST = KruskalMST(G);
  for(Edge e : MST.edges())
  {
    cout << e.either() << " " << e.other(e.either()) << endl;
  }
  cout << "weighted: " << MST.weight() << endl;
}