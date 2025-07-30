// @file Flink.cpp
#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <locale>

bool verbose = false; // Флаг для включения режима вывода сообщений

// Функция для определения наличия пробелов в строке
bool hasSpaces(const std::wstring &str)
{
	return str.find(L' ') != std::wstring::npos;
}

// Функция для получения всех аргументов командной строки как единой строки
std::wstring GetCommandLineArgs()
{
	int argc;

	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if(!argv) 
		return L"";

	if(argc < 2) 
		return L"";

	if(wcscmp(argv[1], L"-v") == 0 || wcscmp(argv[1], L"/v") == 0 ||  wcscmp(argv[1], L"-V") == 0 || wcscmp(argv[1], L"/V") == 0) // Если ключ -v, то ставим флаг и начинаем с 2-го аргумента
		verbose = true;

	std::wstring result;

	for(int i = (verbose ? 2 : 1); i < argc; i++)
	{
		if(i > (verbose ? 2 : 1))
			result += L" ";
		result += argv[i];
	}
	result = L"file:\/\/" + result; // Добавляем префикс ссылки

	if(hasSpaces(result)) // Если есть пробелы
		result = L"\"" + result + L"\"";

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

	if(verbose)
	{
		//std::wcout << L"Программа Flink v.2.4 (C)RUbasic от 30.07.2025 генерирует файловые ссылки" << std::endl;
		std::wcout << L"Program Flink v.2.4 (C)RUbasic generates file links" << std::endl;
	}

	if(textToCopy.empty())
	{
		if(verbose)
		{
			//std::wcerr << L"Использование: " << GetCommandLineArgs() << L" <текст_для_копирования>" << std::endl;
			 std::wcerr << L"Using: " << GetCommandLineArgs() << L" <File or folder path>" << std::endl;
			//system("pause");
			//std::wcerr << L"Нажмите любую клавишу для выхода...";
			 std::wcerr << L"Press any key to exit...";
			_getwch();
		}
		return 1;
	}

	if(CopyToClipboard(textToCopy))
	{
		if(verbose)
		{
			//std::wcout << L"Файловая ссылка скопирована в буфер обмена: " << textToCopy << std::endl;
			std::wcout << L"File link copied to clipboard: " << textToCopy << std::endl;
		}
		return 0;
	}
	else
	{
		if(verbose)
		{
			//std::wcerr << L"Ошибка при доступе к буферу обмена!" << std::endl;
			std::wcerr << L"Clipboard access error!" << std::endl;
			// system("pause");
			//std::wcout << L"Нажмите любую клавишу для выхода...";
			std::wcerr << L"Press any key to exit...";
			_getwch();
		}
		return 1;
	}
}