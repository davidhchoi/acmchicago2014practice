#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#define min(a, b) ((a<b) ? a : b)

int rns(vector<int>& rn, int a) {
    while(rn[a] != a)
        a = rn[a];
    return a;
}

int idxMaxSize(map<int, set<int> >& ps) {
    int maxsize = 0, idx;
    for (map<int, set<int> >::iterator it = ps.begin(); it != ps.end(); it++) {
        if ((*it).second.size() > maxsize) {
            maxsize = (*it).second.size();
            idx = (*it).first;
        }
    }
    return idx;
}

int main()
{
    int n, m;
    while(cin >> n >> m) {
        if (n == 0 && m == 0)
            break;

        vector<int> p;
        p.push_back(-1); // dummy
        vector<int> rn;
        rn.push_back(-1); // dummy
        map<int, set<int> > ps[2];

        int tmp;
        for (int i = 1; i <= n; i++) {
            cin >> tmp;
            p.push_back(tmp);
            rn.push_back(i);
            ps[tmp].insert(make_pair(i, set<int>()));
        }

        int a, b;
        vector<pair<int, int> > hax;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            hax.push_back(make_pair(a, b));
        }
        sort(hax.begin(), hax.end());
        for (unsigned int i = 0; i < hax.size(); i++) {
            a = hax[i].first;
            b = hax[i].second;
            if (p[a] == p[b])
                rn[b] = a;
            int ra = rns(rn, a), rb = rns(rn, b);
            if (ra != rb) {
                ps[p[a]][ra].insert(rb);
                ps[p[b]][rb].insert(ra);
            }
        }

        map<int, set<int> >::iterator it;
        set<int>::iterator it2;

        for (int i = 0; i < 2; i++)
            for (it = ps[i].begin(); it != ps[i].end(); it++)
                if ((*it).second.size() == 0)
                    ps[i].erase(it--);

        int cp = (ps[idxMaxSize(ps[0])].size() > ps[idxMaxSize(ps[1])].size() ? 0 : 1);
        while(true) {
            int idx = idxMaxSize(ps[cp]);
            int oppcp = (cp == 0 ? 1 : 0);
            set<int> res;
            for (it2 = ps[cp][idx].begin(); it2 != ps[cp][idx].end(); it2++)
                set_union(res.begin(), res.end(), ps[oppcp][*it2].begin(),
                          ps[oppcp][*it2].end(), res.begin());
            res.erase(idx);
            
        }
        
        for (it = ps[0].begin(); it != ps[0].end(); it++) {
            cout << (*it).first << ": ";
            for (it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
                cout << (*it2) << ", ";
            cout << endl;
        }
        for (it = ps[1].begin(); it != ps[1].end(); it++) {
            cout << (*it).first << ": ";
            for (it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
                cout << (*it2) << ", ";
            cout << endl;
        }
    }
    return 0;
}
