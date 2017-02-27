#include "Thread.h"


int main (int argc, char **argv)
{
	bool multithread = true;

	utvl::thread::ThreadManagerSample1 th1(multithread);
	utvl::thread::ThreadManagerSample2 th2(multithread);

	th1.callProcessOnThread();
	th2.callProcessOnThread();

	th1.waitProcessOnThread();
	th2.waitProcessOnThread();

	return 0;
}

