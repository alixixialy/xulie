#include <bits/stdc++.h>
using namespace std;

#define m  1
#define mis  3
#define ogap   5
#define egap    2
#define BAND_K  3

int p(char s, char r) {
    return (s == r) ? m : -mis;
}

struct Trace { int pi, pj, pst; };

pair<string,string> align_pair(const string &s, const string &r) {
    int ms = s.size(), mr = r.size();
    const int NEG_INF = -0x3f3f3f3f;

    vector<vector<int>> A(mr+1, vector<int>(ms+1, -0x3f3f3f3f));
    vector<vector<int>> B(mr+1, vector<int>(ms+1,  -0x3f3f3f3f));
    vector<vector<int>> C(mr+1, vector<int>(ms+1,  -0x3f3f3f3f));
    vector<vector<Trace>> TA(mr+1, vector<Trace>(ms+1)),
                         TB(mr+1, vector<Trace>(ms+1)),
                         TC(mr+1, vector<Trace>(ms+1));

    A[0][0] = 0;
    B[0][0] = C[0][0] = -ogap;
    for(int i=1;i<=ms && i<=BAND_K;i++){
        B[0][i] = -ogap - (i-1)*egap;
        TB[0][i] = {0, i-1, 1};
    }
    for(int j=1;j<=mr && j<=BAND_K;j++){
        C[j][0] = -ogap - (j-1)*egap;
        TC[j][0] = {j-1, 0, 2};
    }

    for(int i=1;i<=ms;i++){
        int jl = max(1, i-BAND_K), jr = min(mr, i+BAND_K);
        for(int j=jl;j<=jr;j++){
            int sc = p(s[i-1], r[j-1]);
            int best = A[j-1][i-1], ps=0;
            if(B[j-1][i-1]>best){
			best=B[j-1][i-1]; ps=1; 
			}
            if(C[j-1][i-1]>best){ 
			best=C[j-1][i-1]; ps=2; 
			}
            A[j][i] = best + sc; TA[j][i] = {j-1,i-1,ps};

            int oi = A[j][i-1] - ogap, ei = B[j][i-1] - egap;
            if(oi>=ei){
			B[j][i]=oi; TB[j][i]={j,i-1,0}; 
			}
            else{ 
			B[j][i]=ei; TB[j][i]={j,i-1,1}; 
			}
			
            int od = A[j-1][i] - ogap, ed = C[j-1][i] - egap;
            if(od>=ed){
			 C[j][i]=od; TC[j][i]={j-1,i,0}; 
			 }
            else{
			 C[j][i]=ed; TC[j][i]={j-1,i,2}; 
			 }
        }
    }

    int i=ms, j=mr, st=0;
    int vM=A[j][i], vI=B[j][i], vD=C[j][i];
    if(vI>vM){ vM=vI; st=1; }
    if(vD>vM){ vM=vD; st=2; }

    string as, ar;
    while(i>0 || j>0){
        if(st==0){
            auto &t=TA[j][i];
            as.push_back(s[i-1]); ar.push_back(r[j-1]);
            j=t.pi; i=t.pj; st=t.pst;
        }
        else if(st==1){
            auto &t=TB[j][i];
            as.push_back(s[i-1]); ar.push_back('-');
            j=t.pi; i=t.pj; st=t.pst;
        }
        else {
            auto &t=TC[j][i];
            as.push_back('-'); ar.push_back(r[j-1]);
            j=t.pi; i=t.pj; st=t.pst;
        }
    }
    reverse(as.begin(), as.end());
    reverse(ar.begin(), ar.end());
    return {as, ar};
}

int main(){
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);

    int N;
    cin>>N;
    vector<string> seqs(N);
    for(int i=0;i<N;i++) cin>>seqs[i];

    vector<int> sumScore(N,0);
    //int sp = -0x3f3f3f3f3f; 
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            auto pr=align_pair(seqs[i], seqs[j]);
            int pts=0;
            for(int k=0;k<pr.first.size();k++)
                if(pr.first[k]==pr.second[k]) pts++;
            sumScore[i]+=pts; sumScore[j]+=pts;
        }
//        if(sp<sumScore[i]){
//        	sp = sumScore[i];
//		}
    }
//    cout << sp << endl;
    int center = max_element(sumScore.begin(), sumScore.end()) - sumScore.begin();
    string s0 = seqs[center];
    int L0 = s0.size();
   // cout << center << endl;
    vector<string> MSA(1, s0);
    vector<int> mapping(L0);
    iota(mapping.begin(), mapping.end(), 0);

    for(int idx=0; idx<N; idx++){
        if(idx==center) continue;
        auto pr = align_pair(s0, seqs[idx]);
        string c_al = pr.first, t_al = pr.second;
        int Lnew = c_al.size();
        int Rold = MSA.size();

        vector<string> newMSA(Rold+1, string());
        vector<int> newMap(L0);
        int orig_idx = 0;
        for(int p=0; p<Lnew; p++){
            if(c_al[p]=='-'){
                for(int r=0; r<Rold; r++)
                    newMSA[r].push_back('-');
            } else {
                int col = mapping[orig_idx];
                for(int r=0; r<Rold; r++)
                    newMSA[r].push_back(MSA[r][col]);
                newMap[orig_idx] = newMSA[0].size() - 1;
                orig_idx++;
            }
            newMSA[Rold].push_back(t_al[p]);
        }
        MSA.swap(newMSA);
        mapping.swap(newMap);
    }

    for(auto &row: MSA)
        cout << row << "\n";
    return 0;
}

