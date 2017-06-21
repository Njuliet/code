#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char stuname[20] = "\0";
	char  stuId[20] = "\0";
	char stutel[30]="\0";
	char  stuage[20]="\0";
	char stusex[20]="\0";
	int status = 0;



	status = cgiFormString("stuname",  stuname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuname error!\n");
		return 1;
	}

	status = cgiFormString("stuage",  stuage, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuage error!\n");
		return 1;
	}

	status = cgiFormString("stuId",  stuId, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}


	status = cgiFormString("stusex",  stusex, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stusex error!\n");
		return 1;
	}

	status = cgiFormString("stutel",  stutel, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stutel error!\n");
		return 1;
	}

	//fprintf(cgiOut, "stuname = %s, stuage = %s, stuId = %s,stutel=%s,stusex=%s,majorId=%s\n", stuname, stuage, stuId,stutel,stusex,majorId);
	int ret;
	char sql[1280] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456","stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	strcpy(sql, "create table information(stuId int not null primary key, stuname varchar(20) not null, stuage int not null,stutel varchar(30) not null,majorId int not null,stusex varchar(20) not null,status  int not null)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}


	sprintf(sql, "insert into information values(%d,'%s','%s',%d,'%s','1')",atoi(stuId),stuname,stutel,atoi(stuage),stusex);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
