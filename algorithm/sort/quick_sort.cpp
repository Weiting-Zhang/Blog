#include <iostream>
using namespace std;

int partition(int a[], int left, int right)
{
  int pNum = a[right];
  int lessIndex = left;
  for (int i = left; i < right; i++)
  {
    if (a[i] < pNum)
    {
      swap(a[i], a[lessIndex]);
      lessIndex++;
    }
  }
  swap(a[lessIndex], a[right]);
  return lessIndex;
}

void quick_sort(int a[], int left, int right)
{
  if (left >= right)
  {
    return;
  }
  int pIndex = partition(a, left, right);
  quick_sort(a, left, pIndex - 1);
  quick_sort(a, pIndex + 1, right);
}

int main()
{
  int arr[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
  quick_sort(arr, 0, 14);
  for (int i = 0; i < 15; i++)
  {
    cout << arr[i] << endl;
  }
}