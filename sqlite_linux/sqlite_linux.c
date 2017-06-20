// C语言实现sqlite3数据库查询的基本方法
//2013-12-30 11:16 11421人阅读 评论(3) 收藏 举报
// 分类： linux（18）  
//版权声明：本文为博主原创文章，未经博主允许不得转载。
//
//sqlite回传函数相关 说了3种基本方法：callback，gettable和预处理stmt方法
//
//下面给出测试代码和测试用数据库，代码如下
//
//[cpp] view plain copy
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>  
#include "sqlite3.h"   
  
//  
//typedef int (*sqlite3_callback)(   
//    void* data,       /* Data provided in the 4th argument of sqlite3_exec() */   
//    int ncols,        /* The number of columns in row */   
//    char** values,    /* An array of strings representing fields in the row */   
//    char** headers    /* An array of strings representing column names */   
//);   
  
int callback(void* data, int ncols, char** values, char** headers)  
{  
    int i;  
    int len =0;  
    int ll=0;  
    for(i=0; i < ncols; i++)  
    {  
        if(strlen(headers[i])>len)  
            len = strlen(headers[i]);  
    }  
      
    for(i=0; i < ncols; i++)   
    {  
        ll = len-strlen(headers[i]);  
        while(ll)  
        {  
            fprintf(stdout," ");  
            --ll;  
        }  
        fprintf(stdout, "%s: %s\n", headers[i], values[i]);  
    }  
  
    fprintf(stdout, "\n");  
    return 0;  
}  
  
int search_by_callback(const char* db_name, const char* sql_cmd)   
{    
    int i = 0 ;    
    int j = 0 ;    
    int nrow = 0, ncolumn = 0;    
    char **azResult; //二维数组存放结果    
    sqlite3 *db=NULL;    
    char *zErrMsg = 0;   
    int rc;  
    int len=0;  
  
    if(access(db_name, 0) == -1)  
    {  
        fprintf(stderr, "%s not found\n", db_name);    
        return -1;    
    }  
      
    rc = sqlite3_open(db_name, &db);  
  
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s open failed: %s\n", db_name,sqlite3_errmsg(db));    
        sqlite3_close(db);    
        return -1;    
    }    
  
    //查询数据    
    rc = sqlite3_exec( db,sql_cmd, callback, NULL, &zErrMsg );  
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s %s: %s\n", db_name,sql_cmd, sqlite3_errmsg(db));    
        if(zErrMsg)  
        {  
            fprintf(stderr,"ErrMsg = %s \n", zErrMsg);   
            sqlite3_free(zErrMsg);  
        }  
        sqlite3_close(db);    
        return -1;    
    }  
      
    if(zErrMsg)  
    {  
        sqlite3_free(zErrMsg);  
    }  
  
    //关闭数据库    
    sqlite3_close(db);   
    return 0;    
  
}  
  
int search_by_table(const char* db_name, const char* sql_cmd)   
{    
    int i = 0 ;    
    int j = 0 ;    
    int nrow = 0, ncolumn = 0;    
    char **azResult; //二维数组存放结果    
    sqlite3 *db=NULL;    
    char *zErrMsg = 0;   
    int rc;  
    int len=0;  
  
    if(access(db_name, 0) == -1)  
    {  
        fprintf(stderr, "%s not found\n", db_name);    
        return -1;    
    }  
      
    rc = sqlite3_open(db_name, &db);  
  
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s open failed: %s\n", db_name,sqlite3_errmsg(db));    
        sqlite3_close(db);    
        return -1;    
    }    
  
    //查询数据    
    rc = sqlite3_get_table( db , sql_cmd, &azResult , &nrow , &ncolumn , &zErrMsg );    
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s %s: %s\n", db_name,sql_cmd, sqlite3_errmsg(db));    
        if(zErrMsg)  
            fprintf(stderr,"ErrMsg = %s \n", zErrMsg);   
        sqlite3_free_table( azResult );   
        sqlite3_close(db);    
        return -1;    
    }    
  
    for(j=0; j < ncolumn; j++)  
    {  
        if(strlen(azResult[j])>len)  
            len = strlen(azResult[j]);  
    }  
  
    //从第0索引到第 nColumn - 1索引都是字段名称  
    //从第 nColumn 索引开始，后面都是字段值  
    for( i = 0 ; i < nrow; i++ )  
    {  
        for(j=0; j < ncolumn; j++)  
        {  
            int ll = (len- strlen(azResult[j]));  
            while(ll)  
            {  
                printf(" ");  
                --ll;  
            }  
            printf( "%s: %s\n", azResult[j], azResult[(i+1)*ncolumn+j]);  
        }  
        printf("\n");  
    }  
  
