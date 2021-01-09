#include <bits/stdc++.h>
using namespace std;

int main()
{
  return 0;
}

static void sortSegment(T *start, T *end, int segment_idx, int cur_segment_total)
{
  // TODO
  int size = end - start;
  int step = cur_segment_total;
  int idxMin = segment_idx;
  for (int i = segment_idx; i < size - step; i += step)
  {
    idxMin = i;
    for (int j = i + step; j < size; j += step)
    {
      if (start[idxMin] > start[j])
      {
        idxMin = j;
      }
    }
    T tmp = start[i];
    start[i] = start[idxMin];
    start[idxMin] = tmp;
  }
}

static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases)
{
  // TODO
  // Note: You must print out the array after sorting segments to check whether your algorithm is true.
  for (int i = num_phases - 1; i >= 0; i--)
  {
    cout << num_segment_list[i] << " segments: ";
    for (int j = 0; j < num_segment_list[i]; j++)
    {
      sortSegment(start, end, j, num_segment_list[i]);
    }
    printArray(start, end);
  }
}

template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
  int i, j, idxMin;
  int n = end - start;

  for (i = 0; i < n - 1; i++)
  {
    idxMin = i;
    for (j = i + 1; j < n; j++)
      if (start[j] < start[idxMin])
        idxMin = j;

    T tmp = start[idxMin];
    start[idxMin] = start[i];
    start[i] = tmp;
    printArray(start, end);
  }
}

template <class T>
void Sorting<T>::oddEvenSort(T *start, T *end)
{
  /*TODO*/
  int n = end - start;
  bool isSorted = false;

  while (!isSorted)
  {
    isSorted = true;

    for (int i = 0; i <= n - 2; i = i + 2)
    {
      if (start[i] > start[i + 1])
      {
        T tmp = start[i];
        start[i] = start[i + 1];
        start[i + 1] = tmp;
        isSorted = false;
      }
    }

    for (int i = 1; i <= n - 2; i = i + 2)
    {
      if (start[i] > start[i + 1])
      {
        T tmp = start[i];
        start[i] = start[i + 1];
        start[i + 1] = tmp;
        isSorted = false;
      }
    }

    printArray(start, end);
  }

  return;
}

template <class T>
void SLinkedList<T>::bubbleSort()
{
  for (int i = 0; i < this->size() - 1; i++)
  {
    for (int j = 0; j < this->size() - 1; j++)
    {
      Node *p1 = this->head, *p2 = this->head;
      int m = j, n = j + 1;
      while (m--)
      {
        p1 = p1->next;
      }
      while (n--)
      {
        p2 = p2->next;
      }
      if (p1->data > p2->data)
      {
        T tmp = p1->data;
        p1->data = p2->data;
        p2->data = tmp;
      }
    }
    printList();
  }
}

static T *Partition(T *start, T *end)
{
  // TODO: return the pointer which points to the pivot after rearrange the array.
  T *i = start, *j = end;
  do
  {
    do
    {
      i += 1;
    } while (*i < *start);

    do
    {
      j -= 1;
    } while (*j > *start);

    T tmp = *i;
    *i = *j;
    *j = tmp;
  } while (i < j);

  T tmp = *i;
  *i = *j;
  *j = tmp;

  tmp = *start;
  *start = *j;
  *j = tmp;

  return j;
}

static void QuickSort(T *start, T *end)
{
  // TODO
  // In this question, you must print out the index of pivot in subarray after everytime calling method Partition.
  T *pivot = Partition(start, end);
  cout << pivot - start << ' ';
  if (pivot - start > 0)
    QuickSort(start, pivot);
  if (end - pivot > 1)
    QuickSort(pivot + 1, end);
}

static void merge(T *left, T *middle, T *right)
{
  /*TODO*/
  int i, j, k;
  int n1 = middle - left + 1;
  int n2 = right - middle;

  /* Tạo các mảng tạm */
  int L[n1], R[n2];

  /* Copy dữ liệu sang các mảng tạm */
  for (i = 0; i < n1; i++)
    L[i] = *(left + i);
  for (j = 0; j < n2; j++)
    R[j] = *(middle + 1 + j);

  /* Gộp hai mảng tạm vừa rồi vào mảng arr*/
  i = 0; // Khởi tạo chỉ số bắt đầu của mảng con đầu tiên
  j = 0; // Khởi tạo chỉ số bắt đầu của mảng con thứ hai
  k = 0; // IKhởi tạo chỉ số bắt đầu của mảng lưu kết quả
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      *(left + k) = L[i];
      i++;
    }
    else
    {
      *(left + k) = R[j];
      j++;
    }
    k++;
  }

  /* Copy các phần tử còn lại của mảng L vào arr nếu có */
  while (i < n1)
  {
    *(left + k) = L[i];
    i++;
    k++;
  }

  /* Copy các phần tử còn lại của mảng R vào arr nếu có */
  while (j < n2)
  {
    *(left + k) = R[j];
    j++;
    k++;
  }

  Sorting::printArray(left, right);
}
static void mergeSort(T *start, T *end)
{
  /*TODO*/
  if (end - start < 1)
    return;
  T *mid = start + (end - start) / 2;

  if (mid - start >= 1)
    mergeSort(start, mid);
  if (end - mid >= 2)
    mergeSort(mid + 1, end);

  merge(start, mid, end);
}

