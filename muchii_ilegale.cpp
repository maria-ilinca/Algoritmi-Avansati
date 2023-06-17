#include <bits/stdc++.h>

using namespace std;

struct Point
{
    long long x, y;
};

vector <Point> puncte ;
Point A, B ,C, D;
long long x1=0, x2=0, y=0, y2=0, z1=0, z2=0, z3=0, y3=0, x3=0, s1=0, s2=0,d;

int main ()
{
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;

    // daca D este in interiorul cercului circ triunghiului ABC => AC e ilegala

    x1=B.x-A.x;
    x2=B.y-A.y;
    y=C.x-A.x;
    y2=C.y-A.y;
    z1=D.x-A.x;
    z2=D.y-A.y;
    x3=B.x*B.x-A.x*A.x+B.y*B.y-A.y*A.y;
    y3=C.x*C.x-A.x*A.x+C.y*C.y-A.y*A.y;
    z3=D.x*D.x-A.x*A.x+D.y*D.y-A.y*A.y;

    s2=z1*y2*x3+z2*y3*x1+x2*y*z3;
    s1=x1*y2*z3+y*z2*x3+x2*y3*z1;
    d = s2-s1;

    // daca d<0 => D este in exteriorul cercului circ triunghiului ABC => AC e legala
    if(d>0)
        cout << "AC: ILLEGAL" << '\n';
    else
        cout << "AC: LEGAL" << '\n';

    x1=C.x-B.x;
    x2=C.y-B.y;
    y=D.x-B.x;
    y2=D.y-B.y;
    z1=A.x-B.x;
    z2=A.y-B.y;
    x3=C.x*C.x-B.x*B.x+C.y*C.y-B.y*B.y;
    y3=D.x*D.x-B.x*B.x+D.y*D.y-B.y*B.y;
    z3=A.x*A.x-B.x*B.x+A.y*A.y-B.y*B.y;
    s1= x1*y2*z3+y*z2*x3+x2*y3*z1;
    s2= z1*y2*x3+z2*y3*x1+x2*y*z3;
    d = s2-s1;
    // daca d>0 => A este in exteriorul cercului circ triunghiului BCD => BD e ilegala
    if(d>0)
        cout << "BD: ILLEGAL" << '\n';
    else
        cout << "BD: LEGAL" << '\n';

    return 0;
}