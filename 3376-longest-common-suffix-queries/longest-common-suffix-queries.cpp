#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    int children[26];
    int bestIdx; // best wordsContainer index for this node
    TrieNode() {
        fill(children, children + 26, -1);
        bestIdx = -1;
    }
};

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        vector<TrieNode> trie;
        trie.reserve(500005);
        trie.emplace_back(); // root node

        auto isBetter = [&](int newIdx, int curIdx, const vector<string>& wc) -> bool {
            if (curIdx == -1) return true;
            int newLen = wc[newIdx].size();
            int curLen = wc[curIdx].size();
            // prefer shorter length, then earlier index
            return newLen < curLen || (newLen == curLen && newIdx < curIdx);
        };

        // Insert reversed wordsContainer strings into trie
        for (int i = 0; i < (int)wordsContainer.size(); i++) {
            const string& w = wordsContainer[i];
            int node = 0;

            // Update root with this word
            if (isBetter(i, trie[0].bestIdx, wordsContainer))
                trie[0].bestIdx = i;

            for (int j = w.size() - 1; j >= 0; j--) {
                int c = w[j] - 'a';
                if (trie[node].children[c] == -1) {
                    trie[node].children[c] = trie.size();
                    trie.emplace_back();
                }
                node = trie[node].children[c];

                // Precompute best answer at this node
                if (isBetter(i, trie[node].bestIdx, wordsContainer))
                    trie[node].bestIdx = i;
            }
        }

        // Answer each query
        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (const string& q : wordsQuery) {
            int node = 0;
            int lastValid = trie[0].bestIdx; // fallback: empty suffix

            for (int j = q.size() - 1; j >= 0; j--) {
                int c = q[j] - 'a';
                if (trie[node].children[c] == -1) break;
                node = trie[node].children[c];
                lastValid = trie[node].bestIdx;
            }

            ans.push_back(lastValid);
        }

        return ans;
    }
};