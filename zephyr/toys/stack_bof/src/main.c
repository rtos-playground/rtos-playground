#include <string.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <console.h>

void vuln(void) {
	char stack_buf[32];
	printk("[bof] > ");
	strcpy(stack_buf, console_getline());
}

void main(void)
{
	console_getline_init();

	printk("System running\n");

	for(;;) {
		vuln();
	}
}
