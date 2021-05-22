#include <stdio.h>

int main(void)
{
	int iRelLen;
	char buffer1[16];

	iRelLen = scnprintf (buffer1, 10, "%d", "1234567890");

	printf("iRelLen = %d\n", iRelLen);
	printf("buffer1: %s\n", buffer1);
	return 0;
}


int snprintf(char *buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsnprintf(buf, size, fmt, args);
	va_end(args);

	return i;
}

int scnprintf(char *buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vscnprintf(buf, size, fmt, args);
	va_end(args);

	return i;
}