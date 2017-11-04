#include <stdio.h>
#include <string.h>
char *wtest = "for test";
int main(int argc, char *agv[])
{
	FILE *file = fopen("./tmp/hello", "r+");
	if(file == NULL)
	{
		printf("open failed\n");
	}
	char buf[32] = {'\0'};
	fread(buf, 5, 1, file);
	printf("%s\n", buf);
	
	strcpy(buf, wtest);
	printf("%s\n", buf);
	
	fwrite(buf, strlen(buf), 1, file);
	fclose(file);
	
file = fopen("./tmp/hello", "r+");
	if(file == NULL)
	{
		printf("open failed\n");
	}
	memset(buf, '\0', sizeof(buf));
	fread(buf, 5, 1, file);
	printf("%s\n", buf);	
	return 0;
}