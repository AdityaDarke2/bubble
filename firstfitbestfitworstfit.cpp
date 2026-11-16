#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void printAllocation(string name, vector<int> p,
                     vector<int> a, vector<int> b) {
    cout << "\n--- " << name << " ---\n";
    cout << "Process\tSize\tBlock\tFragmentation\n";

    for (int i = 0; i < p.size(); i++) {
        cout << i + 1 << "\t" << p[i] << "\t";

        if (a[i] != -1)
            cout << a[i] + 1 << "\t" << b[a[i]] - p[i];
        else
            cout << "Not Allocated\t-";

        cout << "\n";
    }
}

// First Fit
void firstFit(vector<int> b, vector<int> p) {
    vector<int> a(p.size(), -1);
    vector<bool> used(b.size(), false);

    for (int i = 0; i < p.size(); i++)
        for (int j = 0; j < b.size(); j++)
            if (!used[j] && b[j] >= p[i]) {
                a[i] = j;
                used[j] = true;
                break;
            }

    printAllocation("FIRST FIT", p, a, b);
}

// Best Fit
void bestFit(vector<int> b, vector<int> p) {
    vector<int> a(p.size(), -1);
    vector<bool> used(b.size(), false);

    for (int i = 0; i < p.size(); i++) {
        int best = -1;

        for (int j = 0; j < b.size(); j++)
            if (!used[j] && b[j] >= p[i])
                if (best == -1 || b[j] < b[best])
                    best = j;

        if (best != -1) {
            a[i] = best;
            used[best] = true;
        }
    }

    printAllocation("BEST FIT", p, a, b);
}

// Worst Fit
void worstFit(vector<int> b, vector<int> p) {
    vector<int> a(p.size(), -1);
    vector<bool> used(b.size(), false);

    for (int i = 0; i < p.size(); i++) {
        int worst = -1;

        for (int j = 0; j < b.size(); j++)
            if (!used[j] && b[j] >= p[i])
                if (worst == -1 || b[j] > b[worst])
                    worst = j;

        if (worst != -1) {
            a[i] = worst;
            used[worst] = true;
        }
    }

    printAllocation("WORST FIT", p, a, b);
}

int main() {
    int n, m;

    cout << "Enter number of blocks: ";
    cin >> n;

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cout << "Block " << i + 1 << ": ";
        cin >> b[i];
    }

    cout << "Enter number of processes: ";
    cin >> m;

    vector<int> p(m);
    for (int i = 0; i < m; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> p[i];
    }

    firstFit(b, p);
    bestFit(b, p);
    worstFit(b, p);

    return 0;
}