#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define EPS 1e-10

int main()
{
    int n;
    while(cin >> n && n != 0) {
        vector<pair<double, double> > vehs;

        int x, v, vmax = 0;
        for (int i = 0; i < n; i++) {
            cin >> x >> v;
            vehs.push_back(make_pair(x, v));
            if (fabs(v) > vmax)
                vmax = fabs(v);
        }

        double tmin = 0.0, tmax = 200000.0 / (double)vmax;
        int minidx, maxidx;
        while(fabs(tmax - tmin) > EPS) {
            double tmid = (tmin + tmax) / 2.0;
            double mind = vehs[0].first + vehs[0].second * tmid, maxd = mind;
            minidx = maxidx = 0;
            for (int i = 1; i < n; i++) {
                double d = vehs[i].first + vehs[i].second * tmid;
                if (d < mind) {
                    mind = d;
                    minidx = i;
                }
                if (d > maxd) {
                    maxd = d;
                    maxidx = i;
                }
            }
            if (vehs[minidx].second - vehs[maxidx].second <= 0)
                tmax = tmid;
            else 
                tmin = tmid;
        }
        printf("%.2f\n", fabs(
               (vehs[maxidx].first + vehs[maxidx].second * tmin) -
               (vehs[minidx].first + vehs[minidx].second * tmin)));
    }
    return 0;
}
