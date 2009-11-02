void start (void) __asm__("_start");

extern void koutinit (void);
extern void kputs (const char*);

void panic ( const char* msg )
{
	kputs("PANIC");
	kputs("**********");
	kputs(msg);
	kputs("**********");
	__asm__("hlt");
}

void start (void)
{
	koutinit();
	kputs("boot");
}
