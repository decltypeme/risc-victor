int main()
{
	char *s="hello there";
	char *p = s;
	char c;
	while(*p){
		c= *p;
		if(c>='a' && c<='z')
			*p = c + 'A' - 'a';
	}
	return 0;
}
