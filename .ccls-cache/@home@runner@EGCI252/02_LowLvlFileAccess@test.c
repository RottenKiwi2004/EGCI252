#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
	int count = 0;
	char capA = 'A';
	while (1) {
		char buffer;
		int n = read(0, &buffer, sizeof(buffer));
		int fd = open("result.out", O_CREAT | O_WRONLY, 0666);
		lseek(fd, 0, SEEK_END);
		if (buffer == 'a') {
			count++;
			write(fd, &capA, sizeof(capA));
		}
		else write(fd, &buffer, sizeof(buffer));
		close(fd);
		lseek(1, 0, SEEK_SET);
		int newCount = 0, countCopy = count;
		while(countCopy) {
			newCount += countCopy % 10;
			countCopy /= 10;
		}
		system("clear");
		while(newCount) {
			char temp = '0' + newCount % 10;
			newCount /= 10;
			write(1, &temp, sizeof(temp));
		}
		
	}
}