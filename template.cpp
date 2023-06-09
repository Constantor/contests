/*
// 99%, что не поможет
#pragma GCC optimize("Ofast") // векторизацию подрубает, ну там сложно
//#pragma GCC optimize("no-stack-protector") // хуйня
#pragma GCC optimize("unroll-loops") // у тебя есть фор по 100 он просто берет и повторяет не фор а 100 раз ну иногда ускоряет
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native") // вот здесь потно ну там 03 02 запускает с битами быстрее работает там тоже векторизация
#pragma GCC optimize("fast-math") // быстрее с вещественными работает ну там float оч быстрый становится
*/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned char uchar;
typedef long double ld;

#define WITH_FILES false
#define TIME_RAND false

#if TIME_RAND
mt19937 rnd(chrono::high_resolution_clock().now().time_since_epoch().count());
mt19937_64 rnd64(chrono::high_resolution_clock().now().time_since_epoch().count());
#else
#define RND_CONST 1337
mt19937 rnd(RND_CONST);
mt19937_64 rnd64(RND_CONST);
#undef RND_CONST
#endif

void solve() {

}

int main(int argc, char *argv[]) {
#if WITH_FILES
	if(2 < argc && string(argv[1]) == "local") {
		int fileLen = static_cast<int>(strlen(argv[2]));
		int fileID = 0;
		for(int i = 5, j = 1; '0' <= argv[2][fileLen - i] && argv[2][fileLen - i] <= '9'; i++, j *= 10)
			fileID += (argv[2][fileLen - i] - '0') * j;
		freopen(("input" + to_string(fileID) + ".txt").c_str(), "r", stdin);
		freopen(("output" + to_string(fileID) + ".txt").c_str(), "w", stdout);
	} else {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	}
#endif
	if(!(1 < argc && string(argv[1]) == "local")) {
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}

    solve();

    return 0;
}
