#include <iostream>
using namespace std;

void select_sort(int a[], int len)
{
  for (int i = 0; i < len; i++)
  {
    int min = a[i], index = i;
    for (int j = i + 1; j < len; j++)
    {
      if (a[j] < min)
      {
        min = a[j];
        index = j;
      }
    }
    a[index] = a[i];
    a[i] = min;
  }
}

int main()
{
  int arr[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
  select_sort(arr, 15);
  for (int i = 0; i < 15; i++)
  {
    cout << arr[i] << endl;
  }
}