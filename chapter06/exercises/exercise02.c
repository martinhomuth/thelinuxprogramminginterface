#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

static jmp_buf env;

void f1()
{
	setjmp(env);
}

int main(int argc, char *argv[])
{
	f1();
	longjmp(env, 1);
}
