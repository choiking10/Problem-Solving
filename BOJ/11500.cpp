#include <iostream>
#include <cmath>
#include <vector>

long long gcd(long long a, long long b){
	if(b == 0) return a;
	return gcd(b,a%b);
}
struct fraction{
	long long a,b;
	fraction(){a=1,b=0;}
	fraction(long long aa, long long bb):a(aa),b(bb){
		long long g= gcd(std::abs(a),std::abs(b));
		if(g == 0) while(1) printf("11");
		a/=g;
		b/=g;
		if(a < 0) b*=-1, a*=-1;
	}
	fraction operator+(fraction f){
		return fraction(f.a*a,b*f.a+f.b*a);
	}
	fraction operator-(fraction f){
		return fraction(f.a*a,b*f.a-f.b*a);
	}
	fraction operator*(long long n){
		return fraction(a,n*b);
	}
	fraction operator/(long long n){
		if(n == 0) while(1) printf("hello");
		return fraction(a*n,b);
	}

};
fraction dy[60][60];
bool check[60];
long long pas[70][70];
void make_pas(){
	pas[0][0] = 1;
	for(int i = 1; i<= 60; i++){
		pas[i][0] = pas[i][i] = 1;
		for(int j = 1; j< i; j++) pas[i][j] = pas[i-1][j-1]+pas[i-1][j];
	}
}
void make_sum(int t){
	if(check[t]) return;
	check[t] = true;
	for(int i = 0; i< t; i++) make_sum(i);
	for(int i = 0; i<= t+1; i++){
		dy[t][i] = fraction(1,pas[t+1][i]); 
	}

	dy[t][0]= dy[t][0] - fraction(1,1);

	for(int i = 0; i<= t-1; i++) {
		for(int j = 0; j<= i + 1; j++){
			dy[t][j] = dy[t][j] - dy[i][j]*pas[t+1][i]; 
		}
	}
	for(int i = 0; i<= t+1; i++){
		dy[t][i] = dy[t][i]/pas[t+1][t];
	}
}
int main(void){
	make_pas();
	check[0] = true;
	dy[0][1] = fraction(1,1);
	make_sum(25);
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		std::vector<fraction> ans(60,fraction(1,0));
		long long result = 0;
		for(int i=0;i<=n;i++){
			long long c;
			scanf("%lld",&c);
			if(i == 0) result = std::abs(c);
			for(int j=0;j<=i+1;j++){
				ans[j] = ans[j] + dy[i][j] * c;
	//			printf("%lld/%lld ",dy[i][j].a,dy[i][j].b);
			}
	//		printf("\n");
		}
		for(int i =0; i<= n+1; i++){
	//		printf("%lld/%lld ",ans[i].a,ans[i].b);
			result = result +std::abs(ans[i].b);
		}
	//	printf("\n");
		printf("%lld\n",result);
	}
}
