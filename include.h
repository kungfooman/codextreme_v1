#include <Windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "cracking.h"
#include <sys/stat.h>


template <typename T, typename ... Ts> T call(size_t addr, Ts ... ts);
template <typename ... Ts> void Com_Printf(const char* fmt, Ts ... ts);
template <typename T, typename ... Ts>
T call(size_t addr, Ts ... ts) {
	T(*f)(...);
	*(T*)&f = (T)addr;
	return f(ts...);
}
template <typename ... Ts>
void Com_Printf(const char* fmt, Ts ... ts) {
	call<void*, const char*, Ts...>(0x00439CC0, fmt, ts...);
}
typedef void(*xcommand_t)(void);
void Cmd_AddCommand(const char* name, xcommand_t cmd) {
	call<void*, const char*, xcommand_t>(0x42C3B0, name, cmd);

}

void Cvar_Set(const char *var_name, const char *value) {
	call<void*, const char*, const char*>(0x43DC50, var_name, value);
}



void ScriptInitiating() {
	int game_mp = (int)GetModuleHandle("uo_game_mp_x86.dll");
}
void *Sys_LoadDll(const char *name, char *fqpath, int(**entryPoint) (int, ...), int(*systemcalls)(int, ...)) {
	int addr = 0x46B760;
	void *l = call<void*, const char*, char*, int(**)(int, ...)>(addr, name, fqpath, entryPoint, systemcalls);
	ScriptInitiating();
	return l;
}

typedef int(*Scr_GetInt_t)(int);
extern Scr_GetInt_t Scr_GetInt;
Scr_GetInt_t Scr_GetInt = (Scr_GetInt_t)0x48FC00;

typedef char* (*Scr_GetString_t)(int);
extern Scr_GetString_t Scr_GetString;
Scr_GetString_t Scr_GetString = (Scr_GetString_t)0x490040;

typedef int(*Scr_AddInt_t)(int);
extern Scr_AddInt_t Scr_AddInt;
Scr_AddInt_t Scr_AddInt = (Scr_AddInt_t)0x490650;

typedef int(*Scr_AddString_t)(char*);
extern Scr_AddString_t Scr_AddString;
Scr_AddString_t Scr_AddString = (Scr_AddString_t)0x4907F0;


int hook_status() {
	Com_Printf("WARNING: teeeest\n");
	return 1;
}

void version() {
	Com_Printf("Call of Duty XTREME v1.0 [ by fabio (Xfire: modsfabio) ]\n");
}


int hook_serverresponse()
{
	//Cvar_Set("sv_hostname", "asdf");
	Cvar_Set("sv_maxclients", "65");
	Com_Printf("doing it\n");
	return 1;
}