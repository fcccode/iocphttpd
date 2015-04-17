#pragma once
#include "stdafx.h"


class IOCPHTTPL_API ScannerA
{
public:
	ScannerA();
	~ScannerA();

	void Input(const CHAR* str);
	bool Accept(CHAR* str);
	CHAR* AcceptRun(CHAR* str);
	void Backup();
	const CHAR* Peek();
	const CHAR* Next();
	bool IsNumeric();
	bool IsAlphabetic();
	bool IsAlphanumeric();
	virtual bool IsEmpty();
	void SkipEmpty();
	CHAR* AcceptUntil(CHAR *str);

private:
	const CHAR* m_str;
	int m_start;
	int m_end;
	int m_pos;
	const CHAR *m_c;
	CHAR m_token[BUFSIZTOK];
};

/*
References:

1) http://cuddle.googlecode.com/hg/talk/lex.html#slide-31


*/