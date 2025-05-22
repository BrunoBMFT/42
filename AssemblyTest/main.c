extern long my_write(int fd, const void *buf, int count);

int	main(void)
{
	my_write(1, "hell\n", 5);
}