#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>
struct arr{
	int n;
	int a[10];
};
struct file {
	struct arr ar;
	char* filename;
};
static int sum =0;
void* thr1(void* ar){
	struct arr *ap = (struct arr*) ar;
	ap->n=3; int i=0;
	for(i=0;i<ap->n;i++)
		ap->a[i] = i+1;
}

void* thr2(void* ar){
	struct arr *ap = (struct arr*) ar;
	int i, s=0;
	for(i=0;i<ap->n;i++)
		s=s + ap->a[i];
	sum=s;

}

void* thr3 (void* ar){
	struct file *fi = (struct file*) ar;
	FILE *out; int count;
	out= fopen(fi->filename,"wb");
	fprintf(out,"number element or array: %d\n", fi->ar.n);
	for(count=0; count<fi->ar.n; count++){
		fprintf(out,"%d\t",fi->ar.a[count]);
	}
	fprintf(out,"\n");
	fprintf(out,"sum=%d\n",sum);
	printf("tong : %d\n",sum);
	fclose(out);
}

int main (int argc,char * argv[]){
	int i;
	pthread_t tid[3];
	struct arr ar;
	int status, *pstatus= &status;
	pthread_create(&tid[0],NULL,thr1,(void*) &ar);
	sleep(1);
	if(pthread_join(tid[0],(void**) pstatus)==0)
	{
		pthread_create(&tid[1],NULL,thr2,(void*) &ar);
		if(pthread_create(&tid[1],NULL,thr2, (void*) &ar)==0)
		{
			struct file arf;
			arf.ar=ar;
			arf.filename=argv[1];
			pthread_create(&tid[2],NULL,thr3,(void*) &arf);
		}
	}	
	sleep(2);
	return 0;
}
