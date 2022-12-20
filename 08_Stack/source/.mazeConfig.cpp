// Maze Config

#include <Windows.h>
#include <iostream>


// Change and fix the size of cmd window.
void windowConfig() {
	// Change the size of cmd window.
	system("mode con cols=100 lines=30");
	// Fix the size of cmd window.
	// Get the Handle of cmd window.
	HWND hWnd = GetConsoleWindow();
	RECT rc;
	// Get the square of cmd window.
	GetWindowRect(hWnd, &rc);
	// Change the style of cmd window.
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	// The change involves changes of border, so SetWindowPos must be invoked, otherwise invalid.
	SetWindowPos(hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, NULL);
}

/*
* Use string in switch/case:
* https://blog.csdn.net/canguanxihu/article/details/45640999#:~:text=%E5%A6%82%E6%9E%9C%E4%BD%A0%20%E4%BD%BF%E7%94%A8%20C%E8%AF%AD%E9%9F%B3%E7%9A%84%20string%20%EF%BC%8C%E4%B9%9F%E5%B0%B1%E6%98%AFchar%20%2A%EF%BC%8C%E6%98%AF%E5%8F%AF%E4%BB%A5%E6%94%BE%E5%9C%A8%20switch%20%2F,a%20switch%20in%20C%2B%2B%20-%20Stack%20Overflow%20%E4%BD%A0%E9%9C%80%E8%A6%81%E6%8A%8A%E5%AD%97%E7%AC%A6%E4%B8%B2%E8%BD%AC%E6%8D%A2%E4%B8%BA%E6%95%B4%E6%95%B0
*/
typedef std::uint64_t hash_t;
constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;
// Define function hash_() to calculate the hash value of a string, and convert it to an integer.
hash_t hash_(char const* str) {
	hash_t ret{ basis };
	while (*str) {
		ret ^= *str;
		ret *= prime;
		str++;
	}
	return ret;
}
// Use the C++11's user defined literals.
// Define a constexpr function which is invoked by switch's case lable.
constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis) {
	// Compiler can get a string's hash value while compiling, which is a const integer.
	if (*str) {
		return hash_compile_time(str + 1, (*str ^ last_value) * prime);
	}
	return last_value;
}
// Operator overload.
constexpr unsigned long long operator "" _hash(char const* p, size_t) {
	return hash_compile_time(p);
}

void textOutput(const char* text, const char* font, bool fI, const char* background, bool bI) {
	int fontIntensity = NULL, backgroundIntensity = NULL;
	if (fI) fontIntensity = FOREGROUND_INTENSITY;
	if (bI) backgroundIntensity = BACKGROUND_INTENSITY;

	int fontColor[3] = { NULL,NULL,NULL },
		backgroundColor[3] = { NULL,NULL,NULL };
	// Set font color
	switch (hash_(font)) {
	case "blue"_hash: { fontColor[0] = FOREGROUND_BLUE; break; }
	case "green"_hash: { fontColor[0] = FOREGROUND_GREEN; break; }
	case "red"_hash: { fontColor[0] = FOREGROUND_RED; break; }
	case "yellow"_hash: { fontColor[0] = FOREGROUND_RED; fontColor[1] = FOREGROUND_GREEN; break; }
	case "pink"_hash: { fontColor[0] = FOREGROUND_RED; fontColor[1] = FOREGROUND_BLUE; break; }
	case "cyan"_hash: { fontColor[0] = FOREGROUND_BLUE; fontColor[1] = FOREGROUND_GREEN; break; }
	case "white"_hash:{ fontColor[0] = FOREGROUND_BLUE; fontColor[1] = FOREGROUND_GREEN; fontColor[2] = FOREGROUND_RED; break; }
	default: { fontColor[0] = FOREGROUND_BLUE; fontColor[1] = FOREGROUND_GREEN; fontColor[2] = FOREGROUND_RED; break; }
	}
	// Set background color
	switch (hash_(background))
	{
	case "blue"_hash: { backgroundColor[0] = BACKGROUND_BLUE; break; }
	case "green"_hash: { backgroundColor[0] = BACKGROUND_GREEN; break; }
	case "red"_hash: { backgroundColor[0] = BACKGROUND_RED; break; }
	case "yellow"_hash: { backgroundColor[0] = BACKGROUND_RED; backgroundColor[1] = BACKGROUND_GREEN; break; }
	case "pink"_hash: { backgroundColor[0] = BACKGROUND_RED; backgroundColor[1] = BACKGROUND_BLUE; break; }
	case "cyan"_hash: { backgroundColor[0] = BACKGROUND_BLUE; backgroundColor[1] = BACKGROUND_GREEN; break; }
	case "white"_hash:{ backgroundColor[0] = BACKGROUND_BLUE; backgroundColor[1] = BACKGROUND_GREEN; backgroundColor[2] = BACKGROUND_RED; break; }
	default: { break; }
	}
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		fontIntensity | fontColor[0] | fontColor[1] | fontColor[2] |
		backgroundIntensity | backgroundColor[0] | backgroundColor[1] | backgroundColor[2]
	);
	std::cout << text;
}
void textOutput(const char* text, const char* font, const char* background) {
	textOutput(text, font, true, background, false);
}
void textOutput(const char* text, const char* font) {
	textOutput(text, font, true, "", false);
}
void textOutput(const char* text) {
	textOutput(text, "", true, "", false);
}

/*
* Click and drag.
* https://blog.csdn.net/wangxun20081008/article/details/113915805
*/
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
void lClick(POINT& coor, bool ifloop) {
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);

	// The location of mouse.
	POINT p;
	// Foreground window.
	HWND h = GetForegroundWindow();
	// Output handle.
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	// Consloe font.
	CONSOLE_FONT_INFO consoleCurrentFont;
	// flag shows whether user has left-clicked.
	bool flag = false;
	while (1) {
		if (KEY_DOWN(VK_LBUTTON)) {
			// left-clicked.
			flag = true;
		}
		else {
			if (flag) {
				// left-clicked and loosen.
				// Get the location of mouse.
				GetCursorPos(&p);
				ScreenToClient(h, &p);
				// Get font information.
				GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont);
				// Calculate coordinate.
				coor.x = p.x /= consoleCurrentFont.dwFontSize.X;
				coor.y = p.y /= consoleCurrentFont.dwFontSize.Y;
				std::cout << " " << coor.x << " " << coor.y;
				if (!ifloop) {
					break;
				}
				flag = false;
			}
		}
		Sleep(100);
	}
}