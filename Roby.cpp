#include <iostream>

using namespace std;
// creez un vector de viraje: viraje[0]=nr de viraje la stanga
// viraje[1] = numarul de viraje la dreapta
// viraje[2] = numarul de puncte in care continua drept inainte

int viraje[3];

void viraj(int px, int py, int qx, int qy, int rx, int ry)
{
    int rez;
    rez = qx*ry+px*qy+py*rx-px*ry-qy*rx-py*qx;
    if (rez > 0)
        viraje[0]++;
    else if (rez < 0) viraje[1]++;
    else viraje[2]++;
}

int main()
{
    int n, x1,y1,x2,y2,x3,y3, xstart, ystart;
    cin >> n;
    // consideram separat primele 2 puncte
    cin >> xstart >> ystart;
    x1=xstart; y1=ystart;
    cin >> x2 >> y2;
    for (int i=0;i<n-2;i++)
    {
        cin >> x3 >> y3;
        viraj(x1, y1, x2, y2, x3, y3);
        x1 = x2;
        x2 = x3;
        y1 = y2;
        y2 = y3;
    }
    // la final trebuie sa ne intoarcem in pct de start
    viraj(x1, y1, x2, y2, xstart, ystart);
    for (int i = 0; i <= 2; i++)
         cout << viraje[i] << "  ";
    return 0;
}

