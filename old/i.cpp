#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int> > calls;

bool includes(pair<int, int> times, int call) {
    int maxS = times.first > calls[call].first ? times.first : calls[call].first;
    int minE = times.second < calls[call].second ? times.second : calls[call].second;
    return minE - maxS > 0;
}

int main() {
    int n,m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; i++) {
            int s,d;
            cin >> s >> d >> s >> d;
            int e = s + d;
            calls.push_back(make_pair(s,e));
        }
        for (int i = 0; i < m; i++) {
            int total=0;
            int s,d;
            cin >> s >> d;
            int e = s + d;
            pair<int, int> times = make_pair(s,e);
            for (int j = 0; j < calls.size(); j++) {
                if (includes(times, j)) total++;
            }
            cout << total << endl;
        }
        calls.clear();
    }
}