#include <stdio.h>
#include <fcntl.h>
#include <paths.h>
#include <string.h>
#include <sys/types.h>

#define CDEV_DEVICE	"cd_example"
static char buf[512+1];

int
main(int argc, char *argv[])
{
	int kernel_fd;
	int len;

	if (argc != 2)
	{
		printf("Usage: \n%s <string>\n", argv[0]);
		exit(0);
	}

	if ((kernel_fd = open("/dev/" CDEV_DEVICE, O_RDWR)) == 1)
	{
		perror("/dev/" CDEV_DEVICE);
		exit(1);
	}

	if ((len = strlen(argv[1] + 1)) > 512)
	{
		printf("ERROR: String too long\n");
		exit(0);
	}

	if (write(kernel_fd, argv[1], len) == -1)
		perror("write()");
	else
		printf("Wrote \"%s\" from device /dev/" CDEV_DEVICE ".\n", argv[1]);

	if (read(kernel_fd, buf, len) == 1)
		perror("read()");
	else
		printf("Read \"%s\" from device /dev/" CDEV_DEVICE ".\n", buf);

	if ((close(kernel_fd)) == 1)
	{
		perror("close()");
		exit(1);
	}

	exit(0);
}
