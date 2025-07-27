// @file Flink.cpp
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <locale>


//TODO #01 Добавить обработку длинных имен файлов с пробелами


// Функция для получения всех аргументов командной строки как единой строки
std::wstring GetCommandLineArgs()
{
	int argc;
	wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if(argc < 2) return L"";

	std::wstring result;
	for(int i = 1; i < argc; i++)
	{
		if(i > 1) result += L" ";
		result += argv[i];
	}
	result = L"file:\/\/" + result;
	if(argc > 2) result = L"\"" + result + L"\""; // Если есть пробелы

	LocalFree(argv);
	return result;
}

// Функция копирования текста в буфер обмена
bool CopyToClipboard(const std::wstring &text)
{
	if(OpenClipboard(nullptr))
	{
		EmptyClipboard();

		// Выделяем память с учетом Unicode (UTF-16)
		HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, (text.size() + 1) * sizeof(wchar_t));

		if(hClipboardData)
		{
			wchar_t *pchData = (wchar_t *)GlobalLock(hClipboardData);
			if(pchData)
			{
				wcscpy_s(pchData, text.size() + 1, text.c_str());
				GlobalUnlock(hClipboardData);
				SetClipboardData(CF_UNICODETEXT, hClipboardData);
				CloseClipboard();
				return true;
			}
			GlobalFree(hClipboardData);
		}
		CloseClipboard();
	}
	return false;
}

int wmain()
{
	// Устанавливаем локаль для корректного вывода русских символов
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	std::wcerr.imbue(std::locale());

	// Получаем аргументы командной строки
	std::wstring textToCopy = GetCommandLineArgs();

	if(textToCopy.empty())
	{
		//std::wcerr << L"Использование: " << GetCommandLineArgs() << L" <текст_для_копирования>" << std::endl;
		std::wcerr << L"Using: " << GetCommandLineArgs() << L" <File or folder path>" << std::endl;
		// system("pause");
		//std::wcerr << L"Нажмите любую клавишу для выхода...";
		std::wcerr << L"Press any key to exit...";
		_getwch();
		return 1;
	}

	if(CopyToClipboard(textToCopy))
	{
		//std::wcout << L"Текст скопирован в буфер обмена: " << textToCopy << std::endl;
		return 0;
	}
	else
	{
		//std::wcerr << L"Ошибка при открытии буфера обмена!" << std::endl;
		std::wcerr << L"Clipboard open error!" << std::endl;
		// system("pause");
		//std::wcout << L"Нажмите любую клавишу для выхода...";
		std::wcerr << L"Press any key to exit...";
		_getwch();
		return 1;
	}
}