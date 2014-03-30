#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int n;
    while(cin >> n && n != 0) {
        n *= 2;
        int sqrtn = ceil(sqrt(n)), cnt = 0;
        for (int i = 1; i < sqrtn; i++) {
            if (n % i != 0) continue;
            int a = n / i;
            int b = i;
            int k1 = (a - b + 1);
            int k2 = (a + b - 1);
            if (k1 % 2 != 0 || k2 % 2 != 0 || k1 < 4 || k2 < 4)
                continue;
            cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}
