
class Solution {
public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Step 1: Iterative DFS
        vector<int> parent(n, -1), depth(n, 0);
        vector<int> order;
        vector<int> st = {0};

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        // Step 2: Calculate subtree sizes
        vector<int> sz(n, 1);

        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            sz[parent[u]] += sz[u];
        }

        // Step 3: Euler Tour positions
        vector<int> tin(n), tout(n);

        for (int i = 0; i < n; i++) {
            tin[order[i]] = i;
        }

        for (int u = 0; u < n; u++) {
            tout[u] = tin[u] + sz[u] - 1;
        }

        // Step 4: Binary Lifting
        int LOG = 17;
        vector<vector<int>> up(LOG, vector<int>(n, 0));

        for (int u = 0; u < n; u++) {
            up[0][u] = (u == 0 ? 0 : parent[u]);
        }

        for (int j = 1; j < LOG; j++) {
            for (int u = 0; u < n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j))
                    u = up[j][u];
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return parent[u];
        };

        // Step 5: Fenwick Tree with XOR
        vector<int> bit(n + 2, 0);

        auto add = [&](int idx, int val) {
            while (idx <= n + 1) {
                bit[idx] ^= val;
                idx += idx & -idx;
            }
        };

        auto rangeUpdate = [&](int l, int r, int val) {
            add(l + 1, val);
            add(r + 2, val);
        };

        auto getPrefix = [&](int idx) {
            int ans = 0;

            while (idx > 0) {
                ans ^= bit[idx];
                idx -= idx & -idx;
            }

            return ans;
        };

        auto getMask = [&](int u) {
            return getPrefix(tin[u] + 1);
        };

        // Step 6: Initialize character masks
        auto mask = [&](char c) {
            return 1 << (c - 'a');
        };

        for (int u = 0; u < n; u++) {
            rangeUpdate(tin[u], tout[u], mask(s[u]));
        }

        // Step 7: Process queries
        vector<bool> ans;

        for (string &q : queries) {
            string type, x, y;
            stringstream ss(q);

            ss >> type >> x >> y;

            int u = stoi(x);

            if (type == "update") {
                char c = y[0];

                int change = mask(s[u]) ^ mask(c);

                rangeUpdate(tin[u], tout[u], change);

                s[u] = c;
            }
            else {
                int v = stoi(y);

                int w = lca(u, v);

                int pathMask =
                    getMask(u) ^
                    getMask(v) ^
                    mask(s[w]);

                // At most one odd-frequency character
                ans.push_back(
                    (pathMask & (pathMask - 1)) == 0
                );
            }
        }

        return ans;
    }
};
