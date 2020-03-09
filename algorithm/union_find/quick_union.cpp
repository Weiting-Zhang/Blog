#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct UF
{
  vector<int> ids;
  int ct;
  UF(int size)
  {
    ids = vector<int>(size, 0);
    ct = size;
    for (int i = 0; i < size; i++)
    {
      ids[i] = i;
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
    ids[fp] = ids[fq];
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

int main()
{
  int N = 10;
  UF uf = UF(N);
  string str;
  while (getline(cin, str))
  {
    int p, q;
    cin >> p;
    cin >> q;
    if (uf.isConnected(p, q))
    {
      continue;
    }
    uf.connect(p, q);
  }
  cout << uf.count() << "components";
}