/*
 ＜問題＞
 入力
 3
 1 2
 2 3
 このとき、1と3の間に新ルートを作る。
 1-2 2-3 3-1 となり、スコアは道の本数3、出力として3を返す。
 
 ＜解答方法＞
 N頂点、N-1辺のグラフ問題。木構造。以下の特徴をもつ。
 ・頂点uから頂点vに行く単純パスはただ一つ存在する
 ・頂点uと頂点vの道を追加するとき、閉路は1つだけ出現し、長さはuからvのパスの長さ＋１
 
 uからvのパスの最短距離の最大値を求める。
 深さ優先、幅優先探索→O(N^2)となってしまう。
 
 ここではO(N)で求められるアルゴリズムを使用する。
 ・頂点1から各頂点までの最短距離を求める
 ・最も最短距離が大きかった頂点をuとして、頂点uからの最短距離を求める。
 ・その時の最短距離最大値がスコアとなる。
 */

#include <iostream>

//配列を扱える
#include <vector>

/*
 キューについて
 push();で列の後ろに追加
 front();で最初の値を取り出す
 pop();でキューの先頭を削除
 empty();でキューが空かどうか確認できる
 */
#include <queue>
using namespace std;

//入力
int N;
int A[1 << 18], B[1 << 18];

//グラフ

//無限を定義
const int INF = (1 << 29);

vector<int> G[1 << 18];
int dist[1 << 18];

//幅優先探索：要検索
void getdist(int start) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
    }
    
    //キューを定義
    queue<int> Q;
    Q.push(start);
    dist[start] = 0;
    
    while (!Q.empty()) {
        int pos = Q.front();
        Q.pop();
        for (int to : G[pos]) {
            if (dist[to] == INF) {
                dist[to] == dist[pos] + 1;
                Q.push(to);
            }
        }
    }
}

int main() {
    //入力
    cin >> N;
    for (int i = 1; i <= N - 1; i++) {
        cin >> A[i] >> B[i];
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }
    
    //頂点1からの最短距離を求める
    //maxid1:　頂点1から最短距離最大の点
    getdist(1);
    int maxn1 = -1, maxid1 = -1;
    for (int i = 1; i <= N; i++) {
        if (maxn1 < dist[i]) {
            maxn1 = dist[i];
            maxid1 = i;
        }
    }
    
    //maxid1からの最短距離を求める
    //maxn2: 最短距離最大値
    getdist(maxid1);
    int maxn2 = -1;
    for (int i = 1; i <= N; i++) {
        maxn2 = max(maxn2, dist[i]);
    }
    
    cout << maxn2 + 1 << endl;
    return 0;
}