#if 0     
    for( j = 0 ; j < ncolumn; j++ )  
    {  
        printf( "%s ", azResult[j]);  
    }  
    printf( "\n");    
  
    for( i=ncolumn ; i<( nrow + 1 ) * ncolumn ; i++ )  
    {  
        if(((i-ncolumn+1)%ncolumn) ==0)  
            printf( "%s\n",azResult[i]);  
        else  
            printf( "%s ",azResult[i] );   
    }  
#endif  
    //与sqlite3_get_table对应，释放掉  azResult 的内存空间    
    sqlite3_free_table( azResult );   
    //关闭数据库    
    sqlite3_close(db);   
    return 0;    
  
}   

int search_by_search(const char* db_name, const char* sql_cmd, const char *search_key)   
{    
    int i = 0 ;    
    int j = 0 ;    
    int nrow = 0, ncolumn = 0;    
    char **azResult; //二维数组存放结果    
    sqlite3 *db=NULL;    
    char *zErrMsg = 0;   
    int rc;  
    int len=0;  
  
    if(access(db_name, 0) == -1)  
    {  
        fprintf(stderr, "%s not found\n", db_name);    
        return -1;    
    }  
      
    rc = sqlite3_open(db_name, &db);  
  
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s open failed: %s\n", db_name,sqlite3_errmsg(db));    
        sqlite3_close(db);    
        return -1;    
    }    
  
    //查询数据    
    rc = sqlite3_get_table( db , sql_cmd, &azResult , &nrow , &ncolumn , &zErrMsg );    
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s %s: %s\n", db_name,sql_cmd, sqlite3_errmsg(db));    
        if(zErrMsg)  
            fprintf(stderr,"ErrMsg = %s \n", zErrMsg);   
        sqlite3_free_table( azResult );   
        sqlite3_close(db);    
        return -1;    
    }    
  
    for(j=0; j < ncolumn; j++)  
    {  
        if(strlen(azResult[j])>len)  
            len = strlen(azResult[j]);  
    }  
  
    //从第0索引到第 nColumn - 1索引都是字段名称  
    //从第 nColumn 索引开始，后面都是字段值  
    for( i = 0 ; i < nrow; i++ )  
    {  
        for(j=0; j < ncolumn; j++)  
        {  
            int ll = (len- strlen(azResult[j]));  
            while(ll)  
            {  
                // printf(" ");  
                --ll;  
            }  

			if(strstr(azResult[(i+1)*ncolumn+j], search_key))
			{
				printf( "=============================================================== \n");  
				printf( "find it %s: %s\n", azResult[j], azResult[(i+1)*ncolumn+j]);  
			}			
			// printf( "search_key %s \n", search_key);  
			// printf( "%s: %s\n", azResult[j], azResult[(i+1)*ncolumn+j]);  
			// break;
        }  
		// break;
        // printf("\n");  
    }  
	printf( "============================end=================================== \n");  
  
#if 0     
    for( j = 0 ; j < ncolumn; j++ )  
    {  
        printf( "%s ", azResult[j]);  
    }  
    printf( "\n");    
  
    for( i=ncolumn ; i<( nrow + 1 ) * ncolumn ; i++ )  
    {  
        if(((i-ncolumn+1)%ncolumn) ==0)  
            printf( "%s\n",azResult[i]);  
        else  
            printf( "%s ",azResult[i] );   
    }  
#endif  
    //与sqlite3_get_table对应，释放掉  azResult 的内存空间    
    sqlite3_free_table( azResult );   
    //关闭数据库    
    sqlite3_close(db);   
    return 0;    
  
}   
  
