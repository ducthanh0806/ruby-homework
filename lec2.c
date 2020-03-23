#include<stdio.h>
#include<stdlib.h>

/*void* memcpy(void* region1, const void* region2, size_t n) {

	const char* first = (const char*) region2;
	const char* last = ((const char*) region2) + n;
	char* result = (char*) region1;
	while (first != last) *result++ = *first++;
	return result;
}*/

void exch (void * buf, int size, int i, int j)
{
	int tmp;
	tmp = *((int*)((char*)buf+(size*i)));
	*((int*)((char*)buf+(size*i))) = *((int*)((char*)buf+(size*j)));
	*((int*)((char*)buf+(size*j))) = tmp;
}

int int_compare(void const* x, void const *y) {
	int m, n;
	m = *((int*)x);
	n = *((int*)y);
	if (m == n) return 0;
	return m>n?1:-1;
}

// return -1 if not found
int search( void* buf, int size, int l, int r, void * item, int (*compare)(void const*, void const*)) {

	int i, res;
	if (r < l) return -1;
	i = (l + r)/2;
	res = compare(item, (char*)buf+(size*i) );
	if (res==0)
		return i;
	else if (res < 0)
		return search(buf, size, l, i-1, item, compare);
	else
	return search(buf, size, i+1, r, item, compare);

}

void sort(void* a, int size, int l, int r, int (*compare)(void const*, void const*)) {

	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1) {
		while (compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
		while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
		if (j == l) break;
		if (i >= j) break;
		exch(a, size, i, j);
		if (compare((char*)a+i*size, (char*)a+r*size)==0)
			exch(a, size, ++p, i);
		if (compare((char*)a+j*size, (char*)a+r*size)==0)
			exch(a, size, --q, j);
			}
	exch(a, size, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) exch(a, size, k, j--);
	for (int k = r-1; k >= q; k--) exch(a, size, k, i++);
	sort(a, size, l, j, compare);
	sort(a, size, i, r, compare);
}

void printarr(int* arr, int size)
{
	printf("a[] = [");
	for(int idx=0; idx < size; idx++)
	{
		printf("%d", arr[idx]);
		if (idx != (size - 1))
			printf(",");
    	}
	printf("]\n");
}

int main() {
	int a[100], i, res;
	int n = 100, item = 5;
	for (i=0; i<n; i++) a[i] = rand() % 50;
	printf("Chua sort:\n");
	printarr(a, 100);
	sort(a,sizeof(int),0,n-1,int_compare);
	printf("Da sort:\n");
	printarr(a, 100);
	res = search (a,sizeof(int),0,n-1,&item,int_compare);
	printf("item = %d\nres = %d\na[res] = %d\n",item,res,a[res]);
	return 0;
}