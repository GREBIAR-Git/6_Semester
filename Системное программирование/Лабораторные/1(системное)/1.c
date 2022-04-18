#include <windows.h>
#include <stdio.h>

HANDLE hThread[3];

DWORD WINAPI ThreadOneProc(LPVOID lpParam)
{
	ExitThread(0);
	return 0;
}

DWORD WINAPI ThreadTwoProc(LPVOID lpParam)
{
	ExitThread(0);
	return 0;
}

DWORD WINAPI ThreadThreeProc(LPVOID lpParam)
{
	ExitThread(0);
	return 0;
}

int main()
{
	hThread[0] = CreateThread( NULL, 0, ThreadOneProc,NULL,CREATE_SUSPENDED,NULL);
	hThread[1] = CreateThread( NULL, 0, ThreadTwoProc,NULL,CREATE_SUSPENDED,NULL);
	hThread[2] = CreateThread( NULL, 0, ThreadThreeProc,NULL,CREATE_SUSPENDED,NULL);
	int menuItem, menuItem2;
	while(TRUE)
	{
		printf("\nmenu:");
		scanf("%d",&menuItem);
		if(menuItem==0)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);
			CONTEXT ct; 
			GetThreadContext(hThread[menuItem2], &ct);
			printf("%lu",ct.ContextFlags);
		}
		else if(menuItem==1)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);

			printf("\npriority level:");
			int priority;
			scanf("%d",&priority);
			SetThreadPriority(hThread[menuItem2],priority);

		}
		else if(menuItem==2)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);
			printf("\n0-Resume, 1-suspend, 2-finish:");
			int stage;
			scanf("%d",&stage);
			if(stage==0)
			{
				ResumeThread(hThread[menuItem2]);
			}
			else if(stage == 1)
			{
				SuspendThread(hThread[menuItem2]);
			}
			else
			{
				TerminateThread(hThread[menuItem2],0);
			}
		}
		else if(menuItem==3)
		{
			printf("\nthread:");
			scanf("%d",&menuItem2);
			FILETIME creationTime,exitTime,kernelTime,userTime;
			GetThreadTimes(hThread[menuItem2],&creationTime, &exitTime,&kernelTime,&userTime); 
			SYSTEMTIME stUTC,stLocal;
			FileTimeToSystemTime(&creationTime, &stUTC); 
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal); 
			printf("Time of creation of thread %d: %02d/%02d/%d %02d:%02d:%02d\r\n\n", menuItem2+1, stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
			FileTimeToSystemTime(&exitTime, &stUTC); 
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal); 
			printf("Time of finished of thread %d: %02d/%02d/%d %02d:%02d:%02d\r\n\n", menuItem2+1, stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
		}
	}
}
