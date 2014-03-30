#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define max(a,b) ((a>b)?a:b)

int main()
{
    int m;
    string str;
    while(cin >> m && m != 0) {
        cin >> str;

        queue<pair<string, vector<int> > > sss;
        vector<int> tmp;
        for (int i = 0; i < str.size(); i++)
            tmp.push_back(i);
        sss.push(make_pair("", tmp));

        int l = 0, rmIdx = 0;
        while(!sss.empty()) {
            string ss = sss.front().first;
            vector<int> ssLocs = sss.front().second;
            sss.pop();

            if (ss.size() > l)
                rmIdx = ssLocs.back();
            l = ss.size();

            vector<vector<int> > alphacnt(26, vector<int>());
            for (int i = 0; i < ssLocs.size(); i++)
                if (ssLocs[i]+l < str.size())
                    alphacnt[str[ssLocs[i]+l]-'a'].push_back(ssLocs[i]);
            for (int i = 0; i < 26; i++) {
                if (alphacnt[i].size() >= m) {
                    sss.push(make_pair(ss + (char)('a'+i), alphacnt[i]));
                }
            }
        }

        if (l == 0)
            cout << "none" << endl;
        else
            cout << l << " " << rmIdx << endl;
    }
    return 0;
}
