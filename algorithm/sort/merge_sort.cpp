#include <iostream>
using namespace std;

void merge(int a[], int left1, int right1, int left2, int right2)
{
  int index1 = left1, index2 = left2;
  int temp[right2 - left1 + 1], index = 0;
  while (index1 <= right1 && index2 <= right2)
  {
    if (a[index1] < a[index2])
    {
      temp[index] = a[index1];
      index1++;
    }
    else
    {
      temp[index] = a[index2];
      index2++;
    }
    index++;
  }

  while (index1 <= right1)
  {
    temp[index] = a[index1];
    index++;
    index1++;
  }

  while (index2 <= right2)
  {
    temp[index] = a[index2];
    index++;
    index2++;
  }

  for (int i = left1; i <= right2; i++)
  {

    a[i] = temp[i - left1];
  }
}

void merge_sort(int a[], int left, int right)
{
  if (right - left == 0)
  {
    return;
  }
  int mid = (left + right) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid + 1, right);
  merge(a, left, mid, mid + 1, right);
}

int main()
{
  int arr[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
  merge_sort(arr, 0, 14);
  for (int i = 0; i < 15; i++)
  {
    cout << arr[i] << endl;
  }
}