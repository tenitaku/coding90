/*
 --問題--
 N個のクラスがある。
 番号iのクラスはレーティングAiの生徒対象。
 番号j(1~Q)の生徒のレーティングはBj。
 生徒の不満度を以下のように定義。
 |対象レーティング - 自分のレーティング|
 不満度として考えられる最小値を求めよ。
 
 --入力--
 N
 A1...An
 Q
 B1
 .
 .
 .
 BQ
 
 --入力例--
 4
 4000 4400 5000 3200
 3
 3312
 2992
 4229
 
 --出力--
 j=1..Qそれぞれについて、標準出力に答えを1行ずつ、総計Q行に出力
 
 --出力例--
 112：3312に対して、3200との差の絶対値が一番小さい
 208：2992に対して、3220との差の絶対値が一番小さい
 171：4229に対して、4400との差の絶対値が一番小さい
 
 --制約--
 ・1<=N<=300000
 ・1<=Q<=300000
 ・0<=Ai<=10^9
 ・0<=Bj<=10^9
 ・入力は全て整数
 
 --解法--
 ソートして二分探索する。
 std::sortを用いてO(NlogN)で計算することができる。
 
 自分の最適なクラスは以下のいずれか
 ・自分以上の対象レーティングのうちレーティング最小のクラス
 ・その一個下のクラス
 ここから２分探索をしてO(logN)で計算する
 std::lower_boundを使う。
 */

#include <iostream>
#include <algorithm>
//多くの数学の関数が使えるようになる
#include <cmath>
using namespace std;

const int INF = 2000000000;
int N;
int A[300009];
int Q;
int B[300009];

int main() {
    //入力
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
    cin >> Q;
    for (int i = 1; i <= Q; i++) cin >> B[j];
    
    //sorting
    sort(A + 1, A + N + 1);
    
    //binary search
    for (int i = 1; i <= Q; i++) {
        //lower_bound(first, last, key)：firstからlastの中でkey以上の要素のうち最小の要素のインデックス
        //upper_bound(first, last, key)：firstからlastの中でkeyより大きい要素のうち最小の要素のインデックス
        int pos1 = lower_bound(A + 1, A + N + 1, B[i]) - A;
        int Diff1 = INF, Diff2 = INF;
        //absは絶対値
        if (pos1 <= N) Diff1 = abs(B[i] - A[pos1]);
        if (pos1 >= 2) Diff2 = abs(B[i] - A[pos1 - 1]);
        cout << min(Diff1, Diff2) << endl;
    }
    return 0;
}




