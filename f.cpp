#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define INFINITY 9999999

struct Pos {
    bool grave;
    bool hole;
    pair<int, int> dest;
    int tdiff;
    int dist;
};

int W = 30, H = 30, G, X, Y, E, X2, Y2, T;
Pos grid[30][30];

bool isvalid(int i, int j)
{
    return (0 <= i && i < W && 0 <= j && j < H && !grid[i][j].grave);
}

bool update()
{
    bool changed = false;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            if (grid[i][j].hole) {
                pair<int, int> dest = grid[i][j].dest;
                if (grid[dest.first][dest.second].dist > grid[i][j].dist + grid[i][j].tdiff) {
                    grid[dest.first][dest.second].dist = grid[i][j].dist + grid[i][j].tdiff;
                    changed = true;
                }
            }
            else if (isvalid(i-1, j) && grid[i-1][j].dist > grid[i][j].dist + 1) {
                grid[i-1][j].dist = grid[i][j].dist + 1;
                changed = true;
            }
            else if (isvalid(i+1, j) && grid[i+1][j].dist > grid[i][j].dist + 1) {
                grid[i+1][j].dist = grid[i][j].dist + 1;
                changed = true;
            }
            else if (isvalid(i, j-1) && grid[i][j-1].dist > grid[i][j].dist + 1) {
                grid[i][j-1].dist = grid[i][j].dist + 1;
                changed = true;
            }
            else if (isvalid(i, j+1) && grid[i][j+1].dist > grid[i][j].dist + 1) {
                grid[i][j+1].dist = grid[i][j].dist + 1;
                changed = true;
            }
        }
    }
    return changed;
}

int main()
{
    while(true) {
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                grid[i][j].grave = grid[i][j].hole = false;
                grid[i][j].dist = INFINITY;
            }
        }
        
        cin >> W >> H;
        if (W == 0 && H == 0)
            break;

        cin >> G;
        for (int i = 0; i < G; i++) {
            cin >> X >> Y;
            grid[X][Y].grave = true;
        }

        cin >> E;
        for (int i = 0; i < E; i++) {
            cin >> X >> Y >> X2 >> Y2 >> T;
            grid[X][Y].hole = true;
            grid[X][Y].dest = make_pair(X2, Y2);
            grid[X][Y].tdiff = T;
        }

        grid[0][0].dist = 0;
        for (int i = 0; i <= W*H; i++)
            update();
        if (update())
            cout << "Never" << endl;
        else if (grid[W-1][H-1].dist == INFINITY)
            cout << "Impossible" << endl;
        else
            cout << grid[W-1][H-1].dist << endl;
    }
    
    return 0;
}
