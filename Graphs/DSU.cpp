int par[N], sz[N];
 
void init( int n )
{
    for ( int i = 1 ; i <= n ; i++)
        par[i] = i, sz[i] = 1;
}
 
 
int findparent( int u)
{
    if(par[u] == u)
        return u;
    return par[u] = findparent(par[u]);
}
 
bool is_con( int u , int v)
{
    return findparent(u) == findparent(v);
}
 
void con( int u , int v)
{
    // if u and v are connected return
    if(is_con(u,v))
        return;
    // else connect
    u = findparent(u);
    v = findparent(v);
    if(sz[u] < sz[v])
    {
        par[u] = v;
        sz[v] += sz[u];
    }
    else
    {
        par[v] = u;
        sz[u] += sz[v];
    }
}
