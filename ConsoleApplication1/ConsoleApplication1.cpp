#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string addBinary(string a, string b) {
    string result = "";
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }
        carry = sum / 2;
        sum = sum % 2;
        result = to_string(sum) + result;
    }
    return result;
}

int main() {
    ifstream input_file("result2_<Мейлис_Аразмадов>_<4>.csv");
    if (!input_file.is_open()) {
        cerr << "Error: failed to open input file" << endl;
        return 1;
    }

    vector<vector<string>> data;

    string line;
    while (getline(input_file, line)) {
        vector<string> row;
        size_t pos = 0;
        while (pos < line.size()) {
            size_t next_pos = line.find(',', pos);
            if (next_pos == string::npos) {
                next_pos = line.size();
            }
            row.push_back(line.substr(pos, next_pos - pos));
            pos = next_pos + 1;
        }
        data.push_back(row);
    }

    input_file.close();

    vector<vector<string>> result_data;

    for (const auto& row : data) {
        if (row.size() != 2) {
            vector<string> result_row = row;
            result_row.push_back("error");
            result_data.push_back(result_row);
            continue;
        }

        string a = row[0];
        string b = row[1];
        string sum = addBinary(a, b);

        vector<string> result_row = row;
        result_row.push_back(sum);
        result_data.push_back(result_row);
    }

    ofstream output_file("result2_<Мейлис_Аразмадов>_<4>.csv,");
    if (!output_file.is_open()) {
        cerr << "Error: failed to open output file" << endl;
        return 1;
    }

    for (const auto& row : result_data) {
        for (size_t i = 0; i < row.size(); i++) {
            output_file << row[i];
            if (i < row.size() - 1) {
                output_file << ",";
            }
        }
        output_file << endl;
    }

    output_file.close();

    return 0;
}