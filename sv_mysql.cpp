#include "sv_mysql.h"


mySQL::mySQL(char *host, char *user, char *pass, char *db, int port) {
	mysql = mysql_init(NULL);
	mysql_real_connect(mysql, host, user, pass, db, port, NULL, 0);
}

void mySQL::gsc_mysql_close() {
	mysql_close(mysql);
	delete this;
}

MYSQL_RES* mySQL::gsc_mysql_query(char *sql)
{
	mysql_query(mysql, sql);
	MYSQL_RES *res = mysql_store_result(mysql);
	return res;
}

MYSQL_ROW mySQL::gsc_mysql_fetch_row(MYSQL_RES *result) {
	MYSQL_ROW row = mysql_fetch_row(result);
	return row;
}

int mySQL::gsc_mysql_real_escape_string(char *str) {
	char *to = (char *)malloc(strlen(str) * 2 + 1);
	return mysql_real_escape_string((MYSQL *)mysql, to, str, strlen(str));
}