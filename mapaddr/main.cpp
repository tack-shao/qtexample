// //map address  test,原来new无法保证分配地址在堆上，有可能分配到栈，导致栈溢出异常。使用内存池分配吧。
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <map>
// #include <vector>
// #include <string>
// #include <iostream>


// using namespace std;


// #define check_paranullpt(PT) \
// do{\
	// if(!PT)\
	// {\
		// fprintf(stdout, "null pointer, %s[%d]-%s\n", __FUNCTION__, __LINE__, __FILE__);\
	// }\
// }while(0)

	
// #define BUFFER_MAX (300 *1024)


// typedef unsigned int WORD32;
// typedef unsigned char BYTE;
// typedef unsigned short DWORD;




// typedef struct T_SNMP_TEST{
    // BYTE ucBuf[BUFFER_MAX];    /*  */
	// WORD32 dwValue;
	// WORD32 *packet_sizes;
// }T_SNMP_TEST, *P_SNMP_TEST;


// typedef std::map<WORD32, P_SNMP_TEST> SNMP_PERF_MAP;
// typedef std::map<WORD32, P_SNMP_TEST>::iterator SNMP_PERF_MAP_IT;



// SNMP_PERF_MAP snmp_maps;



// template<typename T1, typename T2>
// T1* FetchItem(WORD32 dwAddr, T2 &map, T1 *pData)
// {
	// T1 *pInfo = NULL;
	// SNMP_PERF_MAP_IT it;
	// pData = pData;
	// it = map.find(dwAddr);
	// if(it == map.end())
	// {
		// printf("fetch item, no data, key:%#x\n", dwAddr);
		// return NULL;
	// }
	// return it->second;
// }


// template<typename T1, typename T2>
// void UpdateItem(WORD32 dwAddr, T2 &map, T1 *pData)
// {
	// T1 *pInfo = NULL;
	// SNMP_PERF_MAP_IT it;
	// it = map.find(dwAddr);
	// if(it == map.end())
	// {
		// pInfo = new T1();
		// check_paranullpt(pInfo);
		// memset(pInfo, 0, sizeof(*pInfo));
		// memcpy(pInfo, pData, sizeof(*pInfo));
		// map.insert(make_pair(dwAddr, pInfo));
		// printf("updateitem, create data, key:%#x, new addr:%p\n", dwAddr, pInfo);
	// }
	// else
	// {
		// pInfo = it->second;
		// check_paranullpt(pInfo);
		// memset(pInfo, 0, sizeof(*pInfo));
		// memcpy(pInfo, pData, sizeof(*pInfo));
		// printf("updateitem, update data, key:%#x\n", dwAddr);
	// }
// }


// template<typename T1, typename T2>
// void RemoveItem(WORD32 dwAddr, T2 &map)
// {
	// T1 *pInfo = NULL;
	// SNMP_PERF_MAP_IT it;
	// it = map.find(dwAddr);
	// if(it != map.end())
	// {
		// pInfo = it->second;
		// check_paranullpt(pInfo);
		// delete (pInfo);
		// map.erase(dwAddr);
		// printf("removeitem, remove ok, key:%#x\n", dwAddr);
		// return;
	// }
	// printf("removeitem, no data, key:%#x\n", dwAddr);
// }


// // template<typename T2>
// // void ClearItem(T2 &map)
// // {
	// // SNMP_PERF_MAP_IT it;
	// // WORD32 dwAddr;
	// // for(it = map.begin(); it != map.end(); it++)
	// // {
		// // dwAddr  = it->first;
		// // RemoveItem(dwAddr, map);
	// // }
// // }
// template<typename T1>
// void ClearItem(T1 &map)
// {
	// SNMP_PERF_MAP_IT it;
	// WORD32 dwAddr;
	// for(it = map.begin(); it != map.end(); it++)
	// {
		// dwAddr  = it->first;
		// free(it->second);
	// }
	// map.clear();
// }





// void snmp_print_info()
// {
	// SNMP_PERF_MAP_IT it;
	// P_SNMP_TEST pInfo = NULL;
	// for(it = snmp_maps.begin(); it != snmp_maps.end(); it++)
	// {
		// pInfo = it->second;
		// printf("printf info, key:%#x, valueaddr:%p, ucBuf:%p, dwValue:%p, packet_sizes:%p\n", 
				// it->first, it->second, pInfo->ucBuf, &pInfo->dwValue, &pInfo->packet_sizes);
		// //打印C++地址
		// cout<<"static_cast<void *>(pInfo)="<<static_cast<void*>(pInfo)<<endl;		
		// cout<<"static_cast<void *>(pInfo->ucBuf)="<<static_cast<void*>(pInfo->ucBuf)<<endl;		
		// cout<<"static_cast<void *>(&pInfo->dwValue)="<<static_cast<void*>(&pInfo->dwValue)<<endl;		
		// cout<<"static_cast<void *>(&pInfo->packet_sizes)="<<static_cast<void*>(&pInfo->packet_sizes)<<endl;		
	// }
	
	
	
	// printf("printf snmp_maps addr:%p\n", snmp_maps);
// }

// void snmp_test()
// {
	// P_SNMP_TEST pOrg = NULL;
	// WORD32 dwLp  =  0;
	// for( dwLp  =  0 ; dwLp < 1000; dwLp++ )
	// {
		// pOrg = new T_SNMP_TEST();
		// check_paranullpt(pOrg);
		// printf("org char addr:%p\n", pOrg);
		// memset(pOrg, 0 + dwLp, sizeof(*pOrg));
		
		// UpdateItem(dwLp, snmp_maps ,pOrg);
		// if(pOrg)
			// free(pOrg);
	// }


	
// }

// void test_addr()
// {
	// P_SNMP_TEST pInfo = NULL;
	// pInfo = new T_SNMP_TEST();
	// check_paranullpt(pInfo);
	// printf("test new addr:%p\n", pInfo);
	// if(pInfo)
		// free(pInfo);
// }


// // int main(int argc, char **argv)
// // {
	// // snmp_test();
	
	// // snmp_print_info();

	// // // ClearItem(snmp_maps);
	
	// // test_addr();
	
	// // while(1);
	// // return 0;
// // }






