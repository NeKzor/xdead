/*
 * Copyright (c) 2022-2023, NeKz
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <cinttypes>
#include <format>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace xlive {

#define PROPERTY_NUMPLAYERS 0x10000001
#define PROPERTY_SKILLRATING 0x10000006
#define PROPERTY_PRIVATE 0x10000013
#define PROPERTY_DLCFLAGS 0x10000015
#define PROPERTY_TIMELIMIT 0x10000017
#define PROPERTY_TIMECURRENT 0x10000018
#define PROPERTY_VERSION 0x1000001A
#define PROPERTY_SESSIONID 0x20000016
#define CONTEXT_GAME_MODE_MULTIPLAYER 0
#define CONTEXT_MODE 3
#define CONTEXT_MAP 4
#define X_CONTEXT_GAME_TYPE_RANKED 0
#define X_CONTEXT_GAME_TYPE_STANDARD 1
#define X_CONTEXT_PRESENCE 0x8001
#define X_CONTEXT_GAME_TYPE 0x800A
#define X_CONTEXT_GAME_MODE 0x800B
#define XPRIVILEGE_PRESENCE_FRIENDS_ONLY 0xF3
#define XPRIVILEGE_PRESENCE 0xF4
#define XPRIVILEGE_PURCHASE_CONTENT 0xF5
#define XPRIVILEGE_USER_CREATED_CONTENT_FRIENDS_ONLY 0xF6
#define XPRIVILEGE_USER_CREATED_CONTENT 0xF7
#define XPRIVILEGE_PROFILE_VIEWING_FRIENDS_ONLY 0xF8
#define XPRIVILEGE_PROFILE_VIEWING 0xF9
#define XPRIVILEGE_COMMUNICATIONS_FRIENDS_ONLY 0xFB
#define XPRIVILEGE_COMMUNICATIONS 0xFC
#define XPRIVILEGE_MULTIPLAYER_SESSIONS 0xFE

enum class XUSER_SIGNIN_STATE : uint32_t {
    NotSignedIn = 0,
    SignedInLocally = 1,
    SignedInToLive = 2,
};

template <class CharT> struct std::formatter<XUSER_SIGNIN_STATE, CharT> : std::formatter<uint32_t, CharT> {
    template <class FormatContext> auto format(xlive::XUSER_SIGNIN_STATE temp, FormatContext& context) const
    {
        return std::formatter<uint32_t, CharT>::format(uint32_t(temp), context);
    }
};

struct XUSER_SIGNIN_INFO {
    ULONGLONG xuid;
    DWORD flags;
    XUSER_SIGNIN_STATE user_signin_state;
    DWORD guest_number;
    DWORD sponsor_user_index;
    CHAR user_name[16];
};

struct XUSER_STATS_SPEC {
	DWORD view_id;
	DWORD num_column_ids;
	WORD rgw_column_ids[64];
};

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

}
