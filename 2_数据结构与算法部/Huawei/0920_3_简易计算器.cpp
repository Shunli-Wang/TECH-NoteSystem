#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

const string SYNTAX = "<syntax-error>";
const string UNDE = "<undefined>";
const string OVER = "<overflow>";
const string UNDER = "<underflow>";

map<string, int> vals;

bool is_valid_variable_name(const string& input_str) {
    const string pattern = "^[a-zA-Z_][a-zA-Z0-9_]*$";
    return regex_match(input_str, regex(pattern));
}

int calculate(const string& s) {
    int n = s.size();
    vector<int> stack;
    char preSign = '+';
    int num = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] != ' ' && isdigit(s[i])) {
            num = num * 10 + s[i] - '0';
        }
        if (i == n - 1 || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            if (preSign == '+') {
                stack.push_back(num);
            } else if (preSign == '-') {
                stack.push_back(-num);
            } else if (preSign == '*') {
                stack.back() *= num;
            } else {
                stack.back() /= num;
            }
            preSign = s[i];
            num = 0;
        }
    }

    int result = 0;
    for (int num : stack) {
        result += num;
    }
    return result;
}

vector<string> split(const string& s) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    while (getline(iss, token, '+')) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    vector<string> inputs;
    string line;

    while (getline(cin, line)) {
        inputs.push_back(line);
    }

    for (const string& input : inputs) {
        if (input.substr(0, 3) == "let") {
            string tmp = input.substr(3);
            size_t equalsPos = tmp.find('=');
            if (equalsPos == string::npos) {
                cout << SYNTAX << endl;
                continue;
            }
            string k = tmp.substr(0, equalsPos);
            string v = tmp.substr(equalsPos + 1);
            k.erase(remove_if(k.begin(), k.end(), ::isspace), k.end());

            if (!is_valid_variable_name(k)) {
                cout << SYNTAX << endl;
                continue;
            }

            vector<string> res = split(v);
            bool valid = true;
            for (string& token : res) {
                if (vals.find(token) == vals.end()) {
                    cout << UNDE << endl;
                    valid = false;
                    break;
                }
                token = to_string(vals[token]);
            }

            if (valid) {
                int val = calculate(v);
                vals[k] = val;
            }
        } else if (input.substr(0, 3) == "out") {
            string v = input.substr(3, input.size() - 4);
            v.erase(remove_if(v.begin(), v.end(), ::isspace), v.end());

            if (vals.find(v) == vals.end()) {
                cout << UNDE << endl;
            } else {
                int val = vals[v];
                if (val >= numeric_limits<int>::min() && val <= numeric_limits<int>::max()) {
                    cout << val << endl;
                } else if (val < numeric_limits<int>::min()) {
                    cout << UNDER << endl;
                } else {
                    cout << OVER << endl;
                }
            }
        }
    }

    return 0;
}
