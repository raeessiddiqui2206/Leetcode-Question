class Solution {
public:
    void findNewParents(int u, vector<vector<int>>& adj, string& s, vector<int>& lastSeen, vector<int>& newParent) {
        int charIdx = s[u] - 'a';
        int prevAncestor = lastSeen[charIdx];
        
        // Agar same character wala ancestor mila, toh parent update karo
        if (prevAncestor != -1) {
            newParent[u] = prevAncestor;
        }
        
        // Current node ko is character ka latest ancestor banao
        lastSeen[charIdx] = u;
        
        for (int v : adj[u]) {
            findNewParents(v, adj, s, lastSeen, newParent);
        }
        
        // Backtrack: purana ancestor restore karo
        lastSeen[charIdx] = prevAncestor;
    }

    int countSubtreeSize(int u, vector<vector<int>>& newAdj, vector<int>& ans) {
        int size = 1;
        for (int v : newAdj[u]) {
            size += countSubtreeSize(v, newAdj, ans);
        }
        return ans[u] = size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> lastSeen(26, -1);
        
        // Step 1: Naye parents nikalo
        findNewParents(0, adj, s, lastSeen, newParent);

        // Step 2: Updated tree banao aur subtree sizes count karo
        vector<vector<int>> newAdj(n);
        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 0);
        countSubtreeSize(0, newAdj, ans);
        
        return ans;
    }
};