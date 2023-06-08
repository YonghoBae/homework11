/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}
/*배열 메모리할당 해제*/
int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}
/*배열 출력*/
void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");
	/*배열 출력*/
	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		/*최솟값 임의설정*/
		minindex = i;
		min = a[i];
		/*최솟값 탐색*/
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		/*찾은 최솟값과 이전에 정렬한 부분 빼고 가장 앞에 있는 값과 교체*/
		a[minindex] = a[i];
		a[i] = min;
	}
	/*정렬 후 출력*/
	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;
	/*정렬 전 출력*/
	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	/*i를 기준으로 왼쪽은 정렬된 집합, i포함 오른쪽은 정렬이 안된 집합*/
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];
		/*i를 정렬하면서 정렬된 집합에 넣음. 넣을 위치를 찾기위해 j=i를 하고 a[i]보다 앞에 수가 크면 교체
		끝까지 탐색했으면 반복문 종료*/
		j = i;
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		/*찾은 위치에 a[i] 대입*/
		a[j] = t;
	}
	/*정렬 후 출력*/
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;
	/*정렬 전 출력*/
	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	/*배열사이즈만큼 반복*/
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		/*연속으로 있는 두개의 값을 비교하고 큰값을 뒤로 보내면서 정렬*/
		for (j = 1; j < MAX_ARRAY_SIZE-i; j++)
		{
			if (a[j-1] > a[j])
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}
	/*정렬 후 출력*/
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;
	/*정렬 전 출력*/
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	/*h는 간격*/
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		/*i는 비교 시작할 위치*/
		for (i = 0; i < h; i++)
		{
			/*h의 모든 위치에서 삽입 정렬을 수행*/
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	/*정렬 후 출력*/
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //pivot
		i = -1; //left
		j = n - 1; //right

		while(1)
		{
			while(a[++i] < v); //왼쪽에서 pivot보다 큰 값이 나오면 반복문 종료
			while(a[--j] > v); //오른쪽에서 pivot보다 작은 값이 나오면 반복문 종료

			if (i >= j) break; //left >= right면 반복문 종료
			/*pivot의 왼쪽, 오른쪽에서 찾은 left,right에 위치한 값 교체*/
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/*pivot값을 i위치로*/
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		/*정렬이 안된 왼쪽, 오른쪽 집합도 반복적으로 진행*/
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}
	/*hasstable -1로 초기화*/
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;
	
	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];  // a[i]를 key로 설정
		hashcode = hashCode(key);  // key에 해시 함수를 적용하여, hashcode에 대입

		if (hashtable[hashcode] == -1)
		{
			// 해당 hashcode 위치에 아무 값도 없는 경우, key 저장
			hashtable[hashcode] = key;
		} else {
			// 해당 hashcode 위치에 이미 값이 있는 경우, 충돌이 발생해서 선형 조사법을 사용하여 빈 슬롯 탐색. 

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
			// 빈 슬롯을 찾으면, 그 위치에 key 저장합니다.
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	//key에 대한 위치를 index에 저장 
	int index = hashCode(key);
	//해당 index에 key값이 있으면 index리턴 후 함수종료
	if(ht[index] == key)
		return index;
	//없으면 다른 위치 탐색 후 찾으면 반복 종료
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	//찾은 index 리턴
	return index;
}



