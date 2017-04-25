/********************************************************************************
 Copyright (c) 2013-2016 Hironori Hattori. All rights reserved.

 University of Tokyo <hattorih@iis.u-tokyo.ac.jp>
 Carnegie Mellon University <hattorih@cs.cmu.edu>
---------------------------------------------------------------------------------
 $Id: $
********************************************************************************/


#include "utvl/thread.h"

#define USE_PTHREADS

#include <stdio.h>
#include <stdlib.h>

#if defined (_WIN32)
#include <windows.h> // Multi Thread, Sleep
#endif

#if defined (USE_PTHREADS)
#include "pthread.h"
#else
#if defined (_WIN32)
#include <process.h> // Multi Thread
#endif
#endif


namespace utvl
{

namespace thread
{


/**
 * @brief Thread Manager
 */
#if defined (USE_PTHREADS)
void *process(void *parameter)
{
	((ThreadManager *)parameter)->executeProcessOnThread();

	return 0; // Dammy Return Value for Compile Warning
}
#else
#if defined (_WIN32)
unsigned __stdcall process(void *parameter)
{
	((ThreadManager *)parameter)->executeProcessOnThread();
	_endthreadex(0); // Return Value

	return 0; // Dammy Return Value for Compile Warning
}
#endif
#endif


ThreadManager::ThreadManager(bool MultiThread) :
mMultiThread(MultiThread), mHandle(NULL)
{
	printf("<ThreadManager/>\n");
}


ThreadManager::~ThreadManager()
{
	printf("</ThreadManager>\n");
}


void ThreadManager::callProcessOnThread(void)
{
	if (mMultiThread)
	{
#if defined (USE_PTHREADS)
		mHandle = new pthread_t;
		pthread_create((pthread_t *)mHandle, NULL, process, (void*)(this));
#else
#if defined (_WIN32)
		mHandle = (void *)_beginthreadex(NULL, 0, process, (void*)(this), 0, NULL);
#endif
#endif
	}
	else
	{
		executeProcessOnThread();
	}
}


void ThreadManager::waitProcessOnThread(void)
{
	if (mMultiThread)
	{
		if (mHandle != NULL)
		{
#if defined (USE_PTHREADS)
			pthread_join(*((pthread_t *)mHandle), NULL);
			delete mHandle;

			mHandle = NULL;
#else
#if defined (_WIN32)
			WaitForSingleObject((HANDLE)mHandle, INFINITE);
			CloseHandle((HANDLE)mHandle);

			mHandle = NULL;
#endif
#endif
		}
	}
	else
	{
		;
	}
}


/**
 * @brief Thread Manager Sample1
 */
ThreadManagerSample1::ThreadManagerSample1(bool MultiThread) :
ThreadManager(MultiThread)
{
	printf("<ThreadManager1/>\n");
}


ThreadManagerSample1::~ThreadManagerSample1()
{
	waitProcessOnThread();

	printf("</ThreadManager1>\n");
}


void ThreadManagerSample1::executeProcessOnThread(void)
{
	for (int i = 0; i < 10; i++)
	{
		printf("This process is on sample1. (%d)\n", i);
#if defined (_WIN32)
		Sleep(1000);
#endif
	}
}


/**
 * @brief Thread Manager Sample2
 */
ThreadManagerSample2::ThreadManagerSample2(bool MultiThread) :
ThreadManager(MultiThread)
{
	printf("<ThreadManager2/>\n");
}


ThreadManagerSample2::~ThreadManagerSample2()
{
	waitProcessOnThread();

	printf("</ThreadManager2>\n");
}


void ThreadManagerSample2::executeProcessOnThread(void)
{
	for (int i = 0; i < 100; i++)
	{
		printf("This process is on sample2. (%d)\n", i);
#if defined (_WIN32)
		Sleep(100);
#endif
	}
}


} // namespace Thread


} // namespace utvl

