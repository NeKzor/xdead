/*
 * Copyright (c) 2022-2023, NeKz
 *
 * SPDX-License-Identifier: MIT
 *
 *
 * This module aims to provide a minimal
 * layer for replacing xlive.dll (GFWL).
 */

#include "xdead.hpp"

/// <summary>
/// Add new listener to a function.
/// </summary>
/// <param name="ordinal">Ordinal of function to add the listener.</param>
/// <param name="callback">The callback function.</param>
/// <param name="index">The index which the callback should be sorted by.</param>
/// <returns>Status code.</returns>
__declspec(dllexport) auto __stdcall xdead_add_listener(uint32_t ordinal, void* callback, uint32_t index)
    -> xdead::ListenerStatus
{
    return xdead::add_listener(ordinal, callback, index);
}

/// <summary>
/// Remove an added listener from a function.
/// </summary>
/// <param name="ordinal">Ordinal of function to remove the listener.</param>
/// <param name="callback">The callback function.</param>
/// <returns>Status code.</returns>
__declspec(dllexport) auto __stdcall xdead_remove_listener(uint32_t ordinal, void* callback) -> xdead::ListenerStatus
{
    return xdead::remove_listener(ordinal, callback);
}

/// <summary>
/// Remove all added listeners from all functions.
/// </summary>
/// <returns>Status code.</returns>
__declspec(dllexport) auto __stdcall xdead_remove_all_listeners() -> xdead::ListenerStatus
{
    return xdead::remove_all_listeners();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) { return TRUE; }
