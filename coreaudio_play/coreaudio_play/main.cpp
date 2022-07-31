//#include <Windows.h>
//#include <stdio.h>
//#pragma comment(lib, "winmm.lib")
//
//
//// Determines whether the specified waveform-audio output device 
//// supports a specified waveform-audio format. Returns 
//// MMSYSERR_NOERROR if the format is supported, WAVEERR_BADFORMAT if 
//// the format is not supported, and one of the other MMSYSERR_ error 
//// codes if there are other errors encountered in opening the 
//// specified waveform-audio device. 
//
//MMRESULT IsFormatSupported(LPWAVEFORMATEX pwfx, UINT uDeviceID)
//{
//	return (waveOutOpen(
//		NULL,                 // ptr can be NULL for query 
//		uDeviceID,            // the device identifier 
//		pwfx,                 // defines requested format 
//		NULL,                 // no callback 
//		NULL,                 // no instance data 
//		WAVE_FORMAT_QUERY));  // query only, do not open device 
//}
//
//
//int main()
//{
//	
//	int num = waveOutGetNumDevs();
//
//	for (int i = 0;i < num;i++)
//	{
//		WAVEOUTCAPSA woc;
//		waveOutGetDevCapsA(i, &woc, sizeof(WAVEOUTCAPSA));
//		printf("%s\n", woc.szPname);
//	}
//
//	return 0;
//}