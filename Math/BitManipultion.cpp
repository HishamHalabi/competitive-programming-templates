

//taken from chat 8:04   6/30/25
long long rangeOR(long long L, long long R) {
    long long res = 0;
    for (int i = 63; i >= 0; --i) {
        long long mask = 1LL << i;
        if ((L & mask) != (R & mask)) {
            res |= (1LL << (i + 1)) - 1;
            break;
        } else {
            res |= (L & mask);
        }
    }
    return res;
}

//taken from chat 8:04   6/30/25
long long rangeAND(long long L, long long R) {
    int shift = 0;
    while (L < R) {
        L >>= 1;
        R >>= 1;
        shift++;
    }
    return L << shift;
}

//can be proved by induction
int XORtillN(int n) {
    if(n % 4 == 1) return 1;
    if(n % 4 == 2) return n+1;
    if(n % 4 == 3) return 0;
    return n;
}

int findRangeXOR(int l, int r){
    return XORtillN(l-1) ^ XORtillN(r);
}


void Set(int &mask , int bitIndx , int val){
  if (!val)
    mask = mask & ~(1LL << bitIndx);
  else
    mask = mask | (1LL << bitIndx);
}
void flib(int &mask , int bitIndx ){ // 1 >> 0  , 0>>1
       mask = mask ^ (1LL << bitIndx);
}
int Bit(int mask , int bitIndx){ //val[bit]
   return  (mask >> bitIndx) & 1LL == 1LL;
}
int invert(int mask){
    return ~mask;
}
void to_rmeber (){ 
    //don't  read this part cause it's from paid course
    /*
           1LL ,0 LL >> overflow
           lg2(x) >>  the indx of  last one on it and the int log of it
           __builtin_popcountll(num)  >> number of ones in number

           ShR
                  It's considered as division by power of 2s

                  A 	 		= 		5  (00101)
                  A>>1LL		= 		2 (00010)

                  B 	 		 = 		12(01100)
                  B>>2LL		= 		3 (00011)
        ShL
          It's considered as multiplying by power of 2s

               A 	 		= 		5  (00101)
               A<<1		= 		10 (01010)

              B 	 		 = 		12(001100)
              B<<2		= 		48 (110000)
     */

}
