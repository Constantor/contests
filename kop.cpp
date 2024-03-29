// #define _GLIBCXX_DEBUG // сам расставляет кучу ассертов, но может асимптотически (!) замедлить
// #define FAST_ALLOCATOR_MEMORY 1e7 // количество байт

/*
// 99%, что не поможет
#pragma GCC optimize("Ofast") // векторизацию подрубает, ну там сложно
//#pragma GCC optimize("no-stack-protector") // хуйня
#pragma GCC optimize("unroll-loops") // у тебя есть фор по 100 он просто берет и повторяет не фор а 100 раз ну иногда ускоряет
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native") // вот здесь потно ну там 03 02 запускает с битами быстрее работает там тоже векторизация
#pragma GCC optimize("fast-math") // быстрее с вещественными работает ну там float оч быстрый становится
*/

#include <bits/stdc++.h>

/** Fast allocation */

#ifdef FAST_ALLOCATOR_MEMORY
int allocator_pos = 0;
char allocator_memory[(int) FAST_ALLOCATOR_MEMORY];

inline void *operator new(size_t n) {
	char *res = allocator_memory + allocator_pos;
	allocator_pos += n;
	assert(allocator_pos <= (int) FAST_ALLOCATOR_MEMORY);
	return (void *) res;
}

inline void operator delete(void *) noexcept {}
//inline void * operator new [] ( size_t ) { assert(0); }
//inline void operator delete [] ( void * ) { assert(0); }
#endif

/* Another variant of fast allocation
const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new (size_t n) {
	assert((mpos += n) <= MAX_MEM);
	return (void *)(mem + mpos - n);
}
void operator delete (void *) noexcept { } // must have!
void operator delete (void *, size_t) noexcept { } // must have!
*/

/** Fast input-output */

template<class T = int>
inline T readInt();

inline double readDouble();

inline int readUInt();

inline int readChar(); // first non-blank character
inline void readWord(char *s);

inline bool readLine(char *s); // do not save '\n'
inline bool isEof();

inline int getChar();

inline int peekChar();

inline bool seekEof();

inline void skipBlanks();

template<class T>
inline void writeInt(T x, char end = 0, int len = -1);

inline void writeChar(int x);

inline void writeWord(const char *s);

inline void writeDouble(double x, int len = 0); // works correct only for |x| < 2^{63}
inline void flush();

static struct buffer_flusher_t {
	~buffer_flusher_t() {
		flush();
	}
} buffer_flusher;

/** Read */

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
	if(buf_pos == buf_len) {
		buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
		if(buf_pos == buf_len)
			return 1;
	}
	return 0;
}

inline int getChar() {
	return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
	return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
	int c;
	while((c = peekChar()) != -1 && c <= 32)
		buf_pos++;
	return c == -1;
}

inline void skipBlanks() {
	while(!isEof() && buf[buf_pos] <= 32U)
		buf_pos++;
}

inline int readChar() {
	int c = getChar();
	while(c != -1 && c <= 32)
		c = getChar();
	return c;
}

inline int readUInt() {
	int c = readChar(), x = 0;
	while('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return x;
}

template<class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if(c == '-')
		s = -1, c = getChar();
	else if(c == '+')
		c = getChar();
	while('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

inline double readDouble() {
	int s = 1, c = readChar();
	double x = 0;
	if(c == '-')
		s = -1, c = getChar();
	while('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	if(c == '.') {
		c = getChar();
		double coef = 1;
		while('0' <= c && c <= '9')
			x += (c - '0') * (coef *= 1e-1), c = getChar();
	}
	return s == 1 ? x : -x;
}

inline void readWord(char *s) {
	int c = readChar();
	while(c > 32)
		*s++ = c, c = getChar();
	*s = 0;
}

inline bool readLine(char *s) {
	int c = getChar();
	while(c != '\n' && c != -1)
		*s++ = c, c = getChar();
	*s = 0;
	return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar(int x) {
	if(write_buf_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
	write_buf[write_buf_pos++] = x;
}

inline void flush() {
	if(write_buf_pos) {
		fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
		fflush(stdout);
	}
}

template<class T>
inline void writeInt(T x, char end, int output_len) {
	if(x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while(x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while(n < output_len)
		s[n++] = '0';
	while(n--)
		writeChar(s[n]);
	if(end)
		writeChar(end);
}

inline void writeWord(const char *s) {
	while(*s)
		writeChar(*s++);
}

inline void writeDouble(double x, int output_len) {
	if(x < 0)
		writeChar('-'), x = -x;
	assert(x <= (1LLU << 63) - 1);
	long long t = (long long) x;
	writeInt(t), x -= t;
	writeChar('.');
	for(int i = output_len - 1; i > 0; i--) {
		x *= 10;
		t = std::min(9, (int) x);
		writeChar('0' + t), x -= t;
	}
	x *= 10;
	t = std::min(9, (int) (x + 0.5));
	writeChar('0' + t);
}

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned char uchar;
typedef long double ld;

#define WITH_FILES true
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
	bool local = 1 < argc && string(argv[1]) == "local";
	bool localFile = local && 2 < argc;
	if(localFile) {
		freopen(argv[2], "r", stdin);
		freopen(argv[2], "w", stdout);
	} else if(!local && WITH_FILES) {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	}
	if(localFile || (!local && WITH_FILES)) {
		ios::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}

	solve();

	return 0;
}
