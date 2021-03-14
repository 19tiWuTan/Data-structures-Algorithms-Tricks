/*
    tóm tắt : Cho dãy số gồm N phần tử, đếm số lượng đoạn đẹp sao cho : 
        1 <= l <= r <= n
        |A[l] - A[r]| = max(l, r) - min(l, r) (điều kiện (1))
        trong đó max(l, r) trả về giá trị a[i] lớn nhất , i thuộc đoan [l, r]
                 min(l, r) trả về giá trị a[i] nhỏ nhất , i thuộc đoạn [l, r]
    
    nguồn : Frecontest 123 ( có tài liệu trong GGDrive của Thanh )
    
    tóm tắt cách giải : 
        bài toán chỉ tồn tại 2 trường hợp để thỏa mãn điều kiện (1)
            hoặc a[l] = max(l, r) và a[r] = min(l, r)
            hoặc a[l] = min(l, r) và a[r] = max(l, r)
        
     Trường hợp 1 : 
        gọi lim[i] sẽ là vị trí nhỏ nhất sao cho a[i] là min từ lim[i] đến i (kĩ thuật stack)
        ta sẽ dùng kĩ thuật tương tự để có thể tìm được vị trí j sao cho a[i] là lớn nhất trong đoạn [j, i] (mục tiêu 2)
        bây giờ ta chỉ việc đếm số lượng vị trí l  (1 <= l < j) sao cho thỏa điều kiện trường hợp 1
        nhận xét :  mục tiêu đếm số lượng vị trí l : a[l] = max(l, i) -> nó chỉ có thể là những vị trí chưa được pop ra từ stack ( trong quá trị tìm vị trí j ở mục tiêu 2)
                    những vị trí x nào mà x >= lim[i] thì a[x] >= a[i]
                    stack sẽ lưu những vị trí tăng dần -> có thể chặt nhị phân tìm vị trị y nhỏ nhất trong stack sao cho stack[y] >= lim[i]
        như vậy số lượng đoạn có r = i, thoả điều kiện (1) = size của stack - y
        
     Trường hợp 2 : 
        để dễ thực hiện , ta quy về giống trường hợp 1 bằng cách reverse mảng ban đầu
        lưu ý trường hợp tồn tại đoạn a[l] = a[r] đã được tính ở trường hợp 1
                    
*/
/**
    *Makacha
**/
#include <bits/stdc++.h>
using namespace std;

template <typename T> inline void read (T &x) {bool b = 0; char c; while (!isdigit (c = getchar()) && c != '-');
if (c == '-') c = getchar(), b = 1; x = c - 48; while (isdigit(c = getchar())) x = (x<<3) + (x<<1) + c - 48; if (b)x=-x;}
template <typename T> inline void wrip(T x) {if (x > 9) wrip(x / 10); putchar(x%10 + 48); }

template <typename T> inline void write(T x) {if (x < 0) putchar('-'), x = -x; wrip(x); putchar(' ');}
template <typename T> inline void writeln(T x) {if (x < 0) putchar('-'), x = -x; wrip(x); putchar('\n');}
inline char readch() {char c; do c = getchar(); while (c == '\n' || c == ' '); return c;}
inline void reads(string &s) {char c; while((c=getchar())==' '||c =='\n'); s=c; while((c=getchar())!=' '&&c!='\n'&&c!=EOF) s+=c;}
inline void getlines(string &s) {char c; while((c=getchar())=='\n'); s=c; while((c=getchar())!='\n') s+=c;}
typedef const int csint;

#define fi first
#define se second
#define mp make_pair
typedef unsigned long long ll;
typedef long double ld;
typedef pair <int, ll> ii;
typedef vector <int> vi;

const ld pi = acos(-1);
const int inf = 1e9,
N = 3e5 + 11;

int n, a[N], q[N], lim[N], last[N], ok[N];
ll res, ans;
void Cal() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[q[top]] >= a[i])
            top--;
        lim[i] = q[top] + 1;
        q[++top] = i;
    }
    top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[q[top]] < a[i])
            top--;
        int l = 1, r = top;
        while (l <= r) {
            int mid = l + r >> 1;
            if (q[mid] >= lim[i])
                r = mid - 1;
            else
                l = mid + 1;
        }
        res += top - r;
        q[++top] = i;
    }
}
void Cal2() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[q[top]] >= a[i])
            top--;
        lim[i] = q[top] + 1;
        q[++top] = i;
    }
    top = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        while (top && a[q[top]] < a[i])
            top--;
        if (a[q[top]] == a[i])
            last[i] = last[q[top]];
        else
            last[i] = top;
        int l = 1, r = top;
        while (l <= r) {
            int mid = l + r >> 1;
            if (q[mid] >= lim[i])
                r = mid - 1;
            else
                l = mid + 1;
        }
        if (last[i] >= r)
            res += last[i] - r;
        ok[i] = top - last[i];

        q[++top] = i;
    }
}
int main() {
    int ntest;
    read(ntest);
    while (ntest--) {
        read(n);
        for (int i = 1; i <= n; i++)
            read(a[i]);
        res = ans = 0;
        Cal();
        reverse(a + 1, a + n + 1);
        Cal2();
        cout << res + n  << '\n';
    }
}
