/*
 --入力例--
 3 7 3
 1 4 9
 
 --出力例--
 3
 
 --なぜ--
 1 4 9から作れる7の倍数は119 441 994の3つ
 
 --標準入力--
 N B K
 c1 c2 .. ck
 
 --説明--
 数字c1,c2,..,ckのみを使うことで作れるN桁の正の整数のうち、
 Bの倍数であるものは何個あるか？
 答えを10^9+7で割ったあまりを出力せよ
 
 --小課題--
 １：N<=10000, B<=30
 ２：B<=30
 ３：追加の制約はない
 */


/*
 --解法(小課題3)--
 O(B^2logN)で解く方法がある。
 以下のような遷移。
 
 dp[2][(10^1×j+k) mod B] += dp[1][j] × dp[1][k]
 dp[4][(10^2×j+k) mod B] += dp[2][j] × dp[2][k]
 dp[8][(10^4×j+k) mod B] += dp[4][j] × dp[4][k]
 
 難しいので、「きたまさ法」で要検索。
 この問題はトップクラスに難しい。
 1日かけて理解する必要があるかも
 */

//解法(小課題2)

#include <iostream>
using namespace std;

long long modpow(long long a, long long b, long long m) {
    long long p = 1, q = a;
    for (int i = 0; i < 63; i++) {
        if ((b & (1LL << i)) != 0) {
            p *= q;
            p %= m;
        }
    }
    return p;
}

const long long mod = 1000000007;

//入力
long long N, B, K;
long long C[11];

long long power10[64];
long long DP[64][1009];
long long Answer[64][1009];

int main() {
    cin >> N >> B >> K;
    for (int i = 1; i <= K; i++) cin >> C[i];
    
    //前計算
    for (int i = 0; i <= 62; i++) {
        //LLとは64-bit literalのこと：(long long)10と同義
        power10[i] = modpow(10LL, (1LL << i), B);
    }
    
    //dp[1][i]を求める
    for (int i = 1; i <= K; i++) {
        DP[0][C[i] % B] += 1;
    }
    
    //前計算
    for (int i = 0; i < 62; i++) {
        for (int j = 0; j < B; j++) {
            for (int k = 0; k < B; k++) {
                int nex = (j * power10[i] + k) % B;
                DP[i + 1][nex] += DP[i][j] * DP[i][k];
                DP[i + 1][nex] %= mod;
            }
        }
    }
    
    //繰り返し二乗法　dp[N][i]を求める
    Answer[0][0] = 1;
    or (int i = 0; i < 62; i++) {
        if ((N & (1LL << i)) != 0LL) {
            for (int j = 0; j < B; j++) {
                for (int k = 0; k < B; k++) {
                    int nex = (j * power10[i] + k) % B;
                    Answer[i + 1][nex] += Answer[i][j] * Answer[i][k];
                    Answer[i + 1][nex] %= mod;
                }
            }
        }
        else {
            for (int j = 0; j < B; j++) Answer[i + 1][j] = Answer[i][j];
        }
    }
    
    cout << Answer[62][0] << endl;
    return 0;
    
    //正直復習しないと忘れるし何をしているのかの把握が難しい
}
