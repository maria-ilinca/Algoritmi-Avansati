#include <bits/stdc++.h>
using namespace std;

unsigned int l,k,bit;
string C1,C2;

int main()
{
    cin >> l;
    cin >> C1 >> C2;
    cin >> k;
    for (unsigned int i=k;i<l;i++)
    {
        swap(C1[i],C2[i]);
    }
    cout << C1 << endl;
    cout << C2 << endl;
    return 0;
}