#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// copy from graph.cpp
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

struct DepthFirstSearch
{
  vector<bool> marked;
  int ct;
  DepthFirstSearch(Graph G, int s) {
    marked = vector<bool>(G.vSize(), false);
    dfs(G, s);
  }

  void dfs(Graph G, int s) {
    marked[s] = true;
    ct++;
    for(int v : G.adjacent(s)) {
      if (!marked[v]) {
        dfs(G, v);
      }
    }
  }

  bool checkMarked(int v) {
    return marked[v];
  }

  // the count connected to s
  int count() {
    return ct;
  }
};

int main() {
  ifstream ReadFile;
  FILE* fp;
  fp = freopen("algorithm/graph/undirected_graph/tinyG.txt", "r", stdin);
  int N;
  cin >> N;
  Graph gh = Graph(N);
  while (cin)
  {
    int v, w;
    cin >> v;
    cin >> w;
    gh.addEdge(v, w);
  }
  fclose(fp);
  cout << endl;
  int s = 9;
  DepthFirstSearch search = DepthFirstSearch(gh, s);
  for (int i = 0; i < gh.vSize(); i++) {
    if(search.checkMarked(i)) {
      cout << "marked: " << i << endl;
    }
  }
  if (search.count() == gh.vSize()) {
    cout << "connected" << endl;
  } else {
    cout << "not connected" << endl;
  }
}