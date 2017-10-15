#pragma once
#include "stc_enum.h"
#include "stc_func_callback.h"
#include "stc_macro.h"

#ifndef __STC_IOCP_DEFINE__
#define __STC_IOCP_DEFINE__


/*
	----------------- struct define -------------------
*/
struct stc_iocp_io_port
{
	HANDLE io_port;
	int io_threads;
	CRITICAL_SECTION io_lock;
	stc_iocp_io_sync* io_sync;
};

struct stc_iocp_io_overlapped_data
{
	OVERLAPPED  io_overlapped;
	stc_iocp_io_custom_message io_msg;
	SOCKET  io_sock;
	WSABUF  io_buffer;
	select_cb(stc_iocp_io_custom_message, stc_iocp_io_sync*);
};

struct stc_iocp_io_event
{
	OVERLAPPED  io_overlapped;
	io_event_callback cb;
};

struct stc_iocp_io_sync
{
	stc_iocp_io_event *io_send;
	stc_iocp_io_event *io_recv;
	stc_iocp_io_event *io_conn;
	stc_iocp_io_event *io_exit;
	stc_iocp_io_sync() {
		io_send = nullptr;
		io_recv = nullptr;
		io_conn = nullptr;
		io_exit = nullptr;
	}
};

#endif