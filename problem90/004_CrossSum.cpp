/*
 ＜問題＞
 ・入力
 4(H) 4(W)
 3(A(1,1)) 1 4 1(A(1,W))
 5         9 2 6
 5         3 5 8
 9(A(H,1)) 7 9 3(A(h,w))
 
 ・出力
 28 28 25 26
 39 33 40 34
 38 36 36 31
 41 41 39 43
 
 行と列の合計値を返す：(1,1)=3+1+4+1+5+5+9=28
 
 ＜制約＞
 ・2<=H,W<=2000
 ・1<=A(i,j)<=99
 ・入力は全て整数
 
 ＜解法＞
 同じ行、列であるマスの個数：H+W-1
 合計するときの計算量O(H+W)
 HW個のマス全て＝O(HW(H+W))となり、計算が膨大に。
 
 ↓どうするか？
 
 行と列の和をそれぞれ求め(前計算)、そこからA(i,j)の値を引く
 すると、O(1)で求めることができる。（包除原理）
 i行目の整数合計　Rowi
 j列目の整数合計　Columnj
 */

#include <iostream>
using namespace std;

//特定のコードに対する警告をオフにする
#pragma warning (disable: 4996)

int H, W;
int A[2009][2009];
int Row[2009], Column[2009];
int Answer[2009][2009];

int main() {
    //入力
    cin >> H >> W;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            //%dは十進数、データを格納する
            scanf("%d", &A[i][j]);
        }
    }
    
    //前計算
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; J++) {
            Row[i] += A[i][j];
            Column[j] += A[i][j];
        }
    }
    
    //答えの計算
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            Answer[i][j] = Row[i] + Column[j] - A[i][j];
        }
    }
    
    //出力
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (j >= 2) printf(" ");
            printf("%d", Answer[i][j]);
        }
        printf("\n");
    }
    return 0;
}
