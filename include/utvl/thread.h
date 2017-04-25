/********************************************************************************
 Copyright (c) 2013-2016 Hironori Hattori. All rights reserved.

 University of Tokyo <hattorih@iis.u-tokyo.ac.jp>
 Carnegie Mellon University <hattorih@cs.cmu.edu>
---------------------------------------------------------------------------------
 $Id: $
********************************************************************************/


#ifndef __UTVL_THREAD_H__
#define __UTVL_THREAD_H__


namespace utvl
{


namespace thread
{


/**
 * @brief Thread Manager
 */
class ThreadManager
{
public:
	ThreadManager(bool MultiThread = true);
	virtual ~ThreadManager();

	void callProcessOnThread(void);
	void waitProcessOnThread(void);
	virtual void executeProcessOnThread(void) = 0;

private:
	bool mMultiThread;

	void *mHandle;
};


/**
 * @brief Thread Manager Sample1
 */
class ThreadManagerSample1 : public ThreadManager
{
public:
	ThreadManagerSample1(bool MultiThread = true);

	~ThreadManagerSample1();

private:
	void executeProcessOnThread(void);
};


/**
 * @brief Thread Manager Sample2
 */
class ThreadManagerSample2 : public ThreadManager
{
public:
	ThreadManagerSample2(bool MultiThread = true);

	~ThreadManagerSample2();

private:
	void executeProcessOnThread(void);
};


} // namespace thread


} // namespace utvl


#endif // __UTVL_THREAD_H__

