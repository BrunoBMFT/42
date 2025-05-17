#include "includes/ft_printf.h"
#include <stdio.h>
#include <limits.h>

int main(void)
{
	int ret1, ret2;

	printf("Plus: %+d %+d\n", 42, -42);
	ft_printf("Plus: %+d %+d\n", 42, -42);

	// printf("Space: % d % d\n", 42, -42);

	// // Basic tests
	// ft_printf("=== BASIC TESTS ===\n");
	// ft_printf("Char: %c\n", 'A');
	// ft_printf("String: %s\n", "Hello, 42!");
	// ft_printf("Pointer: %p\n", (void *)0x12345678);
	// ft_printf("Decimal: %d\n", 42);
	// ft_printf("Integer: %i\n", -42);
	// ft_printf("Unsigned: %u\n", 3000000000U);
	// ft_printf("Hex (lower): %x\n", 0xabcdef);
	// ft_printf("Hex (upper): %X\n", 0xABCDEF);
	// ft_printf("Percent: %%\n");

	// // Bonus: Flags
	// ft_printf("\n=== BONUS: FLAGS ===\n");
	// ft_printf("Plus: %+d %+d\n", 42, -42);
	// ft_printf("Space: % d % d\n", 42, -42);
	// ft_printf("Hash (x): %#x\n", 42);
	// ft_printf("Hash (X): %#X\n", 42);
	// ft_printf("Zero-padding: %010d\n", 42);
	// ft_printf("Left-align: %-10d<--\n", 42);

	// // Width and precision
	// ft_printf("\n=== BONUS: WIDTH & PRECISION ===\n");
	// ft_printf("Width 10: %10d\n", 42);
	// ft_printf("Precision .5: %.5d\n", 42);
	// ft_printf("Width & precision: %10.5d\n", 42);
	// ft_printf("String precision: %.5s\n", "HelloWorld");
	// ft_printf("String width & precision: %10.5s\n", "HelloWorld");

	// // Multiple conversions
	// ft_printf("\n=== MULTIPLE CONVERSIONS ===\n");
	// ft_printf("Mix: %d, %x, %X, %s, %c, %%\n", 123, 255, 255, "test", 'Z');

	// // Comparison with real printf
	// ft_printf("\n=== RETURN VALUE COMPARISON ===\n");
	// ret1 = ft_printf("Mine: [%#08x]\n", 42);
	// ret2 = printf("Orig: [%#08x]\n", 42);
	// printf("Return values: ft_printf = %d, printf = %d\n", ret1, ret2);
	// // Edge cases
	// ft_printf("\n=== EDGE CASES ===\n");
	// ft_printf("INT_MAX: %d\n", INT_MAX);
	// ft_printf("INT_MIN: %d\n", INT_MIN);
	// ft_printf("UINT_MAX: %u\n", UINT_MAX);
	// ft_printf("Null string: %s\n", (char *)NULL);
	// ft_printf("Null pointer: %p\n", NULL);

    return 0;
}
