#include <bits/stdc++.h>
#include <vector>

//Convex Hall -Acoperire convexa
//Input: n - nr varfuri
//P1 P2 .. Pn - varfurile (xi, yi)
//Output: varfurile acoperirii convexe
//Poligon parcurs in sens trigonometric
//Complexitate de timp O(n)

using namespace std;

// calculez determinantul pentru o lista de puncte formata din 3 pcte

int det (pair<long long, long long> a, pair<long long, long long> b, pair<long long, long long> c)
{
    long long rez = b.first*c.second+a.first*b.second+a.second*c.first-a.first*c.second-b.second*c.first-a.second*b.first;
    if (rez > 0)
        return true;
    return false;
}

int main()
{
    long long n,x,y;
    vector<pair<long long, long long>> points;
    vector<pair<long long, long long>>frontiera_superioara;
    vector<pair<long long, long long>>frontiera_inferioara;
    vector<pair<long long, long long>>frontiera;

    cin >> n;
    for (int i=0;i<n;i++)
    {
        cin >> x >> y;
        points.emplace_back(x,y);
    }

    sort(points.begin(), points.end());

    frontiera_inferioara.push_back(points[0]);
    frontiera_inferioara.push_back(points[1]);

    for (int i = 2; i < n; ++i) {
        frontiera_inferioara.push_back(points[i]);
        while (frontiera_inferioara.size() > 2 && !det(frontiera_inferioara[frontiera_inferioara.size() - 3], frontiera_inferioara[frontiera_inferioara.size() - 2], frontiera_inferioara[frontiera_inferioara.size() - 1])) {
            frontiera_inferioara.erase(frontiera_inferioara.begin() + frontiera_inferioara.size() - 2);
        }
    }

    frontiera_superioara.push_back(points[n - 1]);
    frontiera_superioara.push_back(points[n - 2]);

    for (int i = n - 3; i >= 0; --i) {
        frontiera_superioara.push_back(points[i]);
        while (frontiera_superioara.size() > 2 && !det(frontiera_superioara[frontiera_superioara.size() - 3], frontiera_superioara[frontiera_superioara.size() - 2], frontiera_superioara[frontiera_superioara.size() - 1])) {
            frontiera_superioara.erase(frontiera_superioara.begin() + frontiera_superioara.size() - 2);
        }
    }

    frontiera_superioara.erase(frontiera_superioara.begin());
    frontiera_superioara.erase(frontiera_superioara.begin() + frontiera_superioara.size() - 1);

    frontiera.insert(frontiera.end(), frontiera_inferioara.begin(), frontiera_inferioara.end());
    frontiera.insert(frontiera.end(), frontiera_superioara.begin(), frontiera_superioara.end());

    cout << frontiera.size() << '\n';
    for (auto const& point : frontiera) {
        cout << point.first << " " << point.second << '\n';
    }

    return 0;
}