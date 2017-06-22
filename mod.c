#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
FILE * fd;
	char stuname[20] = "\0";

	char stuId[20] = "\0";

	char stutel[20] = "\0";

	int status = 0;
char ch;

if(!(fd = fopen(headname, "r"))){
	fprintf(cgiOut, "Cannot open file, %s\n", headname);
	return -1;
}
ch = fgetc(fd);

while(ch != EOF){
	fprintf(cgiOut, "%c", ch);
	ch = fgetc(fd);
}
fclose(fd);

	status = cgiFormString("stuname",  stuname, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
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


	sprintf(sql, "update information set stuname='%s',stutel=%d where stuId = %d ", stuname,atoi(stutel), atoi(stuId));


	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1 ;
	}



	fprintf(cgiOut, "修改学生信息成功!\n");
	mysql_close(db);
	return 0;
}
