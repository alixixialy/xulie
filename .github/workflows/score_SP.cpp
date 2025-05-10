#include <bits/stdc++.h>
using namespace std;

#define m 1      
#define mis 3  
#define ogap 5     
#define egap 2    
#define K 3        

#define number 2

int p(char s, char r) {
    return (s == r) ? m : -mis;
}

int kband(string s,string r,int ms,int mr){
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
	//cout << mx << endl;
    return mx;

} 

int main() {
	string s[number];
	int sum[number];
	for(int i = 0;i < number;i++){
		cin >> s[i];
		sum[i] = 0;
	}
	int sp = -0x3f3f3f3f,t;
	for(int i = 0;i < number;i++){
		for(int j = i+1;j < number;j++){
		    int ms = s[i].size(), mr = s[j].size();
			int sm = kband(s[i],s[j],ms,mr);
			sum[i] += sm;
			sum[j] += sm;
		}
		if(sum[i]>sp){
			sp = sum[i];
			i = t;
		}
	}
	 cout << sp;
    return 0;
}
