#include <bits/stdc++.h>
using namespace std;

unsigned int l,k,bit;
string C;

int main()
{
  cin >> l >> k;
  cin >> C;
  for (unsigned int i=0;i<k;i++)
  {
    cin >> bit;
    if (C[bit] == '0')
      C[bit] = '1';
    else
      C[bit] = '0';
  }
    cout << C << endl;
    return 0;

}

