//#include <vld.h>
//#include "Win32Api_MetalSlug.h"
#include "stdafx.h"
#define MAX_LOADSTRING 100

HINSTANCE hInst;                               
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];           

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//for Core
HWND g_hWnd;



// Console Print
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //Memory leak Check!
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(276);


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32APIMETALSLUG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APIMETALSLUG));
    MSG msg;

    // Main
    CCore::GetInst()->Init(g_hWnd);
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            CCore::GetInst()->Progress();
        }
    }
    CCore::GetInst()->Release();
    CCore::GetInst()->DestroyInst();

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APIMETALSLUG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_WIN32APIMETALSLUG); // NULL : 메뉴바 없음 MAKEINTRESOURCE(IDC_WIN32APIMETALSLUG) : 메뉴바 있음
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

 
   HWND hWnd = CreateWindowW(szWindowClass, L"MetalSlug3", WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   // for Core
   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


static HWND g_hDlg;
LRESULT CALLBACK DigProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);

            // =========== ANITOOL 1 ========== //
            case ID_ANITOOL1_LOAD:
            {
                CInputMgr::GetInst()->BlockInput();
                CCamera::GetInst()->BlockUpdate();
                g_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_ANITOOL1_LOAD), hWnd, DigProc);  // texture\Tarma.bmp 입력 
                ShowWindow(g_hDlg, SW_SHOW);
                break;
            }
            case ID_ANITOOL1_SAVE:
            {
                CInputMgr::GetInst()->BlockInput();
                CCamera::GetInst()->BlockUpdate();
                g_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_ANITOOL1_SAVE), hWnd, DigProc); // animation\TARMA_PISTOL_BASIC_MOVE_ST.frame 입력 
                ShowWindow(g_hDlg, SW_SHOW);
                break;
            }
            case ID_ANITOOL1_CHANGE_STATE:
            {
                CInputMgr::GetInst()->BlockInput();
                CCamera::GetInst()->BlockUpdate();
                g_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_ANITOOL1_CHANGE_STATE), hWnd, DigProc);  
                ShowWindow(g_hDlg, SW_SHOW);
                break;
            }
            case ID_ANITOOL1_CHANGE_BODY:
            {
                CInputMgr::GetInst()->BlockInput();
                CCamera::GetInst()->BlockUpdate();
                g_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_ANITOOL1_CHANGE_BODY), hWnd, DigProc);  
                ShowWindow(g_hDlg, SW_SHOW);
                break;
            }
            // =========== ANITOOL 2 ========== //
            case ID_ANITOOL2_LOAD:
            {
                CInputMgr::GetInst()->BlockInput();
                CCamera::GetInst()->BlockUpdate();
                g_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_ANITOOL2_LOAD), hWnd, DigProc);
                ShowWindow(g_hDlg, SW_SHOW);
                break;
            }
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    // for Debug
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK DigProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            break;
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                // =========== ANITOOL 1 ========== //
                case IDC_BTN_ANITOOL1_LOAD:
                {
                    //TCHAR tchFile[BSIZE]{};
                    //GetDlgItemText(hDlg, IDC_EDIT_ANITOOL1_LOAD_FILE, tchFile, BSIZE);
                    //wstring wstrFile(&tchFile[0]); // texture\Tarma.bmp 입력


                    //TCHAR tchKeyName[BSIZE]{};
                    //GetDlgItemText(hDlg, IDC_EDIT_ANITOOL1_LOAD_KEYNAME, tchKeyName, BSIZE);
                    //wstring wstrKeyName(&tchKeyName[0]);


                    // 자동 로드
                    wstring wstrKeyName = L"texture\\Tarma.bmp";
                    wstring wstrFile = L"Tarma";


                    dynamic_cast<CAniToolScene1*>(CSceneMgr::GetInst()->GetCurScene())->SetTexture(wstrKeyName, wstrFile);

                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
                case IDC_BTN_ANITOOL1_SAVE:
                {
                    TCHAR tchTemp[BSIZE]{};
                    GetDlgItemText(hDlg, IDC_EDIT_ANITOOL1_SAVE, tchTemp, BSIZE);
                    wstring wstrTemp(&tchTemp[0]); 

                    dynamic_cast<CAniToolScene1*>(CSceneMgr::GetInst()->GetCurScene())->SaveMapFrame(wstrTemp);
                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
                case IDC_BTN_CHANGE_STATE:
                {
                    TCHAR tchTemp[BSIZE]{};
                    GetDlgItemText(hDlg, IDC_EDIT_ANITOOL1_CHANGE_STATE, tchTemp, BSIZE);
                    wstring wstrTemp(&tchTemp[0]);

                    dynamic_cast<CAniToolScene1*>(CSceneMgr::GetInst()->GetCurScene())->SetCurState(wstrTemp);
                    dynamic_cast<CAniToolScene1*>(CSceneMgr::GetInst()->GetCurScene())->PushbackState(wstrTemp);
                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
                case IDC_RADIO_ANITOOL1_CHANGE_BODY_TOP:
                {
                    dynamic_cast<CAniToolScene1*>(CSceneMgr::GetInst()->GetCurScene())->SetCurbody(BODY_TYPE::TOP);
                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
                case IDC_RADIO_ANITOOL1_CHANGE_BODY_BOT:
                {
                    dynamic_cast<CAniToolScene1*>(CSceneMgr::GetInst()->GetCurScene())->SetCurbody(BODY_TYPE::BOT);
                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
                // =========== ANITOOL 2 ========== //
                case IDC_BTN_ANITOOL2_LOAD:
                {
                   /* TCHAR tchPath[BSIZE]{};
                    TCHAR tchKeyName[BSIZE]{};
                    TCHAR tchDat[BSIZE]{};

                    GetDlgItemText(hDlg, IDC_EDIT_ANITOOL2_LOAD_PATH, tchPath, BSIZE);
                    wstring wstrTexPath(&tchPath[0]);
                    GetDlgItemText(hDlg, IDC_EDIT_ANITOOL2_LOAD_NAME, tchKeyName, BSIZE);
                    wstring wstrKeyName(&tchKeyName[0]);
                    GetDlgItemText(hDlg, IDC_EDIT_ANITOOL2_LOAD_DAT, tchDat, BSIZE);
                    wstring wstrDatPath(&tchDat[0]);*/

                    // 자동 로드 설정 
                    wstring wstrTexPath = L"texture\\Tarma.bmp";
                    wstring wstrKeyName = L"Tarma";
                    wstring wstrDatPath = L"sample2.txt";
                  

                    dynamic_cast<CAniToolScene2*>(CSceneMgr::GetInst()->GetCurScene())->CreateAnimation(wstrKeyName, wstrTexPath, wstrDatPath);
                    // 여기서 애니메이션 생성 호출 

                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
                case IDCANCEL:
                {
                    CCamera::GetInst()->UnblockUpdate();
                    CInputMgr::GetInst()->UnblockInput();
                    EndDialog(g_hDlg, 0);
                    break;
                }
            }
        }
    }
    return 0;
}



INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

