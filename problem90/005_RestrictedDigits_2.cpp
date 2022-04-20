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
 --解法(小課題2)--
 解法(小課題1)におけるdpの繊維は行列の掛け算で表すことができる。
 a=[2 2 1]から b=[2 3 3]への遷移は以下の通り。
 [0 1 1] [2]   [2]
 [1 0 1] [1] = [3]
 [1 1 0] [1]   [3]
 
 dp[0][?]　→ dp[n][?]　は以下のように表される。
 [0 1 1]^n [1]   [dp[n][0]]
 [1 0 1]   [0] = [dp[n][1]]
 [1 1 0]   [0]   [dp[n][2]]
 
 B×B行列Aのn乗計算はA^1,A^2,..を前もって計算することで
 O(B^3logN)で求めることができる。
 
 */

//解法(小課題2)
#include <iostream>
using namespace std;

const long long mod = 1000000007;
const int MAX_N = 33;

struct Matrix {
    int sz;
    long long x[MAX_N][MAX_N];
}

//A×Bを求める
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    C.sz = A.cz;
    for (int i = 0; i < C.sz; i++) {
        for (int j = 0; j < C.sz; j++) {
            C.x[i][j] = 0;
        }
    }
    for (int i = 0; i < A.sz; i++) {
        for (int j = 0; j < A.sz; j++) {
            for (int k = 0; k < A.sz; k++) {
                C.x[i][k] += A.x[i][j] * B.x[i][k];
                C.x[i][k] %= mod;
            }
        }
    }
    return C;
}

//AのT乗を求める
Matrix powers(Matrix A, long long T) {
    Matrix E[64], F;
    E[0] = A;
    for (int i = 1; i < 62; i++) {
        E[i] = multiply(E[i - 1], E[i - 1]);
    }
    
    F.sz = E[0].sz;
    for (int i = 0; i < F.sz; i++) {
        for (int j = 0; j < F.sz; j++) {
            if (i == j) F.x[i][j] = 1;
            if (i != j) F.x[i][j] = 0;
        }
    }
    
    for (int i = 62; i >= 0; i--) {
        if ((T & (1LL << i)) != 0LL) {
            F = multiply(F, E[i]);
        }
    }
    return F;
}

long long N, K, B;
long long C[11];

int main() {
    cin >> N >> B >> K;
    for (int i = 1; i <= K; i++) {
        cin >> C[i];
    }
    
    //行列Aを求める
    Matrix A; A.sz = B;
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            A.x[i][j] = 0;
        }
    }
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < K; j++) {
            int nex = (i * 10 + C[j]) % B;
            A.x[i][nex] += 1;
        }
    }
    
    //行列累乗をする
    Matrix Z = powers(A, N);
    
    long long Answer = Z.x[0][0];
    cout << Answer << endl;
    return 0;
}



