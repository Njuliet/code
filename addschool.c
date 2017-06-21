#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char courseId[20]="\0";
	char coursename[20]="\0";
	char credit[20]="\0";
	int status = 0;

	status = cgiFormString("courseId",  courseId, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get courseId error!\n");
		return 1;
	}

	status = cgiFormString("coursename",  coursename, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get coursename error!\n");
		return 1;
	}

	status = cgiFormString("credit",  credit, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get credit error!\n");
		return 1;
	}



	//fprintf(cgiOut, "stuname = %s, stuage = %s, stuId = %s,stutel=%s,stusex=%s,majorId=%s\n", stuname, stuage, stuId,stutel,stusex,majorId);
	//int ret=0;
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

  strcpy(sql, "create table course(courseId int not null primary key, coursename varchar(20) not null, credit varchar(20) not null");
  if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
  {
    if (ret != 1)
    {
      fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
      mysql_close(db);
      return -1;
    }
  }


	sprintf(sql, "insert into course values(%d,'%s','%s')",atoi(courseId),coursename,credit);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add course ok!\n");
	mysql_close(db);
	return 0;
}
