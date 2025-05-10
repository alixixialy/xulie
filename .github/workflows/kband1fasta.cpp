#include <bits/stdc++.h>
using namespace std;

#define m 1
#define mis 2
#define ogap 3
#define egap 1
#define K 3

// FASTA记录结构体
struct FastaRecord {
    string header;
    string sequence;
};

// 读取FASTA文件函数
vector<FastaRecord> read_fasta(const string& filename) {
    ifstream file(filename);
    vector<FastaRecord> records;
    string line;
    FastaRecord current;

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        if (line[0] == '>') {
            if (!current.header.empty()) {
                records.push_back(current);
                current = FastaRecord();
            }
            current.header = line.substr(1);
        } else {
            line.erase(remove(line.begin(), line.end(), '\r'), line.end());
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            current.sequence += line;
        }
    }
    
    if (!current.header.empty()) {
        records.push_back(current);
    }
    
    if (records.size() < 2) {
        throw runtime_error("需要至少两个序列进行比对");
    }
    
    return records;
}

int p(char s, char r) {
    return (s == r) ? m : -mis;
}

int main() {
    try {
        // 读取输入文件
        auto records = read_fasta("input.fasta");
        string s = records[0].sequence;
        string r = records[1].sequence;

        // 原始比对算法保持不变
        int ms = s.size(), mr = r.size();
        vector<vector<int>> A(mr+1, vector<int>(ms+1, -0x3f3f3f));
        vector<vector<int>> B(mr+1, vector<int>(ms+1, -0x3f3f3f));
        vector<vector<int>> C(mr+1, vector<int>(ms+1, -0x3f3f3f));

        A[0][0] = 0;
        B[0][0] = -ogap;
        C[0][0] = -ogap;

        for (int i = 1; i <= ms && i <= K; i++) {
            A[0][i] = B[0][i] = C[0][i] = -ogap - (i-1)*egap;
        }
        for (int j = 1; j <= mr && j <= K; j++) {
            A[j][0] = B[j][0] = C[j][0] = -ogap - (j-1)*egap;
        }

        for (int i = 1; i <= ms; i++) {
            for (int j = max(1, i-K); j <= min(mr, i+K); j++) {
                A[j][i] = p(s[i-1], r[j-1]) + max({A[j-1][i-1], B[j-1][i-1], C[j-1][i-1]});
                B[j][i] = max(A[j][i-1]-ogap, B[j][i-1]-egap);
                C[j][i] = max(A[j-1][i]-ogap, C[j-1][i]-egap);
            }
        }

        int mx = max({A[mr][ms], B[mr][ms], C[mr][ms]});
        
        // 回溯路径
        int i = ms, j = mr;
        string s1, r1;
        while (i > 0 || j > 0) {
            if (i>0 && j>0 && abs(i-j)<=K && A[j][i]==mx) {
                s1 += s[--i];
                r1 += r[--j];
            } else if (i>0 && abs(i-1-j)<=K && B[j][i]==mx) {
                s1 += s[--i];
                r1 += '-';
            } else if (j>0 && abs(i-j+1)<=K && C[j][i]==mx) {
                s1 += '-';
                r1 += r[--j];
            } else {
                throw runtime_error("回溯路径超出k-band范围");
            }
            mx = max({A[j][i], B[j][i], C[j][i]});
        }

        reverse(s1.begin(), s1.end());
        reverse(r1.begin(), r1.end());

        // 写入FASTA格式文件
        ofstream out("output.fasta");
        auto write_aligned = [&](const string& header, const string& seq) {
            out << ">" << header << "_aligned\n";
            for (size_t i=0; i<seq.size(); i+=80) {
                out << seq.substr(i, 80) << '\n';
            }
        };

        write_aligned(records[0].header, s1);
        write_aligned(records[1].header, r1);

    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }
    return 0;
}
