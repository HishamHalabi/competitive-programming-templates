  
long long intSqrt(long long n) {
    if (n == 0 || n == 1) return n;  // Base cases

    long long low = 0, high = n, ans = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (mid * mid == n) {
            return mid;  // Exact square root
        } else if (mid * mid < n) {
            low = mid + 1;
            ans = mid;  // Closest square root so far
        } else {
            high = mid - 1;
        }
    }
    
    return ans;  // Return the integer square root

///////////////////////////divisors part//////////////////////////////////////////////
vector<int> p;
void  prime_fact(int n){         
          p.clear() ;

          while (n%2 == 0){
                    p.push_back(2);   n/=2;
          }

          for (int i = 3; i <= sqrt(n); i = i+2){
                     while (n%i == 0){
                                p.push_back(i);
                                n = n/i;
                     }
         }
         if (n > 2) p.push_back(n);
         sort(p.begin() , p.end()) ;
}
////////////////////////////////////////////prime factors using preprocessing with sieve O ( cntprimes )  , divisors O(cnt divs)
const int MAX_PRE = 1e6+10;
std::vector<int> spf(MAX_PRE + 1);
const int N  =  1e6+1 ;
vector  <int >freq(N) , ans(N , -1);
vector  <vector < int >  > Divs(N)  , primes (N) ;
 
void sieve() {
    for (int i = 2; i <= MAX_PRE; i++) {
        spf[i] = i;
    }
    for (int i = 2; i * i <= MAX_PRE; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAX_PRE; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}
// get prims at O (n of primes with above prepr)
std::vector<int> getPrimeFactors(int n) {
    std::vector<int> primeFactors;
    while (n != 1) {
        primeFactors.push_back(spf[n]);
        n /= spf[n];
    }
    return primeFactors;
}
 
vector<pair<int,int> > val;
vector<int>  divisors;
 
void build(int idx , int cur){
          if (idx==val.size()){
                  divisors.push_back(cur);
                  return  ;
          }
 
          build(idx+1, cur);
          for (int i =1 ; i <=val[idx].S ; ++i){
                   cur*=val[idx].F;
                   build(idx+1 ,cur);
          }
 
}
void  build_divs(int num){          //generate divs in divsiors time
 
              divisors.clear();
              val.clear();
 
              vector <int>  p =  getPrimeFactors(num) ;
              for (int i = 0 ;  i<p.size() ; ++i){
                       int cnt  =1;
                       while(i+1 < p.size() and p[i]==p[i+1] ){
                               i++;
                               cnt++;
                       }
                       val.push_back({p[i] ,cnt});
              }
              build(0 , 1);
}
 
 
 
//////////////////////////////////////////////////////////////////
 eculiden theorem 
 gcd(a,b) = gcd(max(a,b)%min(a,b) , min(a,b) ) 

exteded eculiden 
 if gcd(a,b)  = g always ther's some x , y (int and maybe neg )   >> a.x + b.y  =g 

int  lcm(int a, int b){
             return a/__gcd(a,b)*b;
}
int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
The recursive function above returns the GCD and the values of coefficients to x and y (which are passed by reference to the function).
