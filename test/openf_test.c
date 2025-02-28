#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int fd1, fd2;
	static char buf[20];
	fd1 = open("test_file", O_CREAT | O_WRONLY, 0644);
	fd2 = open("test_file", O_RDONLY);
    unlink("test_file");
    write(fd1, "hello\n", 6);
    read(fd2, buf, sizeof(buf));
    printf("buf = %s\n", buf);
}