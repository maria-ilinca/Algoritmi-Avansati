#include <iostream>
#include <vector>

using namespace std;

vector <string> poz;

int main() {
    long long t,px,py,qx,qy,rx,ry;
    cin >> t;
    poz.resize(t);

    for (int i=0;i<t;i++) {
        cin >> px >> py >> qx >> qy >> rx >> ry;
        long long viraj = qx * ry + px * qy + rx * py - (qx * py + rx * qy + px * ry);
        if (viraj > 0)
            poz[i] = "LEFT";
        else {
            if (viraj < 0)
                poz[i] = "RIGHT";
            else
                poz[i] = "TOUCH";
        }
    }
    for (auto &pozitii:poz)
        cout << pozitii <<endl;
    return 0;
}
