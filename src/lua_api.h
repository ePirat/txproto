/*
 * This file is part of txproto.
 *
 * txproto is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * txproto is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with txproto; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#pragma once

#include "lua_common.h"
#include "txproto_main.h"

/* Parse a Lua table on top of stack into an AVDictionary */
int sp_lua_parse_table_to_avdict(lua_State *L, AVDictionary **dict);

/* Parse a Lua string on top of stack into an SPEventType bitmask */
int sp_lua_table_to_event_flags(void *ctx, lua_State *L, SPEventType *dst);

/* Load the main API onto a Lua context */
int sp_lua_load_main_api(TXLuaContext *lctx, TXMainContext *ctx);

/* If a script (top-level) returns this, quit gracefully withour raise() */
int sp_lua_quit(lua_State *L);
