#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
#define INF 99999999
class num_pack {
public:
	int max_left;
	int max_right;
	int sum;
	num_pack(int left,int right,int sum):max_left(left),max_right(right),sum(sum){
	
	}
	bool operator>(const num_pack& p) {
		return sum > p.sum;
	}
};

num_pack find_max_crossing_subarray(int* A, int low, int mid, int high) {
	int left_sum = -INF;
	int sum = 0;
	int max_left = low;
	int max_right = high;
	for (int i = mid; i >= low; i--)
	{
		sum += A[i];
		if (sum>left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = -INF;
	sum = 0;
	for (int i = mid+1; i < high+1; i++)
	{
		sum += A[i];
		if (sum>right_sum)
		{
			right_sum = sum;
			max_right = i;
		}
	}
	num_pack result(max_left,max_right,left_sum+right_sum);
	return result;
}
num_pack find_max_subarray(int* A, int low, int high) {
	int mid;
	if (high==low)	{
		num_pack result(low, high, A[low]);
		return result;
	}
	else {
		mid = ceil((low + high) / 2);
	}

	num_pack ll_lh_ls = find_max_subarray(A, low, mid);
	num_pack rr_rh_rs = find_max_subarray(A, mid+1, high);
	num_pack cr = find_max_crossing_subarray(A, low, mid, high);
	if (ll_lh_ls>rr_rh_rs&&ll_lh_ls>cr)
	{
		return ll_lh_ls;
	}
	else if (rr_rh_rs > ll_lh_ls&&rr_rh_rs>cr) {
		return rr_rh_rs;
	}
	else {
		return cr;
	}
}
int buffer[10000],cnt;
int main(){
	freopen("in.txt","r",stdin);
    int x;
    cnt=0;
	cout<<"reading"<<endl;
    while(scanf("%d",&x)==1){
        buffer[cnt++]=x;
    }
	cout<<"read finished"<<endl;
	num_pack result=find_max_subarray(buffer,0,cnt-1);
	cout<<"left: "<<result.max_left<<endl;
	cout<<"right: "<<result.max_right<<endl;
	cout<<"max_sum: "<<result.sum<<endl;
	return 0;
}