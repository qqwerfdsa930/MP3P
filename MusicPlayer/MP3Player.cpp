#include "MP3Player.h"

MP3Player::MP3Player()
{
    BASS_Init(-1, 44100, 0, 0, NULL);
    menuList.push_back("OPEN");
    menuList.push_back("PLAY");
    menuList.push_back("STOP");
    menuList.push_back("EXIT");
    selectedMenuItem = 0;
    counter.ifStop = false;
    close();
}

MP3Player::~MP3Player()
{
    close();
    BASS_Free();
}

void MP3Player::open()
{
    close();
    while(1)
    {
        OPENFILENAME ofn;
        char szFile[1000];
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "MP3 file\0*.mp3";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        GetOpenFileName(&ofn);
        fileName = szFile;
        close();

        hStream = BASS_StreamCreateFile(false, fileName.c_str(), 0, 0, 0);
        if(BASS_ErrorGetCode() != 0)
        {
            MessageBoxA(NULL, "Error for opening!", "Error", MB_OK);
            return;
        }
        else
            break;
    }
}

void MP3Player::play()
{
    if(BASS_ErrorGetCode() != 0)
    {
        MessageBox(NULL, "Error for playing!", "Error", MB_OK);
        return;
    }
    stop();
    BASS_ChannelPlay(hStream, true);
    counter.ifStop = false;
    std::thread timerThread(&Timer::showTime, &counter);
    timerThread.detach();
}

void MP3Player::close()
{
    stop();
    BASS_StreamFree(hStream);
}

void MP3Player::stop()
{
    BASS_ChannelStop(hStream);
    counter.ifStop = true;
}

void MP3Player::showUI()
{
    bool exitSignal = false;
    updateMenu();
    while(1)
    {
        if(exitSignal) break;
        updateStat();
        while (!_kbhit())
            ;
        int KBInFirst = _getch();
        if(KBInFirst == 224)
        {
            char arrKey = _getch();
            switch(arrKey)
            {
            case 75:
                (selectedMenuItem == 0) ? (selectedMenuItem = menuList.size() - 1) : (--selectedMenuItem);
                updateMenu();
                break;
            case 77:
                (selectedMenuItem == menuList.size() - 1) ? (selectedMenuItem = 0) : (++selectedMenuItem);
                updateMenu();
                break;
            }
        }
        else if (KBInFirst == 13)
        {
            switch(selectedMenuItem)
            {
            case 0:
                open();
                selectedMenuItem = 1;
                updateMenu();
                break;
            case 1:
                play();
                break;
            case 2:
                stop();
                break;
            case 3:
                close();
                exitSignal = true;
                break;
            }
        }
    }
}

void MP3Player::updateStat()
{
    ui.write((fileName.size() == 0) ? "No File Selected." : "File: " + fileName, {10, 23});
    ui.write("Use [<-] or [->] to move, [Enter] to run the selected file.", {10, 25});
}

void MP3Player::updateMenu()
{
    int x = 22, y = 20, tab = 20;
    for(int i = 0;i < menuList.size(); ++i)
    {
        ui.write(menuList[i], {x + (i*tab), y}, (selectedMenuItem == i) ? Console::Color::WhiteBlack : Console::Color::BlackWhite);
    }

}
