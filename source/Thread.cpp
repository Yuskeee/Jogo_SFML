#include "Thread.h"

// referência para a variável estática;
pthread_mutex_t Thread::_mutex = NULL;

Thread::Thread()	{	}

Thread::~Thread()
{
	if ( NULL != Thread::_mutex )
		pthread_mutex_destroy( &Thread::_mutex );
}

void Thread::run()	{	}

void Thread::yield()
{
	sched_yield();
}

void Thread::start()
{
	// inicia o atributo;
	int status = pthread_attr_init( &_tAttribute );
	status = pthread_attr_setscope( &_tAttribute,
									PTHREAD_SCOPE_SYSTEM );
	if ( status != 0)
		printError("falha ao iniciar atributo da thread.");

	// cria uma thread;
	status = pthread_create( &_threadID, &_tAttribute,
							 Thread::runThread, (void*)this);
	if ( status != 0)
		printError("falha ao iniciar a thread.");

	// destrói o atributo;
	status = pthread_attr_destroy( &_tAttribute );
	if ( status != 0)
		printError("falha ao destruir atributo da thread.");
}

void Thread::join()
{
	int status = pthread_join( _threadID, NULL );
	if ( status != 0)
		printError("comando join falhou.");
}

void* Thread::runThread(void* pThread)
{
	Thread* sThread = static_cast<Thread*> (pThread);

	if ( NULL == sThread ){ cout << "thread falhou." <<endl;	}
	else {    sThread->run();  /* executa a thread; */			}
}

void Thread::lock()
{
	if ( NULL == Thread::_mutex )
		pthread_mutex_init( &Thread::_mutex, NULL );

	pthread_mutex_lock( &Thread::_mutex );
}

void Thread::unlock()
{
	if ( NULL != Thread::_mutex )
		pthread_mutex_unlock( &Thread::_mutex );
}

void Thread::printError(const string msg)
{
	lock();     // pára para a mensagem;
	cout << "Erro: " << msg << endl;
	unlock();
}
