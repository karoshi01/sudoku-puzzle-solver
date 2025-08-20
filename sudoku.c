#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);


TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int sudoku[9][9];
int originalSudoku[9][9];
int solvedCells[9][9];


int checkRules(int i, int j, int value, int sudokuP[9][9])
{
    for (int c = 0; c < 9; c++)
        if (c != j && value == sudokuP[i][c]) return 0;

    for (int r = 0; r < 9; r++)
        if (r != i && value == sudokuP[r][j]) return 0;

    int startRow = (i / 3) * 3;
    int startCol = (j / 3) * 3;
    for (int row = startRow; row < startRow + 3; row++)
        for (int col = startCol; col < startCol + 3; col++)
            if ((row != i || col != j) && value == sudokuP[row][col])
                return 0;

    return 1;
}

int solveSudoku(int sudoku[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0)
            {
                for (int value = 1; value <= 9; value++)
                {
                    if (checkRules(i, j, value, sudoku))
                    {
                        sudoku[i][j] = value;
                        if (solveSudoku(sudoku)) return 1;
                        sudoku[i][j] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}


int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(46, 43, 43));

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
        0,
        szClassName,
        _T("Sudoku Solver"),
        WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        544,
        775,
        HWND_DESKTOP,
        NULL,
        hThisInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HFONT hFont;

    switch (message)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rect;
            GetClientRect(hwnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;

            int squareSize = 450;
            int x = (width - squareSize) / 2;
            int y = (height - squareSize) / 2;

            HBRUSH hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            RECT squareRect = { x, y, x + squareSize, y + squareSize };
            FillRect(hdc, &squareRect, hBrush);

            HPEN hThinPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            HPEN hThickPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
            int cellSize = squareSize / 9;

            for (int i = 0; i <= 9; i++)
            {
                HPEN hPen = (i % 3 == 0) ? hThickPen : hThinPen;
                HPEN hOld = (HPEN)SelectObject(hdc, hPen);
                MoveToEx(hdc, x + i * cellSize, y, NULL);
                LineTo(hdc, x + i * cellSize, y + squareSize);
                SelectObject(hdc, hOld);
            }

            for (int i = 0; i <= 9; i++)
            {
                HPEN hPen = (i % 3 == 0) ? hThickPen : hThinPen;
                HPEN hOld = (HPEN)SelectObject(hdc, hPen);
                MoveToEx(hdc, x, y + i * cellSize, NULL);
                LineTo(hdc, x + squareSize, y + i * cellSize);
                SelectObject(hdc, hOld);
            }

            DeleteObject(hThinPen);
            DeleteObject(hThickPen);
            EndPaint(hwnd, &ps);
        }
        break;

        case WM_CREATE:
        {
            int squareSize = 450;
            RECT rect;
            GetClientRect(hwnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            int x = (width - squareSize) / 2;
            int y = (height - squareSize) / 2;
            int cellSize = squareSize / 9;

            hFont = CreateFont(
                45, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Segoe UI")
            );


            for (int row = 0; row < 9; row++)
            {
                for (int col = 0; col < 9; col++)
                {
                    int cellX = x + col * cellSize;
                    int cellY = y + row * cellSize;

                    HWND hEdit = CreateWindowEx(
                        0,
                        _T("EDIT"),
                        _T(""),
                        WS_CHILD | WS_VISIBLE | ES_CENTER | ES_NUMBER,
                        cellX + 1, cellY + 1, cellSize - 2, cellSize - 2,
                        hwnd,
                        (HMENU)(1000 + row * 9 + col),
                        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                        NULL
                    );

                    SendMessage(hEdit, EM_SETLIMITTEXT, (WPARAM)1, 0);
                    SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
                }
            }

            CreateWindow(
                _T("BUTTON"),
                _T("Solve"),
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200, 650, 150, 40,
                hwnd,
                (HMENU)1,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            HWND hTitle = CreateWindow(
                _T("STATIC"),
                _T("Sudoku Solver"),
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                100, 20, 350, 80,
                hwnd,
                (HMENU)2,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            HWND hSubtitle = CreateWindow(
                _T("STATIC"),
                _T("by karoshi.executable"),
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                150, 65, 250, 30,
                hwnd,
                (HMENU)3,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
                NULL
            );

            HFONT hTitleFont = CreateFont(
                60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
                _T("Segoe UI")
            );

            HFONT hSubtitleFont = CreateFont(
                30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
                _T("Segoe UI")
            );

            SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);
            SendMessage(hSubtitle, WM_SETFONT, (WPARAM)hSubtitleFont, TRUE);
        }
        break;

        case WM_CTLCOLOREDIT:
        {
            HDC hdcEdit = (HDC)wParam;
            HWND hCtrl = (HWND)lParam;

            int id = GetDlgCtrlID(hCtrl);
            if (id >= 1000 && id < 1000 + 81)
            {
                int row = (id - 1000) / 9;
                int col = (id - 1000) % 9;

                if (solvedCells[row][col])
                    SetTextColor(hdcEdit, RGB(0, 102, 51));
                else
                    SetTextColor(hdcEdit, RGB(0, 0, 0));

                SetBkColor(hdcEdit, RGB(255, 255, 255));
                return (INT_PTR)GetStockObject(WHITE_BRUSH);
            }
        }
        break;

        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC)wParam;
            HWND hCtrl = (HWND)lParam;
            int ctrlId = GetDlgCtrlID(hCtrl);

            SetBkMode(hdcStatic, TRANSPARENT);

            if (ctrlId == 2)
                SetTextColor(hdcStatic, RGB(255, 255, 255));
            else if (ctrlId == 3)
                SetTextColor(hdcStatic, RGB(180, 180, 180));

            return (INT_PTR)GetStockObject(HOLLOW_BRUSH);
        }
        break;

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 1:
                {
                    for (int r = 0; r < 9; r++)
                        for (int c = 0; c < 9; c++)
                            solvedCells[r][c] = 0;

                    for (int row = 0; row < 9; row++)
                        for (int col = 0; col < 9; col++)
                        {
                            HWND hEdit = GetDlgItem(hwnd, 1000 + row * 9 + col);
                            TCHAR buffer[2] = _T("");
                            GetWindowText(hEdit, buffer, 2);

                            int value = _ttoi(buffer);
                            sudoku[row][col] = value;
                            originalSudoku[row][col] = value;
                        }

                    if (solveSudoku(sudoku))
                    {
                        for (int row = 0; row < 9; row++)
                            for (int col = 0; col < 9; col++)
                            {
                                HWND hEdit = GetDlgItem(hwnd, 1000 + row * 9 + col);
                                TCHAR buffer[2];
                                wsprintf(buffer, _T("%d"), sudoku[row][col]);
                                SetWindowText(hEdit, buffer);

                                if (originalSudoku[row][col] == 0)
                                    solvedCells[row][col] = 1;
                            }
                    }
                    else
                        MessageBox(hwnd, _T("No solution exists!"), _T("Error"), MB_OK | MB_ICONERROR);
                }
                break;
            }
            break;
        }

        case WM_DESTROY:
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
