#include "vector"
#include "stack"
#include <iostream>
#include <fstream>
#include <string>
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

struct DepthFirstOrder
{
  vector<bool> marked;
  vector<int> _pre;
  vector<int> _post;
  stack<int> _reversePost;
  DepthFirstOrder(Digraph G)
  {
    marked = vector<bool>(G.V());
    for (int i = 0; i < G.V(); i++)
    {
      if (!marked[i]) {
        dfs(G, i);
      }
    }
  }

  void dfs(Digraph G, int w)
  {
    marked[w] = true;
    _pre.push_back(w);
    for (int i : G.adjacent(w))
    {
      if (!marked[i])
      {
        dfs(G, i);
      }
    }
    _post.push_back(w);
    _reversePost.push(w);
  }

  vector<int> pre()
  {
    return _pre;
  }

  vector<int> post() {
    return _post;
  }

  stack<int> reversePost() {
    return _reversePost;
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

  int s = 0;
  DepthFirstOrder order = DepthFirstOrder(DG);
  vector<int> pre = order.pre();
  vector<int> post = order.post();
  stack<int> reversePost = order.reversePost();
  cout << "pre: " << endl;
  for (int i : pre)
  {
    cout << i << " ";
  }
  cout << endl << "post: " << endl;
  for (int i : post)
  {
    cout << i << " ";
  }

  cout << endl << "reverse post: " << endl;
  while(!reversePost.empty()){
    cout << reversePost.top() << " ";
    reversePost.pop();
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
