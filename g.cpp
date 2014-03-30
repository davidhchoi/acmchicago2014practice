#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct Point {
    long double x, y;
    Point(long double x, long double y) : x(x), y(y) {}
};

bool isvalid(int i, int j, bool il, bool jl, vector<pair<Point, Point> >& gates)
{
    assert(i != j);
    if (i > j) {
        int tmp = i;
        i = j;
        j = tmp;
    }
    
    Point p0 = (il ? gates[i].first : gates[i].second);
    Point p1 = (il ? gates[j].first : gates[j].second);
    
    if (p0.x != p1.x) {
        long double s = (p1.y - p0.y) / (p1.x - p0.x);
        long double b = p0.y - s * p0.x;

        for (i = i+1; i < j; i++) {
            long double ic = (gates[i].first.y - b) / s;
            if (gates[i].first.x > ic || ic > gates[i].second.x)
                return false;
        }
    }
    else {
        for (i = i+1; i < j; i++)
            if (gates[i].first.x > p0.x || p0.x > gates[i].second.x)
                return false;
    }

    return true;
}

int main()
{
    while(true) {
        int n;
        cin >> n;
        if (n == 0)
            break;

        long double sx, sy, gx1, gx2, y;
        cin >> sx >> sy;

        vector<pair<Point, Point> > gates;
        for (int i = 0; i < n; i++) {
            cin >> y >> gx1 >> gx2;
            gates.push_back(make_pair(Point(gx1, y), Point(gx2, y)));
        }

        int i, j;
        cin >> i >> j;
        if (isvalid(i, j, true, true, gates))
            cout << "YA" << endl;
    }
    return 0;
}
