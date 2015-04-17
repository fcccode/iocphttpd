#include "stdafx.h"
#include "CppUnitTest.h"
#include "ScannerA.h"


extern "C" {
#include "wparser.tab.h"
}

extern void ww_parse_it();

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestNative
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ScannerA scanner;
			scanner.Input("GET /test HTTP/1.1\r\n\r\n");
			bool b1 = scanner.Accept("G");
			scanner.Next();
			bool b2 = scanner.Accept("E");
			scanner.Next();
			bool b3 = scanner.Accept("T");
		}

		TEST_METHOD(TestMethod2)
		{
			ScannerA scanner;
			scanner.Input("GET /test HTTP/1.1\r\n\r\n");
			CHAR *c1 = scanner.AcceptRun("GET");
			CHAR *d1 = _strdup(c1);
			printf("%s/n", d1);
			scanner.SkipEmpty();
			CHAR *c2 = scanner.AcceptRun("\/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_");
			CHAR *d2 = _strdup(c2);
			printf("%s/n", d2);
			scanner.SkipEmpty();
			CHAR *c3 = scanner.AcceptRun("\/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_.0123456789");
			CHAR *d3 = _strdup(c3);
			printf("%s/n", d3);
			free(d1);
			free(d2);
			free(d3);
		}


		TEST_METHOD(TestMethod3)
		{
			ww_parse_it();
		}

		TEST_METHOD(TestMethod4)
		{
			std::string str = "	GET /tutorials/other/top-20-mysql-best-practices/ HTTP/1.1 \n\
								Host: net.tutsplus.com \n\
								User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.5) Gecko/20091102 Firefox/3.5.5 (.NET CLR 3.5.30729) \n\
								Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8 \n\
								Accept-Language: en-us,en;q=0.5 \n\
								Accept-Encoding: gzip,deflateAccept-Encoding: gzip,deflate; \n\
								Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7 \n\
								Keep-Alive: 300 \n\
								Connection: keep-alive \n\
								Cookie: PHPSESSID=r2t5uvjq435r4q7ib3vtdjq120 \n\
								Pragma: no-cache \n\
								Cache-Control: no-cache \n\
								\n\
								\n\
				";

			ParseHeader parser;

			parser.Input(str.c_str());
			parser.Parse();
		}


	};
}