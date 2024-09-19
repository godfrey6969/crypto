#include &lt;iostream&gt;
int gcd(int a, int b) {
while (b != 0) {
int temp = b;
b = a % b;
a = temp;
}
return a;
}

int extendedEuclidean(int a, int b, int&amp; x, int&amp; y) {
if (b == 0) {
x = 1;
y = 0;
return a;
}
int x1, y1;
int gcd = extendedEuclidean(b, a % b, x1, y1);
x = y1;
y = x1 - (a / b) * y1;
return gcd;
}

int main() {
int num1, num2;
std::cout &lt;&lt; &quot;Enter two numbers: &quot;;
std::cin &gt;&gt; num1 &gt;&gt; num2;
int result = gcd(num1, num2);
std::cout &lt;&lt; &quot;GCD: &quot; &lt;&lt; result &lt;&lt; std::endl;
return 0;
}