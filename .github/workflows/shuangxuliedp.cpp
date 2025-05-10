#include<bits/stdc++.h>

using namespace std;

#define gap 1
#define m 1
#define mis 2

int p(char s,char r){
	if(s==r){
		return m;
	}else{
		return -mis;
	}
}

int main(){
	string s,r;
	cin >> s >> r;
	int i,j,ms,mr;
	ms = s.size();
	mr = r.size();
//	cout << ms << mr;
	vector<vector<int> > A(mr+1, vector<int>(ms+1, 0));
	A[0][0] = 0;
	for(i = 1;i <= ms;i++){
		A[0][i] = -gap*i;
	} 
	for(j = 1;j <= mr;j++){
		A[j][0] = -gap*j;
	}
	int sc,rc,rs;  // sc是s在前，rc是r在前，rs是字符刚好对着 
	for(i = 1;i <= ms;i++){
		for(j = 1;j <= mr;j++){
			rs =  A[j-1][i-1] + p(s[i-1],r[j-1]);
			sc = A[j][i-1] - gap;
			rc = A[j-1][i] - gap;
			int mx;
			mx = max({rs,sc,rc});
			A[j][i] = mx;
		}
	}
	cout << A[mr][ms] << endl;
	j = mr;
	i = ms;
	string s1,r1;
	while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && A[j][i] == A[j-1][i-1] + p(s[i-1],r[j-1])){
            s1 += s[i-1];
            r1 += r[j-1];
            --i;
            --j;
        } else if (j > 0 && A[j][i] == A[j-1][i] - gap) {
            s1 += '-';
            r1 += r[j-1];
            --j;
        } else if (i > 0 && A[j][i] == A[j][i-1] - gap) {
            s1 += s[i-1];
            r1 += '-';
            --i;
        } else {
            throw runtime_error("Invalid traceback path");
        }
    }
    reverse(s1.begin(),s1.end());
    reverse(r1.begin(),r1.end());
    cout << s1 << endl;
    cout << r1 << endl;
} 

//TTGCCATT
//CCAATTTT
