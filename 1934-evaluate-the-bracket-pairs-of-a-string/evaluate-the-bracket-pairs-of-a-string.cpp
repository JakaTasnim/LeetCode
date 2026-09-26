class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> values;

        for (const auto& item : knowledge) {
            values[item[0]] = item[1];
        }

        string answer;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] != '(') {
                answer += s[i];
            } else {
                string key;
                ++i;  // Skip '('.

                while (s[i] != ')') {
                    key += s[i];
                    ++i;
                }

                auto it = values.find(key);

                if (it != values.end()) {
                    answer += it->second;
                } else {
                    answer += '?';
                }

                // i is at ')'; the for loop moves past it.
            }
        }

        return answer;
    }
};