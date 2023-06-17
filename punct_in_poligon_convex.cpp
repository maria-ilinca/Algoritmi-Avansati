#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y, index;
};

int n, m;

vector < Point > poligon, frontiera_inferioara, frontiera_superioara; // pastreaza punctele din partea de jos si de sus a poligonului
vector < Point > puncte_verificare; // pastreaza punctele de verificat
vector < int > pozitii; // pastreaza rezultatele pentru fiecare punct

// functie care determina orientarea a trei puncte
int det (Point p, Point q, Point r) {
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

bool cmp (Point p, Point q) {
    if (p.x == q.x)
        return p.y < q.y;
    return p.x < q.x;
}

int main() {
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        Point p;
        cin >> p.x >> p.y;
        poligon.push_back(p);
    }

    cin >> m;
    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> puncte_verificare[i].x >> puncte_verificare[i].y;
        puncte_verificare[i].index = i;
    }

    // partitia poligonului in doua parti: partea de jos si partea de sus

        int leftindex = -1;
        int rightindex = -1;

        // determinam punctele din partea de jos si de sus a poligonului
        for (int i = 0; i < n; ++i) {
            // daca punctul curent este mai stanga decat punctul din partea de jos, il actualizam
            if (leftindex == -1 || poligon[i].x < poligon[leftindex].x)
                leftindex = i;
            
            // daca punctul curent este mai dreapta decat punctul din partea de sus, il actualizam
            if (rightindex == -1 || poligon[i].x > poligon[rightindex].x)
                rightindex = i;
        }

        // construim partea de jos a poligonului prin adaugarea punctelor in ordine pana la cel mai din dreapta punct
        int i = leftindex;
        // parcurgem punctele din partea de jos a poligonului

        do {
            frontiera_inferioara.push_back(poligon[i]);
            i = (i + 1) % n;
        } while (i != (rightindex + 1) % n);

        // construim partea de sus a poligonului prin adaugarea punctelor in ordine pana la cel mai din dreapta punct
        // in ordinea inversa a punctelor din partea de jos

        i = leftindex;
        do {
            // adaugam punctul curent in partea de sus a poligonului
            frontiera_superioara.push_back(poligon[i]);
            i = (i - 1 + n) % n;
        } while (i != (rightindex - 1 + n) % n);


    // sortam punctele in functie de coordonata x
    sort(puncte_verificare.begin(), puncte_verificare.end(), cmp);

    int size_inf = frontiera_inferioara.size();
    int size_sup = frontiera_superioara.size();
    
    int minim_x = frontiera_inferioara[0].x;
    int maxim_x = frontiera_inferioara[size_inf - 1].x;

    // index_inf si index_sup sunt indicii pentru frontiera_inferioara si frontiera_superioara
    int index_inf = 0, index_sup = 0, index = 0;

    pozitii.resize(m);

    // verificam daca punctele se afla in exteriorul poligonului
    while (index < m && puncte_verificare[index].x < frontiera_inferioara[0].x) {
        pozitii[puncte_verificare[index].index] = -1;
        ++index;
    }

    int minim_y = frontiera_inferioara[0].y, maxim_y = frontiera_inferioara[0].y;

    // determinam punctele de pe frontierele poligonului care au coordonata x egala cu minim_x

    while (index_inf < size_inf && frontiera_inferioara[index_inf].x == minim_x) {
        minim_y = min(minim_y, frontiera_inferioara[index_inf].y);
        ++index_inf;
    }

    // verificam daca punctele se afla in interiorul poligonului

    while (index_sup < size_sup && frontiera_superioara[index_sup].x == minim_x) {
        maxim_y = max(maxim_y, frontiera_superioara[index_sup].y);
        ++index_sup;
    }

    while (index < m && puncte_verificare[index].x == minim_x) {
        if (puncte_verificare[index].y >= minim_y && puncte_verificare[index].y <= maxim_y) {
            pozitii[puncte_verificare[index].index] = 0;
        } else {
            pozitii[puncte_verificare[index].index] = -1;
        }
        ++index;
    }

// verificam daca punctele se afla pe frontierele poligonului
    while (index < m && puncte_verificare[index].x < maxim_x) {

        while (index_inf < size_inf && frontiera_inferioara[index_inf].x <= puncte_verificare[index].x) {
            ++index_inf;
        }

        --index_inf;

        while (index_sup < size_sup && frontiera_superioara[index_sup].x <= puncte_verificare[index].x) {
            ++index_sup;
        }

        --index_sup;

        // determinam orientarea punctelor fata de dreapta formata de doua puncte consecutive din frontiera

        int or_inf = det(frontiera_inferioara[index_inf], frontiera_inferioara[index_inf + 1], puncte_verificare[index]);
        int or_sup = det(frontiera_superioara[index_sup], frontiera_superioara[index_sup + 1], puncte_verificare[index]);

        if (or_inf == -1 || or_sup == 1) {
            pozitii[puncte_verificare[index].index] = -1;
        } else if (or_inf == 0 || or_sup == 0) {
            pozitii[puncte_verificare[index].index] = 0;
        } else {
            pozitii[puncte_verificare[index].index] = 1;
        }

        ++index;
    }

    minim_y = frontiera_inferioara.back().y;
    maxim_y = frontiera_inferioara.back().y;

    index_inf = size_inf - 1;
    index_sup = size_sup - 1;

    while (index_inf >= 0 && frontiera_inferioara[index_inf].x == maxim_x) {
        minim_y = min(minim_y, frontiera_inferioara[index_inf].y);
        --index_inf;
    }

    while (index_sup >= 0 && frontiera_superioara[index_sup].x == maxim_x) {
        maxim_y = max(maxim_y, frontiera_superioara[index_sup].y);
        --index_sup;
    }

    // verificam daca punctele se afla in interiorul poligonului
    while (index < m && puncte_verificare[index].x == maxim_x) {

        if (puncte_verificare[index].y >= minim_y && puncte_verificare[index].y <= maxim_y) pozitii[puncte_verificare[index].index] = 0;
        else pozitii[puncte_verificare[index].index] = -1;

        ++index;
    }

    // cat timp punctele nu se afla in interiorul poligonului, le marcam ca fiind in exterior
    while (index < m) {
        // marcam punctele ca fiind in exterior
        pozitii[puncte_verificare[index].index] = -1;
        // trecem la urmatorul punct
        ++index;
    }

    for (auto & result: pozitii) {
        if (result == -1) {
            cout << "OUTSIDE" << endl;
        }
        else if (result == 0) {
            cout << "BOUNDARY" << endl;
        }
        else {
            cout << "INSIDE" << endl;
        }
    }
    return 0;
}