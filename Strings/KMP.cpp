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


/*
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
