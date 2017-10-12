#pragma once

#ifndef __STC_IOCP_DEFINE__
#define __STC_IOCP_DEFINE__

/*
	----------------- struct ddefine -------------------
*/
struct stc_iocp_io_port
{
	HANDLE io_port;
	int io_threads;
	CRITICAL_SECTION io_lock;
};

struct stc_iocp_io_overlapped_data
{

};

/*
	 ---------------- macro define ----------------------
*/
#define THREADS_SECTION_SPINCOUNT 2000 



#endif