#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN = 20;
int board[MAXN][MAXN];
int N;

int dx[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
int dy[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

bool ok(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1;
}

// ----- Part 1: Plain backtracking -----
bool tour(int x, int y, int step) {
    if (step == N * N) return true;
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (ok(nx, ny)) {
            board[nx][ny] = step;
            if (tour(nx, ny, step + 1)) return true;
            board[nx][ny] = -1;
        }
    }
    return false;
}

// ----- Part 2: Warnsdorff-optimized (≈ O(N²)) -----
int onwardCount(int x, int y) {
    int c = 0;
    for (int k = 0; k < 8; k++)
        if (ok(x + dx[k], y + dy[k])) c++;
    return c;
}

bool tourFast(int x, int y, int step) {
    if (step == N * N) return true;

    int cand[8], count = 0;
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (ok(nx, ny)) cand[count++] = k;
    }

    // Selection sort candidates by onward count (fewest first)
    for (int i = 0; i < count - 1; i++) {
        int best = i;
        for (int j = i + 1; j < count; j++) {
            int a = cand[j], b = cand[best];
            if (onwardCount(x + dx[a], y + dy[a]) <
                onwardCount(x + dx[b], y + dy[b]))
                best = j;
        }
        int tmp = cand[i]; cand[i] = cand[best]; cand[best] = tmp;
    }

    for (int i = 0; i < count; i++) {
        int k = cand[i];
        int nx = x + dx[k], ny = y + dy[k];
        board[nx][ny] = step;
        if (tourFast(nx, ny, step + 1)) return true;
        board[nx][ny] = -1;
    }
    return false;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(3) << board[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    int sx, sy;
    cout << "N: ";          cin >> N;
    cout << "Start x y: ";  cin >> sx >> sy;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    board[sx][sy] = 0;

    if (tourFast(sx, sy, 1)) {
        cout << "\nTour found:\n";
        printBoard();
    } else {
        cout << "No tour from this square.\n";
    }
    return 0;
}