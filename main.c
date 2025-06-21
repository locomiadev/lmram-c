#include <sys/sysinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void glenda(long mib, char *buffer) {
	sprintf(buffer, "%5ld MiB", mib);
}

void rcl() {
	struct sysinfo memInfo;
	char usedBuffer[20], totalBuffer[20];

	signal(SIGINT, SIG_DFL); // выглядит как хуйня а это ctrl+c вывод питон лучше

	while (1) {
		if (sysinfo(&memInfo) == 0) {
			long used = (memInfo.totalram - memInfo.freeram) / 1024 / 1024;
			long total = memInfo.totalram / 1024 / 1024;
		
			printf("\033[H\033[J"); // этот пиздец это очистка экрана вывод питон лучше
			glenda(used, usedBuffer);
			glenda(total, totalBuffer);
			printf("[LMRAM] %s / %s\n", usedBuffer, totalBuffer);
			usleep(500000); // ахуеть это полсекунды блять
		}
	}
}

int main() {
	rcl();
	return 0;
}
