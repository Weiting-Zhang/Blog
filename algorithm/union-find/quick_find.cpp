#include <iostream>
#include <vector>

using namespace std;

struct UF
{
  vector<int> ids;
  int ct;
  int sz;
  UF(int size)
  {
    ids = vector<int>(size, 0);
    ct = size;
    sz = size;
    for (int i = 0; i < size; i++)
    {
      ids[i] = i;
    }
  }

  void connect(int p, int q)
  {
    // p --> q
    int fq = find(q);
    int fp = find(p);
    if (fp == fq)
    {
      return;
    }
    for (int i = 0; i < sz; i++)
    {
      if (ids[i] == fp)
      {
        ids[i] = fq;
      }
    }
    ct--;
  }

  int find(int p)
  {
    return ids[p];
  }

  bool isConnected(int p, int q)
  {
    return ids[p] == ids[q];
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