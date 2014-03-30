#include <iostream>
#include <vector>
using namespace std;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317};
int nprimes = sizeof(primes)/sizeof(int);

void factors(int n, vector<int>& ps)
{
    for (int i = 0; i < nprimes; i++) {
        int num = n;
        ps.push_back(0);
        while(num % primes[i] == 0) {
            ps[i]++;
            num /= primes[i];
        }
    }
}

int main()
{
    int n, k, m;
    while(cin >> n >> k >> m) {
        if (n == 0 && k == 0 && m == 0)
            break;
        
        for (int i = 0; i < n; i++) {
            
        }
    }
    
    return 0;
}
