#include <bits/stdc++.h>
using namespace std;

int countStop(int totalDistance, int maxDistanceFullTank, vector<int> stopPoint)
{
  int result = 0;
  int distance = 0;
  int i = 0;
  while (distance < totalDistance)
  {
    if (totalDistance - distance <= maxDistanceFullTank)
    {
      return result;
    }
    if (i < int(stopPoint.size()))
    {
      if (stopPoint[i] - distance == maxDistanceFullTank)
      {
        distance = stopPoint[i];
        result++;
        i++;
      }
      else
      {
        if (stopPoint[i] - distance > maxDistanceFullTank)
        {
          if (i == 0 || distance == stopPoint[i - 1])
          {
            return -1;
          }
          else
          {
            distance = stopPoint[i - 1];
            result++;
          }
        }
        else
        {
          i++;
        }
      }
    }
    else
    {
      if (distance == stopPoint[stopPoint.size() - 1])
      {
        if (maxDistanceFullTank < totalDistance - distance)
        {
          return -1;
        }
        else
        {
          return result;
        }
      }
      else
      {
        if (maxDistanceFullTank < totalDistance - stopPoint[stopPoint.size() - 1])
        {
          return -1;
        }
        else
        {
          return ++result;
        }
      }
    }
  }
  return result;
}

long long results(int n, list<int> &listNumber)
{
  if (listNumber.empty())
  {
    return 0;
  }
  int a = listNumber.back();
  listNumber.pop_back();
  return a * pow(10, n) + results(n - 1, listNumber);
}
long long largestNumber(list<int> listNumber)
{
  listNumber.sort();
  return results(listNumber.size() - 1, listNumber);
}

bool isSubSequence(string substr, string s, int m, int n)
{
  if (m == 0)
    return true;
  if (n == 0)
    return false;

  if (substr[m - 1] == s[n - 1] && m - 1 != n - 1)
    return isSubSequence(substr, s, m - 1, n - 1);

  return isSubSequence(substr, s, m, n - 1);
}
bool isGood(int n, string s, int l, int r)
{
  //Return true if good, false if not
  string substr = "";
  for (int i = l; i <= r; i++)
  {
    substr += s[i];
  }
  return isSubSequence(substr, s, r - l + 1, n);
}

string SpecialString(int n, int k)
{
  // TODO: return a string satisfying conditions.
  string str = "";
  for (int i = 0; i < k; i++)
  {
    str += 'b';
  }
  for (int i = k; i < n; i++)
  {
    if (str[i - 1] == 'a')
      str += 'b';
    else if (str[i - 1] == 'b')
      str += 'c';
    else if (str[i - 1] == 'c')
      str += 'a';
  }
  return str;
}

#define ll long long

ll int sumOfOnes(ll int n, ll int l, ll int r)
{
  deque<ll int> dq;
  ll int i = 1;
  ll int tmp;
  ll int rs = 0;
  int x = n % 2;
  n = n >> 1;
  dq.push_front(n);
  dq.push_front(x);
  dq.push_front(n);
  while (!dq.empty())
  {
    tmp = dq.front();
    dq.pop_front();
    if (tmp > 1)
    {
      x = tmp % 2;
      tmp = tmp >> 1;
      dq.push_front(tmp);
      dq.push_front(x);
      dq.push_front(tmp);
    }
    else
    {
      if (i >= l && i <= r)
      {
        rs += tmp;
        i++;
      }
      else if (i > r)
      {
        break;
      }
      else
      {
        i++;
      }
    }
  }
  return rs;
}

int uniqueNumber(int x)
{
  string a = "";
  if (x < 10)
  {
    return x;
  }
  else
  {
    while (x > 0)
    {
      if (x < 10)
      {
        if (x < int(9 - a.size() - 1))
        {
          a += char(x + 48);
          x = 0;
        }
        else
        {
          int c = 9 - a.size();
          if (c < 0)
          {
            return -1;
          }
          a += char(c + 48);
          x -= c;
        }
      }
      else
      {
        int c = 9 - a.size();
        if (c < 0)
        {
          return -1;
        }
        a += char(c + 48);
        x -= c;
      }
    }
  }
  string results = "";
  for (int i = 0; i < int(a.size()); i++)
  {
    results += a[int(a.size()) - i - 1];
  }
  return stoi(results);
}

int main()
{
  return 0;
}