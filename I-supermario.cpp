#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <cstdio>
#include <cassert>
using namespace std;

#define INF 1e99

struct pt {
  int x;
  int y;
  int z;
};

inline int sq(int x) {return x*x;}

double dist(pt a, pt b) {
  return sqrt(sq(a.x-b.x)+sq(a.y-b.y)+sq(a.z-b.z));
}

int nS;
pt start;
int nC[20];
pt sw[20];
pt coins[20][20];
double dms[20];
double dsc[20][20][20]; // i j k = switch i to coin k of switch j
double dcc[20][20][20]; // i k1 k2 = switch i, coin k1 to k2
double switchtocoins[20][20]; // i k = switch i to coins with k last
double swtoswMid[20][20];
//double swtoswEnd[20][20];
double minFinish[20];

double tspCache[9000][20]; // subset k
bool isCached[9000][20];

// kEnd not in subset
double tspCoins(int s, unsigned int subset, int kEnd) {
  if (isCached[subset][kEnd]) {
    return tspCache[subset][kEnd];
  }
  assert(!( (1<<kEnd) &subset));
  if (subset == 0) return dsc[s][s][kEnd];
  double solution = INF;
  for (int k=0; k<nC[s]; k++) {
    if ((1<<k)&subset) {
      double alt = dcc[s][k][kEnd] + tspCoins(s,subset&(~(1 << k)),k);
      if (alt < solution) solution = alt;
    }
  }
  tspCache[subset][kEnd] = solution;
  isCached[subset][kEnd] = true;
  return solution;
}
double tspSwitch(unsigned int subset, int kEnd) {
  if (isCached[subset][kEnd]) {
    return tspCache[subset][kEnd];
  }
  assert(!( (1<<kEnd) &subset));
  if (subset == 0) return dms[kEnd];
  double solution = INF;
  for (int k=0; k<nS; k++) {
    if ((1<<k)&subset) {
      double alt = swtoswMid[k][kEnd] + tspSwitch(subset&(~(1 << k)),k);
      if (alt < solution) solution = alt;
    }
  }
  tspCache[subset][kEnd] = solution;
  isCached[subset][kEnd] = true;
  return solution;
}

void calcSwitch(int s) {
  // set isCached to false
  memset(isCached, 0, sizeof isCached);
  unsigned int fullset = (1<<nC[s])-1;
  minFinish[s] = INF;
  for (int kEnd=0; kEnd<nC[s]; kEnd++) {
    switchtocoins[s][kEnd] = tspCoins(s,fullset&(~(1<<kEnd)),kEnd);
    if (switchtocoins[s][kEnd] < minFinish[s]) {
      minFinish[s] = switchtocoins[s][kEnd];
    }
  }
  for (int sj=0; sj<nS; sj++) {
    if (s == sj) {
      swtoswMid[s][sj] = INF;
      continue;
    }
    double poss= INF;
    for (int kEnd=0; kEnd<nC[s]; kEnd++) {
      poss = min(poss, switchtocoins[s][kEnd]+dsc[sj][s][kEnd]);
    }
    swtoswMid[s][sj] = poss;
  }
}



double solveSwitches() {
  for (int i=0; i<nS; i++) {
    calcSwitch(i);
  }
  /*
  for (int i=0; i<nS; i++) {
    for (int j=0; j<nS; j++) {
      if (i == j) {
        swtoswEnd[i][j] = INF;
        continue;
      }
      swtoswEnd[i][j] = swtoswMid[i][j] + minFinish[j];
    }
  }
  */
  memset(isCached, 0, sizeof isCached);
  double answer = INF;
  unsigned int fullset = (1 << nS) - 1;
  for (int jEnd=0; jEnd<nS; jEnd++) {
    answer = min(answer, minFinish[jEnd] + tspSwitch(fullset&(~(1<<jEnd)), jEnd));
  }
  return answer;
}

int main() {
  while (cin >> nS >> start.x >> start.y >> start.z) {
    if (nS == 0) return 0;
    for (int i=0; i<nS; i++) {
      cin >> nC[i] >> sw[i].x >> sw[i].y >> sw[i].z;
      for (int k=0; k<nC[i]; k++) {
        cin >> coins[i][k].x >> coins[i][k].y >> coins[i][k].z;
      }
    }
    // preprocess
    for (int i=0; i<nS; i++) {
      dms[i] = dist(start, sw[i]);
      for (int k=0; k<nC[i]; k++) {
        for (int k2=0; k2<nC[i]; k2++) {
          double d = dist(coins[i][k], coins[i][k2]);
          dcc[i][k][k2] = d;
        }
        for (int j=0; j<nS; j++) {
          double d= dist(coins[i][k], sw[j]);
          dsc[j][i][k] = d;
        }
      }
    }
    // solve
    printf("%.2f\n", solveSwitches());
  }
  return 0;
}
