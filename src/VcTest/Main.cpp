#include "stdafx.h"

char kChannelName[] = "VCTEST";

int wmain(int argc, WCHAR* argv[])
{
    HANDLE channel = ::WTSVirtualChannelOpen(WTS_CURRENT_SERVER, WTS_CURRENT_SESSION, kChannelName);

    if (!channel)
    {
        std::cerr << "Failed to open a virtual channel!\n";
        return -1;
    }

    int bytesToWrite = 0;

    if (argc >= 2)
    {
        bytesToWrite = _wtoi(argv[1]);        
    }

    if (0 == bytesToWrite)
    {
        bytesToWrite = 1;
    }

    std::cout << "Writing " << bytesToWrite << " bytes to a virtual channel...\n";

    std::vector<char> buffer(bytesToWrite);    
    ULONG written = 0;

    if (!::WTSVirtualChannelWrite(channel, &buffer[0], bytesToWrite, &written))
    {
        std::cerr << "Failed to write to a virtual channel!\n";
        return -1;
    }

    std::cout << "Done!\n";

    ::system("pause");
    ::WTSVirtualChannelClose(channel);

    return 0;
}

