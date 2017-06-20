#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char stuname[20] = "\0";
	char stuage[20] = "\0";
	char stuId[20] = "\0";
	char stutel[30] = "\0";
	char majorId[20] = "\0";
	char stusex[20] = "\0";
	int status = 0;

	status = cgiFormString("stuname",  stuname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}

	status = cgiFormString("stuage",  stuage, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}

	status = cgiFormString("stuId",  stuId, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}

	status = cgiFormString("stutel",  stutel, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stutel error!\n");
		return 1;
	}

	status = cgiFormString("majorId",  majorId, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get majorId error!\n");
		return 1;
	}

	status = cgiFormString("stusex",  stusex, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stusex error!\n");
		return 1;
	}
	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	sprintf(sql, "update information set stuname='%s', stuage= %d,stutel='%s',stusex='%s',majorId=%d where stuId = %d ", stuname, atoi(stuage),stutel,stusex,atoi(majorId), atoi(stuId));


	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1 ;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
