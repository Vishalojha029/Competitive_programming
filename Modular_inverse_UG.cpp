#define NCR
#define PRIME	M
int pw(int a,int p=M-2,int MOD=M){
	int result = 1;
	while (p > 0) {
		if (p & 1)
			result = a * result % MOD;
		a = a * a %M;
		p >>= 1;
	}
	return result;
}
int fact[100005],invfact[100005];
void init(){
	int p=PRIME;
	fact[0]=1;
	int i;
	for(i=1;i<100005;i++){
		fact[i]=(i*fact[i-1])%p;
	}
	i--;
	invfact[i]=pw(fact[i],p-2,p);
	for(i--;i>=0;i--){
		invfact[i]=(invfact[i+1]*(i+1))%p;
	}
}
int ncr(int n,int r){
	return (((fact[n]*invfact[r])%PRIME)*invfact[n-r])%PRIME;
}
