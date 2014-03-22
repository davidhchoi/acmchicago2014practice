#include <iostream>
using namespace std;

int main() {
  int N;
  int testcase = 0;
  while (cin >> N) {
    if (N == 0) return 0;
    if (testcase > 0) {
      cout << endl;
    }
    int pile1 = 0;
    int pile2 = 0;
    for (int instr=0; instr<N; instr++) {
      string action;
      int m;
      cin >> action >> m;
      if (action == "DROP") {
        cout << "DROP 1 " << m << endl;
        pile1 += m;
      } else if (action == "TAKE") {
        int first = 0;
        if (pile2 > 0) {
          first = min(pile2, m);
          m -= first;
          pile2 -= first;
          cout << "TAKE 2 " << first << endl;
        }
        if (m>0) {
          cout << "MOVE 1->2 " << pile1 << endl;
          cout << "TAKE 2 " << m << endl;
          pile2 = pile2 + pile1 - m;
          pile1 = 0;
        }
      }
    }
    testcase++;
  }
  return 0;
}
        

