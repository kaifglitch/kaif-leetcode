class Solution {
public:
        struct Node {
        int prod = 1;
        int cnt[5] = {};
    };

    int mod;
    vector<Node> tree;

    Node merge(Node left, Node right) {

        Node res;


        res.prod = (left.prod * right.prod) % mod;


        for (int r = 0; r < mod; r++) {
            res.cnt[r] += left.cnt[r];
        }

        for (int r = 0; r < mod; r++) {

            int newRem = (left.prod * r) % mod;

            res.cnt[newRem] += right.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {

        if (l == r) {

            int val = nums[l] % mod;

            tree[node].prod = val;
            tree[node].cnt[val] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, int value) {

        if (l == r) {

            int val = value % mod;

            tree[node].prod = val;

            for (int i = 0; i < 5; i++) {
                tree[node].cnt[i] = 0;
            }

            tree[node].cnt[val] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, value);
        }
        else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }

        tree[node] = merge(tree[node * 2],
                           tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {

        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
         mod = k;

        int n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
        
    }
};