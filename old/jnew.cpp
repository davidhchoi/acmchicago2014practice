#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;
string str;
int n;
int m;
int best;

vector<pair<unsigned long long, int> > numFound[40005];

int insertss(unsigned long long hash) {
    for (int i = 0; i < numFound[hash % 40005].size(); i++) {
        if (numFound[hash%40005][i].first == hash) {
            return ++numFound[hash%40005][i].second;
        }
    }
    numFound[hash%40005].push_back(make_pair(hash, 1));
    return 1;
}

bool works(int len) {
    if (len > n) return false;
    for (int i = 0; i < 40005; i++)
        numFound[i].clear();
    unsigned long long hash = 0;
    int bests = -1;
    unsigned long long subtract = 1;
    for (int i = 0; i < len - 1; i++) {
        subtract *= 30;
    }
    for (int i = 0; i < len; i++) {
        hash = (hash * 30 + (str[i] - 'a'));
    }
    if (insertss(hash) >= m)
        bests = 0;
    for (int i = 1; i + len <= n; i++) {
        // cout << hash << " " << subtract << endl;
        hash = hash - subtract * (str[i - 1] - 'a');
        hash = (hash * 30 + (str[i + len - 1] - 'a'));
        int amount = insertss(hash);
        // cout << amount << " a " << i << " " << hash << endl;
        if (amount >= m)
            bests = i;
    }
    // cout << hash << endl;
    best = bests;
    return bests != -1;
}

int main() {
    while (cin >> m) {
        if (m == 0) break;
        cin >> str;
        n = str.length();
        if (!works(1))
            cout << "none" << endl;
        else {
            int upper = n+1, lower = 1;
            while (upper != lower + 1) {
                int mean = (upper + lower) / 2;
                if (works(mean)) {
                    lower = mean;
                } else {
                    upper = mean;
                }
            }
            works(lower);
            cout << lower << " " << best << endl;

        }
    }
}