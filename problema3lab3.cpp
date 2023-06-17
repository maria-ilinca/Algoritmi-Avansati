#include <iostream>

using namespace std;

int xMin = -10000000, maxi_x = 10000000;

int n, a, b, c;

bool ispozitive;
double limit, left_x, right_x, jos_y, sus_y;

void intersection(double a, double b, double c, bool ispozitive, double& left_x, double& right_x, double& jos_y, double& sus_y) {
    double limit;
    ispozitive = true;
    // daca a = 0, atunci ecuatia este de forma by + c <= 0
    if (a == 0) {
        if (b < 0) {
            ispozitive = false;
        }
        // limita este parametrul pentru care ecuatia este adevarata
        limit = (double)(-c) / b;

        if (ispozitive) {
            // daca ispozitive are val true, atunci limita este mai mica decat sus_y
            sus_y = min(sus_y, limit);
        } else {
            // daca ispozitive are val false, atunci limita este mai mare decat jos_y
            jos_y = max(jos_y, limit);
        }
    } else {
        if (a < 0) {
            ispozitive = false;
        }
        limit = (double)(-c) / a;

        if (ispozitive) {
            // daca ispozitive are val true, atunci limita este mai mica decat right_x
            right_x = min(right_x, limit);
        } else {
            // daca ispozitive are val false, atunci limita este mai mare decat left_x
            left_x = max(left_x, limit);
        }
    }
}


int main() {
    cin >> n;
    // initializam limitele cu valori maxime si minime
    // scadem 5 ca sa nu avem probleme cu valori de limita
    left_x = jos_y = xMin-3;
    right_x = sus_y = maxi_x + 3;
    for (int i = 1; i <= n; ++i) {
        // ax + by + c <= 0
        // ax + c <= 0
        // by + c <= 0
        cin >> a >> b >> c;
        intersection(a, b, c, ispozitive, left_x, right_x, jos_y, sus_y);

    }

    if (left_x > right_x || jos_y > sus_y) {
        cout << "VOID";
    } else if (left_x == xMin - 3 || jos_y == xMin - 3 || right_x == maxi_x + 3 || sus_y == maxi_x + 3) {
        cout << "UNBOUNDED";
    } else {
        cout << "BOUNDED";
    }
}