int search_by_stmt(const char* db_name, const char* sql_cmd)   
{    
    sqlite3 *db=NULL;    
    sqlite3_stmt* stmt = 0;  
    int ncolumn = 0;  
    const char *column_name;  
    int vtype , i;  
    int rc;  
  
    if(access(db_name, 0) == -1)  
    {  
        fprintf(stderr, "%s not found\n", db_name);    
        return -1;    
    }  
      
    rc = sqlite3_open(db_name, &db);  
  
    if( rc != SQLITE_OK)  
    {    
        fprintf(stderr, "%s open failed: %s\n", db_name,sqlite3_errmsg(db));    
        sqlite3_close(db);    
        return -1;    
    }    
  
    //查询数据    
    rc = sqlite3_prepare_v2(db, sql_cmd, -1, &stmt, 0);  
    if (rc != SQLITE_OK)  
    {  
        fprintf(stderr, "%s %s: %s\n", db_name,sql_cmd, sqlite3_errmsg(db));    
        sqlite3_close(db);    
        return -1;    
    }  
  
    ncolumn = sqlite3_column_count(stmt);  
  
    while (sqlite3_step(stmt) == SQLITE_ROW)  
    {     
        for(i = 0 ; i < ncolumn ; i++ )  
        {  
            vtype = sqlite3_column_type(stmt , i);  
            column_name = sqlite3_column_name(stmt , i);  
            switch( vtype )  
            {  
              case SQLITE_NULL:  
                  fprintf(stdout, "%s: null\n", column_name);     
                break;  
              case SQLITE_INTEGER:  
                  fprintf(stdout, "%s: %d\n", column_name,sqlite3_column_int(stmt,i));    
                break;  
              case SQLITE_FLOAT:  
                  fprintf(stdout, "%s: %f\n", column_name,sqlite3_column_double(stmt,i));     
                break;  
              case SQLITE_BLOB: /* arguably fall through... */  
                  fprintf(stdout, "%s: BLOB\n", column_name);     
                break;  
              case SQLITE_TEXT:   
                  fprintf(stdout, "%s: %s\n", column_name,sqlite3_column_text(stmt,i));   
                break;  
              default:  
                  fprintf(stdout, "%s: ERROR [%s]\n", column_name, sqlite3_errmsg(db));   
                break;  
            }  
        }  
    }  
  
    sqlite3_finalize(stmt);  
  
    //关闭数据库    
    sqlite3_close(db);   
    return 0;    
  
}  
  
  
  
int main(int argc, char* argv[])  
{  
    int i=0;  
    if(argc < 4)  
    {  
        fprintf(stderr, "usage: %s [table/callback/stmt] <db_name> <sql_table>\r\n", argv[0]);  
        fprintf(stderr, "usage: %s [search] <db_name> <sql_table> <search_key>\r\n", argv[0]);  
        return -1;  
    }  
  
    if((strcmp(argv[1],"table") ==0))  
        search_by_table(argv[2],argv[3]);  
    else if((strcmp(argv[1],"callback") ==0))  
        search_by_callback(argv[2],argv[3]);  
    else if((strcmp(argv[1],"search") ==0))  
        search_by_search(argv[2],argv[3],argv[4]);  
    else  
        search_by_stmt(argv[2],argv[3]);  
    return 0;  
}  

// sqlite> .tab
// android_table      hadoop_table       perl_table         rust_table       
// aspect_table       java_table         php_table          shell_table      
// c_table            javascript_table   postgresql_table   swift_table      
// cpp_table          looktexthis_table  python_table       unittest_table   
// erlang_table       object_c_table     qt_table         
// go_table           oracle_table       qtquick_table    
// sqlite> q

// ./aaa_sqlite_linux table all.db  "SELECT id,name FROM OVT_SONG where SONG_STAR ='鄭秀文'"
// ./aaa_sqlite_linux table all.db  "SELECT content FROM c_table where SONG_STAR ='鄭秀文'"
// ./aaa_sqlite_linux table all.db  "SELECT content FROM c_table"
// ./aaa_sqlite_linux search all.db  "SELECT keywords FROM c_table" "abc"

// sqlite> .schema c_table
// CREATE TABLE c_table([ID] INTEGER PRIMARY KEY,[content] varchar(100),[lantype] varchar(100),[keywords] varchar(100),[note] varchar(100),[vartype] varchar(100),[aspect_field] varchar(100),CreatedTime TimeStamp NOT NULL DEFAULT (datetime('now','localtime')), delflag integer DEFAULT 0, [lowercase_keyworks] varchar(100));
// sqlite> 



// 编译 gcc sqlite3_search.c   sqlite3.c -o sqlite3_search -lpthread -ldl

// 测试  
// ./sqlite3_search callback  KTV.sqlite  "SELECT id,name FROM OVT_SONG where SONG_STAR =鄭秀文'"
// ./sqlite3_search table  KTV.sqlite  "SELECT id,name FROM OVT_SONG where SONG_STAR =鄭秀文'"
// ./sqlite3_search stmt  KTV.sqlite  "SELECT id,name FROM OVT_SONG where SONG_STAR =鄭秀文'"

// 数据库文件下载地址 KTV.sqlite


// linux接口中查询数据库方法
// ./aaa_sqlite_linux search all.db  "SELECT content FROM c_table" "tcpdump"


