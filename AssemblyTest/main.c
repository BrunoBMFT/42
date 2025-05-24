extern long write(int fd, const void *buf, int count);

int	main(void)
{
	write(1, "hell\n", 5);
}