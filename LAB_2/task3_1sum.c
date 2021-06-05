// 2021 Jun 4
// Author: Tran Trung Tin
// Demo passing parameter though system call
int sum_n(int n)
{
  int sum=0;
  for(int i=1; i<=n; i++) sum += i;
  return sum;
}
