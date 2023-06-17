#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

int n, x, y, x_maxim, y_maxim;
int countChangeX, countChangeY;
Point maxPointX, maxPointY;

vector < Point > points;

// build a function that will count the number of changes in the direction of the points
int count_changes(int n, int maxi, int &changes, char c)
{
    changes = 0;
    int index = 0;
    int urcare = 0;
    for (int i = maxi; i < n + maxi; ++i) {
        index = i % n;
        if (c == 'x')
        {
            if (points[index].x < points[index + 1].x) {
                if (urcare == 0) urcare = 1;

                else if (urcare == -1) {
                    urcare = 1;
                    changes++;
                }
            }
            else if (points[index].x > points[index + 1].x) {
                if (urcare == 0) urcare = -1;

                else if (urcare == 1) {
                    urcare = -1;
                    changes++;
                }
            }
        }
        else if (c == 'y')
        {
            if (points[index].y < points[index + 1].y) {
                if (urcare == 0) urcare = 1;

                else if (urcare == -1) {
                    urcare = 1;
                    changes++;
                }
            }
            else if (points[index].y > points[index + 1].y) {
                if (urcare == 0) urcare = -1;

                else if (urcare == 1) {
                    urcare = -1;
                    changes++;
                }
            }
        }
        else
        {
            cout << "Error: invalid character";
            return 0;
        }
    }
    return changes;
}


int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        points.push_back({x, y});

        // Find the point with the maximum x and y coordinates
        if (points[i].x > maxPointX.x) {
            maxPointX = points[i];
            x_maxim = i;
        }
        if (points[i].y > maxPointY.y) {
            maxPointY = points[i];
            y_maxim = i;
        }
    }

    countChangeX = count_changes(n, x_maxim, countChangeX, 'x');

    //cout << countChangeX << endl;

    countChangeY = count_changes(n, y_maxim, countChangeY, 'y');

    //cout << countChangeY << endl;

    countChangeX > 2 ? cout << "NO\n" : cout << "YES\n";
    countChangeY > 2 ? cout << "NO\n" : cout << "YES\n";

    return 0;
}