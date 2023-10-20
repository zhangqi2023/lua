cmake_minimum_required(VERSION 3.8)
project(lua)
set(LUA_CFILES 
        src/lapi.c
        src/lauxlib.c
        src/lbaselib.c
        src/lcode.c
        src/lcorolib.c
        src/lctype.c
        src/ldblib.c
        src/ldebug.c
        src/ldo.c
        src/ldump.c
        src/lfunc.c
        src/lgc.c
        src/linit.c
        src/liolib.c
        src/llex.c
        src/lmathlib.c
        src/lmem.c
        src/loadlib.c
        src/lobject.c
        src/lopcodes.c
        src/loslib.c
        src/lparser.c
        src/lstate.c
        src/lstring.c
        src/lstrlib.c
        src/ltable.c
        src/ltablib.c
        src/ltm.c
        src/lundump.c
        src/lutf8lib.c
        src/lvm.c
        src/lzio.c
        )

set(LUA_HEADERS 
        src/lapi.h
        src/lauxlib.h
        src/lcode.h
        src/lctype.h
        src/ldebug.h
        src/ldo.h
        src/lfunc.h
        src/lgc.h
        src/llex.h
        src/llimits.h
        src/lmem.h
        src/lobject.h
        src/lopcodes.h
        src/lparser.h
        src/lprefix.h
        src/lstate.h
        src/lstring.h
        src/ltable.h
        src/ltm.h
        src/lua.h
        src/lua.hpp
        src/luaconf.h
        src/lualib.h
        src/lundump.h
        src/lvm.h
        src/lzio.h)

set(CJSON_CFILES cjson/dtoa.c
        cjson/g_fmt.c
        cjson/lua_cjson.c
        cjson/strbuf.c
        )
set(CJSON_HEADERS cjson/dtoa_config.h
        cjson/fpconv.h
        cjson/strbuf.h
        )

set(LFS_CFILES lfs/lfs.c)
set(LFS_HEADERS lfs/lfs.h)

set(LUASOCKET_WIN_CFILES luasocket/auxiliar.c
        luasocket/buffer.c
        luasocket/compat.c
        luasocket/except.c
        luasocket/inet.c
        luasocket/io.c
        luasocket/luasocket.c
        luasocket/mime.c
        luasocket/options.c
        luasocket/select.c
        luasocket/tcp.c
        luasocket/timeout.c
        luasocket/udp.c
        luasocket/wsocket.c)

set(LUASOCKET_LINUX_CFILES luasocket/auxiliar.c
        luasocket/buffer.c
        luasocket/compat.c
        luasocket/except.c
        luasocket/inet.c
        luasocket/io.c
        luasocket/luasocket.c
        luasocket/mime.c
        luasocket/options.c
        luasocket/select.c
        luasocket/serial.c
        luasocket/tcp.c
        luasocket/timeout.c
        luasocket/udp.c
        luasocket/unix.c
        luasocket/unixdgram.c
        luasocket/unixstream.c
        luasocket/usocket.c)

set(LUASOCKET_WIN_HEADERS luasocket/auxiliar.h
        luasocket/buffer.h
        luasocket/compat.h
        luasocket/except.h
        luasocket/inet.h
        luasocket/io.h
        luasocket/luasocket.h
        luasocket/mime.h
        luasocket/options.h
        luasocket/pierror.h
        luasocket/select.h
        luasocket/socket.h
        luasocket/tcp.h
        luasocket/timeout.h
        luasocket/udp.h
        luasocket/wsocket.h)

set(LUASOCKET_LINUX_HEADERS luasocket/auxiliar.h
        luasocket/buffer.h
        luasocket/compat.h
        luasocket/except.h
        luasocket/inet.h
        luasocket/io.h
        luasocket/luasocket.h
        luasocket/mime.h
        luasocket/options.h
        luasocket/pierror.h
        luasocket/select.h
        luasocket/socket.h
        luasocket/tcp.h
        luasocket/timeout.h
        luasocket/udp.h
        luasocket/unix.h
        luasocket/unixdgram.h
        luasocket/unixstream.h
        luasocket/usocket.h)

set(PB_HEADERS lua_protobuf/pb.h)
set(PB_CFILES  lua_protobuf/pb.c)
set(SHARETABLE_CFILES  sharetable/lua-sharetable.c)

#lua编译成C++
set(COMPILE_AS_CPP ON)
IF(COMPILE_AS_CPP)
SET_SOURCE_FILES_PROPERTIES(${LUA_CFILES} ${LUA_HEADERS} ${CJSON_CFILES} ${CJSON_HEADERS} ${LFS_CFILES} ${LFS_HEADERS} ${PB_HEADERS} ${PB_CFILES} ${SHARETABLE_CFILES} PROPERTIES LANGUAGE CXX )
SET_SOURCE_FILES_PROPERTIES(${LUASOCKET_LINUX_HEADERS} ${LUASOCKET_LINUX_CFILES} PROPERTIES LANGUAGE CXX )
SET_SOURCE_FILES_PROPERTIES(${LUASOCKET_WIN_HEADERS} ${LUASOCKET_WIN_CFILES} PROPERTIES LANGUAGE CXX )
ENDIF()
add_library(lua)
target_link_libraries(lua PRIVATE library)
target_include_directories(lua PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/threads)
if(WIN32)
    target_sources(lua PRIVATE ${LUA_CFILES} ${CJSON_CFILES}  ${LUASOCKET_WIN_CFILES} ${LFS_CFILES} ${PB_CFILES} ${SHARETABLE_CFILES})
    #stdatomic==>c++23
    target_compile_definitions(lua PRIVATE __STDC_NO_ATOMICS__ _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS)
    target_link_libraries(lua ${WIN_COMMON_LIBS})
else()
    target_sources(lua PRIVATE ${LUA_CFILES} ${CJSON_CFILES} ${LUASOCKET_LINUX_CFILES} ${LFS_CFILES} ${PB_CFILES} ${SHARETABLE_CFILES})
    target_compile_definitions(lua PRIVATE LUA_USE_LINUX __STDC_NO_ATOMICS__)
    target_compile_options(lua PRIVATE "-Wl,-E")
    target_link_libraries(lua PRIVATE dl)
endif()

INSTALL( TARGETS lua
    EXPORT unofficial-lua-config
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(EXPORT unofficial-lua-config DESTINATION share/unofficial-lua)
INSTALL(
    FILES
        src/lualib.h
        src/lua.h
        src/luaconf.h
        src/lauxlib.h
    DESTINATION include
)