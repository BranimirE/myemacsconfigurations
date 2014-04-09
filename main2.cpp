#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 100000
#define MOD 1000000009
typedef long long int Number;
int v[MAX + 5];
int c[100];
int n;
int bags;
int mod(int a, int b){
  int ans = a % b;
  if(ans < 0)
    ans += b;
  return ans;
}
int dp[101][101];
Number f[MAX + 5];
int mp[1000][10000];
Number pow(Number b, Number e){
  if(e == 0) 
    return 1LL;
  if(b == 0) return 0;
  if((b < 1000) && (e < 10000) && (mp[b][e] =!-1))
    return mp[b][e];
  Number ans = pow(b, (e >> 1LL));
  ans = ans * ans;
  if(ans >= MOD)
    ans %= MOD;
  if(e & 1){ 
    ans = ans * b;
    if(ans >= MOD) ans %= MOD;
  }
  if(b < 1000 && e < 10000)
    mp[b][e] = ans;
  return ans;
}
int comb[17000][17000];
int C(int n, int k){
  if(n < 17000 && k < 17000){
    int & ans = comb[n][k];
    if(ans != -1) return ans;
    if(comb[n][n - k] != -1) return ans = comb[n][n - k];
    ans = (f[n] * pow((f[k] * f[n-k]) % MOD , MOD - 2)) % MOD;
    return ans;
  }
  return (f[n] * pow((f[k] * f[n-k]) % MOD , MOD - 2)) % MOD;
}
int mul[101][101];
/*
Number solve(int pos, int obj){
  if(pos == bags) 
    return Number(obj == 0);
  Number &ans = dp[pos][obj];
  if(ans != -1) 
    return ans;
  ans = solve(pos + 1, obj);
  for(int modu = 0; modu < bags; modu++){
    Number mm = mod(obj - modu, bags);
    ans = (ans + ((solve(pos + 1, mm) * mul[pos][modu]) % MOD)) % MOD;
  }
  return ans;
  }*/
int solve2(){
  dp[bags][0] = 1;
  for(int i = 1; i < bags; i++)
    dp[bags][i] = 0;
  for(int pos = bags - 1; pos >= 0; pos--)
    for(int obj = 0; obj < bags; obj++){
      dp[pos][obj] = dp[pos + 1][obj];
      for(int modu = 0; modu < bags; modu++){
        int mm = mod(obj - modu, bags);
        Number tmp = (Number)dp[pos + 1][mm]*(Number)mul[pos][modu];
        if(tmp > MOD) tmp %= MOD;
        dp[pos][obj] += (int) tmp;
        if(dp[pos][obj] >= MOD)
          dp[pos][obj] -= MOD;
      }
    }
  return dp[0][0];
}
int main(){
  int t;
  int q;
  f[0] = 1;
  //clock_t ini, fin;
  clock_t Tini = clock();
  memset(comb, -1, sizeof(comb));
  memset(mp, -1, sizeof(mp));
  for(int i = 1; i <= MAX; i++)
    f[i] = (i * f[i-1]) % MOD;
  scanf("%d", &t);
  while(t--){
    scanf("%d%d", &n, &q);
      
    for(int i = 0; i < n; i++)
      scanf("%d", &v[i]);
    
    while(q--){
      scanf("%d", &bags);
    
      //ini = clock();      
      memset(c, 0, sizeof(c));
      for(int i = 0; i < n; i++)
        c[mod(v[i], bags)]++; 
      memset(mul, 0, sizeof(mul));
      vector<int> cc[bags][bags];
      for(int pos = 0; pos < bags; pos++){
        for(int cant = 1; cant <= c[pos]; cant++){
          int elem = pos * cant % bags;
          cc[pos][elem].push_back(cant);
          //mul[pos][elem] += C(c[pos], cant);
          //if(mul[pos][elem] >= MOD)
          //mul[pos][elem] -= MOD;
        }
        int N = c[pos];
        //cout << "pos "<<pos << endl;
        for(int elem = 0; elem < bags; elem++){
          if(cc[pos][elem].size() > 1)
          cout << "elem = " << elem << " : " << cc[pos][elem].size()  << endl;
          
          for(int i = 0; i < cc[pos][elem].size(); i++){
            int K = cc[pos][elem][i];
            //cout << K << " ";
            
            mul[pos][elem] = (mul[pos][elem] + pow((f[K] * f[N - K]) % MOD, MOD - 2)) % MOD;
          }
          // cout << endl;
          mul[pos][elem] = ((Number)mul[pos][elem] * f[c[pos]]) % MOD;
        }
      }
      

      //fin = clock();
      //cout << "tiempo de ejecucion de preproceso = " << (double(fin - ini) / CLOCKS_PER_SEC) << endl;
      //ini = clock();
      memset(dp, -1, sizeof(dp));
      printf("%d\n", solve2());
      //fin = clock();
      //cout << "tiempo de ejecucion de solucion = " << (double(fin - ini) / CLOCKS_PER_SEC) << endl;
    }
  }
  clock_t Tfin = clock();
  cout << "TIEMPO DE EJECUCION :" << (double(Tfin - Tini) / CLOCKS_PER_SEC) << endl;
  return 0;
}
