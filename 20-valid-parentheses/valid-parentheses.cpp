class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char ch : s) {

            // Opening brackets
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            }

            else {

                // Stack empty
                if (st.empty())
                    return false;

                // Matching check
                if (ch == ')' && st.top() != '(')
                    return false;

                if (ch == '}' && st.top() != '{')
                    return false;

                if (ch == ']' && st.top() != '[')
                    return false;

                st.pop();
            }
        }

        // All brackets matched?
        return st.empty();
    }
};