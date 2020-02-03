#include <iostream>
#include <vector>
using namespace std;

struct Heap
{
  vector<int> vect;
  int size;
  Heap(int len)
  {
    vect = vector<int>(len + 1, 0);
    size = 1;
  }

  int deleteMin()
  {
    if (size <= 1)
    {
      return -1;
    }
    int min = vect[1];
    vect[1] = vect[size - 1];
    size--;
    int index = 1;
    while (2 * index < size)
    {
      int minIndex = 2 * index;
      int lc = vect[minIndex];
      int minC = lc;
      if (minIndex + 1 < size && vect[minIndex + 1] < minC)
      {
        minIndex = minIndex + 1;
        minC = vect[minIndex];
      }
      if (vect[index] > minC)
      {
        swap(vect[index], vect[minIndex]);
      }
      else
      {
        break;
      }
      index = minIndex;
    }
    return min;
  }

  void insert(int num)
  {
    vect[size] = num;
    int index = size;
    while (index > 1)
    {
      if (vect[index] < vect[index / 2])
      {
        swap(vect[index], vect[index / 2]);
      }
      else
      {
        break;
      }
      index = index / 2;
    }
    size++;
  }
};

void heap_sort(int a[], int len)
{
  Heap heap = Heap(len);
  for (int i = 0; i < len; i++)
  {
    heap.insert(a[i]);
  }
  for (int i = 0; i < len; i++)
  {
    a[i] = heap.deleteMin();
  }
}

int main()
{
  int arr[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
  heap_sort(arr, 15);
  for (int i = 0; i < 15; i++)
  {
    cout << arr[i] << endl;
  }
}
