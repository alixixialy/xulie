#include <bits/stdc++.h>
using namespace std;

#define m 1      
#define mis 2  
#define ogap 3     
#define egap 1    
#define K 3        

int p(char s, char r) {
    return (s == r) ? m : -mis;
}

int main() {
    string s, r;
    cin >> s >> r;
    int ms = s.size(), mr = r.size();

    vector<int> prev_A(2*K+1, -0x3f3f3f), curr_A(2*K+1);
    vector<int> prev_B(2*K+1, -0x3f3f3f), curr_B(2*K+1);
    vector<int> prev_C(2*K+1, -0x3f3f3f), curr_C(2*K+1);

    int init_pos = K; 
    prev_A[init_pos] = 0;
    prev_B[init_pos] = -ogap;
    prev_C[init_pos] = -ogap;

    for (int j = 1; j <= K && j <= mr; ++j) {
        int pos = j + K;
        prev_A[pos] = prev_B[pos] = prev_C[pos] = -ogap - (j-1)*egap;
    }

    for (int i = 1; i <= K && i <= ms; ++i) {
        int pos = i + K;
        prev_A[pos] = prev_B[pos] = prev_C[pos] = -ogap - (i-1)*egap;
    }

    for (int i = 1; i <= ms; ++i) {
        int start_j = max(1, i - K);
        int end_j = min(mr, i + K);
        for (int j = start_j; j <= end_j; ++j) {
            int pos = j - (i - K);
            curr_A[pos] = curr_B[pos] = curr_C[pos] = -0x3f3f3f;

            if (i > 0 && j > 0) {
                int a = prev_A[pos], b = prev_B[pos], c = prev_C[pos];
                curr_A[pos] = p(s[i-1], r[j-1]) + max({a, b, c});
            }

            if (i > 0) {
                int prev_pos = pos + 1;
                if (prev_pos < prev_B.size()) {
                    int a = prev_A[prev_pos];
                    int b_val = prev_B[prev_pos];
                    curr_B[pos] = max(a - ogap, b_val - egap);
                }
            }

            if (j > 0) {
                int prev_pos = pos - 1;
                if (prev_pos >= 0) {
                    int a = curr_A[prev_pos];
                    int c_val = curr_C[prev_pos];
                    curr_C[pos] = max(a - ogap, c_val - egap);
                }
            }
        }
        prev_A.swap(curr_A);
        prev_B.swap(curr_B);
        prev_C.swap(curr_C);
    }

    int final_pos = mr - (ms - K);
    int mx = max({prev_A[final_pos], prev_B[final_pos], prev_C[final_pos]});
    cout << mx << endl;
    return 0;
}
