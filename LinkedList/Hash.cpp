#include <bits/stdc++.h>
using namespace std;
int binarySearch(int arr[], int left, int right, int x)
{
    if (left <= right)
    {
        int mid = (left + right) / 2;
        cout << "We traverse on index: " << mid << endl;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            return binarySearch(arr, mid + 1, right, x);
        else
            return binarySearch(arr, left, mid - 1, x);
    }
    return -1;
}
bool findPairs(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
    int sum;
    map<int, pair<int, int>> myMap;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            sum = arr[i] + arr[j];
            if (myMap.find(sum) == myMap.end())
                myMap[sum] = make_pair(i, j);
            else
            {
                pair<int, int> p = myMap[sum];
                pair1.first = arr[p.first];
                pair1.second = arr[p.second];
                pair2.first = arr[i];
                pair2.second = arr[j];
                return true;
            }
        }
    }
    return false;
}
int foldShift1(string key, int addressSize)
{
    int n = key.length();
    if (n <= addressSize)
    {
        return stoi(key);
    }
    string b = key.substr(0, addressSize);
    return stoi(b) + foldShift1(key.substr(addressSize, n - addressSize), addressSize);
}
int foldShift(long long key, int addressSize)
{
    string a = to_string(key);
    int b = pow(10, addressSize);
    return foldShift1(a, addressSize) % b;
}
int rotation(long long key, int addressSize)
{
    string a = to_string(key);
    int n = a.length();
    string b = "";
    b += a[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        b += a[i];
    }
    int c = pow(10, addressSize);

    return foldShift1(b, addressSize) % c;
}
int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int jp = sqrt(n);
    int i;
    for (i = 0; i < n; i += jp){
        cout << i << ' ';
        if (arr[i] == x)
            return i;
        else if (arr[i] > x)
            break;
    }
    if (i >= n){
            cout << n - 1 << ' ';
        if (arr[n-1] < x)
        {
            return -1;
        } else if (arr[n-1] == x)
            return n - 1;
    }
    int j = i;
    i -= jp;
    i += 1;

    for (; i < j; i++){
        if (i >= n)
            break;
        cout << i << ' ';
        if (arr[i] == x)
            return i;
    }
    return -1;
}
int main(){
  return 0;
}