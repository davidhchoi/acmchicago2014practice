#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>
#include <cassert>
using namespace std;

#define MAXN 50001
#define EPSILON 1e-10

typedef pair<double, double> pt;

double d2(pt a, pt b) {
  return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

int main()
{
  int n;
  while (cin >> n) {
    if (n==0) return 0;
    bool flipped;
    // double housex[MAXN];
    // double housey[MAXN];
    pt houses[MAXN];
    double houser2[MAXN];
    double maxr2 = -1;

    bool solved = false;
    double answerx;
    double time;

    for (int i=0; i<n; i++) {
      double x, y;
      cin >> x >> y;
      houses[i] = pt(x,y);
    }
    sort(houses, houses+n);
    int rBegin = n;
    for (int i=0; i<n; i++) {
      double x = houses[i].first;
      double y = houses[i].second;
      houser2[i] = x*x+y*y;
      if (houser2[i] > maxr2) maxr2 = houser2[i];
      if (rBegin == n && x>=0) {
        rBegin = i;
      }
    }
    int minhl = -1;
    for (int i=rBegin-1; i>=0; i--) {
      if (maxr2 - houser2[i] < EPSILON) {
        minhl = i;
        break;
      }
    }
    int minhr = -1;
    for (int i=rBegin; i < n; i++) {
      if (maxr2 - houser2[i] < EPSILON) {
        minhr = i;
        break;
      }
    }
    if (minhl != -1) {
      if (minhr != -1) {
        answerx = 0;
        time = sqrt(maxr2);
        solved = true;
      } else {
        flipped = true;
        for (int i=0; i <= n-1-i; i++) {
          if (i == n-1-i) {
            houses[i] = pt(-houses[i].first, -houses[i].second);
            break;
          }
          pt newr = pt(-houses[i].first, -houses[i].second);
          double newrr2 = houser2[i];
          pt newl = pt(-houses[n-1-i].first, -houses[n-1-i].second);
          double newlr2 = houser2[n-1-i];
          houses[i] = newl;
          houser2[i] = newlr2;
          houses[n-1-i] = newr;
          houser2[n-1-i] = newrr2;
        }
        rBegin = n-rBegin;
        minhr = n-1-minhl;
      }
    }

    if (!solved) {
      int rEnd = minhr+1;
      double cLeft = 0;
      double cRight = houses[minhr].first;
      assert(cRight >= 0);
      while (cRight - cLeft > EPSILON) {
        double guess = (cLeft+cRight)/2;
        pt gC = pt(guess, 0);
        int h = rEnd-1;
        double rad2 = -1;
        pt bdPt;
        for (;h>=0 && houses[h].first>=guess; h--) {
          if (d2(gC, houses[h]) > rad2) {
            rad2 = d2(gC, houses[h]);
            bdPt = houses[h];
          }
        }
        // cerr << "hleft:" << h<<endl;
        bool exceed = false;
        for (;h>=0; h--) {
          // cerr << h << ":: " << d2(gC,houses[h]) << endl;
          if (d2(gC,houses[h]) >= rad2) {
            cRight = guess;
            exceed = true;
            break;
          }
        }
        if (!exceed) {
          cLeft = guess;
        }
        if (cRight-cLeft > 0.01) {
          // cerr <<boolalpha<< "guess:" << guess << " rad2:" << rad2 << " bdPt:" << bdPt.first << ","<<bdPt.second<<" exceed:"<<exceed << endl;
        }
      }
      answerx = cLeft;
      pt gC = pt(cLeft, 0);
      time = -1;
      for (int h=0; h<n; h++) {
        time = max(time, d2(gC, houses[h]));
      }
      time = sqrt(time);
    }
    cout << setprecision(9) << (flipped?(-answerx):answerx) << " " << time << endl;
  }
  return 0;
}
