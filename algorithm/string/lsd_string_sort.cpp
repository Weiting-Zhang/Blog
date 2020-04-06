#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
struct LSD
{
  LSD(vector<string> &a, int len)
  {
    // len: a string length
    // size: vector string size
    int R = 256;
    int size = a.size();
    for (int i = len - 1; i >= 0; i--)
    {
      vector<int> count;
      vector<string> aux;
      count = vector<int>(R + 1, 0);
      aux = vector<string>(size);
      for (string str : a)
      {
        count[str[i] + 1]++;
      }
      for (int j = 1; j < R + 1; j++)
      {
        count[j] = count[j - 1] + count[j];
      }
      for (string str : a)
      {
        aux[count[str[i]]++] = str;
      }
      for (int k = 0; k < size; k++)
      {
        a[k] = aux[k];
      }
    }
  }
};

int main()
{
  vector<string> a;
  ifstream ReadFile;
  FILE *fp;
  fp = freopen("algorithm/string/str.txt", "r", stdin);
  while (cin)
  {
    string s;
    cin >> s;
    a.push_back(s);
  }
  for (string str : a)
  {
    cout << str << endl;
  }
  LSD lsd = LSD(a, 7);
  for (string str : a)
  {
    cout << str << endl;
  }
}
