#include "mlog_init.h"

mlog_init::mlog_init()
{
}

//void setstdout2file(FILE *fp)
//{
//    int old;
//    FILE *fd;
//    old = dup( 1 );   // ȡ��׼������
//    if( old == -1 )
//    {
//        puts( "dup( 1 ) failure\n" );
//        return;
//    }
////    write( old, "This goes to stdout first\r\n", 27 );
//    if( ( fd = fopen( "data", "w" ) ) == NULL )
//    {
//        puts( "Can't open file 'data'\n" );
//        dup2( old, 1 ); // �ָ�
//        return;
//    }
//    if( -1 == dup2( fileno( fd ), 1 ) )//���ļ�������������1,1�Ͳ�����stdout��
//    {
//        puts( "Can't dup2 stdout\n" );
//        dup2( old, 1 ); // �ָ�
//        fclose( fd );
//        return;
//    }
//    fflush( stdout );
//    fclose( fd );
//    dup2( old, 1 ); // �ָ�

//}

