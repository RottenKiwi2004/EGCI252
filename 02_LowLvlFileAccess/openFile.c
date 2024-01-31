#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

	open("file.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

}
