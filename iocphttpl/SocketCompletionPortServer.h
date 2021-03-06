#pragma once
// Link to ws2_32.lib
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#include "stdafx.h"

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpUrlRoute.h"
#include "HttpTemplate.h"
#include "SocketIocpController.h"
#include "CacheController.h"
#include "SocketCompletionPortServerWS.h"
#include "Crypt.h"
#include "Base64.h"
#include "WebSocketRoute.h"
//#define DATA_BUFSIZE 8192

namespace IOCPHTTPL
{

	class IOCPHTTPL_API SocketCompletionPortServer : public HttpUrlRoute, public WebSocketRoute
	{
	public:
		SocketCompletionPortServer();
		~SocketCompletionPortServer();

		SocketCompletionPortServer(int PortNum);

		void Start(int PortNum);

		typedef struct
		{
			OVERLAPPED Overlapped;
			WSABUF DataBuf;
			CHAR Buffer[DATA_BUFSIZE];
			byte *LPBuffer;
			vector<byte> byteBuffer;
			DWORD BytesSEND;
			DWORD BytesRECV;
		} PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

		typedef struct
		{
			SOCKET Socket;
		} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

		typedef /*static*/ void(*LPSTATICFUNC)(HttpRequest *httpRequest, HttpResponse *httpResponse);
		typedef /*static*/ void(*LPSTATICFUNCWEBSOCKET)(char* message);

		int Start();
		int Start2();

		HANDLE GetCompletionPort();
		virtual void EvalGet(HttpRequest *httpRequest, HttpResponse *httpResponse);
		virtual void EvalPost(HttpRequest *httpRequest, HttpResponse *httpResponse);
		virtual void Dispatch(HttpRequest *httpRequest, HttpResponse *httpResponse);
		virtual void EvalStatic(HttpRequest *httpRequest, HttpResponse *httpResponse);
		virtual void UrlNotFound(HttpRequest *httpRequest, HttpResponse *httpResponse);
		virtual void EvalHasUrlParams(HttpRequest *httpRequest, HttpResponse *httpResponse);

		HANDLE ghMutex;
		SocketIocpController socketIocpController;

		void DispatchWebSocket(char* message, char* reply);

	private:
		static DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);
		static DWORD WINAPI ServerWorkerThread2(LPVOID CompletionPortID);
		HANDLE CompletionPort;
		int m_PortNum = PORT;
		bool FileExist(const TCHAR *fileName);
		CacheController cacheController;

		void WebsocketInit(CHAR* buf, SOCKET socket);
		void FrameEncode(char* data, DWORD dwLen, BYTE* reply, DWORD* dwSendLen, BYTE firstByte);
		//void HandleWebsocketFrame(CHAR* databuf, SOCKET socket);
		void HandleWebsocketRequest(CHAR* databuf, SOCKET socket);
	private:
		WebSocket::SocketCompletionPortServerWS websocket;

	};


}