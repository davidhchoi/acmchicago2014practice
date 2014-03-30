#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define min(a, b) ((a<b) ? a : b)

map<int, set<int> > ps[2];

int idxMaxSize(map<int, set<int> >& ps) {
    unsigned int maxsize = 0, idx;
    for (map<int, set<int> >::iterator it = ps.begin(); it != ps.end(); it++) {
        if ((*it).second.size() >= maxsize) {
            maxsize = (*it).second.size();
            idx = (*it).first;
        }
    }
    return idx;
}

void union_sets(set<int>& x, set<int>& y) {
    for (set<int>::iterator it = y.begin(); it != y.end(); it++)
        x.insert(*it);
}

void prune(map<int, set<int> >& r) {
    for (map<int, set<int> >::iterator it = r.begin(); it != r.end(); it++)
        if ((*it).second.size() == 0)
            r.erase(it--);
}

void bipart(vector<int>& p) {
    map<int, set<int> >::iterator it, it3;
    set<int>::iterator it2;
    for (int i = 0; i < 2; i++) {
        for (it = ps[i].begin(); it != ps[i].end(); it++) {
            vector<int> adj;
            int node = (*it).first;
            for (it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
                if (p[*it2] == i)
                    adj.push_back(*it2);
            for (unsigned int j = 0; j < adj.size(); j++) {
                union_sets((*it).second, ps[i][adj[j]]);
                (*it).second.erase(adj[j]);
                for (it3 = ps[i].begin(); it3 != ps[i].end(); it3++) {
                    (*it3).second.erase(adj[j]);
                    (*it3).second.insert(node);
                }
            }
            (*it).second.erase(node);
        }
    }
}

void print() {
    map<int, set<int> >::iterator it;
    set<int>::iterator it2;
    for (int i = 0; i < 2; i++) {
        for (it = ps[i].begin(); it != ps[i].end(); it++) {
            cout << (*it).first << ": ";
            for (it2 = (*it).second.begin(); it2 != (*it).second.end(); it2++)
                cout << (*it2) << ", ";
            cout << endl;
        }
    }
    system("PAUSE");
}

int main()
{
    int n, m;
    while(cin >> n >> m) {
        if (n == 0 && m == 0)
            break;

        vector<int> p;
        p.push_back(-1); // dummy
        ps[0].clear();
        ps[1].clear();

        int tmp;
        for (int i = 1; i <= n; i++) {
            cin >> tmp;
            p.push_back(tmp);
            ps[tmp].insert(make_pair(i, set<int>()));
        }

        int a, b;
        vector<pair<int, int> > hax;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            hax.push_back(make_pair(a, b));
        }
        for (unsigned int i = 0; i < hax.size(); i++) {
            a = hax[i].first;
            b = hax[i].second;
            ps[p[a]][a].insert(b);
            ps[p[b]][b].insert(a);
        }

//        print();
        bipart(p);
        // for (int i = 0; i < 2; i++)
        //     prune(ps[i]);

//        print();

        map<int, set<int> >::iterator it;
        set<int>::iterator it2;

        int cp = (ps[idxMaxSize(ps[0])].size() > ps[idxMaxSize(ps[1])].size() ? 0 : 1);
        int nmoves = 0;
        while(true) {
            int oppcp = (cp == 0 ? 1 : 0);
            if (ps[0].size() == 0 || ps[1].size() == 0)
                break;
            
            int idx = idxMaxSize(ps[cp]);
            int newidx = *(ps[cp][idx].begin());
//            cout << "merging " << idx << " into " << newidx << endl;
            
            vector<int> gone;
            it2 = ps[cp][idx].begin();
            it2++;
            for (; it2 != ps[cp][idx].end(); it2++) {
                union_sets(ps[oppcp][newidx], ps[oppcp][*it2]);
                ps[oppcp].erase(*it2);
                gone.push_back(*it2);
            }
            ps[oppcp][newidx].erase(idx);
            ps[cp].erase(idx);
            for (it = ps[cp].begin(); it != ps[cp].end(); it++) {
                for (unsigned int i = 0; i < gone.size(); i++) {
                    if ((*it).second.find(gone[i]) != (*it).second.end()) {
                        (*it).second.erase(gone[i]);
                        (*it).second.insert(newidx);
                    }
                }
            }

            cp = oppcp;
            nmoves++;

            bipart(p);
            // for (int i = 0; i < 2; i++)
            //     prune(ps[i]);
            
//            print();
        }
        
        cout << nmoves << endl;
    }
    return 0;
}
