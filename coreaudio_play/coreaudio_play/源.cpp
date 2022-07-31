#include <Windows.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")


// Determines whether the specified waveform-audio output device 
// supports a specified waveform-audio format. Returns 
// MMSYSERR_NOERROR if the format is supported, WAVEERR_BADFORMAT if 
// the format is not supported, and one of the other MMSYSERR_ error 
// codes if there are other errors encountered in opening the 
// specified waveform-audio device. 

MMRESULT IsFormatSupported(LPWAVEFORMATEX pwfx, UINT uDeviceID)
{
	return (waveOutOpen(
		NULL,                 // ptr can be NULL for query 
		uDeviceID,            // the device identifier 
		pwfx,                 // defines requested format 
		NULL,                 // no callback 
		NULL,                 // no instance data 
		WAVE_FORMAT_QUERY));  // query only, do not open device 
}


int main()
{
	////MMSYSERR_NOERROR
	//{
	//	WAVEFORMATEX wfx = { 0 };
	//	wfx.wFormatTag = WAVE_FORMAT_PCM; //设置波形声音的格式
	//	wfx.nChannels = 2;            //设置音频文件的通道数量
	//	wfx.nSamplesPerSec = 48000; //设置每个声道播放和记录时的样本频率
	//	wfx.wBitsPerSample = 16;    //每隔采样点所占的大小

	//	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	//	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	//	int ret = IsFormatSupported(&wfx, 0);
	//	ret = 1;
	//}
	
	//MMSYSERR_INVALHANDLE

	const int buf_size = 44100*120*2;
	char* buf = new char[buf_size];

	FILE* thbgm; //文件

	//fopen_s(&thbgm, R"(C:\\Users\\luxiang\\Desktop\\udprecv\\udprecv\\123.pcm)", "rb");
	fopen_s(&thbgm, "out.pcm", "rb");
	fread(buf, sizeof(char), buf_size, thbgm); //预读取文件
	fclose(thbgm);

	WAVEFORMATEX wfx = { 0 };
	wfx.wFormatTag = WAVE_FORMAT_PCM; //设置波形声音的格式
	wfx.nChannels = 2;            //设置音频文件的通道数量
	wfx.nSamplesPerSec = 44100; //设置每个声道播放和记录时的样本频率
	wfx.wBitsPerSample = 16;    //每隔采样点所占的大小

	wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	//HANDLE wait = CreateEvent(NULL, 0, 0, NULL);
	HWAVEOUT hwo;
	//MMSYSERR_NOERROR

	int ret = waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0L, CALLBACK_NULL); //打开一个给定的波形音频输出装置来进行回放

	int data_size = 44100/8;
	char* data_ptr = buf;


	WAVEHDR wh[2] = { 0 };

	wh[1].dwFlags |= WHDR_DONE;




	for(int i = 0;;)
	{


		wh[i].lpData = data_ptr;
		wh[i].dwBufferLength = data_size;
		wh[i].dwFlags = 0L;
		wh[i].dwLoops = 0L;

		data_ptr += data_size;

		int ret;
		ret = waveOutPrepareHeader(hwo, wh+i, sizeof(WAVEHDR)); //准备一个波形数据块用于播放
		if (MMSYSERR_NOERROR != ret)
			printf("waveOutPrepareHeader %d",ret);
		ret = waveOutWrite(hwo, wh + i, sizeof(WAVEHDR)); //在音频媒体中播放第二个函数wh指定的数据
		if (MMSYSERR_NOERROR != ret)
			printf("waveOutWrite %d",ret);

		i++;
		i %= 2;
WAIT:
		if (wh[i].dwFlags & WHDR_DONE)
			continue;
		else
		{
			Sleep(1);
			goto WAIT;
		}
			

	

	}

	waveOutClose(hwo);
	//CloseHandle(wait);


	return 0;
}