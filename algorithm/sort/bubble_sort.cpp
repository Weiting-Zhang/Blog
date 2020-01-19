#include <iostream>
using namespace std;

void bubble_sort(int a[], int len)
{
  for (int i = 0; i < len; i++)
  {
    for (int j = 0; j < len - i - 1; j++)
    {
      if (a[j + 1] < a[j])
      {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
}

int main()
{
  int arr[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
  bubble_sort(arr, 15);
  for (int i = 0; i < 15; i++)
  {
    cout << arr[i] << endl;
  }
}