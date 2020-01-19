#include <iostream>
using namespace std;

void insert_sort(int a[], int len)
{
  for (int i = 1; i < len; i++)
  {
    if (a[i] < a[i - 1])
    {
      for (int j = i; j > 0; j--)
      {
        if (a[j] < a[j - 1])
        {
          int temp = a[j];
          a[j] = a[j - 1];
          a[j - 1] = temp;
        }
      }
    }
  }
}

int main()
{
  int arr[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
  insert_sort(arr, 15);
  for (int i = 0; i < 15; i++)
  {
    cout << arr[i] << endl;
  }
}