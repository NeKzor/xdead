/*
 * Copyright (c) 2022-2023, NeKz
 *
 * SPDX-License-Identifier: MIT
 */

#include <algorithm>
#include <intrin.h>

#include "framework.hpp"
#include "xdead.hpp"
#include "xlive.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <wincrypt.h>

#pragma warning(disable : 102)

using namespace xlive;

#define EXPORT __declspec(dllexport)

#define DECL_DETOUR_API(type, cc, name, ...)                                                                           \
    using _##name = type(cc*)(##__VA_ARGS__);                                                                          \
    static auto name##_listeners = std::vector<xdead::Listener<_##name>>();                                            \
    EXPORT type cc name(##__VA_ARGS__)

#define DETOUR_API(type, cc, name, ...) EXPORT type cc name(##__VA_ARGS__)

typedef uintptr_t hex;

#define dptr(ptr) ptr ? *(uintptr_t*)ptr : 0

DECL_DETOUR_API(signed int, __stdcall, xlive_3, int a1, signed int a2, signed int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_4, int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_6, int a1, int a2, signed int* a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_7, int a1, int a2, signed int a3, int* a4, signed int a5);
DECL_DETOUR_API(int, __stdcall, xlive_8, int a1, int a2, int a3, void* a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_9, int a1, int a2, int a3);
DECL_DETOUR_API(int, __stdcall, xlive_11, int a1, int a2, int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_12, int a1, int a2, int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_13, int a1, signed int a2);
DECL_DETOUR_API(uintptr_t, __stdcall, xlive_14, void* a1, int a2, int a3);
DECL_DETOUR_API(int, __stdcall, xlive_15, int a1, int a2, int a3, int a4, DWORD a5);
DECL_DETOUR_API(int, __stdcall, xlive_18, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_20, int a1, int a2, int a3, char a4, int a5, DWORD* a6);
DECL_DETOUR_API(int, __stdcall, xlive_22, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_24, int a1, int a2, int a3, int a4, int a5, int a6);
DECL_DETOUR_API(DWORD, __stdcall, xlive_27);
DECL_DETOUR_API(int, __stdcall, xlive_51, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_52);
DECL_DETOUR_API(int, __stdcall, xlive_53, BYTE* a1, HCRYPTPROV a2);
DECL_DETOUR_API(signed int, __stdcall, xlive_55, int a1, void* a2);
DECL_DETOUR_API(signed int, __stdcall, xlive_56, const void* a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_57, int a1, const void* a2, DWORD* a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_58, int a1, int a2, DWORD* a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_63, unsigned int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_67, int a1, int a2, DWORD* a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_68, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_69, int a1, void* a2, int a3, int a4, int a5);
DECL_DETOUR_API(int, __fastcall, xlive_70, int ecx0, int edx0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
    int a8, int a9, int a10, int a11, int a12);
DECL_DETOUR_API(int, __fastcall, xlive_71, int ecx0, int edx0, int a1, int a2, int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_72, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_73, int a1);
DECL_DETOUR_API(unsigned int, __stdcall, xlive_75);
DECL_DETOUR_API(signed int, __stdcall, xlive_77, const void* a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_84, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_651, int a1, int a2, DWORD* a3, DWORD* a4);
DECL_DETOUR_API(int, __stdcall, xlive_652, LONG Value);
DECL_DETOUR_API(DWORD, __stdcall, xlive_1082, int a1);
DECL_DETOUR_API(DWORD, __stdcall, xlive_1083, int a1, DWORD* a2, int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_5001, int a1);
DECL_DETOUR_API(unsigned int, __stdcall, xlive_5002);
DECL_DETOUR_API(int, __stdcall, xlive_5003);
DECL_DETOUR_API(signed int, __stdcall, xlive_5006);
DECL_DETOUR_API(signed int, __stdcall, xlive_5007, int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_5008, int a1, int a2, DWORD* a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_5016, int a1, unsigned int a2);
DECL_DETOUR_API(signed int, __stdcall, xlive_5017, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_5030, HIMC);
DECL_DETOUR_API(int, __stdcall, xlive_5031, unsigned int a1, DWORD* a2);
DECL_DETOUR_API(int, __stdcall, xlive_5212, int, int, int, int, int, int, int, int, void* Src, void*, int, int);
DECL_DETOUR_API(signed int, __stdcall, xlive_5215, int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_5216, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
DECL_DETOUR_API(int, __stdcall, xlive_5251, HANDLE hObject);
DECL_DETOUR_API(signed int, __stdcall, xlive_5252, int a1, __int64 a2);
DECL_DETOUR_API(int, __stdcall, xlive_5256, int a1, int a2, int a3, DWORD* a4, int a5);
DECL_DETOUR_API(signed int, __stdcall, xlive_5258, int a1);
DECL_DETOUR_API(XUSER_SIGNIN_STATE, __stdcall, xlive_5262, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_5263, uint32_t user_index, CHAR* user_name, uint32_t user_name_length);
DECL_DETOUR_API(int, __stdcall, xlive_5265, unsigned int a1, int a2, DWORD* a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_5267, uint32_t user_index, uint32_t flags, XUSER_SIGNIN_INFO* signin_info);
DECL_DETOUR_API(int, __stdcall, xlive_5270, __int64 a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_5271, int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_5274, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5275, int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_5277, int a1, int a2, int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_5279, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
DECL_DETOUR_API(signed int, __stdcall, xlive_5280, int a1, int a2, int a3, unsigned int a4, int a5, unsigned int a6,
    unsigned int a7, int a8, int a9);
DECL_DETOUR_API(int, __stdcall, xlive_5281, int a1, unsigned int a2, int a3, unsigned int a4, int a5, unsigned int* a6,
    int a7, int a8);
DECL_DETOUR_API(int, __stdcall, xlive_5284, int, int, int, int, void* Src, int, int);
DECL_DETOUR_API(int, __stdcall, xlive_5286, int, int, int, int, int, void* Src, int, int);
DECL_DETOUR_API(int, __stdcall, xlive_5292, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(int, __stdcall, xlive_5293, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5294, int a1, unsigned int a2, int a3, int a4);
DECL_DETOUR_API(int, __stdcall, xlive_5303, int a1, const char* a2, int a3, int a4, unsigned int a5, int a6, int a7);
DECL_DETOUR_API(int, __stdcall, xlive_5305, char a1, const unsigned __int16* a2, char a3, int a4, int a5);
DECL_DETOUR_API(
    int, __stdcall, xlive_5306, int a1, const unsigned __int16* a2, int a3, int a4, unsigned int a5, int a6, int a7);
DECL_DETOUR_API(int, __stdcall, xlive_5310);
DECL_DETOUR_API(int, __stdcall, xlive_5311);
DECL_DETOUR_API(signed int, __stdcall, xlive_5312, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(signed int, __stdcall, xlive_5313, int a1);
DECL_DETOUR_API(signed int, __stdcall, xlive_5314, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5315, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5316, int a1, int a2, int a3, wchar_t* a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5320, int a1, int a2, int a3, int* a4, int a5, int a6);
DECL_DETOUR_API(int, __stdcall, xlive_5321, int a1, int a2, int a3, unsigned __int16 a4, __int16 a5, int a6, int a7,
    unsigned int* a8, int a9, int a10);
DECL_DETOUR_API(signed int, __stdcall, xlive_5322, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(signed int, __stdcall, xlive_5324, void* a1);
DECL_DETOUR_API(unsigned int, __stdcall, xlive_5326, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(signed int, __stdcall, xlive_5327, int a1, int a2, int* a3, int a4, int a5);
DECL_DETOUR_API(signed int, __stdcall, xlive_5328, int a1, DWORD* a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5329, int a1, int a2);
DECL_DETOUR_API(uintptr_t, __stdcall, xlive_5330, int a1, int a2);
DECL_DETOUR_API(signed int, __stdcall, xlive_5331, int a1, int a2, int a3, int a4, DWORD* a5, int a6, int a7);
DECL_DETOUR_API(signed int, __stdcall, xlive_5333, int a1, int a2, int a3, int a4, int* a5, int a6, int a7);
DECL_DETOUR_API(unsigned int, __stdcall, xlive_5335, void* Src, int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5336, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5337, int a1, unsigned int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5338, int a1, int a2, int a3);
DECL_DETOUR_API(signed int, __stdcall, xlive_5340, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
DECL_DETOUR_API(signed int, __stdcall, xlive_5342, int a1, unsigned int a2, int a3, int a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5343, unsigned int a1, int a2, double* a3, double* a4, double* a5);
DECL_DETOUR_API(signed int, __stdcall, xlive_5344, int a1, int a2, int a3, unsigned int a4, int a5, int a6, int a7);
DECL_DETOUR_API(
    int, __stdcall, xlive_5345, int a1, const unsigned __int16* a2, int a3, int a4, unsigned int a5, int a6, int a7);
DECL_DETOUR_API(int, __stdcall, xlive_5350, int a1, void* a2, int a3, int a4, int a5, int a6, int a7);
DECL_DETOUR_API(int, __stdcall, xlive_5355, int a1, int a2, char* a3, unsigned int* a4);
DECL_DETOUR_API(int, __stdcall, xlive_5356, int a1, int a2, char* a3, unsigned int* a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5360, unsigned int a1, int a2, DWORD* a3, int* a4);
DECL_DETOUR_API(signed int, __stdcall, xlive_5365, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5367, int a1, int a2, unsigned int a3, int a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5372, HANDLE hObject, int, int, int, int, int);

DECL_DETOUR_API(__int16, __stdcall, xlive_38, __int16 a1);
DECL_DETOUR_API(int, __stdcall, xlive_5208, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(int, __stdcall, xlive_5209, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(int, __stdcall, xlive_5210, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5214, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5250, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_5259, int a1, int a2, int a3, int a4);
DECL_DETOUR_API(int, __stdcall, xlive_5260, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5300, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
DECL_DETOUR_API(int, __stdcall, xlive_5318, int a1, int a2, int a3);
DECL_DETOUR_API(int, __stdcall, xlive_5034, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5035, BYTE* protected_data, DWORD size_of_protected_data, BYTE* unprotected_data,
    DWORD* size_of_data, HANDLE* protected_data_handle);
DECL_DETOUR_API(int, __stdcall, xlive_5036, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5038, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_5206, int a1);
DECL_DETOUR_API(int, __stdcall, xlive_5264, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5278, int a1, int a2, int a3);
DECL_DETOUR_API(int, __stdcall, xlive_5297, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5317, int a1, int a2, int a3, int a4, int a5);
DECL_DETOUR_API(int, __stdcall, xlive_5332, int a1, int a2);
DECL_DETOUR_API(int, __stdcall, xlive_5026, int a1, int a2);

#define XDEAD_FUNCTION_LISTENER(name, ordinal)                                                                         \
    {                                                                                                                  \
        ordinal,                                                                                                       \
        {                                                                                                              \
#name, (std::vector <xdead::Listener <>>*)&xlive_##ordinal##_listeners                                     \
        }                                                                                                              \
    }

auto xdead::get_function_listeners() -> std::map<uint32_t, xdead::FunctionListener>&
{
    static std::map<uint32_t, xdead::FunctionListener> function_listeners = {
        XDEAD_FUNCTION_LISTENER(XSocketCreate, 3),
        XDEAD_FUNCTION_LISTENER(XSocketClose, 4),
        XDEAD_FUNCTION_LISTENER(XSocketIOCTLSocket, 6),
        XDEAD_FUNCTION_LISTENER(XSocketSetSockOpt, 7),
        XDEAD_FUNCTION_LISTENER(XSocketGetSockOpt, 8),
        XDEAD_FUNCTION_LISTENER(XSocketGetSockName, 9),
        XDEAD_FUNCTION_LISTENER(XSocketBind, 11),
        XDEAD_FUNCTION_LISTENER(XSocketConnect, 12),
        XDEAD_FUNCTION_LISTENER(XSocketListen, 13),
        XDEAD_FUNCTION_LISTENER(XSocketAccept, 14),
        XDEAD_FUNCTION_LISTENER(XSocketSelect, 15),
        XDEAD_FUNCTION_LISTENER(XSocketRecv, 18),
        XDEAD_FUNCTION_LISTENER(XSocketSend, 22),
        XDEAD_FUNCTION_LISTENER(XSocketSendTo, 24),
        XDEAD_FUNCTION_LISTENER(XNetStartup, 51),
        XDEAD_FUNCTION_LISTENER(XNetCleanup, 52),
        XDEAD_FUNCTION_LISTENER(XNetRandom, 53),
        XDEAD_FUNCTION_LISTENER(XNetRegisterKey, 55),
        XDEAD_FUNCTION_LISTENER(XNetUnregisterKey, 56),
        XDEAD_FUNCTION_LISTENER(XNetXnAddrToInAddr, 57),
        XDEAD_FUNCTION_LISTENER(XNetServerToInAddr, 58),
        XDEAD_FUNCTION_LISTENER(XNetUnregisterInAddr, 63),
        XDEAD_FUNCTION_LISTENER(XNetDnsLookup, 67),
        XDEAD_FUNCTION_LISTENER(XNetDnsRelease, 68),
        XDEAD_FUNCTION_LISTENER(XNetQosListen, 69),
        XDEAD_FUNCTION_LISTENER(XNetQosLookup, 70),
        XDEAD_FUNCTION_LISTENER(XNetQosServiceLookup, 71),
        XDEAD_FUNCTION_LISTENER(XNetQosRelease, 72),
        XDEAD_FUNCTION_LISTENER(XNetGetTitleXnAddr, 73),
        XDEAD_FUNCTION_LISTENER(XNetGetEthernetLinkStatus, 75),
        XDEAD_FUNCTION_LISTENER(XNetQosGetListenStats, 77),
        XDEAD_FUNCTION_LISTENER(XNetSetSystemLinkPort, 84),
        XDEAD_FUNCTION_LISTENER(XNotifyPositionUI, 652),
        XDEAD_FUNCTION_LISTENER(XGetOverlappedExtendedError, 1082),
        XDEAD_FUNCTION_LISTENER(XLiveUninitialize, 5003),
        XDEAD_FUNCTION_LISTENER(XLiveOnDestroyDevice, 5006),
        XDEAD_FUNCTION_LISTENER(XLiveOnResetDevice, 5007),
        XDEAD_FUNCTION_LISTENER(XHVCreateEngine, 5008),
        XDEAD_FUNCTION_LISTENER(XLivePBufferAllocate, 5016),
        XDEAD_FUNCTION_LISTENER(XLivePBufferFree, 5017),
        XDEAD_FUNCTION_LISTENER(XLiveSetDebugLevel, 5031),
        XDEAD_FUNCTION_LISTENER(XShowCustomPlayerListUI, 5212),
        XDEAD_FUNCTION_LISTENER(XShowGuideUI, 5215),
        XDEAD_FUNCTION_LISTENER(XShowKeyboardUI, 5216),
        XDEAD_FUNCTION_LISTENER(XCloseHandle, 5251),
        XDEAD_FUNCTION_LISTENER(XShowGamerCardUI, 5252),
        XDEAD_FUNCTION_LISTENER(XEnumerate, 5256),
        XDEAD_FUNCTION_LISTENER(XLiveSignout, 5258),
        XDEAD_FUNCTION_LISTENER(XUserGetSigninState, 5262),
        XDEAD_FUNCTION_LISTENER(XUserGetName, 5263),
        XDEAD_FUNCTION_LISTENER(XUserCheckPrivilege, 5265),
        XDEAD_FUNCTION_LISTENER(XUserGetSigninInfo, 5267),
        XDEAD_FUNCTION_LISTENER(XNotifyCreateListener, 5270),
        XDEAD_FUNCTION_LISTENER(XShowPlayersUI, 5271),
        XDEAD_FUNCTION_LISTENER(XUserAwardGamerPicture, 5274),
        XDEAD_FUNCTION_LISTENER(XShowFriendsUI, 5275),
        XDEAD_FUNCTION_LISTENER(XUserSetContext, 5277),
        XDEAD_FUNCTION_LISTENER(XUserReadAchievementPicture, 5279),
        XDEAD_FUNCTION_LISTENER(XUserCreateAchievementEnumerator, 5280),
        XDEAD_FUNCTION_LISTENER(XUserReadStats, 5281),
        XDEAD_FUNCTION_LISTENER(XUserCreateStatsEnumeratorByRank, 5284),
        XDEAD_FUNCTION_LISTENER(XUserCreateStatsEnumeratorByXuid, 5286),
        XDEAD_FUNCTION_LISTENER(XUserSetContextEx, 5292),
        XDEAD_FUNCTION_LISTENER(XUserSetPropertyEx, 5293),
        XDEAD_FUNCTION_LISTENER(XLivePBufferGetByteArray, 5294),
        XDEAD_FUNCTION_LISTENER(XStringVerify, 5303),
        XDEAD_FUNCTION_LISTENER(XStorageUploadFromMemory, 5305),
        XDEAD_FUNCTION_LISTENER(XStorageEnumerate, 5306),
        XDEAD_FUNCTION_LISTENER(XOnlineStartup, 5310),
        XDEAD_FUNCTION_LISTENER(XOnlineCleanup, 5311),
        XDEAD_FUNCTION_LISTENER(XFriendsCreateEnumerator, 5312),
        XDEAD_FUNCTION_LISTENER(XPresenceInitialize, 5313),
        XDEAD_FUNCTION_LISTENER(XUserMuteListQuery, 5314),
        XDEAD_FUNCTION_LISTENER(XInviteGetAcceptedInfo, 5315),
        XDEAD_FUNCTION_LISTENER(XInviteSend, 5316),
        XDEAD_FUNCTION_LISTENER(XSessionSearchByID, 5320),
        XDEAD_FUNCTION_LISTENER(XSessionSearch, 5321),
        XDEAD_FUNCTION_LISTENER(XSessionModify, 5322),
        XDEAD_FUNCTION_LISTENER(XOnlineGetNatType, 5324),
        XDEAD_FUNCTION_LISTENER(XSessionJoinRemote, 5326),
        XDEAD_FUNCTION_LISTENER(XSessionJoinLocal, 5327),
        XDEAD_FUNCTION_LISTENER(XSessionGetDetails, 5328),
        XDEAD_FUNCTION_LISTENER(XSessionFlushStats, 5329),
        XDEAD_FUNCTION_LISTENER(XSessionDelete, 5330),
        XDEAD_FUNCTION_LISTENER(XUserReadProfileSettings, 5331),
        XDEAD_FUNCTION_LISTENER(XSessionArbitrationRegister, 5333),
        XDEAD_FUNCTION_LISTENER(XTitleServerCreateEnumerator, 5335),
        XDEAD_FUNCTION_LISTENER(XSessionLeaveRemote, 5336),
        XDEAD_FUNCTION_LISTENER(XUserWriteProfileSettings, 5337),
        XDEAD_FUNCTION_LISTENER(XPresenceSubscribe, 5338),
        XDEAD_FUNCTION_LISTENER(XPresenceCreateEnumerator, 5340),
        XDEAD_FUNCTION_LISTENER(XSessionModifySkill, 5342),
        XDEAD_FUNCTION_LISTENER(XSessionCalculateSkill, 5343),
        XDEAD_FUNCTION_LISTENER(XStorageBuildServerPath, 5344),
        XDEAD_FUNCTION_LISTENER(XStorageDownloadToMemory, 5345),
        XDEAD_FUNCTION_LISTENER(XLiveContentCreateAccessHandle, 5350),
        XDEAD_FUNCTION_LISTENER(XLiveContentGetPath, 5355),
        XDEAD_FUNCTION_LISTENER(XLiveContentGetDisplayName, 5356),
        XDEAD_FUNCTION_LISTENER(XLiveContentCreateEnumerator, 5360),
        XDEAD_FUNCTION_LISTENER(XShowMarketplaceUI, 5365),
        XDEAD_FUNCTION_LISTENER(XContentGetMarketplaceCounts, 5367),
        XDEAD_FUNCTION_LISTENER(XMarketplaceCreateOfferEnumerator, 5372),
        XDEAD_FUNCTION_LISTENER(XSocketNTOHS, 38),
        XDEAD_FUNCTION_LISTENER(XShowGameInviteUI, 5208),
        XDEAD_FUNCTION_LISTENER(XShowMessageComposeUI, 5209),
        XDEAD_FUNCTION_LISTENER(XShowFriendRequestUI, 5210),
        XDEAD_FUNCTION_LISTENER(XShowPlayerReviewUI, 5214),
        XDEAD_FUNCTION_LISTENER(XShowAchievementsUI, 5250),
        XDEAD_FUNCTION_LISTENER(XLiveSignin, 5259),
        XDEAD_FUNCTION_LISTENER(XShowSigninUI, 5260),
        XDEAD_FUNCTION_LISTENER(XSessionCreate, 5300),
        XDEAD_FUNCTION_LISTENER(XSessionStart, 5318),
        XDEAD_FUNCTION_LISTENER(XLiveProtectData, 5034),
        XDEAD_FUNCTION_LISTENER(XLiveUnprotectData, 5035),
        XDEAD_FUNCTION_LISTENER(XLiveCreateProtectedDataContext, 5036),
        XDEAD_FUNCTION_LISTENER(XLiveCloseProtectedDataContext, 5038),
        XDEAD_FUNCTION_LISTENER(XShowMessagesUI, 5206),
        XDEAD_FUNCTION_LISTENER(XUserAreUsersFriends, 5264),
        XDEAD_FUNCTION_LISTENER(XUserWriteAchievements, 5278),
        XDEAD_FUNCTION_LISTENER(XLiveInitializeEx, 5297),
        XDEAD_FUNCTION_LISTENER(XSessionWriteStats, 5317),
        XDEAD_FUNCTION_LISTENER(XSessionEnd, 5332),
        XDEAD_FUNCTION_LISTENER(XLiveSetSponsorToken, 5026),
    };
    return function_listeners;
};

#undef XDEAD_FUNCTION_LISTENER

auto __forceinline print_stack(int parameters) -> void
{
    auto retAddress = uintptr_t(_AddressOfReturnAddress());
    for (int i = 12; i <= 12 + parameters + 1; ++i) {
        auto stack = retAddress + (i << 2);
        println("[xdead] stack(0x{:04x}) -> 0x{:08x} | {}", stack, *(uintptr_t*)stack, *(uintptr_t*)stack);
    }
}

auto xdead_debug_break(bool resume_main_thread = true) -> void
{
    if (IsDebuggerPresent()) {
        return;
    }

    println("[xdead] waiting for debugger to attach...");

    while (!IsDebuggerPresent()) {
        Sleep(420);
    }

    DebugBreak();
}

auto __return_value = 0;

#define SET_RETURN_VALUE(rv) auto __return_value = rv;

#define RUN_LISTENERS(_ordinal, _name, ...)                                                                            \
    auto ordinal = _ordinal;                                                                                           \
    auto name = _name;                                                                                                 \
    auto original = xlive_##_ordinal;                                                                                  \
    auto result = __return_value;                                                                                      \
    for (auto& listener : xlive_##_ordinal##_listeners) {                                                              \
        auto rv = listener.callback(##__VA_ARGS__);                                                                    \
        if (rv != __return_value) {                                                                                    \
            result = rv;                                                                                               \
            goto log_and_return;                                                                                       \
        }                                                                                                              \
    }
#define RUN_LISTENERS_AND_RETURN(_ordinal, _name, ...)                                                                 \
    auto ordinal = _ordinal;                                                                                           \
    auto name = _name;                                                                                                 \
    auto original = xlive_##_ordinal;                                                                                  \
    auto result = __return_value;                                                                                      \
    for (auto& listener : xlive_##_ordinal##_listeners) {                                                              \
        auto rv = listener.callback(##__VA_ARGS__);                                                                    \
        if (rv != __return_value) {                                                                                    \
            return rv;                                                                                                 \
        }                                                                                                              \
    }                                                                                                                  \
    return result

#define LOG_AND_RETURN(fmt, ...)                                                                                       \
    log_and_return:                                                                                                    \
    println("[xdead] [{:04}] [0x{:x}] [0x{:x}] {}(" fmt ") -> {:x} | {}", ordinal, uintptr_t(original),                \
        uintptr_t(_ReturnAddress()), name, ##__VA_ARGS__, result, result);                                             \
    return result

// clang-format off

auto __stdcall xdead::add_listener(uint32_t ordinal, void* callback, uint32_t index) -> xdead::ListenerStatus
{
    auto function_listener_iter = xdead::get_function_listeners().find(ordinal);
    if (function_listener_iter == xdead::get_function_listeners().end()) {
        return xdead::ListenerStatus::OrdinalNotFound;
    }

    if (!callback) {
        return xdead::ListenerStatus::InvalidCallback;
    }

    auto& function_listener = function_listener_iter->second;
    auto& listeners = function_listener.listeners;
    listeners->push_back({ index, callback });

    std::sort(listeners->begin(), listeners->end(), [](xdead::Listener<> &a, xdead::Listener<> &b) -> bool
    {
        return a.index < b.index;
    });

    return xdead::ListenerStatus::Ok;
}
auto __stdcall xdead::remove_listener(uint32_t ordinal, void* callback) -> xdead::ListenerStatus
{
    auto function_listener_iter = xdead::get_function_listeners().find(ordinal);
    if (function_listener_iter == xdead::get_function_listeners().end()) {
        return ListenerStatus::OrdinalNotFound;
    }

    if (!callback) {
        return ListenerStatus::InvalidCallback;
    }

    auto& function_listener = function_listener_iter->second;
    auto& listeners = function_listener.listeners;

    auto listener = std::find_if(listeners->begin(), listeners->end(), [&callback](Listener<>& listener)
    {
        return listener.callback== callback;
    });

    if (listener == listeners->end()) {
        return ListenerStatus::CallbackNotFound;
    }

    listeners->erase(listener);

    return ListenerStatus::Ok;
}
auto __stdcall xdead::remove_all_listeners() -> xdead::ListenerStatus
{
    for (auto& [ordinal, function_listener] : xdead::get_function_listeners()) {
        function_listener.listeners->clear();
    }

    return xdead::ListenerStatus::Ok;
}

DETOUR_API(signed int, __stdcall, xlive_3, int a1, signed int a2, signed int a3)
{
    RUN_LISTENERS(3, "XSocketCreate", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_4, int a1)
{
    RUN_LISTENERS(4, "XSocketClose", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_6, int a1, int a2, signed int* a3)
{
    RUN_LISTENERS(6, "XSocketIOCTLSocket", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_7, int a1, int a2, signed int a3, int* a4, signed int a5)
{
    RUN_LISTENERS(7, "XSocketSetSockOpt", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_8, int a1, int a2, int a3, void* a4, int a5)
{
    RUN_LISTENERS(8, "XSocketGetSockOpt", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_9, int a1, int a2, int a3)
{
    RUN_LISTENERS(9, "XSocketGetSockName", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(int, __stdcall, xlive_11, int a1, int a2, int a3)
{
    RUN_LISTENERS(11, "XSocketBind", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_12, int a1, int a2, int a3)
{
    RUN_LISTENERS(12, "XSocketConnect", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_13, int a1, signed int a2)
{
    RUN_LISTENERS(13, "XSocketListen", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(uintptr_t, __stdcall, xlive_14, void* a1, int a2, int a3)
{
    RUN_LISTENERS(14, "XSocketAccept", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(int, __stdcall, xlive_15, int a1, int a2, int a3, int a4, DWORD a5)
{
    RUN_LISTENERS(15, "XSocketSelect", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_18, int a1, int a2, int a3, int a4)
{
    // called frequently
    RUN_LISTENERS(18, "XSocketRecv", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_20, int a1, int a2, int a3, char a4, int a5, DWORD* a6)
{
    SET_RETURN_VALUE(-1);
    // called frequently when in multiplayer lobby
    RUN_LISTENERS_AND_RETURN(20, "XSocketRecvFrom", a1, a2, a3, a4, a5, a6);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6));
}
DETOUR_API(int, __stdcall, xlive_22, int a1, int a2, int a3, int a4)
{
    RUN_LISTENERS(22, "XSocketSend", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_24, int a1, int a2, int a3, int a4, int a5, int a6)
{
    RUN_LISTENERS(24, "XSocketSendTo", a1, a2, a3, a4, a5, a6);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6));
}
DETOUR_API(DWORD, __stdcall, xlive_27)
{
    SET_RETURN_VALUE(0);
    // called frequently when online
    RUN_LISTENERS_AND_RETURN(27, "XSocketWSAGetLastError");
}
DETOUR_API(int, __stdcall, xlive_51, int a1)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(51, "XNetStartup", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_52)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(52, "XNetCleanup");
    LOG_AND_RETURN("");
}
DETOUR_API(int, __stdcall, xlive_53, BYTE* a1, HCRYPTPROV a2)
{
    RUN_LISTENERS(53, "XNetRandom", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(signed int, __stdcall, xlive_55, int a1, void* a2)
{
    RUN_LISTENERS(55, "XNetRegisterKey", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(signed int, __stdcall, xlive_56, const void* a1)
{
    RUN_LISTENERS(56, "XNetUnregisterKey", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_57, int a1, const void* a2, DWORD* a3)
{
    RUN_LISTENERS(57, "XNetXnAddrToInAddr", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_58, int a1, int a2, DWORD* a3)
{
    RUN_LISTENERS(58, "XNetServerToInAddr", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_63, unsigned int a1)
{
    RUN_LISTENERS(63, "XNetUnregisterInAddr", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_67, int a1, int a2, DWORD* a3)
{
    RUN_LISTENERS(67, "XNetDnsLookup", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_68, int a1)
{
    RUN_LISTENERS(68, "XNetDnsRelease", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_69, int a1, void* a2, int a3, int a4, int a5)
{
    RUN_LISTENERS(69, "XNetQosListen", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __fastcall, xlive_70, int ecx0, int edx0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12)
{
    RUN_LISTENERS(70, "XNetQosLookup", ecx0, edx0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(ecx0), hex(edx0), hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8), hex(a9), hex(a10), hex(a11), hex(a12));
}
DETOUR_API(int, __fastcall, xlive_71, int ecx0, int edx0, int a1, int a2, int a3)
{
    RUN_LISTENERS(71, "XNetQosServiceLookup", ecx0, edx0, a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(ecx0), hex(edx0), hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_72, int a1)
{
    RUN_LISTENERS(72, "XNetQosRelease", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_73, int a1)
{
    // Called frequently
    RUN_LISTENERS_AND_RETURN(73, "XNetGetTitleXnAddr", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(unsigned int, __stdcall, xlive_75)
{
    RUN_LISTENERS(75, "XNetGetEthernetLinkStatus");
    LOG_AND_RETURN("");
}
DETOUR_API(signed int, __stdcall, xlive_77, const void* a1, int a2)
{
    RUN_LISTENERS(77, "XNetQosGetListenStats", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_84, int a1)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(84, "XNetSetSystemLinkPort", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_651, int a1, int a2, DWORD* a3, DWORD* a4)
{
    SET_RETURN_VALUE(0);
    // Called frequently
    RUN_LISTENERS_AND_RETURN(651, "XNotifyGetNext", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_652, LONG Value)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(652, "XNotifyPositionUI", Value);
    LOG_AND_RETURN("{:x}", hex(Value));
}
DETOUR_API(DWORD, __stdcall, xlive_1082, int a1)
{
    SET_RETURN_VALUE(0);
    // called on login, frequently when online
    RUN_LISTENERS(1082, "XGetOverlappedExtendedError", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(DWORD, __stdcall, xlive_1083, int a1, DWORD* a2, int a3)
{
    SET_RETURN_VALUE(0);
    // called on login or when gfwl ui opens, frequently when online
    RUN_LISTENERS_AND_RETURN(1083, "XGetOverlappedResult", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_5001, int a1)
{
    // frequent call
    RUN_LISTENERS_AND_RETURN(5001, "XLiveInput", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(unsigned int, __stdcall, xlive_5002)
{
    // frequent call
    RUN_LISTENERS_AND_RETURN(5002, "XLiveRender");
}
DETOUR_API(int, __stdcall, xlive_5003)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5003, "XLiveUninitialize");
    LOG_AND_RETURN("");
}
DETOUR_API(signed int, __stdcall, xlive_5006)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5006, "XLiveOnDestroyDevice");
    LOG_AND_RETURN("");
}
DETOUR_API(signed int, __stdcall, xlive_5007, int a1)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5007, "XLiveOnResetDevice", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_5008, int a1, int a2, DWORD* a3)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5008, "XHVCreateEngine", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_5016, int a1, unsigned int a2)
{
    RUN_LISTENERS(5016, "XLivePBufferAllocate", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(signed int, __stdcall, xlive_5017, int a1)
{
    RUN_LISTENERS(5017, "XLivePBufferFree", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5030, HIMC a1)
{
    SET_RETURN_VALUE(0);
    // frequently called when window focused
    RUN_LISTENERS_AND_RETURN(5030, "XLivePreTranslateMessage", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5031, unsigned int a1, DWORD* a2)
{
    // Wait, this sounds interesting...
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5031, "XLiveSetDebugLevel", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5212, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, void* Src, void* a10, int a11, int a12)
{
    // called frequently on login
    RUN_LISTENERS(5212, "XShowCustomPlayerListUI", a1, a2, a3, a4, a5, a6, a7, a8, Src, a10, a11, a12);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8), hex(Src), hex(a10), hex(a11), hex(a12));
}
DETOUR_API(signed int, __stdcall, xlive_5215, int a1)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5215, "XShowGuideUI", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_5216, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    RUN_LISTENERS(5216, "XShowKeyboardUI", a1, a2, a3, a4, a5, a6, a7, a8);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8));
}
DETOUR_API(int, __stdcall, xlive_5251, HANDLE hObject)
{
    SET_RETURN_VALUE(1);
    // called frequently acquiring a handle
    RUN_LISTENERS(5251, "XCloseHandle", hObject);
    LOG_AND_RETURN("{:x}", hex(hObject));
}
DETOUR_API(signed int, __stdcall, xlive_5252, int a1, __int64 a2)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5252, "XShowGamerCardUI", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), __int64(a2));
}
DETOUR_API(int, __stdcall, xlive_5256, int a1, int a2, int a3, DWORD* a4, int a5)
{
    struct XLiveLeaderboardStats {
        char unk_0000[40]; // 0x00
        uint32_t xp; // 0x28
        char unk_002c[20]; // 0x2c
        uint32_t derezz; // 0x40
        char unk_0044[20]; // 0x44
        uint32_t wipes; // 0x58
        char unk_005c[20]; // 0x5c
        uint32_t assists; // 0x70
        char unk_0074[20]; // 0x74
        uint32_t bits_nodes; // 0x88
        char unk_008c[20]; // 0x8c
        uint32_t played; // 0xa0
        char unk_00a4[28]; // 0xa4
    };
    static_assert(offsetof(XLiveLeaderboardStats, xp) == 0x28);
    static_assert(offsetof(XLiveLeaderboardStats, derezz) == 0x40);
    static_assert(offsetof(XLiveLeaderboardStats, wipes) == 0x58);
    static_assert(offsetof(XLiveLeaderboardStats, assists) == 0x70);
    static_assert(offsetof(XLiveLeaderboardStats, bits_nodes) == 0x88);
    static_assert(offsetof(XLiveLeaderboardStats, played) == 0xa0);
    static_assert(sizeof(XLiveLeaderboardStats) == 0xc0);

    struct XLiveLeaderboardEntry {
        ULONGLONG xuid; // 0x00
        uint32_t rank; // 0x0x8
        char unk_000c[12]; // 0x0c
        char gamer_tag[16]; // 0x18
        uint32_t columns; // 0x28
        XLiveLeaderboardStats* stats; // 0x2c
    };
    static_assert(offsetof(XLiveLeaderboardEntry, xuid) == 0x00);
    static_assert(offsetof(XLiveLeaderboardEntry, rank) == 0x08);
    static_assert(offsetof(XLiveLeaderboardEntry, gamer_tag) == 0x18);
    static_assert(offsetof(XLiveLeaderboardEntry, columns) == 0x28);
    static_assert(offsetof(XLiveLeaderboardEntry, stats) == 0x2c);
    static_assert(sizeof(XLiveLeaderboardEntry) == 0x30);

    struct XLiveLeaderboard {
        uint32_t unk_0000; // 0x00
        uint32_t unk_0004; // 0x04
        uint32_t unk_0008; // 0x08
        uint32_t unk_000c; // 0x0c
        uint32_t count; // 0x10
        XLiveLeaderboardEntry* first_entry; // 0x14
        XLiveLeaderboardEntry entries[22]; // 0x18
    };
    static_assert(offsetof(XLiveLeaderboard, count) == 0x10);
    static_assert(offsetof(XLiveLeaderboard, first_entry) == 0x14);
    static_assert(offsetof(XLiveLeaderboard, entries) == 0x18);

    SET_RETURN_VALUE(0);
    // called after login
    RUN_LISTENERS(5256, "XEnumerate", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(signed int, __stdcall, xlive_5258, int a1)
{
    RUN_LISTENERS(5258, "XLiveSignout", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(XUSER_SIGNIN_STATE, __stdcall, xlive_5262, int a1)
{
    SET_RETURN_VALUE(XUSER_SIGNIN_STATE::NotSignedIn);
    RUN_LISTENERS(5262, "XUserGetSigninState", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5263, uint32_t user_index, CHAR* user_name, uint32_t user_name_length)
{
    SET_RETURN_VALUE(0);
    // called after login
    RUN_LISTENERS(5263, "XUserGetName", user_index, user_name, user_name_length);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(user_index), hex(user_name), hex(user_name_length));
}
DETOUR_API(int, __stdcall, xlive_5265, unsigned int a1, int a2, DWORD* a3)
{
    RUN_LISTENERS(5265, "XUserCheckPrivilege", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_5267, uint32_t user_index, uint32_t flags, XUSER_SIGNIN_INFO* signin_info)
{
    if (signin_info) {
        // TODO: Figure out new self-made login system:
        //          - Fallback to GFWL?
        //          - Should we auto-login? Which GFWL account should it be?

        signin_info->xuid = 0xE00000FDAD8D3F73; // TODO: This should be variable
        signin_info->flags = 0;
        signin_info->user_signin_state = XUSER_SIGNIN_STATE::SignedInLocally;
        signin_info->guest_number = 0;
        signin_info->sponsor_user_index = 254;
        memcpy(signin_info->user_name, "NeKz", 5); // TODO: This should be variable
        return 0;
    }

    SET_RETURN_VALUE(0);

    // called after login
    RUN_LISTENERS(5267, "XUserGetSigninInfo", user_index, flags, signin_info);
    
    if (signin_info) {
        println("[xdead] signin_info->xuid = {:X}", signin_info->xuid);
        println("[xdead] signin_info->flags = {}", signin_info->flags);
        println("[xdead] signin_info->user_signin_state = {}", uint32_t(signin_info->user_signin_state));
        println("[xdead] signin_info->guest_number = {}", signin_info->guest_number);
        println("[xdead] signin_info->sponsor_user_index = {}", signin_info->sponsor_user_index);
        println("[xdead] signin_info->user_name = {}", signin_info->user_name);
    }

    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(user_index), hex(flags), hex(signin_info));
}
DETOUR_API(int, __stdcall, xlive_5270, __int64 a1)
{
    // NOTE: The game needs a value or it will fail to initialize.
    SET_RETURN_VALUE(1);
    RUN_LISTENERS(5270, "XNotifyCreateListener", a1);
    LOG_AND_RETURN("{:x}", a1);
}
DETOUR_API(signed int, __stdcall, xlive_5271, int a1)
{
    RUN_LISTENERS(5271, "XShowPlayersUI", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_5274, int a1, int a2, int a3, int a4)
{
    RUN_LISTENERS(5274, "XUserAwardGamerPicture", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5275, int a1)
{
    RUN_LISTENERS(5275, "XShowFriendsUI", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_5277, int a1, int a2, int a3)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5277, "XUserSetContext", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_5279, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    RUN_LISTENERS(5279, "XUserReadAchievementPicture", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(signed int, __stdcall, xlive_5280, int a1, int a2, int a3, unsigned int a4, int a5, unsigned int a6, unsigned int a7, int a8, int a9)
{
    SET_RETURN_VALUE(0);
    // called after login
    RUN_LISTENERS(5280, "XUserCreateAchievementEnumerator", a1, a2, a3, a4, a5, a6, a7, a8, a9);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8), hex(a9));
}
DETOUR_API(int, __stdcall, xlive_5281, int a1, unsigned int a2, int a3, unsigned int a4, int a5, unsigned int* a6, int a7, int a8)
{
    RUN_LISTENERS(5281, "XUserReadStats", a1, a2, a3, a4, a5, a6, a7, a8);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8));
}
DETOUR_API(int, __stdcall, xlive_5284, int a1, int a2, int a3, int a4, void* Src, int a6, int a7)
{
    struct XUSER_STATS_SPEC {
	    DWORD view_id;
	    DWORD num_column_ids;
	    WORD rgw_column_ids[64];
    };

    auto a5 = (XUSER_STATS_SPEC*)Src;
    println("[xdead] view_id = {}", a5->view_id);
    println("[xdead] num_column_ids = {}", a5->num_column_ids);
    println("[xdead] rgw_column_ids[0] = {}", a5->rgw_column_ids[0]);
    println("[xdead] rgw_column_ids[1] = {}", a5->rgw_column_ids[1]);
    println("[xdead] rgw_column_ids[2] = {}", a5->rgw_column_ids[2]);
    println("[xdead] rgw_column_ids[3] = {}", a5->rgw_column_ids[3]);
    println("[xdead] rgw_column_ids[4] = {}", a5->rgw_column_ids[4]);

    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5284, "XUserCreateStatsEnumeratorByRank", a1, a2, a3, a4, Src, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(Src), hex(a6), hex(a7));
}
DETOUR_API(int, __stdcall, xlive_5286, int a1, int a2, int a3, int a4, int a5, void* Src, int a7, int a8)
{
    RUN_LISTENERS(5286, "XUserCreateStatsEnumeratorByXuid", a1, a2, a3, a4, a5, Src, a7, a8);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(Src), hex(a7), hex(a8));
}
DETOUR_API(int, __stdcall, xlive_5292, int a1, int a2, int a3, int a4)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5292, "XUserSetContextEx", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_5293, int a1, int a2, int a3, int a4, int a5)
{
    SET_RETURN_VALUE(0);
    // called on level load?
    RUN_LISTENERS(5293, "XUserSetPropertyEx", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5294, int a1, unsigned int a2, int a3, int a4)
{
    RUN_LISTENERS(5294, "XLivePBufferGetByteArray", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_5303, int a1, const char* a2, int a3, int a4, unsigned int a5, int a6, int a7)
{
    RUN_LISTENERS(5303, "XStringVerify", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(int, __stdcall, xlive_5305, char a1, const unsigned __int16* a2, char a3, int a4, int a5)
{
    RUN_LISTENERS(5305, "XStorageUploadFromMemory", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5306, int a1, const unsigned __int16* a2, int a3, int a4, unsigned int a5, int a6, int a7)
{
    RUN_LISTENERS(5306, "XStorageEnumerate", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(int, __stdcall, xlive_5310)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5310, "XOnlineStartup");
    LOG_AND_RETURN("");
}
DETOUR_API(int, __stdcall, xlive_5311)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5311, "XOnlineCleanup");
    LOG_AND_RETURN("");
}
DETOUR_API(signed int, __stdcall, xlive_5312, int a1, int a2, int a3, int a4, int a5)
{
    // NOTE: The game needs a value or it will loop forever when exiting.
    SET_RETURN_VALUE(1);

    // called after login, or when loading/exiting main menu
    RUN_LISTENERS(5312, "XFriendsCreateEnumerator", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(signed int, __stdcall, xlive_5313, int a1)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5313, "XPresenceInitialize", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(signed int, __stdcall, xlive_5314, int a1, int a2, int a3, int a4)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5314, "XUserMuteListQuery", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5315, int a1, int a2)
{
    RUN_LISTENERS(5315, "XInviteGetAcceptedInfo", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5316, int a1, int a2, int a3, wchar_t* a4, int a5)
{
    RUN_LISTENERS(5316, "XInviteSend", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5320, int a1, int a2, int a3, int* a4, int a5, int a6)
{
    RUN_LISTENERS(5320, "XSessionSearchByID", a1, a2, a3, a4, a5, a6);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6));
}
DETOUR_API(int, __stdcall, xlive_5321, int a1, int a2, int a3, unsigned __int16 a4, __int16 a5, int a6, int a7, unsigned int* a8, int a9, int a10)
{
    RUN_LISTENERS(5321, "XSessionSearch", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8), hex(a9), hex(a10));
}
DETOUR_API(signed int, __stdcall, xlive_5322, int a1, int a2, int a3, int a4, int a5)
{
    RUN_LISTENERS(5322, "XSessionModify", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(signed int, __stdcall, xlive_5324, void* a1)
{
    SET_RETURN_VALUE(1);
    RUN_LISTENERS(5324, "XOnlineGetNatType", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(unsigned int, __stdcall, xlive_5326, int a1, int a2, int a3, int a4, int a5)
{
    RUN_LISTENERS(5326, "XSessionJoinRemote", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(signed int, __stdcall, xlive_5327, int a1, int a2, int* a3, int a4, int a5)
{
    RUN_LISTENERS(5327, "XSessionJoinLocal", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(signed int, __stdcall, xlive_5328, int a1, DWORD* a2, int a3, int a4)
{
    RUN_LISTENERS(5328, "XSessionGetDetails", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5329, int a1, int a2)
{
    RUN_LISTENERS(5329, "XSessionFlushStats", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(uintptr_t, __stdcall, xlive_5330, int a1, int a2)
{
    RUN_LISTENERS(5330, "XSessionDelete", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(signed int, __stdcall, xlive_5331, int a1, int a2, int a3, int a4, DWORD* a5, int a6, int a7)
{
    SET_RETURN_VALUE(0);
    // called after login
    RUN_LISTENERS(5331, "XUserReadProfileSettings", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(signed int, __stdcall, xlive_5333, int a1, int a2, int a3, int a4, int* a5, int a6, int a7)
{
    RUN_LISTENERS(5333, "XSessionArbitrationRegister", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(unsigned int, __stdcall, xlive_5335, void* Src, int a2, int a3, int a4)
{
    RUN_LISTENERS(5335, "XTitleServerCreateEnumerator", Src, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(Src), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5336, int a1, int a2, int a3, int a4)
{
    RUN_LISTENERS(5336, "XSessionLeaveRemote", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5337, int a1, unsigned int a2, int a3, int a4)
{
    RUN_LISTENERS(5337, "XUserWriteProfileSettings", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5338, int a1, int a2, int a3)
{
    RUN_LISTENERS(5338, "XPresenceSubscribe", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(signed int, __stdcall, xlive_5340, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    RUN_LISTENERS(5340, "XPresenceCreateEnumerator", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(signed int, __stdcall, xlive_5342, int a1, unsigned int a2, int a3, int a4)
{
    RUN_LISTENERS(5342, "XSessionModifySkill", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5343, unsigned int a1, int a2, double* a3, double* a4, double* a5)
{
    RUN_LISTENERS(5343, "XSessionCalculateSkill", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(signed int, __stdcall, xlive_5344, int a1, int a2, int a3, unsigned int a4, int a5, int a6, int a7)
{
    RUN_LISTENERS(5344, "XStorageBuildServerPath", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(int, __stdcall, xlive_5345, int a1, const unsigned __int16* a2, int a3, int a4, unsigned int a5, int a6, int a7)
{
    RUN_LISTENERS(5345, "XStorageDownloadToMemory", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(int, __stdcall, xlive_5350, int a1, void* a2, int a3, int a4, int a5, int a6, int a7)
{
    RUN_LISTENERS(5350, "XLiveContentCreateAccessHandle", a1, a2, a3, a4, a5, a6, a7);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7));
}
DETOUR_API(int, __stdcall, xlive_5355, int a1, int a2, char* a3, unsigned int* a4)
{
    RUN_LISTENERS(5355, "XLiveContentGetPath", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_5356, int a1, int a2, char* a3, unsigned int* a4)
{
    RUN_LISTENERS(5356, "XLiveContentGetDisplayName", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5360, unsigned int a1, int a2, DWORD* a3, int* a4)
{
    // called after login
    RUN_LISTENERS(5360, "XLiveContentCreateEnumerator", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(signed int, __stdcall, xlive_5365, int a1, int a2, int a3, int a4, int a5)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5365, "XShowMarketplaceUI", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5367, int a1, int a2, unsigned int a3, int a4, int a5)
{
    RUN_LISTENERS(5367, "XContentGetMarketplaceCounts", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5372, HANDLE hObject, int a2, int a3, int a4, int a5, int a6)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5372, "XMarketplaceCreateOfferEnumerator", hObject, a2, a3, a4, a5, a6);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(hObject), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6));
}
DETOUR_API(__int16, __stdcall, xlive_38, __int16 a1)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(38, "XSocketNTOHS", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5208, int a1, int a2, int a3, int a4)
{
    RUN_LISTENERS(5208, "XShowGameInviteUI", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_5209, int a1, int a2, int a3, int a4)
{
    RUN_LISTENERS(5209, "XShowMessageComposeUI", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_5210, int a1, int a2)
{
    RUN_LISTENERS(5210, "XShowFriendRequestUI", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5214, int a1, int a2)
{
    RUN_LISTENERS(5214, "XShowPlayerReviewUI", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5250, int a1)
{
    RUN_LISTENERS(5250, "XShowAchievementsUI", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5259, int a1, int a2, int a3, int a4)
{
    RUN_LISTENERS(5259, "XLiveSignin", a1, a2, a3, a4);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4));
}
DETOUR_API(int, __stdcall, xlive_5260, int a1, int a2)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5260, "XShowSigninUI", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5300, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    RUN_LISTENERS(5300, "XSessionCreate", a1, a2, a3, a4, a5, a6, a7, a8);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5), hex(a6), hex(a7), hex(a8));
}
DETOUR_API(int, __stdcall, xlive_5318, int a1, int a2, int a3)
{
    RUN_LISTENERS(5318, "XSessionStart", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(int, __stdcall, xlive_5034, int a1, int a2, int a3, int a4, int a5)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5034, "XLiveProtectData", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x} -> {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), dptr(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5035, BYTE* protected_data, DWORD size_of_protected_data, BYTE* unprotected_data, DWORD* size_of_data, HANDLE* protected_data_handle)
{
    SET_RETURN_VALUE(-1);
    RUN_LISTENERS(5035, "XLiveUnprotectData", protected_data, size_of_protected_data, unprotected_data, size_of_data, protected_data_handle);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x} -> {:x}, {:x} -> {:x}", hex(protected_data), hex(size_of_protected_data), hex(unprotected_data), hex(size_of_data), dptr(size_of_data), hex(protected_data_handle), dptr(protected_data_handle));
}
DETOUR_API(int, __stdcall, xlive_5036, int a1, int a2)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5036, "XLiveCreateProtectedDataContext", a1, a2);
    LOG_AND_RETURN("{:x}, {:x} -> {:x}", hex(a1), hex(a2), dptr(a2));
}
DETOUR_API(int, __stdcall, xlive_5038, int a1)
{
    // Isn't it interesting how this function crashes if we do not hook it?
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5038, "XLiveCloseProtectedDataContext", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5206, int a1)
{
    RUN_LISTENERS(5206, "XShowMessagesUI", a1);
    LOG_AND_RETURN("{:x}", hex(a1));
}
DETOUR_API(int, __stdcall, xlive_5264, int a1, int a2, int a3, int a4, int a5)
{
    RUN_LISTENERS(5264, "XUserAreUsersFriends", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5278, int a1, int a2, int a3)
{
    RUN_LISTENERS(5278, "XUserWriteAchievements", a1, a2, a3);
    LOG_AND_RETURN("{:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3));
}
DETOUR_API(int, __stdcall, xlive_5297, int a1, int a2)
{
    SET_RETURN_VALUE(0);
    RUN_LISTENERS(5297, "XLiveInitializeEx", a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5317, int a1, int a2, int a3, int a4, int a5)
{
    RUN_LISTENERS(5317, "XSessionWriteStats", a1, a2, a3, a4, a5);
    LOG_AND_RETURN("{:x}, {:x}, {:x}, {:x}, {:x}", hex(a1), hex(a2), hex(a3), hex(a4), hex(a5));
}
DETOUR_API(int, __stdcall, xlive_5332, int a1, int a2)
{
    RUN_LISTENERS(5332, "XSessionEnd",  a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
DETOUR_API(int, __stdcall, xlive_5026, int a1, int a2)
{
    RUN_LISTENERS(5026, "XLiveSetSponsorToken",  a1, a2);
    LOG_AND_RETURN("{:x}, {:x}", hex(a1), hex(a2));
}
// clang-format on
