class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.size();

        vector<int> partner(n, -1);
        stack<int> st;

        // Find the matching bracket for each parenthesis.
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                st.push(i);
            } 
            else if (s[i] == ')') {
                int j = st.top();
                st.pop();

                partner[i] = j;
                partner[j] = i;
            }
        }

        string answer;

        // +1 means forward; -1 means backward.
        for (int i = 0, direction = 1;
             i >= 0 && i < n;
             i += direction) {

            if (s[i] == '(' || s[i] == ')') {
                i = partner[i];
                direction = -direction;
            } 
            else {
                answer += s[i];
            }
        }

        return answer;
    }
};