#include <stdio.h>
#include <Windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
    char buff[255];

    if (IsWindowVisible(hWnd)) {
        GetWindowText(hWnd, (LPSTR) buff, 254);
        if(buff[0] != '\0') {
            printf("%s\n", buff);
        }
    }
    return TRUE;
}


int window_exists(LPCTSTR name) {
    HWND window_handle = FindWindow(NULL, name);
    
    if(window_handle == NULL) return 0;
    return 1;
}


int set_window_as_fg(HWND window_handle) {

    int set_as_fg = SetForegroundWindow(window_handle);

    if(set_as_fg == 0) return 0;
    return 1;
}

void list_all_windows() {
    EnumWindows(EnumWindowsProc, 0);
}


void send_key(char vk_id) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = vk_id;
    
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
    
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));    
}


void send_mouse(char vk_id) {

}

void stream_keys(int stream_size, char* key_stream) {
    for(int i = 0; i < stream_size; i++) {
    	send_key(key_stream[i]);    
    }
    
}


void send_custom_input() {
    send_key('I');
}


int refersh(LPCTSTR window_name) {

    if(window_exists(window_name) == 0) {
        printf("Window does not exist... listing all open windows... \n\n");
        list_all_windows();
        return -1;
    }



    else {
        Sleep(2000);
        HWND window_handle = FindWindow(NULL, window_name);
        set_window_as_fg(window_handle);

        send_custom_input();
    }

    return 0;
}


int main(int argc, char* argv[]) {

    LPCTSTR lost_ark_name = "LOST ARK (64-bit, DX11) v.2.0.2.1";

    if(argc == 2) {
        lost_ark_name = argv[1];
    }

    int temp = refersh(lost_ark_name);
    if(temp != 0) return -1;

    return 0;
}