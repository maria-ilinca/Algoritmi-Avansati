#include <bits/stdc++.h>
using namespace std;

int n;
double a, b, c;
double suma = 0;

vector < double > valf;

double f(double x)
{
    double funct = 0;
    funct = a*x*x+b*x+c;
    return funct;
}

int main()
{
    cin >> a >> b >> c;
    cin >> n;
    valf.resize(n+1);
    valf[0] = 0;
    for (int i=1;i<=n;i++)
    {
        double x;
        cin >> x;
        valf[i] = f(x);
        suma = suma + valf[i];
    }
    for (int i=0;i<=n;i++)
    {
        double s = 0;
        for (int j=0;j<=i;j++)
        {
           s = s + valf[j];
        }
          cout << setprecision (4) << s/suma << endl;
    }
    return 0;
}
