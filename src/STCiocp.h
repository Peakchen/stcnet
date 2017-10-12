#pragma once

#ifndef __STC_IOCP__
#define __STC_IOCP__

/*
	func: stc_iocp_start
	purpose: 初始化连接套接字动态库
*/

void stc_iocp_init();

/*
	func: stc_iocp_start
	purpose: 开始启动
*/

void stc_iocp_start();

/*
	func: stc_iocp_associate
	purpose: 关联完成端口
*/
void stc_iocp_associate();

/*
	func: stc_iocp_loop
	purpose: 循环监听获取队列完成状态
	param： void* p_io_port
*/
void stc_iocp_loop(void* p_io_port);

/*
	func: stc_iocp_post
	purpose: 投递队列完成状态 
*/
void stc_iocp_post();

/*
	func: create_io_thread
	purpose: 创建io线程  create io threads
	param: void* p_io_port
*/

void create_io_thread(void* p_io_port);


