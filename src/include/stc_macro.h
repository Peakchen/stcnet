#pragma once

#ifndef __STC_MACRO__
#define __STC_MACRO__

/*
---------------- macro define ----------------------
*/

#define THREADS_SECTION_SPINCOUNT 2000 

#define LOCAL_HOST_IP "127.0.0.1"

#define LOCAL_HOST_MIN_PORT 10000
#define LOCAL_HOST_MAX_PORT 20000

#define select_cb(type, object) if (type == EN_STC_IOCP_SEND){ \
    object->io_send();                                      \
 }else if (type == EN_STC_IOCP_RECV){                    \
    object->io_recv();                                      \
 }else if (type == EN_STC_IOCP_CONN) {                   \
	object->io_conn();                                      \
 }else if (type == EN_STC_IOCP_CONN) {                   \
    object->io_exit();                                      \
 }
 

#endif