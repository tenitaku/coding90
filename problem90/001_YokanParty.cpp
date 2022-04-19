#include <iostream>
/*
 標準入力、出力を使用できるようになる。
 cin:標準入力　cin >> a >> b;
 cout:出力　cout << somevalue << anothervalue;
 */
using namespace std;
// std::string str; と毎回宣言せずに良くなる

long long N, K, L;
long long A[1 << 18];
//1<<18 (1の左18シフト) = 262144(10)
//64bitの情報

/*
 0以上L以下の二分探索問題。
 答えはM以上か？　＝＝　K+1こ以上の「長さM以上のピース」に分割可能か？
 
 左から順にピースの長さがM以上になるところを探す。
 */
bool solve(long long M) {
    long long cnt = 0; pre = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] - pre >= M && L - A[i] >= M) {
            cnt += 1;
            pre = A[i];
        }
    }
    if (cnt >= K) return true;
    return false;
}

int main() {
    cin >> N >> L;
    cin >> K;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    
    long long left = -1;
    long long right = L + 1;
    while (right - left > 1) {
        long long mid = left + (right - left) / 2;
        if (solve(mid) == false) right = mid;
        else left = mid;
    }
    cout << left << endl;
    // endl をつけることで最終的な結果のみを出力できる
    return 0;
}
