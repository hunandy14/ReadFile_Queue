#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stringSplit(char* str, const char* delim) {
	char temp[64];
	strcpy(temp, str);

	char* pch = strtok(temp, delim);
	while (pch != NULL) {
		printf("%s\n", pch);
		pch = strtok(NULL, delim);
	}
}
int main() {
	stringSplit("one two three four five", " ");
	return 0;
}