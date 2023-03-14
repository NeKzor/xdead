# XDead

Minimal replacement layer for XLive (GFWL).

## Overview

- [Tested Games](#tested-games)
- [Listener API (WIP)](#api-wip)
- [Automatic Module Loader (TODO)](#automatic-module-loader-todo)
- [Supported Functions](#supported-functions)
- [TODO](#todo)
- [Credits](#credits)

## Tested Games

|Game|Implementation|
|---|:-:|
|Tron: Evolution|Used in [TEM][] for offline usage and support on Linux w/Wine.|

[TEM]: https://github.com/NeKzor/tem

## API (WIP)

Listeners are user-defined callbacks which are used to hook into functions.
They allow to read and modify existing parameters but also overwrite the default return value.

TODO: Expose function signatures as types/macros? Or allow exports like `XDead_XFriendsCreateEnumerator`?

### Include

Overview of the header file:

```cpp
namespace xdead {

#define XDEAD_CALLBACK(type, name, ...) type __stdcall name##_callback(##__VA_ARGS__)
#define XDEAD_FUNCTION_NAME(name, ordinal) static constexpr auto name = ordinal

enum class ListenerStatus {
    Ok               = 0,
    OrdinalNotFound  = 1,
    InvalidCallback  = 2,
    CallbackNotFound = 3,
};

// ...
XDEAD_FUNCTION_NAME(XFriendsCreateEnumerator, 5312);
// ...

auto __stdcall add_listener(uint32_t ordinal, void* callback, uint32_t index) -> ListenerStatus;
auto __stdcall remove_listener(uint32_t ordinal, void* callback) -> ListenerStatus;
auto __stdcall remove_all_listeners() -> ListenerStatus;

using add_listener_t = decltype(&add_listener);
using remove_listener_t = decltype(&remove_listener);
using remove_all_listeners_t = decltype(&remove_all_listeners);
}
```

### Example Usage

The basic philosophy is to reimplement a small surface of the API, only to get the game working.
After this step the user has the freedom for creativity to rewrite any features of XLive like account management,
save files and UI etc.

```cpp
// Define a callback
XDEAD_CALLBACK(signed int, XFriendsCreateEnumerator, int a1, int a2, int a3, int a4, int a5)
{
    // By default XDead always returns 0 which in most functions means "success".
    // If a callback returns anything else, all other callbacks of this
    // functions will not run.
    return 1;
}

// Get exported functions

auto xdead = GetModuleHandleA("xlive.dll");

auto xdead_add_listener = xdead::add_listener_t(
    GetProcAddress(xdead, "xdead_add_listener")
);

auto xdead_remove_listener = xdead::remove_listener_t(
    GetProcAddress(xdead, "xdead_remove_listener")
);

auto xdead_remove_all_listeners = xdead::remove_all_listeners_t(
    GetProcAddress(xdead, "xdead_remove_all_listeners")
);

// Add callback as listener

auto status = xdead_add_listener(
    xdead::XFriendsCreateEnumerator,   // Provide ordinal by function name
    XFriendsCreateEnumerator_callback, // Function from above
    0                                  // Sort index
);

if (status == xdead::ListenerStatus::Ok) {
    println("Added listener for XFriendsCreateEnumerator");
}

// Remove listener

xdead_remove_listener(XFriendsCreateEnumerator_callback);

// Or automatically remove all previously added listeners

// NOTE: This also remove listeners which have been added by other modules.
xdead_remove_all_listeners();
```

## Automatic Module Loader (TODO)

XDead can also be used to load additional modules automatically.
When the main process calls into `XLiveInitialize/XLiveInitializeEx`, it will check for an existing `xdead.json`
definition file and then load each module sequentially.

TODO: Use YAML instead of JSON?

```json
{
    "version": "0.1.0",
    "mods": [
        {
            "name": "tem",
            "version": "0.1.0",
            "author": "NeKz",
            "path": "tem.dll",
        }
    ]
}
```

## Supported Functions

<details>
  <summary>View table</summary>

||Function|Ordinal|
|:-:|---|:-:|
||XWSAStartup|1|
||XWSACleanup|2|
|✔|XSocketCreate|3|
|✔|XSocketClose|4|
||XSocketShutdown|5|
|✔|XSocketIOCTLSocket|6|
|✔|XSocketSetSockOpt|7|
|✔|XSocketGetSockOpt|8|
|✔|XSocketGetSockName|9|
||XSocketGetPeerName|10|
|✔|XSocketBind|11|
|✔|XSocketConnect|12|
|✔|XSocketListen|13|
|✔|XSocketAccept|14|
|✔|XSocketSelect|15|
||XWSAGetOverlappedResult|16|
||XWSACancelOverlappedIO|17|
|✔|XSocketRecv|18|
||WSARecv|19|
||XSocketRecvFrom|20|
||XWSARecvFrom|21|
|✔|XSocketSend|22|
||XWSASend|23|
|✔|XSocketSendTo|24|
||XWSASendTo|25|
||XSocketInet_Addr|26|
||XSocketWSAGetLastError|27|
||XWSASetLastError|28|
||XWSACreateEvent|29|
||XWSACloseEvent|30|
||XWSASetEvent|31|
||XWSAResetEvent|32|
||XWSAWaitForMultipleEvents|33|
||XWSAFDIsSet|34|
||XWSAEventSelect|35|
||XSocketHTONL|37|
|✔|XSocketNTOHS|38|
||XSocketNTOHL|39|
||XSocketHTONS|40|
|✔|XNetStartup|51|
|✔|XNetCleanup|52|
|✔|XNetRandom|53|
||XNetCreateKey|54|
|✔|XNetRegisterKey|55|
|✔|XNetUnregisterKey|56|
|✔|XNetXnAddrToInAddr|57|
|✔|XNetServerToInAddr|58|
||XNetTsAddrToInAddr|59|
||XNetInAddrToXnAddr|60|
||XNetInAddrToServer|61|
||XNetInAddrToString|62|
|✔|XNetUnregisterInAddr|63|
||XNetXnAddrToMachineId|64|
||XNetConnect|65|
||XNetGetConnectStatus|66|
|✔|XNetDnsLookup|67|
|✔|XNetDnsRelease|68|
|✔|XNetQosListen|69|
|✔|XNetQosLookup|70|
|✔|XNetQosServiceLookup|71|
|✔|XNetQosRelease|72|
|✔|XNetGetTitleXnAddr|73|
||XNetGetDebugXnAddr|74|
|✔|XNetGetEthernetLinkStatus|75|
||XNetGetBroadcastVersionStatus|76|
|✔|XNetQosGetListenStats|77|
||XNetGetOpt|78|
||XNetSetOpt|79|
||XNetStartupEx|80|
||XNetReplaceKey|81|
||XNetGetXnAddrPlatform|82|
||XNetGetSystemLinkPort|83|
|✔|XNetSetSystemLinkPort|84|
||XNetSetSystemLinkPort|84|
||XCustomSetAction|472|
||XCustomGetLastActionPress|473|
||XCustomSetDynamicActions|474|
||XCustomGetLastActionPressEx|476|
||XCustomRegisterDynamicActions|477|
||XCustomUnregisterDynamicActions|478|
||XCustomGetCurrentGamercard|479|
||XNotifyGetNext|651|
|✔|XNotifyPositionUI|652|
||XNotifyDelayUI|653|
|✔|XGetOverlappedExtendedError|1082|
||XGetOverlappedResult|1083|
||XLiveInitialize|5000|
||XLiveInput|5001|
||XLiveRender|5002|
|✔|XLiveUninitialize|5003|
||XLiveOnCreateDevice|5005|
|✔|XLiveOnDestroyDevice|5006|
|✔|XLiveOnResetDevice|5007|
|✔|XHVCreateEngine|5008|
||XLiveRegisterDataSection|5010|
||XLiveUnregisterDataSection|5011|
||XLiveUpdateHashes|5012|
|✔|XLivePBufferAllocate|5016|
|✔|XLivePBufferFree|5017|
||XLivePBufferGetByte|5018|
||XLivePBufferSetByte|5019|
||XLivePBufferGetDWORD|5020|
||XLivePBufferSetDWORD|5021|
||XLiveGetUpdateInformation|5022|
||XNetGetCurrentAdapter|5023|
||XLiveUpdateSystem|5024|
||XLiveGetLiveIdError|5025|
|✔|XLiveSetSponsorToken|5026|
||XLiveUninstallTitle|5027|
||XLiveLoadLibraryEx|5028|
||XLiveFreeLibrary|5029|
||XLivePreTranslateMessage|5030|
|✔|XLiveSetDebugLevel|5031|
||XLiveVerifyArcadeLicense|5032|
|✔|XLiveProtectData|5034|
|✔|XLiveUnprotectData|5035|
|✔|XLiveCreateProtectedDataContext|5036|
||XLiveQueryProtectedDataInformation|5037|
|✔|XLiveCloseProtectedDataContext|5038|
||XLiveVerifyDataFile|5039|
|✔|XShowMessagesUI|5206|
|✔|XShowGameInviteUI|5208|
|✔|XShowMessageComposeUI|5209|
|✔|XShowFriendRequestUI|5210|
|✔|XShowCustomPlayerListUI|5212|
|✔|XShowPlayerReviewUI|5214|
|✔|XShowGuideUI|5215|
|✔|XShowKeyboardUI|5216|
||XShowArcadeUI|5218|
||XLocatorServerAdvertise|5230|
||XLocatorServerUnAdvertise|5231|
||XLocatorGetServiceProperty|5233|
||XLocatorCreateServerEnumerator|5234|
||XLocatorCreateServerEnumeratorByIDs|5235|
||XLocatorServiceInitialize|5236|
||XLocatorServiceUnInitialize|5237|
||XLocatorCreateKey|5238|
|✔|XShowAchievementsUI|5250|
|✔|XCloseHandle|5251|
|✔|XShowGamerCardUI|5252|
||XCancelOverlapped|5254|
||XEnumerateBack|5255|
|✔|XEnumerate|5256|
||XLiveManageCredentials|5257|
|✔|XLiveSignout|5258|
|✔|XLiveSignin|5259|
|✔|XShowSigninUI|5260|
||XUserGetXUID|5261|
|✔|XUserGetSigninState|5262|
|✔|XUserGetName|5263|
|✔|XUserAreUsersFriends|5264|
|✔|XUserCheckPrivilege|5265|
||XShowMessageBoxUI|5266|
|✔|XUserGetSigninInfo|5267|
|✔|XNotifyCreateListener|5270|
|✔|XShowPlayersUI|5271|
||XUserReadGamerPictureByKey|5273|
|✔|XUserAwardGamerPicture|5274|
|✔|XShowFriendsUI|5275|
||XUserSetProperty|5276|
|✔|XUserSetContext|5277|
|✔|XUserWriteAchievements|5278|
|✔|XUserReadAchievementPicture|5279|
|✔|XUserCreateAchievementEnumerator|5280|
|✔|XUserReadStats|5281|
||XUserReadGamerPicture|5282|
|✔|XUserCreateStatsEnumeratorByRank|5284|
||XUserCreateStatsEnumeratorByRating|5285|
|✔|XUserCreateStatsEnumeratorByXuid|5286|
||XUserResetStatsView|5287|
||XUserGetProperty|5288|
||XUserGetContext|5289|
||XUserGetReputationStars|5290|
||XUserResetStatsViewAllUsers|5291|
|✔|XUserSetContextEx|5292|
|✔|XUserSetPropertyEx|5293|
|✔|XLivePBufferGetByteArray|5294|
||XLivePBufferSetByteArray|5295|
||XLiveGetLocalOnlinePort|5296|
|✔|XLiveInitializeEx|5297|
||XLiveGetGuideKey|5298|
||XShowGuideKeyRemapUI|5299|
|✔|XSessionCreate|5300|
|✔|XStringVerify|5303|
||XStorageUploadFromMemoryGetProgress|5304|
|✔|XStorageUploadFromMemory|5305|
|✔|XStorageEnumerate|5306|
||XStorageDownloadToMemoryGetProgress|5307|
||XStorageDelete|5308|
||XStorageBuildServerPathByXuid|5309|
|✔|XOnlineStartup|5310|
|✔|XOnlineCleanup|5311|
|✔|XFriendsCreateEnumerator|5312|
|✔|XPresenceInitialize|5313|
|✔|XUserMuteListQuery|5314|
|✔|XInviteGetAcceptedInfo|5315|
|✔|XInviteSend|5316|
|✔|XSessionWriteStats|5317|
|✔|XSessionStart|5318|
||XSessionSearchEx|5319|
|✔|XSessionSearchByID|5320|
|✔|XSessionSearch|5321|
|✔|XSessionModify|5322|
||XSessionMigrateHost|5323|
|✔|XOnlineGetNatType|5324|
|✔|XSessionJoinRemote|5326|
|✔|XSessionJoinLocal|5327|
|✔|XSessionGetDetails|5328|
|✔|XSessionFlushStats|5329|
|✔|XSessionDelete|5330|
|✔|XUserReadProfileSettings|5331|
|✔|XSessionEnd|5332|
|✔|XSessionArbitrationRegister|5333|
||XOnlineGetServiceInfo|5334|
|✔|XTitleServerCreateEnumerator|5335|
|✔|XSessionLeaveRemote|5336|
|✔|XUserWriteProfileSettings|5337|
|✔|XPresenceSubscribe|5338|
||XUserReadProfileSettingsByXuid|5339|
|✔|XPresenceCreateEnumerator|5340|
||XPresenceUnsubscribe|5341|
|✔|XSessionModifySkill|5342|
|✔|XSessionCalculateSkill|5343|
|✔|XStorageBuildServerPath|5344|
|✔|XStorageDownloadToMemory|5345|
||XUserEstimateRankForRating|5346|
||XLiveProtectedLoadLibrary|5347|
||XLiveProtectedCreateFile|5348|
||XLiveProtectedVerifyFile|5349|
|✔|XLiveContentCreateAccessHandle|5350|
||XLiveContentInstallPackage|5351|
||XLiveContentUninstall|5352|
||XLiveContentVerifyInstalledPackage|5354|
|✔|XLiveContentGetPath|5355|
|✔|XLiveContentGetDisplayName|5356|
||XLiveContentGetThumbnail|5357|
||XLiveContentInstallLicense|5358|
||XLiveGetUPnPState|5359|
|✔|XLiveContentCreateEnumerator|5360|
||XLiveContentRetrieveOffersByDate|5361|
||XLiveMarketplaceDoesContentIdMatch|5362|
||XLiveContentGetLicensePath|5363|
|✔|XShowMarketplaceUI|5365|
||XShowMarketplaceDownloadItemsUI|5366|
|✔|XContentGetMarketplaceCounts|5367|
||XMarketplaceConsumeAssets|5370|
||XMarketplaceCreateAssetEnumerator|5371|
|✔|XMarketplaceCreateOfferEnumerator|5372|
||XMarketplaceGetDownloadStatus|5374|
||XMarketplaceGetImageUrl|5375|
||XMarketplaceCreateOfferEnumeratorByOffering|5376|
||XUserFindUsers|5377|
</details>

### TODO

<details>
  <summary>View list</summary>

- XWSAStartup
- XWSACleanup
- XSocketShutdown
- XSocketGetPeerName
- XWSAGetOverlappedResult
- XWSACancelOverlappedIO
- WSARecv
- XSocketRecvFrom
- XWSARecvFrom
- XWSASend
- XWSASendTo
- XSocketInet_Addr
- XSocketWSAGetLastError
- XWSASetLastError
- XWSACreateEvent
- XWSACloseEvent
- XWSASetEvent
- XWSAResetEvent
- XWSAWaitForMultipleEvents
- XWSAFDIsSet
- XWSAEventSelect
- XSocketHTONL
- XSocketNTOHL
- XSocketHTONS
- XNetCreateKey
- XNetTsAddrToInAddr
- XNetInAddrToXnAddr
- XNetInAddrToServer
- XNetInAddrToString
- XNetXnAddrToMachineId
- XNetConnect
- XNetGetConnectStatus
- XNetGetDebugXnAddr
- XNetGetBroadcastVersionStatus
- XNetGetOpt
- XNetSetOpt
- XNetStartupEx
- XNetReplaceKey
- XNetGetXnAddrPlatform
- XNetGetSystemLinkPort
- XNetSetSystemLinkPort
- XCustomSetAction
- XCustomGetLastActionPress
- XCustomSetDynamicActions
- XCustomGetLastActionPressEx
- XCustomRegisterDynamicActions
- XCustomUnregisterDynamicActions
- XCustomGetCurrentGamercard
- XNotifyGetNext
- XNotifyDelayUI
- XGetOverlappedResult
- XLiveInitialize
- XLiveInput
- XLiveRender
- XLiveOnCreateDevice
- XLiveRegisterDataSection
- XLiveUnregisterDataSection
- XLiveUpdateHashes
- XLivePBufferGetByte
- XLivePBufferSetByte
- XLivePBufferGetDWORD
- XLivePBufferSetDWORD
- XLiveGetUpdateInformation
- XNetGetCurrentAdapter
- XLiveUpdateSystem
- XLiveGetLiveIdError
- XLiveUninstallTitle
- XLiveLoadLibraryEx
- XLiveFreeLibrary
- XLivePreTranslateMessage
- XLiveVerifyArcadeLicense
- XLiveQueryProtectedDataInformation
- XLiveVerifyDataFile
- XShowArcadeUI
- XLocatorServerAdvertise
- XLocatorServerUnAdvertise
- XLocatorGetServiceProperty
- XLocatorCreateServerEnumerator
- XLocatorCreateServerEnumeratorByIDs
- XLocatorServiceInitialize
- XLocatorServiceUnInitialize
- XLocatorCreateKey
- XCancelOverlapped
- XEnumerateBack
- XLiveManageCredentials
- XUserGetXUID
- XShowMessageBoxUI
- XUserReadGamerPictureByKey
- XUserSetProperty
- XUserReadGamerPicture
- XUserCreateStatsEnumeratorByRating
- XUserResetStatsView
- XUserGetProperty
- XUserGetContext
- XUserGetReputationStars
- XUserResetStatsViewAllUsers
- XLivePBufferSetByteArray
- XLiveGetLocalOnlinePort
- XLiveGetGuideKey
- XShowGuideKeyRemapUI
- XStorageUploadFromMemoryGetProgress
- XStorageDownloadToMemoryGetProgress
- XStorageDelete
- XStorageBuildServerPathByXuid
- XSessionSearchEx
- XSessionMigrateHost
- XOnlineGetServiceInfo
- XUserReadProfileSettingsByXuid
- XPresenceUnsubscribe
- XUserEstimateRankForRating
- XLiveProtectedLoadLibrary
- XLiveProtectedCreateFile
- XLiveProtectedVerifyFile
- XLiveContentInstallPackage
- XLiveContentUninstall
- XLiveContentVerifyInstalledPackage
- XLiveContentGetThumbnail
- XLiveContentInstallLicense
- XLiveGetUPnPState
- XLiveContentRetrieveOffersByDate
- XLiveMarketplaceDoesContentIdMatch
- XLiveContentGetLicensePath
- XShowMarketplaceDownloadItemsUI
- XMarketplaceConsumeAssets
- XMarketplaceCreateAssetEnumerator
- XMarketplaceGetDownloadStatus
- XMarketplaceGetImageUrl
- XMarketplaceCreateOfferEnumeratorByOffering
- XUserFindUsers
</details>

## Credits

### XLiveLessNess (XLLN)

[XLLN][] is by far the most advanced FOSS project out there which aims to be a full rewrite of XLive.
However, XDead only provides a minimal layer to work with and does not try to reimplement any of the original functions.

#### Comparison

||XLLN|XDead|
|---|---|---|
|Goal?|Full Rewrite|Minimal Layer|
|Additional API?|Yes|Yes|
|Modules?|[XLLN-Modules][]|No|
|Module Loader?|XLNN or [XLLN-Wrapper][]|Yes|
|Standalone header?|No|Yes|
|Local online support?|Yes|No|
|Supported games?|8<sup>1</sup>|1|

<sup>1</sup> Counting only the official XLLN-Modules. However, XLLN might work for many other games.

[XLLN]: https://gitlab.com/GlitchyScripts/xlivelessness
[XLLN-Wrapper]: https://gitlab.com/GlitchyScripts/xlln-wrappers
[XLLN-Modules]: https://gitlab.com/GlitchyScripts/xlln-modules
