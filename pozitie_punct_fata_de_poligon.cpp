#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
};

long long n, m;
int muchii_stanga, muchii_dreapta;

vector < Point > polygon; // vectorul in care vom retine punctele poligonului

int orientare(Point p, Point q, Point r) {
    
    long long rez;
    rez = q.x*r.y+p.x*q.y+p.y*r.x-p.x*r.y-q.y*r.x-p.y*q.x;
    if (rez > 0)
        return 1;
    else {
        if (rez < 0)
            return -1;
        else
            return 0;
    }
}

// functie care verifica daca punctul q este in interiorul poligonului

int pozitie_punct(Point q) {

    for (int i = 0; i < n; ++i) { 
        
        Point p1 = polygon[i], p2 = polygon[(i + 1) % n];
        // primul si al doilea punct al muchiei

        if (p1.y > p2.y || (p1.y == p2.y && p1.x > p2.x)) {
            // daca primul punct este mai sus decat al doilea punct, ii interschimbam
            swap(p1, p2);
        }

        if (q.y < p1.y || q.y > p2.y) { // daca q este in afara muchiei, ignora muchia
            continue;
        }
        // daca muchia este verticala

        if (p1.x == p2.x) {
            // daca q este aliniat cu muchia, il ignora
            if (q.y == p1.y) continue;

            // daca q este la stanga muchiei, creste muchii_dreapta
            else if (q.x < p1.x) muchii_dreapta++;

            // daca q este la dreapta muchiei, creste muchii_stanga
             else if (q.x > p1.x) muchii_stanga++;

             else return 0; // q e pe muchie

        }
        else if (p1.y == p2.y) { // daca muchia este orizontala
            if (q.x >= p1.x && q.x <= p2.x) return 0; // q este pe muchie
            
            else continue;
        }

        else { // daca muchia nu este nici verticala nici orizontala

            int rez = orientare(p1, p2, q);

           // daca q este pe muchie, returneaza 0
            if (rez == 0) return 0;
            

            // daca q este pe muchie, ignora-l
            if (q.y == p1.y) continue;

            // daca q este la stanga muchiei, creste muchii_dreapta
            // daca q este la dreapta muchiei, creste muchii_stanga

            if (rez == -1) {
                muchii_stanga++;
            } else {
                muchii_dreapta++;
            }
        }
    }

    // daca numarul de muchii la stanga si dreapta este impar, punctul este in interiorul poligonului
    if (muchii_stanga % 2 == 1 && muchii_dreapta % 2 == 1) return 1;

    return -1;
}

int main() {

    Point punct;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        polygon.push_back({x, y});
    }

    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        cin >> punct.x >> punct.y;

        int poz = pozitie_punct(punct);

        if (poz == 0)
            cout << "BOUNDARY\n";

        else if (poz == 1)
            cout << "INSIDE\n";

        else
            cout << "OUTSIDE\n";

      muchii_dreapta = muchii_stanga = 0;
    }

    return 0;
}