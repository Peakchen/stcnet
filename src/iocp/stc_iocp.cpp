#include "STCiocp.h"
#include <synchapi.h>
#include <ioapiset.h>
#include <winsock.h>

void stc_iocp_associate()
{
	HANDLE hresult = CreateIoCompletionPort();

}

void stc_iocp_loop(void* vp_io_port)
{
	stc_iocp_io_port* p_io_port = (stc_iocp_io_port*)vp_io_port;
	if (!p_io_port)
	{
		return;
	}

	while (true)
	{
		OVERLAPPED *poverlapped = NULL;
		ULONG_PTR key = 0;
		DWORD bytes = 0;

		int ok = GetQueuedCompletionStatus(
			p_io_port->io_port,
			&bytes, 
			&key,
			&poverlapped,
			ms);

		if (key != ULONG_PTR(-1) 
			&& poverlapped)
		{
			stc_iocp_io_overlapped_data io_overlappedData = CONTAINING_RECORD(poverlapped, stc_iocp_io_overlapped_data, io_overlapped);
			select_cb(io_overlappedData.io_msg, p_io_port->io_sync);
		}
		else if (!poverlapped)
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

stc_iocp_io_port* stc_iocp_start()
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
	return pIoport;
}

void create_io_thread(void* vp_io_port)
{
	if (!vp_io_port)
	{
		return;
	}

	stc_iocp_io_port* pport = (stc_iocp_io_port*)(vp_io_port);
	int nthreads = pport->io_threads;
	if (nthreads < 0)
	{
		return;
	}

	for (int i = 0; i < nthreads; ++i)
	{
		if (_beginthread(stc_iocp_loop, 0, pport) == (uintptr_t)-1)
			goto this_err;
	}

this_err:
	if (pport->io_port)
	{
		CloseHandle(pport->io_port);
	}

	free(pport);
	return;
}

void stc_iocp_send_cb(void* vp_io)
{

}

void stc_iocp_recv_cb(void* vp_io)
{

}

void stc_iocp_connect_cb(void* vp_io)
{

}

void stc_iocp_exit_cb(void* vp_io)
{
	stc_iocp_io_port* pio_port = (stc_iocp_io_port*)(vp_io);
	if (!pio_port)
	{
		return;
	}
	closesocket(pio_port->io_port);
}

void stc_iocp_disconnect_cb(void* vp_io)
{

}


void create_io_sock()
{
	SOCKET sock;
	if (sock = WSASocket(AF_INET, 
		SOCK_STREAM, 
		0, 
		NULL,
		0,
		WSA_FLAG_OVERLAPPED) == INVALID_SOCKET)
	{
		printf("[%s]: create sock faild.", __FUNCTION__);
		return;
	}

	SOCKADDR_IN sockaddr_in;
	sockaddr_in.sin_addr.S_un = inet_addr(LOCAL_HOST_IP);
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(LOCAL_HOST_MIN_PORT);
	if (bind(sock, (SOCKADDR*)sockaddr_in, sizeof(SOCKADDR)) != 0)
	{
		DWORD dwerror = WSAGetLastError();
		printf("[%s]: bind sock faild. error: %d.", __FUNCTION__, dwerror);
		closesocket(sock);
		return;
	}

	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("[%s]: listen sock faild.", __FUNCTION__);
		closesocket(sock);
		return;
	}
}

void register_io_cb(void* vp_io)
{
	stc_iocp_io_port* pio_port = (stc_iocp_io_port*)(vp_io);
	if (!pio_port)
	{
		return;
	}

	if (!pio_port->io_sync)
	{
		if ((pio_port->io_sync = calloc(1, sizeof(stc_iocp_io_sync))) == NULL)
		{
			return;
		}
	}

	pio_port->io_sync->io_conn = stc_iocp_connect_cb;
	pio_port->io_sync->io_exit = stc_iocp_exit_cb;
	pio_port->io_sync->io_recv = stc_iocp_recv_cb;
	pio_port->io_sync->io_send = stc_iocp_send_cb;
}