template <class T>
T *Sorting<T>::Partition(T *start, T *end)
{
  cout << "Quick sort: ";
  printArray(start, end);
  T *i = start, *j = end;
  while (i < j)
  {
    do
    {
      i += 1;
    } while (*i < *start);

    do
    {
      j -= 1;
    } while (*j > *start);

    T tmp = *i;
    *i = *j;
    *j = tmp;
  }

  T tmp = *i;
  *i = *j;
  *j = tmp;

  tmp = *start;
  *start = *j;
  *j = tmp;

  return j;
}

template <class T>
void Sorting<T>::insertionSort(T *start, T *end)
{
  if (end - start > 1)
  {
    cout << "Insertion sort: ";
    printArray(start, end);

    T *cur = start + 1;
    while (cur < end)
    {
      T tmp = *cur;
      T *w = cur - 1;
      while (w >= start && tmp < *w)
      {
        *(w + 1) = *w;
        w--;
      }
      *(w + 1) = tmp;
      cur++;
    }
  }
}

template <class T>
void Sorting<T>::hybridQuickSort(T *start, T *end, int min_size)
{
  if (end - start < min_size)
  {
    insertionSort(start, end);
    return;
  }
  T *pivot = Partition(start, end);
  if (pivot - start > 0)
    hybridQuickSort(start, pivot, min_size);
  if (end - pivot > 1)
    hybridQuickSort(pivot + 1, end, min_size);
}

static void merge(T *start, T *middle, T *end)
{
  int n1 = middle - start + 1;
  int n2 = end - middle;
  int i = 0, j = 0, k = 0;
  int L[n1], R[n2];
  for (i = 0; i < n1; i++)
  {
    L[i] = start[i];
  }
  for (j = 0; j < n2; j++)
  {
    R[j] = middle[j + 1];
  }
  i = 0;
  j = 0;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      start[k] = L[i];
      i++;
    }
    else
    {
      start[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1)
  {
    start[k] = L[i];
    i++;
    k++;
  }
  while (j < n2)
  {
    start[k] = R[j];
    j++;
    k++;
  }
};

static void InsertionSort(T *start, T *end)
{
  int size = end - start;
  for (int i = 0; i <= size; i++)
  {
    T value = start[i];
    int index = i;
    for (int j = i; j > 0; j--)
    {
      if (start[j - 1] > value)
      {
        start[j] = start[j - 1];
        index = j - 1;
      }
    }
    start[index] = value;
  }
};
static void TimSort(T *start, T *end, int min_size)
{
  int n = end - start;
  for (int i = 0; i < n; i += min_size)
  {
    if ((i + min_size - 1) < (n - 1))
    {
      InsertionSort(start + i, start + i + min_size - 1);
    }
    else
    {
      InsertionSort(start + i, end);
    }
  }
  cout << "Insertion Sort:";
  for (int i = 0; i < n; i++)
  {
    cout << " " << start[i];
  }
  cout << endl;
  int right = 0;
  int count = 1;
  for (int size = min_size; size < n; size = 2 * size)
  {
    for (int left = 0; left < n; left += 2 * size)
    {
      int mid = left + size - 1;
      if ((left + 2 * size - 1) < (n - 1))
      {
        right = (left + 2 * size - 1);
      }
      else
      {
        right = n - 1;
      }
      merge(start + left, start + mid, start + right);
      cout << "Merge " << count << ":";
      for (int i = 0; i < n; i++)
      {
        cout << " " << start[i];
      }
      cout << endl;
      count++;
    }
  }
};

bool isPermutation(string a, string b)
{
  //TODO
  int ax[255] = {0}, bx[255] = {0};
  if (a.length() != b.length())
    return false;

  for (int i = 0; i < int(a.length()); i++)
  {
    ax[int(a[i])] += 1;
    bx[int(b[i])] += 1;
  }

  for (int i = 0; i < 255; i++)
  {
    if (ax[i] != bx[i])
      return false;
  }
  return true;
}