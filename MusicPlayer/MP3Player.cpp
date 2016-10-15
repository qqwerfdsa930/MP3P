#include "MP3Player.h"

MP3Player::MP3Player()
{
    BASS_Init(-1, 44100, 0, 0, NULL);
    stopSignal = false;
}

MP3Player::~MP3Player()
{
    close();
    stopSignal = true;
    BASS_Free();
}

void MP3Player::open()
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
}
void MP3Player::play()
{
    BASS_ChannelPlay(hStream, true);
    getchar();
}

void MP3Player::close()
{
    BASS_StreamFree(hStream);
}

bool MP3Player::ifStop()
{
    return stopSignal;
}
