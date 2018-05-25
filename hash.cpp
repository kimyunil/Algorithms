#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <memory.h>

#define MAX_KEY 64
#define MAX_DATA 128
#define MAX_TABLE 23
//4096

typedef struct
{
	char key[MAX_KEY + 1];
	char data[MAX_DATA + 1];
}Hash;
Hash tb[MAX_TABLE];

unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}
	printf("hash = %ld\n", (hash % MAX_TABLE));
	return (hash % MAX_TABLE);
}

int find(const char *key, char *data)
{
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;
	int step = 1;

	while (tb[h].key[0] != 0 && cnt--)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			strcpy(data, tb[h].data);
			return 1;
		}
		h = (h + 1) % MAX_TABLE;
	}
	return 0;
}

int add(const char *key, char *data)
{
	unsigned long h = hash(key);
	int step = 1;
	int i = 0;

	while (tb[h].key[0] != 0)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			return 0;
		}
		h = (h + 1) % MAX_TABLE;
	}
	strcpy(tb[h].key, key);
	strcpy(tb[h].data, data);
	return 1;
}

void show() {
	for (int i = 0; i < MAX_TABLE; i++)
		printf("tb[%d] = [%s,%s]\n", i, tb[i].key, tb[i].data);
}
int main(int argc, char* argv[])
{
	int  N, Q;
	freopen("input.txt", "r", stdin);
	memset(tb, 0, sizeof(tb));
	scanf("%d", &N);
	char k[MAX_KEY + 1];
	char d[MAX_DATA + 1];
	
	for (int i = 0; i < N; i++){
		scanf("%s %s\n", &k, &d);
		add(k,d);
		show();
	}
	
	if (find("dd", d))
	{
		printf("found : %s\n", d);
	}
	else
	{
		printf("not find\n");
	}

	/*
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++)
	{
		char k[MAX_KEY + 1];
		char d[MAX_DATA + 1];

		scanf("%s\n", &k);

		if (find(k, d))
		{
			printf("%s\n", d);
		}
		else
		{
			printf("not find\n");
		}
	}
	*/
	return 0;
}
