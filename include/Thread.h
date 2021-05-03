/*

Código de autoria do Prof. Dr. Jean M. Simão. Com permissão do mesmo para uso do código no desenvolvimento do projeto.

PS:>Talvez haja algumas mudanças

*/

#ifndef _THREAD_H_
#define _THREAD_H_

#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;

class Thread
{
private:
	pthread_t _threadID;			// pthread;
	static pthread_mutex_t _mutex;	// mutex estático;
	// atributo da thread, pode conter
	// informações sobre o funcionamento da thread;
	pthread_attr_t _tAttribute;
	// método que inicia as thread;
	static void* runThread(void* pThread);
	virtual void run();				// código para execução;
	void printError(const string msg);
public:
	Thread();
	virtual ~Thread();

	void start();					// cria a thread;
	void join();					// espera a thread acabar;
	void yield();					// libera o processador;
	void lock();
	void unlock();
};

#endif

