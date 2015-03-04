#include "mysql/mysql.h"

class mySQL {
	public:
		void gsc_mysql_close();
		MYSQL_RES* gsc_mysql_query(char*);
		MYSQL_ROW gsc_mysql_fetch_row(MYSQL_RES*);
		void gsc_mysql_num_rows(int);
		int gsc_mysql_real_escape_string(char*);
		mySQL(char*, char*, char*, char*, int);
		
	private:
		MYSQL* mysql;
};

