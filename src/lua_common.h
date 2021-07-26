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

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>

#include "utils.h"
#include "logging.h"

typedef struct LuaLoadedLibrary {
    char *name;
    char *path;
    void *libp;
    void *lib_open_sym;
} LuaLoadedLibrary;

typedef struct TXLuaContext {
    SPClass *class;

    struct TXLuaContext *master_thread;
    int thread_ref;

    lua_State *L;
    pthread_mutex_t *lock;
    LuaLoadedLibrary *loaded_lib_list;
    int loaded_lib_list_len;
} TXLuaContext;

#define LUA_PRIV_PREFIX "sp"
#define LUA_PUB_PREFIX "tx"
#define LUA_API_VERSION (int []){ 0, 1 } /* major, minor */

#ifndef LUA_BASELIBNAME
#define LUA_BASELIBNAME "base"
#endif

/* Create a Lua context and fill it with our API */
int sp_lua_create_ctx(TXLuaContext **s, void *ctx, const char *lua_libs_list);

/* Create a new Lua thread from a context */
TXLuaContext *sp_lua_create_thread(TXLuaContext *lctx);

/* Lock Lua interface and get a handle */
lua_State *sp_lua_lock_interface(TXLuaContext *lctx);

/* Unlock the Lua interface, ret is directly returned */
int sp_lua_unlock_interface(TXLuaContext *lctx, int ret);

/* Load file into the Lua context */
int sp_lua_load_file(TXLuaContext *lctx, const char *script_name);

/* Load a library into the given Lua context */
int sp_lua_load_library(TXLuaContext *lctx, const char *lib);

/* Closes a context or a thread */
void sp_lua_close_ctx(TXLuaContext **lctx);