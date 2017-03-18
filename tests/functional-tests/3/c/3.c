
int fib(int x)
{
	if(x == 0 || x == 1)
		return 1;
	return fib(x-1) + fib(x-2); 
}

int main()
{
	fib(7);
	return 0;
}
