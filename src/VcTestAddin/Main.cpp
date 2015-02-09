#include "stdafx.h"

char kChannelName[] = "VCTEST";
CHANNEL_ENTRY_POINTS g_entryPoints = {};
LPVOID g_initHandle = nullptr;
DWORD g_openHandle = 0;

void VCAPITYPE ChannelOpenEvent(
    __in DWORD                          OpenHandle,
    __in UINT                           Event,
    __in_bcount(DataLength) LPVOID      pData,
    __in UINT32                         DataLength,
    __in UINT32                         TotalLength,
    __in UINT32                         DataFlags
    )
{
    switch (Event)
    {
    case CHANNEL_EVENT_DATA_RECEIVED:
        {
            std::wstringstream ss;
            ss << L"Packet received, dataLength: " << DataLength << ", totalLength: " << TotalLength << ", dataFlags: " << DataFlags;

            ::MessageBox(nullptr, ss.str().c_str(), L"Info", MB_ICONINFORMATION);
        }
        break;

    default:
        break;
    }
}

void VCAPITYPE ChannelInitEventProc(
    __in LPVOID                         InitHandle,
    __in UINT                           Event,
    __in_bcount(DataLength) LPVOID      pData,
    __in UINT                           DataLength
    )
{
    switch (Event)
    {
    case CHANNEL_EVENT_INITIALIZED:
        break;

    case CHANNEL_EVENT_CONNECTED:
        assert(0 == g_openHandle);
        g_entryPoints.pVirtualChannelOpen(
            InitHandle,
            &g_openHandle,
            kChannelName,
            &ChannelOpenEvent
            );
        break;

    case CHANNEL_EVENT_V1_CONNECTED:
        break;

    case CHANNEL_EVENT_DISCONNECTED:
        g_entryPoints.pVirtualChannelClose(g_openHandle);
        g_openHandle = 0;
        break;

    case CHANNEL_EVENT_TERMINATED:
        break;

    default:
        break;
    }
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    return true;
}

BOOL VCAPITYPE VirtualChannelEntry(PCHANNEL_ENTRY_POINTS pEntryPoints)
{
    ::MessageBox(nullptr, L"VirtualChannelEntry", L"Info", MB_ICONINFORMATION);

    g_entryPoints = *pEntryPoints;

    CHANNEL_DEF channelDef = {};
    ::strncpy_s(channelDef.name, kChannelName, CHANNEL_NAME_LEN);

    g_entryPoints.pVirtualChannelInit(
        &g_initHandle,
        &channelDef,
        1,
        VIRTUAL_CHANNEL_VERSION_WIN2000,
        &ChannelInitEventProc
        );

    return true;
}