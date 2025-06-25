
int m=1e9+7,mod=m , p1 =19 ,  p2= 17;


int sub(int a , int b   ){
       return (a%mod - b%mod + mod)%mod;
}

vector<int > pw1(N) , pw2(N) ;

struct Hashing {
        vector<pair<int,int> >Hash , re_Hash ;


        int n  ;
        Hashing(string x){                 //zero based

         //   l ....r    << p2 p1 p0

                n=x.size();
                Hash.resize(2*n);
                re_Hash.resize(2*n) ;


                pw1[0]   = 1;
                pw2[0]  = 1;

                for (int i = 0 ; i <n ; ++i){
                        Hash[i].F=Hash[i].S =  (x[i]-'0') ;
                        if (i){
                                Hash[i].F +=  Hash[i-1].F*p1 ;
                                Hash[i].S +=  Hash[i-1].S*p2 ;
                                 pw1[i] = (pw1[i-1] * p1)%mod ;
                                 pw2[i] =  (pw2[i-1]  * p2)%mod;
                        }
                        Hash[i].F%=mod;
                        Hash[i].S%=mod;



                }

                pw1[n]  = (pw1[n-1] *p1)%mod;
                pw2[n]  = (pw2[n-1] *p2)%mod;

                for (int i = n-1 ; i >=0 ; --i){       //  p0 p1 p2
                        re_Hash[i].F =re_Hash[i].S =  x[i]-'0';
                        if (i!=n-1){
                                re_Hash[i].F +=re_Hash[i+1].F * p1;
                                re_Hash[i].S +=re_Hash[i+1].S *p2;

                        }
                        re_Hash[i].F %=mod;
                        re_Hash[i].S%=mod;
                }
        }

        int power(int a, int b){
        if(b < 0) return 1;
         int res = 1;
         while(b){
                  if(b & 1) res = res * a % mod;
                  a = a * a % mod;
                  b >>= 1;
         }
         return res;
}


        pair<int ,int>  calc_hash(int l  , int r) //zero based
{
                pair<int ,int>  ans  = Hash[r];

                if (l){
                    ans.F = sub(ans.F ,  Hash[l-1].F*pw1[r-l+1]) ;
                    ans.S = sub(ans.S ,  Hash[l-1].S*pw2[r-l+1]) ;;
                }
                    return ans;
}
        pair<int,int>  calc_reversed_hash(int l , int r){

                pair<int,int>  ans  = re_Hash[l] ;

                if (r!=n-1){
                        ans.F=sub(ans.F , re_Hash[r+1].F*pw1[r-l+1]) ;
                        ans.S=sub(ans.S , re_Hash[r+1].S*pw2[r-l+1]) ;
                }
                return ans ;

        }
        bool palindrom (int  l , int r){
                    return calc_hash(l,r) ==  calc_reversed_hash(l,r)  ;

        }

};


