#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Graph
{
  vector<vector<int> > adjList;
  int size;
  Graph(int N)
  {
    adjList = vector<vector<int> >(N);
    size = N;
  }

  void addEdge(int v, int w)
  {
    adjList[v].push_back(w);
    adjList[w].push_back(v);
  }

  vector<int> adjacent(int v)
  {
    return adjList[v];
  }

  int vSize () {
    return size;
  }
};

int main()
{
  ifstream ReadFile;
  FILE* fp;
  fp = freopen("algorithm/graph/undirected_graph/tinyG.txt", "r", stdin);
  int N;
  cin >> N;
  Graph gh = Graph(N);
  string str;
  while (getline(cin, str))
  {
    int v, w;
    cin >> v;
    cin >> w;
    gh.addEdge(v, w);
  }
  fclose(fp);
  cout << endl;
  for (int i = 0; i < N; i++)
  {
    vector<int> adj = gh.adjacent(i);
    for (int j = 0; j < adj.size(); j++)
    {
      cout << i << "-" << adj[j] << endl;
    }
  }
}