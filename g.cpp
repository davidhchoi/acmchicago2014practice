#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    while(cin >> n && n != 0) {
        int sidx = 2, eidx = 2;
        int sum = 2, cnt = 0;
        while(sidx <= n) {
            if (sum == n && eidx <= n)
                cnt++;
            if (sum < n)
                sum += ++eidx;
            else if (sum >= n)
                sum -= sidx++;

            if (sidx > eidx)
                eidx = sidx;
        }
        cout << cnt << endl;
    }
    return 0;
}
