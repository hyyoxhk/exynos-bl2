char __bss_start[0] __attribute__((section(".__bss_start")));
char __bss_end[0] __attribute__((section(".__bss_end")));
unsigned int __bss_len = __bss_end - __bss_start;
