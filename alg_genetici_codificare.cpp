#include <bits/stdc++.h>

using namespace std;

//function to convert binary to decimal

int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0

    int base = 1;

    int len = num.length();

    for (int i = len - 1; i >= 0; i--) {

        if (num[i] == '1')

            dec_value += base;

        base = base * 2;
    }

    return dec_value;
}

//function to convert decimal to binary
string decimalToBinary(long long n)
{
    string s = "";
    while (n > 0) {
        s = (n % 2 == 0 ? "0" : "1") + s;
        n /= 2;
    }

    return s;
}

int main() {
    long long a, b, p, m;
    string sir;
    cin >> a >> b;
    cin >> p;
    long long l = ceil (log2 ((b - a)*pow(10, p)));
    double d = (b - a) / pow (2, l);
    cin >> m;
    for (int i=1;i<=m;i++) {
        cin >> sir;
        if (sir == "TO") {
            double x;
            cin >> x;
            double interval = a + d;
            int cnt = 0;
            while (interval < x)
            {
                cnt = cnt + 1;
                interval = interval + d;
            }

            if (interval == x)
            {
                cnt = cnt + 1;
            }

            string binar = decimalToBinary(cnt);
            if (binar.length() < l) {
                for (long long i = 0; i < l - binar.length(); i++) {
                    cout << "0";
                }
            }

            cout << binar << endl;

        }

        if (sir == "FROM") {
            string binar;
            cin >> binar;
            long long interval = binaryToDecimal(binar);
            double x = a + interval * d;
            cout << setprecision(4) << x << endl;

        }
    }
    return 0;
}
