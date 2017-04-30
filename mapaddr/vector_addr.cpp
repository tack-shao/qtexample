//map address  test,原来new无法保证分配地址在堆上，有可能分配到栈，导致栈溢出异常。使用内存池分配吧。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <map>
#include <vector>
#include <string>
#include <iostream>


using namespace std;


#define check_paranullpt(PT) \
do{\
	if(!PT)\
	{\
		fprintf(stdout, "null pointer, %s[%d]-%s\n", __FUNCTION__, __LINE__, __FILE__);\
	}\
}while(0)

	
#define BUFFER_MAX (300 *1024)


typedef unsigned int WORD32;
typedef unsigned char BYTE;
typedef unsigned short DWORD;




typedef struct T_SNMP_TEST{
	WORD32 dwKey;
    BYTE ucBuf[BUFFER_MAX];    /*  */
	WORD32 dwValue;
	WORD32 *packet_sizes;
}T_SNMP_TEST, *P_SNMP_TEST;


typedef std::vector<T_SNMP_TEST> SNMP_PERF_VEC;
typedef std::vector<T_SNMP_TEST>::iterator SNMP_PERF_VEC_IT;



SNMP_PERF_VEC snmp_vecs;
T_SNMP_TEST g_snmptest = {0};
T_SNMP_TEST g_snmptmp = {0};



template<typename T1, typename T2>
T1* FetchItem(WORD32 dwKey, T2 &vec, T1 *pData)
{
	T1 *pInfo = NULL;
	SNMP_PERF_VEC_IT it;
	pData = pData;
	for(it = vec.begin(); it != vec.end(); it++)
	{
		if((*it).dwKey == dwKey)
		{
			return &(*it);
		}
	}
	printf("fetch item, no data, key:%#x\n", dwKey);
	return NULL;
}


template<typename T1, typename T2>
void UpdateItem(WORD32 dwKey, T2 &vec, T1 *pData)
{
	T1 *pInfo = NULL;
	SNMP_PERF_VEC_IT it;
	for(it = vec.begin(); it != vec.end(); it++)
	{
		if((*it).dwKey == dwKey)
		{
			pInfo = &(*it);
			check_paranullpt(pInfo);
			memset(pInfo, 0, sizeof(*pInfo));
			memcpy(pInfo, pData, sizeof(*pInfo));
			printf("updateitem, update data, key:%#x\n", dwKey);
			return;
		}
	}
	
	// pInfo = new T1();
	pInfo = &g_snmptest;
	check_paranullpt(pInfo);
	memset(pInfo, 0, sizeof(*pInfo));
	memcpy(pInfo, pData, sizeof(*pInfo));
	vec.push_back(*pInfo);
	printf("updateitem, create data, key:%#x, new addr:%p\n", dwKey, pInfo);

}


template<typename T1, typename T2>
void RemoveItem(WORD32 dwKey, T2 &vec)
{
	T1 *pInfo = NULL;
	SNMP_PERF_VEC_IT it;
	for(it = vec.begin(); it != vec.end(); it++)
	{
		if((*it).dwKey == dwKey)
		{
			pInfo = &(*it);
			check_paranullpt(pInfo);
			vec.erase(it);
			printf("removeitem, remove ok, key:%#x\n", dwKey);
			return;
		}
	}
	printf("removeitem, no data, key:%#x\n", dwKey);
}


// template<typename T2>
// void ClearItem(T2 &vec)
// {
	// SNMP_PERF_VEC_IT it;
	// WORD32 dwKey;
	// for(it = vec.begin(); it != vec.end(); it++)
	// {
		// dwKey  = it->first;
		// RemoveItem(dwKey, vec);
	// }
// }
template<typename T1>
void ClearItem(T1 &vec)
{
	SNMP_PERF_VEC_IT it;
	WORD32 dwKey;
	// for(it = vec.begin(); it != vec.end(); it++)
	// {
		// dwKey  = it->first;
		// delete (it->second);
	// }
	vec.clear();
}





void snmp_print_info()
{
	SNMP_PERF_VEC_IT it;
	P_SNMP_TEST pInfo = NULL;
	for(it = snmp_vecs.begin(); it != snmp_vecs.end(); it++)
	{
		pInfo = &(*it);
		printf("printf info, key:%#x, valueaddr:%p, ucBuf:%p, dwValue:%p, packet_sizes:%p\n", 
				pInfo->dwKey, pInfo, pInfo->ucBuf, &pInfo->dwValue, &pInfo->packet_sizes);
		//打印C++地址
		cout<<"static_cast<void *>(pInfo)="<<static_cast<void*>(pInfo)<<endl;		
		cout<<"static_cast<void *>(pInfo->ucBuf)="<<static_cast<void*>(pInfo->ucBuf)<<endl;		
		cout<<"static_cast<void *>(&pInfo->dwValue)="<<static_cast<void*>(&pInfo->dwValue)<<endl;		
		cout<<"static_cast<void *>(&pInfo->packet_sizes)="<<static_cast<void*>(&pInfo->packet_sizes)<<endl;		
	}
	
	
	
	printf("printf snmp_vecs addr:%p\n", snmp_vecs);
}

void snmp_test()
{
	P_SNMP_TEST pOrg = NULL;
	WORD32 dwLp  =  0;
	for( dwLp  =  0 ; dwLp < 4000; dwLp++ )
	{
		// pOrg = new T_SNMP_TEST();
		pOrg = &g_snmptmp;
		check_paranullpt(pOrg);
		printf("org char addr:%p\n", pOrg);
		memset(pOrg, 0 + dwLp, sizeof(*pOrg));
		
		UpdateItem(dwLp, snmp_vecs ,pOrg);
		// if(pOrg)
			// delete (pOrg);
	}


	
}

void test_addr()
{
	P_SNMP_TEST pInfo = NULL;
	pInfo = new T_SNMP_TEST();
	check_paranullpt(pInfo);
	printf("test new addr:%p\n", pInfo);
	if(pInfo)
		delete (pInfo);
}


int main(int argc, char **argv)
{
	snmp_test();
	
	snmp_print_info();

	// ClearItem(snmp_vecs);
	
	test_addr();
	
	while(1);
	return 0;
}






