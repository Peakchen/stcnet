#include "STCiocp.h"
#include <synchapi.h>
#include <ioapiset.h>

void stc_iocp_associate()
{
	HANDLE hresult = CreateIoCompletionPort();

}

void stc_iocp_loop(void* p_io_port)
{
	while (true)
	{
		OVERLAPPED *overlapped = NULL;
		ULONG_PTR key = 0;
		DWORD bytes = 0;
		int ok = GetQueuedCompletionStatus(
			p_io_port->io_port,
			&bytes, 
			&key,
			&overlapped,
			ms);

		if (key != ULONG_PTR(-1) 
			&& overlapped)
		{
			OverlapPlus = CONTAINING_RECORD(overlapped, OVERLAPPEDPLUS, ol);
		}
		else if (!overlapped)
		{
			break;
		}
	}
}

void stc_iocp_post()
{
	
}

void stc_iocp_init()
{
	WORD wVerReq = MAKEWORD(2, 2);
	WSADATA wsaData;
	int error = WSAStartup(wVerReq, &wsaData);
	if (error != 0)
	{
		printf("[%s]: WSAStartup failded, error is: %d\n.", __FUNCTION__, error);
		exit(1);
	}
}

void stc_iocp_start()
{
	SYSTEM_INFO  stSystemInfo;
	GetSystemInfo(&stSystemInfo);
	int ncpus = stSystemInfo.dwNumberOfProcessors; // cpu counts

	stc_iocp_io_port *pIoport = NULL;
	if ((pIoport = calloc(1, sizeof(stc_iocp_io_port))) == NULL)
	{
		return;
	}

	pIoport->io_threads = ncpus*2;  // read and write threads
	pIoport->io_port = CreateIoCompletionPort(
		INVALID_HANDLE_VALUE,
		NULL,
		0,
		ncpus);

	create_io_thread(pIoport->io_threads);
	InitializeCriticalSectionAndSpinCount(&pIoport->lock, THREADS_SECTION_SPINCOUNT);
}

void create_io_thread(void* p_io_port)
{
	if (!p_io_port)
	{
		return;
	}

	int nthreads = p_io_port->io_threads;
	if (nthreads < 0)
	{
		return;
	}

	for (int i = 0; i < nthreads; ++i)
	{
		if (_beginthread(stc_iocp_loop, 0, p_io_port) == (uintptr_t)-1)
			goto this_err;
	}

this_err:
	if (p_io_port->io_port)
	{
		CloseHandle(p_io_port->io_port);
	}

	free(p_io_port);
}

