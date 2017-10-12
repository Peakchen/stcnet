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

void stc_iocp_start();

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


