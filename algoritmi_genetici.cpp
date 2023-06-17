#include <bits/stdc++.h>

using namespace std;


ofstream fout ("Evolutie.txt");
int n, a, b, c, d, e, p,l;
double pr, pm, etape,D;

/* input  = dimensiunea populatiei (numarul de cromozomi)
          = domeniul de definitie al functiei (capetele unui interval inchis)
          = parametrii pentru functia de maximizat (coeficientii polinomului de grad 2)
          = precizia cu care se lucreaza (cu care se discretizeaza intervalul)
          = probabilitatea de recombinare (crossover, incrucisare)
          = probabilitatea de mutatie
          = numarul de etape al algoritmului
*/

struct individ {
    string cromozom;
    double valoare;
    double fitness;
    double probabilitate;
    int index;
};

vector < individ > populatie;
vector < individ > populatie_noua;
vector < individ > incrucisari;
vector <individ> bestindividuals;

void read(){
    cout << "Introduceti dimensiunea populatiei: ";
    cin >> n;
    cout << "Introduceti capetele intervalului inchis: ";
    cin >> a >> b;
    cout << "Introduceti coeficientii polinomului de grad 2: ";
    cin >> c >> d >> e;
    cout << "Introduceti precizia cu care se lucreaza: ";
    cin >> p;
    cout << "Introduceti probabilitatea de recombinare: ";
    cin >> pr;
    cout << "Introduceti probabilitatea de mutatie: ";
    cin >> pm;
    cout << "Introduceti numarul de etape al algoritmului: ";
    cin >> etape;
}

// pentru problema de maxim functia este chiar f
double f(double x, int c, int d, int e){
    return c * x * x + d * x + e;
}

string decimalToBinary (int n){
    string s = "";
    while (n > 0){
        s = (n % 2 == 0 ? "0" : "1") + s;
        n /= 2;
    }
    return s;
}

int binaryToDecimal(string bString) {
    int decimal = 0;
    for (int i = 0; i < bString.size(); ++i) {
        decimal += (bString[i] - '0') * pow(2, bString.size() - i - 1);
    }

    return decimal;
}

void generate_initial_population(){
    srand(time(NULL));
    fout << "Populatia initiala" << endl;

    // generam n cromozomi (siruri de 0 si 1) de lungime l
    l = log2 ((b - a)*pow(10, p));
    D = (b - a) / pow (2, l);
    for (int i=1;i<=n;i++){
        individ indiv;

        string s;
        double x;
        int cnt = 0;
        double interval = a + D;
        // generate a random double x in the interval [a,b]
        x = a + (double)rand() / RAND_MAX * (b - a);
        indiv.valoare = x;
        // calculare cnt = numarul de intervale de lungime D din [a,x]
        while (interval < x){
            cnt = cnt + 1;
            interval = interval + D;
        }
        // transformare x din baza 10 in baza 2
        s = decimalToBinary (cnt);
        // completare cu 0 la stanga pana la lungimea l
        for (int j = 0; j < l - s.length(); j++)
            s.insert(0, "0");

        indiv.cromozom = s;
        indiv.fitness = f(x, c, d, e);
        populatie.push_back(indiv);

        fout << i << ": " << indiv.cromozom << " x= " << indiv.valoare << " f= " << indiv.fitness << endl;
    }
}

void select(){
    populatie_noua.clear();
    fout << "Probabilitatile de selectie" << endl;
    double suma = 0;
    for (int i=0;i<n;i++){
        suma = suma + populatie[i].fitness;
    }
    for (int i=0;i<n;i++){
        populatie[i].probabilitate = populatie[i].fitness / suma;
        fout <<"cromozom    " << i+1 << " "<< populatie[i].probabilitate << endl;
    }

    // determinarea intervalelor de selectie ca suma de probabilitati
    // pentru fiecare cromozom se calculeaza suma probabilitatilor tuturor cromozomilor dinaintea lui
    // intervalul de selectie este [0, suma probabilitatilor]
    vector < double > intervale;
    double suma_probabilitati = 0;
    intervale.push_back(suma_probabilitati);

    for (int i=0;i<n-1;i++){
        suma_probabilitati = suma_probabilitati + populatie[i].probabilitate;
        intervale.push_back(suma_probabilitati);
    }
    fout << "Intervale probabilitati selectie" << endl;
    for (int i=0;i<intervale.size();i++)
        fout << intervale[i] << " ";

    // generam un numar random intre 0 si 1
    // si determinam cromozomul care corespunde intervalului in care se afla numarul generat
    fout << endl;
    for (int i=0;i<n;i++){
        double u;
        u = (double)rand() / RAND_MAX;
        fout << "u = " << u << " ";
        fout << "selectam cromozomul ";
        // cautare binara a lui u in intervale
        int st = 0, dr = intervale.size() - 1, mij;
        while (st <= dr){
            mij = (st + dr) / 2;
            if (u < intervale[mij])
                dr = mij - 1;
            else
                st = mij + 1;
        }
        fout << st - 1 << endl;
        populatie_noua.push_back(populatie[st-1]);
    }
    fout << "Dupa selectie: " << endl;
    for (int i=0;i<n;i++){
        fout << i+1 << ": "<<populatie_noua[i].cromozom << " x= " << populatie_noua[i].valoare << " f= " << populatie_noua[i].fitness << endl;
    }
    if (bestindividuals.size()) {
        populatie_noua[0] = bestindividuals[0];
    }
}


