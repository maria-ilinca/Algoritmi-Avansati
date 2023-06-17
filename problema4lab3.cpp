#include <bits/stdc++.h>

using namespace std;

int n, m,a, b, c;
bool ispozitive;
double limit, x, y;


vector < long double > Left, Right, down, up;

void intersection(double a, double b, double c, bool ispozitive, vector <long double> &left, vector <long double> &right, vector <long double> &down, vector <long double> &up) {
    double limit;
    ispozitive = true;
    // by + c <= 0
    if (a == 0) {
        if (b < 0) {
            ispozitive = false;
        }

        limit = (double)(-c) / b;

        if (ispozitive) {
            up.push_back(limit);
        } else {
            down.push_back(limit);
        }
    } else {  // ax + c <= 0
        if (a < 0) {
            ispozitive = false;
        }

        limit = (double)(-c) / a;

        if (ispozitive) {
            right.push_back(limit);
        } else {
            left.push_back(limit);
        }
    }
}


int SmallerBiggestLim(vector < long double >& smaller_lim, double element) {

    if (smaller_lim.empty() || element < smaller_lim[0]) {
        return -1;
    }
        int left = 0, right = smaller_lim.size() - 1, poz = -1;
        while (right >= left) {
            int mid = (left + right) / 2;
            if (element > smaller_lim[mid]) {
                poz = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
            //poz = mid;
        }
        return poz;

}

// the smallest l such that l > element
int BiggerSmallestLim(vector < long double >& bigger_lim, double element) {
    if (bigger_lim.empty() || element > bigger_lim.back()) {
        return -1;
    }

    int left = 0, right = bigger_lim.size() - 1, poz = -1;
    while (right >= left) {
        int mid = (left + right) / 2;
        if (element < bigger_lim[mid]) {
            poz = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
        //poz = mid;
    }

    return poz;
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> a >> b >> c;
        intersection (a, b, c, ispozitive, Left, Right, down, up);
    }

    cin >> m;

    sort(Left.begin(), Left.end());
    sort(Right.begin(), Right.end());
    sort(down.begin(), down.end());
    sort(up.begin(), up.end());

    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;

        int leftIndex = SmallerBiggestLim(Left, x);
        // determina cel mai mare element la stanga lui x
        //cout << leftIndex << '\n';
        int rightIndex = BiggerSmallestLim(Right, x);
        // determina cel mai mic element la dreapta lui x
        // cout << rightIndex << '\n';
        int downIndex = SmallerBiggestLim(down, y);
        // determina cel mai mare element sub y
        // cout << downIndex << '\n';
        int upIndex = BiggerSmallestLim(up, y);
        // determina cel mai mic element peste y
        // cout << upIndex << '\n';

        if (leftIndex == -1 || rightIndex == -1 || downIndex == -1 || upIndex == -1) {
            cout << "NO" << '\n';
        } else {
            long double area = (Right[rightIndex] - Left[leftIndex]) * (up[upIndex] - down[downIndex]);
            cout << "YES" << '\n';
            cout << setprecision(6) << fixed << area << '\n';
        }
    }
}