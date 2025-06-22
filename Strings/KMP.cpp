/*
    صل على محمد
    if (u == Abdel-Aziz Mostafa )  love u <3 ;
*/
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


#define F first
#define S second
#define all(v) v.begin(), v.end()

#define cnt(num)  __builtin_popcountll(num)


/* very very important for autmation to consider letter cases
 * pi  = i  >>  i is length so next trial are i+1
 * consider text +  "$"  +  patt
 */
const int N  = 3e5+4  , mod =1e9 +  7;

vector<int> prefiFunction(string pattern) {
    int n = pattern.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


void  KMP_Count(string text, string pattern) {
      string searchable =  pattern  +  + "$"  +  text ;
      vector<int> pi = prefiFunction(searchable);

      for (int i  =   pattern.size()   +1  ;  i  <  searchable.size() ; i++) {
               if   (pi[i] == pattern.size())   {
                        cout <<  i   -  pattern.size() +1  -  pattern.size() -1 <<endl;
               }
      }
}
/*
 * auto[i][c]  >> imagine u take some prefix that it's pi =  i     and u added letter c wht will be the New L
 */
auto compute_automaton(string s ) {
    s += '#';
    int n = s.size();
    vector<vector<int>> aut (n ,  vector < int  > (26)) ;
    vector<int> pi = prefiFunction(s);
    aut.assign(n, vector<int>(26));
    for (int i  = 0; i   < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
    return aut ;
}



int  n ;
string text , patt  ,res;
vector < vector  < int > > aut ;


int dp[20005][1005] ;
int solve(int i ,  int len)  {
       if (i == n) return   0 ;

       int &ret = dp[i][len] ;
       if (~ret)
             return ret;


       ret= 1 +  solve(i+1 , len) ;

       int nwLen =  aut[len][res[i]  - 'a'] ;
       if (nwLen >= patt.size())  return ret;
       return ret   =   min (ret   ,  solve(i+1 , nwLen) ) ;
}

signed main() {
       ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);


       while(cin  >>  text){
            cin >> patt ;

       res   =  patt  + "$" +  text ;


      //u can build aut on only patt cause aut only need max prefix   need to be calced for auto[i][c]  and we dont need to calc for aut[i>=lenOfPatt] >> ivalid case
       aut = compute_automaton(res) ;
       n   =  aut.size()  -1   ;

       memset(dp , -1 , sizeof  dp) ;
       //cout << n <<"\n";

         //af
         cout<<solve(   patt.size()  +1  ,   0 ) <<"\n";
     }



}

//////////////////////////////

int  n  ,  m  , L ;
string s1 , s2 , virus ;
vector  <vector  <int >> aut  ;

pair < int , int  >   dp[101][101][101] ;

//0 i+1  1 i+2 2 take both
pair < int,int >  solve(int i ,  int  j ,  int len)  {

    if (i == n ) return  {0 , 0} ;
    if (j == m)   return   {0 , 0} ;
    auto &ret =dp[i][j][len] ;
    if (~ret.F)  return ret;

    pair < int, int >  t1 = {solve(i+1 , j  , len).F , 0} ;
    pair < int, int > t2 = {solve(i , j +1 , len).F  , 1} ;
    if ((s1[i] != s2[j] ||  aut[len][s1[i]-'A'] >= L) ) return ret =max(t1,t2)   ;
    pair < int, int > t3 =  make_pair(1+solve(i+1 , j+1 , aut[len][s1[i]-'A']).F,  2) ;

    return ret = max(t1 , max(t2, t3)) ;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> s1 >> s2 >> virus ;

    n = s1.size() ,  m = s2.size()  ,  L=  virus.size() ;

    aut =  compute_automaton(virus) ;

    for (int i = 0 ; i  <n  ; ++i)
        for (int j = 0  ; j   < m ; ++j)
            for (int  l = 0 ;  l  < L ; ++l)dp[i][j][l].F = -1;



    string ans = "";
    int  i = 0  ,   j = 0  ,len = 0 ;
    while(i!=n and  j!=m) {
        auto ret = solve( i   ,j   ,len)  ;
       // cout<<ret.F<<"\n";

        if (ret.S == 0 )  {
            i++   ;
        }else if (ret.S == 1)  {
            j ++ ;
        }else  {
            ans+=s1[i] ;
            len =aut[len][s1[i]-'A'];
            i++ , j++ ;
        }
    }

    if (ans.empty())cout<<0<<"\n";
    else cout<<ans<<"\n";



}