void crossover() {
    incrucisari.clear();
    fout << "Probabilitate de incrucisare: " << pr << endl;
    for (int i = 0; i < n; i++) {
        double u;
        u = (double) rand() / RAND_MAX;
        populatie_noua[i].index = i;
        if (u < pr && i > 0) {
            fout << i + 1 << ": " << populatie_noua[i].cromozom << " u= " << u << "<" << pr << " participa" << endl;
            incrucisari.push_back(populatie_noua[i]);
        } else
            fout << i + 1 << ": " << populatie_noua[i].cromozom << " u= " << u << endl;
    }
    for (int i = 0; i < incrucisari.size(); i = i + 2) {
        if (i + 1 == incrucisari.size())
            break;
        fout << "Cromozomii care participa la incrucisare: " << endl;
        fout << incrucisari[i].cromozom << " " << incrucisari[i + 1].cromozom << endl;
        int poz = rand() % l;
        fout << "Pozitia de incrucisare: " << poz << endl;
        string c1, c2;
        c1 = incrucisari[i].cromozom;
        c2 = incrucisari[i + 1].cromozom;

        string c1aux = c1;
        string c2aux = c2;

        for (int j = 0; j < poz; j++)
            swap(c1[j], c2[j]);

        fout << "Rezultat: " << endl;
        fout << c1 << " " << c2 << endl;
        // generez o gena random si o schimb cu una random din cromozomul 1
        int gena = rand() % l;
        char aux = c1aux[gena];
        c1aux[gena] = c2aux[gena];
        c2aux[gena] = aux;
        fout << "Mutatie: " << endl;
        fout << c1aux << " " << c2aux << endl;

        int decimal = binaryToDecimal(c1aux);

        double leftBound = a;
        int count = 0;

        while (count < decimal) {
            leftBound += D;
            ++count;
        }

        populatie_noua[incrucisari[i].index].cromozom = c1aux;
        populatie_noua[incrucisari[i].index].valoare = leftBound;
        populatie_noua[incrucisari[i].index].fitness = f(leftBound, c, d, e);

        decimal = binaryToDecimal(c2aux);

        leftBound = a;
        count = 0;

        while (count < decimal) {
            leftBound += D;
            ++count;
        }

        populatie_noua[incrucisari[i + 1].index].cromozom = c2aux;
        populatie_noua[incrucisari[i + 1].index].valoare = leftBound;
        populatie_noua[incrucisari[i + 1].index].fitness = f(leftBound, c, d, e);
    }

    fout << "Dupa combinare: " << endl;
    for (int i = 0; i < n; i++) {
        fout << i + 1 << ": " << populatie_noua[i].cromozom << " x= " << populatie_noua[i].valoare << " f= "
             << populatie_noua[i].fitness << endl;
    }
}


void mutate(){
    fout << "Probabilitate de mutatie pentru fiecare gena " << pm << endl;
    fout << "Au fost modificati cromozomii: " << endl;
    // generare numar random cromozom care va fi modificat
    int cromozom = rand() % n;
    fout << cromozom << endl;
    // pentru fiecare gena a cromozomului generam un numar random intre 0 si 1
    // daca numarul este mai mic decat probabilitatea de mutatie atunci gena este modificata
    for (int i=0;i<l;i++){
        double u;
        u = (double)rand() / RAND_MAX;
        if (u < pm){
            if (populatie_noua[cromozom].cromozom[i] == '0')
                populatie_noua[cromozom].cromozom[i] = '1';
            else
                populatie_noua[cromozom].cromozom[i] = '0';
        }
    }

    int decimal = binaryToDecimal(populatie_noua[cromozom].cromozom);

    double leftBound = a;
    int count = 0;

    while (count < decimal) {
        leftBound += D;
        ++count;
    }

    populatie_noua[cromozom].valoare = leftBound;
    populatie_noua[cromozom].fitness = f(leftBound, c, d, e);

    fout << "Dupa mutatie: " << endl;
    for (int i=0;i<n;i++){
        fout << i+1 << ": "<<populatie_noua[i].cromozom << " x= " << populatie_noua[i].valoare << " f= " << populatie_noua[i].fitness << endl;
    }

}

// maximul pentru functia de fitness
void maximandmean(int epoca)
{
    bestindividuals.clear();
    double maxim = -1;
    double suma = 0;
    for (int i=0;i<n;i++){
        suma = suma + populatie_noua[i].fitness;
        if (populatie_noua[i].fitness > maxim)
            maxim = populatie_noua[i].fitness;
    }

    vector <individ> sortedindividuals;
    sortedindividuals = populatie_noua;

    sort(sortedindividuals.begin(), sortedindividuals.end(), [](const individ & i1, const individ & i2) {
        return i1.fitness > i2.fitness;
    });
    bestindividuals.push_back(sortedindividuals[0]);

    fout << "Ceil mai bun cromozom: " << endl;
    for (int i=0;i<1;i++){
        fout << i+1 << ": "<<bestindividuals[i].cromozom << " x= " << bestindividuals[i].valoare << " f= " << bestindividuals[i].fitness << endl;
    }

    fout << "Epoca " << epoca << endl;
    fout << "Max fitness: " << fixed << setprecision(20)<< maxim << endl;
    fout << "Mean fitness: " << fixed <<setprecision(20)<< suma / n << endl;
    cout << maxim << '\n';
    fout << endl;
}


int main()
{
    read();
    generate_initial_population();
    select();
    crossover();
    mutate();
    maximandmean(1);
    for (int i=0;i<etape;i++){
        populatie = populatie_noua;
        populatie[0] = bestindividuals[0];
        select();
        crossover();
        mutate();
        maximandmean(i+1);
    }

    return 0;
}
