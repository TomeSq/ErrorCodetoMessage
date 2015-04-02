// ErrorCodetoMessage.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

#include <Windows.h>
#include <stdio.h>
#include <locale.h>
#include <string>


void ErrorCodetoMessage(DWORD code, DWORD langId, std::wstring& message)
{
	LPWSTR lpMessageBuffer=NULL;

	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, code, langId, (LPWSTR)&lpMessageBuffer, 0, NULL);

	if(lpMessageBuffer != NULL){
		message = std::wstring(lpMessageBuffer);
		LocalFree(lpMessageBuffer);
		lpMessageBuffer = NULL;
	} else{
		message = L"";
	}
}


int _tmain(int argc, wchar_t* argv[])
{
	_wsetlocale( LC_ALL, L"Japanese");

	DWORD code=0;

	if(argc < 2){
		wprintf(L"ErrorCodetoMessage.exe HexErrorCode\r\n");
		return 1;
	}

	code = wcstoul(argv[1], NULL, 16);

	// ���{��Ŏ擾
	std::wstring jpMessage;
	ErrorCodetoMessage(code, MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN), jpMessage);

	// �p��Ŏ擾
	std::wstring usMessage;
	ErrorCodetoMessage(code, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), usMessage);

	int jpLength = jpMessage.length();
	int usLength = usMessage.length();

	// �ϊ����ł��ĂȂ�������G���[���o��
	if(jpLength <= 0 && usLength <= 0){
		wprintf(L"Errocode Not Found!!!\r\n");
		return 1;
	}

	wprintf(L"0x%X\r\n", code);
	wprintf(L"%s", jpMessage.c_str());
	wprintf(L"%s", usMessage.c_str());

	return 0;
}

