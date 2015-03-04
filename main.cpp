#include "include.h"
#include <string>
#include "sv_mysql.h"


mySQL mySqlCon("127.0.0.1", "", "", "db", 3306);

int closer()
{

	int a = Scr_GetInt(0);
	int b = Scr_GetInt(1);
	char* c = Scr_GetString(2);

	switch (a)
	{
		case 1: //getGuidNew
			Scr_AddInt(1);
			break;

		case 2: //login User
			Scr_AddInt(6666);
			break;

		case 3: //MySQL Query SELECT
		{
			MYSQL_RES *res = mySqlCon.gsc_mysql_query(c);
			MYSQL_ROW row = mySqlCon.gsc_mysql_fetch_row(res);
			Scr_AddString(row[0]);
			break;
		}
		case 4: //MySQL Query
		{
			if (!mySqlCon.gsc_mysql_query(c))
				Scr_AddInt(1);
			else
				Scr_AddInt(0);
			break;
		}

		default:
			Com_Printf("Unkown closer() command: %d\n", a);
	}

	return 1;
}

void connectMySql()
{
	MYSQL_RES *res = mySqlCon.gsc_mysql_query("SELECT map FROM likemap GROUP BY map");
	MYSQL_ROW row;
	while (row = mySqlCon.gsc_mysql_fetch_row(res)) {
		Com_Printf("Data: %s \n", row[0]);
	}
}

///////////////////////////////////////////////////////////////////
int hook_maxclients()
{
	Com_Printf("asd1");
	/*
	char vc[3];
	memcpy(&vc, (void*)0x4611AF, 3);
	memcmp(vc, "asd", 3);

	char vc1[3];
	memcpy(&vc1, (void*)0x998BA0, 3);
	memcmp(vc1, "asd", 3);
	*/
	char vc2[3];
	memcpy(&vc2, (void*)0x004611BC, 3);
	memcmp(vc2, "asd", 3);



	return 1;
}
///////////////////////////////////////////////////////////////////
void crackFunctions()
{
	//cracking_hook_function(0x00458400, (int)hook_status);
	Cmd_AddCommand("help", version);
	cracking_hook_function(0x00458400, (int)hook_serverresponse);
	cracking_hook_call(0x004611B7, (int)hook_maxclients);

	



}
void crackGSCFunctions()
{
	cracking_hook_call(0x4686FA, (int)Sys_LoadDll);
	if (GetModuleHandle("uo_game_mp_x86.dll") != NULL) {
		ScriptInitiating();
	}
	cracking_hook_function(0x2003AA50, (int)closer);	
	
}
DWORD g_threadID;
HMODULE g_hModule;
extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			g_hModule = hinstDLL;
			DisableThreadLibraryCalls(hinstDLL);
			Com_Printf("\n[CoD XTREME] Injected successfully. Visit www.modszombies.com\n");
			crackFunctions();
			crackGSCFunctions();
			//connectMySql();			
			break;

		case DLL_PROCESS_DETACH:
		case DLL_THREAD_DETACH:
			FreeLibraryAndExitThread(g_hModule, 0);
			break;
		}
	return TRUE;
}





