/*
 ＜問題＞
 入力 Nに対し、長さNの正しいカッコ列を全て辞書順に改行区切りで出力する
 例
 入力：2→出力：()
 入力：4→出力：(())改行()()
 
 ＜bit全探索＞
 長さがNで'('と')'の二種類の文字から構成される。よって、長さがNとすると最大2^N通り
 for文：N重ループ
 bit全探索を使う：O(2^N×N)で問題を解ける
 i=0..2^N-1でループ
 二進数表記で0の時'('、1の時')'とする
 例
 000:(((、111：)))
 N=3の時、000から111まで調べる
 
 ＜正しい括弧列の判定＞
 以下の２条件を満たす。
 ・ ( と ) の数が同じ
 ・全ての1<=i<=Nについて、左からi文字目までの時点で ( の数が ) 以上である
 →　(の数 - )の数　を累積的に計算することでO(N)で判定できる。
 */

#include <iostream>
#include <string>
using namespace std;

bool hantei(string S) {
    int dep = 0;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == '(') dep += 1;
        if (S[i] == ')') dep -= 1;
        if (dep < 0) return false;
    }
    // ( の数が ) より少ない
    if (dep == 0) return true;
    // ( の数が ) と同じ
    return false
    // ( の数が ) より最終的に多い
}

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < (1 << N); i++) {
        string Candidate = "";
        for (int j = N - 1; j >= 0; j--) {
            //以下ifの判定文はiのjビット目が0であるための条件：頻出！
            if ((i & (i << j)) == 0) {
                Candidate += "(";
            }
            else {
                Candidate += ")";
            }
        }
        bool I = hantei(Candidate);
        if (I == true) cout << Candidate << endl;
    }
    return 0;
}
