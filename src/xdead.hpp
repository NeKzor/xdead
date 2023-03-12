/*
 * Copyright (c) 2022-2023, NeKz
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cinttypes>
#include <map>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace xdead {

/// <summary>
/// Return status code.
/// </summary>
enum class ListenerStatus {
    /// <summary>
    /// Function call completed without problems.
    /// </summary>
    Ok = 0,
    /// <summary>
    /// Provided ordinal value could not been found.
    /// </summary>
    OrdinalNotFound = 1,
    /// <summary>
    /// Provided callback value is NULL.
    /// </summary>
    InvalidCallback = 2,
    /// <summary>
    /// Provided callback value could not been found.
    /// </summary>
    CallbackNotFound = 3,
};

template <typename T = void*> struct Listener {
    uint32_t index;
    T callback;
};

struct FunctionListener {
    const char* name;
    std::vector<Listener<>>* listeners;
};

auto get_function_listeners() -> std::map<uint32_t, xdead::FunctionListener>&;

extern auto __stdcall add_listener(uint32_t ordinal, void* callback, uint32_t index) -> ListenerStatus;
extern auto __stdcall remove_listener(uint32_t ordinal, void* callback) -> ListenerStatus;
extern auto __stdcall remove_all_listeners() -> ListenerStatus;

using add_listener_t = decltype(&add_listener);
using remove_listener_t = decltype(&remove_listener);
using remove_all_listeners_T = decltype(&remove_all_listeners);

#define XDEAD_FUNCTION_NAME(name, ordinal) static constexpr auto name = ordinal;

XDEAD_FUNCTION_NAME(XSocketCreate, 3);
XDEAD_FUNCTION_NAME(XSocketClose, 4);
XDEAD_FUNCTION_NAME(XSocketIOCTLSocket, 6);
XDEAD_FUNCTION_NAME(XSocketSetSockOpt, 7);
XDEAD_FUNCTION_NAME(XSocketGetSockOpt, 8);
XDEAD_FUNCTION_NAME(XSocketGetSockName, 9);
XDEAD_FUNCTION_NAME(XSocketBind, 11);
XDEAD_FUNCTION_NAME(XSocketConnect, 12);
XDEAD_FUNCTION_NAME(XSocketListen, 13);
XDEAD_FUNCTION_NAME(XSocketAccept, 14);
XDEAD_FUNCTION_NAME(XSocketSelect, 15);
XDEAD_FUNCTION_NAME(XSocketRecv, 18);
XDEAD_FUNCTION_NAME(XSocketSend, 22);
XDEAD_FUNCTION_NAME(XSocketSendTo, 24);
XDEAD_FUNCTION_NAME(XNetStartup, 51);
XDEAD_FUNCTION_NAME(XNetCleanup, 52);
XDEAD_FUNCTION_NAME(XNetRandom, 53);
XDEAD_FUNCTION_NAME(XNetRegisterKey, 55);
XDEAD_FUNCTION_NAME(XNetUnregisterKey, 56);
XDEAD_FUNCTION_NAME(XNetXnAddrToInAddr, 57);
XDEAD_FUNCTION_NAME(XNetServerToInAddr, 58);
XDEAD_FUNCTION_NAME(XNetUnregisterInAddr, 63);
XDEAD_FUNCTION_NAME(XNetDnsLookup, 67);
XDEAD_FUNCTION_NAME(XNetDnsRelease, 68);
XDEAD_FUNCTION_NAME(XNetQosListen, 69);
XDEAD_FUNCTION_NAME(XNetQosLookup, 70);
XDEAD_FUNCTION_NAME(XNetQosServiceLookup, 71);
XDEAD_FUNCTION_NAME(XNetQosRelease, 72);
XDEAD_FUNCTION_NAME(XNetGetTitleXnAddr, 73);
XDEAD_FUNCTION_NAME(XNetGetEthernetLinkStatus, 75);
XDEAD_FUNCTION_NAME(XNetQosGetListenStats, 77);
XDEAD_FUNCTION_NAME(XNetSetSystemLinkPort, 84);
XDEAD_FUNCTION_NAME(XNotifyPositionUI, 652);
XDEAD_FUNCTION_NAME(XGetOverlappedExtendedError, 1082);
XDEAD_FUNCTION_NAME(XLiveUninitialize, 5003);
XDEAD_FUNCTION_NAME(XLiveOnDestroyDevice, 5006);
XDEAD_FUNCTION_NAME(XLiveOnResetDevice, 5007);
XDEAD_FUNCTION_NAME(XHVCreateEngine, 5008);
XDEAD_FUNCTION_NAME(XLivePBufferAllocate, 5016);
XDEAD_FUNCTION_NAME(XLivePBufferFree, 5017);
XDEAD_FUNCTION_NAME(XLiveSetDebugLevel, 5031);
XDEAD_FUNCTION_NAME(XShowCustomPlayerListUI, 5212);
XDEAD_FUNCTION_NAME(XShowGuideUI, 5215);
XDEAD_FUNCTION_NAME(XShowKeyboardUI, 5216);
XDEAD_FUNCTION_NAME(XCloseHandle, 5251);
XDEAD_FUNCTION_NAME(XShowGamerCardUI, 5252);
XDEAD_FUNCTION_NAME(XEnumerate, 5256);
XDEAD_FUNCTION_NAME(XLiveSignout, 5258);
XDEAD_FUNCTION_NAME(XUserGetSigninState, 5262);
XDEAD_FUNCTION_NAME(XUserGetName, 5263);
XDEAD_FUNCTION_NAME(XUserCheckPrivilege, 5265);
XDEAD_FUNCTION_NAME(XUserGetSigninInfo, 5267);
XDEAD_FUNCTION_NAME(XNotifyCreateListener, 5270);
XDEAD_FUNCTION_NAME(XShowPlayersUI, 5271);
XDEAD_FUNCTION_NAME(XUserAwardGamerPicture, 5274);
XDEAD_FUNCTION_NAME(XShowFriendsUI, 5275);
XDEAD_FUNCTION_NAME(XUserSetContext, 5277);
XDEAD_FUNCTION_NAME(XUserReadAchievementPicture, 5279);
XDEAD_FUNCTION_NAME(XUserCreateAchievementEnumerator, 5280);
XDEAD_FUNCTION_NAME(XUserReadStats, 5281);
XDEAD_FUNCTION_NAME(XUserCreateStatsEnumeratorByRank, 5284);
XDEAD_FUNCTION_NAME(XUserCreateStatsEnumeratorByXuid, 5286);
XDEAD_FUNCTION_NAME(XUserSetContextEx, 5292);
XDEAD_FUNCTION_NAME(XUserSetPropertyEx, 5293);
XDEAD_FUNCTION_NAME(XLivePBufferGetByteArray, 5294);
XDEAD_FUNCTION_NAME(XStringVerify, 5303);
XDEAD_FUNCTION_NAME(XStorageUploadFromMemory, 5305);
XDEAD_FUNCTION_NAME(XStorageEnumerate, 5306);
XDEAD_FUNCTION_NAME(XOnlineStartup, 5310);
XDEAD_FUNCTION_NAME(XOnlineCleanup, 5311);
XDEAD_FUNCTION_NAME(XFriendsCreateEnumerator, 5312);
XDEAD_FUNCTION_NAME(XPresenceInitialize, 5313);
XDEAD_FUNCTION_NAME(XUserMuteListQuery, 5314);
XDEAD_FUNCTION_NAME(XInviteGetAcceptedInfo, 5315);
XDEAD_FUNCTION_NAME(XInviteSend, 5316);
XDEAD_FUNCTION_NAME(XSessionSearchByID, 5320);
XDEAD_FUNCTION_NAME(XSessionSearch, 5321);
XDEAD_FUNCTION_NAME(XSessionModify, 5322);
XDEAD_FUNCTION_NAME(XOnlineGetNatType, 5324);
XDEAD_FUNCTION_NAME(XSessionJoinRemote, 5326);
XDEAD_FUNCTION_NAME(XSessionJoinLocal, 5327);
XDEAD_FUNCTION_NAME(XSessionGetDetails, 5328);
XDEAD_FUNCTION_NAME(XSessionFlushStats, 5329);
XDEAD_FUNCTION_NAME(XSessionDelete, 5330);
XDEAD_FUNCTION_NAME(XUserReadProfileSettings, 5331);
XDEAD_FUNCTION_NAME(XSessionArbitrationRegister, 5333);
XDEAD_FUNCTION_NAME(XTitleServerCreateEnumerator, 5335);
XDEAD_FUNCTION_NAME(XSessionLeaveRemote, 5336);
XDEAD_FUNCTION_NAME(XUserWriteProfileSettings, 5337);
XDEAD_FUNCTION_NAME(XPresenceSubscribe, 5338);
XDEAD_FUNCTION_NAME(XPresenceCreateEnumerator, 5340);
XDEAD_FUNCTION_NAME(XSessionModifySkill, 5342);
XDEAD_FUNCTION_NAME(XSessionCalculateSkill, 5343);
XDEAD_FUNCTION_NAME(XStorageBuildServerPath, 5344);
XDEAD_FUNCTION_NAME(XStorageDownloadToMemory, 5345);
XDEAD_FUNCTION_NAME(XLiveContentCreateAccessHandle, 5350);
XDEAD_FUNCTION_NAME(XLiveContentGetPath, 5355);
XDEAD_FUNCTION_NAME(XLiveContentGetDisplayName, 5356);
XDEAD_FUNCTION_NAME(XLiveContentCreateEnumerator, 5360);
XDEAD_FUNCTION_NAME(XShowMarketplaceUI, 5365);
XDEAD_FUNCTION_NAME(XContentGetMarketplaceCounts, 5367);
XDEAD_FUNCTION_NAME(XMarketplaceCreateOfferEnumerator, 5372);
XDEAD_FUNCTION_NAME(XSocketNTOHS, 38);
XDEAD_FUNCTION_NAME(XShowGameInviteUI, 5208);
XDEAD_FUNCTION_NAME(XShowMessageComposeUI, 5209);
XDEAD_FUNCTION_NAME(XShowFriendRequestUI, 5210);
XDEAD_FUNCTION_NAME(XShowPlayerReviewUI, 5214);
XDEAD_FUNCTION_NAME(XShowAchievementsUI, 5250);
XDEAD_FUNCTION_NAME(XLiveSignin, 5259);
XDEAD_FUNCTION_NAME(XShowSigninUI, 5260);
XDEAD_FUNCTION_NAME(XSessionCreate, 5300);
XDEAD_FUNCTION_NAME(XSessionStart, 5318);
XDEAD_FUNCTION_NAME(XLiveProtectData, 5034);
XDEAD_FUNCTION_NAME(XLiveUnprotectData, 5035);
XDEAD_FUNCTION_NAME(XLiveCreateProtectedDataContext, 5036);
XDEAD_FUNCTION_NAME(XLiveCloseProtectedDataContext, 5038);
XDEAD_FUNCTION_NAME(XShowMessagesUI, 5206);
XDEAD_FUNCTION_NAME(XUserAreUsersFriends, 5264);
XDEAD_FUNCTION_NAME(XUserWriteAchievements, 5278);
XDEAD_FUNCTION_NAME(XLiveInitializeEx, 5297);
XDEAD_FUNCTION_NAME(XSessionWriteStats, 5317);
XDEAD_FUNCTION_NAME(XSessionEnd, 5332);
XDEAD_FUNCTION_NAME(XLiveSetSponsorToken, 5026);

#undef XDEAD_FUNCTION_NAME
}
