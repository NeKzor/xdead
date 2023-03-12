/*
 * Copyright (c) 2022-2023, NeKz
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <format>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

template <typename... Args> inline auto println(const std::string format, Args&&... args) -> void
{
    auto msg = std::vformat(format, std::make_format_args(args...));
    OutputDebugStringA((msg + "\n").c_str());
}
template <typename... Args> inline auto wprintln(const std::wstring format, Args&&... args) -> void
{
    auto msg = std::vformat(format, std::make_wformat_args(args...));
    OutputDebugStringW((msg + "\n").c_str());
}
