#include <iostream>
#include <vector>

using namespace std;

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
      int root = find(ids[p]);
      ids[p] = root;
      return root;
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
  while (cin)
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