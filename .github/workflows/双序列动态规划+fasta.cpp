#include <bits/stdc++.h>
using namespace std;

#define gap 1
#define m 1
#define mis 2

struct FastaRecord {
    string header;
    string sequence;
};

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
        auto records = read_fasta("input.fasta");
        string s = records[0].sequence;
        string r = records[1].sequence;

        int ms = s.size(), mr = r.size();
        vector<vector<int>> A(mr+1, vector<int>(ms+1, 0));
        
        for (int i = 1; i <= ms; i++) A[0][i] = -gap * i;
        for (int j = 1; j <= mr; j++) A[j][0] = -gap * j;
        
        for (int i = 1; i <= ms; i++) {
            for (int j = 1; j <= mr; j++) {
                int rs = A[j-1][i-1] + p(s[i-1], r[j-1]);
                int sc = A[j][i-1] - gap;
                int rc = A[j-1][i] - gap;
                A[j][i] = max({rs, sc, rc});
            }
        }
        
        string s1, r1;
        int i = ms, j = mr;
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && A[j][i] == A[j-1][i-1] + p(s[i-1], r[j-1])) {
                s1 += s[--i];
                r1 += r[--j];
            } else if (j > 0 && A[j][i] == A[j-1][i] - gap) {
                s1 += '-';
                r1 += r[--j];
            } else {
                s1 += s[--i];
                r1 += '-';
            }
        }
        
        reverse(s1.begin(), s1.end());
        reverse(r1.begin(), r1.end());
        
        ofstream out("output.fasta");
        auto write_fasta = [&](const string& header, const string& seq) {
            out << ">" << header << "_aligned\n";
            for (size_t i = 0; i < seq.size(); i += 80) {
                out << seq.substr(i, 80) << "\n";
            }
        }; // 这里添加分号
        
        write_fasta(records[0].header, s1);
        write_fasta(records[1].header, r1);
        
    } catch (const exception& e) { // 修复try块闭合
        cerr << "错误: " << e.what() << endl;
        return 1;
    }
    return 0;
}
