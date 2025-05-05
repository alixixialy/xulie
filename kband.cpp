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
    int i,j;
    vector<vector<int>> A(mr + 1, vector<int>(ms + 1, -0x3f3f3f)); 
    vector<vector<int>> B(mr + 1, vector<int>(ms + 1, -0x3f3f3f));  
    vector<vector<int>> C(mr + 1, vector<int>(ms + 1, -0x3f3f3f));  

    A[0][0] = 0;
    B[0][0] = -ogap;
    C[0][0] = -ogap;

    for (i = 1; i <= ms && i <= K; i++) {
        A[0][i] = B[0][i] = C[0][i] = -ogap - (i - 1) * egap;
    }
    for (j = 1; j <= mr && j <= K; j++) {
        A[j][0] = B[j][0] = C[j][0] = -ogap - (j - 1) * egap;
    }

    for (i = 1; i <= ms; i++) {
        for (j = max(1, i - K); j <= min(mr, i + K); j++) {
            A[j][i] = p(s[i-1], r[j-1]) + max({A[j-1][i-1], B[j-1][i-1], C[j-1][i-1]});
            int xogap = A[j][i-1] - ogap;
            int xegap = B[j][i-1] - egap;
            B[j][i] = max(xogap, xegap);
            int yogap = A[j-1][i] - ogap;
            int yegap = C[j-1][i] - egap;
            C[j][i] = max(yogap, yegap);
        }
    }

    int mx = max({A[mr][ms], B[mr][ms], C[mr][ms]});
    cout << mx << endl;

    i = ms, j = mr;
    string s1, r1;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && abs(i-j) <= K && A[j][i] == mx) {
            s1 += s[i-1];
            r1 += r[j-1];
            i--; j--;
        } else if (i > 0 && abs(i-1-j) <= K && (B[j][i] == mx)) {
            s1 += s[i-1];
            r1 += '-';
            i--;
        } else if (j > 0 && abs(i-j+1) <= K && (C[j][i] == mx)) {
            s1 += '-';
            r1 += r[j-1];
            j--;
        } else {
            throw runtime_error("Traceback path outside k-band");
        }
        mx = max({A[j][i],B[j][i],C[j][i]});
    }

    reverse(s1.begin(), s1.end());
    reverse(r1.begin(), r1.end());
    cout << s1 << endl << r1 << endl;
    return 0;
}

//ACTGACGTAA
//ACGTGCATTAG 
