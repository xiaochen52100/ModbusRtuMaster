#include <stdio.h>
#include <stdint.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#include <Ws2tcpip.h>
#include <STDIO.H>
#include "MobusRtuMaster.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main()
{
	int len = 0;
	int rep = 0;
	uint8_t send_data[128] = { 0 };
	uint16_t write_data[32]= { 0 };
	uint32_t write_data_uint32[8] = { 0 };
	uint8_t rcv_data[32] = { 0 };
	int32_t holding_register[2] = {0};

	//初始化socket客户端
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 0;
	}

	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(9000);
	serAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.103");
	//inet_pton(AF_INET,"192.168.0.103",&serAddr.sin_addr.S_un.S_addr);
	if (connect(sclient, (struct sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error !\r\n");
		closesocket(sclient);
		return 0;
	}
	printf("connect success !\r\n");
	//清零
	memset(send_data, 0, sizeof(send_data));
	write_data[0] = 1;
	len = write_mudbus_holding_register_massage_uint16(send_data, 1, 66, 1, write_data);	//写入清零打包
	//for (int i = 0; i < len; i++)
	//{
	//	printf("%02x ", send_data[i]);
	//}
	//printf("\r\n ");
	send(sclient, send_data, len, 0);	//socket发送数据
	memset(rcv_data, 0, sizeof(rcv_data));
	len = recv(sclient, rcv_data, sizeof(rcv_data), 0);	//socket接受数据
	rep = write_mudbus_holding_register_reply(rcv_data, len, 1);
	if (rep==0)
	{
		printf("reset zero success\r\n");
	}

	Sleep(1000);

	//皮重清零
	memset(send_data, 0, sizeof(send_data));
	write_data_uint32[0] = 0;
	len = write_mudbus_holding_register_massage_int32(send_data, 1, 54, 2, write_data_uint32);	//写入皮重打包
	//for (int i = 0; i < len; i++)
	//{
	//	printf("%02x ", send_data[i]);
	//}
	//printf("\r\n ");
	send(sclient, send_data, len, 0);	//socket发送数据
	memset(rcv_data, 0, sizeof(rcv_data));
	len = recv(sclient, rcv_data, sizeof(rcv_data), 0);	//socket接受数据
	rep =write_mudbus_holding_register_reply(rcv_data, len, 1);
	if (rep == 0)
	{
		printf("reset skin success\r\n");
	}

	for (int i = 0; i < 100; i++)
	{
		memset(send_data, 0, sizeof(send_data));
		len = read_mudbus_holding_register_massage(send_data, 1, 64, 2);	//读重量数据打包
		//for (int i = 0; i < len; i++)
		//{
		//	printf("%02x ", send_data[i]);
		//}
		//printf("\r\n ");
		send(sclient, send_data, len, 0);	//socket发送数据

		memset(rcv_data, 0, sizeof(rcv_data));
		len = recv(sclient, rcv_data, sizeof(rcv_data), 0);	//socket接受数据
		//for (int i = 0; i < len; i++)
		//{
		//	printf("%02x ", rcv_data[i]);
		//}
		//printf("\r\n ");

		analysis_read_recevice_to_int32(rcv_data, len, 1, holding_register);	//解析重量
		printf("%f g\r\n ", holding_register[0] / 10.0);
		Sleep(1000);
	}

	closesocket(sclient);
	WSACleanup();

	//memset(send_data, 0, sizeof(send_data));
	//memset(write_data, 0, sizeof(write_data));
	//write_data[0] = 100;
	//len = write_mudbus_holding_register_massage_uint16(send_data, 1, 0x45, 1, write_data);	//放置砝码 100g打包
	//for (int i = 0; i < len; i++)
	//{
	//	printf("%02x ", send_data[i]);
	//}
	//printf("\r\n ");
	//memset(send_data, 0, sizeof(send_data));
	//memset(write_data, 0, sizeof(write_data));
	//len=write_mudbus_holding_register_massage_char(send_data,1,0,16, send_char);	//设置WIFI名称打包
	//for (int i = 0; i < len; i++)
	//{
	//	printf("%02x ", send_data[i]);
	//}
	//printf("\r\n ");
	//memset(send_data, 0, sizeof(send_data));
	//write_data_uint32[0] = 10;
	//len = write_mudbus_holding_register_massage_int32(send_data, 1, 54, 2, write_data_uint32);	//写入皮重打包
	//for (int i = 0; i < len; i++)
	//{
	//	printf("%02x ", send_data[i]);
	//}
	//printf("\r\n ");
	//memset(holding_register, 0, sizeof(holding_register));
	//analysis_read_recevice_to_int32(rcv_data, 9, 1, holding_register);	//解析重量
	//printf("%d\r\n ", holding_register[0]);

	//memset(send_data, 0, sizeof(send_data));
	//len = read_mudbus_holding_register_massage(send_data, 1, 0, 12);	//读WIFI名称打包
	//for (int i = 0; i < len; i++)
	//{
	//	printf("%02x ", send_data[i]);
	//}
	//printf("\r\n ");

	//memset(holding_register_char, 0, sizeof(holding_register_char));
	//analysis_read_recevice_to_char(rcv_char, 29, 1, holding_register_char);	//解析WIFI名称
	//printf("%s\r\n", holding_register_char);
	

}