#include <iostream>
using namespace std;

const int MAXD = 30;

struct Peg {
    int d[MAXD];
    int top = -1;
    void push(int v) { d[++top] = v; }
    int  pop()       { return d[top--]; }
    int  peek()      { return top >= 0 ? d[top] : 0; } // 0 = empty
};

void doMove(Peg pegs[], int a, int b) {
    int disk = pegs[a].pop();
    pegs[b].push(disk);
    cout << "Move disk " << disk
         << " from peg " << char('A' + a)
         << " to peg "   << char('A' + b) << "\n";
}

void hanoiIterative(int n) {
    Peg pegs[3];

    // Largest disk first so smallest ends up on top
    for (int i = n; i >= 1; i--)
        pegs[0].push(i);

    // Cyclic order for the smallest disk
    int order[3];
    if (n % 2 == 1) { order[0] = 0; order[1] = 2; order[2] = 1; }
    else            { order[0] = 0; order[1] = 1; order[2] = 2; }

    long long total = (1LL << n) - 1;
    int idx = 0;

    for (long long m = 0; m < total; m++) {
        if (m % 2 == 0) {
            int from = order[idx % 3];
            int to   = order[(idx + 1) % 3];
            doMove(pegs, from, to);
            idx++;
        } else {
            int occupied = order[idx % 3];
            int p1 = -1, p2 = -1;
            for (int p = 0; p < 3; p++) {
                if (p == occupied) continue;
                if (p1 == -1) p1 = p; else p2 = p;
            }
            int t1 = pegs[p1].peek();
            int t2 = pegs[p2].peek();

            if (t1 == 0)      doMove(pegs, p2, p1);
            else if (t2 == 0) doMove(pegs, p1, p2);
            else if (t1 < t2) doMove(pegs, p1, p2);
            else              doMove(pegs, p2, p1);
        }
    }
}

int main() {
    int n;
    cout << "Number of disks: ";
    cin >> n;
    cout << "Total moves: " << ((1LL << n) - 1) << "\n\n";
    hanoiIterative(n);
    return 0;
}