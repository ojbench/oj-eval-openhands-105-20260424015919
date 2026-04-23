
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    // E[k][eaten] = expected days to eat exactly m apples starting from k apples having already eaten 'eaten' apples
    vector<vector<double>> E(n + 1, vector<double>(m + 1, 0.0));
    
    // Base case: if we've already eaten m apples, we need 0 more days
    for (int k = 0; k <= n; k++) {
        E[k][m] = 0.0;
    }
    
    // Calculate DP values
    // We need to be careful about the order of calculation
    for (int eaten = m - 1; eaten >= 0; eaten--) {
        for (int k = 0; k <= n; k++) {
            if (k == 0) {
                // No apples left, but we haven't eaten m yet - this is an invalid state
                // In practice, we shouldn't reach this state if m <= n
                E[k][eaten] = 0.0;
                continue;
            }
            
            double sum = 0.0;
            for (int i = 1; i <= k; i++) {
                int new_k = max(k - i, 0);
                int new_eaten = min(eaten + i, m);
                sum += E[new_k][new_eaten];
            }
            
            E[k][eaten] = 1.0 + sum / k;
        }
    }
    
    cout << fixed << setprecision(2) << E[n][0] << endl;
    
    return 0;
}
