> 对堆排序、归并排序、快排做了要点总结，其他如冒泡/选择/插入不多赘述了，见相应代码

### 一. [堆排序](https://github.com/Weiting-Zhang/Blog/tree/master/algorithm/sort/heap_sort.cpp)

1. 思路：使用数组构造一个有序的小顶堆(完全二叉树)，每次取其顶端元素（最小值），即可实现排序。构造过程可抽象为 `insert` 操作， 取出顶端元素抽象为 `deleteMin` 操作
2. 二叉堆实现

   - 由于二叉堆都是完全二叉树，满足"除了最底层，其他所有层都已经填满，且最底层尽可能从左到右填入" 的性质，其层级性质可以用数组索引来表示。
   - 具体方法为：空出数组第一个元素，则第 k 个元素的左右孩子分别为 2k, 2k+1

3. `insert` 实现

   - 将新插入的元素放到最后一个位置，并进行上浮(`swim`)操作
   - `swim`：如果当前元素大于其父亲或者已经到第一个位置（根）则结束比较，否则一直和其父亲交换
   - 相应代码
     ```cpp
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
     ```

4. `deleteMin` 实现

   - 将最后一个元素放到根的位置，并返回根元素的值
   - 对新的根进行下沉(`sink`)操作
   - `sink`: 如果它没有孩子或者它的值比左右孩子都小则结束比较，否则一直和其左右孩子较小的那个交换
   - 相应代码
     ```cpp
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
     ```

5. [完整代码](https://github.com/Weiting-Zhang/Blog/tree/master/algorithm/sort/heap_sort.cpp)

6. 补充：如何进行原地排序

   - 在原地通过 `swim` 构造出一个有序的大顶堆，当第 k 次取出当前堆的顶端元素时（会取出最 k 大的值），则放到空闲的最后 n-k 的位置上，最终即可原地排序。

### 二. 归并排序

1. 思路
2. 递归操作
3. merge 实现

### 三. 快速排序

1. 思路
2. 递归操作
3. partition 实现
