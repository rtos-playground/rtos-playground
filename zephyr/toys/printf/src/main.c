#include <string.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <console.h>

int shoot(int **bow) {
	printk("Are you %u enough?\n", **bow);
	for(;;) {
		char * tmp = console_getline();
		if(*tmp == '\x00') {
			break;
		}
		printf(tmp);
	}
	return **bow;
}

void main(void)
{
	int target= 1337;
	int *arrow=&target;
	console_getline_init();
	printk("System running\n");
	printk("%u.\n", shoot(&arrow) * 93409 * 40237);
}
