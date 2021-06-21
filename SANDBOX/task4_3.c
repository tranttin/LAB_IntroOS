
// [1] 270

increment(&sequence);
where the increment() function is implemented using theCAS instruction:
void increment(atomic_int *v)
{
int temp;
do {
temp = *v;
}
while (temp != compare_and_swap(v, temp, temp+1));
}
