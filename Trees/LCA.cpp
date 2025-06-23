/*
   صل عل محمد

  دايما احلم ربنا المنان

*/
#include<bits/stdc++.h>
using namespace std  ;

#define int long long //TLE
#define F first
#define S second
///////////////////////////////
pre  :  n * log
quey  log
////////////////////////
const int N    = 3e5+7 , mxlog = 20 ;

vector<int > g[N]  ;
int dp[N][mxlog+5]   , depth[N] , n  ;

void dfs (int nd  , int par){
        for (auto &ch  : g[nd]) {
                  if(ch ==par)
                         continue ;
                  depth[ch]  =  depth[nd]+1 ;
                  dp[ch][0] = nd;
                  dfs(ch , nd) ;
        }
}


int lca (int  u ,  int v) {  // O(logn)

        if (depth[u]   < depth[v])
                  swap( u , v) ;

        for (int  k  =mxlog ; k>=0 ; k--){
                  if (dp[u][k]!=-1 and  depth[dp[u][k]] >=depth[v]){
                           u =  dp[u][k]  ;
                  }
        }

        if (u == v)
               return   u  ;


        for (int  k  =  mxlog ; k>=0 ; k--){
                  if (dp[u][k]!=dp[v][k]){
                           u =dp[u][k] ;
                           v =dp[v][k];
                  }
        }

        return dp[u][0] ;
}

void pre_lca(int root) {
         for (int  i = 1 ; i  <=n ; ++i){
                    for (int k =    0 ; k<=mxlog ; ++k )
                             dp[i][k] = -1  ;
         }

         depth[root] =   0 ;

         dfs(root ,  -1) ;

          for (int  k =1 ; k <=mxlog ; ++k){
                    for (int u = 1 ; u<=n ; ++u){
                             dp[u][k]  = (dp[u][k-1]==-1)  ?  -1  :  dp[dp[u][k-1]][k-1] ;
                    }
          }


}

int dis ( int u  , int v)  {
           int  l  =  lca(u , v)  ;
           return depth[u]  +  depth[v]  -  2*depth[l] ;
}


int kth_par(int  u  , int x)  {
       for (int k =  mxlog ;   k>= 0 ; k--){
                if ((1<<k)  <=x ){
                          u =  dp[u][k] ;
                          x-=1<<k  ;
                          if ( u== -1)
                                return  u ;
                }
        }
        return  u  ;
}

void lets_start_as_we_never_failed()   {


          cin >> n ;

          for (int  i = 0 ; i <= n ; ++i)
                   g[i].clear() ; 


          for (int  i   = 0 ; i+1 < n ;  ++i){
                    int u  , v;
                    cin >> u >>v;
                    g[u] .push_back(v) ;
                    g[v].push_back(u) ;
          }

          pre_lca(1);




}


signed main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);      cout.tie(0);


    int tc =1;
    cin>>tc;

    while(tc--)
        lets_start_as_we_never_failed();

}
///////////////////////////////////////
pre : n*log 
query :  1
/////////////////////////////////////////////
/*
   صل عل محمد

  دايما احلم ربنا المنان

*/
#include<bits/stdc++.h>
using namespace std  ;

#define int long long //TLE
#define F first
#define S second


const int N =  3e5+7 , mxlog=20  ;



int indx   = -1 ;
vector <int > g[N]  ;
int st[N][mxlog+5] , lg[N]   ,  E[N]  , fst[N]  , n   ;

int calc (int v1 , int v2){
      if (fst[v1]  <=fst[v2])
            return v1;
      return v2;
}


int   mi_query(int  l , int r ){
       int  k  =lg[r-l+1] ;
       return calc(st[l][k]  , st[r-(1<<k)+1][k]) ;
}



void euler  (int nd  , int par) {

        E[++indx]  =  nd ;
        fst[nd]  =  indx ;
        for (auto &ch  :  g[nd]) {
                 if (ch ==par)
                        continue ;
                 euler(ch , nd)  ;
                 E[++indx]   =  nd ;
        }
}

void pre   ( int root =1){
       indx =-1 ;

       euler(root ,-1) ;

       int len =  2* n -1  ;

       lg[1] =   0 ;
       for (int  i =   0 ; i  <len ;  ++i){
                 st[i][0]  =  E[i] ;
                 if (i  >=2)
                        lg[i]  =lg[i/2]+1;
       }
       lg[len]  = lg[len/2]+1   ; 
       lg[2*n]   =  lg[n]+1;

       for (int k =1 ;  k  <=  mxlog ;  ++k){
                for (int  i  =0 ;  i  + (1 << k) -1  < len  ; ++i){
                           st[i][k]  = calc(st[i][k-1] , st[i +(1 << k-1)][k-1]) ;
                }
       }


}
int lca  (int u  ,int v)  {
     int L  = fst[u]  , R=  fst[v]   ;
     if ( L > R)
          swap( L ,R)  ;
     return mi_query(L , R)  ;


}

void lets_start_as_we_never_failed()   {


          cin >> n ;

        for (int  i = 0 ; i <= n ; ++i)
                   g[i].clear() ; 


          for (int  u   = 0 ; u < n ;  ++u){
                    int  m  ;
                    cin >> m ;

                    for (int i = 0 ; i  <  m ; ++i)
                    {
                             int  v;
                             cin >> v;
                             g[u] .push_back(v) ;
                             g[v].push_back(u);
                    }
          }

          pre(1);


          int q;
          cin >>q;

          while(q-- ) {
                   int u ,  v;
                   cin  >> u >>v;

                   cout<<lca(u  ,v ) <<"\n";
          }

}


signed main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);      cout.tie(0);


    int tc =1;
    //cin>>tc;

    while(tc--)
        lets_start_as_we_never_failed();

}

