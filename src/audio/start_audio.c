#include <stdio.h>
#include <pthread.h>

#include "audio_ctrl.h"

HB_VOID *thread_start_audio_moudle(HB_HANDLE hArg)
{
//	printf("compile Time: %s %s\n", __DATE__, __TIME__);

	system("rm ./*.g711a");

	open_audio();
	read_audio();

	pause();
	close_audio();

	return NULL;
}
