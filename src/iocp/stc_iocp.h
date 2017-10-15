#pragma once

#ifndef __STC_IOCP__
#define __STC_IOCP__

/*
	func: stc_iocp_start
	purpose: ��ʼ�������׽��ֶ�̬��
*/

void stc_iocp_init();

/*
	func: stc_iocp_start
	purpose: ��ʼ����
*/

stc_iocp_io_port* stc_iocp_start();

/*
	func: stc_iocp_associate
	purpose: ������ɶ˿�
*/
void stc_iocp_associate();

/*
	func: stc_iocp_loop
	purpose: ѭ��������ȡ�������״̬
	param�� void* p_io_port
*/
void stc_iocp_loop(void* p_io_port);

/*
	func: stc_iocp_post
	purpose: Ͷ�ݶ������״̬ 
*/
void stc_iocp_post();

/*
	func: create_io_thread
	purpose: ����io�߳�  create io threads
	param: void* p_io_port
*/

void create_io_thread(void* p_io_port);

/*
	func: stc_iocp_send_cb
	purpose: complete io send callback
	param: ?
*/

void stc_iocp_send_cb(void* vp_io);

/*
	func: stc_iocp_recv_cb
	purpose: complete io recv callback
	param: ?
*/

void stc_iocp_recv_cb(void* vp_io);

/*
	func: stc_iocp_connect_cb
	purpose: 
	param: ?
*/

void stc_iocp_connect_cb(void* vp_io);

/*
func: stc_iocp_exit_cb
purpose: complete io exit callback
param: ?
*/

void stc_iocp_exit_cb(void* vp_io);

/*
func: stc_iocp_disconnect_cb
purpose: complete io disconnect callback
param: ?
*/

void stc_iocp_disconnect_cb(void* vp_io);

/*
func: create_io_sock
purpose:
param: ?
*/

void create_io_sock();

void register_io_cb(void* vp_io);