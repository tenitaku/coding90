/*
 --入力--
 N K
 S
 
 --入力例--
 7 3
 atcoder
 
 --出力例--
 acd
 
 --なぜ？--
 長さKのSの部分列のうち、辞書順で最小であるのがacdであるから。
 
 --制約--
 1<=K<=N<=100000
 Sは英小文字の身からなる長さNの文字列
 
 --考え方--
 「前選んだ文字の右にある文字の中で最左のもの」以降全部選び、K文字以上になること。
 ・・全探索だとO(|S|K)

 --O(1)で求める方法--
 以下のような配列c[i][j]を前計算する
 c[i][j]：i文字目の右にある文字jの中で最も左にあるもののインデックス
 
 --例--
 S="bacbcba"の場合
   b a c b c b a
 a 2 2 7 7 7 7 7
 b 1 4 4 4 6 6 -
 c 3 3 3 5 5 - -
 */

#include <iostream>
using namespace std;

string S;
int N, K;
int nex[100009][26];

int main() {
    cin >> N >> K;
    cin >> S;
    
    for (int i = 0; i < 26; i++) nex[S.size()][i] = S.size();
    for (int i = (int)S.size() - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            if ((int)(S[i] - 'a') == j) {
                nex[i][j] = i;
            }
            else {
                nex[i][j] = nex[i + 1][j];
            }
        }
    }
    
    string Answer = "";
    int CurrentPos = 0;
    for (int i = 1; i <= K; i++) {
        for (int j = 0; j < 26; j++) {
            int NexPos = nex[CurrentPos][j];
            int MaxPossibleLength = (int)(S.size() - NexPos - 1) + i;
            if (MaxPossibleLength >= K) {
                Answer += (char)('a' + j);
                CurrentPos = NexPos + 1;
                break;
            }
        }
    }
    
    cout << Answer << endl;
    return 0;
}
