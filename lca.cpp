const int N = 200005;
vector<int> tree[N], level(N);
int up[21][N];
void dfs(int src, int par, int lev)
{
    level[src] = lev;
    up[0][src] = par;
    for (auto ch : tree[src])
    {
        if (ch != par)
            dfs(ch, src, lev + 1);
    }
}
void preprocess(int n)
{
    dfs(1, -1, 0);
    for (int h = 1; (1 << h) <= n; h++)
    {
        for (int i = 1; i <= n; i++)
            up[h][i] = up[h - 1][up[h - 1][i]];
    }
}
int LCA(int x, int y)
{
    // calc diff -> lift diff ->if same then return else lift both
 
    if (level[x] < level[y])
        swap(x, y);
    int diff = level[x] - level[y];
    for (int i = 20; i >= 0; i--)
        if (diff & (1 << i))
            x = up[i][x];
    if (x == y)
        return y;
    // lift both
    for (int i = 20; i >= 0; i--)
    {
        if (up[i][x] != up[i][y])
        {
            x = up[i][x];
            y = up[i][y];
        }
    }
    return up[0][x];
}
void solve()
{
    int n;
    cin >> n;
    int q;
    cin >> q;
    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    preprocess(n);
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        int lca = LCA(a, b);
        int k = min(level[a], level[b]);
        cout << abs(level[a] - level[b]) + 2 * abs(level[lca] - k) << endl;//this finds the distance between two nodes
    }
}
