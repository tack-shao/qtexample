#include <iostream>
#include "hashtable.h"
#include <assert.h>

using namespace std;

//#pragma pack(1)
//#pragma pack()
#pragma pack(12)
//#pragma pack(16)
typedef struct T_HashInfo{
    char bigdata3[300*1024];
    int dwaddr   ;    /*  */
    int seq      ;    /*  */
    char buf[187];    /*  */
    float tax     ;    /*  */
    char bigdata[300*1024];
    char test;
    unsigned int samplenum;
    unsigned int sampleport[123];
    char bigdata2[400*1024];
}T_HashInfo, *P_HashInfo;

#pragma pack()


CCustomHashTable<T_HashInfo> hash_test(10);
void print_hashinfo();
void print_T_HashInfo(T_HashInfo *pInfo);

template<typename T>
T* GetHashItem(CCustomHashTable<T> &hash, int dwaddr)
{
    char sKey[32] = {0};
    snprintf(sKey, sizeof(sKey), "%u", dwaddr);
    T *ptmp = hash.get(sKey);
    if(ptmp)
    {
        return ptmp;
    }
    else
    {
//        printf("put hash value error!!!\n");
    }
    return NULL;
}

template<typename T>
void UpdateHashItem(CCustomHashTable<T> &hash, T * val)
{
    char sKey[32] = {0};
    snprintf(sKey, sizeof(sKey), "%u", val->dwaddr);
    T *ptmp = hash.put(sKey);
    if(ptmp)
    {
        *ptmp = *val;
    }
    else
    {
        printf("put hash value error!!!\n");
    }

}

template<typename T>
void RemoveHashItem(CCustomHashTable<T> &hash, T * val)
{
    char sKey[32] = {0};
    snprintf(sKey, sizeof(sKey), "%d", val->dwaddr);
    int ret = hash.remove(sKey);
    if(-1 != ret)
    {
        printf("remove ok, hash remove item!!!\n");
    }
    else
    {
        printf("no data, hash remove item!!!,key:%#x\n", val->dwaddr);
    }

}



void hash_test1(void)
{
    printf("hash_test1 , beging hash size:%u\n", hash_test.count());
    int i  =  0;
    int LoopNum = 200;
    T_HashInfo tInfo = {0};
    P_HashInfo pInfo = NULL;
    for( i  =  0 ; i < LoopNum; i++ )
    {
        memset(&tInfo, 0, sizeof(tInfo));
        tInfo.dwaddr = 0x101 + i;
        tInfo.seq = 1 + i;
        tInfo.tax = 0.0 + i;
        sprintf(tInfo.buf, "0x%d", i);
        UpdateHashItem(hash_test, &tInfo);
    }
    print_hashinfo();
    printf("after update, hash size:%u\n", hash_test.count());

    LoopNum = 50;
    for( i  =  0 ; i < LoopNum; i++ )
    {
        memset(&tInfo, 0, sizeof(tInfo));
        tInfo.dwaddr = 0x101 + i;
        tInfo.seq = 1 + i;
        tInfo.tax = 0.0 + i;
        sprintf(tInfo.buf, "%d", i);
        RemoveHashItem(hash_test, &tInfo);
    }
    print_hashinfo();
    printf("after delete, hash size:%u\n", hash_test.count());


    printf("get data testing......., hash size:%u\n", hash_test.count());
    LoopNum = 50;
    for( i  =  0 ; i < LoopNum; i++ )
    {
        memset(&tInfo, 0, sizeof(tInfo));
        tInfo.dwaddr = 0x101 + i;
        tInfo.seq = 1 + i;
        tInfo.tax = 0.0 + i;
        sprintf(tInfo.buf, "%d", i);
        pInfo = GetHashItem(hash_test, tInfo.dwaddr);
        if(pInfo)
        {
//            *pInfo = tInfo;
            printf("got data, key:%#x\n", pInfo->dwaddr);
        }
        else
        {
            printf("no data, key:%#x\n", tInfo.dwaddr);
        }
//        UpdateHashItem(hash_test, &tInfo);
    }

    print_hashinfo();
    printf("after get method again, hash size:%u\n", hash_test.count());



//    set_integer(&hash_test, "1", 1);
//    set_integer(&hash_test, "2", 2);
//    set_integer(&hash_test, "2", 2);


//    printf("after delete, hash size:%u\n", hash_test.count());

//    CHashTableIterator<CCustomHashTable<int>> it;

}


void print_hashinfo()
{
    CHashTableIterator<T_HashInfo> tobj(hash_test);
    T_HashInfo *pIt = NULL;
    T_HashInfo *pInfo = NULL;
    printf("hash key!!\n");
    int dNo = 1;
    printf("No pInfo  dwaddr seq  tax  buf (iter)\n");
    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
    {
        pInfo = pIt;
        if(!pInfo)
        {
            assert(0);
            printf("got no data (iter)\n");
            continue;
        }
        printf("%-03u 0x%-08x 0x%-04x %-03u %-06.2f %-3s\n",
               dNo, pInfo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
    }
    dNo = 1;
    printf("\nNo pInfo  dwaddr seq  tax  buf (by GetHashItem)\n");
    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
    {
        pInfo = GetHashItem(hash_test, pIt->dwaddr);
        if(!pInfo)
        {
            assert(0);
            printf("got no data (by GetHashItem)\n");
            continue;
        }
        printf("%-03u 0x%-08x 0x%-04x %-03u %-06.2f %-3s\n",
               dNo, pInfo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
    }

    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
    {
        pInfo = GetHashItem(hash_test, pIt->dwaddr);
        if(!pInfo)
        {
            assert(0);
            printf("got no data (by GetHashItem)\n");
            continue;
        }
        print_T_HashInfo(pInfo);
    }



    printf("hash show\n");
    hash_test.show();
    printf("hash size:%u\n", hash_test.count());
}


void clear_hashinfo()
{
//    CHashTableIterator<T_HashInfo> tobj(hash_test);
//    T_HashInfo *pIt = NULL;
//    T_HashInfo *pInfo = NULL;
//    printf("hash key!!\n");
//    int dNo = 1;
//    printf("No  dwaddr seq  tax  buf (iter)\n");
//    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
//    {
//        pInfo = pIt;
//        if(!pInfo)
//        {
//            printf("got no data (iter)\n");
//            continue;
//        }
//        printf("%-03u 0x%-04x %-03u %-06.2f %-3s\n",
//               dNo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
//    }
//    dNo = 1;
//    printf("\nNo  dwaddr seq  tax  buf (by GetHashItem)\n");
//    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
//    {
//        pInfo = GetHashItem(hash_test, pIt->dwaddr);
//        if(!pInfo)
//        {
//            printf("got no data (by GetHashItem)\n");
//            continue;
//        }
//        printf("%-03u 0x%-04x %-03u %-06.2f %-3s\n",
//               dNo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
//    }
    printf("hash clear\n");
    hash_test.clear();
    printf("hash show\n");
    hash_test.show();
    printf("hash size:%u\n", hash_test.count());
}

void print_hash_userdatasize()
{
    printf("sizeof(T_HashInfo)     :%u\n", sizeof(T_HashInfo));
    printf("sizeof(T_HashInfo) %% 4 :%u\n", sizeof(T_HashInfo) % 4);
}

void print_T_HashInfo(T_HashInfo *pInfo)
{
    if(!pInfo)
        return;
    printf("Struct T_HashInfo info following ===== [pInfo->]\n");
    printf("bigdata3[3001024] :    %p   \n", pInfo->bigdata3);
    printf("dwaddr            :    %p   \n", &pInfo->dwaddr           );
    printf("seq               :    %p   \n", &pInfo->seq              );
    printf("buf[187]          :    %p   \n", pInfo->buf         );
    printf("tax               :    %p   \n", &pInfo->tax              );
    printf("bigdata[3001024]  :    %p   \n", pInfo->bigdata );
    printf("test              :    %p   \n", &pInfo->test             );
    printf("samplenum         :    %p   \n", &pInfo->samplenum        );
    printf("sampleport[123]   :    %p   \n", pInfo->sampleport  );
    printf("bigdata2[4001024] :    %p   \n", pInfo->bigdata2);

    printf("Struct T_HashInfo info following ===== [pInfo->]\n");
    printf("bigdata3[300*1024] :    %p   \n", pInfo->bigdata3  );
    printf("dwaddr             :    %p   \n", pInfo->dwaddr    );
    printf("seq                :    %p   \n", pInfo->seq       );
    printf("buf[187]           :    %p   \n", pInfo->buf       );
    printf("tax                :    %p   \n", pInfo->tax       );
    printf("bigdata[300*1024]  :    %p   \n", pInfo->bigdata   );
    printf("test               :    %p   \n", pInfo->test      );
    printf("samplenum          :    %p   \n", pInfo->samplenum );
    printf("sampleport[123]    :    %p   \n", pInfo->sampleport);
    printf("bigdata2[400*1024] :    %p   \n", pInfo->bigdata2  );


}

int main()
{
    hash_test1();;
    print_hashinfo();
    print_hash_userdatasize();
    clear_hashinfo();
    cout << "Hello World!" << endl;
    return 0;
}



/*
>>> 0x245e1b0 - 0x2447534
93308
>>> 0x245e1b0 - 0x2447534 - 93296
12
>>> 0x1738ca8 - 0x172202c
93308
>>>

*/





/*
>>> 0x16f4cac - 0x16de02c - 93300
12
>>>

*/



/*


*/









/*

D:\Qtexample\git\qtexample\hash_table-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK____\debug\hash_table.exe Æô¶¯ÖÐ...
hash_test1 , beging hash size:0
hash key!!
No pInfo  dwaddr seq  tax  buf (iter)
1   0xf79402c  0x110  16  15.00  0x15
2   0xf88e2f4  0x108  8   7.00   0x7
3   0xf9885bc  0x103  3   2.00   0x2
4   0xfa82884  0x10a  10  9.00   0x9
5   0xfb7cb4c  0x101  1   0.00   0x0
6   0xfc76e14  0x10b  11  10.00  0x10
7   0xfd710dc  0x107  7   6.00   0x6
8   0xfe6b3a4  0x106  6   5.00   0x5
9   0xff6566c  0x109  9   8.00   0x8
10  0x1005f934 0x10d  13  12.00  0x12
11  0x10159bfc 0x102  2   1.00   0x1
12  0x10253ec4 0x105  5   4.00   0x4
13  0x1034e18c 0x10c  12  11.00  0x11
14  0x10448454 0x10e  14  13.00  0x13
15  0x1054271c 0x104  4   3.00   0x3
16  0x1063c9e4 0x10f  15  14.00  0x14
17  0x10736cac 0x112  18  17.00  0x17
18  0x10830f74 0x113  19  18.00  0x18
19  0x1092b23c 0x114  20  19.00  0x19
20  0x10a25504 0x116  22  21.00  0x21
21  0x10b1f7cc 0x118  24  23.00  0x23
22  0x10c19a94 0x119  25  24.00  0x24
23  0x10d13d5c 0x11a  26  25.00  0x25
24  0x10e0e024 0x11c  28  27.00  0x27
25  0x10f082ec 0x11d  29  28.00  0x28
26  0x110025b4 0x11e  30  29.00  0x29
27  0x110fc87c 0x117  23  22.00  0x22
28  0x111f6b44 0x11f  31  30.00  0x30
29  0x112f0e0c 0x115  21  20.00  0x20
30  0x113eb0d4 0x11b  27  26.00  0x26
31  0x114e539c 0x120  32  31.00  0x31
32  0x115df664 0x111  17  16.00  0x16
33  0x116d992c 0x122  34  33.00  0x33
34  0x117d3bf4 0x123  35  34.00  0x34
35  0x118cdebc 0x128  40  39.00  0x39
36  0x119c8184 0x12a  42  41.00  0x41
37  0x11ac244c 0x12b  43  42.00  0x42
38  0x11bbc714 0x12e  46  45.00  0x45
39  0x11cb69dc 0x12f  47  46.00  0x46
40  0x11db0ca4 0x130  48  47.00  0x47
41  0x11eaaf6c 0x131  49  48.00  0x48
42  0x11fa5234 0x132  50  49.00  0x49
43  0x1209f4fc 0x133  51  50.00  0x50
44  0x121997c4 0x12d  45  44.00  0x44
45  0x12293a8c 0x134  52  51.00  0x51
46  0x1238dd54 0x125  37  36.00  0x36
47  0x1248801c 0x129  41  40.00  0x40
48  0x125822e4 0x136  54  53.00  0x53
49  0x1267c5ac 0x138  56  55.00  0x55
50  0x12776874 0x139  57  56.00  0x56
51  0x12870b3c 0x13a  58  57.00  0x57
52  0x1296ae04 0x127  39  38.00  0x38
53  0x12a650cc 0x135  53  52.00  0x52
54  0x12b5f394 0x137  55  54.00  0x54
55  0x12c5965c 0x13b  59  58.00  0x58
56  0x12d53924 0x13d  61  60.00  0x60
57  0x12e4dbec 0x13e  62  61.00  0x61
58  0x12f47eb4 0x121  33  32.00  0x32
59  0x1304217c 0x126  38  37.00  0x37
60  0x1313c444 0x13f  63  62.00  0x62
61  0x1323670c 0x124  36  35.00  0x35
62  0x133309d4 0x140  64  63.00  0x63
63  0x1342ac9c 0x12c  44  43.00  0x43
64  0x13524f64 0x13c  60  59.00  0x59
65  0x1361f22c 0x141  65  64.00  0x64
66  0x137194f4 0x142  66  65.00  0x65
67  0x138137bc 0x143  67  66.00  0x66
68  0x1390da84 0x144  68  67.00  0x67
69  0x13a07d4c 0x147  71  70.00  0x70
70  0x13b02014 0x148  72  71.00  0x71
71  0x13bfc2dc 0x14a  74  73.00  0x73
72  0x13cf65a4 0x14b  75  74.00  0x74
73  0x13df086c 0x14c  76  75.00  0x75
74  0x13eeab34 0x14e  78  77.00  0x77
75  0x13fe4dfc 0x151  81  80.00  0x80
76  0x140df0c4 0x152  82  81.00  0x81
77  0x141d938c 0x153  83  82.00  0x82
78  0x142d3654 0x154  84  83.00  0x83
79  0x143cd91c 0x155  85  84.00  0x84
80  0x144c7be4 0x156  86  85.00  0x85
81  0x145c1eac 0x158  88  87.00  0x87
82  0x146bc174 0x159  89  88.00  0x88
83  0x147b643c 0x15b  91  90.00  0x90
84  0x148b0704 0x15c  92  91.00  0x91
85  0x149aa9cc 0x15e  94  93.00  0x93
86  0x14aa4c94 0x15f  95  94.00  0x94
87  0x14b9ef5c 0x150  80  79.00  0x79
88  0x14c99224 0x160  96  95.00  0x95
89  0x14d934ec 0x157  87  86.00  0x86
90  0x14e8d7b4 0x161  97  96.00  0x96
91  0x14f87a7c 0x162  98  97.00  0x97
92  0x15081d44 0x163  99  98.00  0x98
93  0x1517c00c 0x145  69  68.00  0x68
94  0x152762d4 0x165  101 100.00 0x100
95  0x1537059c 0x166  102 101.00 0x101
96  0x1546a864 0x16a  106 105.00 0x105
97  0x15564b2c 0x16b  107 106.00 0x106
98  0x1565edf4 0x14d  77  76.00  0x76
99  0x157590bc 0x16c  108 107.00 0x107
100 0x15853384 0x16d  109 108.00 0x108
101 0x1594d64c 0x16e  110 109.00 0x109
102 0x15a47914 0x16f  111 110.00 0x110
103 0x15b41bdc 0x171  113 112.00 0x112
104 0x15c3bea4 0x149  73  72.00  0x72
105 0x15d3616c 0x169  105 104.00 0x104
106 0x15e30434 0x170  112 111.00 0x111
107 0x15f2a6fc 0x167  103 102.00 0x102
108 0x160249c4 0x172  114 113.00 0x113
109 0x1611ec8c 0x173  115 114.00 0x114
110 0x16218f54 0x174  116 115.00 0x115
111 0x1631321c 0x175  117 116.00 0x116
112 0x1640d4e4 0x15a  90  89.00  0x89
113 0x165077ac 0x176  118 117.00 0x117
114 0x16601a74 0x178  120 119.00 0x119
115 0x166fbd3c 0x168  104 103.00 0x103
116 0x167f6004 0x179  121 120.00 0x120
117 0x168f02cc 0x17a  122 121.00 0x121
118 0x169ea594 0x146  70  69.00  0x69
119 0x16ae485c 0x17b  123 122.00 0x122
120 0x16bdeb24 0x17c  124 123.00 0x123
121 0x16cd8dec 0x164  100 99.00  0x99
122 0x16dd30b4 0x17d  125 124.00 0x124
123 0x16ecd37c 0x17e  126 125.00 0x125
124 0x16fc7644 0x17f  127 126.00 0x126
125 0x170c190c 0x180  128 127.00 0x127
126 0x171bbbd4 0x15d  93  92.00  0x92
127 0x172b5e9c 0x177  119 118.00 0x118
128 0x173b0164 0x14f  79  78.00  0x78
129 0x174aa42c 0x182  130 129.00 0x129
130 0x175a46f4 0x18a  138 137.00 0x137
131 0x1769e9bc 0x18b  139 138.00 0x138
132 0x17798c84 0x18d  141 140.00 0x140
133 0x17892f4c 0x18e  142 141.00 0x141
134 0x1798d214 0x18f  143 142.00 0x142
135 0x17a874dc 0x194  148 147.00 0x147
136 0x17b817a4 0x195  149 148.00 0x148
137 0x17c7ba6c 0x196  150 149.00 0x149
138 0x17d75d34 0x197  151 150.00 0x150
139 0x17e6fffc 0x198  152 151.00 0x151
140 0x17f6a2c4 0x199  153 152.00 0x152
141 0x1806458c 0x19c  156 155.00 0x155
142 0x1815e854 0x19e  158 157.00 0x157
143 0x18258b1c 0x19f  159 158.00 0x158
144 0x18352de4 0x1a1  161 160.00 0x160
145 0x1844d0ac 0x1a2  162 161.00 0x161
146 0x18547374 0x1a3  163 162.00 0x162
147 0x1864163c 0x1a4  164 163.00 0x163
148 0x1873b904 0x1a5  165 164.00 0x164
149 0x18835bcc 0x1a6  166 165.00 0x165
150 0x1892fe94 0x185  133 132.00 0x132
151 0x18a2a15c 0x18c  140 139.00 0x139
152 0x18b24424 0x1a7  167 166.00 0x166
153 0x18c1e6ec 0x1aa  170 169.00 0x169
154 0x18d189b4 0x1b0  176 175.00 0x175
155 0x18e12c7c 0x1b2  178 177.00 0x177
156 0x18f0cf44 0x1ac  172 171.00 0x171
157 0x1900720c 0x1b3  179 178.00 0x178
158 0x191014d4 0x1b5  181 180.00 0x180
159 0x191fb79c 0x1b6  182 181.00 0x181
160 0x192f5a64 0x1b7  183 182.00 0x182
161 0x193efd2c 0x19b  155 154.00 0x154
162 0x194e9ff4 0x189  137 136.00 0x136
163 0x195e42bc 0x1bb  187 186.00 0x186
164 0x196de584 0x1bc  188 187.00 0x187
165 0x197d884c 0x1bd  189 188.00 0x188
166 0x198d2b14 0x1ab  171 170.00 0x170
167 0x199ccddc 0x1be  190 189.00 0x189
168 0x19ac70a4 0x1bf  191 190.00 0x190
169 0x19bc136c 0x1c0  192 191.00 0x191
170 0x19cbb634 0x1ae  174 173.00 0x173
171 0x19db58fc 0x1c1  193 192.00 0x192
172 0x19eafbc4 0x1c2  194 193.00 0x193
173 0x19fa9e8c 0x1c3  195 194.00 0x194
174 0x1a0a4154 0x1c4  196 195.00 0x195
175 0x1a19e41c 0x181  129 128.00 0x128
176 0x1a2986e4 0x1c5  197 196.00 0x196
177 0x1a3929ac 0x1c7  199 198.00 0x198
178 0x1a48cc74 0x1a8  168 167.00 0x167
179 0x1a586f3c 0x1c8  200 199.00 0x199
180 0x1a875794 0x19a  154 153.00 0x153
181 0x1a96fa5c 0x193  147 146.00 0x146
182 0x1af4cb0c 0x1af  175 174.00 0x174
183 0x1b42f8f4 0x1b1  177 176.00 0x176
184 0x1b623e84 0x1ad  173 172.00 0x172
185 0x1b818414 0x1ba  186 185.00 0x185
186 0x1bc00f34 0x186  134 133.00 0x133
187 0x1bdf54c4 0x191  145 144.00 0x144
188 0x1bfe9a54 0x184  132 131.00 0x131
189 0x1c2d82ac 0x1c6  198 197.00 0x197
190 0x1ce9240c 0x187  135 134.00 0x134
191 0x1cf8c6d4 0x19d  157 156.00 0x156
192 0x1d08699c 0x190  144 143.00 0x143
193 0x1d9522a4 0x192  146 145.00 0x145
194 0x1db46834 0x1b9  185 184.00 0x184
195 0x1dc40afc 0x1a0  160 159.00 0x159
196 0x1e21dbac 0x188  136 135.00 0x135
197 0x1e50c404 0x183  131 130.00 0x130
198 0x1e7fac5c 0x1b4  180 179.00 0x179
199 0x1e9ef1ec 0x1a9  169 168.00 0x168
200 0x1edd7d0c 0x1b8  184 183.00 0x183

No pInfo  dwaddr seq  tax  buf (by GetHashItem)
1   0xf79402c  0x110  16  15.00  0x15
2   0xf88e2f4  0x108  8   7.00   0x7
3   0xf9885bc  0x103  3   2.00   0x2
4   0xfa82884  0x10a  10  9.00   0x9
5   0xfb7cb4c  0x101  1   0.00   0x0
6   0xfc76e14  0x10b  11  10.00  0x10
7   0xfd710dc  0x107  7   6.00   0x6
8   0xfe6b3a4  0x106  6   5.00   0x5
9   0xff6566c  0x109  9   8.00   0x8
10  0x1005f934 0x10d  13  12.00  0x12
11  0x10159bfc 0x102  2   1.00   0x1
12  0x10253ec4 0x105  5   4.00   0x4
13  0x1034e18c 0x10c  12  11.00  0x11
14  0x10448454 0x10e  14  13.00  0x13
15  0x1054271c 0x104  4   3.00   0x3
16  0x1063c9e4 0x10f  15  14.00  0x14
17  0x10736cac 0x112  18  17.00  0x17
18  0x10830f74 0x113  19  18.00  0x18
19  0x1092b23c 0x114  20  19.00  0x19
20  0x10a25504 0x116  22  21.00  0x21
21  0x10b1f7cc 0x118  24  23.00  0x23
22  0x10c19a94 0x119  25  24.00  0x24
23  0x10d13d5c 0x11a  26  25.00  0x25
24  0x10e0e024 0x11c  28  27.00  0x27
25  0x10f082ec 0x11d  29  28.00  0x28
26  0x110025b4 0x11e  30  29.00  0x29
27  0x110fc87c 0x117  23  22.00  0x22
28  0x111f6b44 0x11f  31  30.00  0x30
29  0x112f0e0c 0x115  21  20.00  0x20
30  0x113eb0d4 0x11b  27  26.00  0x26
31  0x114e539c 0x120  32  31.00  0x31
32  0x115df664 0x111  17  16.00  0x16
33  0x116d992c 0x122  34  33.00  0x33
34  0x117d3bf4 0x123  35  34.00  0x34
35  0x118cdebc 0x128  40  39.00  0x39
36  0x119c8184 0x12a  42  41.00  0x41
37  0x11ac244c 0x12b  43  42.00  0x42
38  0x11bbc714 0x12e  46  45.00  0x45
39  0x11cb69dc 0x12f  47  46.00  0x46
40  0x11db0ca4 0x130  48  47.00  0x47
41  0x11eaaf6c 0x131  49  48.00  0x48
42  0x11fa5234 0x132  50  49.00  0x49
43  0x1209f4fc 0x133  51  50.00  0x50
44  0x121997c4 0x12d  45  44.00  0x44
45  0x12293a8c 0x134  52  51.00  0x51
46  0x1238dd54 0x125  37  36.00  0x36
47  0x1248801c 0x129  41  40.00  0x40
48  0x125822e4 0x136  54  53.00  0x53
49  0x1267c5ac 0x138  56  55.00  0x55
50  0x12776874 0x139  57  56.00  0x56
51  0x12870b3c 0x13a  58  57.00  0x57
52  0x1296ae04 0x127  39  38.00  0x38
53  0x12a650cc 0x135  53  52.00  0x52
54  0x12b5f394 0x137  55  54.00  0x54
55  0x12c5965c 0x13b  59  58.00  0x58
56  0x12d53924 0x13d  61  60.00  0x60
57  0x12e4dbec 0x13e  62  61.00  0x61
58  0x12f47eb4 0x121  33  32.00  0x32
59  0x1304217c 0x126  38  37.00  0x37
60  0x1313c444 0x13f  63  62.00  0x62
61  0x1323670c 0x124  36  35.00  0x35
62  0x133309d4 0x140  64  63.00  0x63
63  0x1342ac9c 0x12c  44  43.00  0x43
64  0x13524f64 0x13c  60  59.00  0x59
65  0x1361f22c 0x141  65  64.00  0x64
66  0x137194f4 0x142  66  65.00  0x65
67  0x138137bc 0x143  67  66.00  0x66
68  0x1390da84 0x144  68  67.00  0x67
69  0x13a07d4c 0x147  71  70.00  0x70
70  0x13b02014 0x148  72  71.00  0x71
71  0x13bfc2dc 0x14a  74  73.00  0x73
72  0x13cf65a4 0x14b  75  74.00  0x74
73  0x13df086c 0x14c  76  75.00  0x75
74  0x13eeab34 0x14e  78  77.00  0x77
75  0x13fe4dfc 0x151  81  80.00  0x80
76  0x140df0c4 0x152  82  81.00  0x81
77  0x141d938c 0x153  83  82.00  0x82
78  0x142d3654 0x154  84  83.00  0x83
79  0x143cd91c 0x155  85  84.00  0x84
80  0x144c7be4 0x156  86  85.00  0x85
81  0x145c1eac 0x158  88  87.00  0x87
82  0x146bc174 0x159  89  88.00  0x88
83  0x147b643c 0x15b  91  90.00  0x90
84  0x148b0704 0x15c  92  91.00  0x91
85  0x149aa9cc 0x15e  94  93.00  0x93
86  0x14aa4c94 0x15f  95  94.00  0x94
87  0x14b9ef5c 0x150  80  79.00  0x79
88  0x14c99224 0x160  96  95.00  0x95
89  0x14d934ec 0x157  87  86.00  0x86
90  0x14e8d7b4 0x161  97  96.00  0x96
91  0x14f87a7c 0x162  98  97.00  0x97
92  0x15081d44 0x163  99  98.00  0x98
93  0x1517c00c 0x145  69  68.00  0x68
94  0x152762d4 0x165  101 100.00 0x100
95  0x1537059c 0x166  102 101.00 0x101
96  0x1546a864 0x16a  106 105.00 0x105
97  0x15564b2c 0x16b  107 106.00 0x106
98  0x1565edf4 0x14d  77  76.00  0x76
99  0x157590bc 0x16c  108 107.00 0x107
100 0x15853384 0x16d  109 108.00 0x108
101 0x1594d64c 0x16e  110 109.00 0x109
102 0x15a47914 0x16f  111 110.00 0x110
103 0x15b41bdc 0x171  113 112.00 0x112
104 0x15c3bea4 0x149  73  72.00  0x72
105 0x15d3616c 0x169  105 104.00 0x104
106 0x15e30434 0x170  112 111.00 0x111
107 0x15f2a6fc 0x167  103 102.00 0x102
108 0x160249c4 0x172  114 113.00 0x113
109 0x1611ec8c 0x173  115 114.00 0x114
110 0x16218f54 0x174  116 115.00 0x115
111 0x1631321c 0x175  117 116.00 0x116
112 0x1640d4e4 0x15a  90  89.00  0x89
113 0x165077ac 0x176  118 117.00 0x117
114 0x16601a74 0x178  120 119.00 0x119
115 0x166fbd3c 0x168  104 103.00 0x103
116 0x167f6004 0x179  121 120.00 0x120
117 0x168f02cc 0x17a  122 121.00 0x121
118 0x169ea594 0x146  70  69.00  0x69
119 0x16ae485c 0x17b  123 122.00 0x122
120 0x16bdeb24 0x17c  124 123.00 0x123
121 0x16cd8dec 0x164  100 99.00  0x99
122 0x16dd30b4 0x17d  125 124.00 0x124
123 0x16ecd37c 0x17e  126 125.00 0x125
124 0x16fc7644 0x17f  127 126.00 0x126
125 0x170c190c 0x180  128 127.00 0x127
126 0x171bbbd4 0x15d  93  92.00  0x92
127 0x172b5e9c 0x177  119 118.00 0x118
128 0x173b0164 0x14f  79  78.00  0x78
129 0x174aa42c 0x182  130 129.00 0x129
130 0x175a46f4 0x18a  138 137.00 0x137
131 0x1769e9bc 0x18b  139 138.00 0x138
132 0x17798c84 0x18d  141 140.00 0x140
133 0x17892f4c 0x18e  142 141.00 0x141
134 0x1798d214 0x18f  143 142.00 0x142
135 0x17a874dc 0x194  148 147.00 0x147
136 0x17b817a4 0x195  149 148.00 0x148
137 0x17c7ba6c 0x196  150 149.00 0x149
138 0x17d75d34 0x197  151 150.00 0x150
139 0x17e6fffc 0x198  152 151.00 0x151
140 0x17f6a2c4 0x199  153 152.00 0x152
141 0x1806458c 0x19c  156 155.00 0x155
142 0x1815e854 0x19e  158 157.00 0x157
143 0x18258b1c 0x19f  159 158.00 0x158
144 0x18352de4 0x1a1  161 160.00 0x160
145 0x1844d0ac 0x1a2  162 161.00 0x161
146 0x18547374 0x1a3  163 162.00 0x162
147 0x1864163c 0x1a4  164 163.00 0x163
148 0x1873b904 0x1a5  165 164.00 0x164
149 0x18835bcc 0x1a6  166 165.00 0x165
150 0x1892fe94 0x185  133 132.00 0x132
151 0x18a2a15c 0x18c  140 139.00 0x139
152 0x18b24424 0x1a7  167 166.00 0x166
153 0x18c1e6ec 0x1aa  170 169.00 0x169
154 0x18d189b4 0x1b0  176 175.00 0x175
155 0x18e12c7c 0x1b2  178 177.00 0x177
156 0x18f0cf44 0x1ac  172 171.00 0x171
157 0x1900720c 0x1b3  179 178.00 0x178
158 0x191014d4 0x1b5  181 180.00 0x180
159 0x191fb79c 0x1b6  182 181.00 0x181
160 0x192f5a64 0x1b7  183 182.00 0x182
161 0x193efd2c 0x19b  155 154.00 0x154
162 0x194e9ff4 0x189  137 136.00 0x136
163 0x195e42bc 0x1bb  187 186.00 0x186
164 0x196de584 0x1bc  188 187.00 0x187
165 0x197d884c 0x1bd  189 188.00 0x188
166 0x198d2b14 0x1ab  171 170.00 0x170
167 0x199ccddc 0x1be  190 189.00 0x189
168 0x19ac70a4 0x1bf  191 190.00 0x190
169 0x19bc136c 0x1c0  192 191.00 0x191
170 0x19cbb634 0x1ae  174 173.00 0x173
171 0x19db58fc 0x1c1  193 192.00 0x192
172 0x19eafbc4 0x1c2  194 193.00 0x193
173 0x19fa9e8c 0x1c3  195 194.00 0x194
174 0x1a0a4154 0x1c4  196 195.00 0x195
175 0x1a19e41c 0x181  129 128.00 0x128
176 0x1a2986e4 0x1c5  197 196.00 0x196
177 0x1a3929ac 0x1c7  199 198.00 0x198
178 0x1a48cc74 0x1a8  168 167.00 0x167
179 0x1a586f3c 0x1c8  200 199.00 0x199
180 0x1a875794 0x19a  154 153.00 0x153
181 0x1a96fa5c 0x193  147 146.00 0x146
182 0x1af4cb0c 0x1af  175 174.00 0x174
183 0x1b42f8f4 0x1b1  177 176.00 0x176
184 0x1b623e84 0x1ad  173 172.00 0x172
185 0x1b818414 0x1ba  186 185.00 0x185
186 0x1bc00f34 0x186  134 133.00 0x133
187 0x1bdf54c4 0x191  145 144.00 0x144
188 0x1bfe9a54 0x184  132 131.00 0x131
189 0x1c2d82ac 0x1c6  198 197.00 0x197
190 0x1ce9240c 0x187  135 134.00 0x134
191 0x1cf8c6d4 0x19d  157 156.00 0x156
192 0x1d08699c 0x190  144 143.00 0x143
193 0x1d9522a4 0x192  146 145.00 0x145
194 0x1db46834 0x1b9  185 184.00 0x184
195 0x1dc40afc 0x1a0  160 159.00 0x159
196 0x1e21dbac 0x188  136 135.00 0x135
197 0x1e50c404 0x183  131 130.00 0x130
198 0x1e7fac5c 0x1b4  180 179.00 0x179
199 0x1e9ef1ec 0x1a9  169 168.00 0x168
200 0x1edd7d0c 0x1b8  184 183.00 0x183
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0F79402C
dwaddr            :    0F7DF02C
seq               :    0F7DF030
buf[187]          :    0F7DF034
tax               :    0F7DF0F0
bigdata[3001024]  :    0F7DF0F4
test              :    0F82A0F4
samplenum         :    0F82A0F8
sampleport[123]   :    0F82A0FC
bigdata2[4001024] :    0F82A2E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0F88E2F4
dwaddr            :    0F8D92F4
seq               :    0F8D92F8
buf[187]          :    0F8D92FC
tax               :    0F8D93B8
bigdata[3001024]  :    0F8D93BC
test              :    0F9243BC
samplenum         :    0F9243C0
sampleport[123]   :    0F9243C4
bigdata2[4001024] :    0F9245B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0F9885BC
dwaddr            :    0F9D35BC
seq               :    0F9D35C0
buf[187]          :    0F9D35C4
tax               :    0F9D3680
bigdata[3001024]  :    0F9D3684
test              :    0FA1E684
samplenum         :    0FA1E688
sampleport[123]   :    0FA1E68C
bigdata2[4001024] :    0FA1E878
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0FA82884
dwaddr            :    0FACD884
seq               :    0FACD888
buf[187]          :    0FACD88C
tax               :    0FACD948
bigdata[3001024]  :    0FACD94C
test              :    0FB1894C
samplenum         :    0FB18950
sampleport[123]   :    0FB18954
bigdata2[4001024] :    0FB18B40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0FB7CB4C
dwaddr            :    0FBC7B4C
seq               :    0FBC7B50
buf[187]          :    0FBC7B54
tax               :    0FBC7C10
bigdata[3001024]  :    0FBC7C14
test              :    0FC12C14
samplenum         :    0FC12C18
sampleport[123]   :    0FC12C1C
bigdata2[4001024] :    0FC12E08
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0FC76E14
dwaddr            :    0FCC1E14
seq               :    0FCC1E18
buf[187]          :    0FCC1E1C
tax               :    0FCC1ED8
bigdata[3001024]  :    0FCC1EDC
test              :    0FD0CEDC
samplenum         :    0FD0CEE0
sampleport[123]   :    0FD0CEE4
bigdata2[4001024] :    0FD0D0D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0FD710DC
dwaddr            :    0FDBC0DC
seq               :    0FDBC0E0
buf[187]          :    0FDBC0E4
tax               :    0FDBC1A0
bigdata[3001024]  :    0FDBC1A4
test              :    0FE071A4
samplenum         :    0FE071A8
sampleport[123]   :    0FE071AC
bigdata2[4001024] :    0FE07398
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0FE6B3A4
dwaddr            :    0FEB63A4
seq               :    0FEB63A8
buf[187]          :    0FEB63AC
tax               :    0FEB6468
bigdata[3001024]  :    0FEB646C
test              :    0FF0146C
samplenum         :    0FF01470
sampleport[123]   :    0FF01474
bigdata2[4001024] :    0FF01660
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    0FF6566C
dwaddr            :    0FFB066C
seq               :    0FFB0670
buf[187]          :    0FFB0674
tax               :    0FFB0730
bigdata[3001024]  :    0FFB0734
test              :    0FFFB734
samplenum         :    0FFFB738
sampleport[123]   :    0FFFB73C
bigdata2[4001024] :    0FFFB928
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1005F934
dwaddr            :    100AA934
seq               :    100AA938
buf[187]          :    100AA93C
tax               :    100AA9F8
bigdata[3001024]  :    100AA9FC
test              :    100F59FC
samplenum         :    100F5A00
sampleport[123]   :    100F5A04
bigdata2[4001024] :    100F5BF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10159BFC
dwaddr            :    101A4BFC
seq               :    101A4C00
buf[187]          :    101A4C04
tax               :    101A4CC0
bigdata[3001024]  :    101A4CC4
test              :    101EFCC4
samplenum         :    101EFCC8
sampleport[123]   :    101EFCCC
bigdata2[4001024] :    101EFEB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10253EC4
dwaddr            :    1029EEC4
seq               :    1029EEC8
buf[187]          :    1029EECC
tax               :    1029EF88
bigdata[3001024]  :    1029EF8C
test              :    102E9F8C
samplenum         :    102E9F90
sampleport[123]   :    102E9F94
bigdata2[4001024] :    102EA180
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1034E18C
dwaddr            :    1039918C
seq               :    10399190
buf[187]          :    10399194
tax               :    10399250
bigdata[3001024]  :    10399254
test              :    103E4254
samplenum         :    103E4258
sampleport[123]   :    103E425C
bigdata2[4001024] :    103E4448
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10448454
dwaddr            :    10493454
seq               :    10493458
buf[187]          :    1049345C
tax               :    10493518
bigdata[3001024]  :    1049351C
test              :    104DE51C
samplenum         :    104DE520
sampleport[123]   :    104DE524
bigdata2[4001024] :    104DE710
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1054271C
dwaddr            :    1058D71C
seq               :    1058D720
buf[187]          :    1058D724
tax               :    1058D7E0
bigdata[3001024]  :    1058D7E4
test              :    105D87E4
samplenum         :    105D87E8
sampleport[123]   :    105D87EC
bigdata2[4001024] :    105D89D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1063C9E4
dwaddr            :    106879E4
seq               :    106879E8
buf[187]          :    106879EC
tax               :    10687AA8
bigdata[3001024]  :    10687AAC
test              :    106D2AAC
samplenum         :    106D2AB0
sampleport[123]   :    106D2AB4
bigdata2[4001024] :    106D2CA0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10736CAC
dwaddr            :    10781CAC
seq               :    10781CB0
buf[187]          :    10781CB4
tax               :    10781D70
bigdata[3001024]  :    10781D74
test              :    107CCD74
samplenum         :    107CCD78
sampleport[123]   :    107CCD7C
bigdata2[4001024] :    107CCF68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10830F74
dwaddr            :    1087BF74
seq               :    1087BF78
buf[187]          :    1087BF7C
tax               :    1087C038
bigdata[3001024]  :    1087C03C
test              :    108C703C
samplenum         :    108C7040
sampleport[123]   :    108C7044
bigdata2[4001024] :    108C7230
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1092B23C
dwaddr            :    1097623C
seq               :    10976240
buf[187]          :    10976244
tax               :    10976300
bigdata[3001024]  :    10976304
test              :    109C1304
samplenum         :    109C1308
sampleport[123]   :    109C130C
bigdata2[4001024] :    109C14F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10A25504
dwaddr            :    10A70504
seq               :    10A70508
buf[187]          :    10A7050C
tax               :    10A705C8
bigdata[3001024]  :    10A705CC
test              :    10ABB5CC
samplenum         :    10ABB5D0
sampleport[123]   :    10ABB5D4
bigdata2[4001024] :    10ABB7C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10B1F7CC
dwaddr            :    10B6A7CC
seq               :    10B6A7D0
buf[187]          :    10B6A7D4
tax               :    10B6A890
bigdata[3001024]  :    10B6A894
test              :    10BB5894
samplenum         :    10BB5898
sampleport[123]   :    10BB589C
bigdata2[4001024] :    10BB5A88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10C19A94
dwaddr            :    10C64A94
seq               :    10C64A98
buf[187]          :    10C64A9C
tax               :    10C64B58
bigdata[3001024]  :    10C64B5C
test              :    10CAFB5C
samplenum         :    10CAFB60
sampleport[123]   :    10CAFB64
bigdata2[4001024] :    10CAFD50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10D13D5C
dwaddr            :    10D5ED5C
seq               :    10D5ED60
buf[187]          :    10D5ED64
tax               :    10D5EE20
bigdata[3001024]  :    10D5EE24
test              :    10DA9E24
samplenum         :    10DA9E28
sampleport[123]   :    10DA9E2C
bigdata2[4001024] :    10DAA018
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10E0E024
dwaddr            :    10E59024
seq               :    10E59028
buf[187]          :    10E5902C
tax               :    10E590E8
bigdata[3001024]  :    10E590EC
test              :    10EA40EC
samplenum         :    10EA40F0
sampleport[123]   :    10EA40F4
bigdata2[4001024] :    10EA42E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    10F082EC
dwaddr            :    10F532EC
seq               :    10F532F0
buf[187]          :    10F532F4
tax               :    10F533B0
bigdata[3001024]  :    10F533B4
test              :    10F9E3B4
samplenum         :    10F9E3B8
sampleport[123]   :    10F9E3BC
bigdata2[4001024] :    10F9E5A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    110025B4
dwaddr            :    1104D5B4
seq               :    1104D5B8
buf[187]          :    1104D5BC
tax               :    1104D678
bigdata[3001024]  :    1104D67C
test              :    1109867C
samplenum         :    11098680
sampleport[123]   :    11098684
bigdata2[4001024] :    11098870
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    110FC87C
dwaddr            :    1114787C
seq               :    11147880
buf[187]          :    11147884
tax               :    11147940
bigdata[3001024]  :    11147944
test              :    11192944
samplenum         :    11192948
sampleport[123]   :    1119294C
bigdata2[4001024] :    11192B38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    111F6B44
dwaddr            :    11241B44
seq               :    11241B48
buf[187]          :    11241B4C
tax               :    11241C08
bigdata[3001024]  :    11241C0C
test              :    1128CC0C
samplenum         :    1128CC10
sampleport[123]   :    1128CC14
bigdata2[4001024] :    1128CE00
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    112F0E0C
dwaddr            :    1133BE0C
seq               :    1133BE10
buf[187]          :    1133BE14
tax               :    1133BED0
bigdata[3001024]  :    1133BED4
test              :    11386ED4
samplenum         :    11386ED8
sampleport[123]   :    11386EDC
bigdata2[4001024] :    113870C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    113EB0D4
dwaddr            :    114360D4
seq               :    114360D8
buf[187]          :    114360DC
tax               :    11436198
bigdata[3001024]  :    1143619C
test              :    1148119C
samplenum         :    114811A0
sampleport[123]   :    114811A4
bigdata2[4001024] :    11481390
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    114E539C
dwaddr            :    1153039C
seq               :    115303A0
buf[187]          :    115303A4
tax               :    11530460
bigdata[3001024]  :    11530464
test              :    1157B464
samplenum         :    1157B468
sampleport[123]   :    1157B46C
bigdata2[4001024] :    1157B658
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    115DF664
dwaddr            :    1162A664
seq               :    1162A668
buf[187]          :    1162A66C
tax               :    1162A728
bigdata[3001024]  :    1162A72C
test              :    1167572C
samplenum         :    11675730
sampleport[123]   :    11675734
bigdata2[4001024] :    11675920
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    116D992C
dwaddr            :    1172492C
seq               :    11724930
buf[187]          :    11724934
tax               :    117249F0
bigdata[3001024]  :    117249F4
test              :    1176F9F4
samplenum         :    1176F9F8
sampleport[123]   :    1176F9FC
bigdata2[4001024] :    1176FBE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    117D3BF4
dwaddr            :    1181EBF4
seq               :    1181EBF8
buf[187]          :    1181EBFC
tax               :    1181ECB8
bigdata[3001024]  :    1181ECBC
test              :    11869CBC
samplenum         :    11869CC0
sampleport[123]   :    11869CC4
bigdata2[4001024] :    11869EB0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    118CDEBC
dwaddr            :    11918EBC
seq               :    11918EC0
buf[187]          :    11918EC4
tax               :    11918F80
bigdata[3001024]  :    11918F84
test              :    11963F84
samplenum         :    11963F88
sampleport[123]   :    11963F8C
bigdata2[4001024] :    11964178
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    119C8184
dwaddr            :    11A13184
seq               :    11A13188
buf[187]          :    11A1318C
tax               :    11A13248
bigdata[3001024]  :    11A1324C
test              :    11A5E24C
samplenum         :    11A5E250
sampleport[123]   :    11A5E254
bigdata2[4001024] :    11A5E440
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    11AC244C
dwaddr            :    11B0D44C
seq               :    11B0D450
buf[187]          :    11B0D454
tax               :    11B0D510
bigdata[3001024]  :    11B0D514
test              :    11B58514
samplenum         :    11B58518
sampleport[123]   :    11B5851C
bigdata2[4001024] :    11B58708
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    11BBC714
dwaddr            :    11C07714
seq               :    11C07718
buf[187]          :    11C0771C
tax               :    11C077D8
bigdata[3001024]  :    11C077DC
test              :    11C527DC
samplenum         :    11C527E0
sampleport[123]   :    11C527E4
bigdata2[4001024] :    11C529D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    11CB69DC
dwaddr            :    11D019DC
seq               :    11D019E0
buf[187]          :    11D019E4
tax               :    11D01AA0
bigdata[3001024]  :    11D01AA4
test              :    11D4CAA4
samplenum         :    11D4CAA8
sampleport[123]   :    11D4CAAC
bigdata2[4001024] :    11D4CC98
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    11DB0CA4
dwaddr            :    11DFBCA4
seq               :    11DFBCA8
buf[187]          :    11DFBCAC
tax               :    11DFBD68
bigdata[3001024]  :    11DFBD6C
test              :    11E46D6C
samplenum         :    11E46D70
sampleport[123]   :    11E46D74
bigdata2[4001024] :    11E46F60
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    11EAAF6C
dwaddr            :    11EF5F6C
seq               :    11EF5F70
buf[187]          :    11EF5F74
tax               :    11EF6030
bigdata[3001024]  :    11EF6034
test              :    11F41034
samplenum         :    11F41038
sampleport[123]   :    11F4103C
bigdata2[4001024] :    11F41228
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    11FA5234
dwaddr            :    11FF0234
seq               :    11FF0238
buf[187]          :    11FF023C
tax               :    11FF02F8
bigdata[3001024]  :    11FF02FC
test              :    1203B2FC
samplenum         :    1203B300
sampleport[123]   :    1203B304
bigdata2[4001024] :    1203B4F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1209F4FC
dwaddr            :    120EA4FC
seq               :    120EA500
buf[187]          :    120EA504
tax               :    120EA5C0
bigdata[3001024]  :    120EA5C4
test              :    121355C4
samplenum         :    121355C8
sampleport[123]   :    121355CC
bigdata2[4001024] :    121357B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    121997C4
dwaddr            :    121E47C4
seq               :    121E47C8
buf[187]          :    121E47CC
tax               :    121E4888
bigdata[3001024]  :    121E488C
test              :    1222F88C
samplenum         :    1222F890
sampleport[123]   :    1222F894
bigdata2[4001024] :    1222FA80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12293A8C
dwaddr            :    122DEA8C
seq               :    122DEA90
buf[187]          :    122DEA94
tax               :    122DEB50
bigdata[3001024]  :    122DEB54
test              :    12329B54
samplenum         :    12329B58
sampleport[123]   :    12329B5C
bigdata2[4001024] :    12329D48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1238DD54
dwaddr            :    123D8D54
seq               :    123D8D58
buf[187]          :    123D8D5C
tax               :    123D8E18
bigdata[3001024]  :    123D8E1C
test              :    12423E1C
samplenum         :    12423E20
sampleport[123]   :    12423E24
bigdata2[4001024] :    12424010
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1248801C
dwaddr            :    124D301C
seq               :    124D3020
buf[187]          :    124D3024
tax               :    124D30E0
bigdata[3001024]  :    124D30E4
test              :    1251E0E4
samplenum         :    1251E0E8
sampleport[123]   :    1251E0EC
bigdata2[4001024] :    1251E2D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    125822E4
dwaddr            :    125CD2E4
seq               :    125CD2E8
buf[187]          :    125CD2EC
tax               :    125CD3A8
bigdata[3001024]  :    125CD3AC
test              :    126183AC
samplenum         :    126183B0
sampleport[123]   :    126183B4
bigdata2[4001024] :    126185A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1267C5AC
dwaddr            :    126C75AC
seq               :    126C75B0
buf[187]          :    126C75B4
tax               :    126C7670
bigdata[3001024]  :    126C7674
test              :    12712674
samplenum         :    12712678
sampleport[123]   :    1271267C
bigdata2[4001024] :    12712868
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12776874
dwaddr            :    127C1874
seq               :    127C1878
buf[187]          :    127C187C
tax               :    127C1938
bigdata[3001024]  :    127C193C
test              :    1280C93C
samplenum         :    1280C940
sampleport[123]   :    1280C944
bigdata2[4001024] :    1280CB30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12870B3C
dwaddr            :    128BBB3C
seq               :    128BBB40
buf[187]          :    128BBB44
tax               :    128BBC00
bigdata[3001024]  :    128BBC04
test              :    12906C04
samplenum         :    12906C08
sampleport[123]   :    12906C0C
bigdata2[4001024] :    12906DF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1296AE04
dwaddr            :    129B5E04
seq               :    129B5E08
buf[187]          :    129B5E0C
tax               :    129B5EC8
bigdata[3001024]  :    129B5ECC
test              :    12A00ECC
samplenum         :    12A00ED0
sampleport[123]   :    12A00ED4
bigdata2[4001024] :    12A010C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12A650CC
dwaddr            :    12AB00CC
seq               :    12AB00D0
buf[187]          :    12AB00D4
tax               :    12AB0190
bigdata[3001024]  :    12AB0194
test              :    12AFB194
samplenum         :    12AFB198
sampleport[123]   :    12AFB19C
bigdata2[4001024] :    12AFB388
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12B5F394
dwaddr            :    12BAA394
seq               :    12BAA398
buf[187]          :    12BAA39C
tax               :    12BAA458
bigdata[3001024]  :    12BAA45C
test              :    12BF545C
samplenum         :    12BF5460
sampleport[123]   :    12BF5464
bigdata2[4001024] :    12BF5650
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12C5965C
dwaddr            :    12CA465C
seq               :    12CA4660
buf[187]          :    12CA4664
tax               :    12CA4720
bigdata[3001024]  :    12CA4724
test              :    12CEF724
samplenum         :    12CEF728
sampleport[123]   :    12CEF72C
bigdata2[4001024] :    12CEF918
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12D53924
dwaddr            :    12D9E924
seq               :    12D9E928
buf[187]          :    12D9E92C
tax               :    12D9E9E8
bigdata[3001024]  :    12D9E9EC
test              :    12DE99EC
samplenum         :    12DE99F0
sampleport[123]   :    12DE99F4
bigdata2[4001024] :    12DE9BE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12E4DBEC
dwaddr            :    12E98BEC
seq               :    12E98BF0
buf[187]          :    12E98BF4
tax               :    12E98CB0
bigdata[3001024]  :    12E98CB4
test              :    12EE3CB4
samplenum         :    12EE3CB8
sampleport[123]   :    12EE3CBC
bigdata2[4001024] :    12EE3EA8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12F47EB4
dwaddr            :    12F92EB4
seq               :    12F92EB8
buf[187]          :    12F92EBC
tax               :    12F92F78
bigdata[3001024]  :    12F92F7C
test              :    12FDDF7C
samplenum         :    12FDDF80
sampleport[123]   :    12FDDF84
bigdata2[4001024] :    12FDE170
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1304217C
dwaddr            :    1308D17C
seq               :    1308D180
buf[187]          :    1308D184
tax               :    1308D240
bigdata[3001024]  :    1308D244
test              :    130D8244
samplenum         :    130D8248
sampleport[123]   :    130D824C
bigdata2[4001024] :    130D8438
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1313C444
dwaddr            :    13187444
seq               :    13187448
buf[187]          :    1318744C
tax               :    13187508
bigdata[3001024]  :    1318750C
test              :    131D250C
samplenum         :    131D2510
sampleport[123]   :    131D2514
bigdata2[4001024] :    131D2700
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1323670C
dwaddr            :    1328170C
seq               :    13281710
buf[187]          :    13281714
tax               :    132817D0
bigdata[3001024]  :    132817D4
test              :    132CC7D4
samplenum         :    132CC7D8
sampleport[123]   :    132CC7DC
bigdata2[4001024] :    132CC9C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    133309D4
dwaddr            :    1337B9D4
seq               :    1337B9D8
buf[187]          :    1337B9DC
tax               :    1337BA98
bigdata[3001024]  :    1337BA9C
test              :    133C6A9C
samplenum         :    133C6AA0
sampleport[123]   :    133C6AA4
bigdata2[4001024] :    133C6C90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1342AC9C
dwaddr            :    13475C9C
seq               :    13475CA0
buf[187]          :    13475CA4
tax               :    13475D60
bigdata[3001024]  :    13475D64
test              :    134C0D64
samplenum         :    134C0D68
sampleport[123]   :    134C0D6C
bigdata2[4001024] :    134C0F58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13524F64
dwaddr            :    1356FF64
seq               :    1356FF68
buf[187]          :    1356FF6C
tax               :    13570028
bigdata[3001024]  :    1357002C
test              :    135BB02C
samplenum         :    135BB030
sampleport[123]   :    135BB034
bigdata2[4001024] :    135BB220
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1361F22C
dwaddr            :    1366A22C
seq               :    1366A230
buf[187]          :    1366A234
tax               :    1366A2F0
bigdata[3001024]  :    1366A2F4
test              :    136B52F4
samplenum         :    136B52F8
sampleport[123]   :    136B52FC
bigdata2[4001024] :    136B54E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    137194F4
dwaddr            :    137644F4
seq               :    137644F8
buf[187]          :    137644FC
tax               :    137645B8
bigdata[3001024]  :    137645BC
test              :    137AF5BC
samplenum         :    137AF5C0
sampleport[123]   :    137AF5C4
bigdata2[4001024] :    137AF7B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    138137BC
dwaddr            :    1385E7BC
seq               :    1385E7C0
buf[187]          :    1385E7C4
tax               :    1385E880
bigdata[3001024]  :    1385E884
test              :    138A9884
samplenum         :    138A9888
sampleport[123]   :    138A988C
bigdata2[4001024] :    138A9A78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1390DA84
dwaddr            :    13958A84
seq               :    13958A88
buf[187]          :    13958A8C
tax               :    13958B48
bigdata[3001024]  :    13958B4C
test              :    139A3B4C
samplenum         :    139A3B50
sampleport[123]   :    139A3B54
bigdata2[4001024] :    139A3D40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13A07D4C
dwaddr            :    13A52D4C
seq               :    13A52D50
buf[187]          :    13A52D54
tax               :    13A52E10
bigdata[3001024]  :    13A52E14
test              :    13A9DE14
samplenum         :    13A9DE18
sampleport[123]   :    13A9DE1C
bigdata2[4001024] :    13A9E008
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13B02014
dwaddr            :    13B4D014
seq               :    13B4D018
buf[187]          :    13B4D01C
tax               :    13B4D0D8
bigdata[3001024]  :    13B4D0DC
test              :    13B980DC
samplenum         :    13B980E0
sampleport[123]   :    13B980E4
bigdata2[4001024] :    13B982D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13BFC2DC
dwaddr            :    13C472DC
seq               :    13C472E0
buf[187]          :    13C472E4
tax               :    13C473A0
bigdata[3001024]  :    13C473A4
test              :    13C923A4
samplenum         :    13C923A8
sampleport[123]   :    13C923AC
bigdata2[4001024] :    13C92598
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13CF65A4
dwaddr            :    13D415A4
seq               :    13D415A8
buf[187]          :    13D415AC
tax               :    13D41668
bigdata[3001024]  :    13D4166C
test              :    13D8C66C
samplenum         :    13D8C670
sampleport[123]   :    13D8C674
bigdata2[4001024] :    13D8C860
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13DF086C
dwaddr            :    13E3B86C
seq               :    13E3B870
buf[187]          :    13E3B874
tax               :    13E3B930
bigdata[3001024]  :    13E3B934
test              :    13E86934
samplenum         :    13E86938
sampleport[123]   :    13E8693C
bigdata2[4001024] :    13E86B28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13EEAB34
dwaddr            :    13F35B34
seq               :    13F35B38
buf[187]          :    13F35B3C
tax               :    13F35BF8
bigdata[3001024]  :    13F35BFC
test              :    13F80BFC
samplenum         :    13F80C00
sampleport[123]   :    13F80C04
bigdata2[4001024] :    13F80DF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13FE4DFC
dwaddr            :    1402FDFC
seq               :    1402FE00
buf[187]          :    1402FE04
tax               :    1402FEC0
bigdata[3001024]  :    1402FEC4
test              :    1407AEC4
samplenum         :    1407AEC8
sampleport[123]   :    1407AECC
bigdata2[4001024] :    1407B0B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    140DF0C4
dwaddr            :    1412A0C4
seq               :    1412A0C8
buf[187]          :    1412A0CC
tax               :    1412A188
bigdata[3001024]  :    1412A18C
test              :    1417518C
samplenum         :    14175190
sampleport[123]   :    14175194
bigdata2[4001024] :    14175380
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    141D938C
dwaddr            :    1422438C
seq               :    14224390
buf[187]          :    14224394
tax               :    14224450
bigdata[3001024]  :    14224454
test              :    1426F454
samplenum         :    1426F458
sampleport[123]   :    1426F45C
bigdata2[4001024] :    1426F648
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    142D3654
dwaddr            :    1431E654
seq               :    1431E658
buf[187]          :    1431E65C
tax               :    1431E718
bigdata[3001024]  :    1431E71C
test              :    1436971C
samplenum         :    14369720
sampleport[123]   :    14369724
bigdata2[4001024] :    14369910
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    143CD91C
dwaddr            :    1441891C
seq               :    14418920
buf[187]          :    14418924
tax               :    144189E0
bigdata[3001024]  :    144189E4
test              :    144639E4
samplenum         :    144639E8
sampleport[123]   :    144639EC
bigdata2[4001024] :    14463BD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    144C7BE4
dwaddr            :    14512BE4
seq               :    14512BE8
buf[187]          :    14512BEC
tax               :    14512CA8
bigdata[3001024]  :    14512CAC
test              :    1455DCAC
samplenum         :    1455DCB0
sampleport[123]   :    1455DCB4
bigdata2[4001024] :    1455DEA0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    145C1EAC
dwaddr            :    1460CEAC
seq               :    1460CEB0
buf[187]          :    1460CEB4
tax               :    1460CF70
bigdata[3001024]  :    1460CF74
test              :    14657F74
samplenum         :    14657F78
sampleport[123]   :    14657F7C
bigdata2[4001024] :    14658168
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    146BC174
dwaddr            :    14707174
seq               :    14707178
buf[187]          :    1470717C
tax               :    14707238
bigdata[3001024]  :    1470723C
test              :    1475223C
samplenum         :    14752240
sampleport[123]   :    14752244
bigdata2[4001024] :    14752430
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    147B643C
dwaddr            :    1480143C
seq               :    14801440
buf[187]          :    14801444
tax               :    14801500
bigdata[3001024]  :    14801504
test              :    1484C504
samplenum         :    1484C508
sampleport[123]   :    1484C50C
bigdata2[4001024] :    1484C6F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    148B0704
dwaddr            :    148FB704
seq               :    148FB708
buf[187]          :    148FB70C
tax               :    148FB7C8
bigdata[3001024]  :    148FB7CC
test              :    149467CC
samplenum         :    149467D0
sampleport[123]   :    149467D4
bigdata2[4001024] :    149469C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    149AA9CC
dwaddr            :    149F59CC
seq               :    149F59D0
buf[187]          :    149F59D4
tax               :    149F5A90
bigdata[3001024]  :    149F5A94
test              :    14A40A94
samplenum         :    14A40A98
sampleport[123]   :    14A40A9C
bigdata2[4001024] :    14A40C88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14AA4C94
dwaddr            :    14AEFC94
seq               :    14AEFC98
buf[187]          :    14AEFC9C
tax               :    14AEFD58
bigdata[3001024]  :    14AEFD5C
test              :    14B3AD5C
samplenum         :    14B3AD60
sampleport[123]   :    14B3AD64
bigdata2[4001024] :    14B3AF50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14B9EF5C
dwaddr            :    14BE9F5C
seq               :    14BE9F60
buf[187]          :    14BE9F64
tax               :    14BEA020
bigdata[3001024]  :    14BEA024
test              :    14C35024
samplenum         :    14C35028
sampleport[123]   :    14C3502C
bigdata2[4001024] :    14C35218
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14C99224
dwaddr            :    14CE4224
seq               :    14CE4228
buf[187]          :    14CE422C
tax               :    14CE42E8
bigdata[3001024]  :    14CE42EC
test              :    14D2F2EC
samplenum         :    14D2F2F0
sampleport[123]   :    14D2F2F4
bigdata2[4001024] :    14D2F4E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14D934EC
dwaddr            :    14DDE4EC
seq               :    14DDE4F0
buf[187]          :    14DDE4F4
tax               :    14DDE5B0
bigdata[3001024]  :    14DDE5B4
test              :    14E295B4
samplenum         :    14E295B8
sampleport[123]   :    14E295BC
bigdata2[4001024] :    14E297A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14E8D7B4
dwaddr            :    14ED87B4
seq               :    14ED87B8
buf[187]          :    14ED87BC
tax               :    14ED8878
bigdata[3001024]  :    14ED887C
test              :    14F2387C
samplenum         :    14F23880
sampleport[123]   :    14F23884
bigdata2[4001024] :    14F23A70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14F87A7C
dwaddr            :    14FD2A7C
seq               :    14FD2A80
buf[187]          :    14FD2A84
tax               :    14FD2B40
bigdata[3001024]  :    14FD2B44
test              :    1501DB44
samplenum         :    1501DB48
sampleport[123]   :    1501DB4C
bigdata2[4001024] :    1501DD38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15081D44
dwaddr            :    150CCD44
seq               :    150CCD48
buf[187]          :    150CCD4C
tax               :    150CCE08
bigdata[3001024]  :    150CCE0C
test              :    15117E0C
samplenum         :    15117E10
sampleport[123]   :    15117E14
bigdata2[4001024] :    15118000
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1517C00C
dwaddr            :    151C700C
seq               :    151C7010
buf[187]          :    151C7014
tax               :    151C70D0
bigdata[3001024]  :    151C70D4
test              :    152120D4
samplenum         :    152120D8
sampleport[123]   :    152120DC
bigdata2[4001024] :    152122C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    152762D4
dwaddr            :    152C12D4
seq               :    152C12D8
buf[187]          :    152C12DC
tax               :    152C1398
bigdata[3001024]  :    152C139C
test              :    1530C39C
samplenum         :    1530C3A0
sampleport[123]   :    1530C3A4
bigdata2[4001024] :    1530C590
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1537059C
dwaddr            :    153BB59C
seq               :    153BB5A0
buf[187]          :    153BB5A4
tax               :    153BB660
bigdata[3001024]  :    153BB664
test              :    15406664
samplenum         :    15406668
sampleport[123]   :    1540666C
bigdata2[4001024] :    15406858
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1546A864
dwaddr            :    154B5864
seq               :    154B5868
buf[187]          :    154B586C
tax               :    154B5928
bigdata[3001024]  :    154B592C
test              :    1550092C
samplenum         :    15500930
sampleport[123]   :    15500934
bigdata2[4001024] :    15500B20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15564B2C
dwaddr            :    155AFB2C
seq               :    155AFB30
buf[187]          :    155AFB34
tax               :    155AFBF0
bigdata[3001024]  :    155AFBF4
test              :    155FABF4
samplenum         :    155FABF8
sampleport[123]   :    155FABFC
bigdata2[4001024] :    155FADE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1565EDF4
dwaddr            :    156A9DF4
seq               :    156A9DF8
buf[187]          :    156A9DFC
tax               :    156A9EB8
bigdata[3001024]  :    156A9EBC
test              :    156F4EBC
samplenum         :    156F4EC0
sampleport[123]   :    156F4EC4
bigdata2[4001024] :    156F50B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    157590BC
dwaddr            :    157A40BC
seq               :    157A40C0
buf[187]          :    157A40C4
tax               :    157A4180
bigdata[3001024]  :    157A4184
test              :    157EF184
samplenum         :    157EF188
sampleport[123]   :    157EF18C
bigdata2[4001024] :    157EF378
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15853384
dwaddr            :    1589E384
seq               :    1589E388
buf[187]          :    1589E38C
tax               :    1589E448
bigdata[3001024]  :    1589E44C
test              :    158E944C
samplenum         :    158E9450
sampleport[123]   :    158E9454
bigdata2[4001024] :    158E9640
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1594D64C
dwaddr            :    1599864C
seq               :    15998650
buf[187]          :    15998654
tax               :    15998710
bigdata[3001024]  :    15998714
test              :    159E3714
samplenum         :    159E3718
sampleport[123]   :    159E371C
bigdata2[4001024] :    159E3908
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15A47914
dwaddr            :    15A92914
seq               :    15A92918
buf[187]          :    15A9291C
tax               :    15A929D8
bigdata[3001024]  :    15A929DC
test              :    15ADD9DC
samplenum         :    15ADD9E0
sampleport[123]   :    15ADD9E4
bigdata2[4001024] :    15ADDBD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15B41BDC
dwaddr            :    15B8CBDC
seq               :    15B8CBE0
buf[187]          :    15B8CBE4
tax               :    15B8CCA0
bigdata[3001024]  :    15B8CCA4
test              :    15BD7CA4
samplenum         :    15BD7CA8
sampleport[123]   :    15BD7CAC
bigdata2[4001024] :    15BD7E98
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15C3BEA4
dwaddr            :    15C86EA4
seq               :    15C86EA8
buf[187]          :    15C86EAC
tax               :    15C86F68
bigdata[3001024]  :    15C86F6C
test              :    15CD1F6C
samplenum         :    15CD1F70
sampleport[123]   :    15CD1F74
bigdata2[4001024] :    15CD2160
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15D3616C
dwaddr            :    15D8116C
seq               :    15D81170
buf[187]          :    15D81174
tax               :    15D81230
bigdata[3001024]  :    15D81234
test              :    15DCC234
samplenum         :    15DCC238
sampleport[123]   :    15DCC23C
bigdata2[4001024] :    15DCC428
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15E30434
dwaddr            :    15E7B434
seq               :    15E7B438
buf[187]          :    15E7B43C
tax               :    15E7B4F8
bigdata[3001024]  :    15E7B4FC
test              :    15EC64FC
samplenum         :    15EC6500
sampleport[123]   :    15EC6504
bigdata2[4001024] :    15EC66F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15F2A6FC
dwaddr            :    15F756FC
seq               :    15F75700
buf[187]          :    15F75704
tax               :    15F757C0
bigdata[3001024]  :    15F757C4
test              :    15FC07C4
samplenum         :    15FC07C8
sampleport[123]   :    15FC07CC
bigdata2[4001024] :    15FC09B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    160249C4
dwaddr            :    1606F9C4
seq               :    1606F9C8
buf[187]          :    1606F9CC
tax               :    1606FA88
bigdata[3001024]  :    1606FA8C
test              :    160BAA8C
samplenum         :    160BAA90
sampleport[123]   :    160BAA94
bigdata2[4001024] :    160BAC80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1611EC8C
dwaddr            :    16169C8C
seq               :    16169C90
buf[187]          :    16169C94
tax               :    16169D50
bigdata[3001024]  :    16169D54
test              :    161B4D54
samplenum         :    161B4D58
sampleport[123]   :    161B4D5C
bigdata2[4001024] :    161B4F48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16218F54
dwaddr            :    16263F54
seq               :    16263F58
buf[187]          :    16263F5C
tax               :    16264018
bigdata[3001024]  :    1626401C
test              :    162AF01C
samplenum         :    162AF020
sampleport[123]   :    162AF024
bigdata2[4001024] :    162AF210
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1631321C
dwaddr            :    1635E21C
seq               :    1635E220
buf[187]          :    1635E224
tax               :    1635E2E0
bigdata[3001024]  :    1635E2E4
test              :    163A92E4
samplenum         :    163A92E8
sampleport[123]   :    163A92EC
bigdata2[4001024] :    163A94D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1640D4E4
dwaddr            :    164584E4
seq               :    164584E8
buf[187]          :    164584EC
tax               :    164585A8
bigdata[3001024]  :    164585AC
test              :    164A35AC
samplenum         :    164A35B0
sampleport[123]   :    164A35B4
bigdata2[4001024] :    164A37A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    165077AC
dwaddr            :    165527AC
seq               :    165527B0
buf[187]          :    165527B4
tax               :    16552870
bigdata[3001024]  :    16552874
test              :    1659D874
samplenum         :    1659D878
sampleport[123]   :    1659D87C
bigdata2[4001024] :    1659DA68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16601A74
dwaddr            :    1664CA74
seq               :    1664CA78
buf[187]          :    1664CA7C
tax               :    1664CB38
bigdata[3001024]  :    1664CB3C
test              :    16697B3C
samplenum         :    16697B40
sampleport[123]   :    16697B44
bigdata2[4001024] :    16697D30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    166FBD3C
dwaddr            :    16746D3C
seq               :    16746D40
buf[187]          :    16746D44
tax               :    16746E00
bigdata[3001024]  :    16746E04
test              :    16791E04
samplenum         :    16791E08
sampleport[123]   :    16791E0C
bigdata2[4001024] :    16791FF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    167F6004
dwaddr            :    16841004
seq               :    16841008
buf[187]          :    1684100C
tax               :    168410C8
bigdata[3001024]  :    168410CC
test              :    1688C0CC
samplenum         :    1688C0D0
sampleport[123]   :    1688C0D4
bigdata2[4001024] :    1688C2C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    168F02CC
dwaddr            :    1693B2CC
seq               :    1693B2D0
buf[187]          :    1693B2D4
tax               :    1693B390
bigdata[3001024]  :    1693B394
test              :    16986394
samplenum         :    16986398
sampleport[123]   :    1698639C
bigdata2[4001024] :    16986588
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    169EA594
dwaddr            :    16A35594
seq               :    16A35598
buf[187]          :    16A3559C
tax               :    16A35658
bigdata[3001024]  :    16A3565C
test              :    16A8065C
samplenum         :    16A80660
sampleport[123]   :    16A80664
bigdata2[4001024] :    16A80850
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16AE485C
dwaddr            :    16B2F85C
seq               :    16B2F860
buf[187]          :    16B2F864
tax               :    16B2F920
bigdata[3001024]  :    16B2F924
test              :    16B7A924
samplenum         :    16B7A928
sampleport[123]   :    16B7A92C
bigdata2[4001024] :    16B7AB18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16BDEB24
dwaddr            :    16C29B24
seq               :    16C29B28
buf[187]          :    16C29B2C
tax               :    16C29BE8
bigdata[3001024]  :    16C29BEC
test              :    16C74BEC
samplenum         :    16C74BF0
sampleport[123]   :    16C74BF4
bigdata2[4001024] :    16C74DE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16CD8DEC
dwaddr            :    16D23DEC
seq               :    16D23DF0
buf[187]          :    16D23DF4
tax               :    16D23EB0
bigdata[3001024]  :    16D23EB4
test              :    16D6EEB4
samplenum         :    16D6EEB8
sampleport[123]   :    16D6EEBC
bigdata2[4001024] :    16D6F0A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16DD30B4
dwaddr            :    16E1E0B4
seq               :    16E1E0B8
buf[187]          :    16E1E0BC
tax               :    16E1E178
bigdata[3001024]  :    16E1E17C
test              :    16E6917C
samplenum         :    16E69180
sampleport[123]   :    16E69184
bigdata2[4001024] :    16E69370
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16ECD37C
dwaddr            :    16F1837C
seq               :    16F18380
buf[187]          :    16F18384
tax               :    16F18440
bigdata[3001024]  :    16F18444
test              :    16F63444
samplenum         :    16F63448
sampleport[123]   :    16F6344C
bigdata2[4001024] :    16F63638
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16FC7644
dwaddr            :    17012644
seq               :    17012648
buf[187]          :    1701264C
tax               :    17012708
bigdata[3001024]  :    1701270C
test              :    1705D70C
samplenum         :    1705D710
sampleport[123]   :    1705D714
bigdata2[4001024] :    1705D900
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    170C190C
dwaddr            :    1710C90C
seq               :    1710C910
buf[187]          :    1710C914
tax               :    1710C9D0
bigdata[3001024]  :    1710C9D4
test              :    171579D4
samplenum         :    171579D8
sampleport[123]   :    171579DC
bigdata2[4001024] :    17157BC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    171BBBD4
dwaddr            :    17206BD4
seq               :    17206BD8
buf[187]          :    17206BDC
tax               :    17206C98
bigdata[3001024]  :    17206C9C
test              :    17251C9C
samplenum         :    17251CA0
sampleport[123]   :    17251CA4
bigdata2[4001024] :    17251E90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    172B5E9C
dwaddr            :    17300E9C
seq               :    17300EA0
buf[187]          :    17300EA4
tax               :    17300F60
bigdata[3001024]  :    17300F64
test              :    1734BF64
samplenum         :    1734BF68
sampleport[123]   :    1734BF6C
bigdata2[4001024] :    1734C158
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    173B0164
dwaddr            :    173FB164
seq               :    173FB168
buf[187]          :    173FB16C
tax               :    173FB228
bigdata[3001024]  :    173FB22C
test              :    1744622C
samplenum         :    17446230
sampleport[123]   :    17446234
bigdata2[4001024] :    17446420
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    174AA42C
dwaddr            :    174F542C
seq               :    174F5430
buf[187]          :    174F5434
tax               :    174F54F0
bigdata[3001024]  :    174F54F4
test              :    175404F4
samplenum         :    175404F8
sampleport[123]   :    175404FC
bigdata2[4001024] :    175406E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    175A46F4
dwaddr            :    175EF6F4
seq               :    175EF6F8
buf[187]          :    175EF6FC
tax               :    175EF7B8
bigdata[3001024]  :    175EF7BC
test              :    1763A7BC
samplenum         :    1763A7C0
sampleport[123]   :    1763A7C4
bigdata2[4001024] :    1763A9B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1769E9BC
dwaddr            :    176E99BC
seq               :    176E99C0
buf[187]          :    176E99C4
tax               :    176E9A80
bigdata[3001024]  :    176E9A84
test              :    17734A84
samplenum         :    17734A88
sampleport[123]   :    17734A8C
bigdata2[4001024] :    17734C78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17798C84
dwaddr            :    177E3C84
seq               :    177E3C88
buf[187]          :    177E3C8C
tax               :    177E3D48
bigdata[3001024]  :    177E3D4C
test              :    1782ED4C
samplenum         :    1782ED50
sampleport[123]   :    1782ED54
bigdata2[4001024] :    1782EF40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17892F4C
dwaddr            :    178DDF4C
seq               :    178DDF50
buf[187]          :    178DDF54
tax               :    178DE010
bigdata[3001024]  :    178DE014
test              :    17929014
samplenum         :    17929018
sampleport[123]   :    1792901C
bigdata2[4001024] :    17929208
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1798D214
dwaddr            :    179D8214
seq               :    179D8218
buf[187]          :    179D821C
tax               :    179D82D8
bigdata[3001024]  :    179D82DC
test              :    17A232DC
samplenum         :    17A232E0
sampleport[123]   :    17A232E4
bigdata2[4001024] :    17A234D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17A874DC
dwaddr            :    17AD24DC
seq               :    17AD24E0
buf[187]          :    17AD24E4
tax               :    17AD25A0
bigdata[3001024]  :    17AD25A4
test              :    17B1D5A4
samplenum         :    17B1D5A8
sampleport[123]   :    17B1D5AC
bigdata2[4001024] :    17B1D798
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17B817A4
dwaddr            :    17BCC7A4
seq               :    17BCC7A8
buf[187]          :    17BCC7AC
tax               :    17BCC868
bigdata[3001024]  :    17BCC86C
test              :    17C1786C
samplenum         :    17C17870
sampleport[123]   :    17C17874
bigdata2[4001024] :    17C17A60
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17C7BA6C
dwaddr            :    17CC6A6C
seq               :    17CC6A70
buf[187]          :    17CC6A74
tax               :    17CC6B30
bigdata[3001024]  :    17CC6B34
test              :    17D11B34
samplenum         :    17D11B38
sampleport[123]   :    17D11B3C
bigdata2[4001024] :    17D11D28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17D75D34
dwaddr            :    17DC0D34
seq               :    17DC0D38
buf[187]          :    17DC0D3C
tax               :    17DC0DF8
bigdata[3001024]  :    17DC0DFC
test              :    17E0BDFC
samplenum         :    17E0BE00
sampleport[123]   :    17E0BE04
bigdata2[4001024] :    17E0BFF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17E6FFFC
dwaddr            :    17EBAFFC
seq               :    17EBB000
buf[187]          :    17EBB004
tax               :    17EBB0C0
bigdata[3001024]  :    17EBB0C4
test              :    17F060C4
samplenum         :    17F060C8
sampleport[123]   :    17F060CC
bigdata2[4001024] :    17F062B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17F6A2C4
dwaddr            :    17FB52C4
seq               :    17FB52C8
buf[187]          :    17FB52CC
tax               :    17FB5388
bigdata[3001024]  :    17FB538C
test              :    1800038C
samplenum         :    18000390
sampleport[123]   :    18000394
bigdata2[4001024] :    18000580
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1806458C
dwaddr            :    180AF58C
seq               :    180AF590
buf[187]          :    180AF594
tax               :    180AF650
bigdata[3001024]  :    180AF654
test              :    180FA654
samplenum         :    180FA658
sampleport[123]   :    180FA65C
bigdata2[4001024] :    180FA848
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1815E854
dwaddr            :    181A9854
seq               :    181A9858
buf[187]          :    181A985C
tax               :    181A9918
bigdata[3001024]  :    181A991C
test              :    181F491C
samplenum         :    181F4920
sampleport[123]   :    181F4924
bigdata2[4001024] :    181F4B10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18258B1C
dwaddr            :    182A3B1C
seq               :    182A3B20
buf[187]          :    182A3B24
tax               :    182A3BE0
bigdata[3001024]  :    182A3BE4
test              :    182EEBE4
samplenum         :    182EEBE8
sampleport[123]   :    182EEBEC
bigdata2[4001024] :    182EEDD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18352DE4
dwaddr            :    1839DDE4
seq               :    1839DDE8
buf[187]          :    1839DDEC
tax               :    1839DEA8
bigdata[3001024]  :    1839DEAC
test              :    183E8EAC
samplenum         :    183E8EB0
sampleport[123]   :    183E8EB4
bigdata2[4001024] :    183E90A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1844D0AC
dwaddr            :    184980AC
seq               :    184980B0
buf[187]          :    184980B4
tax               :    18498170
bigdata[3001024]  :    18498174
test              :    184E3174
samplenum         :    184E3178
sampleport[123]   :    184E317C
bigdata2[4001024] :    184E3368
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18547374
dwaddr            :    18592374
seq               :    18592378
buf[187]          :    1859237C
tax               :    18592438
bigdata[3001024]  :    1859243C
test              :    185DD43C
samplenum         :    185DD440
sampleport[123]   :    185DD444
bigdata2[4001024] :    185DD630
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1864163C
dwaddr            :    1868C63C
seq               :    1868C640
buf[187]          :    1868C644
tax               :    1868C700
bigdata[3001024]  :    1868C704
test              :    186D7704
samplenum         :    186D7708
sampleport[123]   :    186D770C
bigdata2[4001024] :    186D78F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1873B904
dwaddr            :    18786904
seq               :    18786908
buf[187]          :    1878690C
tax               :    187869C8
bigdata[3001024]  :    187869CC
test              :    187D19CC
samplenum         :    187D19D0
sampleport[123]   :    187D19D4
bigdata2[4001024] :    187D1BC0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18835BCC
dwaddr            :    18880BCC
seq               :    18880BD0
buf[187]          :    18880BD4
tax               :    18880C90
bigdata[3001024]  :    18880C94
test              :    188CBC94
samplenum         :    188CBC98
sampleport[123]   :    188CBC9C
bigdata2[4001024] :    188CBE88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1892FE94
dwaddr            :    1897AE94
seq               :    1897AE98
buf[187]          :    1897AE9C
tax               :    1897AF58
bigdata[3001024]  :    1897AF5C
test              :    189C5F5C
samplenum         :    189C5F60
sampleport[123]   :    189C5F64
bigdata2[4001024] :    189C6150
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18A2A15C
dwaddr            :    18A7515C
seq               :    18A75160
buf[187]          :    18A75164
tax               :    18A75220
bigdata[3001024]  :    18A75224
test              :    18AC0224
samplenum         :    18AC0228
sampleport[123]   :    18AC022C
bigdata2[4001024] :    18AC0418
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18B24424
dwaddr            :    18B6F424
seq               :    18B6F428
buf[187]          :    18B6F42C
tax               :    18B6F4E8
bigdata[3001024]  :    18B6F4EC
test              :    18BBA4EC
samplenum         :    18BBA4F0
sampleport[123]   :    18BBA4F4
bigdata2[4001024] :    18BBA6E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18C1E6EC
dwaddr            :    18C696EC
seq               :    18C696F0
buf[187]          :    18C696F4
tax               :    18C697B0
bigdata[3001024]  :    18C697B4
test              :    18CB47B4
samplenum         :    18CB47B8
sampleport[123]   :    18CB47BC
bigdata2[4001024] :    18CB49A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18D189B4
dwaddr            :    18D639B4
seq               :    18D639B8
buf[187]          :    18D639BC
tax               :    18D63A78
bigdata[3001024]  :    18D63A7C
test              :    18DAEA7C
samplenum         :    18DAEA80
sampleport[123]   :    18DAEA84
bigdata2[4001024] :    18DAEC70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18E12C7C
dwaddr            :    18E5DC7C
seq               :    18E5DC80
buf[187]          :    18E5DC84
tax               :    18E5DD40
bigdata[3001024]  :    18E5DD44
test              :    18EA8D44
samplenum         :    18EA8D48
sampleport[123]   :    18EA8D4C
bigdata2[4001024] :    18EA8F38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18F0CF44
dwaddr            :    18F57F44
seq               :    18F57F48
buf[187]          :    18F57F4C
tax               :    18F58008
bigdata[3001024]  :    18F5800C
test              :    18FA300C
samplenum         :    18FA3010
sampleport[123]   :    18FA3014
bigdata2[4001024] :    18FA3200
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1900720C
dwaddr            :    1905220C
seq               :    19052210
buf[187]          :    19052214
tax               :    190522D0
bigdata[3001024]  :    190522D4
test              :    1909D2D4
samplenum         :    1909D2D8
sampleport[123]   :    1909D2DC
bigdata2[4001024] :    1909D4C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191014D4
dwaddr            :    1914C4D4
seq               :    1914C4D8
buf[187]          :    1914C4DC
tax               :    1914C598
bigdata[3001024]  :    1914C59C
test              :    1919759C
samplenum         :    191975A0
sampleport[123]   :    191975A4
bigdata2[4001024] :    19197790
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191FB79C
dwaddr            :    1924679C
seq               :    192467A0
buf[187]          :    192467A4
tax               :    19246860
bigdata[3001024]  :    19246864
test              :    19291864
samplenum         :    19291868
sampleport[123]   :    1929186C
bigdata2[4001024] :    19291A58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    192F5A64
dwaddr            :    19340A64
seq               :    19340A68
buf[187]          :    19340A6C
tax               :    19340B28
bigdata[3001024]  :    19340B2C
test              :    1938BB2C
samplenum         :    1938BB30
sampleport[123]   :    1938BB34
bigdata2[4001024] :    1938BD20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    193EFD2C
dwaddr            :    1943AD2C
seq               :    1943AD30
buf[187]          :    1943AD34
tax               :    1943ADF0
bigdata[3001024]  :    1943ADF4
test              :    19485DF4
samplenum         :    19485DF8
sampleport[123]   :    19485DFC
bigdata2[4001024] :    19485FE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    194E9FF4
dwaddr            :    19534FF4
seq               :    19534FF8
buf[187]          :    19534FFC
tax               :    195350B8
bigdata[3001024]  :    195350BC
test              :    195800BC
samplenum         :    195800C0
sampleport[123]   :    195800C4
bigdata2[4001024] :    195802B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    195E42BC
dwaddr            :    1962F2BC
seq               :    1962F2C0
buf[187]          :    1962F2C4
tax               :    1962F380
bigdata[3001024]  :    1962F384
test              :    1967A384
samplenum         :    1967A388
sampleport[123]   :    1967A38C
bigdata2[4001024] :    1967A578
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    196DE584
dwaddr            :    19729584
seq               :    19729588
buf[187]          :    1972958C
tax               :    19729648
bigdata[3001024]  :    1972964C
test              :    1977464C
samplenum         :    19774650
sampleport[123]   :    19774654
bigdata2[4001024] :    19774840
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    197D884C
dwaddr            :    1982384C
seq               :    19823850
buf[187]          :    19823854
tax               :    19823910
bigdata[3001024]  :    19823914
test              :    1986E914
samplenum         :    1986E918
sampleport[123]   :    1986E91C
bigdata2[4001024] :    1986EB08
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    198D2B14
dwaddr            :    1991DB14
seq               :    1991DB18
buf[187]          :    1991DB1C
tax               :    1991DBD8
bigdata[3001024]  :    1991DBDC
test              :    19968BDC
samplenum         :    19968BE0
sampleport[123]   :    19968BE4
bigdata2[4001024] :    19968DD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    199CCDDC
dwaddr            :    19A17DDC
seq               :    19A17DE0
buf[187]          :    19A17DE4
tax               :    19A17EA0
bigdata[3001024]  :    19A17EA4
test              :    19A62EA4
samplenum         :    19A62EA8
sampleport[123]   :    19A62EAC
bigdata2[4001024] :    19A63098
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19AC70A4
dwaddr            :    19B120A4
seq               :    19B120A8
buf[187]          :    19B120AC
tax               :    19B12168
bigdata[3001024]  :    19B1216C
test              :    19B5D16C
samplenum         :    19B5D170
sampleport[123]   :    19B5D174
bigdata2[4001024] :    19B5D360
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19BC136C
dwaddr            :    19C0C36C
seq               :    19C0C370
buf[187]          :    19C0C374
tax               :    19C0C430
bigdata[3001024]  :    19C0C434
test              :    19C57434
samplenum         :    19C57438
sampleport[123]   :    19C5743C
bigdata2[4001024] :    19C57628
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19CBB634
dwaddr            :    19D06634
seq               :    19D06638
buf[187]          :    19D0663C
tax               :    19D066F8
bigdata[3001024]  :    19D066FC
test              :    19D516FC
samplenum         :    19D51700
sampleport[123]   :    19D51704
bigdata2[4001024] :    19D518F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19DB58FC
dwaddr            :    19E008FC
seq               :    19E00900
buf[187]          :    19E00904
tax               :    19E009C0
bigdata[3001024]  :    19E009C4
test              :    19E4B9C4
samplenum         :    19E4B9C8
sampleport[123]   :    19E4B9CC
bigdata2[4001024] :    19E4BBB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19EAFBC4
dwaddr            :    19EFABC4
seq               :    19EFABC8
buf[187]          :    19EFABCC
tax               :    19EFAC88
bigdata[3001024]  :    19EFAC8C
test              :    19F45C8C
samplenum         :    19F45C90
sampleport[123]   :    19F45C94
bigdata2[4001024] :    19F45E80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19FA9E8C
dwaddr            :    19FF4E8C
seq               :    19FF4E90
buf[187]          :    19FF4E94
tax               :    19FF4F50
bigdata[3001024]  :    19FF4F54
test              :    1A03FF54
samplenum         :    1A03FF58
sampleport[123]   :    1A03FF5C
bigdata2[4001024] :    1A040148
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A0A4154
dwaddr            :    1A0EF154
seq               :    1A0EF158
buf[187]          :    1A0EF15C
tax               :    1A0EF218
bigdata[3001024]  :    1A0EF21C
test              :    1A13A21C
samplenum         :    1A13A220
sampleport[123]   :    1A13A224
bigdata2[4001024] :    1A13A410
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A19E41C
dwaddr            :    1A1E941C
seq               :    1A1E9420
buf[187]          :    1A1E9424
tax               :    1A1E94E0
bigdata[3001024]  :    1A1E94E4
test              :    1A2344E4
samplenum         :    1A2344E8
sampleport[123]   :    1A2344EC
bigdata2[4001024] :    1A2346D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A2986E4
dwaddr            :    1A2E36E4
seq               :    1A2E36E8
buf[187]          :    1A2E36EC
tax               :    1A2E37A8
bigdata[3001024]  :    1A2E37AC
test              :    1A32E7AC
samplenum         :    1A32E7B0
sampleport[123]   :    1A32E7B4
bigdata2[4001024] :    1A32E9A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A3929AC
dwaddr            :    1A3DD9AC
seq               :    1A3DD9B0
buf[187]          :    1A3DD9B4
tax               :    1A3DDA70
bigdata[3001024]  :    1A3DDA74
test              :    1A428A74
samplenum         :    1A428A78
sampleport[123]   :    1A428A7C
bigdata2[4001024] :    1A428C68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A48CC74
dwaddr            :    1A4D7C74
seq               :    1A4D7C78
buf[187]          :    1A4D7C7C
tax               :    1A4D7D38
bigdata[3001024]  :    1A4D7D3C
test              :    1A522D3C
samplenum         :    1A522D40
sampleport[123]   :    1A522D44
bigdata2[4001024] :    1A522F30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A586F3C
dwaddr            :    1A5D1F3C
seq               :    1A5D1F40
buf[187]          :    1A5D1F44
tax               :    1A5D2000
bigdata[3001024]  :    1A5D2004
test              :    1A61D004
samplenum         :    1A61D008
sampleport[123]   :    1A61D00C
bigdata2[4001024] :    1A61D1F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A875794
dwaddr            :    1A8C0794
seq               :    1A8C0798
buf[187]          :    1A8C079C
tax               :    1A8C0858
bigdata[3001024]  :    1A8C085C
test              :    1A90B85C
samplenum         :    1A90B860
sampleport[123]   :    1A90B864
bigdata2[4001024] :    1A90BA50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A96FA5C
dwaddr            :    1A9BAA5C
seq               :    1A9BAA60
buf[187]          :    1A9BAA64
tax               :    1A9BAB20
bigdata[3001024]  :    1A9BAB24
test              :    1AA05B24
samplenum         :    1AA05B28
sampleport[123]   :    1AA05B2C
bigdata2[4001024] :    1AA05D18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1AF4CB0C
dwaddr            :    1AF97B0C
seq               :    1AF97B10
buf[187]          :    1AF97B14
tax               :    1AF97BD0
bigdata[3001024]  :    1AF97BD4
test              :    1AFE2BD4
samplenum         :    1AFE2BD8
sampleport[123]   :    1AFE2BDC
bigdata2[4001024] :    1AFE2DC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B42F8F4
dwaddr            :    1B47A8F4
seq               :    1B47A8F8
buf[187]          :    1B47A8FC
tax               :    1B47A9B8
bigdata[3001024]  :    1B47A9BC
test              :    1B4C59BC
samplenum         :    1B4C59C0
sampleport[123]   :    1B4C59C4
bigdata2[4001024] :    1B4C5BB0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B623E84
dwaddr            :    1B66EE84
seq               :    1B66EE88
buf[187]          :    1B66EE8C
tax               :    1B66EF48
bigdata[3001024]  :    1B66EF4C
test              :    1B6B9F4C
samplenum         :    1B6B9F50
sampleport[123]   :    1B6B9F54
bigdata2[4001024] :    1B6BA140
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B818414
dwaddr            :    1B863414
seq               :    1B863418
buf[187]          :    1B86341C
tax               :    1B8634D8
bigdata[3001024]  :    1B8634DC
test              :    1B8AE4DC
samplenum         :    1B8AE4E0
sampleport[123]   :    1B8AE4E4
bigdata2[4001024] :    1B8AE6D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BC00F34
dwaddr            :    1BC4BF34
seq               :    1BC4BF38
buf[187]          :    1BC4BF3C
tax               :    1BC4BFF8
bigdata[3001024]  :    1BC4BFFC
test              :    1BC96FFC
samplenum         :    1BC97000
sampleport[123]   :    1BC97004
bigdata2[4001024] :    1BC971F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BDF54C4
dwaddr            :    1BE404C4
seq               :    1BE404C8
buf[187]          :    1BE404CC
tax               :    1BE40588
bigdata[3001024]  :    1BE4058C
test              :    1BE8B58C
samplenum         :    1BE8B590
sampleport[123]   :    1BE8B594
bigdata2[4001024] :    1BE8B780
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BFE9A54
dwaddr            :    1C034A54
seq               :    1C034A58
buf[187]          :    1C034A5C
tax               :    1C034B18
bigdata[3001024]  :    1C034B1C
test              :    1C07FB1C
samplenum         :    1C07FB20
sampleport[123]   :    1C07FB24
bigdata2[4001024] :    1C07FD10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1C2D82AC
dwaddr            :    1C3232AC
seq               :    1C3232B0
buf[187]          :    1C3232B4
tax               :    1C323370
bigdata[3001024]  :    1C323374
test              :    1C36E374
samplenum         :    1C36E378
sampleport[123]   :    1C36E37C
bigdata2[4001024] :    1C36E568
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CE9240C
dwaddr            :    1CEDD40C
seq               :    1CEDD410
buf[187]          :    1CEDD414
tax               :    1CEDD4D0
bigdata[3001024]  :    1CEDD4D4
test              :    1CF284D4
samplenum         :    1CF284D8
sampleport[123]   :    1CF284DC
bigdata2[4001024] :    1CF286C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CF8C6D4
dwaddr            :    1CFD76D4
seq               :    1CFD76D8
buf[187]          :    1CFD76DC
tax               :    1CFD7798
bigdata[3001024]  :    1CFD779C
test              :    1D02279C
samplenum         :    1D0227A0
sampleport[123]   :    1D0227A4
bigdata2[4001024] :    1D022990
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D08699C
dwaddr            :    1D0D199C
seq               :    1D0D19A0
buf[187]          :    1D0D19A4
tax               :    1D0D1A60
bigdata[3001024]  :    1D0D1A64
test              :    1D11CA64
samplenum         :    1D11CA68
sampleport[123]   :    1D11CA6C
bigdata2[4001024] :    1D11CC58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D9522A4
dwaddr            :    1D99D2A4
seq               :    1D99D2A8
buf[187]          :    1D99D2AC
tax               :    1D99D368
bigdata[3001024]  :    1D99D36C
test              :    1D9E836C
samplenum         :    1D9E8370
sampleport[123]   :    1D9E8374
bigdata2[4001024] :    1D9E8560
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DB46834
dwaddr            :    1DB91834
seq               :    1DB91838
buf[187]          :    1DB9183C
tax               :    1DB918F8
bigdata[3001024]  :    1DB918FC
test              :    1DBDC8FC
samplenum         :    1DBDC900
sampleport[123]   :    1DBDC904
bigdata2[4001024] :    1DBDCAF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DC40AFC
dwaddr            :    1DC8BAFC
seq               :    1DC8BB00
buf[187]          :    1DC8BB04
tax               :    1DC8BBC0
bigdata[3001024]  :    1DC8BBC4
test              :    1DCD6BC4
samplenum         :    1DCD6BC8
sampleport[123]   :    1DCD6BCC
bigdata2[4001024] :    1DCD6DB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E21DBAC
dwaddr            :    1E268BAC
seq               :    1E268BB0
buf[187]          :    1E268BB4
tax               :    1E268C70
bigdata[3001024]  :    1E268C74
test              :    1E2B3C74
samplenum         :    1E2B3C78
sampleport[123]   :    1E2B3C7C
bigdata2[4001024] :    1E2B3E68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E50C404
dwaddr            :    1E557404
seq               :    1E557408
buf[187]          :    1E55740C
tax               :    1E5574C8
bigdata[3001024]  :    1E5574CC
test              :    1E5A24CC
samplenum         :    1E5A24D0
sampleport[123]   :    1E5A24D4
bigdata2[4001024] :    1E5A26C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E7FAC5C
dwaddr            :    1E845C5C
seq               :    1E845C60
buf[187]          :    1E845C64
tax               :    1E845D20
bigdata[3001024]  :    1E845D24
test              :    1E890D24
samplenum         :    1E890D28
sampleport[123]   :    1E890D2C
bigdata2[4001024] :    1E890F18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E9EF1EC
dwaddr            :    1EA3A1EC
seq               :    1EA3A1F0
buf[187]          :    1EA3A1F4
tax               :    1EA3A2B0
bigdata[3001024]  :    1EA3A2B4
test              :    1EA852B4
samplenum         :    1EA852B8
sampleport[123]   :    1EA852BC
bigdata2[4001024] :    1EA854A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1EDD7D0C
dwaddr            :    1EE22D0C
seq               :    1EE22D10
buf[187]          :    1EE22D14
tax               :    1EE22DD0
bigdata[3001024]  :    1EE22DD4
test              :    1EE6DDD4
samplenum         :    1EE6DDD8
sampleport[123]   :    1EE6DDDC
bigdata2[4001024] :    1EE6DFC8
hash show
No hash1    hash2     hash3    valueaddr
255 0x0        0x0        0x0        0x1f0c6564
254 0x0        0x0        0x0        0x1efcc29c
253 0x0        0x0        0x0        0x1eed1fd4
252 0x720752fc 0x2e6526c  0x7e325c42 0x1edd7d0c (data)
251 0x0        0x0        0x0        0x1ecdda44
250 0x0        0x0        0x0        0x1ebe377c
249 0x0        0x0        0x0        0x1eae94b4
248 0xdc63b7f8 0x2052961a 0x76f37377 0x1e9ef1ec (data)
247 0x0        0x0        0x0        0x1e8f4f24
246 0x81d59cf6 0xab7ebcba 0xe5b79834 0x1e7fac5c (data)
245 0x0        0x0        0x0        0x1e700994
244 0x0        0x0        0x0        0x1e6066cc
243 0x75571df3 0xda01101d 0x28af836d 0x1e50c404 (data)
242 0x0        0x0        0x0        0x1e41213c
241 0x0        0x0        0x0        0x1e317e74
240 0x1ae3f5f0 0x65b3d5b1 0x5e3d633b 0x1e21dbac (data)
239 0x0        0x0        0x0        0x1e1238e4
238 0x0        0x0        0x0        0x1e02961c
237 0x0        0x0        0x0        0x1df2f354
236 0x0        0x0        0x0        0x1de3508c
235 0x0        0x0        0x0        0x1dd3adc4
234 0x709391ea 0x4bf5a4ca 0xbb374f06 0x1dc40afc (data)
233 0xfc8524e9 0xaa4a697a 0x545895b0 0x1db46834 (data)
232 0x0        0x0        0x0        0x1da4c56c
231 0x10582ce7 0x73994279 0x1f213222 0x1d9522a4 (data)
230 0x0        0x0        0x0        0x1d857fdc
229 0x0        0x0        0x0        0x1d75dd14
228 0x0        0x0        0x0        0x1d663a4c
227 0x0        0x0        0x0        0x1d569784
226 0x0        0x0        0x0        0x1d46f4bc
225 0x0        0x0        0x0        0x1d3751f4
224 0x0        0x0        0x0        0x1d27af2c
223 0x0        0x0        0x0        0x1d180c64
222 0x8930f5de 0x34a9f12e 0x397bd808 0x1d08699c (data)
221 0x2a1252dd 0x1d31f9b4 0xbae26aeb 0x1cf8c6d4 (data)
220 0xd095adc  0x8a2f5df0 0x520d40e3 0x1ce9240c (data)
219 0x0        0x0        0x0        0x1cd98144
218 0x0        0x0        0x0        0x1cc9de7c
217 0x0        0x0        0x0        0x1cba3bb4
216 0x0        0x0        0x0        0x1caa98ec
215 0x0        0x0        0x0        0x1c9af624
214 0x0        0x0        0x0        0x1c8b535c
213 0x0        0x0        0x0        0x1c7bb094
212 0x0        0x0        0x0        0x1c6c0dcc
211 0x0        0x0        0x0        0x1c5c6b04
210 0x0        0x0        0x0        0x1c4cc83c
209 0x0        0x0        0x0        0x1c3d2574
208 0xefa929d0 0x8ae4dc74 0x55fa180e 0x1c2d82ac (data)
207 0x0        0x0        0x0        0x1c1ddfe4
206 0x0        0x0        0x0        0x1c0e3d1c
205 0xe492d7cd 0x9e4bdc50 0x293d4c00 0x1bfe9a54 (data)
204 0x0        0x0        0x0        0x1beef78c
203 0x7b283cb  0x9c05ca38 0x131111fa 0x1bdf54c4 (data)
202 0x0        0x0        0x0        0x1bcfb1fc
201 0x838b2cc9 0x228366e6 0x78678911 0x1bc00f34 (data)
200 0x0        0x0        0x0        0x1bb06c6c
199 0x0        0x0        0x0        0x1ba0c9a4
198 0x0        0x0        0x0        0x1b9126dc
197 0xeb6f8bc5 0x45d6e13b 0x5868b668 0x1b818414 (data)
196 0x0        0x0        0x0        0x1b71e14c
195 0x1cd7d2c3 0xb6a63bd7 0xe936128a 0x1b623e84 (data)
194 0x0        0x0        0x0        0x1b529bbc
193 0xdb545fc1 0xfdbae1c4 0xe462bdd9 0x1b42f8f4 (data)
192 0x0        0x0        0x0        0x1b33562c
191 0x0        0x0        0x0        0x1b23b364
190 0x0        0x0        0x0        0x1b14109c
189 0x0        0x0        0x0        0x1b046dd4
188 0xf3f152bc 0xcde66c2d 0x81235657 0x1af4cb0c (data)
187 0x0        0x0        0x0        0x1ae52844
186 0x0        0x0        0x0        0x1ad5857c
185 0x0        0x0        0x0        0x1ac5e2b4
184 0x0        0x0        0x0        0x1ab63fec
183 0x0        0x0        0x0        0x1aa69d24
182 0x2f178eb6 0xac5947d1 0x7650fa74 0x1a96fa5c (data)
181 0x8c3529b5 0x85c14f4b 0xf5c94897 0x1a875794 (data)
180 0x0        0x0        0x0        0x1a77b4cc
179 0x0        0x0        0x0        0x1a681204
178 0x2896c530 0xafce8752 0x7da85db0 0x1a586f3c (data)
177 0x8d7b3cb1 0x51d4ef6d 0x9b454e69 0x1a48cc74 (data)
176 0xbeb1a299 0xfb62a503 0xb84c2510 0x1a3929ac (data)
175 0x72170607 0xf90ada2c 0x7c7d785d 0x1a2986e4 (data)
174 0xb1c275ae 0x99233845 0x207b334b 0x1a19e41c (data)
173 0x4d58a456 0x26cadf84 0x150cb00b 0x1a0a4154 (data)
172 0x5ab20b7a 0xc95657c5 0x193c93d3 0x19fa9e8c (data)
171 0xd4307d6f 0x61fa6cd3 0x33565a21 0x19eafbc4 (data)
170 0xd832e831 0xe8a3671  0x6aed428e 0x19db58fc (data)
169 0x7d7324a9 0x654a573b 0xab499fa5 0x19cbb634 (data)
168 0x4dd62f69 0x9f167fa9 0xfc6e5c38 0x19bc136c (data)
167 0xdc13e557 0xdb5cb3e4 0xfdfc9355 0x19ac70a4 (data)
166 0x8ea1eaa3 0xccd2b9ed 0x30cc5bd3 0x199ccddc (data)
165 0x18f6dfa5 0x6370be42 0x7e27c351 0x198d2b14 (data)
164 0x18868d0a 0x987e9bbc 0xf5282373 0x197d884c (data)
163 0x499e0643 0xe9f8e2cb 0x189e1e6d 0x196de584 (data)
162 0xd4202994 0x9a16e493 0x31197e3e 0x195e42bc (data)
161 0x25ac57a1 0xba73d019 0x374cab6d 0x194e9ff4 (data)
160 0x2b75fa0  0x2d6d745d 0xdfa38165 0x193efd2c (data)
159 0xd7469e64 0x69263326 0xbf968169 0x192f5a64 (data)
158 0x42a2593c 0xf8ba7afe 0x29159fdf 0x191fb79c (data)
157 0xd3679302 0xbcf0b6b3 0x288750b2 0x191014d4 (data)
156 0x17f2fb5f 0xffd29eeb 0x2053e094 0x1900720c (data)
155 0x8933159b 0x273a720f 0x7fb50c3c 0x18f0cf44 (data)
154 0x46ea7016 0x8e54e79c 0xcde5dd8a 0x18e12c7c (data)
153 0xe41bfd90 0x227ae46c 0x8d13758f 0x18d189b4 (data)
152 0x4a44d051 0x74feb44b 0xb3170bd7 0x18c1e6ec (data)
151 0x10c51366 0x223ae935 0xb2c22e3a 0x18b24424 (data)
150 0x7f2d9496 0xecb78d67 0x36998e80 0x18a2a15c (data)
149 0x71761095 0xfd79588  0xbfbe52b6 0x1892fe94 (data)
148 0x2f8ab137 0xfdfaec9d 0xdbb3e66c 0x18835bcc (data)
147 0x38601e1b 0x126664dc 0xd783c5b4 0x1873b904 (data)
146 0xb6e2680e 0xbaca5fca 0xfde90c46 0x1864163c (data)
145 0x26009378 0x89ad2b56 0xe116565b 0x18547374 (data)
144 0xb3e45420 0x1831628e 0x779548ed 0x1844d0ac (data)
143 0x22219e1e 0x5c7baec3 0x76078780 0x18352de4 (data)
142 0xe6b4f643 0x1f59869b 0x7ed337a6 0x18258b1c (data)
141 0xb7ac7d0a 0x6edfffec 0x93650ab8 0x1815e854 (data)
140 0x155df08c 0xc2f1fc1c 0xd393a2bd 0x1806458c (data)
139 0x23054f13 0x38c59533 0x2da4c6c4 0x17f6a2c4 (data)
138 0xb6e1884b 0xa959dceb 0xbb27d872 0x17e6fffc (data)
137 0x27244275 0xed1310a6 0xbab5171f 0x17d75d34 (data)
136 0x75964d81 0xfa9d1aaf 0x7785df99 0x17c7ba6c (data)
135 0xe3b12a28 0xae3138fe 0xb261a739 0x17b817a4 (data)
134 0xb2a9a161 0xdfb74189 0x5fd79a27 0x17a874dc (data)
133 0x29be9604 0x2eef02fb 0x6cb897dd 0x1798d214 (data)
132 0xbc5a515c 0xbf734b23 0xfa3b896b 0x17892f4c (data)
131 0x2d9f9b62 0xfb39876e 0xfba94606 0x17798c84 (data)
130 0xe90af33f 0xb81baf36 0xf37df620 0x1769e9bc (data)
129 0xb8127876 0xc99dd641 0x1ecbcb3e 0x175a46f4 (data)
128 0x27e51207 0xcd8f1a14 0xe59f4beb 0x174aa42c (data)
127 0xe12e73ff 0x97244af4 0x9f157f4a 0x173b0164 (data)
126 0xd148c97d 0x1088d3da 0x255f91f0 0x172b5e9c (data)
125 0x806627d  0xeb04dbc8 0x77d1de10 0x171bbbd4 (data)
124 0xe0dafee7 0xe8a54132 0xcdcd0e55 0x170c190c (data)
123 0x7d64d130 0x9b4b476a 0xe44a6e06 0x16fc7644 (data)
122 0x422b7361 0x448b42c2 0x8d3ba650 0x16ecd37c (data)
121 0x55c1dc4d 0xab17ca83 0x810b8588 0x16dd30b4 (data)
120 0xfc445f78 0xc65842f9 0xd314c962 0x16cd8dec (data)
119 0xdb43aa58 0x3bbf195  0xab614c7a 0x16bdeb24 (data)
118 0x11fcac46 0x867c7e17 0xba9af00d 0x16ae485c (data)
117 0x9ab66bf5 0x61086ff2 0xad93b755 0x169ea594 (data)
116 0x84186b1e 0x17e037cf 0x2c19eebb 0x168f02cc (data)
115 0x15dda120 0x53aafb82 0x2d8b21d6 0x167f6004 (data)
114 0x5cad11f2 0xa134761b 0x14a57fb2 0x166fbd3c (data)
113 0x476faed4 0x4424f18b 0xe0bbe950 0x16601a74 (data)
112 0x80504234 0x610eaaad 0xc8e9acee 0x165077ac (data)
111 0x5e9560ef 0x295c5454 0x2df0c74d 0x1640d4e4 (data)
110 0x1dee6de3 0x12e0acf5 0xe16eccbd 0x1631321c (data)
109 0x22a1cfb2 0xcd20a95d 0x881f04eb 0x16218f54 (data)
108 0x354b609e 0x22bc211c 0x842f2733 0x1611ec8c (data)
107 0xbbc9168b 0x8a101a0a 0xae45eec1 0x160249c4 (data)
106 0xaad75dea 0x400cd65  0x8935d03f 0x15f2a6fc (data)
105 0x637c6c67 0x3cc45bde 0x96f97fc8 0x15e30434 (data)
104 0xd22f67e7 0x9984d0d  0x3ecfb640 0x15d3616c (data)
103 0xcc256967 0xa350e06e 0xf7b2ae08 0x15c3bea4 (data)
102 0xf698ab3f 0xad581206 0x7a617e   0x15b41bdc (data)
101 0xf2b9a659 0x788e9793 0x976bb0a5 0x15a47914 (data)
100 0xa00ba9ad 0x6f009d9a 0x5a5b7823 0x1594d64c (data)
99  0x362cce04 0x3bacbfcb 0x9fbf0083 0x15853384 (data)
98  0x6734454d 0x4a2ac6bc 0x72093d9d 0x157590bc (data)
97  0x2d88d761 0x954c35db 0x5b242207 0x1565edf4 (data)
96  0xfa8a6a9a 0x39c4c0e4 0x5b8e5dce 0x15564b2c (data)
95  0xc5c5c8cb 0xe604c54c 0x32ff9598 0x1546a864 (data)
94  0x3f339ab2 0x959c84bd 0x1fb6ce89 0x1537059c (data)
93  0xaef6508c 0xd1d648f0 0x1e2401e4 0x152762d4 (data)
92  0xc910c5c  0x35a44da3 0x6877cff5 0x1517c00c (data)
91  0x6a6338d1 0x92f460a8 0x16f0b1c2 0x15081d44 (data)
90  0x3b7bb398 0xe37219df 0xfb468cdc 0x14f87a7c (data)
89  0xa6c59c4f 0x909c1f87 0xd2c1ec8f 0x14e8d7b4 (data)
88  0x414a3d8  0x7f98092a 0x2c25e2a0 0x14d934ec (data)
87  0x998a3e1e 0x4f5c1a2f 0xbbb024d9 0x14c99224 (data)
86  0x77091456 0xc38868a5 0x5af107ea 0x14b9ef5c (data)
85  0x8e609132 0xa0c0926e 0xb7800701 0x14aa4c94 (data)
84  0xe2e727   0x86ca978  0x9deacef3 0x149aa9cc (data)
83  0x9de2a525 0x7a989210 0xe152c0a6 0x148b0704 (data)
82  0xc276f1b  0x3ed25e5d 0xe0c00fcb 0x147b643c (data)
81  0xc8b20746 0x7df07605 0xe814bfed 0x146bc174 (data)
80  0x99aa8c0f 0xc760f72  0x5a282f3  0x145c1eac (data)
79  0x3b5b0189 0xa0580c82 0x45542af6 0x144c7be4 (data)
78  0x2cb1aea5 0x4fc484c3 0x4964092e 0x143cd91c (data)
77  0xa233d8b0 0xe768bfd5 0x630ec0dc 0x142d3654 (data)
76  0x219a16c4 0x1d0e739  0xd01eb7   0x141d938c (data)
75  0xb47ed19c 0x904caee1 0x96530001 0x140df0c4 (data)
74  0x25bb1ba2 0xd40662ac 0x97c1cf6c 0x13fe4dfc (data)
73  0xb036f8b6 0xe6a23383 0x72a34254 0x13eeab34 (data)
72  0x12c77530 0x4a8c3073 0x3255ea51 0x13df086c (data)
71  0x52dda1c  0xa510b832 0x3e65c989 0x13cf65a4 (data)
70  0x8bafac09 0xdbc8324  0x140f007b 0x13bfc2dc (data)
69  0x59c1ae3f 0x32cca9b6 0x6131b0be 0x13b02014 (data)
68  0xc8046401 0x768665fb 0x60a37fd3 0x13a07d4c (data)
67  0x5d898715 0x442234d4 0x85c1f2eb 0x1390da84 (data)
66  0xc037a8c2 0x37cc328c 0xac4692b8 0x138137bc (data)
65  0xff780a93 0xe80c3724 0xc5375aee 0x137194f4 (data)
64  0xe892a5bf 0x790bf65  0xc9077936 0x1361f22c (data)
63  0x84432d3e 0xa2377f71 0x9573f4e4 0x13524f64 (data)
62  0x57e2613e 0x3d5bdf13 0xafb94c9e 0x1342ac9c (data)
61  0x6610d3aa 0xaf3c8473 0xe36db0c4 0x133309d4 (data)
60  0xdce2877c 0x82746140 0xb90df380 0x1323670c (data)
59  0xd2d02fac 0x606ff0ed 0xcf52edb9 0x1313c444 (data)
58  0x7e130afa 0x2e5a62b0 0xf9fb5b85 0x1304217c (data)
57  0xc1657d79 0xa817235b 0x968a0c73 0x12f47eb4 (data)
56  0x4734e8f4 0xf1f3b935 0x59d1f30f 0x12e4dbec (data)
55  0xd6f122ca 0xb5b97578 0x58433c62 0x12d53924 (data)
54  0x12644a97 0xf69b5d20 0x50978c44 0x12c5965c (data)
53  0xf667e374 0xc4afafe6 0xf1e73a87 0x12b5f394 (data)
52  0xfdd7dbf3 0x3137bb0e 0xbb665252 0x12a650cc (data)
51  0x2f0b81b3 0x5fdc1bc7 0x144d669b 0x1296ae04 (data)
50  0x437cc1de 0x871d2457 0xbd21b15a 0x12870b3c (data)
49  0xdec2ee09 0xf4f3220f 0x94a6d109 0x12776874 (data)
48  0xe18d4c58 0x2b3327a7 0xfdd7195f 0x1267c5ac (data)
47  0x78e59561 0x6c0394f0 0xdb8df375 0x125822e4 (data)
46  0xeb9ee9ee 0x1cfe339f 0x1c99d6bd 0x1248801c (data)
45  0xe3ad252d 0x5db464e8 0xd07c3bd6 0x1238dd54 (data)
44  0x68331cab 0xa0abf2d6 0x2de54ce4 0x12293a8c (data)
43  0xd960172b 0x95f7e405 0x85d3856c 0x121997c4 (data)
42  0xf9f6d695 0xe4e13e9b 0x2c778389 0x1209f4fc (data)
41  0xab44d961 0xf36f3492 0xe1474b0f 0x11fa5234 (data)
40  0x3d63bec8 0xa7c316c3 0x24a333af 0x11eaaf6c (data)
39  0x6c7b3581 0xd6456fb4 0xc9150eb1 0x11db0ca4 (data)
38  0xf1c51a56 0xa5ab69ec 0xe0926ee2 0x11cb69dc (data)
37  0xce8ab807 0x7a6b6c44 0x89e3a6b4 0x11bbc714 (data)
36  0xefbfe488 0xc928b60a 0x8b880766 0x11ac244c (data)
35  0x7a5b23d0 0x58b4ffd2 0x1d0b19d0 0x119c8184 (data)
34  0xb92ce61a 0xb703996  0xd1a91e3b 0x118cdebc (data)
33  0xcb082850 0x6de8e901 0xb53dd058 0x117d3bf4 (data)
32  0x458a5e45 0xc544d217 0x9f5719aa 0x116d992c (data)
31  0xebef2b7f 0x84216810 0xce639f7a 0x115df664 (data)
30  0x5481ba21 0x398b6a83 0x912c5    0x114e539c (data)
29  0xcd77bcdc 0x3c8bf1b9 0xcd7e30c3 0x113eb0d4 (data)
28  0xe3dce7bc 0xc56b3f67 0x2867211  0x112f0e0c (data)
27  0xc544701f 0x7dc1a6ce 0x19bdda8  0x111f6b44 (data)
26  0xe7fdeada 0x10bdbaf2 0x9597a3ca 0x110fc87c (data)
25  0x97f67feb 0x6a4facc7 0xccab152e 0x110025b4 (data)
24  0x1d11842  0x3ee38e96 0x94f6d8e  0x10f082ec (data)
23  0x50c9930b 0x4f65f7e1 0xe4f95090 0x10e0e024 (data)
22  0xf2381e8d 0xe34bf411 0xa40ff895 0x10d13d5c (data)
21  0xe5d2b1a1 0xcd77c50  0xa83fdb4d 0x10c19a94 (data)
20  0x6b50c7b4 0xa47b4746 0x825512bf 0x10b1f7cc (data)
19  0x72192d82 0x8121f32a 0x314bd7c  0x10a25504 (data)
18  0xb16ee848 0xd2e5356e 0xcfb6ba97 0x1092b23c (data)
17  0x27498fe1 0x8649173f 0xa52c237  0x10830f74 (data)
16  0x765104a8 0xf7cf6e48 0xe7e4ff29 0x10736cac (data)
15  0xc34a2602 0xb47de5f9 0xab2274f4 0x1063c9e4 (data)
14  0xe8ac5d2e 0x41f5cafc 0xeb290c03 0x1054271c (data)
13  0x4dc85017 0x1cd1deef 0x8148bd06 0x10448454 (data)
12  0xd77d20bb 0xdc05e739 0x69750c79 0x1034e18c (data)
11  0x662e2b3b 0xe959f1ea 0xc143c5f1 0x10253ec4 (data)
10  0xfb20fdea 0xbdc2258  0xf2bddd3a 0x10159bfc (data)
9   0x4299e7e3 0x4d99aee1 0xfff612cf 0x1005f934 (data)
8   0x822d82d8 0xdb6d032c 0x60337332 0xff6566c  (data)
7   0x71c48417 0x6c579ab  0xcd73e629 0xfe6b3a4  (data)
6   0x4e8b2646 0xd9057c03 0xa4022e7f 0xfd710dc  (data)
5   0x46b8ea85 0x984f2b74 0x68e7c314 0xfc76e14  (data)
4   0x6ae537d4 0x4f96ee15 0xf32f1257 0xfb7cb4c  (data)
3   0x140ae571 0x8fc1217d 0xa5d70b92 0xfa82884  (data)
2   0x6ec43ab2 0x9a406b80 0x643ec38c 0xf9885bc  (data)
1   0xd3350991 0xaaeb7a5b 0x8d854e2c 0xf88e2f4  (data)
0   0xd4a0892e 0x5be16db8 0xa712572c 0xf79402c  (data)
hash size:200
after update, hash size:200
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
remove ok, hash remove item!!!
hash key!!
No pInfo  dwaddr seq  tax  buf (iter)
1   0x1209f4fc 0x133  51  50.00  0x50
2   0x12293a8c 0x134  52  51.00  0x51
3   0x125822e4 0x136  54  53.00  0x53
4   0x1267c5ac 0x138  56  55.00  0x55
5   0x12776874 0x139  57  56.00  0x56
6   0x12870b3c 0x13a  58  57.00  0x57
7   0x12a650cc 0x135  53  52.00  0x52
8   0x12b5f394 0x137  55  54.00  0x54
9   0x12c5965c 0x13b  59  58.00  0x58
10  0x12d53924 0x13d  61  60.00  0x60
11  0x12e4dbec 0x13e  62  61.00  0x61
12  0x1313c444 0x13f  63  62.00  0x62
13  0x133309d4 0x140  64  63.00  0x63
14  0x13524f64 0x13c  60  59.00  0x59
15  0x1361f22c 0x141  65  64.00  0x64
16  0x137194f4 0x142  66  65.00  0x65
17  0x138137bc 0x143  67  66.00  0x66
18  0x1390da84 0x144  68  67.00  0x67
19  0x13a07d4c 0x147  71  70.00  0x70
20  0x13b02014 0x148  72  71.00  0x71
21  0x13bfc2dc 0x14a  74  73.00  0x73
22  0x13cf65a4 0x14b  75  74.00  0x74
23  0x13df086c 0x14c  76  75.00  0x75
24  0x13eeab34 0x14e  78  77.00  0x77
25  0x13fe4dfc 0x151  81  80.00  0x80
26  0x140df0c4 0x152  82  81.00  0x81
27  0x141d938c 0x153  83  82.00  0x82
28  0x142d3654 0x154  84  83.00  0x83
29  0x143cd91c 0x155  85  84.00  0x84
30  0x144c7be4 0x156  86  85.00  0x85
31  0x145c1eac 0x158  88  87.00  0x87
32  0x146bc174 0x159  89  88.00  0x88
33  0x147b643c 0x15b  91  90.00  0x90
34  0x148b0704 0x15c  92  91.00  0x91
35  0x149aa9cc 0x15e  94  93.00  0x93
36  0x14aa4c94 0x15f  95  94.00  0x94
37  0x14b9ef5c 0x150  80  79.00  0x79
38  0x14c99224 0x160  96  95.00  0x95
39  0x14d934ec 0x157  87  86.00  0x86
40  0x14e8d7b4 0x161  97  96.00  0x96
41  0x14f87a7c 0x162  98  97.00  0x97
42  0x15081d44 0x163  99  98.00  0x98
43  0x1517c00c 0x145  69  68.00  0x68
44  0x152762d4 0x165  101 100.00 0x100
45  0x1537059c 0x166  102 101.00 0x101
46  0x1546a864 0x16a  106 105.00 0x105
47  0x15564b2c 0x16b  107 106.00 0x106
48  0x1565edf4 0x14d  77  76.00  0x76
49  0x157590bc 0x16c  108 107.00 0x107
50  0x15853384 0x16d  109 108.00 0x108
51  0x1594d64c 0x16e  110 109.00 0x109
52  0x15a47914 0x16f  111 110.00 0x110
53  0x15b41bdc 0x171  113 112.00 0x112
54  0x15c3bea4 0x149  73  72.00  0x72
55  0x15d3616c 0x169  105 104.00 0x104
56  0x15e30434 0x170  112 111.00 0x111
57  0x15f2a6fc 0x167  103 102.00 0x102
58  0x160249c4 0x172  114 113.00 0x113
59  0x1611ec8c 0x173  115 114.00 0x114
60  0x16218f54 0x174  116 115.00 0x115
61  0x1631321c 0x175  117 116.00 0x116
62  0x1640d4e4 0x15a  90  89.00  0x89
63  0x165077ac 0x176  118 117.00 0x117
64  0x16601a74 0x178  120 119.00 0x119
65  0x166fbd3c 0x168  104 103.00 0x103
66  0x167f6004 0x179  121 120.00 0x120
67  0x168f02cc 0x17a  122 121.00 0x121
68  0x169ea594 0x146  70  69.00  0x69
69  0x16ae485c 0x17b  123 122.00 0x122
70  0x16bdeb24 0x17c  124 123.00 0x123
71  0x16cd8dec 0x164  100 99.00  0x99
72  0x16dd30b4 0x17d  125 124.00 0x124
73  0x16ecd37c 0x17e  126 125.00 0x125
74  0x16fc7644 0x17f  127 126.00 0x126
75  0x170c190c 0x180  128 127.00 0x127
76  0x171bbbd4 0x15d  93  92.00  0x92
77  0x172b5e9c 0x177  119 118.00 0x118
78  0x173b0164 0x14f  79  78.00  0x78
79  0x174aa42c 0x182  130 129.00 0x129
80  0x175a46f4 0x18a  138 137.00 0x137
81  0x1769e9bc 0x18b  139 138.00 0x138
82  0x17798c84 0x18d  141 140.00 0x140
83  0x17892f4c 0x18e  142 141.00 0x141
84  0x1798d214 0x18f  143 142.00 0x142
85  0x17a874dc 0x194  148 147.00 0x147
86  0x17b817a4 0x195  149 148.00 0x148
87  0x17c7ba6c 0x196  150 149.00 0x149
88  0x17d75d34 0x197  151 150.00 0x150
89  0x17e6fffc 0x198  152 151.00 0x151
90  0x17f6a2c4 0x199  153 152.00 0x152
91  0x1806458c 0x19c  156 155.00 0x155
92  0x1815e854 0x19e  158 157.00 0x157
93  0x18258b1c 0x19f  159 158.00 0x158
94  0x18352de4 0x1a1  161 160.00 0x160
95  0x1844d0ac 0x1a2  162 161.00 0x161
96  0x18547374 0x1a3  163 162.00 0x162
97  0x1864163c 0x1a4  164 163.00 0x163
98  0x1873b904 0x1a5  165 164.00 0x164
99  0x18835bcc 0x1a6  166 165.00 0x165
100 0x1892fe94 0x185  133 132.00 0x132
101 0x18a2a15c 0x18c  140 139.00 0x139
102 0x18b24424 0x1a7  167 166.00 0x166
103 0x18c1e6ec 0x1aa  170 169.00 0x169
104 0x18d189b4 0x1b0  176 175.00 0x175
105 0x18e12c7c 0x1b2  178 177.00 0x177
106 0x18f0cf44 0x1ac  172 171.00 0x171
107 0x1900720c 0x1b3  179 178.00 0x178
108 0x191014d4 0x1b5  181 180.00 0x180
109 0x191fb79c 0x1b6  182 181.00 0x181
110 0x192f5a64 0x1b7  183 182.00 0x182
111 0x193efd2c 0x19b  155 154.00 0x154
112 0x194e9ff4 0x189  137 136.00 0x136
113 0x195e42bc 0x1bb  187 186.00 0x186
114 0x196de584 0x1bc  188 187.00 0x187
115 0x197d884c 0x1bd  189 188.00 0x188
116 0x198d2b14 0x1ab  171 170.00 0x170
117 0x199ccddc 0x1be  190 189.00 0x189
118 0x19ac70a4 0x1bf  191 190.00 0x190
119 0x19bc136c 0x1c0  192 191.00 0x191
120 0x19cbb634 0x1ae  174 173.00 0x173
121 0x19db58fc 0x1c1  193 192.00 0x192
122 0x19eafbc4 0x1c2  194 193.00 0x193
123 0x19fa9e8c 0x1c3  195 194.00 0x194
124 0x1a0a4154 0x1c4  196 195.00 0x195
125 0x1a19e41c 0x181  129 128.00 0x128
126 0x1a2986e4 0x1c5  197 196.00 0x196
127 0x1a3929ac 0x1c7  199 198.00 0x198
128 0x1a48cc74 0x1a8  168 167.00 0x167
129 0x1a586f3c 0x1c8  200 199.00 0x199
130 0x1a875794 0x19a  154 153.00 0x153
131 0x1a96fa5c 0x193  147 146.00 0x146
132 0x1af4cb0c 0x1af  175 174.00 0x174
133 0x1b42f8f4 0x1b1  177 176.00 0x176
134 0x1b623e84 0x1ad  173 172.00 0x172
135 0x1b818414 0x1ba  186 185.00 0x185
136 0x1bc00f34 0x186  134 133.00 0x133
137 0x1bdf54c4 0x191  145 144.00 0x144
138 0x1bfe9a54 0x184  132 131.00 0x131
139 0x1c2d82ac 0x1c6  198 197.00 0x197
140 0x1ce9240c 0x187  135 134.00 0x134
141 0x1cf8c6d4 0x19d  157 156.00 0x156
142 0x1d08699c 0x190  144 143.00 0x143
143 0x1d9522a4 0x192  146 145.00 0x145
144 0x1db46834 0x1b9  185 184.00 0x184
145 0x1dc40afc 0x1a0  160 159.00 0x159
146 0x1e21dbac 0x188  136 135.00 0x135
147 0x1e50c404 0x183  131 130.00 0x130
148 0x1e7fac5c 0x1b4  180 179.00 0x179
149 0x1e9ef1ec 0x1a9  169 168.00 0x168
150 0x1edd7d0c 0x1b8  184 183.00 0x183

No pInfo  dwaddr seq  tax  buf (by GetHashItem)
1   0x1209f4fc 0x133  51  50.00  0x50
2   0x12293a8c 0x134  52  51.00  0x51
3   0x125822e4 0x136  54  53.00  0x53
4   0x1267c5ac 0x138  56  55.00  0x55
5   0x12776874 0x139  57  56.00  0x56
6   0x12870b3c 0x13a  58  57.00  0x57
7   0x12a650cc 0x135  53  52.00  0x52
8   0x12b5f394 0x137  55  54.00  0x54
9   0x12c5965c 0x13b  59  58.00  0x58
10  0x12d53924 0x13d  61  60.00  0x60
11  0x12e4dbec 0x13e  62  61.00  0x61
12  0x1313c444 0x13f  63  62.00  0x62
13  0x133309d4 0x140  64  63.00  0x63
14  0x13524f64 0x13c  60  59.00  0x59
15  0x1361f22c 0x141  65  64.00  0x64
16  0x137194f4 0x142  66  65.00  0x65
17  0x138137bc 0x143  67  66.00  0x66
18  0x1390da84 0x144  68  67.00  0x67
19  0x13a07d4c 0x147  71  70.00  0x70
20  0x13b02014 0x148  72  71.00  0x71
21  0x13bfc2dc 0x14a  74  73.00  0x73
22  0x13cf65a4 0x14b  75  74.00  0x74
23  0x13df086c 0x14c  76  75.00  0x75
24  0x13eeab34 0x14e  78  77.00  0x77
25  0x13fe4dfc 0x151  81  80.00  0x80
26  0x140df0c4 0x152  82  81.00  0x81
27  0x141d938c 0x153  83  82.00  0x82
28  0x142d3654 0x154  84  83.00  0x83
29  0x143cd91c 0x155  85  84.00  0x84
30  0x144c7be4 0x156  86  85.00  0x85
31  0x145c1eac 0x158  88  87.00  0x87
32  0x146bc174 0x159  89  88.00  0x88
33  0x147b643c 0x15b  91  90.00  0x90
34  0x148b0704 0x15c  92  91.00  0x91
35  0x149aa9cc 0x15e  94  93.00  0x93
36  0x14aa4c94 0x15f  95  94.00  0x94
37  0x14b9ef5c 0x150  80  79.00  0x79
38  0x14c99224 0x160  96  95.00  0x95
39  0x14d934ec 0x157  87  86.00  0x86
40  0x14e8d7b4 0x161  97  96.00  0x96
41  0x14f87a7c 0x162  98  97.00  0x97
42  0x15081d44 0x163  99  98.00  0x98
43  0x1517c00c 0x145  69  68.00  0x68
44  0x152762d4 0x165  101 100.00 0x100
45  0x1537059c 0x166  102 101.00 0x101
46  0x1546a864 0x16a  106 105.00 0x105
47  0x15564b2c 0x16b  107 106.00 0x106
48  0x1565edf4 0x14d  77  76.00  0x76
49  0x157590bc 0x16c  108 107.00 0x107
50  0x15853384 0x16d  109 108.00 0x108
51  0x1594d64c 0x16e  110 109.00 0x109
52  0x15a47914 0x16f  111 110.00 0x110
53  0x15b41bdc 0x171  113 112.00 0x112
54  0x15c3bea4 0x149  73  72.00  0x72
55  0x15d3616c 0x169  105 104.00 0x104
56  0x15e30434 0x170  112 111.00 0x111
57  0x15f2a6fc 0x167  103 102.00 0x102
58  0x160249c4 0x172  114 113.00 0x113
59  0x1611ec8c 0x173  115 114.00 0x114
60  0x16218f54 0x174  116 115.00 0x115
61  0x1631321c 0x175  117 116.00 0x116
62  0x1640d4e4 0x15a  90  89.00  0x89
63  0x165077ac 0x176  118 117.00 0x117
64  0x16601a74 0x178  120 119.00 0x119
65  0x166fbd3c 0x168  104 103.00 0x103
66  0x167f6004 0x179  121 120.00 0x120
67  0x168f02cc 0x17a  122 121.00 0x121
68  0x169ea594 0x146  70  69.00  0x69
69  0x16ae485c 0x17b  123 122.00 0x122
70  0x16bdeb24 0x17c  124 123.00 0x123
71  0x16cd8dec 0x164  100 99.00  0x99
72  0x16dd30b4 0x17d  125 124.00 0x124
73  0x16ecd37c 0x17e  126 125.00 0x125
74  0x16fc7644 0x17f  127 126.00 0x126
75  0x170c190c 0x180  128 127.00 0x127
76  0x171bbbd4 0x15d  93  92.00  0x92
77  0x172b5e9c 0x177  119 118.00 0x118
78  0x173b0164 0x14f  79  78.00  0x78
79  0x174aa42c 0x182  130 129.00 0x129
80  0x175a46f4 0x18a  138 137.00 0x137
81  0x1769e9bc 0x18b  139 138.00 0x138
82  0x17798c84 0x18d  141 140.00 0x140
83  0x17892f4c 0x18e  142 141.00 0x141
84  0x1798d214 0x18f  143 142.00 0x142
85  0x17a874dc 0x194  148 147.00 0x147
86  0x17b817a4 0x195  149 148.00 0x148
87  0x17c7ba6c 0x196  150 149.00 0x149
88  0x17d75d34 0x197  151 150.00 0x150
89  0x17e6fffc 0x198  152 151.00 0x151
90  0x17f6a2c4 0x199  153 152.00 0x152
91  0x1806458c 0x19c  156 155.00 0x155
92  0x1815e854 0x19e  158 157.00 0x157
93  0x18258b1c 0x19f  159 158.00 0x158
94  0x18352de4 0x1a1  161 160.00 0x160
95  0x1844d0ac 0x1a2  162 161.00 0x161
96  0x18547374 0x1a3  163 162.00 0x162
97  0x1864163c 0x1a4  164 163.00 0x163
98  0x1873b904 0x1a5  165 164.00 0x164
99  0x18835bcc 0x1a6  166 165.00 0x165
100 0x1892fe94 0x185  133 132.00 0x132
101 0x18a2a15c 0x18c  140 139.00 0x139
102 0x18b24424 0x1a7  167 166.00 0x166
103 0x18c1e6ec 0x1aa  170 169.00 0x169
104 0x18d189b4 0x1b0  176 175.00 0x175
105 0x18e12c7c 0x1b2  178 177.00 0x177
106 0x18f0cf44 0x1ac  172 171.00 0x171
107 0x1900720c 0x1b3  179 178.00 0x178
108 0x191014d4 0x1b5  181 180.00 0x180
109 0x191fb79c 0x1b6  182 181.00 0x181
110 0x192f5a64 0x1b7  183 182.00 0x182
111 0x193efd2c 0x19b  155 154.00 0x154
112 0x194e9ff4 0x189  137 136.00 0x136
113 0x195e42bc 0x1bb  187 186.00 0x186
114 0x196de584 0x1bc  188 187.00 0x187
115 0x197d884c 0x1bd  189 188.00 0x188
116 0x198d2b14 0x1ab  171 170.00 0x170
117 0x199ccddc 0x1be  190 189.00 0x189
118 0x19ac70a4 0x1bf  191 190.00 0x190
119 0x19bc136c 0x1c0  192 191.00 0x191
120 0x19cbb634 0x1ae  174 173.00 0x173
121 0x19db58fc 0x1c1  193 192.00 0x192
122 0x19eafbc4 0x1c2  194 193.00 0x193
123 0x19fa9e8c 0x1c3  195 194.00 0x194
124 0x1a0a4154 0x1c4  196 195.00 0x195
125 0x1a19e41c 0x181  129 128.00 0x128
126 0x1a2986e4 0x1c5  197 196.00 0x196
127 0x1a3929ac 0x1c7  199 198.00 0x198
128 0x1a48cc74 0x1a8  168 167.00 0x167
129 0x1a586f3c 0x1c8  200 199.00 0x199
130 0x1a875794 0x19a  154 153.00 0x153
131 0x1a96fa5c 0x193  147 146.00 0x146
132 0x1af4cb0c 0x1af  175 174.00 0x174
133 0x1b42f8f4 0x1b1  177 176.00 0x176
134 0x1b623e84 0x1ad  173 172.00 0x172
135 0x1b818414 0x1ba  186 185.00 0x185
136 0x1bc00f34 0x186  134 133.00 0x133
137 0x1bdf54c4 0x191  145 144.00 0x144
138 0x1bfe9a54 0x184  132 131.00 0x131
139 0x1c2d82ac 0x1c6  198 197.00 0x197
140 0x1ce9240c 0x187  135 134.00 0x134
141 0x1cf8c6d4 0x19d  157 156.00 0x156
142 0x1d08699c 0x190  144 143.00 0x143
143 0x1d9522a4 0x192  146 145.00 0x145
144 0x1db46834 0x1b9  185 184.00 0x184
145 0x1dc40afc 0x1a0  160 159.00 0x159
146 0x1e21dbac 0x188  136 135.00 0x135
147 0x1e50c404 0x183  131 130.00 0x130
148 0x1e7fac5c 0x1b4  180 179.00 0x179
149 0x1e9ef1ec 0x1a9  169 168.00 0x168
150 0x1edd7d0c 0x1b8  184 183.00 0x183
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1209F4FC
dwaddr            :    120EA4FC
seq               :    120EA500
buf[187]          :    120EA504
tax               :    120EA5C0
bigdata[3001024]  :    120EA5C4
test              :    121355C4
samplenum         :    121355C8
sampleport[123]   :    121355CC
bigdata2[4001024] :    121357B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12293A8C
dwaddr            :    122DEA8C
seq               :    122DEA90
buf[187]          :    122DEA94
tax               :    122DEB50
bigdata[3001024]  :    122DEB54
test              :    12329B54
samplenum         :    12329B58
sampleport[123]   :    12329B5C
bigdata2[4001024] :    12329D48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    125822E4
dwaddr            :    125CD2E4
seq               :    125CD2E8
buf[187]          :    125CD2EC
tax               :    125CD3A8
bigdata[3001024]  :    125CD3AC
test              :    126183AC
samplenum         :    126183B0
sampleport[123]   :    126183B4
bigdata2[4001024] :    126185A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1267C5AC
dwaddr            :    126C75AC
seq               :    126C75B0
buf[187]          :    126C75B4
tax               :    126C7670
bigdata[3001024]  :    126C7674
test              :    12712674
samplenum         :    12712678
sampleport[123]   :    1271267C
bigdata2[4001024] :    12712868
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12776874
dwaddr            :    127C1874
seq               :    127C1878
buf[187]          :    127C187C
tax               :    127C1938
bigdata[3001024]  :    127C193C
test              :    1280C93C
samplenum         :    1280C940
sampleport[123]   :    1280C944
bigdata2[4001024] :    1280CB30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12870B3C
dwaddr            :    128BBB3C
seq               :    128BBB40
buf[187]          :    128BBB44
tax               :    128BBC00
bigdata[3001024]  :    128BBC04
test              :    12906C04
samplenum         :    12906C08
sampleport[123]   :    12906C0C
bigdata2[4001024] :    12906DF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12A650CC
dwaddr            :    12AB00CC
seq               :    12AB00D0
buf[187]          :    12AB00D4
tax               :    12AB0190
bigdata[3001024]  :    12AB0194
test              :    12AFB194
samplenum         :    12AFB198
sampleport[123]   :    12AFB19C
bigdata2[4001024] :    12AFB388
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12B5F394
dwaddr            :    12BAA394
seq               :    12BAA398
buf[187]          :    12BAA39C
tax               :    12BAA458
bigdata[3001024]  :    12BAA45C
test              :    12BF545C
samplenum         :    12BF5460
sampleport[123]   :    12BF5464
bigdata2[4001024] :    12BF5650
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12C5965C
dwaddr            :    12CA465C
seq               :    12CA4660
buf[187]          :    12CA4664
tax               :    12CA4720
bigdata[3001024]  :    12CA4724
test              :    12CEF724
samplenum         :    12CEF728
sampleport[123]   :    12CEF72C
bigdata2[4001024] :    12CEF918
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12D53924
dwaddr            :    12D9E924
seq               :    12D9E928
buf[187]          :    12D9E92C
tax               :    12D9E9E8
bigdata[3001024]  :    12D9E9EC
test              :    12DE99EC
samplenum         :    12DE99F0
sampleport[123]   :    12DE99F4
bigdata2[4001024] :    12DE9BE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12E4DBEC
dwaddr            :    12E98BEC
seq               :    12E98BF0
buf[187]          :    12E98BF4
tax               :    12E98CB0
bigdata[3001024]  :    12E98CB4
test              :    12EE3CB4
samplenum         :    12EE3CB8
sampleport[123]   :    12EE3CBC
bigdata2[4001024] :    12EE3EA8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1313C444
dwaddr            :    13187444
seq               :    13187448
buf[187]          :    1318744C
tax               :    13187508
bigdata[3001024]  :    1318750C
test              :    131D250C
samplenum         :    131D2510
sampleport[123]   :    131D2514
bigdata2[4001024] :    131D2700
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    133309D4
dwaddr            :    1337B9D4
seq               :    1337B9D8
buf[187]          :    1337B9DC
tax               :    1337BA98
bigdata[3001024]  :    1337BA9C
test              :    133C6A9C
samplenum         :    133C6AA0
sampleport[123]   :    133C6AA4
bigdata2[4001024] :    133C6C90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13524F64
dwaddr            :    1356FF64
seq               :    1356FF68
buf[187]          :    1356FF6C
tax               :    13570028
bigdata[3001024]  :    1357002C
test              :    135BB02C
samplenum         :    135BB030
sampleport[123]   :    135BB034
bigdata2[4001024] :    135BB220
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1361F22C
dwaddr            :    1366A22C
seq               :    1366A230
buf[187]          :    1366A234
tax               :    1366A2F0
bigdata[3001024]  :    1366A2F4
test              :    136B52F4
samplenum         :    136B52F8
sampleport[123]   :    136B52FC
bigdata2[4001024] :    136B54E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    137194F4
dwaddr            :    137644F4
seq               :    137644F8
buf[187]          :    137644FC
tax               :    137645B8
bigdata[3001024]  :    137645BC
test              :    137AF5BC
samplenum         :    137AF5C0
sampleport[123]   :    137AF5C4
bigdata2[4001024] :    137AF7B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    138137BC
dwaddr            :    1385E7BC
seq               :    1385E7C0
buf[187]          :    1385E7C4
tax               :    1385E880
bigdata[3001024]  :    1385E884
test              :    138A9884
samplenum         :    138A9888
sampleport[123]   :    138A988C
bigdata2[4001024] :    138A9A78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1390DA84
dwaddr            :    13958A84
seq               :    13958A88
buf[187]          :    13958A8C
tax               :    13958B48
bigdata[3001024]  :    13958B4C
test              :    139A3B4C
samplenum         :    139A3B50
sampleport[123]   :    139A3B54
bigdata2[4001024] :    139A3D40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13A07D4C
dwaddr            :    13A52D4C
seq               :    13A52D50
buf[187]          :    13A52D54
tax               :    13A52E10
bigdata[3001024]  :    13A52E14
test              :    13A9DE14
samplenum         :    13A9DE18
sampleport[123]   :    13A9DE1C
bigdata2[4001024] :    13A9E008
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13B02014
dwaddr            :    13B4D014
seq               :    13B4D018
buf[187]          :    13B4D01C
tax               :    13B4D0D8
bigdata[3001024]  :    13B4D0DC
test              :    13B980DC
samplenum         :    13B980E0
sampleport[123]   :    13B980E4
bigdata2[4001024] :    13B982D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13BFC2DC
dwaddr            :    13C472DC
seq               :    13C472E0
buf[187]          :    13C472E4
tax               :    13C473A0
bigdata[3001024]  :    13C473A4
test              :    13C923A4
samplenum         :    13C923A8
sampleport[123]   :    13C923AC
bigdata2[4001024] :    13C92598
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13CF65A4
dwaddr            :    13D415A4
seq               :    13D415A8
buf[187]          :    13D415AC
tax               :    13D41668
bigdata[3001024]  :    13D4166C
test              :    13D8C66C
samplenum         :    13D8C670
sampleport[123]   :    13D8C674
bigdata2[4001024] :    13D8C860
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13DF086C
dwaddr            :    13E3B86C
seq               :    13E3B870
buf[187]          :    13E3B874
tax               :    13E3B930
bigdata[3001024]  :    13E3B934
test              :    13E86934
samplenum         :    13E86938
sampleport[123]   :    13E8693C
bigdata2[4001024] :    13E86B28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13EEAB34
dwaddr            :    13F35B34
seq               :    13F35B38
buf[187]          :    13F35B3C
tax               :    13F35BF8
bigdata[3001024]  :    13F35BFC
test              :    13F80BFC
samplenum         :    13F80C00
sampleport[123]   :    13F80C04
bigdata2[4001024] :    13F80DF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13FE4DFC
dwaddr            :    1402FDFC
seq               :    1402FE00
buf[187]          :    1402FE04
tax               :    1402FEC0
bigdata[3001024]  :    1402FEC4
test              :    1407AEC4
samplenum         :    1407AEC8
sampleport[123]   :    1407AECC
bigdata2[4001024] :    1407B0B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    140DF0C4
dwaddr            :    1412A0C4
seq               :    1412A0C8
buf[187]          :    1412A0CC
tax               :    1412A188
bigdata[3001024]  :    1412A18C
test              :    1417518C
samplenum         :    14175190
sampleport[123]   :    14175194
bigdata2[4001024] :    14175380
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    141D938C
dwaddr            :    1422438C
seq               :    14224390
buf[187]          :    14224394
tax               :    14224450
bigdata[3001024]  :    14224454
test              :    1426F454
samplenum         :    1426F458
sampleport[123]   :    1426F45C
bigdata2[4001024] :    1426F648
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    142D3654
dwaddr            :    1431E654
seq               :    1431E658
buf[187]          :    1431E65C
tax               :    1431E718
bigdata[3001024]  :    1431E71C
test              :    1436971C
samplenum         :    14369720
sampleport[123]   :    14369724
bigdata2[4001024] :    14369910
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    143CD91C
dwaddr            :    1441891C
seq               :    14418920
buf[187]          :    14418924
tax               :    144189E0
bigdata[3001024]  :    144189E4
test              :    144639E4
samplenum         :    144639E8
sampleport[123]   :    144639EC
bigdata2[4001024] :    14463BD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    144C7BE4
dwaddr            :    14512BE4
seq               :    14512BE8
buf[187]          :    14512BEC
tax               :    14512CA8
bigdata[3001024]  :    14512CAC
test              :    1455DCAC
samplenum         :    1455DCB0
sampleport[123]   :    1455DCB4
bigdata2[4001024] :    1455DEA0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    145C1EAC
dwaddr            :    1460CEAC
seq               :    1460CEB0
buf[187]          :    1460CEB4
tax               :    1460CF70
bigdata[3001024]  :    1460CF74
test              :    14657F74
samplenum         :    14657F78
sampleport[123]   :    14657F7C
bigdata2[4001024] :    14658168
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    146BC174
dwaddr            :    14707174
seq               :    14707178
buf[187]          :    1470717C
tax               :    14707238
bigdata[3001024]  :    1470723C
test              :    1475223C
samplenum         :    14752240
sampleport[123]   :    14752244
bigdata2[4001024] :    14752430
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    147B643C
dwaddr            :    1480143C
seq               :    14801440
buf[187]          :    14801444
tax               :    14801500
bigdata[3001024]  :    14801504
test              :    1484C504
samplenum         :    1484C508
sampleport[123]   :    1484C50C
bigdata2[4001024] :    1484C6F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    148B0704
dwaddr            :    148FB704
seq               :    148FB708
buf[187]          :    148FB70C
tax               :    148FB7C8
bigdata[3001024]  :    148FB7CC
test              :    149467CC
samplenum         :    149467D0
sampleport[123]   :    149467D4
bigdata2[4001024] :    149469C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    149AA9CC
dwaddr            :    149F59CC
seq               :    149F59D0
buf[187]          :    149F59D4
tax               :    149F5A90
bigdata[3001024]  :    149F5A94
test              :    14A40A94
samplenum         :    14A40A98
sampleport[123]   :    14A40A9C
bigdata2[4001024] :    14A40C88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14AA4C94
dwaddr            :    14AEFC94
seq               :    14AEFC98
buf[187]          :    14AEFC9C
tax               :    14AEFD58
bigdata[3001024]  :    14AEFD5C
test              :    14B3AD5C
samplenum         :    14B3AD60
sampleport[123]   :    14B3AD64
bigdata2[4001024] :    14B3AF50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14B9EF5C
dwaddr            :    14BE9F5C
seq               :    14BE9F60
buf[187]          :    14BE9F64
tax               :    14BEA020
bigdata[3001024]  :    14BEA024
test              :    14C35024
samplenum         :    14C35028
sampleport[123]   :    14C3502C
bigdata2[4001024] :    14C35218
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14C99224
dwaddr            :    14CE4224
seq               :    14CE4228
buf[187]          :    14CE422C
tax               :    14CE42E8
bigdata[3001024]  :    14CE42EC
test              :    14D2F2EC
samplenum         :    14D2F2F0
sampleport[123]   :    14D2F2F4
bigdata2[4001024] :    14D2F4E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14D934EC
dwaddr            :    14DDE4EC
seq               :    14DDE4F0
buf[187]          :    14DDE4F4
tax               :    14DDE5B0
bigdata[3001024]  :    14DDE5B4
test              :    14E295B4
samplenum         :    14E295B8
sampleport[123]   :    14E295BC
bigdata2[4001024] :    14E297A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14E8D7B4
dwaddr            :    14ED87B4
seq               :    14ED87B8
buf[187]          :    14ED87BC
tax               :    14ED8878
bigdata[3001024]  :    14ED887C
test              :    14F2387C
samplenum         :    14F23880
sampleport[123]   :    14F23884
bigdata2[4001024] :    14F23A70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14F87A7C
dwaddr            :    14FD2A7C
seq               :    14FD2A80
buf[187]          :    14FD2A84
tax               :    14FD2B40
bigdata[3001024]  :    14FD2B44
test              :    1501DB44
samplenum         :    1501DB48
sampleport[123]   :    1501DB4C
bigdata2[4001024] :    1501DD38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15081D44
dwaddr            :    150CCD44
seq               :    150CCD48
buf[187]          :    150CCD4C
tax               :    150CCE08
bigdata[3001024]  :    150CCE0C
test              :    15117E0C
samplenum         :    15117E10
sampleport[123]   :    15117E14
bigdata2[4001024] :    15118000
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1517C00C
dwaddr            :    151C700C
seq               :    151C7010
buf[187]          :    151C7014
tax               :    151C70D0
bigdata[3001024]  :    151C70D4
test              :    152120D4
samplenum         :    152120D8
sampleport[123]   :    152120DC
bigdata2[4001024] :    152122C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    152762D4
dwaddr            :    152C12D4
seq               :    152C12D8
buf[187]          :    152C12DC
tax               :    152C1398
bigdata[3001024]  :    152C139C
test              :    1530C39C
samplenum         :    1530C3A0
sampleport[123]   :    1530C3A4
bigdata2[4001024] :    1530C590
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1537059C
dwaddr            :    153BB59C
seq               :    153BB5A0
buf[187]          :    153BB5A4
tax               :    153BB660
bigdata[3001024]  :    153BB664
test              :    15406664
samplenum         :    15406668
sampleport[123]   :    1540666C
bigdata2[4001024] :    15406858
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1546A864
dwaddr            :    154B5864
seq               :    154B5868
buf[187]          :    154B586C
tax               :    154B5928
bigdata[3001024]  :    154B592C
test              :    1550092C
samplenum         :    15500930
sampleport[123]   :    15500934
bigdata2[4001024] :    15500B20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15564B2C
dwaddr            :    155AFB2C
seq               :    155AFB30
buf[187]          :    155AFB34
tax               :    155AFBF0
bigdata[3001024]  :    155AFBF4
test              :    155FABF4
samplenum         :    155FABF8
sampleport[123]   :    155FABFC
bigdata2[4001024] :    155FADE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1565EDF4
dwaddr            :    156A9DF4
seq               :    156A9DF8
buf[187]          :    156A9DFC
tax               :    156A9EB8
bigdata[3001024]  :    156A9EBC
test              :    156F4EBC
samplenum         :    156F4EC0
sampleport[123]   :    156F4EC4
bigdata2[4001024] :    156F50B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    157590BC
dwaddr            :    157A40BC
seq               :    157A40C0
buf[187]          :    157A40C4
tax               :    157A4180
bigdata[3001024]  :    157A4184
test              :    157EF184
samplenum         :    157EF188
sampleport[123]   :    157EF18C
bigdata2[4001024] :    157EF378
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15853384
dwaddr            :    1589E384
seq               :    1589E388
buf[187]          :    1589E38C
tax               :    1589E448
bigdata[3001024]  :    1589E44C
test              :    158E944C
samplenum         :    158E9450
sampleport[123]   :    158E9454
bigdata2[4001024] :    158E9640
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1594D64C
dwaddr            :    1599864C
seq               :    15998650
buf[187]          :    15998654
tax               :    15998710
bigdata[3001024]  :    15998714
test              :    159E3714
samplenum         :    159E3718
sampleport[123]   :    159E371C
bigdata2[4001024] :    159E3908
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15A47914
dwaddr            :    15A92914
seq               :    15A92918
buf[187]          :    15A9291C
tax               :    15A929D8
bigdata[3001024]  :    15A929DC
test              :    15ADD9DC
samplenum         :    15ADD9E0
sampleport[123]   :    15ADD9E4
bigdata2[4001024] :    15ADDBD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15B41BDC
dwaddr            :    15B8CBDC
seq               :    15B8CBE0
buf[187]          :    15B8CBE4
tax               :    15B8CCA0
bigdata[3001024]  :    15B8CCA4
test              :    15BD7CA4
samplenum         :    15BD7CA8
sampleport[123]   :    15BD7CAC
bigdata2[4001024] :    15BD7E98
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15C3BEA4
dwaddr            :    15C86EA4
seq               :    15C86EA8
buf[187]          :    15C86EAC
tax               :    15C86F68
bigdata[3001024]  :    15C86F6C
test              :    15CD1F6C
samplenum         :    15CD1F70
sampleport[123]   :    15CD1F74
bigdata2[4001024] :    15CD2160
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15D3616C
dwaddr            :    15D8116C
seq               :    15D81170
buf[187]          :    15D81174
tax               :    15D81230
bigdata[3001024]  :    15D81234
test              :    15DCC234
samplenum         :    15DCC238
sampleport[123]   :    15DCC23C
bigdata2[4001024] :    15DCC428
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15E30434
dwaddr            :    15E7B434
seq               :    15E7B438
buf[187]          :    15E7B43C
tax               :    15E7B4F8
bigdata[3001024]  :    15E7B4FC
test              :    15EC64FC
samplenum         :    15EC6500
sampleport[123]   :    15EC6504
bigdata2[4001024] :    15EC66F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15F2A6FC
dwaddr            :    15F756FC
seq               :    15F75700
buf[187]          :    15F75704
tax               :    15F757C0
bigdata[3001024]  :    15F757C4
test              :    15FC07C4
samplenum         :    15FC07C8
sampleport[123]   :    15FC07CC
bigdata2[4001024] :    15FC09B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    160249C4
dwaddr            :    1606F9C4
seq               :    1606F9C8
buf[187]          :    1606F9CC
tax               :    1606FA88
bigdata[3001024]  :    1606FA8C
test              :    160BAA8C
samplenum         :    160BAA90
sampleport[123]   :    160BAA94
bigdata2[4001024] :    160BAC80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1611EC8C
dwaddr            :    16169C8C
seq               :    16169C90
buf[187]          :    16169C94
tax               :    16169D50
bigdata[3001024]  :    16169D54
test              :    161B4D54
samplenum         :    161B4D58
sampleport[123]   :    161B4D5C
bigdata2[4001024] :    161B4F48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16218F54
dwaddr            :    16263F54
seq               :    16263F58
buf[187]          :    16263F5C
tax               :    16264018
bigdata[3001024]  :    1626401C
test              :    162AF01C
samplenum         :    162AF020
sampleport[123]   :    162AF024
bigdata2[4001024] :    162AF210
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1631321C
dwaddr            :    1635E21C
seq               :    1635E220
buf[187]          :    1635E224
tax               :    1635E2E0
bigdata[3001024]  :    1635E2E4
test              :    163A92E4
samplenum         :    163A92E8
sampleport[123]   :    163A92EC
bigdata2[4001024] :    163A94D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1640D4E4
dwaddr            :    164584E4
seq               :    164584E8
buf[187]          :    164584EC
tax               :    164585A8
bigdata[3001024]  :    164585AC
test              :    164A35AC
samplenum         :    164A35B0
sampleport[123]   :    164A35B4
bigdata2[4001024] :    164A37A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    165077AC
dwaddr            :    165527AC
seq               :    165527B0
buf[187]          :    165527B4
tax               :    16552870
bigdata[3001024]  :    16552874
test              :    1659D874
samplenum         :    1659D878
sampleport[123]   :    1659D87C
bigdata2[4001024] :    1659DA68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16601A74
dwaddr            :    1664CA74
seq               :    1664CA78
buf[187]          :    1664CA7C
tax               :    1664CB38
bigdata[3001024]  :    1664CB3C
test              :    16697B3C
samplenum         :    16697B40
sampleport[123]   :    16697B44
bigdata2[4001024] :    16697D30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    166FBD3C
dwaddr            :    16746D3C
seq               :    16746D40
buf[187]          :    16746D44
tax               :    16746E00
bigdata[3001024]  :    16746E04
test              :    16791E04
samplenum         :    16791E08
sampleport[123]   :    16791E0C
bigdata2[4001024] :    16791FF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    167F6004
dwaddr            :    16841004
seq               :    16841008
buf[187]          :    1684100C
tax               :    168410C8
bigdata[3001024]  :    168410CC
test              :    1688C0CC
samplenum         :    1688C0D0
sampleport[123]   :    1688C0D4
bigdata2[4001024] :    1688C2C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    168F02CC
dwaddr            :    1693B2CC
seq               :    1693B2D0
buf[187]          :    1693B2D4
tax               :    1693B390
bigdata[3001024]  :    1693B394
test              :    16986394
samplenum         :    16986398
sampleport[123]   :    1698639C
bigdata2[4001024] :    16986588
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    169EA594
dwaddr            :    16A35594
seq               :    16A35598
buf[187]          :    16A3559C
tax               :    16A35658
bigdata[3001024]  :    16A3565C
test              :    16A8065C
samplenum         :    16A80660
sampleport[123]   :    16A80664
bigdata2[4001024] :    16A80850
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16AE485C
dwaddr            :    16B2F85C
seq               :    16B2F860
buf[187]          :    16B2F864
tax               :    16B2F920
bigdata[3001024]  :    16B2F924
test              :    16B7A924
samplenum         :    16B7A928
sampleport[123]   :    16B7A92C
bigdata2[4001024] :    16B7AB18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16BDEB24
dwaddr            :    16C29B24
seq               :    16C29B28
buf[187]          :    16C29B2C
tax               :    16C29BE8
bigdata[3001024]  :    16C29BEC
test              :    16C74BEC
samplenum         :    16C74BF0
sampleport[123]   :    16C74BF4
bigdata2[4001024] :    16C74DE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16CD8DEC
dwaddr            :    16D23DEC
seq               :    16D23DF0
buf[187]          :    16D23DF4
tax               :    16D23EB0
bigdata[3001024]  :    16D23EB4
test              :    16D6EEB4
samplenum         :    16D6EEB8
sampleport[123]   :    16D6EEBC
bigdata2[4001024] :    16D6F0A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16DD30B4
dwaddr            :    16E1E0B4
seq               :    16E1E0B8
buf[187]          :    16E1E0BC
tax               :    16E1E178
bigdata[3001024]  :    16E1E17C
test              :    16E6917C
samplenum         :    16E69180
sampleport[123]   :    16E69184
bigdata2[4001024] :    16E69370
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16ECD37C
dwaddr            :    16F1837C
seq               :    16F18380
buf[187]          :    16F18384
tax               :    16F18440
bigdata[3001024]  :    16F18444
test              :    16F63444
samplenum         :    16F63448
sampleport[123]   :    16F6344C
bigdata2[4001024] :    16F63638
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16FC7644
dwaddr            :    17012644
seq               :    17012648
buf[187]          :    1701264C
tax               :    17012708
bigdata[3001024]  :    1701270C
test              :    1705D70C
samplenum         :    1705D710
sampleport[123]   :    1705D714
bigdata2[4001024] :    1705D900
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    170C190C
dwaddr            :    1710C90C
seq               :    1710C910
buf[187]          :    1710C914
tax               :    1710C9D0
bigdata[3001024]  :    1710C9D4
test              :    171579D4
samplenum         :    171579D8
sampleport[123]   :    171579DC
bigdata2[4001024] :    17157BC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    171BBBD4
dwaddr            :    17206BD4
seq               :    17206BD8
buf[187]          :    17206BDC
tax               :    17206C98
bigdata[3001024]  :    17206C9C
test              :    17251C9C
samplenum         :    17251CA0
sampleport[123]   :    17251CA4
bigdata2[4001024] :    17251E90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    172B5E9C
dwaddr            :    17300E9C
seq               :    17300EA0
buf[187]          :    17300EA4
tax               :    17300F60
bigdata[3001024]  :    17300F64
test              :    1734BF64
samplenum         :    1734BF68
sampleport[123]   :    1734BF6C
bigdata2[4001024] :    1734C158
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    173B0164
dwaddr            :    173FB164
seq               :    173FB168
buf[187]          :    173FB16C
tax               :    173FB228
bigdata[3001024]  :    173FB22C
test              :    1744622C
samplenum         :    17446230
sampleport[123]   :    17446234
bigdata2[4001024] :    17446420
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    174AA42C
dwaddr            :    174F542C
seq               :    174F5430
buf[187]          :    174F5434
tax               :    174F54F0
bigdata[3001024]  :    174F54F4
test              :    175404F4
samplenum         :    175404F8
sampleport[123]   :    175404FC
bigdata2[4001024] :    175406E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    175A46F4
dwaddr            :    175EF6F4
seq               :    175EF6F8
buf[187]          :    175EF6FC
tax               :    175EF7B8
bigdata[3001024]  :    175EF7BC
test              :    1763A7BC
samplenum         :    1763A7C0
sampleport[123]   :    1763A7C4
bigdata2[4001024] :    1763A9B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1769E9BC
dwaddr            :    176E99BC
seq               :    176E99C0
buf[187]          :    176E99C4
tax               :    176E9A80
bigdata[3001024]  :    176E9A84
test              :    17734A84
samplenum         :    17734A88
sampleport[123]   :    17734A8C
bigdata2[4001024] :    17734C78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17798C84
dwaddr            :    177E3C84
seq               :    177E3C88
buf[187]          :    177E3C8C
tax               :    177E3D48
bigdata[3001024]  :    177E3D4C
test              :    1782ED4C
samplenum         :    1782ED50
sampleport[123]   :    1782ED54
bigdata2[4001024] :    1782EF40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17892F4C
dwaddr            :    178DDF4C
seq               :    178DDF50
buf[187]          :    178DDF54
tax               :    178DE010
bigdata[3001024]  :    178DE014
test              :    17929014
samplenum         :    17929018
sampleport[123]   :    1792901C
bigdata2[4001024] :    17929208
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1798D214
dwaddr            :    179D8214
seq               :    179D8218
buf[187]          :    179D821C
tax               :    179D82D8
bigdata[3001024]  :    179D82DC
test              :    17A232DC
samplenum         :    17A232E0
sampleport[123]   :    17A232E4
bigdata2[4001024] :    17A234D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17A874DC
dwaddr            :    17AD24DC
seq               :    17AD24E0
buf[187]          :    17AD24E4
tax               :    17AD25A0
bigdata[3001024]  :    17AD25A4
test              :    17B1D5A4
samplenum         :    17B1D5A8
sampleport[123]   :    17B1D5AC
bigdata2[4001024] :    17B1D798
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17B817A4
dwaddr            :    17BCC7A4
seq               :    17BCC7A8
buf[187]          :    17BCC7AC
tax               :    17BCC868
bigdata[3001024]  :    17BCC86C
test              :    17C1786C
samplenum         :    17C17870
sampleport[123]   :    17C17874
bigdata2[4001024] :    17C17A60
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17C7BA6C
dwaddr            :    17CC6A6C
seq               :    17CC6A70
buf[187]          :    17CC6A74
tax               :    17CC6B30
bigdata[3001024]  :    17CC6B34
test              :    17D11B34
samplenum         :    17D11B38
sampleport[123]   :    17D11B3C
bigdata2[4001024] :    17D11D28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17D75D34
dwaddr            :    17DC0D34
seq               :    17DC0D38
buf[187]          :    17DC0D3C
tax               :    17DC0DF8
bigdata[3001024]  :    17DC0DFC
test              :    17E0BDFC
samplenum         :    17E0BE00
sampleport[123]   :    17E0BE04
bigdata2[4001024] :    17E0BFF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17E6FFFC
dwaddr            :    17EBAFFC
seq               :    17EBB000
buf[187]          :    17EBB004
tax               :    17EBB0C0
bigdata[3001024]  :    17EBB0C4
test              :    17F060C4
samplenum         :    17F060C8
sampleport[123]   :    17F060CC
bigdata2[4001024] :    17F062B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17F6A2C4
dwaddr            :    17FB52C4
seq               :    17FB52C8
buf[187]          :    17FB52CC
tax               :    17FB5388
bigdata[3001024]  :    17FB538C
test              :    1800038C
samplenum         :    18000390
sampleport[123]   :    18000394
bigdata2[4001024] :    18000580
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1806458C
dwaddr            :    180AF58C
seq               :    180AF590
buf[187]          :    180AF594
tax               :    180AF650
bigdata[3001024]  :    180AF654
test              :    180FA654
samplenum         :    180FA658
sampleport[123]   :    180FA65C
bigdata2[4001024] :    180FA848
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1815E854
dwaddr            :    181A9854
seq               :    181A9858
buf[187]          :    181A985C
tax               :    181A9918
bigdata[3001024]  :    181A991C
test              :    181F491C
samplenum         :    181F4920
sampleport[123]   :    181F4924
bigdata2[4001024] :    181F4B10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18258B1C
dwaddr            :    182A3B1C
seq               :    182A3B20
buf[187]          :    182A3B24
tax               :    182A3BE0
bigdata[3001024]  :    182A3BE4
test              :    182EEBE4
samplenum         :    182EEBE8
sampleport[123]   :    182EEBEC
bigdata2[4001024] :    182EEDD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18352DE4
dwaddr            :    1839DDE4
seq               :    1839DDE8
buf[187]          :    1839DDEC
tax               :    1839DEA8
bigdata[3001024]  :    1839DEAC
test              :    183E8EAC
samplenum         :    183E8EB0
sampleport[123]   :    183E8EB4
bigdata2[4001024] :    183E90A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1844D0AC
dwaddr            :    184980AC
seq               :    184980B0
buf[187]          :    184980B4
tax               :    18498170
bigdata[3001024]  :    18498174
test              :    184E3174
samplenum         :    184E3178
sampleport[123]   :    184E317C
bigdata2[4001024] :    184E3368
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18547374
dwaddr            :    18592374
seq               :    18592378
buf[187]          :    1859237C
tax               :    18592438
bigdata[3001024]  :    1859243C
test              :    185DD43C
samplenum         :    185DD440
sampleport[123]   :    185DD444
bigdata2[4001024] :    185DD630
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1864163C
dwaddr            :    1868C63C
seq               :    1868C640
buf[187]          :    1868C644
tax               :    1868C700
bigdata[3001024]  :    1868C704
test              :    186D7704
samplenum         :    186D7708
sampleport[123]   :    186D770C
bigdata2[4001024] :    186D78F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1873B904
dwaddr            :    18786904
seq               :    18786908
buf[187]          :    1878690C
tax               :    187869C8
bigdata[3001024]  :    187869CC
test              :    187D19CC
samplenum         :    187D19D0
sampleport[123]   :    187D19D4
bigdata2[4001024] :    187D1BC0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18835BCC
dwaddr            :    18880BCC
seq               :    18880BD0
buf[187]          :    18880BD4
tax               :    18880C90
bigdata[3001024]  :    18880C94
test              :    188CBC94
samplenum         :    188CBC98
sampleport[123]   :    188CBC9C
bigdata2[4001024] :    188CBE88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1892FE94
dwaddr            :    1897AE94
seq               :    1897AE98
buf[187]          :    1897AE9C
tax               :    1897AF58
bigdata[3001024]  :    1897AF5C
test              :    189C5F5C
samplenum         :    189C5F60
sampleport[123]   :    189C5F64
bigdata2[4001024] :    189C6150
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18A2A15C
dwaddr            :    18A7515C
seq               :    18A75160
buf[187]          :    18A75164
tax               :    18A75220
bigdata[3001024]  :    18A75224
test              :    18AC0224
samplenum         :    18AC0228
sampleport[123]   :    18AC022C
bigdata2[4001024] :    18AC0418
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18B24424
dwaddr            :    18B6F424
seq               :    18B6F428
buf[187]          :    18B6F42C
tax               :    18B6F4E8
bigdata[3001024]  :    18B6F4EC
test              :    18BBA4EC
samplenum         :    18BBA4F0
sampleport[123]   :    18BBA4F4
bigdata2[4001024] :    18BBA6E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18C1E6EC
dwaddr            :    18C696EC
seq               :    18C696F0
buf[187]          :    18C696F4
tax               :    18C697B0
bigdata[3001024]  :    18C697B4
test              :    18CB47B4
samplenum         :    18CB47B8
sampleport[123]   :    18CB47BC
bigdata2[4001024] :    18CB49A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18D189B4
dwaddr            :    18D639B4
seq               :    18D639B8
buf[187]          :    18D639BC
tax               :    18D63A78
bigdata[3001024]  :    18D63A7C
test              :    18DAEA7C
samplenum         :    18DAEA80
sampleport[123]   :    18DAEA84
bigdata2[4001024] :    18DAEC70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18E12C7C
dwaddr            :    18E5DC7C
seq               :    18E5DC80
buf[187]          :    18E5DC84
tax               :    18E5DD40
bigdata[3001024]  :    18E5DD44
test              :    18EA8D44
samplenum         :    18EA8D48
sampleport[123]   :    18EA8D4C
bigdata2[4001024] :    18EA8F38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18F0CF44
dwaddr            :    18F57F44
seq               :    18F57F48
buf[187]          :    18F57F4C
tax               :    18F58008
bigdata[3001024]  :    18F5800C
test              :    18FA300C
samplenum         :    18FA3010
sampleport[123]   :    18FA3014
bigdata2[4001024] :    18FA3200
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1900720C
dwaddr            :    1905220C
seq               :    19052210
buf[187]          :    19052214
tax               :    190522D0
bigdata[3001024]  :    190522D4
test              :    1909D2D4
samplenum         :    1909D2D8
sampleport[123]   :    1909D2DC
bigdata2[4001024] :    1909D4C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191014D4
dwaddr            :    1914C4D4
seq               :    1914C4D8
buf[187]          :    1914C4DC
tax               :    1914C598
bigdata[3001024]  :    1914C59C
test              :    1919759C
samplenum         :    191975A0
sampleport[123]   :    191975A4
bigdata2[4001024] :    19197790
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191FB79C
dwaddr            :    1924679C
seq               :    192467A0
buf[187]          :    192467A4
tax               :    19246860
bigdata[3001024]  :    19246864
test              :    19291864
samplenum         :    19291868
sampleport[123]   :    1929186C
bigdata2[4001024] :    19291A58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    192F5A64
dwaddr            :    19340A64
seq               :    19340A68
buf[187]          :    19340A6C
tax               :    19340B28
bigdata[3001024]  :    19340B2C
test              :    1938BB2C
samplenum         :    1938BB30
sampleport[123]   :    1938BB34
bigdata2[4001024] :    1938BD20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    193EFD2C
dwaddr            :    1943AD2C
seq               :    1943AD30
buf[187]          :    1943AD34
tax               :    1943ADF0
bigdata[3001024]  :    1943ADF4
test              :    19485DF4
samplenum         :    19485DF8
sampleport[123]   :    19485DFC
bigdata2[4001024] :    19485FE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    194E9FF4
dwaddr            :    19534FF4
seq               :    19534FF8
buf[187]          :    19534FFC
tax               :    195350B8
bigdata[3001024]  :    195350BC
test              :    195800BC
samplenum         :    195800C0
sampleport[123]   :    195800C4
bigdata2[4001024] :    195802B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    195E42BC
dwaddr            :    1962F2BC
seq               :    1962F2C0
buf[187]          :    1962F2C4
tax               :    1962F380
bigdata[3001024]  :    1962F384
test              :    1967A384
samplenum         :    1967A388
sampleport[123]   :    1967A38C
bigdata2[4001024] :    1967A578
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    196DE584
dwaddr            :    19729584
seq               :    19729588
buf[187]          :    1972958C
tax               :    19729648
bigdata[3001024]  :    1972964C
test              :    1977464C
samplenum         :    19774650
sampleport[123]   :    19774654
bigdata2[4001024] :    19774840
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    197D884C
dwaddr            :    1982384C
seq               :    19823850
buf[187]          :    19823854
tax               :    19823910
bigdata[3001024]  :    19823914
test              :    1986E914
samplenum         :    1986E918
sampleport[123]   :    1986E91C
bigdata2[4001024] :    1986EB08
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    198D2B14
dwaddr            :    1991DB14
seq               :    1991DB18
buf[187]          :    1991DB1C
tax               :    1991DBD8
bigdata[3001024]  :    1991DBDC
test              :    19968BDC
samplenum         :    19968BE0
sampleport[123]   :    19968BE4
bigdata2[4001024] :    19968DD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    199CCDDC
dwaddr            :    19A17DDC
seq               :    19A17DE0
buf[187]          :    19A17DE4
tax               :    19A17EA0
bigdata[3001024]  :    19A17EA4
test              :    19A62EA4
samplenum         :    19A62EA8
sampleport[123]   :    19A62EAC
bigdata2[4001024] :    19A63098
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19AC70A4
dwaddr            :    19B120A4
seq               :    19B120A8
buf[187]          :    19B120AC
tax               :    19B12168
bigdata[3001024]  :    19B1216C
test              :    19B5D16C
samplenum         :    19B5D170
sampleport[123]   :    19B5D174
bigdata2[4001024] :    19B5D360
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19BC136C
dwaddr            :    19C0C36C
seq               :    19C0C370
buf[187]          :    19C0C374
tax               :    19C0C430
bigdata[3001024]  :    19C0C434
test              :    19C57434
samplenum         :    19C57438
sampleport[123]   :    19C5743C
bigdata2[4001024] :    19C57628
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19CBB634
dwaddr            :    19D06634
seq               :    19D06638
buf[187]          :    19D0663C
tax               :    19D066F8
bigdata[3001024]  :    19D066FC
test              :    19D516FC
samplenum         :    19D51700
sampleport[123]   :    19D51704
bigdata2[4001024] :    19D518F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19DB58FC
dwaddr            :    19E008FC
seq               :    19E00900
buf[187]          :    19E00904
tax               :    19E009C0
bigdata[3001024]  :    19E009C4
test              :    19E4B9C4
samplenum         :    19E4B9C8
sampleport[123]   :    19E4B9CC
bigdata2[4001024] :    19E4BBB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19EAFBC4
dwaddr            :    19EFABC4
seq               :    19EFABC8
buf[187]          :    19EFABCC
tax               :    19EFAC88
bigdata[3001024]  :    19EFAC8C
test              :    19F45C8C
samplenum         :    19F45C90
sampleport[123]   :    19F45C94
bigdata2[4001024] :    19F45E80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19FA9E8C
dwaddr            :    19FF4E8C
seq               :    19FF4E90
buf[187]          :    19FF4E94
tax               :    19FF4F50
bigdata[3001024]  :    19FF4F54
test              :    1A03FF54
samplenum         :    1A03FF58
sampleport[123]   :    1A03FF5C
bigdata2[4001024] :    1A040148
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A0A4154
dwaddr            :    1A0EF154
seq               :    1A0EF158
buf[187]          :    1A0EF15C
tax               :    1A0EF218
bigdata[3001024]  :    1A0EF21C
test              :    1A13A21C
samplenum         :    1A13A220
sampleport[123]   :    1A13A224
bigdata2[4001024] :    1A13A410
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A19E41C
dwaddr            :    1A1E941C
seq               :    1A1E9420
buf[187]          :    1A1E9424
tax               :    1A1E94E0
bigdata[3001024]  :    1A1E94E4
test              :    1A2344E4
samplenum         :    1A2344E8
sampleport[123]   :    1A2344EC
bigdata2[4001024] :    1A2346D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A2986E4
dwaddr            :    1A2E36E4
seq               :    1A2E36E8
buf[187]          :    1A2E36EC
tax               :    1A2E37A8
bigdata[3001024]  :    1A2E37AC
test              :    1A32E7AC
samplenum         :    1A32E7B0
sampleport[123]   :    1A32E7B4
bigdata2[4001024] :    1A32E9A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A3929AC
dwaddr            :    1A3DD9AC
seq               :    1A3DD9B0
buf[187]          :    1A3DD9B4
tax               :    1A3DDA70
bigdata[3001024]  :    1A3DDA74
test              :    1A428A74
samplenum         :    1A428A78
sampleport[123]   :    1A428A7C
bigdata2[4001024] :    1A428C68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A48CC74
dwaddr            :    1A4D7C74
seq               :    1A4D7C78
buf[187]          :    1A4D7C7C
tax               :    1A4D7D38
bigdata[3001024]  :    1A4D7D3C
test              :    1A522D3C
samplenum         :    1A522D40
sampleport[123]   :    1A522D44
bigdata2[4001024] :    1A522F30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A586F3C
dwaddr            :    1A5D1F3C
seq               :    1A5D1F40
buf[187]          :    1A5D1F44
tax               :    1A5D2000
bigdata[3001024]  :    1A5D2004
test              :    1A61D004
samplenum         :    1A61D008
sampleport[123]   :    1A61D00C
bigdata2[4001024] :    1A61D1F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A875794
dwaddr            :    1A8C0794
seq               :    1A8C0798
buf[187]          :    1A8C079C
tax               :    1A8C0858
bigdata[3001024]  :    1A8C085C
test              :    1A90B85C
samplenum         :    1A90B860
sampleport[123]   :    1A90B864
bigdata2[4001024] :    1A90BA50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A96FA5C
dwaddr            :    1A9BAA5C
seq               :    1A9BAA60
buf[187]          :    1A9BAA64
tax               :    1A9BAB20
bigdata[3001024]  :    1A9BAB24
test              :    1AA05B24
samplenum         :    1AA05B28
sampleport[123]   :    1AA05B2C
bigdata2[4001024] :    1AA05D18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1AF4CB0C
dwaddr            :    1AF97B0C
seq               :    1AF97B10
buf[187]          :    1AF97B14
tax               :    1AF97BD0
bigdata[3001024]  :    1AF97BD4
test              :    1AFE2BD4
samplenum         :    1AFE2BD8
sampleport[123]   :    1AFE2BDC
bigdata2[4001024] :    1AFE2DC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B42F8F4
dwaddr            :    1B47A8F4
seq               :    1B47A8F8
buf[187]          :    1B47A8FC
tax               :    1B47A9B8
bigdata[3001024]  :    1B47A9BC
test              :    1B4C59BC
samplenum         :    1B4C59C0
sampleport[123]   :    1B4C59C4
bigdata2[4001024] :    1B4C5BB0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B623E84
dwaddr            :    1B66EE84
seq               :    1B66EE88
buf[187]          :    1B66EE8C
tax               :    1B66EF48
bigdata[3001024]  :    1B66EF4C
test              :    1B6B9F4C
samplenum         :    1B6B9F50
sampleport[123]   :    1B6B9F54
bigdata2[4001024] :    1B6BA140
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B818414
dwaddr            :    1B863414
seq               :    1B863418
buf[187]          :    1B86341C
tax               :    1B8634D8
bigdata[3001024]  :    1B8634DC
test              :    1B8AE4DC
samplenum         :    1B8AE4E0
sampleport[123]   :    1B8AE4E4
bigdata2[4001024] :    1B8AE6D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BC00F34
dwaddr            :    1BC4BF34
seq               :    1BC4BF38
buf[187]          :    1BC4BF3C
tax               :    1BC4BFF8
bigdata[3001024]  :    1BC4BFFC
test              :    1BC96FFC
samplenum         :    1BC97000
sampleport[123]   :    1BC97004
bigdata2[4001024] :    1BC971F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BDF54C4
dwaddr            :    1BE404C4
seq               :    1BE404C8
buf[187]          :    1BE404CC
tax               :    1BE40588
bigdata[3001024]  :    1BE4058C
test              :    1BE8B58C
samplenum         :    1BE8B590
sampleport[123]   :    1BE8B594
bigdata2[4001024] :    1BE8B780
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BFE9A54
dwaddr            :    1C034A54
seq               :    1C034A58
buf[187]          :    1C034A5C
tax               :    1C034B18
bigdata[3001024]  :    1C034B1C
test              :    1C07FB1C
samplenum         :    1C07FB20
sampleport[123]   :    1C07FB24
bigdata2[4001024] :    1C07FD10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1C2D82AC
dwaddr            :    1C3232AC
seq               :    1C3232B0
buf[187]          :    1C3232B4
tax               :    1C323370
bigdata[3001024]  :    1C323374
test              :    1C36E374
samplenum         :    1C36E378
sampleport[123]   :    1C36E37C
bigdata2[4001024] :    1C36E568
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CE9240C
dwaddr            :    1CEDD40C
seq               :    1CEDD410
buf[187]          :    1CEDD414
tax               :    1CEDD4D0
bigdata[3001024]  :    1CEDD4D4
test              :    1CF284D4
samplenum         :    1CF284D8
sampleport[123]   :    1CF284DC
bigdata2[4001024] :    1CF286C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CF8C6D4
dwaddr            :    1CFD76D4
seq               :    1CFD76D8
buf[187]          :    1CFD76DC
tax               :    1CFD7798
bigdata[3001024]  :    1CFD779C
test              :    1D02279C
samplenum         :    1D0227A0
sampleport[123]   :    1D0227A4
bigdata2[4001024] :    1D022990
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D08699C
dwaddr            :    1D0D199C
seq               :    1D0D19A0
buf[187]          :    1D0D19A4
tax               :    1D0D1A60
bigdata[3001024]  :    1D0D1A64
test              :    1D11CA64
samplenum         :    1D11CA68
sampleport[123]   :    1D11CA6C
bigdata2[4001024] :    1D11CC58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D9522A4
dwaddr            :    1D99D2A4
seq               :    1D99D2A8
buf[187]          :    1D99D2AC
tax               :    1D99D368
bigdata[3001024]  :    1D99D36C
test              :    1D9E836C
samplenum         :    1D9E8370
sampleport[123]   :    1D9E8374
bigdata2[4001024] :    1D9E8560
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DB46834
dwaddr            :    1DB91834
seq               :    1DB91838
buf[187]          :    1DB9183C
tax               :    1DB918F8
bigdata[3001024]  :    1DB918FC
test              :    1DBDC8FC
samplenum         :    1DBDC900
sampleport[123]   :    1DBDC904
bigdata2[4001024] :    1DBDCAF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DC40AFC
dwaddr            :    1DC8BAFC
seq               :    1DC8BB00
buf[187]          :    1DC8BB04
tax               :    1DC8BBC0
bigdata[3001024]  :    1DC8BBC4
test              :    1DCD6BC4
samplenum         :    1DCD6BC8
sampleport[123]   :    1DCD6BCC
bigdata2[4001024] :    1DCD6DB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E21DBAC
dwaddr            :    1E268BAC
seq               :    1E268BB0
buf[187]          :    1E268BB4
tax               :    1E268C70
bigdata[3001024]  :    1E268C74
test              :    1E2B3C74
samplenum         :    1E2B3C78
sampleport[123]   :    1E2B3C7C
bigdata2[4001024] :    1E2B3E68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E50C404
dwaddr            :    1E557404
seq               :    1E557408
buf[187]          :    1E55740C
tax               :    1E5574C8
bigdata[3001024]  :    1E5574CC
test              :    1E5A24CC
samplenum         :    1E5A24D0
sampleport[123]   :    1E5A24D4
bigdata2[4001024] :    1E5A26C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E7FAC5C
dwaddr            :    1E845C5C
seq               :    1E845C60
buf[187]          :    1E845C64
tax               :    1E845D20
bigdata[3001024]  :    1E845D24
test              :    1E890D24
samplenum         :    1E890D28
sampleport[123]   :    1E890D2C
bigdata2[4001024] :    1E890F18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E9EF1EC
dwaddr            :    1EA3A1EC
seq               :    1EA3A1F0
buf[187]          :    1EA3A1F4
tax               :    1EA3A2B0
bigdata[3001024]  :    1EA3A2B4
test              :    1EA852B4
samplenum         :    1EA852B8
sampleport[123]   :    1EA852BC
bigdata2[4001024] :    1EA854A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1EDD7D0C
dwaddr            :    1EE22D0C
seq               :    1EE22D10
buf[187]          :    1EE22D14
tax               :    1EE22DD0
bigdata[3001024]  :    1EE22DD4
test              :    1EE6DDD4
samplenum         :    1EE6DDD8
sampleport[123]   :    1EE6DDDC
bigdata2[4001024] :    1EE6DFC8
hash show
No hash1    hash2     hash3    valueaddr
255 0x0        0x0        0x0        0x1f0c6564
254 0x0        0x0        0x0        0x1efcc29c
253 0x0        0x0        0x0        0x1eed1fd4
252 0x720752fc 0x2e6526c  0x7e325c42 0x1edd7d0c (data)
251 0x0        0x0        0x0        0x1ecdda44
250 0x0        0x0        0x0        0x1ebe377c
249 0x0        0x0        0x0        0x1eae94b4
248 0xdc63b7f8 0x2052961a 0x76f37377 0x1e9ef1ec (data)
247 0x0        0x0        0x0        0x1e8f4f24
246 0x81d59cf6 0xab7ebcba 0xe5b79834 0x1e7fac5c (data)
245 0x0        0x0        0x0        0x1e700994
244 0x0        0x0        0x0        0x1e6066cc
243 0x75571df3 0xda01101d 0x28af836d 0x1e50c404 (data)
242 0x0        0x0        0x0        0x1e41213c
241 0x0        0x0        0x0        0x1e317e74
240 0x1ae3f5f0 0x65b3d5b1 0x5e3d633b 0x1e21dbac (data)
239 0x0        0x0        0x0        0x1e1238e4
238 0x0        0x0        0x0        0x1e02961c
237 0x0        0x0        0x0        0x1df2f354
236 0x0        0x0        0x0        0x1de3508c
235 0x0        0x0        0x0        0x1dd3adc4
234 0x709391ea 0x4bf5a4ca 0xbb374f06 0x1dc40afc (data)
233 0xfc8524e9 0xaa4a697a 0x545895b0 0x1db46834 (data)
232 0x0        0x0        0x0        0x1da4c56c
231 0x10582ce7 0x73994279 0x1f213222 0x1d9522a4 (data)
230 0x0        0x0        0x0        0x1d857fdc
229 0x0        0x0        0x0        0x1d75dd14
228 0x0        0x0        0x0        0x1d663a4c
227 0x0        0x0        0x0        0x1d569784
226 0x0        0x0        0x0        0x1d46f4bc
225 0x0        0x0        0x0        0x1d3751f4
224 0x0        0x0        0x0        0x1d27af2c
223 0x0        0x0        0x0        0x1d180c64
222 0x8930f5de 0x34a9f12e 0x397bd808 0x1d08699c (data)
221 0x2a1252dd 0x1d31f9b4 0xbae26aeb 0x1cf8c6d4 (data)
220 0xd095adc  0x8a2f5df0 0x520d40e3 0x1ce9240c (data)
219 0x0        0x0        0x0        0x1cd98144
218 0x0        0x0        0x0        0x1cc9de7c
217 0x0        0x0        0x0        0x1cba3bb4
216 0x0        0x0        0x0        0x1caa98ec
215 0x0        0x0        0x0        0x1c9af624
214 0x0        0x0        0x0        0x1c8b535c
213 0x0        0x0        0x0        0x1c7bb094
212 0x0        0x0        0x0        0x1c6c0dcc
211 0x0        0x0        0x0        0x1c5c6b04
210 0x0        0x0        0x0        0x1c4cc83c
209 0x0        0x0        0x0        0x1c3d2574
208 0xefa929d0 0x8ae4dc74 0x55fa180e 0x1c2d82ac (data)
207 0x0        0x0        0x0        0x1c1ddfe4
206 0x0        0x0        0x0        0x1c0e3d1c
205 0xe492d7cd 0x9e4bdc50 0x293d4c00 0x1bfe9a54 (data)
204 0x0        0x0        0x0        0x1beef78c
203 0x7b283cb  0x9c05ca38 0x131111fa 0x1bdf54c4 (data)
202 0x0        0x0        0x0        0x1bcfb1fc
201 0x838b2cc9 0x228366e6 0x78678911 0x1bc00f34 (data)
200 0x0        0x0        0x0        0x1bb06c6c
199 0x0        0x0        0x0        0x1ba0c9a4
198 0x0        0x0        0x0        0x1b9126dc
197 0xeb6f8bc5 0x45d6e13b 0x5868b668 0x1b818414 (data)
196 0x0        0x0        0x0        0x1b71e14c
195 0x1cd7d2c3 0xb6a63bd7 0xe936128a 0x1b623e84 (data)
194 0x0        0x0        0x0        0x1b529bbc
193 0xdb545fc1 0xfdbae1c4 0xe462bdd9 0x1b42f8f4 (data)
192 0x0        0x0        0x0        0x1b33562c
191 0x0        0x0        0x0        0x1b23b364
190 0x0        0x0        0x0        0x1b14109c
189 0x0        0x0        0x0        0x1b046dd4
188 0xf3f152bc 0xcde66c2d 0x81235657 0x1af4cb0c (data)
187 0x0        0x0        0x0        0x1ae52844
186 0x0        0x0        0x0        0x1ad5857c
185 0x0        0x0        0x0        0x1ac5e2b4
184 0x0        0x0        0x0        0x1ab63fec
183 0x0        0x0        0x0        0x1aa69d24
182 0x2f178eb6 0xac5947d1 0x7650fa74 0x1a96fa5c (data)
181 0x8c3529b5 0x85c14f4b 0xf5c94897 0x1a875794 (data)
180 0x0        0x0        0x0        0x1a77b4cc
179 0x0        0x0        0x0        0x1a681204
178 0x2896c530 0xafce8752 0x7da85db0 0x1a586f3c (data)
177 0x8d7b3cb1 0x51d4ef6d 0x9b454e69 0x1a48cc74 (data)
176 0xbeb1a299 0xfb62a503 0xb84c2510 0x1a3929ac (data)
175 0x72170607 0xf90ada2c 0x7c7d785d 0x1a2986e4 (data)
174 0xb1c275ae 0x99233845 0x207b334b 0x1a19e41c (data)
173 0x4d58a456 0x26cadf84 0x150cb00b 0x1a0a4154 (data)
172 0x5ab20b7a 0xc95657c5 0x193c93d3 0x19fa9e8c (data)
171 0xd4307d6f 0x61fa6cd3 0x33565a21 0x19eafbc4 (data)
170 0xd832e831 0xe8a3671  0x6aed428e 0x19db58fc (data)
169 0x7d7324a9 0x654a573b 0xab499fa5 0x19cbb634 (data)
168 0x4dd62f69 0x9f167fa9 0xfc6e5c38 0x19bc136c (data)
167 0xdc13e557 0xdb5cb3e4 0xfdfc9355 0x19ac70a4 (data)
166 0x8ea1eaa3 0xccd2b9ed 0x30cc5bd3 0x199ccddc (data)
165 0x18f6dfa5 0x6370be42 0x7e27c351 0x198d2b14 (data)
164 0x18868d0a 0x987e9bbc 0xf5282373 0x197d884c (data)
163 0x499e0643 0xe9f8e2cb 0x189e1e6d 0x196de584 (data)
162 0xd4202994 0x9a16e493 0x31197e3e 0x195e42bc (data)
161 0x25ac57a1 0xba73d019 0x374cab6d 0x194e9ff4 (data)
160 0x2b75fa0  0x2d6d745d 0xdfa38165 0x193efd2c (data)
159 0xd7469e64 0x69263326 0xbf968169 0x192f5a64 (data)
158 0x42a2593c 0xf8ba7afe 0x29159fdf 0x191fb79c (data)
157 0xd3679302 0xbcf0b6b3 0x288750b2 0x191014d4 (data)
156 0x17f2fb5f 0xffd29eeb 0x2053e094 0x1900720c (data)
155 0x8933159b 0x273a720f 0x7fb50c3c 0x18f0cf44 (data)
154 0x46ea7016 0x8e54e79c 0xcde5dd8a 0x18e12c7c (data)
153 0xe41bfd90 0x227ae46c 0x8d13758f 0x18d189b4 (data)
152 0x4a44d051 0x74feb44b 0xb3170bd7 0x18c1e6ec (data)
151 0x10c51366 0x223ae935 0xb2c22e3a 0x18b24424 (data)
150 0x7f2d9496 0xecb78d67 0x36998e80 0x18a2a15c (data)
149 0x71761095 0xfd79588  0xbfbe52b6 0x1892fe94 (data)
148 0x2f8ab137 0xfdfaec9d 0xdbb3e66c 0x18835bcc (data)
147 0x38601e1b 0x126664dc 0xd783c5b4 0x1873b904 (data)
146 0xb6e2680e 0xbaca5fca 0xfde90c46 0x1864163c (data)
145 0x26009378 0x89ad2b56 0xe116565b 0x18547374 (data)
144 0xb3e45420 0x1831628e 0x779548ed 0x1844d0ac (data)
143 0x22219e1e 0x5c7baec3 0x76078780 0x18352de4 (data)
142 0xe6b4f643 0x1f59869b 0x7ed337a6 0x18258b1c (data)
141 0xb7ac7d0a 0x6edfffec 0x93650ab8 0x1815e854 (data)
140 0x155df08c 0xc2f1fc1c 0xd393a2bd 0x1806458c (data)
139 0x23054f13 0x38c59533 0x2da4c6c4 0x17f6a2c4 (data)
138 0xb6e1884b 0xa959dceb 0xbb27d872 0x17e6fffc (data)
137 0x27244275 0xed1310a6 0xbab5171f 0x17d75d34 (data)
136 0x75964d81 0xfa9d1aaf 0x7785df99 0x17c7ba6c (data)
135 0xe3b12a28 0xae3138fe 0xb261a739 0x17b817a4 (data)
134 0xb2a9a161 0xdfb74189 0x5fd79a27 0x17a874dc (data)
133 0x29be9604 0x2eef02fb 0x6cb897dd 0x1798d214 (data)
132 0xbc5a515c 0xbf734b23 0xfa3b896b 0x17892f4c (data)
131 0x2d9f9b62 0xfb39876e 0xfba94606 0x17798c84 (data)
130 0xe90af33f 0xb81baf36 0xf37df620 0x1769e9bc (data)
129 0xb8127876 0xc99dd641 0x1ecbcb3e 0x175a46f4 (data)
128 0x27e51207 0xcd8f1a14 0xe59f4beb 0x174aa42c (data)
127 0xe12e73ff 0x97244af4 0x9f157f4a 0x173b0164 (data)
126 0xd148c97d 0x1088d3da 0x255f91f0 0x172b5e9c (data)
125 0x806627d  0xeb04dbc8 0x77d1de10 0x171bbbd4 (data)
124 0xe0dafee7 0xe8a54132 0xcdcd0e55 0x170c190c (data)
123 0x7d64d130 0x9b4b476a 0xe44a6e06 0x16fc7644 (data)
122 0x422b7361 0x448b42c2 0x8d3ba650 0x16ecd37c (data)
121 0x55c1dc4d 0xab17ca83 0x810b8588 0x16dd30b4 (data)
120 0xfc445f78 0xc65842f9 0xd314c962 0x16cd8dec (data)
119 0xdb43aa58 0x3bbf195  0xab614c7a 0x16bdeb24 (data)
118 0x11fcac46 0x867c7e17 0xba9af00d 0x16ae485c (data)
117 0x9ab66bf5 0x61086ff2 0xad93b755 0x169ea594 (data)
116 0x84186b1e 0x17e037cf 0x2c19eebb 0x168f02cc (data)
115 0x15dda120 0x53aafb82 0x2d8b21d6 0x167f6004 (data)
114 0x5cad11f2 0xa134761b 0x14a57fb2 0x166fbd3c (data)
113 0x476faed4 0x4424f18b 0xe0bbe950 0x16601a74 (data)
112 0x80504234 0x610eaaad 0xc8e9acee 0x165077ac (data)
111 0x5e9560ef 0x295c5454 0x2df0c74d 0x1640d4e4 (data)
110 0x1dee6de3 0x12e0acf5 0xe16eccbd 0x1631321c (data)
109 0x22a1cfb2 0xcd20a95d 0x881f04eb 0x16218f54 (data)
108 0x354b609e 0x22bc211c 0x842f2733 0x1611ec8c (data)
107 0xbbc9168b 0x8a101a0a 0xae45eec1 0x160249c4 (data)
106 0xaad75dea 0x400cd65  0x8935d03f 0x15f2a6fc (data)
105 0x637c6c67 0x3cc45bde 0x96f97fc8 0x15e30434 (data)
104 0xd22f67e7 0x9984d0d  0x3ecfb640 0x15d3616c (data)
103 0xcc256967 0xa350e06e 0xf7b2ae08 0x15c3bea4 (data)
102 0xf698ab3f 0xad581206 0x7a617e   0x15b41bdc (data)
101 0xf2b9a659 0x788e9793 0x976bb0a5 0x15a47914 (data)
100 0xa00ba9ad 0x6f009d9a 0x5a5b7823 0x1594d64c (data)
99  0x362cce04 0x3bacbfcb 0x9fbf0083 0x15853384 (data)
98  0x6734454d 0x4a2ac6bc 0x72093d9d 0x157590bc (data)
97  0x2d88d761 0x954c35db 0x5b242207 0x1565edf4 (data)
96  0xfa8a6a9a 0x39c4c0e4 0x5b8e5dce 0x15564b2c (data)
95  0xc5c5c8cb 0xe604c54c 0x32ff9598 0x1546a864 (data)
94  0x3f339ab2 0x959c84bd 0x1fb6ce89 0x1537059c (data)
93  0xaef6508c 0xd1d648f0 0x1e2401e4 0x152762d4 (data)
92  0xc910c5c  0x35a44da3 0x6877cff5 0x1517c00c (data)
91  0x6a6338d1 0x92f460a8 0x16f0b1c2 0x15081d44 (data)
90  0x3b7bb398 0xe37219df 0xfb468cdc 0x14f87a7c (data)
89  0xa6c59c4f 0x909c1f87 0xd2c1ec8f 0x14e8d7b4 (data)
88  0x414a3d8  0x7f98092a 0x2c25e2a0 0x14d934ec (data)
87  0x998a3e1e 0x4f5c1a2f 0xbbb024d9 0x14c99224 (data)
86  0x77091456 0xc38868a5 0x5af107ea 0x14b9ef5c (data)
85  0x8e609132 0xa0c0926e 0xb7800701 0x14aa4c94 (data)
84  0xe2e727   0x86ca978  0x9deacef3 0x149aa9cc (data)
83  0x9de2a525 0x7a989210 0xe152c0a6 0x148b0704 (data)
82  0xc276f1b  0x3ed25e5d 0xe0c00fcb 0x147b643c (data)
81  0xc8b20746 0x7df07605 0xe814bfed 0x146bc174 (data)
80  0x99aa8c0f 0xc760f72  0x5a282f3  0x145c1eac (data)
79  0x3b5b0189 0xa0580c82 0x45542af6 0x144c7be4 (data)
78  0x2cb1aea5 0x4fc484c3 0x4964092e 0x143cd91c (data)
77  0xa233d8b0 0xe768bfd5 0x630ec0dc 0x142d3654 (data)
76  0x219a16c4 0x1d0e739  0xd01eb7   0x141d938c (data)
75  0xb47ed19c 0x904caee1 0x96530001 0x140df0c4 (data)
74  0x25bb1ba2 0xd40662ac 0x97c1cf6c 0x13fe4dfc (data)
73  0xb036f8b6 0xe6a23383 0x72a34254 0x13eeab34 (data)
72  0x12c77530 0x4a8c3073 0x3255ea51 0x13df086c (data)
71  0x52dda1c  0xa510b832 0x3e65c989 0x13cf65a4 (data)
70  0x8bafac09 0xdbc8324  0x140f007b 0x13bfc2dc (data)
69  0x59c1ae3f 0x32cca9b6 0x6131b0be 0x13b02014 (data)
68  0xc8046401 0x768665fb 0x60a37fd3 0x13a07d4c (data)
67  0x5d898715 0x442234d4 0x85c1f2eb 0x1390da84 (data)
66  0xc037a8c2 0x37cc328c 0xac4692b8 0x138137bc (data)
65  0xff780a93 0xe80c3724 0xc5375aee 0x137194f4 (data)
64  0xe892a5bf 0x790bf65  0xc9077936 0x1361f22c (data)
63  0x84432d3e 0xa2377f71 0x9573f4e4 0x13524f64 (data)
62  0x0        0x0        0x0        0x1342ac9c
61  0x6610d3aa 0xaf3c8473 0xe36db0c4 0x133309d4 (data)
60  0x0        0x0        0x0        0x1323670c
59  0xd2d02fac 0x606ff0ed 0xcf52edb9 0x1313c444 (data)
58  0x0        0x0        0x0        0x1304217c
57  0x0        0x0        0x0        0x12f47eb4
56  0x4734e8f4 0xf1f3b935 0x59d1f30f 0x12e4dbec (data)
55  0xd6f122ca 0xb5b97578 0x58433c62 0x12d53924 (data)
54  0x12644a97 0xf69b5d20 0x50978c44 0x12c5965c (data)
53  0xf667e374 0xc4afafe6 0xf1e73a87 0x12b5f394 (data)
52  0xfdd7dbf3 0x3137bb0e 0xbb665252 0x12a650cc (data)
51  0x0        0x0        0x0        0x1296ae04
50  0x437cc1de 0x871d2457 0xbd21b15a 0x12870b3c (data)
49  0xdec2ee09 0xf4f3220f 0x94a6d109 0x12776874 (data)
48  0xe18d4c58 0x2b3327a7 0xfdd7195f 0x1267c5ac (data)
47  0x78e59561 0x6c0394f0 0xdb8df375 0x125822e4 (data)
46  0x0        0x0        0x0        0x1248801c
45  0x0        0x0        0x0        0x1238dd54
44  0x68331cab 0xa0abf2d6 0x2de54ce4 0x12293a8c (data)
43  0x0        0x0        0x0        0x121997c4
42  0xf9f6d695 0xe4e13e9b 0x2c778389 0x1209f4fc (data)
41  0x0        0x0        0x0        0x11fa5234
40  0x0        0x0        0x0        0x11eaaf6c
39  0x0        0x0        0x0        0x11db0ca4
38  0x0        0x0        0x0        0x11cb69dc
37  0x0        0x0        0x0        0x11bbc714
36  0x0        0x0        0x0        0x11ac244c
35  0x0        0x0        0x0        0x119c8184
34  0x0        0x0        0x0        0x118cdebc
33  0x0        0x0        0x0        0x117d3bf4
32  0x0        0x0        0x0        0x116d992c
31  0x0        0x0        0x0        0x115df664
30  0x0        0x0        0x0        0x114e539c
29  0x0        0x0        0x0        0x113eb0d4
28  0x0        0x0        0x0        0x112f0e0c
27  0x0        0x0        0x0        0x111f6b44
26  0x0        0x0        0x0        0x110fc87c
25  0x0        0x0        0x0        0x110025b4
24  0x0        0x0        0x0        0x10f082ec
23  0x0        0x0        0x0        0x10e0e024
22  0x0        0x0        0x0        0x10d13d5c
21  0x0        0x0        0x0        0x10c19a94
20  0x0        0x0        0x0        0x10b1f7cc
19  0x0        0x0        0x0        0x10a25504
18  0x0        0x0        0x0        0x1092b23c
17  0x0        0x0        0x0        0x10830f74
16  0x0        0x0        0x0        0x10736cac
15  0x0        0x0        0x0        0x1063c9e4
14  0x0        0x0        0x0        0x1054271c
13  0x0        0x0        0x0        0x10448454
12  0x0        0x0        0x0        0x1034e18c
11  0x0        0x0        0x0        0x10253ec4
10  0x0        0x0        0x0        0x10159bfc
9   0x0        0x0        0x0        0x1005f934
8   0x0        0x0        0x0        0xff6566c
7   0x0        0x0        0x0        0xfe6b3a4
6   0x0        0x0        0x0        0xfd710dc
5   0x0        0x0        0x0        0xfc76e14
4   0x0        0x0        0x0        0xfb7cb4c
3   0x0        0x0        0x0        0xfa82884
2   0x0        0x0        0x0        0xf9885bc
1   0x0        0x0        0x0        0xf88e2f4
0   0x0        0x0        0x0        0xf79402c
hash size:150
after delete, hash size:150
get data testing......., hash size:150
no data, key:0x101
no data, key:0x102
no data, key:0x103
no data, key:0x104
no data, key:0x105
no data, key:0x106
no data, key:0x107
no data, key:0x108
no data, key:0x109
no data, key:0x10a
no data, key:0x10b
no data, key:0x10c
no data, key:0x10d
no data, key:0x10e
no data, key:0x10f
no data, key:0x110
no data, key:0x111
no data, key:0x112
no data, key:0x113
no data, key:0x114
no data, key:0x115
no data, key:0x116
no data, key:0x117
no data, key:0x118
no data, key:0x119
no data, key:0x11a
no data, key:0x11b
no data, key:0x11c
no data, key:0x11d
no data, key:0x11e
no data, key:0x11f
no data, key:0x120
no data, key:0x121
no data, key:0x122
no data, key:0x123
no data, key:0x124
no data, key:0x125
no data, key:0x126
no data, key:0x127
no data, key:0x128
no data, key:0x129
no data, key:0x12a
no data, key:0x12b
no data, key:0x12c
no data, key:0x12d
no data, key:0x12e
no data, key:0x12f
no data, key:0x130
no data, key:0x131
no data, key:0x132
hash key!!
No pInfo  dwaddr seq  tax  buf (iter)
1   0x1209f4fc 0x133  51  50.00  0x50
2   0x12293a8c 0x134  52  51.00  0x51
3   0x125822e4 0x136  54  53.00  0x53
4   0x1267c5ac 0x138  56  55.00  0x55
5   0x12776874 0x139  57  56.00  0x56
6   0x12870b3c 0x13a  58  57.00  0x57
7   0x12a650cc 0x135  53  52.00  0x52
8   0x12b5f394 0x137  55  54.00  0x54
9   0x12c5965c 0x13b  59  58.00  0x58
10  0x12d53924 0x13d  61  60.00  0x60
11  0x12e4dbec 0x13e  62  61.00  0x61
12  0x1313c444 0x13f  63  62.00  0x62
13  0x133309d4 0x140  64  63.00  0x63
14  0x13524f64 0x13c  60  59.00  0x59
15  0x1361f22c 0x141  65  64.00  0x64
16  0x137194f4 0x142  66  65.00  0x65
17  0x138137bc 0x143  67  66.00  0x66
18  0x1390da84 0x144  68  67.00  0x67
19  0x13a07d4c 0x147  71  70.00  0x70
20  0x13b02014 0x148  72  71.00  0x71
21  0x13bfc2dc 0x14a  74  73.00  0x73
22  0x13cf65a4 0x14b  75  74.00  0x74
23  0x13df086c 0x14c  76  75.00  0x75
24  0x13eeab34 0x14e  78  77.00  0x77
25  0x13fe4dfc 0x151  81  80.00  0x80
26  0x140df0c4 0x152  82  81.00  0x81
27  0x141d938c 0x153  83  82.00  0x82
28  0x142d3654 0x154  84  83.00  0x83
29  0x143cd91c 0x155  85  84.00  0x84
30  0x144c7be4 0x156  86  85.00  0x85
31  0x145c1eac 0x158  88  87.00  0x87
32  0x146bc174 0x159  89  88.00  0x88
33  0x147b643c 0x15b  91  90.00  0x90
34  0x148b0704 0x15c  92  91.00  0x91
35  0x149aa9cc 0x15e  94  93.00  0x93
36  0x14aa4c94 0x15f  95  94.00  0x94
37  0x14b9ef5c 0x150  80  79.00  0x79
38  0x14c99224 0x160  96  95.00  0x95
39  0x14d934ec 0x157  87  86.00  0x86
40  0x14e8d7b4 0x161  97  96.00  0x96
41  0x14f87a7c 0x162  98  97.00  0x97
42  0x15081d44 0x163  99  98.00  0x98
43  0x1517c00c 0x145  69  68.00  0x68
44  0x152762d4 0x165  101 100.00 0x100
45  0x1537059c 0x166  102 101.00 0x101
46  0x1546a864 0x16a  106 105.00 0x105
47  0x15564b2c 0x16b  107 106.00 0x106
48  0x1565edf4 0x14d  77  76.00  0x76
49  0x157590bc 0x16c  108 107.00 0x107
50  0x15853384 0x16d  109 108.00 0x108
51  0x1594d64c 0x16e  110 109.00 0x109
52  0x15a47914 0x16f  111 110.00 0x110
53  0x15b41bdc 0x171  113 112.00 0x112
54  0x15c3bea4 0x149  73  72.00  0x72
55  0x15d3616c 0x169  105 104.00 0x104
56  0x15e30434 0x170  112 111.00 0x111
57  0x15f2a6fc 0x167  103 102.00 0x102
58  0x160249c4 0x172  114 113.00 0x113
59  0x1611ec8c 0x173  115 114.00 0x114
60  0x16218f54 0x174  116 115.00 0x115
61  0x1631321c 0x175  117 116.00 0x116
62  0x1640d4e4 0x15a  90  89.00  0x89
63  0x165077ac 0x176  118 117.00 0x117
64  0x16601a74 0x178  120 119.00 0x119
65  0x166fbd3c 0x168  104 103.00 0x103
66  0x167f6004 0x179  121 120.00 0x120
67  0x168f02cc 0x17a  122 121.00 0x121
68  0x169ea594 0x146  70  69.00  0x69
69  0x16ae485c 0x17b  123 122.00 0x122
70  0x16bdeb24 0x17c  124 123.00 0x123
71  0x16cd8dec 0x164  100 99.00  0x99
72  0x16dd30b4 0x17d  125 124.00 0x124
73  0x16ecd37c 0x17e  126 125.00 0x125
74  0x16fc7644 0x17f  127 126.00 0x126
75  0x170c190c 0x180  128 127.00 0x127
76  0x171bbbd4 0x15d  93  92.00  0x92
77  0x172b5e9c 0x177  119 118.00 0x118
78  0x173b0164 0x14f  79  78.00  0x78
79  0x174aa42c 0x182  130 129.00 0x129
80  0x175a46f4 0x18a  138 137.00 0x137
81  0x1769e9bc 0x18b  139 138.00 0x138
82  0x17798c84 0x18d  141 140.00 0x140
83  0x17892f4c 0x18e  142 141.00 0x141
84  0x1798d214 0x18f  143 142.00 0x142
85  0x17a874dc 0x194  148 147.00 0x147
86  0x17b817a4 0x195  149 148.00 0x148
87  0x17c7ba6c 0x196  150 149.00 0x149
88  0x17d75d34 0x197  151 150.00 0x150
89  0x17e6fffc 0x198  152 151.00 0x151
90  0x17f6a2c4 0x199  153 152.00 0x152
91  0x1806458c 0x19c  156 155.00 0x155
92  0x1815e854 0x19e  158 157.00 0x157
93  0x18258b1c 0x19f  159 158.00 0x158
94  0x18352de4 0x1a1  161 160.00 0x160
95  0x1844d0ac 0x1a2  162 161.00 0x161
96  0x18547374 0x1a3  163 162.00 0x162
97  0x1864163c 0x1a4  164 163.00 0x163
98  0x1873b904 0x1a5  165 164.00 0x164
99  0x18835bcc 0x1a6  166 165.00 0x165
100 0x1892fe94 0x185  133 132.00 0x132
101 0x18a2a15c 0x18c  140 139.00 0x139
102 0x18b24424 0x1a7  167 166.00 0x166
103 0x18c1e6ec 0x1aa  170 169.00 0x169
104 0x18d189b4 0x1b0  176 175.00 0x175
105 0x18e12c7c 0x1b2  178 177.00 0x177
106 0x18f0cf44 0x1ac  172 171.00 0x171
107 0x1900720c 0x1b3  179 178.00 0x178
108 0x191014d4 0x1b5  181 180.00 0x180
109 0x191fb79c 0x1b6  182 181.00 0x181
110 0x192f5a64 0x1b7  183 182.00 0x182
111 0x193efd2c 0x19b  155 154.00 0x154
112 0x194e9ff4 0x189  137 136.00 0x136
113 0x195e42bc 0x1bb  187 186.00 0x186
114 0x196de584 0x1bc  188 187.00 0x187
115 0x197d884c 0x1bd  189 188.00 0x188
116 0x198d2b14 0x1ab  171 170.00 0x170
117 0x199ccddc 0x1be  190 189.00 0x189
118 0x19ac70a4 0x1bf  191 190.00 0x190
119 0x19bc136c 0x1c0  192 191.00 0x191
120 0x19cbb634 0x1ae  174 173.00 0x173
121 0x19db58fc 0x1c1  193 192.00 0x192
122 0x19eafbc4 0x1c2  194 193.00 0x193
123 0x19fa9e8c 0x1c3  195 194.00 0x194
124 0x1a0a4154 0x1c4  196 195.00 0x195
125 0x1a19e41c 0x181  129 128.00 0x128
126 0x1a2986e4 0x1c5  197 196.00 0x196
127 0x1a3929ac 0x1c7  199 198.00 0x198
128 0x1a48cc74 0x1a8  168 167.00 0x167
129 0x1a586f3c 0x1c8  200 199.00 0x199
130 0x1a875794 0x19a  154 153.00 0x153
131 0x1a96fa5c 0x193  147 146.00 0x146
132 0x1af4cb0c 0x1af  175 174.00 0x174
133 0x1b42f8f4 0x1b1  177 176.00 0x176
134 0x1b623e84 0x1ad  173 172.00 0x172
135 0x1b818414 0x1ba  186 185.00 0x185
136 0x1bc00f34 0x186  134 133.00 0x133
137 0x1bdf54c4 0x191  145 144.00 0x144
138 0x1bfe9a54 0x184  132 131.00 0x131
139 0x1c2d82ac 0x1c6  198 197.00 0x197
140 0x1ce9240c 0x187  135 134.00 0x134
141 0x1cf8c6d4 0x19d  157 156.00 0x156
142 0x1d08699c 0x190  144 143.00 0x143
143 0x1d9522a4 0x192  146 145.00 0x145
144 0x1db46834 0x1b9  185 184.00 0x184
145 0x1dc40afc 0x1a0  160 159.00 0x159
146 0x1e21dbac 0x188  136 135.00 0x135
147 0x1e50c404 0x183  131 130.00 0x130
148 0x1e7fac5c 0x1b4  180 179.00 0x179
149 0x1e9ef1ec 0x1a9  169 168.00 0x168
150 0x1edd7d0c 0x1b8  184 183.00 0x183

No pInfo  dwaddr seq  tax  buf (by GetHashItem)
1   0x1209f4fc 0x133  51  50.00  0x50
2   0x12293a8c 0x134  52  51.00  0x51
3   0x125822e4 0x136  54  53.00  0x53
4   0x1267c5ac 0x138  56  55.00  0x55
5   0x12776874 0x139  57  56.00  0x56
6   0x12870b3c 0x13a  58  57.00  0x57
7   0x12a650cc 0x135  53  52.00  0x52
8   0x12b5f394 0x137  55  54.00  0x54
9   0x12c5965c 0x13b  59  58.00  0x58
10  0x12d53924 0x13d  61  60.00  0x60
11  0x12e4dbec 0x13e  62  61.00  0x61
12  0x1313c444 0x13f  63  62.00  0x62
13  0x133309d4 0x140  64  63.00  0x63
14  0x13524f64 0x13c  60  59.00  0x59
15  0x1361f22c 0x141  65  64.00  0x64
16  0x137194f4 0x142  66  65.00  0x65
17  0x138137bc 0x143  67  66.00  0x66
18  0x1390da84 0x144  68  67.00  0x67
19  0x13a07d4c 0x147  71  70.00  0x70
20  0x13b02014 0x148  72  71.00  0x71
21  0x13bfc2dc 0x14a  74  73.00  0x73
22  0x13cf65a4 0x14b  75  74.00  0x74
23  0x13df086c 0x14c  76  75.00  0x75
24  0x13eeab34 0x14e  78  77.00  0x77
25  0x13fe4dfc 0x151  81  80.00  0x80
26  0x140df0c4 0x152  82  81.00  0x81
27  0x141d938c 0x153  83  82.00  0x82
28  0x142d3654 0x154  84  83.00  0x83
29  0x143cd91c 0x155  85  84.00  0x84
30  0x144c7be4 0x156  86  85.00  0x85
31  0x145c1eac 0x158  88  87.00  0x87
32  0x146bc174 0x159  89  88.00  0x88
33  0x147b643c 0x15b  91  90.00  0x90
34  0x148b0704 0x15c  92  91.00  0x91
35  0x149aa9cc 0x15e  94  93.00  0x93
36  0x14aa4c94 0x15f  95  94.00  0x94
37  0x14b9ef5c 0x150  80  79.00  0x79
38  0x14c99224 0x160  96  95.00  0x95
39  0x14d934ec 0x157  87  86.00  0x86
40  0x14e8d7b4 0x161  97  96.00  0x96
41  0x14f87a7c 0x162  98  97.00  0x97
42  0x15081d44 0x163  99  98.00  0x98
43  0x1517c00c 0x145  69  68.00  0x68
44  0x152762d4 0x165  101 100.00 0x100
45  0x1537059c 0x166  102 101.00 0x101
46  0x1546a864 0x16a  106 105.00 0x105
47  0x15564b2c 0x16b  107 106.00 0x106
48  0x1565edf4 0x14d  77  76.00  0x76
49  0x157590bc 0x16c  108 107.00 0x107
50  0x15853384 0x16d  109 108.00 0x108
51  0x1594d64c 0x16e  110 109.00 0x109
52  0x15a47914 0x16f  111 110.00 0x110
53  0x15b41bdc 0x171  113 112.00 0x112
54  0x15c3bea4 0x149  73  72.00  0x72
55  0x15d3616c 0x169  105 104.00 0x104
56  0x15e30434 0x170  112 111.00 0x111
57  0x15f2a6fc 0x167  103 102.00 0x102
58  0x160249c4 0x172  114 113.00 0x113
59  0x1611ec8c 0x173  115 114.00 0x114
60  0x16218f54 0x174  116 115.00 0x115
61  0x1631321c 0x175  117 116.00 0x116
62  0x1640d4e4 0x15a  90  89.00  0x89
63  0x165077ac 0x176  118 117.00 0x117
64  0x16601a74 0x178  120 119.00 0x119
65  0x166fbd3c 0x168  104 103.00 0x103
66  0x167f6004 0x179  121 120.00 0x120
67  0x168f02cc 0x17a  122 121.00 0x121
68  0x169ea594 0x146  70  69.00  0x69
69  0x16ae485c 0x17b  123 122.00 0x122
70  0x16bdeb24 0x17c  124 123.00 0x123
71  0x16cd8dec 0x164  100 99.00  0x99
72  0x16dd30b4 0x17d  125 124.00 0x124
73  0x16ecd37c 0x17e  126 125.00 0x125
74  0x16fc7644 0x17f  127 126.00 0x126
75  0x170c190c 0x180  128 127.00 0x127
76  0x171bbbd4 0x15d  93  92.00  0x92
77  0x172b5e9c 0x177  119 118.00 0x118
78  0x173b0164 0x14f  79  78.00  0x78
79  0x174aa42c 0x182  130 129.00 0x129
80  0x175a46f4 0x18a  138 137.00 0x137
81  0x1769e9bc 0x18b  139 138.00 0x138
82  0x17798c84 0x18d  141 140.00 0x140
83  0x17892f4c 0x18e  142 141.00 0x141
84  0x1798d214 0x18f  143 142.00 0x142
85  0x17a874dc 0x194  148 147.00 0x147
86  0x17b817a4 0x195  149 148.00 0x148
87  0x17c7ba6c 0x196  150 149.00 0x149
88  0x17d75d34 0x197  151 150.00 0x150
89  0x17e6fffc 0x198  152 151.00 0x151
90  0x17f6a2c4 0x199  153 152.00 0x152
91  0x1806458c 0x19c  156 155.00 0x155
92  0x1815e854 0x19e  158 157.00 0x157
93  0x18258b1c 0x19f  159 158.00 0x158
94  0x18352de4 0x1a1  161 160.00 0x160
95  0x1844d0ac 0x1a2  162 161.00 0x161
96  0x18547374 0x1a3  163 162.00 0x162
97  0x1864163c 0x1a4  164 163.00 0x163
98  0x1873b904 0x1a5  165 164.00 0x164
99  0x18835bcc 0x1a6  166 165.00 0x165
100 0x1892fe94 0x185  133 132.00 0x132
101 0x18a2a15c 0x18c  140 139.00 0x139
102 0x18b24424 0x1a7  167 166.00 0x166
103 0x18c1e6ec 0x1aa  170 169.00 0x169
104 0x18d189b4 0x1b0  176 175.00 0x175
105 0x18e12c7c 0x1b2  178 177.00 0x177
106 0x18f0cf44 0x1ac  172 171.00 0x171
107 0x1900720c 0x1b3  179 178.00 0x178
108 0x191014d4 0x1b5  181 180.00 0x180
109 0x191fb79c 0x1b6  182 181.00 0x181
110 0x192f5a64 0x1b7  183 182.00 0x182
111 0x193efd2c 0x19b  155 154.00 0x154
112 0x194e9ff4 0x189  137 136.00 0x136
113 0x195e42bc 0x1bb  187 186.00 0x186
114 0x196de584 0x1bc  188 187.00 0x187
115 0x197d884c 0x1bd  189 188.00 0x188
116 0x198d2b14 0x1ab  171 170.00 0x170
117 0x199ccddc 0x1be  190 189.00 0x189
118 0x19ac70a4 0x1bf  191 190.00 0x190
119 0x19bc136c 0x1c0  192 191.00 0x191
120 0x19cbb634 0x1ae  174 173.00 0x173
121 0x19db58fc 0x1c1  193 192.00 0x192
122 0x19eafbc4 0x1c2  194 193.00 0x193
123 0x19fa9e8c 0x1c3  195 194.00 0x194
124 0x1a0a4154 0x1c4  196 195.00 0x195
125 0x1a19e41c 0x181  129 128.00 0x128
126 0x1a2986e4 0x1c5  197 196.00 0x196
127 0x1a3929ac 0x1c7  199 198.00 0x198
128 0x1a48cc74 0x1a8  168 167.00 0x167
129 0x1a586f3c 0x1c8  200 199.00 0x199
130 0x1a875794 0x19a  154 153.00 0x153
131 0x1a96fa5c 0x193  147 146.00 0x146
132 0x1af4cb0c 0x1af  175 174.00 0x174
133 0x1b42f8f4 0x1b1  177 176.00 0x176
134 0x1b623e84 0x1ad  173 172.00 0x172
135 0x1b818414 0x1ba  186 185.00 0x185
136 0x1bc00f34 0x186  134 133.00 0x133
137 0x1bdf54c4 0x191  145 144.00 0x144
138 0x1bfe9a54 0x184  132 131.00 0x131
139 0x1c2d82ac 0x1c6  198 197.00 0x197
140 0x1ce9240c 0x187  135 134.00 0x134
141 0x1cf8c6d4 0x19d  157 156.00 0x156
142 0x1d08699c 0x190  144 143.00 0x143
143 0x1d9522a4 0x192  146 145.00 0x145
144 0x1db46834 0x1b9  185 184.00 0x184
145 0x1dc40afc 0x1a0  160 159.00 0x159
146 0x1e21dbac 0x188  136 135.00 0x135
147 0x1e50c404 0x183  131 130.00 0x130
148 0x1e7fac5c 0x1b4  180 179.00 0x179
149 0x1e9ef1ec 0x1a9  169 168.00 0x168
150 0x1edd7d0c 0x1b8  184 183.00 0x183
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1209F4FC
dwaddr            :    120EA4FC
seq               :    120EA500
buf[187]          :    120EA504
tax               :    120EA5C0
bigdata[3001024]  :    120EA5C4
test              :    121355C4
samplenum         :    121355C8
sampleport[123]   :    121355CC
bigdata2[4001024] :    121357B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12293A8C
dwaddr            :    122DEA8C
seq               :    122DEA90
buf[187]          :    122DEA94
tax               :    122DEB50
bigdata[3001024]  :    122DEB54
test              :    12329B54
samplenum         :    12329B58
sampleport[123]   :    12329B5C
bigdata2[4001024] :    12329D48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    125822E4
dwaddr            :    125CD2E4
seq               :    125CD2E8
buf[187]          :    125CD2EC
tax               :    125CD3A8
bigdata[3001024]  :    125CD3AC
test              :    126183AC
samplenum         :    126183B0
sampleport[123]   :    126183B4
bigdata2[4001024] :    126185A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1267C5AC
dwaddr            :    126C75AC
seq               :    126C75B0
buf[187]          :    126C75B4
tax               :    126C7670
bigdata[3001024]  :    126C7674
test              :    12712674
samplenum         :    12712678
sampleport[123]   :    1271267C
bigdata2[4001024] :    12712868
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12776874
dwaddr            :    127C1874
seq               :    127C1878
buf[187]          :    127C187C
tax               :    127C1938
bigdata[3001024]  :    127C193C
test              :    1280C93C
samplenum         :    1280C940
sampleport[123]   :    1280C944
bigdata2[4001024] :    1280CB30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12870B3C
dwaddr            :    128BBB3C
seq               :    128BBB40
buf[187]          :    128BBB44
tax               :    128BBC00
bigdata[3001024]  :    128BBC04
test              :    12906C04
samplenum         :    12906C08
sampleport[123]   :    12906C0C
bigdata2[4001024] :    12906DF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12A650CC
dwaddr            :    12AB00CC
seq               :    12AB00D0
buf[187]          :    12AB00D4
tax               :    12AB0190
bigdata[3001024]  :    12AB0194
test              :    12AFB194
samplenum         :    12AFB198
sampleport[123]   :    12AFB19C
bigdata2[4001024] :    12AFB388
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12B5F394
dwaddr            :    12BAA394
seq               :    12BAA398
buf[187]          :    12BAA39C
tax               :    12BAA458
bigdata[3001024]  :    12BAA45C
test              :    12BF545C
samplenum         :    12BF5460
sampleport[123]   :    12BF5464
bigdata2[4001024] :    12BF5650
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12C5965C
dwaddr            :    12CA465C
seq               :    12CA4660
buf[187]          :    12CA4664
tax               :    12CA4720
bigdata[3001024]  :    12CA4724
test              :    12CEF724
samplenum         :    12CEF728
sampleport[123]   :    12CEF72C
bigdata2[4001024] :    12CEF918
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12D53924
dwaddr            :    12D9E924
seq               :    12D9E928
buf[187]          :    12D9E92C
tax               :    12D9E9E8
bigdata[3001024]  :    12D9E9EC
test              :    12DE99EC
samplenum         :    12DE99F0
sampleport[123]   :    12DE99F4
bigdata2[4001024] :    12DE9BE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12E4DBEC
dwaddr            :    12E98BEC
seq               :    12E98BF0
buf[187]          :    12E98BF4
tax               :    12E98CB0
bigdata[3001024]  :    12E98CB4
test              :    12EE3CB4
samplenum         :    12EE3CB8
sampleport[123]   :    12EE3CBC
bigdata2[4001024] :    12EE3EA8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1313C444
dwaddr            :    13187444
seq               :    13187448
buf[187]          :    1318744C
tax               :    13187508
bigdata[3001024]  :    1318750C
test              :    131D250C
samplenum         :    131D2510
sampleport[123]   :    131D2514
bigdata2[4001024] :    131D2700
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    133309D4
dwaddr            :    1337B9D4
seq               :    1337B9D8
buf[187]          :    1337B9DC
tax               :    1337BA98
bigdata[3001024]  :    1337BA9C
test              :    133C6A9C
samplenum         :    133C6AA0
sampleport[123]   :    133C6AA4
bigdata2[4001024] :    133C6C90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13524F64
dwaddr            :    1356FF64
seq               :    1356FF68
buf[187]          :    1356FF6C
tax               :    13570028
bigdata[3001024]  :    1357002C
test              :    135BB02C
samplenum         :    135BB030
sampleport[123]   :    135BB034
bigdata2[4001024] :    135BB220
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1361F22C
dwaddr            :    1366A22C
seq               :    1366A230
buf[187]          :    1366A234
tax               :    1366A2F0
bigdata[3001024]  :    1366A2F4
test              :    136B52F4
samplenum         :    136B52F8
sampleport[123]   :    136B52FC
bigdata2[4001024] :    136B54E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    137194F4
dwaddr            :    137644F4
seq               :    137644F8
buf[187]          :    137644FC
tax               :    137645B8
bigdata[3001024]  :    137645BC
test              :    137AF5BC
samplenum         :    137AF5C0
sampleport[123]   :    137AF5C4
bigdata2[4001024] :    137AF7B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    138137BC
dwaddr            :    1385E7BC
seq               :    1385E7C0
buf[187]          :    1385E7C4
tax               :    1385E880
bigdata[3001024]  :    1385E884
test              :    138A9884
samplenum         :    138A9888
sampleport[123]   :    138A988C
bigdata2[4001024] :    138A9A78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1390DA84
dwaddr            :    13958A84
seq               :    13958A88
buf[187]          :    13958A8C
tax               :    13958B48
bigdata[3001024]  :    13958B4C
test              :    139A3B4C
samplenum         :    139A3B50
sampleport[123]   :    139A3B54
bigdata2[4001024] :    139A3D40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13A07D4C
dwaddr            :    13A52D4C
seq               :    13A52D50
buf[187]          :    13A52D54
tax               :    13A52E10
bigdata[3001024]  :    13A52E14
test              :    13A9DE14
samplenum         :    13A9DE18
sampleport[123]   :    13A9DE1C
bigdata2[4001024] :    13A9E008
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13B02014
dwaddr            :    13B4D014
seq               :    13B4D018
buf[187]          :    13B4D01C
tax               :    13B4D0D8
bigdata[3001024]  :    13B4D0DC
test              :    13B980DC
samplenum         :    13B980E0
sampleport[123]   :    13B980E4
bigdata2[4001024] :    13B982D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13BFC2DC
dwaddr            :    13C472DC
seq               :    13C472E0
buf[187]          :    13C472E4
tax               :    13C473A0
bigdata[3001024]  :    13C473A4
test              :    13C923A4
samplenum         :    13C923A8
sampleport[123]   :    13C923AC
bigdata2[4001024] :    13C92598
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13CF65A4
dwaddr            :    13D415A4
seq               :    13D415A8
buf[187]          :    13D415AC
tax               :    13D41668
bigdata[3001024]  :    13D4166C
test              :    13D8C66C
samplenum         :    13D8C670
sampleport[123]   :    13D8C674
bigdata2[4001024] :    13D8C860
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13DF086C
dwaddr            :    13E3B86C
seq               :    13E3B870
buf[187]          :    13E3B874
tax               :    13E3B930
bigdata[3001024]  :    13E3B934
test              :    13E86934
samplenum         :    13E86938
sampleport[123]   :    13E8693C
bigdata2[4001024] :    13E86B28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13EEAB34
dwaddr            :    13F35B34
seq               :    13F35B38
buf[187]          :    13F35B3C
tax               :    13F35BF8
bigdata[3001024]  :    13F35BFC
test              :    13F80BFC
samplenum         :    13F80C00
sampleport[123]   :    13F80C04
bigdata2[4001024] :    13F80DF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13FE4DFC
dwaddr            :    1402FDFC
seq               :    1402FE00
buf[187]          :    1402FE04
tax               :    1402FEC0
bigdata[3001024]  :    1402FEC4
test              :    1407AEC4
samplenum         :    1407AEC8
sampleport[123]   :    1407AECC
bigdata2[4001024] :    1407B0B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    140DF0C4
dwaddr            :    1412A0C4
seq               :    1412A0C8
buf[187]          :    1412A0CC
tax               :    1412A188
bigdata[3001024]  :    1412A18C
test              :    1417518C
samplenum         :    14175190
sampleport[123]   :    14175194
bigdata2[4001024] :    14175380
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    141D938C
dwaddr            :    1422438C
seq               :    14224390
buf[187]          :    14224394
tax               :    14224450
bigdata[3001024]  :    14224454
test              :    1426F454
samplenum         :    1426F458
sampleport[123]   :    1426F45C
bigdata2[4001024] :    1426F648
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    142D3654
dwaddr            :    1431E654
seq               :    1431E658
buf[187]          :    1431E65C
tax               :    1431E718
bigdata[3001024]  :    1431E71C
test              :    1436971C
samplenum         :    14369720
sampleport[123]   :    14369724
bigdata2[4001024] :    14369910
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    143CD91C
dwaddr            :    1441891C
seq               :    14418920
buf[187]          :    14418924
tax               :    144189E0
bigdata[3001024]  :    144189E4
test              :    144639E4
samplenum         :    144639E8
sampleport[123]   :    144639EC
bigdata2[4001024] :    14463BD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    144C7BE4
dwaddr            :    14512BE4
seq               :    14512BE8
buf[187]          :    14512BEC
tax               :    14512CA8
bigdata[3001024]  :    14512CAC
test              :    1455DCAC
samplenum         :    1455DCB0
sampleport[123]   :    1455DCB4
bigdata2[4001024] :    1455DEA0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    145C1EAC
dwaddr            :    1460CEAC
seq               :    1460CEB0
buf[187]          :    1460CEB4
tax               :    1460CF70
bigdata[3001024]  :    1460CF74
test              :    14657F74
samplenum         :    14657F78
sampleport[123]   :    14657F7C
bigdata2[4001024] :    14658168
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    146BC174
dwaddr            :    14707174
seq               :    14707178
buf[187]          :    1470717C
tax               :    14707238
bigdata[3001024]  :    1470723C
test              :    1475223C
samplenum         :    14752240
sampleport[123]   :    14752244
bigdata2[4001024] :    14752430
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    147B643C
dwaddr            :    1480143C
seq               :    14801440
buf[187]          :    14801444
tax               :    14801500
bigdata[3001024]  :    14801504
test              :    1484C504
samplenum         :    1484C508
sampleport[123]   :    1484C50C
bigdata2[4001024] :    1484C6F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    148B0704
dwaddr            :    148FB704
seq               :    148FB708
buf[187]          :    148FB70C
tax               :    148FB7C8
bigdata[3001024]  :    148FB7CC
test              :    149467CC
samplenum         :    149467D0
sampleport[123]   :    149467D4
bigdata2[4001024] :    149469C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    149AA9CC
dwaddr            :    149F59CC
seq               :    149F59D0
buf[187]          :    149F59D4
tax               :    149F5A90
bigdata[3001024]  :    149F5A94
test              :    14A40A94
samplenum         :    14A40A98
sampleport[123]   :    14A40A9C
bigdata2[4001024] :    14A40C88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14AA4C94
dwaddr            :    14AEFC94
seq               :    14AEFC98
buf[187]          :    14AEFC9C
tax               :    14AEFD58
bigdata[3001024]  :    14AEFD5C
test              :    14B3AD5C
samplenum         :    14B3AD60
sampleport[123]   :    14B3AD64
bigdata2[4001024] :    14B3AF50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14B9EF5C
dwaddr            :    14BE9F5C
seq               :    14BE9F60
buf[187]          :    14BE9F64
tax               :    14BEA020
bigdata[3001024]  :    14BEA024
test              :    14C35024
samplenum         :    14C35028
sampleport[123]   :    14C3502C
bigdata2[4001024] :    14C35218
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14C99224
dwaddr            :    14CE4224
seq               :    14CE4228
buf[187]          :    14CE422C
tax               :    14CE42E8
bigdata[3001024]  :    14CE42EC
test              :    14D2F2EC
samplenum         :    14D2F2F0
sampleport[123]   :    14D2F2F4
bigdata2[4001024] :    14D2F4E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14D934EC
dwaddr            :    14DDE4EC
seq               :    14DDE4F0
buf[187]          :    14DDE4F4
tax               :    14DDE5B0
bigdata[3001024]  :    14DDE5B4
test              :    14E295B4
samplenum         :    14E295B8
sampleport[123]   :    14E295BC
bigdata2[4001024] :    14E297A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14E8D7B4
dwaddr            :    14ED87B4
seq               :    14ED87B8
buf[187]          :    14ED87BC
tax               :    14ED8878
bigdata[3001024]  :    14ED887C
test              :    14F2387C
samplenum         :    14F23880
sampleport[123]   :    14F23884
bigdata2[4001024] :    14F23A70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14F87A7C
dwaddr            :    14FD2A7C
seq               :    14FD2A80
buf[187]          :    14FD2A84
tax               :    14FD2B40
bigdata[3001024]  :    14FD2B44
test              :    1501DB44
samplenum         :    1501DB48
sampleport[123]   :    1501DB4C
bigdata2[4001024] :    1501DD38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15081D44
dwaddr            :    150CCD44
seq               :    150CCD48
buf[187]          :    150CCD4C
tax               :    150CCE08
bigdata[3001024]  :    150CCE0C
test              :    15117E0C
samplenum         :    15117E10
sampleport[123]   :    15117E14
bigdata2[4001024] :    15118000
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1517C00C
dwaddr            :    151C700C
seq               :    151C7010
buf[187]          :    151C7014
tax               :    151C70D0
bigdata[3001024]  :    151C70D4
test              :    152120D4
samplenum         :    152120D8
sampleport[123]   :    152120DC
bigdata2[4001024] :    152122C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    152762D4
dwaddr            :    152C12D4
seq               :    152C12D8
buf[187]          :    152C12DC
tax               :    152C1398
bigdata[3001024]  :    152C139C
test              :    1530C39C
samplenum         :    1530C3A0
sampleport[123]   :    1530C3A4
bigdata2[4001024] :    1530C590
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1537059C
dwaddr            :    153BB59C
seq               :    153BB5A0
buf[187]          :    153BB5A4
tax               :    153BB660
bigdata[3001024]  :    153BB664
test              :    15406664
samplenum         :    15406668
sampleport[123]   :    1540666C
bigdata2[4001024] :    15406858
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1546A864
dwaddr            :    154B5864
seq               :    154B5868
buf[187]          :    154B586C
tax               :    154B5928
bigdata[3001024]  :    154B592C
test              :    1550092C
samplenum         :    15500930
sampleport[123]   :    15500934
bigdata2[4001024] :    15500B20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15564B2C
dwaddr            :    155AFB2C
seq               :    155AFB30
buf[187]          :    155AFB34
tax               :    155AFBF0
bigdata[3001024]  :    155AFBF4
test              :    155FABF4
samplenum         :    155FABF8
sampleport[123]   :    155FABFC
bigdata2[4001024] :    155FADE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1565EDF4
dwaddr            :    156A9DF4
seq               :    156A9DF8
buf[187]          :    156A9DFC
tax               :    156A9EB8
bigdata[3001024]  :    156A9EBC
test              :    156F4EBC
samplenum         :    156F4EC0
sampleport[123]   :    156F4EC4
bigdata2[4001024] :    156F50B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    157590BC
dwaddr            :    157A40BC
seq               :    157A40C0
buf[187]          :    157A40C4
tax               :    157A4180
bigdata[3001024]  :    157A4184
test              :    157EF184
samplenum         :    157EF188
sampleport[123]   :    157EF18C
bigdata2[4001024] :    157EF378
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15853384
dwaddr            :    1589E384
seq               :    1589E388
buf[187]          :    1589E38C
tax               :    1589E448
bigdata[3001024]  :    1589E44C
test              :    158E944C
samplenum         :    158E9450
sampleport[123]   :    158E9454
bigdata2[4001024] :    158E9640
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1594D64C
dwaddr            :    1599864C
seq               :    15998650
buf[187]          :    15998654
tax               :    15998710
bigdata[3001024]  :    15998714
test              :    159E3714
samplenum         :    159E3718
sampleport[123]   :    159E371C
bigdata2[4001024] :    159E3908
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15A47914
dwaddr            :    15A92914
seq               :    15A92918
buf[187]          :    15A9291C
tax               :    15A929D8
bigdata[3001024]  :    15A929DC
test              :    15ADD9DC
samplenum         :    15ADD9E0
sampleport[123]   :    15ADD9E4
bigdata2[4001024] :    15ADDBD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15B41BDC
dwaddr            :    15B8CBDC
seq               :    15B8CBE0
buf[187]          :    15B8CBE4
tax               :    15B8CCA0
bigdata[3001024]  :    15B8CCA4
test              :    15BD7CA4
samplenum         :    15BD7CA8
sampleport[123]   :    15BD7CAC
bigdata2[4001024] :    15BD7E98
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15C3BEA4
dwaddr            :    15C86EA4
seq               :    15C86EA8
buf[187]          :    15C86EAC
tax               :    15C86F68
bigdata[3001024]  :    15C86F6C
test              :    15CD1F6C
samplenum         :    15CD1F70
sampleport[123]   :    15CD1F74
bigdata2[4001024] :    15CD2160
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15D3616C
dwaddr            :    15D8116C
seq               :    15D81170
buf[187]          :    15D81174
tax               :    15D81230
bigdata[3001024]  :    15D81234
test              :    15DCC234
samplenum         :    15DCC238
sampleport[123]   :    15DCC23C
bigdata2[4001024] :    15DCC428
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15E30434
dwaddr            :    15E7B434
seq               :    15E7B438
buf[187]          :    15E7B43C
tax               :    15E7B4F8
bigdata[3001024]  :    15E7B4FC
test              :    15EC64FC
samplenum         :    15EC6500
sampleport[123]   :    15EC6504
bigdata2[4001024] :    15EC66F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15F2A6FC
dwaddr            :    15F756FC
seq               :    15F75700
buf[187]          :    15F75704
tax               :    15F757C0
bigdata[3001024]  :    15F757C4
test              :    15FC07C4
samplenum         :    15FC07C8
sampleport[123]   :    15FC07CC
bigdata2[4001024] :    15FC09B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    160249C4
dwaddr            :    1606F9C4
seq               :    1606F9C8
buf[187]          :    1606F9CC
tax               :    1606FA88
bigdata[3001024]  :    1606FA8C
test              :    160BAA8C
samplenum         :    160BAA90
sampleport[123]   :    160BAA94
bigdata2[4001024] :    160BAC80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1611EC8C
dwaddr            :    16169C8C
seq               :    16169C90
buf[187]          :    16169C94
tax               :    16169D50
bigdata[3001024]  :    16169D54
test              :    161B4D54
samplenum         :    161B4D58
sampleport[123]   :    161B4D5C
bigdata2[4001024] :    161B4F48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16218F54
dwaddr            :    16263F54
seq               :    16263F58
buf[187]          :    16263F5C
tax               :    16264018
bigdata[3001024]  :    1626401C
test              :    162AF01C
samplenum         :    162AF020
sampleport[123]   :    162AF024
bigdata2[4001024] :    162AF210
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1631321C
dwaddr            :    1635E21C
seq               :    1635E220
buf[187]          :    1635E224
tax               :    1635E2E0
bigdata[3001024]  :    1635E2E4
test              :    163A92E4
samplenum         :    163A92E8
sampleport[123]   :    163A92EC
bigdata2[4001024] :    163A94D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1640D4E4
dwaddr            :    164584E4
seq               :    164584E8
buf[187]          :    164584EC
tax               :    164585A8
bigdata[3001024]  :    164585AC
test              :    164A35AC
samplenum         :    164A35B0
sampleport[123]   :    164A35B4
bigdata2[4001024] :    164A37A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    165077AC
dwaddr            :    165527AC
seq               :    165527B0
buf[187]          :    165527B4
tax               :    16552870
bigdata[3001024]  :    16552874
test              :    1659D874
samplenum         :    1659D878
sampleport[123]   :    1659D87C
bigdata2[4001024] :    1659DA68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16601A74
dwaddr            :    1664CA74
seq               :    1664CA78
buf[187]          :    1664CA7C
tax               :    1664CB38
bigdata[3001024]  :    1664CB3C
test              :    16697B3C
samplenum         :    16697B40
sampleport[123]   :    16697B44
bigdata2[4001024] :    16697D30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    166FBD3C
dwaddr            :    16746D3C
seq               :    16746D40
buf[187]          :    16746D44
tax               :    16746E00
bigdata[3001024]  :    16746E04
test              :    16791E04
samplenum         :    16791E08
sampleport[123]   :    16791E0C
bigdata2[4001024] :    16791FF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    167F6004
dwaddr            :    16841004
seq               :    16841008
buf[187]          :    1684100C
tax               :    168410C8
bigdata[3001024]  :    168410CC
test              :    1688C0CC
samplenum         :    1688C0D0
sampleport[123]   :    1688C0D4
bigdata2[4001024] :    1688C2C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    168F02CC
dwaddr            :    1693B2CC
seq               :    1693B2D0
buf[187]          :    1693B2D4
tax               :    1693B390
bigdata[3001024]  :    1693B394
test              :    16986394
samplenum         :    16986398
sampleport[123]   :    1698639C
bigdata2[4001024] :    16986588
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    169EA594
dwaddr            :    16A35594
seq               :    16A35598
buf[187]          :    16A3559C
tax               :    16A35658
bigdata[3001024]  :    16A3565C
test              :    16A8065C
samplenum         :    16A80660
sampleport[123]   :    16A80664
bigdata2[4001024] :    16A80850
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16AE485C
dwaddr            :    16B2F85C
seq               :    16B2F860
buf[187]          :    16B2F864
tax               :    16B2F920
bigdata[3001024]  :    16B2F924
test              :    16B7A924
samplenum         :    16B7A928
sampleport[123]   :    16B7A92C
bigdata2[4001024] :    16B7AB18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16BDEB24
dwaddr            :    16C29B24
seq               :    16C29B28
buf[187]          :    16C29B2C
tax               :    16C29BE8
bigdata[3001024]  :    16C29BEC
test              :    16C74BEC
samplenum         :    16C74BF0
sampleport[123]   :    16C74BF4
bigdata2[4001024] :    16C74DE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16CD8DEC
dwaddr            :    16D23DEC
seq               :    16D23DF0
buf[187]          :    16D23DF4
tax               :    16D23EB0
bigdata[3001024]  :    16D23EB4
test              :    16D6EEB4
samplenum         :    16D6EEB8
sampleport[123]   :    16D6EEBC
bigdata2[4001024] :    16D6F0A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16DD30B4
dwaddr            :    16E1E0B4
seq               :    16E1E0B8
buf[187]          :    16E1E0BC
tax               :    16E1E178
bigdata[3001024]  :    16E1E17C
test              :    16E6917C
samplenum         :    16E69180
sampleport[123]   :    16E69184
bigdata2[4001024] :    16E69370
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16ECD37C
dwaddr            :    16F1837C
seq               :    16F18380
buf[187]          :    16F18384
tax               :    16F18440
bigdata[3001024]  :    16F18444
test              :    16F63444
samplenum         :    16F63448
sampleport[123]   :    16F6344C
bigdata2[4001024] :    16F63638
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16FC7644
dwaddr            :    17012644
seq               :    17012648
buf[187]          :    1701264C
tax               :    17012708
bigdata[3001024]  :    1701270C
test              :    1705D70C
samplenum         :    1705D710
sampleport[123]   :    1705D714
bigdata2[4001024] :    1705D900
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    170C190C
dwaddr            :    1710C90C
seq               :    1710C910
buf[187]          :    1710C914
tax               :    1710C9D0
bigdata[3001024]  :    1710C9D4
test              :    171579D4
samplenum         :    171579D8
sampleport[123]   :    171579DC
bigdata2[4001024] :    17157BC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    171BBBD4
dwaddr            :    17206BD4
seq               :    17206BD8
buf[187]          :    17206BDC
tax               :    17206C98
bigdata[3001024]  :    17206C9C
test              :    17251C9C
samplenum         :    17251CA0
sampleport[123]   :    17251CA4
bigdata2[4001024] :    17251E90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    172B5E9C
dwaddr            :    17300E9C
seq               :    17300EA0
buf[187]          :    17300EA4
tax               :    17300F60
bigdata[3001024]  :    17300F64
test              :    1734BF64
samplenum         :    1734BF68
sampleport[123]   :    1734BF6C
bigdata2[4001024] :    1734C158
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    173B0164
dwaddr            :    173FB164
seq               :    173FB168
buf[187]          :    173FB16C
tax               :    173FB228
bigdata[3001024]  :    173FB22C
test              :    1744622C
samplenum         :    17446230
sampleport[123]   :    17446234
bigdata2[4001024] :    17446420
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    174AA42C
dwaddr            :    174F542C
seq               :    174F5430
buf[187]          :    174F5434
tax               :    174F54F0
bigdata[3001024]  :    174F54F4
test              :    175404F4
samplenum         :    175404F8
sampleport[123]   :    175404FC
bigdata2[4001024] :    175406E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    175A46F4
dwaddr            :    175EF6F4
seq               :    175EF6F8
buf[187]          :    175EF6FC
tax               :    175EF7B8
bigdata[3001024]  :    175EF7BC
test              :    1763A7BC
samplenum         :    1763A7C0
sampleport[123]   :    1763A7C4
bigdata2[4001024] :    1763A9B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1769E9BC
dwaddr            :    176E99BC
seq               :    176E99C0
buf[187]          :    176E99C4
tax               :    176E9A80
bigdata[3001024]  :    176E9A84
test              :    17734A84
samplenum         :    17734A88
sampleport[123]   :    17734A8C
bigdata2[4001024] :    17734C78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17798C84
dwaddr            :    177E3C84
seq               :    177E3C88
buf[187]          :    177E3C8C
tax               :    177E3D48
bigdata[3001024]  :    177E3D4C
test              :    1782ED4C
samplenum         :    1782ED50
sampleport[123]   :    1782ED54
bigdata2[4001024] :    1782EF40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17892F4C
dwaddr            :    178DDF4C
seq               :    178DDF50
buf[187]          :    178DDF54
tax               :    178DE010
bigdata[3001024]  :    178DE014
test              :    17929014
samplenum         :    17929018
sampleport[123]   :    1792901C
bigdata2[4001024] :    17929208
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1798D214
dwaddr            :    179D8214
seq               :    179D8218
buf[187]          :    179D821C
tax               :    179D82D8
bigdata[3001024]  :    179D82DC
test              :    17A232DC
samplenum         :    17A232E0
sampleport[123]   :    17A232E4
bigdata2[4001024] :    17A234D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17A874DC
dwaddr            :    17AD24DC
seq               :    17AD24E0
buf[187]          :    17AD24E4
tax               :    17AD25A0
bigdata[3001024]  :    17AD25A4
test              :    17B1D5A4
samplenum         :    17B1D5A8
sampleport[123]   :    17B1D5AC
bigdata2[4001024] :    17B1D798
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17B817A4
dwaddr            :    17BCC7A4
seq               :    17BCC7A8
buf[187]          :    17BCC7AC
tax               :    17BCC868
bigdata[3001024]  :    17BCC86C
test              :    17C1786C
samplenum         :    17C17870
sampleport[123]   :    17C17874
bigdata2[4001024] :    17C17A60
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17C7BA6C
dwaddr            :    17CC6A6C
seq               :    17CC6A70
buf[187]          :    17CC6A74
tax               :    17CC6B30
bigdata[3001024]  :    17CC6B34
test              :    17D11B34
samplenum         :    17D11B38
sampleport[123]   :    17D11B3C
bigdata2[4001024] :    17D11D28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17D75D34
dwaddr            :    17DC0D34
seq               :    17DC0D38
buf[187]          :    17DC0D3C
tax               :    17DC0DF8
bigdata[3001024]  :    17DC0DFC
test              :    17E0BDFC
samplenum         :    17E0BE00
sampleport[123]   :    17E0BE04
bigdata2[4001024] :    17E0BFF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17E6FFFC
dwaddr            :    17EBAFFC
seq               :    17EBB000
buf[187]          :    17EBB004
tax               :    17EBB0C0
bigdata[3001024]  :    17EBB0C4
test              :    17F060C4
samplenum         :    17F060C8
sampleport[123]   :    17F060CC
bigdata2[4001024] :    17F062B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17F6A2C4
dwaddr            :    17FB52C4
seq               :    17FB52C8
buf[187]          :    17FB52CC
tax               :    17FB5388
bigdata[3001024]  :    17FB538C
test              :    1800038C
samplenum         :    18000390
sampleport[123]   :    18000394
bigdata2[4001024] :    18000580
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1806458C
dwaddr            :    180AF58C
seq               :    180AF590
buf[187]          :    180AF594
tax               :    180AF650
bigdata[3001024]  :    180AF654
test              :    180FA654
samplenum         :    180FA658
sampleport[123]   :    180FA65C
bigdata2[4001024] :    180FA848
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1815E854
dwaddr            :    181A9854
seq               :    181A9858
buf[187]          :    181A985C
tax               :    181A9918
bigdata[3001024]  :    181A991C
test              :    181F491C
samplenum         :    181F4920
sampleport[123]   :    181F4924
bigdata2[4001024] :    181F4B10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18258B1C
dwaddr            :    182A3B1C
seq               :    182A3B20
buf[187]          :    182A3B24
tax               :    182A3BE0
bigdata[3001024]  :    182A3BE4
test              :    182EEBE4
samplenum         :    182EEBE8
sampleport[123]   :    182EEBEC
bigdata2[4001024] :    182EEDD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18352DE4
dwaddr            :    1839DDE4
seq               :    1839DDE8
buf[187]          :    1839DDEC
tax               :    1839DEA8
bigdata[3001024]  :    1839DEAC
test              :    183E8EAC
samplenum         :    183E8EB0
sampleport[123]   :    183E8EB4
bigdata2[4001024] :    183E90A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1844D0AC
dwaddr            :    184980AC
seq               :    184980B0
buf[187]          :    184980B4
tax               :    18498170
bigdata[3001024]  :    18498174
test              :    184E3174
samplenum         :    184E3178
sampleport[123]   :    184E317C
bigdata2[4001024] :    184E3368
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18547374
dwaddr            :    18592374
seq               :    18592378
buf[187]          :    1859237C
tax               :    18592438
bigdata[3001024]  :    1859243C
test              :    185DD43C
samplenum         :    185DD440
sampleport[123]   :    185DD444
bigdata2[4001024] :    185DD630
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1864163C
dwaddr            :    1868C63C
seq               :    1868C640
buf[187]          :    1868C644
tax               :    1868C700
bigdata[3001024]  :    1868C704
test              :    186D7704
samplenum         :    186D7708
sampleport[123]   :    186D770C
bigdata2[4001024] :    186D78F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1873B904
dwaddr            :    18786904
seq               :    18786908
buf[187]          :    1878690C
tax               :    187869C8
bigdata[3001024]  :    187869CC
test              :    187D19CC
samplenum         :    187D19D0
sampleport[123]   :    187D19D4
bigdata2[4001024] :    187D1BC0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18835BCC
dwaddr            :    18880BCC
seq               :    18880BD0
buf[187]          :    18880BD4
tax               :    18880C90
bigdata[3001024]  :    18880C94
test              :    188CBC94
samplenum         :    188CBC98
sampleport[123]   :    188CBC9C
bigdata2[4001024] :    188CBE88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1892FE94
dwaddr            :    1897AE94
seq               :    1897AE98
buf[187]          :    1897AE9C
tax               :    1897AF58
bigdata[3001024]  :    1897AF5C
test              :    189C5F5C
samplenum         :    189C5F60
sampleport[123]   :    189C5F64
bigdata2[4001024] :    189C6150
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18A2A15C
dwaddr            :    18A7515C
seq               :    18A75160
buf[187]          :    18A75164
tax               :    18A75220
bigdata[3001024]  :    18A75224
test              :    18AC0224
samplenum         :    18AC0228
sampleport[123]   :    18AC022C
bigdata2[4001024] :    18AC0418
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18B24424
dwaddr            :    18B6F424
seq               :    18B6F428
buf[187]          :    18B6F42C
tax               :    18B6F4E8
bigdata[3001024]  :    18B6F4EC
test              :    18BBA4EC
samplenum         :    18BBA4F0
sampleport[123]   :    18BBA4F4
bigdata2[4001024] :    18BBA6E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18C1E6EC
dwaddr            :    18C696EC
seq               :    18C696F0
buf[187]          :    18C696F4
tax               :    18C697B0
bigdata[3001024]  :    18C697B4
test              :    18CB47B4
samplenum         :    18CB47B8
sampleport[123]   :    18CB47BC
bigdata2[4001024] :    18CB49A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18D189B4
dwaddr            :    18D639B4
seq               :    18D639B8
buf[187]          :    18D639BC
tax               :    18D63A78
bigdata[3001024]  :    18D63A7C
test              :    18DAEA7C
samplenum         :    18DAEA80
sampleport[123]   :    18DAEA84
bigdata2[4001024] :    18DAEC70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18E12C7C
dwaddr            :    18E5DC7C
seq               :    18E5DC80
buf[187]          :    18E5DC84
tax               :    18E5DD40
bigdata[3001024]  :    18E5DD44
test              :    18EA8D44
samplenum         :    18EA8D48
sampleport[123]   :    18EA8D4C
bigdata2[4001024] :    18EA8F38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18F0CF44
dwaddr            :    18F57F44
seq               :    18F57F48
buf[187]          :    18F57F4C
tax               :    18F58008
bigdata[3001024]  :    18F5800C
test              :    18FA300C
samplenum         :    18FA3010
sampleport[123]   :    18FA3014
bigdata2[4001024] :    18FA3200
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1900720C
dwaddr            :    1905220C
seq               :    19052210
buf[187]          :    19052214
tax               :    190522D0
bigdata[3001024]  :    190522D4
test              :    1909D2D4
samplenum         :    1909D2D8
sampleport[123]   :    1909D2DC
bigdata2[4001024] :    1909D4C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191014D4
dwaddr            :    1914C4D4
seq               :    1914C4D8
buf[187]          :    1914C4DC
tax               :    1914C598
bigdata[3001024]  :    1914C59C
test              :    1919759C
samplenum         :    191975A0
sampleport[123]   :    191975A4
bigdata2[4001024] :    19197790
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191FB79C
dwaddr            :    1924679C
seq               :    192467A0
buf[187]          :    192467A4
tax               :    19246860
bigdata[3001024]  :    19246864
test              :    19291864
samplenum         :    19291868
sampleport[123]   :    1929186C
bigdata2[4001024] :    19291A58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    192F5A64
dwaddr            :    19340A64
seq               :    19340A68
buf[187]          :    19340A6C
tax               :    19340B28
bigdata[3001024]  :    19340B2C
test              :    1938BB2C
samplenum         :    1938BB30
sampleport[123]   :    1938BB34
bigdata2[4001024] :    1938BD20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    193EFD2C
dwaddr            :    1943AD2C
seq               :    1943AD30
buf[187]          :    1943AD34
tax               :    1943ADF0
bigdata[3001024]  :    1943ADF4
test              :    19485DF4
samplenum         :    19485DF8
sampleport[123]   :    19485DFC
bigdata2[4001024] :    19485FE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    194E9FF4
dwaddr            :    19534FF4
seq               :    19534FF8
buf[187]          :    19534FFC
tax               :    195350B8
bigdata[3001024]  :    195350BC
test              :    195800BC
samplenum         :    195800C0
sampleport[123]   :    195800C4
bigdata2[4001024] :    195802B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    195E42BC
dwaddr            :    1962F2BC
seq               :    1962F2C0
buf[187]          :    1962F2C4
tax               :    1962F380
bigdata[3001024]  :    1962F384
test              :    1967A384
samplenum         :    1967A388
sampleport[123]   :    1967A38C
bigdata2[4001024] :    1967A578
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    196DE584
dwaddr            :    19729584
seq               :    19729588
buf[187]          :    1972958C
tax               :    19729648
bigdata[3001024]  :    1972964C
test              :    1977464C
samplenum         :    19774650
sampleport[123]   :    19774654
bigdata2[4001024] :    19774840
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    197D884C
dwaddr            :    1982384C
seq               :    19823850
buf[187]          :    19823854
tax               :    19823910
bigdata[3001024]  :    19823914
test              :    1986E914
samplenum         :    1986E918
sampleport[123]   :    1986E91C
bigdata2[4001024] :    1986EB08
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    198D2B14
dwaddr            :    1991DB14
seq               :    1991DB18
buf[187]          :    1991DB1C
tax               :    1991DBD8
bigdata[3001024]  :    1991DBDC
test              :    19968BDC
samplenum         :    19968BE0
sampleport[123]   :    19968BE4
bigdata2[4001024] :    19968DD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    199CCDDC
dwaddr            :    19A17DDC
seq               :    19A17DE0
buf[187]          :    19A17DE4
tax               :    19A17EA0
bigdata[3001024]  :    19A17EA4
test              :    19A62EA4
samplenum         :    19A62EA8
sampleport[123]   :    19A62EAC
bigdata2[4001024] :    19A63098
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19AC70A4
dwaddr            :    19B120A4
seq               :    19B120A8
buf[187]          :    19B120AC
tax               :    19B12168
bigdata[3001024]  :    19B1216C
test              :    19B5D16C
samplenum         :    19B5D170
sampleport[123]   :    19B5D174
bigdata2[4001024] :    19B5D360
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19BC136C
dwaddr            :    19C0C36C
seq               :    19C0C370
buf[187]          :    19C0C374
tax               :    19C0C430
bigdata[3001024]  :    19C0C434
test              :    19C57434
samplenum         :    19C57438
sampleport[123]   :    19C5743C
bigdata2[4001024] :    19C57628
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19CBB634
dwaddr            :    19D06634
seq               :    19D06638
buf[187]          :    19D0663C
tax               :    19D066F8
bigdata[3001024]  :    19D066FC
test              :    19D516FC
samplenum         :    19D51700
sampleport[123]   :    19D51704
bigdata2[4001024] :    19D518F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19DB58FC
dwaddr            :    19E008FC
seq               :    19E00900
buf[187]          :    19E00904
tax               :    19E009C0
bigdata[3001024]  :    19E009C4
test              :    19E4B9C4
samplenum         :    19E4B9C8
sampleport[123]   :    19E4B9CC
bigdata2[4001024] :    19E4BBB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19EAFBC4
dwaddr            :    19EFABC4
seq               :    19EFABC8
buf[187]          :    19EFABCC
tax               :    19EFAC88
bigdata[3001024]  :    19EFAC8C
test              :    19F45C8C
samplenum         :    19F45C90
sampleport[123]   :    19F45C94
bigdata2[4001024] :    19F45E80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19FA9E8C
dwaddr            :    19FF4E8C
seq               :    19FF4E90
buf[187]          :    19FF4E94
tax               :    19FF4F50
bigdata[3001024]  :    19FF4F54
test              :    1A03FF54
samplenum         :    1A03FF58
sampleport[123]   :    1A03FF5C
bigdata2[4001024] :    1A040148
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A0A4154
dwaddr            :    1A0EF154
seq               :    1A0EF158
buf[187]          :    1A0EF15C
tax               :    1A0EF218
bigdata[3001024]  :    1A0EF21C
test              :    1A13A21C
samplenum         :    1A13A220
sampleport[123]   :    1A13A224
bigdata2[4001024] :    1A13A410
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A19E41C
dwaddr            :    1A1E941C
seq               :    1A1E9420
buf[187]          :    1A1E9424
tax               :    1A1E94E0
bigdata[3001024]  :    1A1E94E4
test              :    1A2344E4
samplenum         :    1A2344E8
sampleport[123]   :    1A2344EC
bigdata2[4001024] :    1A2346D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A2986E4
dwaddr            :    1A2E36E4
seq               :    1A2E36E8
buf[187]          :    1A2E36EC
tax               :    1A2E37A8
bigdata[3001024]  :    1A2E37AC
test              :    1A32E7AC
samplenum         :    1A32E7B0
sampleport[123]   :    1A32E7B4
bigdata2[4001024] :    1A32E9A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A3929AC
dwaddr            :    1A3DD9AC
seq               :    1A3DD9B0
buf[187]          :    1A3DD9B4
tax               :    1A3DDA70
bigdata[3001024]  :    1A3DDA74
test              :    1A428A74
samplenum         :    1A428A78
sampleport[123]   :    1A428A7C
bigdata2[4001024] :    1A428C68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A48CC74
dwaddr            :    1A4D7C74
seq               :    1A4D7C78
buf[187]          :    1A4D7C7C
tax               :    1A4D7D38
bigdata[3001024]  :    1A4D7D3C
test              :    1A522D3C
samplenum         :    1A522D40
sampleport[123]   :    1A522D44
bigdata2[4001024] :    1A522F30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A586F3C
dwaddr            :    1A5D1F3C
seq               :    1A5D1F40
buf[187]          :    1A5D1F44
tax               :    1A5D2000
bigdata[3001024]  :    1A5D2004
test              :    1A61D004
samplenum         :    1A61D008
sampleport[123]   :    1A61D00C
bigdata2[4001024] :    1A61D1F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A875794
dwaddr            :    1A8C0794
seq               :    1A8C0798
buf[187]          :    1A8C079C
tax               :    1A8C0858
bigdata[3001024]  :    1A8C085C
test              :    1A90B85C
samplenum         :    1A90B860
sampleport[123]   :    1A90B864
bigdata2[4001024] :    1A90BA50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A96FA5C
dwaddr            :    1A9BAA5C
seq               :    1A9BAA60
buf[187]          :    1A9BAA64
tax               :    1A9BAB20
bigdata[3001024]  :    1A9BAB24
test              :    1AA05B24
samplenum         :    1AA05B28
sampleport[123]   :    1AA05B2C
bigdata2[4001024] :    1AA05D18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1AF4CB0C
dwaddr            :    1AF97B0C
seq               :    1AF97B10
buf[187]          :    1AF97B14
tax               :    1AF97BD0
bigdata[3001024]  :    1AF97BD4
test              :    1AFE2BD4
samplenum         :    1AFE2BD8
sampleport[123]   :    1AFE2BDC
bigdata2[4001024] :    1AFE2DC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B42F8F4
dwaddr            :    1B47A8F4
seq               :    1B47A8F8
buf[187]          :    1B47A8FC
tax               :    1B47A9B8
bigdata[3001024]  :    1B47A9BC
test              :    1B4C59BC
samplenum         :    1B4C59C0
sampleport[123]   :    1B4C59C4
bigdata2[4001024] :    1B4C5BB0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B623E84
dwaddr            :    1B66EE84
seq               :    1B66EE88
buf[187]          :    1B66EE8C
tax               :    1B66EF48
bigdata[3001024]  :    1B66EF4C
test              :    1B6B9F4C
samplenum         :    1B6B9F50
sampleport[123]   :    1B6B9F54
bigdata2[4001024] :    1B6BA140
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B818414
dwaddr            :    1B863414
seq               :    1B863418
buf[187]          :    1B86341C
tax               :    1B8634D8
bigdata[3001024]  :    1B8634DC
test              :    1B8AE4DC
samplenum         :    1B8AE4E0
sampleport[123]   :    1B8AE4E4
bigdata2[4001024] :    1B8AE6D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BC00F34
dwaddr            :    1BC4BF34
seq               :    1BC4BF38
buf[187]          :    1BC4BF3C
tax               :    1BC4BFF8
bigdata[3001024]  :    1BC4BFFC
test              :    1BC96FFC
samplenum         :    1BC97000
sampleport[123]   :    1BC97004
bigdata2[4001024] :    1BC971F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BDF54C4
dwaddr            :    1BE404C4
seq               :    1BE404C8
buf[187]          :    1BE404CC
tax               :    1BE40588
bigdata[3001024]  :    1BE4058C
test              :    1BE8B58C
samplenum         :    1BE8B590
sampleport[123]   :    1BE8B594
bigdata2[4001024] :    1BE8B780
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BFE9A54
dwaddr            :    1C034A54
seq               :    1C034A58
buf[187]          :    1C034A5C
tax               :    1C034B18
bigdata[3001024]  :    1C034B1C
test              :    1C07FB1C
samplenum         :    1C07FB20
sampleport[123]   :    1C07FB24
bigdata2[4001024] :    1C07FD10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1C2D82AC
dwaddr            :    1C3232AC
seq               :    1C3232B0
buf[187]          :    1C3232B4
tax               :    1C323370
bigdata[3001024]  :    1C323374
test              :    1C36E374
samplenum         :    1C36E378
sampleport[123]   :    1C36E37C
bigdata2[4001024] :    1C36E568
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CE9240C
dwaddr            :    1CEDD40C
seq               :    1CEDD410
buf[187]          :    1CEDD414
tax               :    1CEDD4D0
bigdata[3001024]  :    1CEDD4D4
test              :    1CF284D4
samplenum         :    1CF284D8
sampleport[123]   :    1CF284DC
bigdata2[4001024] :    1CF286C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CF8C6D4
dwaddr            :    1CFD76D4
seq               :    1CFD76D8
buf[187]          :    1CFD76DC
tax               :    1CFD7798
bigdata[3001024]  :    1CFD779C
test              :    1D02279C
samplenum         :    1D0227A0
sampleport[123]   :    1D0227A4
bigdata2[4001024] :    1D022990
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D08699C
dwaddr            :    1D0D199C
seq               :    1D0D19A0
buf[187]          :    1D0D19A4
tax               :    1D0D1A60
bigdata[3001024]  :    1D0D1A64
test              :    1D11CA64
samplenum         :    1D11CA68
sampleport[123]   :    1D11CA6C
bigdata2[4001024] :    1D11CC58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D9522A4
dwaddr            :    1D99D2A4
seq               :    1D99D2A8
buf[187]          :    1D99D2AC
tax               :    1D99D368
bigdata[3001024]  :    1D99D36C
test              :    1D9E836C
samplenum         :    1D9E8370
sampleport[123]   :    1D9E8374
bigdata2[4001024] :    1D9E8560
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DB46834
dwaddr            :    1DB91834
seq               :    1DB91838
buf[187]          :    1DB9183C
tax               :    1DB918F8
bigdata[3001024]  :    1DB918FC
test              :    1DBDC8FC
samplenum         :    1DBDC900
sampleport[123]   :    1DBDC904
bigdata2[4001024] :    1DBDCAF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DC40AFC
dwaddr            :    1DC8BAFC
seq               :    1DC8BB00
buf[187]          :    1DC8BB04
tax               :    1DC8BBC0
bigdata[3001024]  :    1DC8BBC4
test              :    1DCD6BC4
samplenum         :    1DCD6BC8
sampleport[123]   :    1DCD6BCC
bigdata2[4001024] :    1DCD6DB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E21DBAC
dwaddr            :    1E268BAC
seq               :    1E268BB0
buf[187]          :    1E268BB4
tax               :    1E268C70
bigdata[3001024]  :    1E268C74
test              :    1E2B3C74
samplenum         :    1E2B3C78
sampleport[123]   :    1E2B3C7C
bigdata2[4001024] :    1E2B3E68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E50C404
dwaddr            :    1E557404
seq               :    1E557408
buf[187]          :    1E55740C
tax               :    1E5574C8
bigdata[3001024]  :    1E5574CC
test              :    1E5A24CC
samplenum         :    1E5A24D0
sampleport[123]   :    1E5A24D4
bigdata2[4001024] :    1E5A26C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E7FAC5C
dwaddr            :    1E845C5C
seq               :    1E845C60
buf[187]          :    1E845C64
tax               :    1E845D20
bigdata[3001024]  :    1E845D24
test              :    1E890D24
samplenum         :    1E890D28
sampleport[123]   :    1E890D2C
bigdata2[4001024] :    1E890F18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E9EF1EC
dwaddr            :    1EA3A1EC
seq               :    1EA3A1F0
buf[187]          :    1EA3A1F4
tax               :    1EA3A2B0
bigdata[3001024]  :    1EA3A2B4
test              :    1EA852B4
samplenum         :    1EA852B8
sampleport[123]   :    1EA852BC
bigdata2[4001024] :    1EA854A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1EDD7D0C
dwaddr            :    1EE22D0C
seq               :    1EE22D10
buf[187]          :    1EE22D14
tax               :    1EE22DD0
bigdata[3001024]  :    1EE22DD4
test              :    1EE6DDD4
samplenum         :    1EE6DDD8
sampleport[123]   :    1EE6DDDC
bigdata2[4001024] :    1EE6DFC8
hash show
No hash1    hash2     hash3    valueaddr
255 0x0        0x0        0x0        0x1f0c6564
254 0x0        0x0        0x0        0x1efcc29c
253 0x0        0x0        0x0        0x1eed1fd4
252 0x720752fc 0x2e6526c  0x7e325c42 0x1edd7d0c (data)
251 0x0        0x0        0x0        0x1ecdda44
250 0x0        0x0        0x0        0x1ebe377c
249 0x0        0x0        0x0        0x1eae94b4
248 0xdc63b7f8 0x2052961a 0x76f37377 0x1e9ef1ec (data)
247 0x0        0x0        0x0        0x1e8f4f24
246 0x81d59cf6 0xab7ebcba 0xe5b79834 0x1e7fac5c (data)
245 0x0        0x0        0x0        0x1e700994
244 0x0        0x0        0x0        0x1e6066cc
243 0x75571df3 0xda01101d 0x28af836d 0x1e50c404 (data)
242 0x0        0x0        0x0        0x1e41213c
241 0x0        0x0        0x0        0x1e317e74
240 0x1ae3f5f0 0x65b3d5b1 0x5e3d633b 0x1e21dbac (data)
239 0x0        0x0        0x0        0x1e1238e4
238 0x0        0x0        0x0        0x1e02961c
237 0x0        0x0        0x0        0x1df2f354
236 0x0        0x0        0x0        0x1de3508c
235 0x0        0x0        0x0        0x1dd3adc4
234 0x709391ea 0x4bf5a4ca 0xbb374f06 0x1dc40afc (data)
233 0xfc8524e9 0xaa4a697a 0x545895b0 0x1db46834 (data)
232 0x0        0x0        0x0        0x1da4c56c
231 0x10582ce7 0x73994279 0x1f213222 0x1d9522a4 (data)
230 0x0        0x0        0x0        0x1d857fdc
229 0x0        0x0        0x0        0x1d75dd14
228 0x0        0x0        0x0        0x1d663a4c
227 0x0        0x0        0x0        0x1d569784
226 0x0        0x0        0x0        0x1d46f4bc
225 0x0        0x0        0x0        0x1d3751f4
224 0x0        0x0        0x0        0x1d27af2c
223 0x0        0x0        0x0        0x1d180c64
222 0x8930f5de 0x34a9f12e 0x397bd808 0x1d08699c (data)
221 0x2a1252dd 0x1d31f9b4 0xbae26aeb 0x1cf8c6d4 (data)
220 0xd095adc  0x8a2f5df0 0x520d40e3 0x1ce9240c (data)
219 0x0        0x0        0x0        0x1cd98144
218 0x0        0x0        0x0        0x1cc9de7c
217 0x0        0x0        0x0        0x1cba3bb4
216 0x0        0x0        0x0        0x1caa98ec
215 0x0        0x0        0x0        0x1c9af624
214 0x0        0x0        0x0        0x1c8b535c
213 0x0        0x0        0x0        0x1c7bb094
212 0x0        0x0        0x0        0x1c6c0dcc
211 0x0        0x0        0x0        0x1c5c6b04
210 0x0        0x0        0x0        0x1c4cc83c
209 0x0        0x0        0x0        0x1c3d2574
208 0xefa929d0 0x8ae4dc74 0x55fa180e 0x1c2d82ac (data)
207 0x0        0x0        0x0        0x1c1ddfe4
206 0x0        0x0        0x0        0x1c0e3d1c
205 0xe492d7cd 0x9e4bdc50 0x293d4c00 0x1bfe9a54 (data)
204 0x0        0x0        0x0        0x1beef78c
203 0x7b283cb  0x9c05ca38 0x131111fa 0x1bdf54c4 (data)
202 0x0        0x0        0x0        0x1bcfb1fc
201 0x838b2cc9 0x228366e6 0x78678911 0x1bc00f34 (data)
200 0x0        0x0        0x0        0x1bb06c6c
199 0x0        0x0        0x0        0x1ba0c9a4
198 0x0        0x0        0x0        0x1b9126dc
197 0xeb6f8bc5 0x45d6e13b 0x5868b668 0x1b818414 (data)
196 0x0        0x0        0x0        0x1b71e14c
195 0x1cd7d2c3 0xb6a63bd7 0xe936128a 0x1b623e84 (data)
194 0x0        0x0        0x0        0x1b529bbc
193 0xdb545fc1 0xfdbae1c4 0xe462bdd9 0x1b42f8f4 (data)
192 0x0        0x0        0x0        0x1b33562c
191 0x0        0x0        0x0        0x1b23b364
190 0x0        0x0        0x0        0x1b14109c
189 0x0        0x0        0x0        0x1b046dd4
188 0xf3f152bc 0xcde66c2d 0x81235657 0x1af4cb0c (data)
187 0x0        0x0        0x0        0x1ae52844
186 0x0        0x0        0x0        0x1ad5857c
185 0x0        0x0        0x0        0x1ac5e2b4
184 0x0        0x0        0x0        0x1ab63fec
183 0x0        0x0        0x0        0x1aa69d24
182 0x2f178eb6 0xac5947d1 0x7650fa74 0x1a96fa5c (data)
181 0x8c3529b5 0x85c14f4b 0xf5c94897 0x1a875794 (data)
180 0x0        0x0        0x0        0x1a77b4cc
179 0x0        0x0        0x0        0x1a681204
178 0x2896c530 0xafce8752 0x7da85db0 0x1a586f3c (data)
177 0x8d7b3cb1 0x51d4ef6d 0x9b454e69 0x1a48cc74 (data)
176 0xbeb1a299 0xfb62a503 0xb84c2510 0x1a3929ac (data)
175 0x72170607 0xf90ada2c 0x7c7d785d 0x1a2986e4 (data)
174 0xb1c275ae 0x99233845 0x207b334b 0x1a19e41c (data)
173 0x4d58a456 0x26cadf84 0x150cb00b 0x1a0a4154 (data)
172 0x5ab20b7a 0xc95657c5 0x193c93d3 0x19fa9e8c (data)
171 0xd4307d6f 0x61fa6cd3 0x33565a21 0x19eafbc4 (data)
170 0xd832e831 0xe8a3671  0x6aed428e 0x19db58fc (data)
169 0x7d7324a9 0x654a573b 0xab499fa5 0x19cbb634 (data)
168 0x4dd62f69 0x9f167fa9 0xfc6e5c38 0x19bc136c (data)
167 0xdc13e557 0xdb5cb3e4 0xfdfc9355 0x19ac70a4 (data)
166 0x8ea1eaa3 0xccd2b9ed 0x30cc5bd3 0x199ccddc (data)
165 0x18f6dfa5 0x6370be42 0x7e27c351 0x198d2b14 (data)
164 0x18868d0a 0x987e9bbc 0xf5282373 0x197d884c (data)
163 0x499e0643 0xe9f8e2cb 0x189e1e6d 0x196de584 (data)
162 0xd4202994 0x9a16e493 0x31197e3e 0x195e42bc (data)
161 0x25ac57a1 0xba73d019 0x374cab6d 0x194e9ff4 (data)
160 0x2b75fa0  0x2d6d745d 0xdfa38165 0x193efd2c (data)
159 0xd7469e64 0x69263326 0xbf968169 0x192f5a64 (data)
158 0x42a2593c 0xf8ba7afe 0x29159fdf 0x191fb79c (data)
157 0xd3679302 0xbcf0b6b3 0x288750b2 0x191014d4 (data)
156 0x17f2fb5f 0xffd29eeb 0x2053e094 0x1900720c (data)
155 0x8933159b 0x273a720f 0x7fb50c3c 0x18f0cf44 (data)
154 0x46ea7016 0x8e54e79c 0xcde5dd8a 0x18e12c7c (data)
153 0xe41bfd90 0x227ae46c 0x8d13758f 0x18d189b4 (data)
152 0x4a44d051 0x74feb44b 0xb3170bd7 0x18c1e6ec (data)
151 0x10c51366 0x223ae935 0xb2c22e3a 0x18b24424 (data)
150 0x7f2d9496 0xecb78d67 0x36998e80 0x18a2a15c (data)
149 0x71761095 0xfd79588  0xbfbe52b6 0x1892fe94 (data)
148 0x2f8ab137 0xfdfaec9d 0xdbb3e66c 0x18835bcc (data)
147 0x38601e1b 0x126664dc 0xd783c5b4 0x1873b904 (data)
146 0xb6e2680e 0xbaca5fca 0xfde90c46 0x1864163c (data)
145 0x26009378 0x89ad2b56 0xe116565b 0x18547374 (data)
144 0xb3e45420 0x1831628e 0x779548ed 0x1844d0ac (data)
143 0x22219e1e 0x5c7baec3 0x76078780 0x18352de4 (data)
142 0xe6b4f643 0x1f59869b 0x7ed337a6 0x18258b1c (data)
141 0xb7ac7d0a 0x6edfffec 0x93650ab8 0x1815e854 (data)
140 0x155df08c 0xc2f1fc1c 0xd393a2bd 0x1806458c (data)
139 0x23054f13 0x38c59533 0x2da4c6c4 0x17f6a2c4 (data)
138 0xb6e1884b 0xa959dceb 0xbb27d872 0x17e6fffc (data)
137 0x27244275 0xed1310a6 0xbab5171f 0x17d75d34 (data)
136 0x75964d81 0xfa9d1aaf 0x7785df99 0x17c7ba6c (data)
135 0xe3b12a28 0xae3138fe 0xb261a739 0x17b817a4 (data)
134 0xb2a9a161 0xdfb74189 0x5fd79a27 0x17a874dc (data)
133 0x29be9604 0x2eef02fb 0x6cb897dd 0x1798d214 (data)
132 0xbc5a515c 0xbf734b23 0xfa3b896b 0x17892f4c (data)
131 0x2d9f9b62 0xfb39876e 0xfba94606 0x17798c84 (data)
130 0xe90af33f 0xb81baf36 0xf37df620 0x1769e9bc (data)
129 0xb8127876 0xc99dd641 0x1ecbcb3e 0x175a46f4 (data)
128 0x27e51207 0xcd8f1a14 0xe59f4beb 0x174aa42c (data)
127 0xe12e73ff 0x97244af4 0x9f157f4a 0x173b0164 (data)
126 0xd148c97d 0x1088d3da 0x255f91f0 0x172b5e9c (data)
125 0x806627d  0xeb04dbc8 0x77d1de10 0x171bbbd4 (data)
124 0xe0dafee7 0xe8a54132 0xcdcd0e55 0x170c190c (data)
123 0x7d64d130 0x9b4b476a 0xe44a6e06 0x16fc7644 (data)
122 0x422b7361 0x448b42c2 0x8d3ba650 0x16ecd37c (data)
121 0x55c1dc4d 0xab17ca83 0x810b8588 0x16dd30b4 (data)
120 0xfc445f78 0xc65842f9 0xd314c962 0x16cd8dec (data)
119 0xdb43aa58 0x3bbf195  0xab614c7a 0x16bdeb24 (data)
118 0x11fcac46 0x867c7e17 0xba9af00d 0x16ae485c (data)
117 0x9ab66bf5 0x61086ff2 0xad93b755 0x169ea594 (data)
116 0x84186b1e 0x17e037cf 0x2c19eebb 0x168f02cc (data)
115 0x15dda120 0x53aafb82 0x2d8b21d6 0x167f6004 (data)
114 0x5cad11f2 0xa134761b 0x14a57fb2 0x166fbd3c (data)
113 0x476faed4 0x4424f18b 0xe0bbe950 0x16601a74 (data)
112 0x80504234 0x610eaaad 0xc8e9acee 0x165077ac (data)
111 0x5e9560ef 0x295c5454 0x2df0c74d 0x1640d4e4 (data)
110 0x1dee6de3 0x12e0acf5 0xe16eccbd 0x1631321c (data)
109 0x22a1cfb2 0xcd20a95d 0x881f04eb 0x16218f54 (data)
108 0x354b609e 0x22bc211c 0x842f2733 0x1611ec8c (data)
107 0xbbc9168b 0x8a101a0a 0xae45eec1 0x160249c4 (data)
106 0xaad75dea 0x400cd65  0x8935d03f 0x15f2a6fc (data)
105 0x637c6c67 0x3cc45bde 0x96f97fc8 0x15e30434 (data)
104 0xd22f67e7 0x9984d0d  0x3ecfb640 0x15d3616c (data)
103 0xcc256967 0xa350e06e 0xf7b2ae08 0x15c3bea4 (data)
102 0xf698ab3f 0xad581206 0x7a617e   0x15b41bdc (data)
101 0xf2b9a659 0x788e9793 0x976bb0a5 0x15a47914 (data)
100 0xa00ba9ad 0x6f009d9a 0x5a5b7823 0x1594d64c (data)
99  0x362cce04 0x3bacbfcb 0x9fbf0083 0x15853384 (data)
98  0x6734454d 0x4a2ac6bc 0x72093d9d 0x157590bc (data)
97  0x2d88d761 0x954c35db 0x5b242207 0x1565edf4 (data)
96  0xfa8a6a9a 0x39c4c0e4 0x5b8e5dce 0x15564b2c (data)
95  0xc5c5c8cb 0xe604c54c 0x32ff9598 0x1546a864 (data)
94  0x3f339ab2 0x959c84bd 0x1fb6ce89 0x1537059c (data)
93  0xaef6508c 0xd1d648f0 0x1e2401e4 0x152762d4 (data)
92  0xc910c5c  0x35a44da3 0x6877cff5 0x1517c00c (data)
91  0x6a6338d1 0x92f460a8 0x16f0b1c2 0x15081d44 (data)
90  0x3b7bb398 0xe37219df 0xfb468cdc 0x14f87a7c (data)
89  0xa6c59c4f 0x909c1f87 0xd2c1ec8f 0x14e8d7b4 (data)
88  0x414a3d8  0x7f98092a 0x2c25e2a0 0x14d934ec (data)
87  0x998a3e1e 0x4f5c1a2f 0xbbb024d9 0x14c99224 (data)
86  0x77091456 0xc38868a5 0x5af107ea 0x14b9ef5c (data)
85  0x8e609132 0xa0c0926e 0xb7800701 0x14aa4c94 (data)
84  0xe2e727   0x86ca978  0x9deacef3 0x149aa9cc (data)
83  0x9de2a525 0x7a989210 0xe152c0a6 0x148b0704 (data)
82  0xc276f1b  0x3ed25e5d 0xe0c00fcb 0x147b643c (data)
81  0xc8b20746 0x7df07605 0xe814bfed 0x146bc174 (data)
80  0x99aa8c0f 0xc760f72  0x5a282f3  0x145c1eac (data)
79  0x3b5b0189 0xa0580c82 0x45542af6 0x144c7be4 (data)
78  0x2cb1aea5 0x4fc484c3 0x4964092e 0x143cd91c (data)
77  0xa233d8b0 0xe768bfd5 0x630ec0dc 0x142d3654 (data)
76  0x219a16c4 0x1d0e739  0xd01eb7   0x141d938c (data)
75  0xb47ed19c 0x904caee1 0x96530001 0x140df0c4 (data)
74  0x25bb1ba2 0xd40662ac 0x97c1cf6c 0x13fe4dfc (data)
73  0xb036f8b6 0xe6a23383 0x72a34254 0x13eeab34 (data)
72  0x12c77530 0x4a8c3073 0x3255ea51 0x13df086c (data)
71  0x52dda1c  0xa510b832 0x3e65c989 0x13cf65a4 (data)
70  0x8bafac09 0xdbc8324  0x140f007b 0x13bfc2dc (data)
69  0x59c1ae3f 0x32cca9b6 0x6131b0be 0x13b02014 (data)
68  0xc8046401 0x768665fb 0x60a37fd3 0x13a07d4c (data)
67  0x5d898715 0x442234d4 0x85c1f2eb 0x1390da84 (data)
66  0xc037a8c2 0x37cc328c 0xac4692b8 0x138137bc (data)
65  0xff780a93 0xe80c3724 0xc5375aee 0x137194f4 (data)
64  0xe892a5bf 0x790bf65  0xc9077936 0x1361f22c (data)
63  0x84432d3e 0xa2377f71 0x9573f4e4 0x13524f64 (data)
62  0x0        0x0        0x0        0x1342ac9c
61  0x6610d3aa 0xaf3c8473 0xe36db0c4 0x133309d4 (data)
60  0x0        0x0        0x0        0x1323670c
59  0xd2d02fac 0x606ff0ed 0xcf52edb9 0x1313c444 (data)
58  0x0        0x0        0x0        0x1304217c
57  0x0        0x0        0x0        0x12f47eb4
56  0x4734e8f4 0xf1f3b935 0x59d1f30f 0x12e4dbec (data)
55  0xd6f122ca 0xb5b97578 0x58433c62 0x12d53924 (data)
54  0x12644a97 0xf69b5d20 0x50978c44 0x12c5965c (data)
53  0xf667e374 0xc4afafe6 0xf1e73a87 0x12b5f394 (data)
52  0xfdd7dbf3 0x3137bb0e 0xbb665252 0x12a650cc (data)
51  0x0        0x0        0x0        0x1296ae04
50  0x437cc1de 0x871d2457 0xbd21b15a 0x12870b3c (data)
49  0xdec2ee09 0xf4f3220f 0x94a6d109 0x12776874 (data)
48  0xe18d4c58 0x2b3327a7 0xfdd7195f 0x1267c5ac (data)
47  0x78e59561 0x6c0394f0 0xdb8df375 0x125822e4 (data)
46  0x0        0x0        0x0        0x1248801c
45  0x0        0x0        0x0        0x1238dd54
44  0x68331cab 0xa0abf2d6 0x2de54ce4 0x12293a8c (data)
43  0x0        0x0        0x0        0x121997c4
42  0xf9f6d695 0xe4e13e9b 0x2c778389 0x1209f4fc (data)
41  0x0        0x0        0x0        0x11fa5234
40  0x0        0x0        0x0        0x11eaaf6c
39  0x0        0x0        0x0        0x11db0ca4
38  0x0        0x0        0x0        0x11cb69dc
37  0x0        0x0        0x0        0x11bbc714
36  0x0        0x0        0x0        0x11ac244c
35  0x0        0x0        0x0        0x119c8184
34  0x0        0x0        0x0        0x118cdebc
33  0x0        0x0        0x0        0x117d3bf4
32  0x0        0x0        0x0        0x116d992c
31  0x0        0x0        0x0        0x115df664
30  0x0        0x0        0x0        0x114e539c
29  0x0        0x0        0x0        0x113eb0d4
28  0x0        0x0        0x0        0x112f0e0c
27  0x0        0x0        0x0        0x111f6b44
26  0x0        0x0        0x0        0x110fc87c
25  0x0        0x0        0x0        0x110025b4
24  0x0        0x0        0x0        0x10f082ec
23  0x0        0x0        0x0        0x10e0e024
22  0x0        0x0        0x0        0x10d13d5c
21  0x0        0x0        0x0        0x10c19a94
20  0x0        0x0        0x0        0x10b1f7cc
19  0x0        0x0        0x0        0x10a25504
18  0x0        0x0        0x0        0x1092b23c
17  0x0        0x0        0x0        0x10830f74
16  0x0        0x0        0x0        0x10736cac
15  0x0        0x0        0x0        0x1063c9e4
14  0x0        0x0        0x0        0x1054271c
13  0x0        0x0        0x0        0x10448454
12  0x0        0x0        0x0        0x1034e18c
11  0x0        0x0        0x0        0x10253ec4
10  0x0        0x0        0x0        0x10159bfc
9   0x0        0x0        0x0        0x1005f934
8   0x0        0x0        0x0        0xff6566c
7   0x0        0x0        0x0        0xfe6b3a4
6   0x0        0x0        0x0        0xfd710dc
5   0x0        0x0        0x0        0xfc76e14
4   0x0        0x0        0x0        0xfb7cb4c
3   0x0        0x0        0x0        0xfa82884
2   0x0        0x0        0x0        0xf9885bc
1   0x0        0x0        0x0        0xf88e2f4
0   0x0        0x0        0x0        0xf79402c
hash size:150
after get method again, hash size:150
hash key!!
No pInfo  dwaddr seq  tax  buf (iter)
1   0x1209f4fc 0x133  51  50.00  0x50
2   0x12293a8c 0x134  52  51.00  0x51
3   0x125822e4 0x136  54  53.00  0x53
4   0x1267c5ac 0x138  56  55.00  0x55
5   0x12776874 0x139  57  56.00  0x56
6   0x12870b3c 0x13a  58  57.00  0x57
7   0x12a650cc 0x135  53  52.00  0x52
8   0x12b5f394 0x137  55  54.00  0x54
9   0x12c5965c 0x13b  59  58.00  0x58
10  0x12d53924 0x13d  61  60.00  0x60
11  0x12e4dbec 0x13e  62  61.00  0x61
12  0x1313c444 0x13f  63  62.00  0x62
13  0x133309d4 0x140  64  63.00  0x63
14  0x13524f64 0x13c  60  59.00  0x59
15  0x1361f22c 0x141  65  64.00  0x64
16  0x137194f4 0x142  66  65.00  0x65
17  0x138137bc 0x143  67  66.00  0x66
18  0x1390da84 0x144  68  67.00  0x67
19  0x13a07d4c 0x147  71  70.00  0x70
20  0x13b02014 0x148  72  71.00  0x71
21  0x13bfc2dc 0x14a  74  73.00  0x73
22  0x13cf65a4 0x14b  75  74.00  0x74
23  0x13df086c 0x14c  76  75.00  0x75
24  0x13eeab34 0x14e  78  77.00  0x77
25  0x13fe4dfc 0x151  81  80.00  0x80
26  0x140df0c4 0x152  82  81.00  0x81
27  0x141d938c 0x153  83  82.00  0x82
28  0x142d3654 0x154  84  83.00  0x83
29  0x143cd91c 0x155  85  84.00  0x84
30  0x144c7be4 0x156  86  85.00  0x85
31  0x145c1eac 0x158  88  87.00  0x87
32  0x146bc174 0x159  89  88.00  0x88
33  0x147b643c 0x15b  91  90.00  0x90
34  0x148b0704 0x15c  92  91.00  0x91
35  0x149aa9cc 0x15e  94  93.00  0x93
36  0x14aa4c94 0x15f  95  94.00  0x94
37  0x14b9ef5c 0x150  80  79.00  0x79
38  0x14c99224 0x160  96  95.00  0x95
39  0x14d934ec 0x157  87  86.00  0x86
40  0x14e8d7b4 0x161  97  96.00  0x96
41  0x14f87a7c 0x162  98  97.00  0x97
42  0x15081d44 0x163  99  98.00  0x98
43  0x1517c00c 0x145  69  68.00  0x68
44  0x152762d4 0x165  101 100.00 0x100
45  0x1537059c 0x166  102 101.00 0x101
46  0x1546a864 0x16a  106 105.00 0x105
47  0x15564b2c 0x16b  107 106.00 0x106
48  0x1565edf4 0x14d  77  76.00  0x76
49  0x157590bc 0x16c  108 107.00 0x107
50  0x15853384 0x16d  109 108.00 0x108
51  0x1594d64c 0x16e  110 109.00 0x109
52  0x15a47914 0x16f  111 110.00 0x110
53  0x15b41bdc 0x171  113 112.00 0x112
54  0x15c3bea4 0x149  73  72.00  0x72
55  0x15d3616c 0x169  105 104.00 0x104
56  0x15e30434 0x170  112 111.00 0x111
57  0x15f2a6fc 0x167  103 102.00 0x102
58  0x160249c4 0x172  114 113.00 0x113
59  0x1611ec8c 0x173  115 114.00 0x114
60  0x16218f54 0x174  116 115.00 0x115
61  0x1631321c 0x175  117 116.00 0x116
62  0x1640d4e4 0x15a  90  89.00  0x89
63  0x165077ac 0x176  118 117.00 0x117
64  0x16601a74 0x178  120 119.00 0x119
65  0x166fbd3c 0x168  104 103.00 0x103
66  0x167f6004 0x179  121 120.00 0x120
67  0x168f02cc 0x17a  122 121.00 0x121
68  0x169ea594 0x146  70  69.00  0x69
69  0x16ae485c 0x17b  123 122.00 0x122
70  0x16bdeb24 0x17c  124 123.00 0x123
71  0x16cd8dec 0x164  100 99.00  0x99
72  0x16dd30b4 0x17d  125 124.00 0x124
73  0x16ecd37c 0x17e  126 125.00 0x125
74  0x16fc7644 0x17f  127 126.00 0x126
75  0x170c190c 0x180  128 127.00 0x127
76  0x171bbbd4 0x15d  93  92.00  0x92
77  0x172b5e9c 0x177  119 118.00 0x118
78  0x173b0164 0x14f  79  78.00  0x78
79  0x174aa42c 0x182  130 129.00 0x129
80  0x175a46f4 0x18a  138 137.00 0x137
81  0x1769e9bc 0x18b  139 138.00 0x138
82  0x17798c84 0x18d  141 140.00 0x140
83  0x17892f4c 0x18e  142 141.00 0x141
84  0x1798d214 0x18f  143 142.00 0x142
85  0x17a874dc 0x194  148 147.00 0x147
86  0x17b817a4 0x195  149 148.00 0x148
87  0x17c7ba6c 0x196  150 149.00 0x149
88  0x17d75d34 0x197  151 150.00 0x150
89  0x17e6fffc 0x198  152 151.00 0x151
90  0x17f6a2c4 0x199  153 152.00 0x152
91  0x1806458c 0x19c  156 155.00 0x155
92  0x1815e854 0x19e  158 157.00 0x157
93  0x18258b1c 0x19f  159 158.00 0x158
94  0x18352de4 0x1a1  161 160.00 0x160
95  0x1844d0ac 0x1a2  162 161.00 0x161
96  0x18547374 0x1a3  163 162.00 0x162
97  0x1864163c 0x1a4  164 163.00 0x163
98  0x1873b904 0x1a5  165 164.00 0x164
99  0x18835bcc 0x1a6  166 165.00 0x165
100 0x1892fe94 0x185  133 132.00 0x132
101 0x18a2a15c 0x18c  140 139.00 0x139
102 0x18b24424 0x1a7  167 166.00 0x166
103 0x18c1e6ec 0x1aa  170 169.00 0x169
104 0x18d189b4 0x1b0  176 175.00 0x175
105 0x18e12c7c 0x1b2  178 177.00 0x177
106 0x18f0cf44 0x1ac  172 171.00 0x171
107 0x1900720c 0x1b3  179 178.00 0x178
108 0x191014d4 0x1b5  181 180.00 0x180
109 0x191fb79c 0x1b6  182 181.00 0x181
110 0x192f5a64 0x1b7  183 182.00 0x182
111 0x193efd2c 0x19b  155 154.00 0x154
112 0x194e9ff4 0x189  137 136.00 0x136
113 0x195e42bc 0x1bb  187 186.00 0x186
114 0x196de584 0x1bc  188 187.00 0x187
115 0x197d884c 0x1bd  189 188.00 0x188
116 0x198d2b14 0x1ab  171 170.00 0x170
117 0x199ccddc 0x1be  190 189.00 0x189
118 0x19ac70a4 0x1bf  191 190.00 0x190
119 0x19bc136c 0x1c0  192 191.00 0x191
120 0x19cbb634 0x1ae  174 173.00 0x173
121 0x19db58fc 0x1c1  193 192.00 0x192
122 0x19eafbc4 0x1c2  194 193.00 0x193
123 0x19fa9e8c 0x1c3  195 194.00 0x194
124 0x1a0a4154 0x1c4  196 195.00 0x195
125 0x1a19e41c 0x181  129 128.00 0x128
126 0x1a2986e4 0x1c5  197 196.00 0x196
127 0x1a3929ac 0x1c7  199 198.00 0x198
128 0x1a48cc74 0x1a8  168 167.00 0x167
129 0x1a586f3c 0x1c8  200 199.00 0x199
130 0x1a875794 0x19a  154 153.00 0x153
131 0x1a96fa5c 0x193  147 146.00 0x146
132 0x1af4cb0c 0x1af  175 174.00 0x174
133 0x1b42f8f4 0x1b1  177 176.00 0x176
134 0x1b623e84 0x1ad  173 172.00 0x172
135 0x1b818414 0x1ba  186 185.00 0x185
136 0x1bc00f34 0x186  134 133.00 0x133
137 0x1bdf54c4 0x191  145 144.00 0x144
138 0x1bfe9a54 0x184  132 131.00 0x131
139 0x1c2d82ac 0x1c6  198 197.00 0x197
140 0x1ce9240c 0x187  135 134.00 0x134
141 0x1cf8c6d4 0x19d  157 156.00 0x156
142 0x1d08699c 0x190  144 143.00 0x143
143 0x1d9522a4 0x192  146 145.00 0x145
144 0x1db46834 0x1b9  185 184.00 0x184
145 0x1dc40afc 0x1a0  160 159.00 0x159
146 0x1e21dbac 0x188  136 135.00 0x135
147 0x1e50c404 0x183  131 130.00 0x130
148 0x1e7fac5c 0x1b4  180 179.00 0x179
149 0x1e9ef1ec 0x1a9  169 168.00 0x168
150 0x1edd7d0c 0x1b8  184 183.00 0x183

No pInfo  dwaddr seq  tax  buf (by GetHashItem)
1   0x1209f4fc 0x133  51  50.00  0x50
2   0x12293a8c 0x134  52  51.00  0x51
3   0x125822e4 0x136  54  53.00  0x53
4   0x1267c5ac 0x138  56  55.00  0x55
5   0x12776874 0x139  57  56.00  0x56
6   0x12870b3c 0x13a  58  57.00  0x57
7   0x12a650cc 0x135  53  52.00  0x52
8   0x12b5f394 0x137  55  54.00  0x54
9   0x12c5965c 0x13b  59  58.00  0x58
10  0x12d53924 0x13d  61  60.00  0x60
11  0x12e4dbec 0x13e  62  61.00  0x61
12  0x1313c444 0x13f  63  62.00  0x62
13  0x133309d4 0x140  64  63.00  0x63
14  0x13524f64 0x13c  60  59.00  0x59
15  0x1361f22c 0x141  65  64.00  0x64
16  0x137194f4 0x142  66  65.00  0x65
17  0x138137bc 0x143  67  66.00  0x66
18  0x1390da84 0x144  68  67.00  0x67
19  0x13a07d4c 0x147  71  70.00  0x70
20  0x13b02014 0x148  72  71.00  0x71
21  0x13bfc2dc 0x14a  74  73.00  0x73
22  0x13cf65a4 0x14b  75  74.00  0x74
23  0x13df086c 0x14c  76  75.00  0x75
24  0x13eeab34 0x14e  78  77.00  0x77
25  0x13fe4dfc 0x151  81  80.00  0x80
26  0x140df0c4 0x152  82  81.00  0x81
27  0x141d938c 0x153  83  82.00  0x82
28  0x142d3654 0x154  84  83.00  0x83
29  0x143cd91c 0x155  85  84.00  0x84
30  0x144c7be4 0x156  86  85.00  0x85
31  0x145c1eac 0x158  88  87.00  0x87
32  0x146bc174 0x159  89  88.00  0x88
33  0x147b643c 0x15b  91  90.00  0x90
34  0x148b0704 0x15c  92  91.00  0x91
35  0x149aa9cc 0x15e  94  93.00  0x93
36  0x14aa4c94 0x15f  95  94.00  0x94
37  0x14b9ef5c 0x150  80  79.00  0x79
38  0x14c99224 0x160  96  95.00  0x95
39  0x14d934ec 0x157  87  86.00  0x86
40  0x14e8d7b4 0x161  97  96.00  0x96
41  0x14f87a7c 0x162  98  97.00  0x97
42  0x15081d44 0x163  99  98.00  0x98
43  0x1517c00c 0x145  69  68.00  0x68
44  0x152762d4 0x165  101 100.00 0x100
45  0x1537059c 0x166  102 101.00 0x101
46  0x1546a864 0x16a  106 105.00 0x105
47  0x15564b2c 0x16b  107 106.00 0x106
48  0x1565edf4 0x14d  77  76.00  0x76
49  0x157590bc 0x16c  108 107.00 0x107
50  0x15853384 0x16d  109 108.00 0x108
51  0x1594d64c 0x16e  110 109.00 0x109
52  0x15a47914 0x16f  111 110.00 0x110
53  0x15b41bdc 0x171  113 112.00 0x112
54  0x15c3bea4 0x149  73  72.00  0x72
55  0x15d3616c 0x169  105 104.00 0x104
56  0x15e30434 0x170  112 111.00 0x111
57  0x15f2a6fc 0x167  103 102.00 0x102
58  0x160249c4 0x172  114 113.00 0x113
59  0x1611ec8c 0x173  115 114.00 0x114
60  0x16218f54 0x174  116 115.00 0x115
61  0x1631321c 0x175  117 116.00 0x116
62  0x1640d4e4 0x15a  90  89.00  0x89
63  0x165077ac 0x176  118 117.00 0x117
64  0x16601a74 0x178  120 119.00 0x119
65  0x166fbd3c 0x168  104 103.00 0x103
66  0x167f6004 0x179  121 120.00 0x120
67  0x168f02cc 0x17a  122 121.00 0x121
68  0x169ea594 0x146  70  69.00  0x69
69  0x16ae485c 0x17b  123 122.00 0x122
70  0x16bdeb24 0x17c  124 123.00 0x123
71  0x16cd8dec 0x164  100 99.00  0x99
72  0x16dd30b4 0x17d  125 124.00 0x124
73  0x16ecd37c 0x17e  126 125.00 0x125
74  0x16fc7644 0x17f  127 126.00 0x126
75  0x170c190c 0x180  128 127.00 0x127
76  0x171bbbd4 0x15d  93  92.00  0x92
77  0x172b5e9c 0x177  119 118.00 0x118
78  0x173b0164 0x14f  79  78.00  0x78
79  0x174aa42c 0x182  130 129.00 0x129
80  0x175a46f4 0x18a  138 137.00 0x137
81  0x1769e9bc 0x18b  139 138.00 0x138
82  0x17798c84 0x18d  141 140.00 0x140
83  0x17892f4c 0x18e  142 141.00 0x141
84  0x1798d214 0x18f  143 142.00 0x142
85  0x17a874dc 0x194  148 147.00 0x147
86  0x17b817a4 0x195  149 148.00 0x148
87  0x17c7ba6c 0x196  150 149.00 0x149
88  0x17d75d34 0x197  151 150.00 0x150
89  0x17e6fffc 0x198  152 151.00 0x151
90  0x17f6a2c4 0x199  153 152.00 0x152
91  0x1806458c 0x19c  156 155.00 0x155
92  0x1815e854 0x19e  158 157.00 0x157
93  0x18258b1c 0x19f  159 158.00 0x158
94  0x18352de4 0x1a1  161 160.00 0x160
95  0x1844d0ac 0x1a2  162 161.00 0x161
96  0x18547374 0x1a3  163 162.00 0x162
97  0x1864163c 0x1a4  164 163.00 0x163
98  0x1873b904 0x1a5  165 164.00 0x164
99  0x18835bcc 0x1a6  166 165.00 0x165
100 0x1892fe94 0x185  133 132.00 0x132
101 0x18a2a15c 0x18c  140 139.00 0x139
102 0x18b24424 0x1a7  167 166.00 0x166
103 0x18c1e6ec 0x1aa  170 169.00 0x169
104 0x18d189b4 0x1b0  176 175.00 0x175
105 0x18e12c7c 0x1b2  178 177.00 0x177
106 0x18f0cf44 0x1ac  172 171.00 0x171
107 0x1900720c 0x1b3  179 178.00 0x178
108 0x191014d4 0x1b5  181 180.00 0x180
109 0x191fb79c 0x1b6  182 181.00 0x181
110 0x192f5a64 0x1b7  183 182.00 0x182
111 0x193efd2c 0x19b  155 154.00 0x154
112 0x194e9ff4 0x189  137 136.00 0x136
113 0x195e42bc 0x1bb  187 186.00 0x186
114 0x196de584 0x1bc  188 187.00 0x187
115 0x197d884c 0x1bd  189 188.00 0x188
116 0x198d2b14 0x1ab  171 170.00 0x170
117 0x199ccddc 0x1be  190 189.00 0x189
118 0x19ac70a4 0x1bf  191 190.00 0x190
119 0x19bc136c 0x1c0  192 191.00 0x191
120 0x19cbb634 0x1ae  174 173.00 0x173
121 0x19db58fc 0x1c1  193 192.00 0x192
122 0x19eafbc4 0x1c2  194 193.00 0x193
123 0x19fa9e8c 0x1c3  195 194.00 0x194
124 0x1a0a4154 0x1c4  196 195.00 0x195
125 0x1a19e41c 0x181  129 128.00 0x128
126 0x1a2986e4 0x1c5  197 196.00 0x196
127 0x1a3929ac 0x1c7  199 198.00 0x198
128 0x1a48cc74 0x1a8  168 167.00 0x167
129 0x1a586f3c 0x1c8  200 199.00 0x199
130 0x1a875794 0x19a  154 153.00 0x153
131 0x1a96fa5c 0x193  147 146.00 0x146
132 0x1af4cb0c 0x1af  175 174.00 0x174
133 0x1b42f8f4 0x1b1  177 176.00 0x176
134 0x1b623e84 0x1ad  173 172.00 0x172
135 0x1b818414 0x1ba  186 185.00 0x185
136 0x1bc00f34 0x186  134 133.00 0x133
137 0x1bdf54c4 0x191  145 144.00 0x144
138 0x1bfe9a54 0x184  132 131.00 0x131
139 0x1c2d82ac 0x1c6  198 197.00 0x197
140 0x1ce9240c 0x187  135 134.00 0x134
141 0x1cf8c6d4 0x19d  157 156.00 0x156
142 0x1d08699c 0x190  144 143.00 0x143
143 0x1d9522a4 0x192  146 145.00 0x145
144 0x1db46834 0x1b9  185 184.00 0x184
145 0x1dc40afc 0x1a0  160 159.00 0x159
146 0x1e21dbac 0x188  136 135.00 0x135
147 0x1e50c404 0x183  131 130.00 0x130
148 0x1e7fac5c 0x1b4  180 179.00 0x179
149 0x1e9ef1ec 0x1a9  169 168.00 0x168
150 0x1edd7d0c 0x1b8  184 183.00 0x183
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1209F4FC
dwaddr            :    120EA4FC
seq               :    120EA500
buf[187]          :    120EA504
tax               :    120EA5C0
bigdata[3001024]  :    120EA5C4
test              :    121355C4
samplenum         :    121355C8
sampleport[123]   :    121355CC
bigdata2[4001024] :    121357B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12293A8C
dwaddr            :    122DEA8C
seq               :    122DEA90
buf[187]          :    122DEA94
tax               :    122DEB50
bigdata[3001024]  :    122DEB54
test              :    12329B54
samplenum         :    12329B58
sampleport[123]   :    12329B5C
bigdata2[4001024] :    12329D48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    125822E4
dwaddr            :    125CD2E4
seq               :    125CD2E8
buf[187]          :    125CD2EC
tax               :    125CD3A8
bigdata[3001024]  :    125CD3AC
test              :    126183AC
samplenum         :    126183B0
sampleport[123]   :    126183B4
bigdata2[4001024] :    126185A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1267C5AC
dwaddr            :    126C75AC
seq               :    126C75B0
buf[187]          :    126C75B4
tax               :    126C7670
bigdata[3001024]  :    126C7674
test              :    12712674
samplenum         :    12712678
sampleport[123]   :    1271267C
bigdata2[4001024] :    12712868
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12776874
dwaddr            :    127C1874
seq               :    127C1878
buf[187]          :    127C187C
tax               :    127C1938
bigdata[3001024]  :    127C193C
test              :    1280C93C
samplenum         :    1280C940
sampleport[123]   :    1280C944
bigdata2[4001024] :    1280CB30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12870B3C
dwaddr            :    128BBB3C
seq               :    128BBB40
buf[187]          :    128BBB44
tax               :    128BBC00
bigdata[3001024]  :    128BBC04
test              :    12906C04
samplenum         :    12906C08
sampleport[123]   :    12906C0C
bigdata2[4001024] :    12906DF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12A650CC
dwaddr            :    12AB00CC
seq               :    12AB00D0
buf[187]          :    12AB00D4
tax               :    12AB0190
bigdata[3001024]  :    12AB0194
test              :    12AFB194
samplenum         :    12AFB198
sampleport[123]   :    12AFB19C
bigdata2[4001024] :    12AFB388
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12B5F394
dwaddr            :    12BAA394
seq               :    12BAA398
buf[187]          :    12BAA39C
tax               :    12BAA458
bigdata[3001024]  :    12BAA45C
test              :    12BF545C
samplenum         :    12BF5460
sampleport[123]   :    12BF5464
bigdata2[4001024] :    12BF5650
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12C5965C
dwaddr            :    12CA465C
seq               :    12CA4660
buf[187]          :    12CA4664
tax               :    12CA4720
bigdata[3001024]  :    12CA4724
test              :    12CEF724
samplenum         :    12CEF728
sampleport[123]   :    12CEF72C
bigdata2[4001024] :    12CEF918
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12D53924
dwaddr            :    12D9E924
seq               :    12D9E928
buf[187]          :    12D9E92C
tax               :    12D9E9E8
bigdata[3001024]  :    12D9E9EC
test              :    12DE99EC
samplenum         :    12DE99F0
sampleport[123]   :    12DE99F4
bigdata2[4001024] :    12DE9BE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    12E4DBEC
dwaddr            :    12E98BEC
seq               :    12E98BF0
buf[187]          :    12E98BF4
tax               :    12E98CB0
bigdata[3001024]  :    12E98CB4
test              :    12EE3CB4
samplenum         :    12EE3CB8
sampleport[123]   :    12EE3CBC
bigdata2[4001024] :    12EE3EA8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1313C444
dwaddr            :    13187444
seq               :    13187448
buf[187]          :    1318744C
tax               :    13187508
bigdata[3001024]  :    1318750C
test              :    131D250C
samplenum         :    131D2510
sampleport[123]   :    131D2514
bigdata2[4001024] :    131D2700
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    133309D4
dwaddr            :    1337B9D4
seq               :    1337B9D8
buf[187]          :    1337B9DC
tax               :    1337BA98
bigdata[3001024]  :    1337BA9C
test              :    133C6A9C
samplenum         :    133C6AA0
sampleport[123]   :    133C6AA4
bigdata2[4001024] :    133C6C90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13524F64
dwaddr            :    1356FF64
seq               :    1356FF68
buf[187]          :    1356FF6C
tax               :    13570028
bigdata[3001024]  :    1357002C
test              :    135BB02C
samplenum         :    135BB030
sampleport[123]   :    135BB034
bigdata2[4001024] :    135BB220
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1361F22C
dwaddr            :    1366A22C
seq               :    1366A230
buf[187]          :    1366A234
tax               :    1366A2F0
bigdata[3001024]  :    1366A2F4
test              :    136B52F4
samplenum         :    136B52F8
sampleport[123]   :    136B52FC
bigdata2[4001024] :    136B54E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    137194F4
dwaddr            :    137644F4
seq               :    137644F8
buf[187]          :    137644FC
tax               :    137645B8
bigdata[3001024]  :    137645BC
test              :    137AF5BC
samplenum         :    137AF5C0
sampleport[123]   :    137AF5C4
bigdata2[4001024] :    137AF7B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    138137BC
dwaddr            :    1385E7BC
seq               :    1385E7C0
buf[187]          :    1385E7C4
tax               :    1385E880
bigdata[3001024]  :    1385E884
test              :    138A9884
samplenum         :    138A9888
sampleport[123]   :    138A988C
bigdata2[4001024] :    138A9A78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1390DA84
dwaddr            :    13958A84
seq               :    13958A88
buf[187]          :    13958A8C
tax               :    13958B48
bigdata[3001024]  :    13958B4C
test              :    139A3B4C
samplenum         :    139A3B50
sampleport[123]   :    139A3B54
bigdata2[4001024] :    139A3D40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13A07D4C
dwaddr            :    13A52D4C
seq               :    13A52D50
buf[187]          :    13A52D54
tax               :    13A52E10
bigdata[3001024]  :    13A52E14
test              :    13A9DE14
samplenum         :    13A9DE18
sampleport[123]   :    13A9DE1C
bigdata2[4001024] :    13A9E008
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13B02014
dwaddr            :    13B4D014
seq               :    13B4D018
buf[187]          :    13B4D01C
tax               :    13B4D0D8
bigdata[3001024]  :    13B4D0DC
test              :    13B980DC
samplenum         :    13B980E0
sampleport[123]   :    13B980E4
bigdata2[4001024] :    13B982D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13BFC2DC
dwaddr            :    13C472DC
seq               :    13C472E0
buf[187]          :    13C472E4
tax               :    13C473A0
bigdata[3001024]  :    13C473A4
test              :    13C923A4
samplenum         :    13C923A8
sampleport[123]   :    13C923AC
bigdata2[4001024] :    13C92598
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13CF65A4
dwaddr            :    13D415A4
seq               :    13D415A8
buf[187]          :    13D415AC
tax               :    13D41668
bigdata[3001024]  :    13D4166C
test              :    13D8C66C
samplenum         :    13D8C670
sampleport[123]   :    13D8C674
bigdata2[4001024] :    13D8C860
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13DF086C
dwaddr            :    13E3B86C
seq               :    13E3B870
buf[187]          :    13E3B874
tax               :    13E3B930
bigdata[3001024]  :    13E3B934
test              :    13E86934
samplenum         :    13E86938
sampleport[123]   :    13E8693C
bigdata2[4001024] :    13E86B28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13EEAB34
dwaddr            :    13F35B34
seq               :    13F35B38
buf[187]          :    13F35B3C
tax               :    13F35BF8
bigdata[3001024]  :    13F35BFC
test              :    13F80BFC
samplenum         :    13F80C00
sampleport[123]   :    13F80C04
bigdata2[4001024] :    13F80DF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    13FE4DFC
dwaddr            :    1402FDFC
seq               :    1402FE00
buf[187]          :    1402FE04
tax               :    1402FEC0
bigdata[3001024]  :    1402FEC4
test              :    1407AEC4
samplenum         :    1407AEC8
sampleport[123]   :    1407AECC
bigdata2[4001024] :    1407B0B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    140DF0C4
dwaddr            :    1412A0C4
seq               :    1412A0C8
buf[187]          :    1412A0CC
tax               :    1412A188
bigdata[3001024]  :    1412A18C
test              :    1417518C
samplenum         :    14175190
sampleport[123]   :    14175194
bigdata2[4001024] :    14175380
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    141D938C
dwaddr            :    1422438C
seq               :    14224390
buf[187]          :    14224394
tax               :    14224450
bigdata[3001024]  :    14224454
test              :    1426F454
samplenum         :    1426F458
sampleport[123]   :    1426F45C
bigdata2[4001024] :    1426F648
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    142D3654
dwaddr            :    1431E654
seq               :    1431E658
buf[187]          :    1431E65C
tax               :    1431E718
bigdata[3001024]  :    1431E71C
test              :    1436971C
samplenum         :    14369720
sampleport[123]   :    14369724
bigdata2[4001024] :    14369910
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    143CD91C
dwaddr            :    1441891C
seq               :    14418920
buf[187]          :    14418924
tax               :    144189E0
bigdata[3001024]  :    144189E4
test              :    144639E4
samplenum         :    144639E8
sampleport[123]   :    144639EC
bigdata2[4001024] :    14463BD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    144C7BE4
dwaddr            :    14512BE4
seq               :    14512BE8
buf[187]          :    14512BEC
tax               :    14512CA8
bigdata[3001024]  :    14512CAC
test              :    1455DCAC
samplenum         :    1455DCB0
sampleport[123]   :    1455DCB4
bigdata2[4001024] :    1455DEA0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    145C1EAC
dwaddr            :    1460CEAC
seq               :    1460CEB0
buf[187]          :    1460CEB4
tax               :    1460CF70
bigdata[3001024]  :    1460CF74
test              :    14657F74
samplenum         :    14657F78
sampleport[123]   :    14657F7C
bigdata2[4001024] :    14658168
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    146BC174
dwaddr            :    14707174
seq               :    14707178
buf[187]          :    1470717C
tax               :    14707238
bigdata[3001024]  :    1470723C
test              :    1475223C
samplenum         :    14752240
sampleport[123]   :    14752244
bigdata2[4001024] :    14752430
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    147B643C
dwaddr            :    1480143C
seq               :    14801440
buf[187]          :    14801444
tax               :    14801500
bigdata[3001024]  :    14801504
test              :    1484C504
samplenum         :    1484C508
sampleport[123]   :    1484C50C
bigdata2[4001024] :    1484C6F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    148B0704
dwaddr            :    148FB704
seq               :    148FB708
buf[187]          :    148FB70C
tax               :    148FB7C8
bigdata[3001024]  :    148FB7CC
test              :    149467CC
samplenum         :    149467D0
sampleport[123]   :    149467D4
bigdata2[4001024] :    149469C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    149AA9CC
dwaddr            :    149F59CC
seq               :    149F59D0
buf[187]          :    149F59D4
tax               :    149F5A90
bigdata[3001024]  :    149F5A94
test              :    14A40A94
samplenum         :    14A40A98
sampleport[123]   :    14A40A9C
bigdata2[4001024] :    14A40C88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14AA4C94
dwaddr            :    14AEFC94
seq               :    14AEFC98
buf[187]          :    14AEFC9C
tax               :    14AEFD58
bigdata[3001024]  :    14AEFD5C
test              :    14B3AD5C
samplenum         :    14B3AD60
sampleport[123]   :    14B3AD64
bigdata2[4001024] :    14B3AF50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14B9EF5C
dwaddr            :    14BE9F5C
seq               :    14BE9F60
buf[187]          :    14BE9F64
tax               :    14BEA020
bigdata[3001024]  :    14BEA024
test              :    14C35024
samplenum         :    14C35028
sampleport[123]   :    14C3502C
bigdata2[4001024] :    14C35218
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14C99224
dwaddr            :    14CE4224
seq               :    14CE4228
buf[187]          :    14CE422C
tax               :    14CE42E8
bigdata[3001024]  :    14CE42EC
test              :    14D2F2EC
samplenum         :    14D2F2F0
sampleport[123]   :    14D2F2F4
bigdata2[4001024] :    14D2F4E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14D934EC
dwaddr            :    14DDE4EC
seq               :    14DDE4F0
buf[187]          :    14DDE4F4
tax               :    14DDE5B0
bigdata[3001024]  :    14DDE5B4
test              :    14E295B4
samplenum         :    14E295B8
sampleport[123]   :    14E295BC
bigdata2[4001024] :    14E297A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14E8D7B4
dwaddr            :    14ED87B4
seq               :    14ED87B8
buf[187]          :    14ED87BC
tax               :    14ED8878
bigdata[3001024]  :    14ED887C
test              :    14F2387C
samplenum         :    14F23880
sampleport[123]   :    14F23884
bigdata2[4001024] :    14F23A70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    14F87A7C
dwaddr            :    14FD2A7C
seq               :    14FD2A80
buf[187]          :    14FD2A84
tax               :    14FD2B40
bigdata[3001024]  :    14FD2B44
test              :    1501DB44
samplenum         :    1501DB48
sampleport[123]   :    1501DB4C
bigdata2[4001024] :    1501DD38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15081D44
dwaddr            :    150CCD44
seq               :    150CCD48
buf[187]          :    150CCD4C
tax               :    150CCE08
bigdata[3001024]  :    150CCE0C
test              :    15117E0C
samplenum         :    15117E10
sampleport[123]   :    15117E14
bigdata2[4001024] :    15118000
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1517C00C
dwaddr            :    151C700C
seq               :    151C7010
buf[187]          :    151C7014
tax               :    151C70D0
bigdata[3001024]  :    151C70D4
test              :    152120D4
samplenum         :    152120D8
sampleport[123]   :    152120DC
bigdata2[4001024] :    152122C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    152762D4
dwaddr            :    152C12D4
seq               :    152C12D8
buf[187]          :    152C12DC
tax               :    152C1398
bigdata[3001024]  :    152C139C
test              :    1530C39C
samplenum         :    1530C3A0
sampleport[123]   :    1530C3A4
bigdata2[4001024] :    1530C590
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1537059C
dwaddr            :    153BB59C
seq               :    153BB5A0
buf[187]          :    153BB5A4
tax               :    153BB660
bigdata[3001024]  :    153BB664
test              :    15406664
samplenum         :    15406668
sampleport[123]   :    1540666C
bigdata2[4001024] :    15406858
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1546A864
dwaddr            :    154B5864
seq               :    154B5868
buf[187]          :    154B586C
tax               :    154B5928
bigdata[3001024]  :    154B592C
test              :    1550092C
samplenum         :    15500930
sampleport[123]   :    15500934
bigdata2[4001024] :    15500B20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15564B2C
dwaddr            :    155AFB2C
seq               :    155AFB30
buf[187]          :    155AFB34
tax               :    155AFBF0
bigdata[3001024]  :    155AFBF4
test              :    155FABF4
samplenum         :    155FABF8
sampleport[123]   :    155FABFC
bigdata2[4001024] :    155FADE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1565EDF4
dwaddr            :    156A9DF4
seq               :    156A9DF8
buf[187]          :    156A9DFC
tax               :    156A9EB8
bigdata[3001024]  :    156A9EBC
test              :    156F4EBC
samplenum         :    156F4EC0
sampleport[123]   :    156F4EC4
bigdata2[4001024] :    156F50B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    157590BC
dwaddr            :    157A40BC
seq               :    157A40C0
buf[187]          :    157A40C4
tax               :    157A4180
bigdata[3001024]  :    157A4184
test              :    157EF184
samplenum         :    157EF188
sampleport[123]   :    157EF18C
bigdata2[4001024] :    157EF378
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15853384
dwaddr            :    1589E384
seq               :    1589E388
buf[187]          :    1589E38C
tax               :    1589E448
bigdata[3001024]  :    1589E44C
test              :    158E944C
samplenum         :    158E9450
sampleport[123]   :    158E9454
bigdata2[4001024] :    158E9640
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1594D64C
dwaddr            :    1599864C
seq               :    15998650
buf[187]          :    15998654
tax               :    15998710
bigdata[3001024]  :    15998714
test              :    159E3714
samplenum         :    159E3718
sampleport[123]   :    159E371C
bigdata2[4001024] :    159E3908
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15A47914
dwaddr            :    15A92914
seq               :    15A92918
buf[187]          :    15A9291C
tax               :    15A929D8
bigdata[3001024]  :    15A929DC
test              :    15ADD9DC
samplenum         :    15ADD9E0
sampleport[123]   :    15ADD9E4
bigdata2[4001024] :    15ADDBD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15B41BDC
dwaddr            :    15B8CBDC
seq               :    15B8CBE0
buf[187]          :    15B8CBE4
tax               :    15B8CCA0
bigdata[3001024]  :    15B8CCA4
test              :    15BD7CA4
samplenum         :    15BD7CA8
sampleport[123]   :    15BD7CAC
bigdata2[4001024] :    15BD7E98
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15C3BEA4
dwaddr            :    15C86EA4
seq               :    15C86EA8
buf[187]          :    15C86EAC
tax               :    15C86F68
bigdata[3001024]  :    15C86F6C
test              :    15CD1F6C
samplenum         :    15CD1F70
sampleport[123]   :    15CD1F74
bigdata2[4001024] :    15CD2160
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15D3616C
dwaddr            :    15D8116C
seq               :    15D81170
buf[187]          :    15D81174
tax               :    15D81230
bigdata[3001024]  :    15D81234
test              :    15DCC234
samplenum         :    15DCC238
sampleport[123]   :    15DCC23C
bigdata2[4001024] :    15DCC428
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15E30434
dwaddr            :    15E7B434
seq               :    15E7B438
buf[187]          :    15E7B43C
tax               :    15E7B4F8
bigdata[3001024]  :    15E7B4FC
test              :    15EC64FC
samplenum         :    15EC6500
sampleport[123]   :    15EC6504
bigdata2[4001024] :    15EC66F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    15F2A6FC
dwaddr            :    15F756FC
seq               :    15F75700
buf[187]          :    15F75704
tax               :    15F757C0
bigdata[3001024]  :    15F757C4
test              :    15FC07C4
samplenum         :    15FC07C8
sampleport[123]   :    15FC07CC
bigdata2[4001024] :    15FC09B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    160249C4
dwaddr            :    1606F9C4
seq               :    1606F9C8
buf[187]          :    1606F9CC
tax               :    1606FA88
bigdata[3001024]  :    1606FA8C
test              :    160BAA8C
samplenum         :    160BAA90
sampleport[123]   :    160BAA94
bigdata2[4001024] :    160BAC80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1611EC8C
dwaddr            :    16169C8C
seq               :    16169C90
buf[187]          :    16169C94
tax               :    16169D50
bigdata[3001024]  :    16169D54
test              :    161B4D54
samplenum         :    161B4D58
sampleport[123]   :    161B4D5C
bigdata2[4001024] :    161B4F48
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16218F54
dwaddr            :    16263F54
seq               :    16263F58
buf[187]          :    16263F5C
tax               :    16264018
bigdata[3001024]  :    1626401C
test              :    162AF01C
samplenum         :    162AF020
sampleport[123]   :    162AF024
bigdata2[4001024] :    162AF210
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1631321C
dwaddr            :    1635E21C
seq               :    1635E220
buf[187]          :    1635E224
tax               :    1635E2E0
bigdata[3001024]  :    1635E2E4
test              :    163A92E4
samplenum         :    163A92E8
sampleport[123]   :    163A92EC
bigdata2[4001024] :    163A94D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1640D4E4
dwaddr            :    164584E4
seq               :    164584E8
buf[187]          :    164584EC
tax               :    164585A8
bigdata[3001024]  :    164585AC
test              :    164A35AC
samplenum         :    164A35B0
sampleport[123]   :    164A35B4
bigdata2[4001024] :    164A37A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    165077AC
dwaddr            :    165527AC
seq               :    165527B0
buf[187]          :    165527B4
tax               :    16552870
bigdata[3001024]  :    16552874
test              :    1659D874
samplenum         :    1659D878
sampleport[123]   :    1659D87C
bigdata2[4001024] :    1659DA68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16601A74
dwaddr            :    1664CA74
seq               :    1664CA78
buf[187]          :    1664CA7C
tax               :    1664CB38
bigdata[3001024]  :    1664CB3C
test              :    16697B3C
samplenum         :    16697B40
sampleport[123]   :    16697B44
bigdata2[4001024] :    16697D30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    166FBD3C
dwaddr            :    16746D3C
seq               :    16746D40
buf[187]          :    16746D44
tax               :    16746E00
bigdata[3001024]  :    16746E04
test              :    16791E04
samplenum         :    16791E08
sampleport[123]   :    16791E0C
bigdata2[4001024] :    16791FF8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    167F6004
dwaddr            :    16841004
seq               :    16841008
buf[187]          :    1684100C
tax               :    168410C8
bigdata[3001024]  :    168410CC
test              :    1688C0CC
samplenum         :    1688C0D0
sampleport[123]   :    1688C0D4
bigdata2[4001024] :    1688C2C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    168F02CC
dwaddr            :    1693B2CC
seq               :    1693B2D0
buf[187]          :    1693B2D4
tax               :    1693B390
bigdata[3001024]  :    1693B394
test              :    16986394
samplenum         :    16986398
sampleport[123]   :    1698639C
bigdata2[4001024] :    16986588
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    169EA594
dwaddr            :    16A35594
seq               :    16A35598
buf[187]          :    16A3559C
tax               :    16A35658
bigdata[3001024]  :    16A3565C
test              :    16A8065C
samplenum         :    16A80660
sampleport[123]   :    16A80664
bigdata2[4001024] :    16A80850
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16AE485C
dwaddr            :    16B2F85C
seq               :    16B2F860
buf[187]          :    16B2F864
tax               :    16B2F920
bigdata[3001024]  :    16B2F924
test              :    16B7A924
samplenum         :    16B7A928
sampleport[123]   :    16B7A92C
bigdata2[4001024] :    16B7AB18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16BDEB24
dwaddr            :    16C29B24
seq               :    16C29B28
buf[187]          :    16C29B2C
tax               :    16C29BE8
bigdata[3001024]  :    16C29BEC
test              :    16C74BEC
samplenum         :    16C74BF0
sampleport[123]   :    16C74BF4
bigdata2[4001024] :    16C74DE0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16CD8DEC
dwaddr            :    16D23DEC
seq               :    16D23DF0
buf[187]          :    16D23DF4
tax               :    16D23EB0
bigdata[3001024]  :    16D23EB4
test              :    16D6EEB4
samplenum         :    16D6EEB8
sampleport[123]   :    16D6EEBC
bigdata2[4001024] :    16D6F0A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16DD30B4
dwaddr            :    16E1E0B4
seq               :    16E1E0B8
buf[187]          :    16E1E0BC
tax               :    16E1E178
bigdata[3001024]  :    16E1E17C
test              :    16E6917C
samplenum         :    16E69180
sampleport[123]   :    16E69184
bigdata2[4001024] :    16E69370
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16ECD37C
dwaddr            :    16F1837C
seq               :    16F18380
buf[187]          :    16F18384
tax               :    16F18440
bigdata[3001024]  :    16F18444
test              :    16F63444
samplenum         :    16F63448
sampleport[123]   :    16F6344C
bigdata2[4001024] :    16F63638
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    16FC7644
dwaddr            :    17012644
seq               :    17012648
buf[187]          :    1701264C
tax               :    17012708
bigdata[3001024]  :    1701270C
test              :    1705D70C
samplenum         :    1705D710
sampleport[123]   :    1705D714
bigdata2[4001024] :    1705D900
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    170C190C
dwaddr            :    1710C90C
seq               :    1710C910
buf[187]          :    1710C914
tax               :    1710C9D0
bigdata[3001024]  :    1710C9D4
test              :    171579D4
samplenum         :    171579D8
sampleport[123]   :    171579DC
bigdata2[4001024] :    17157BC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    171BBBD4
dwaddr            :    17206BD4
seq               :    17206BD8
buf[187]          :    17206BDC
tax               :    17206C98
bigdata[3001024]  :    17206C9C
test              :    17251C9C
samplenum         :    17251CA0
sampleport[123]   :    17251CA4
bigdata2[4001024] :    17251E90
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    172B5E9C
dwaddr            :    17300E9C
seq               :    17300EA0
buf[187]          :    17300EA4
tax               :    17300F60
bigdata[3001024]  :    17300F64
test              :    1734BF64
samplenum         :    1734BF68
sampleport[123]   :    1734BF6C
bigdata2[4001024] :    1734C158
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    173B0164
dwaddr            :    173FB164
seq               :    173FB168
buf[187]          :    173FB16C
tax               :    173FB228
bigdata[3001024]  :    173FB22C
test              :    1744622C
samplenum         :    17446230
sampleport[123]   :    17446234
bigdata2[4001024] :    17446420
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    174AA42C
dwaddr            :    174F542C
seq               :    174F5430
buf[187]          :    174F5434
tax               :    174F54F0
bigdata[3001024]  :    174F54F4
test              :    175404F4
samplenum         :    175404F8
sampleport[123]   :    175404FC
bigdata2[4001024] :    175406E8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    175A46F4
dwaddr            :    175EF6F4
seq               :    175EF6F8
buf[187]          :    175EF6FC
tax               :    175EF7B8
bigdata[3001024]  :    175EF7BC
test              :    1763A7BC
samplenum         :    1763A7C0
sampleport[123]   :    1763A7C4
bigdata2[4001024] :    1763A9B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1769E9BC
dwaddr            :    176E99BC
seq               :    176E99C0
buf[187]          :    176E99C4
tax               :    176E9A80
bigdata[3001024]  :    176E9A84
test              :    17734A84
samplenum         :    17734A88
sampleport[123]   :    17734A8C
bigdata2[4001024] :    17734C78
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17798C84
dwaddr            :    177E3C84
seq               :    177E3C88
buf[187]          :    177E3C8C
tax               :    177E3D48
bigdata[3001024]  :    177E3D4C
test              :    1782ED4C
samplenum         :    1782ED50
sampleport[123]   :    1782ED54
bigdata2[4001024] :    1782EF40
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17892F4C
dwaddr            :    178DDF4C
seq               :    178DDF50
buf[187]          :    178DDF54
tax               :    178DE010
bigdata[3001024]  :    178DE014
test              :    17929014
samplenum         :    17929018
sampleport[123]   :    1792901C
bigdata2[4001024] :    17929208
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1798D214
dwaddr            :    179D8214
seq               :    179D8218
buf[187]          :    179D821C
tax               :    179D82D8
bigdata[3001024]  :    179D82DC
test              :    17A232DC
samplenum         :    17A232E0
sampleport[123]   :    17A232E4
bigdata2[4001024] :    17A234D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17A874DC
dwaddr            :    17AD24DC
seq               :    17AD24E0
buf[187]          :    17AD24E4
tax               :    17AD25A0
bigdata[3001024]  :    17AD25A4
test              :    17B1D5A4
samplenum         :    17B1D5A8
sampleport[123]   :    17B1D5AC
bigdata2[4001024] :    17B1D798
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17B817A4
dwaddr            :    17BCC7A4
seq               :    17BCC7A8
buf[187]          :    17BCC7AC
tax               :    17BCC868
bigdata[3001024]  :    17BCC86C
test              :    17C1786C
samplenum         :    17C17870
sampleport[123]   :    17C17874
bigdata2[4001024] :    17C17A60
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17C7BA6C
dwaddr            :    17CC6A6C
seq               :    17CC6A70
buf[187]          :    17CC6A74
tax               :    17CC6B30
bigdata[3001024]  :    17CC6B34
test              :    17D11B34
samplenum         :    17D11B38
sampleport[123]   :    17D11B3C
bigdata2[4001024] :    17D11D28
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17D75D34
dwaddr            :    17DC0D34
seq               :    17DC0D38
buf[187]          :    17DC0D3C
tax               :    17DC0DF8
bigdata[3001024]  :    17DC0DFC
test              :    17E0BDFC
samplenum         :    17E0BE00
sampleport[123]   :    17E0BE04
bigdata2[4001024] :    17E0BFF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17E6FFFC
dwaddr            :    17EBAFFC
seq               :    17EBB000
buf[187]          :    17EBB004
tax               :    17EBB0C0
bigdata[3001024]  :    17EBB0C4
test              :    17F060C4
samplenum         :    17F060C8
sampleport[123]   :    17F060CC
bigdata2[4001024] :    17F062B8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    17F6A2C4
dwaddr            :    17FB52C4
seq               :    17FB52C8
buf[187]          :    17FB52CC
tax               :    17FB5388
bigdata[3001024]  :    17FB538C
test              :    1800038C
samplenum         :    18000390
sampleport[123]   :    18000394
bigdata2[4001024] :    18000580
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1806458C
dwaddr            :    180AF58C
seq               :    180AF590
buf[187]          :    180AF594
tax               :    180AF650
bigdata[3001024]  :    180AF654
test              :    180FA654
samplenum         :    180FA658
sampleport[123]   :    180FA65C
bigdata2[4001024] :    180FA848
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1815E854
dwaddr            :    181A9854
seq               :    181A9858
buf[187]          :    181A985C
tax               :    181A9918
bigdata[3001024]  :    181A991C
test              :    181F491C
samplenum         :    181F4920
sampleport[123]   :    181F4924
bigdata2[4001024] :    181F4B10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18258B1C
dwaddr            :    182A3B1C
seq               :    182A3B20
buf[187]          :    182A3B24
tax               :    182A3BE0
bigdata[3001024]  :    182A3BE4
test              :    182EEBE4
samplenum         :    182EEBE8
sampleport[123]   :    182EEBEC
bigdata2[4001024] :    182EEDD8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18352DE4
dwaddr            :    1839DDE4
seq               :    1839DDE8
buf[187]          :    1839DDEC
tax               :    1839DEA8
bigdata[3001024]  :    1839DEAC
test              :    183E8EAC
samplenum         :    183E8EB0
sampleport[123]   :    183E8EB4
bigdata2[4001024] :    183E90A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1844D0AC
dwaddr            :    184980AC
seq               :    184980B0
buf[187]          :    184980B4
tax               :    18498170
bigdata[3001024]  :    18498174
test              :    184E3174
samplenum         :    184E3178
sampleport[123]   :    184E317C
bigdata2[4001024] :    184E3368
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18547374
dwaddr            :    18592374
seq               :    18592378
buf[187]          :    1859237C
tax               :    18592438
bigdata[3001024]  :    1859243C
test              :    185DD43C
samplenum         :    185DD440
sampleport[123]   :    185DD444
bigdata2[4001024] :    185DD630
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1864163C
dwaddr            :    1868C63C
seq               :    1868C640
buf[187]          :    1868C644
tax               :    1868C700
bigdata[3001024]  :    1868C704
test              :    186D7704
samplenum         :    186D7708
sampleport[123]   :    186D770C
bigdata2[4001024] :    186D78F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1873B904
dwaddr            :    18786904
seq               :    18786908
buf[187]          :    1878690C
tax               :    187869C8
bigdata[3001024]  :    187869CC
test              :    187D19CC
samplenum         :    187D19D0
sampleport[123]   :    187D19D4
bigdata2[4001024] :    187D1BC0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18835BCC
dwaddr            :    18880BCC
seq               :    18880BD0
buf[187]          :    18880BD4
tax               :    18880C90
bigdata[3001024]  :    18880C94
test              :    188CBC94
samplenum         :    188CBC98
sampleport[123]   :    188CBC9C
bigdata2[4001024] :    188CBE88
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1892FE94
dwaddr            :    1897AE94
seq               :    1897AE98
buf[187]          :    1897AE9C
tax               :    1897AF58
bigdata[3001024]  :    1897AF5C
test              :    189C5F5C
samplenum         :    189C5F60
sampleport[123]   :    189C5F64
bigdata2[4001024] :    189C6150
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18A2A15C
dwaddr            :    18A7515C
seq               :    18A75160
buf[187]          :    18A75164
tax               :    18A75220
bigdata[3001024]  :    18A75224
test              :    18AC0224
samplenum         :    18AC0228
sampleport[123]   :    18AC022C
bigdata2[4001024] :    18AC0418
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18B24424
dwaddr            :    18B6F424
seq               :    18B6F428
buf[187]          :    18B6F42C
tax               :    18B6F4E8
bigdata[3001024]  :    18B6F4EC
test              :    18BBA4EC
samplenum         :    18BBA4F0
sampleport[123]   :    18BBA4F4
bigdata2[4001024] :    18BBA6E0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18C1E6EC
dwaddr            :    18C696EC
seq               :    18C696F0
buf[187]          :    18C696F4
tax               :    18C697B0
bigdata[3001024]  :    18C697B4
test              :    18CB47B4
samplenum         :    18CB47B8
sampleport[123]   :    18CB47BC
bigdata2[4001024] :    18CB49A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18D189B4
dwaddr            :    18D639B4
seq               :    18D639B8
buf[187]          :    18D639BC
tax               :    18D63A78
bigdata[3001024]  :    18D63A7C
test              :    18DAEA7C
samplenum         :    18DAEA80
sampleport[123]   :    18DAEA84
bigdata2[4001024] :    18DAEC70
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18E12C7C
dwaddr            :    18E5DC7C
seq               :    18E5DC80
buf[187]          :    18E5DC84
tax               :    18E5DD40
bigdata[3001024]  :    18E5DD44
test              :    18EA8D44
samplenum         :    18EA8D48
sampleport[123]   :    18EA8D4C
bigdata2[4001024] :    18EA8F38
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    18F0CF44
dwaddr            :    18F57F44
seq               :    18F57F48
buf[187]          :    18F57F4C
tax               :    18F58008
bigdata[3001024]  :    18F5800C
test              :    18FA300C
samplenum         :    18FA3010
sampleport[123]   :    18FA3014
bigdata2[4001024] :    18FA3200
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1900720C
dwaddr            :    1905220C
seq               :    19052210
buf[187]          :    19052214
tax               :    190522D0
bigdata[3001024]  :    190522D4
test              :    1909D2D4
samplenum         :    1909D2D8
sampleport[123]   :    1909D2DC
bigdata2[4001024] :    1909D4C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191014D4
dwaddr            :    1914C4D4
seq               :    1914C4D8
buf[187]          :    1914C4DC
tax               :    1914C598
bigdata[3001024]  :    1914C59C
test              :    1919759C
samplenum         :    191975A0
sampleport[123]   :    191975A4
bigdata2[4001024] :    19197790
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    191FB79C
dwaddr            :    1924679C
seq               :    192467A0
buf[187]          :    192467A4
tax               :    19246860
bigdata[3001024]  :    19246864
test              :    19291864
samplenum         :    19291868
sampleport[123]   :    1929186C
bigdata2[4001024] :    19291A58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    192F5A64
dwaddr            :    19340A64
seq               :    19340A68
buf[187]          :    19340A6C
tax               :    19340B28
bigdata[3001024]  :    19340B2C
test              :    1938BB2C
samplenum         :    1938BB30
sampleport[123]   :    1938BB34
bigdata2[4001024] :    1938BD20
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    193EFD2C
dwaddr            :    1943AD2C
seq               :    1943AD30
buf[187]          :    1943AD34
tax               :    1943ADF0
bigdata[3001024]  :    1943ADF4
test              :    19485DF4
samplenum         :    19485DF8
sampleport[123]   :    19485DFC
bigdata2[4001024] :    19485FE8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    194E9FF4
dwaddr            :    19534FF4
seq               :    19534FF8
buf[187]          :    19534FFC
tax               :    195350B8
bigdata[3001024]  :    195350BC
test              :    195800BC
samplenum         :    195800C0
sampleport[123]   :    195800C4
bigdata2[4001024] :    195802B0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    195E42BC
dwaddr            :    1962F2BC
seq               :    1962F2C0
buf[187]          :    1962F2C4
tax               :    1962F380
bigdata[3001024]  :    1962F384
test              :    1967A384
samplenum         :    1967A388
sampleport[123]   :    1967A38C
bigdata2[4001024] :    1967A578
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    196DE584
dwaddr            :    19729584
seq               :    19729588
buf[187]          :    1972958C
tax               :    19729648
bigdata[3001024]  :    1972964C
test              :    1977464C
samplenum         :    19774650
sampleport[123]   :    19774654
bigdata2[4001024] :    19774840
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    197D884C
dwaddr            :    1982384C
seq               :    19823850
buf[187]          :    19823854
tax               :    19823910
bigdata[3001024]  :    19823914
test              :    1986E914
samplenum         :    1986E918
sampleport[123]   :    1986E91C
bigdata2[4001024] :    1986EB08
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    198D2B14
dwaddr            :    1991DB14
seq               :    1991DB18
buf[187]          :    1991DB1C
tax               :    1991DBD8
bigdata[3001024]  :    1991DBDC
test              :    19968BDC
samplenum         :    19968BE0
sampleport[123]   :    19968BE4
bigdata2[4001024] :    19968DD0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    199CCDDC
dwaddr            :    19A17DDC
seq               :    19A17DE0
buf[187]          :    19A17DE4
tax               :    19A17EA0
bigdata[3001024]  :    19A17EA4
test              :    19A62EA4
samplenum         :    19A62EA8
sampleport[123]   :    19A62EAC
bigdata2[4001024] :    19A63098
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19AC70A4
dwaddr            :    19B120A4
seq               :    19B120A8
buf[187]          :    19B120AC
tax               :    19B12168
bigdata[3001024]  :    19B1216C
test              :    19B5D16C
samplenum         :    19B5D170
sampleport[123]   :    19B5D174
bigdata2[4001024] :    19B5D360
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19BC136C
dwaddr            :    19C0C36C
seq               :    19C0C370
buf[187]          :    19C0C374
tax               :    19C0C430
bigdata[3001024]  :    19C0C434
test              :    19C57434
samplenum         :    19C57438
sampleport[123]   :    19C5743C
bigdata2[4001024] :    19C57628
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19CBB634
dwaddr            :    19D06634
seq               :    19D06638
buf[187]          :    19D0663C
tax               :    19D066F8
bigdata[3001024]  :    19D066FC
test              :    19D516FC
samplenum         :    19D51700
sampleport[123]   :    19D51704
bigdata2[4001024] :    19D518F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19DB58FC
dwaddr            :    19E008FC
seq               :    19E00900
buf[187]          :    19E00904
tax               :    19E009C0
bigdata[3001024]  :    19E009C4
test              :    19E4B9C4
samplenum         :    19E4B9C8
sampleport[123]   :    19E4B9CC
bigdata2[4001024] :    19E4BBB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19EAFBC4
dwaddr            :    19EFABC4
seq               :    19EFABC8
buf[187]          :    19EFABCC
tax               :    19EFAC88
bigdata[3001024]  :    19EFAC8C
test              :    19F45C8C
samplenum         :    19F45C90
sampleport[123]   :    19F45C94
bigdata2[4001024] :    19F45E80
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    19FA9E8C
dwaddr            :    19FF4E8C
seq               :    19FF4E90
buf[187]          :    19FF4E94
tax               :    19FF4F50
bigdata[3001024]  :    19FF4F54
test              :    1A03FF54
samplenum         :    1A03FF58
sampleport[123]   :    1A03FF5C
bigdata2[4001024] :    1A040148
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A0A4154
dwaddr            :    1A0EF154
seq               :    1A0EF158
buf[187]          :    1A0EF15C
tax               :    1A0EF218
bigdata[3001024]  :    1A0EF21C
test              :    1A13A21C
samplenum         :    1A13A220
sampleport[123]   :    1A13A224
bigdata2[4001024] :    1A13A410
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A19E41C
dwaddr            :    1A1E941C
seq               :    1A1E9420
buf[187]          :    1A1E9424
tax               :    1A1E94E0
bigdata[3001024]  :    1A1E94E4
test              :    1A2344E4
samplenum         :    1A2344E8
sampleport[123]   :    1A2344EC
bigdata2[4001024] :    1A2346D8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A2986E4
dwaddr            :    1A2E36E4
seq               :    1A2E36E8
buf[187]          :    1A2E36EC
tax               :    1A2E37A8
bigdata[3001024]  :    1A2E37AC
test              :    1A32E7AC
samplenum         :    1A32E7B0
sampleport[123]   :    1A32E7B4
bigdata2[4001024] :    1A32E9A0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A3929AC
dwaddr            :    1A3DD9AC
seq               :    1A3DD9B0
buf[187]          :    1A3DD9B4
tax               :    1A3DDA70
bigdata[3001024]  :    1A3DDA74
test              :    1A428A74
samplenum         :    1A428A78
sampleport[123]   :    1A428A7C
bigdata2[4001024] :    1A428C68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A48CC74
dwaddr            :    1A4D7C74
seq               :    1A4D7C78
buf[187]          :    1A4D7C7C
tax               :    1A4D7D38
bigdata[3001024]  :    1A4D7D3C
test              :    1A522D3C
samplenum         :    1A522D40
sampleport[123]   :    1A522D44
bigdata2[4001024] :    1A522F30
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A586F3C
dwaddr            :    1A5D1F3C
seq               :    1A5D1F40
buf[187]          :    1A5D1F44
tax               :    1A5D2000
bigdata[3001024]  :    1A5D2004
test              :    1A61D004
samplenum         :    1A61D008
sampleport[123]   :    1A61D00C
bigdata2[4001024] :    1A61D1F8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A875794
dwaddr            :    1A8C0794
seq               :    1A8C0798
buf[187]          :    1A8C079C
tax               :    1A8C0858
bigdata[3001024]  :    1A8C085C
test              :    1A90B85C
samplenum         :    1A90B860
sampleport[123]   :    1A90B864
bigdata2[4001024] :    1A90BA50
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1A96FA5C
dwaddr            :    1A9BAA5C
seq               :    1A9BAA60
buf[187]          :    1A9BAA64
tax               :    1A9BAB20
bigdata[3001024]  :    1A9BAB24
test              :    1AA05B24
samplenum         :    1AA05B28
sampleport[123]   :    1AA05B2C
bigdata2[4001024] :    1AA05D18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1AF4CB0C
dwaddr            :    1AF97B0C
seq               :    1AF97B10
buf[187]          :    1AF97B14
tax               :    1AF97BD0
bigdata[3001024]  :    1AF97BD4
test              :    1AFE2BD4
samplenum         :    1AFE2BD8
sampleport[123]   :    1AFE2BDC
bigdata2[4001024] :    1AFE2DC8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B42F8F4
dwaddr            :    1B47A8F4
seq               :    1B47A8F8
buf[187]          :    1B47A8FC
tax               :    1B47A9B8
bigdata[3001024]  :    1B47A9BC
test              :    1B4C59BC
samplenum         :    1B4C59C0
sampleport[123]   :    1B4C59C4
bigdata2[4001024] :    1B4C5BB0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B623E84
dwaddr            :    1B66EE84
seq               :    1B66EE88
buf[187]          :    1B66EE8C
tax               :    1B66EF48
bigdata[3001024]  :    1B66EF4C
test              :    1B6B9F4C
samplenum         :    1B6B9F50
sampleport[123]   :    1B6B9F54
bigdata2[4001024] :    1B6BA140
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1B818414
dwaddr            :    1B863414
seq               :    1B863418
buf[187]          :    1B86341C
tax               :    1B8634D8
bigdata[3001024]  :    1B8634DC
test              :    1B8AE4DC
samplenum         :    1B8AE4E0
sampleport[123]   :    1B8AE4E4
bigdata2[4001024] :    1B8AE6D0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BC00F34
dwaddr            :    1BC4BF34
seq               :    1BC4BF38
buf[187]          :    1BC4BF3C
tax               :    1BC4BFF8
bigdata[3001024]  :    1BC4BFFC
test              :    1BC96FFC
samplenum         :    1BC97000
sampleport[123]   :    1BC97004
bigdata2[4001024] :    1BC971F0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BDF54C4
dwaddr            :    1BE404C4
seq               :    1BE404C8
buf[187]          :    1BE404CC
tax               :    1BE40588
bigdata[3001024]  :    1BE4058C
test              :    1BE8B58C
samplenum         :    1BE8B590
sampleport[123]   :    1BE8B594
bigdata2[4001024] :    1BE8B780
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1BFE9A54
dwaddr            :    1C034A54
seq               :    1C034A58
buf[187]          :    1C034A5C
tax               :    1C034B18
bigdata[3001024]  :    1C034B1C
test              :    1C07FB1C
samplenum         :    1C07FB20
sampleport[123]   :    1C07FB24
bigdata2[4001024] :    1C07FD10
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1C2D82AC
dwaddr            :    1C3232AC
seq               :    1C3232B0
buf[187]          :    1C3232B4
tax               :    1C323370
bigdata[3001024]  :    1C323374
test              :    1C36E374
samplenum         :    1C36E378
sampleport[123]   :    1C36E37C
bigdata2[4001024] :    1C36E568
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CE9240C
dwaddr            :    1CEDD40C
seq               :    1CEDD410
buf[187]          :    1CEDD414
tax               :    1CEDD4D0
bigdata[3001024]  :    1CEDD4D4
test              :    1CF284D4
samplenum         :    1CF284D8
sampleport[123]   :    1CF284DC
bigdata2[4001024] :    1CF286C8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1CF8C6D4
dwaddr            :    1CFD76D4
seq               :    1CFD76D8
buf[187]          :    1CFD76DC
tax               :    1CFD7798
bigdata[3001024]  :    1CFD779C
test              :    1D02279C
samplenum         :    1D0227A0
sampleport[123]   :    1D0227A4
bigdata2[4001024] :    1D022990
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D08699C
dwaddr            :    1D0D199C
seq               :    1D0D19A0
buf[187]          :    1D0D19A4
tax               :    1D0D1A60
bigdata[3001024]  :    1D0D1A64
test              :    1D11CA64
samplenum         :    1D11CA68
sampleport[123]   :    1D11CA6C
bigdata2[4001024] :    1D11CC58
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1D9522A4
dwaddr            :    1D99D2A4
seq               :    1D99D2A8
buf[187]          :    1D99D2AC
tax               :    1D99D368
bigdata[3001024]  :    1D99D36C
test              :    1D9E836C
samplenum         :    1D9E8370
sampleport[123]   :    1D9E8374
bigdata2[4001024] :    1D9E8560
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DB46834
dwaddr            :    1DB91834
seq               :    1DB91838
buf[187]          :    1DB9183C
tax               :    1DB918F8
bigdata[3001024]  :    1DB918FC
test              :    1DBDC8FC
samplenum         :    1DBDC900
sampleport[123]   :    1DBDC904
bigdata2[4001024] :    1DBDCAF0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1DC40AFC
dwaddr            :    1DC8BAFC
seq               :    1DC8BB00
buf[187]          :    1DC8BB04
tax               :    1DC8BBC0
bigdata[3001024]  :    1DC8BBC4
test              :    1DCD6BC4
samplenum         :    1DCD6BC8
sampleport[123]   :    1DCD6BCC
bigdata2[4001024] :    1DCD6DB8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E21DBAC
dwaddr            :    1E268BAC
seq               :    1E268BB0
buf[187]          :    1E268BB4
tax               :    1E268C70
bigdata[3001024]  :    1E268C74
test              :    1E2B3C74
samplenum         :    1E2B3C78
sampleport[123]   :    1E2B3C7C
bigdata2[4001024] :    1E2B3E68
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E50C404
dwaddr            :    1E557404
seq               :    1E557408
buf[187]          :    1E55740C
tax               :    1E5574C8
bigdata[3001024]  :    1E5574CC
test              :    1E5A24CC
samplenum         :    1E5A24D0
sampleport[123]   :    1E5A24D4
bigdata2[4001024] :    1E5A26C0
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E7FAC5C
dwaddr            :    1E845C5C
seq               :    1E845C60
buf[187]          :    1E845C64
tax               :    1E845D20
bigdata[3001024]  :    1E845D24
test              :    1E890D24
samplenum         :    1E890D28
sampleport[123]   :    1E890D2C
bigdata2[4001024] :    1E890F18
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1E9EF1EC
dwaddr            :    1EA3A1EC
seq               :    1EA3A1F0
buf[187]          :    1EA3A1F4
tax               :    1EA3A2B0
bigdata[3001024]  :    1EA3A2B4
test              :    1EA852B4
samplenum         :    1EA852B8
sampleport[123]   :    1EA852BC
bigdata2[4001024] :    1EA854A8
Struct T_HashInfo info following ===== [pInfo->]
bigdata3[3001024] :    1EDD7D0C
dwaddr            :    1EE22D0C
seq               :    1EE22D10
buf[187]          :    1EE22D14
tax               :    1EE22DD0
bigdata[3001024]  :    1EE22DD4
test              :    1EE6DDD4
samplenum         :    1EE6DDD8
sampleport[123]   :    1EE6DDDC
bigdata2[4001024] :    1EE6DFC8
hash show
No hash1    hash2     hash3    valueaddr
255 0x0        0x0        0x0        0x1f0c6564
254 0x0        0x0        0x0        0x1efcc29c
253 0x0        0x0        0x0        0x1eed1fd4
252 0x720752fc 0x2e6526c  0x7e325c42 0x1edd7d0c (data)
251 0x0        0x0        0x0        0x1ecdda44
250 0x0        0x0        0x0        0x1ebe377c
249 0x0        0x0        0x0        0x1eae94b4
248 0xdc63b7f8 0x2052961a 0x76f37377 0x1e9ef1ec (data)
247 0x0        0x0        0x0        0x1e8f4f24
246 0x81d59cf6 0xab7ebcba 0xe5b79834 0x1e7fac5c (data)
245 0x0        0x0        0x0        0x1e700994
244 0x0        0x0        0x0        0x1e6066cc
243 0x75571df3 0xda01101d 0x28af836d 0x1e50c404 (data)
242 0x0        0x0        0x0        0x1e41213c
241 0x0        0x0        0x0        0x1e317e74
240 0x1ae3f5f0 0x65b3d5b1 0x5e3d633b 0x1e21dbac (data)
239 0x0        0x0        0x0        0x1e1238e4
238 0x0        0x0        0x0        0x1e02961c
237 0x0        0x0        0x0        0x1df2f354
236 0x0        0x0        0x0        0x1de3508c
235 0x0        0x0        0x0        0x1dd3adc4
234 0x709391ea 0x4bf5a4ca 0xbb374f06 0x1dc40afc (data)
233 0xfc8524e9 0xaa4a697a 0x545895b0 0x1db46834 (data)
232 0x0        0x0        0x0        0x1da4c56c
231 0x10582ce7 0x73994279 0x1f213222 0x1d9522a4 (data)
230 0x0        0x0        0x0        0x1d857fdc
229 0x0        0x0        0x0        0x1d75dd14
228 0x0        0x0        0x0        0x1d663a4c
227 0x0        0x0        0x0        0x1d569784
226 0x0        0x0        0x0        0x1d46f4bc
225 0x0        0x0        0x0        0x1d3751f4
224 0x0        0x0        0x0        0x1d27af2c
223 0x0        0x0        0x0        0x1d180c64
222 0x8930f5de 0x34a9f12e 0x397bd808 0x1d08699c (data)
221 0x2a1252dd 0x1d31f9b4 0xbae26aeb 0x1cf8c6d4 (data)
220 0xd095adc  0x8a2f5df0 0x520d40e3 0x1ce9240c (data)
219 0x0        0x0        0x0        0x1cd98144
218 0x0        0x0        0x0        0x1cc9de7c
217 0x0        0x0        0x0        0x1cba3bb4
216 0x0        0x0        0x0        0x1caa98ec
215 0x0        0x0        0x0        0x1c9af624
214 0x0        0x0        0x0        0x1c8b535c
213 0x0        0x0        0x0        0x1c7bb094
212 0x0        0x0        0x0        0x1c6c0dcc
211 0x0        0x0        0x0        0x1c5c6b04
210 0x0        0x0        0x0        0x1c4cc83c
209 0x0        0x0        0x0        0x1c3d2574
208 0xefa929d0 0x8ae4dc74 0x55fa180e 0x1c2d82ac (data)
207 0x0        0x0        0x0        0x1c1ddfe4
206 0x0        0x0        0x0        0x1c0e3d1c
205 0xe492d7cd 0x9e4bdc50 0x293d4c00 0x1bfe9a54 (data)
204 0x0        0x0        0x0        0x1beef78c
203 0x7b283cb  0x9c05ca38 0x131111fa 0x1bdf54c4 (data)
202 0x0        0x0        0x0        0x1bcfb1fc
201 0x838b2cc9 0x228366e6 0x78678911 0x1bc00f34 (data)
200 0x0        0x0        0x0        0x1bb06c6c
199 0x0        0x0        0x0        0x1ba0c9a4
198 0x0        0x0        0x0        0x1b9126dc
197 0xeb6f8bc5 0x45d6e13b 0x5868b668 0x1b818414 (data)
196 0x0        0x0        0x0        0x1b71e14c
195 0x1cd7d2c3 0xb6a63bd7 0xe936128a 0x1b623e84 (data)
194 0x0        0x0        0x0        0x1b529bbc
193 0xdb545fc1 0xfdbae1c4 0xe462bdd9 0x1b42f8f4 (data)
192 0x0        0x0        0x0        0x1b33562c
191 0x0        0x0        0x0        0x1b23b364
190 0x0        0x0        0x0        0x1b14109c
189 0x0        0x0        0x0        0x1b046dd4
188 0xf3f152bc 0xcde66c2d 0x81235657 0x1af4cb0c (data)
187 0x0        0x0        0x0        0x1ae52844
186 0x0        0x0        0x0        0x1ad5857c
185 0x0        0x0        0x0        0x1ac5e2b4
184 0x0        0x0        0x0        0x1ab63fec
183 0x0        0x0        0x0        0x1aa69d24
182 0x2f178eb6 0xac5947d1 0x7650fa74 0x1a96fa5c (data)
181 0x8c3529b5 0x85c14f4b 0xf5c94897 0x1a875794 (data)
180 0x0        0x0        0x0        0x1a77b4cc
179 0x0        0x0        0x0        0x1a681204
178 0x2896c530 0xafce8752 0x7da85db0 0x1a586f3c (data)
177 0x8d7b3cb1 0x51d4ef6d 0x9b454e69 0x1a48cc74 (data)
176 0xbeb1a299 0xfb62a503 0xb84c2510 0x1a3929ac (data)
175 0x72170607 0xf90ada2c 0x7c7d785d 0x1a2986e4 (data)
174 0xb1c275ae 0x99233845 0x207b334b 0x1a19e41c (data)
173 0x4d58a456 0x26cadf84 0x150cb00b 0x1a0a4154 (data)
172 0x5ab20b7a 0xc95657c5 0x193c93d3 0x19fa9e8c (data)
171 0xd4307d6f 0x61fa6cd3 0x33565a21 0x19eafbc4 (data)
170 0xd832e831 0xe8a3671  0x6aed428e 0x19db58fc (data)
169 0x7d7324a9 0x654a573b 0xab499fa5 0x19cbb634 (data)
168 0x4dd62f69 0x9f167fa9 0xfc6e5c38 0x19bc136c (data)
167 0xdc13e557 0xdb5cb3e4 0xfdfc9355 0x19ac70a4 (data)
166 0x8ea1eaa3 0xccd2b9ed 0x30cc5bd3 0x199ccddc (data)
165 0x18f6dfa5 0x6370be42 0x7e27c351 0x198d2b14 (data)
164 0x18868d0a 0x987e9bbc 0xf5282373 0x197d884c (data)
163 0x499e0643 0xe9f8e2cb 0x189e1e6d 0x196de584 (data)
162 0xd4202994 0x9a16e493 0x31197e3e 0x195e42bc (data)
161 0x25ac57a1 0xba73d019 0x374cab6d 0x194e9ff4 (data)
160 0x2b75fa0  0x2d6d745d 0xdfa38165 0x193efd2c (data)
159 0xd7469e64 0x69263326 0xbf968169 0x192f5a64 (data)
158 0x42a2593c 0xf8ba7afe 0x29159fdf 0x191fb79c (data)
157 0xd3679302 0xbcf0b6b3 0x288750b2 0x191014d4 (data)
156 0x17f2fb5f 0xffd29eeb 0x2053e094 0x1900720c (data)
155 0x8933159b 0x273a720f 0x7fb50c3c 0x18f0cf44 (data)
154 0x46ea7016 0x8e54e79c 0xcde5dd8a 0x18e12c7c (data)
153 0xe41bfd90 0x227ae46c 0x8d13758f 0x18d189b4 (data)
152 0x4a44d051 0x74feb44b 0xb3170bd7 0x18c1e6ec (data)
151 0x10c51366 0x223ae935 0xb2c22e3a 0x18b24424 (data)
150 0x7f2d9496 0xecb78d67 0x36998e80 0x18a2a15c (data)
149 0x71761095 0xfd79588  0xbfbe52b6 0x1892fe94 (data)
148 0x2f8ab137 0xfdfaec9d 0xdbb3e66c 0x18835bcc (data)
147 0x38601e1b 0x126664dc 0xd783c5b4 0x1873b904 (data)
146 0xb6e2680e 0xbaca5fca 0xfde90c46 0x1864163c (data)
145 0x26009378 0x89ad2b56 0xe116565b 0x18547374 (data)
144 0xb3e45420 0x1831628e 0x779548ed 0x1844d0ac (data)
143 0x22219e1e 0x5c7baec3 0x76078780 0x18352de4 (data)
142 0xe6b4f643 0x1f59869b 0x7ed337a6 0x18258b1c (data)
141 0xb7ac7d0a 0x6edfffec 0x93650ab8 0x1815e854 (data)
140 0x155df08c 0xc2f1fc1c 0xd393a2bd 0x1806458c (data)
139 0x23054f13 0x38c59533 0x2da4c6c4 0x17f6a2c4 (data)
138 0xb6e1884b 0xa959dceb 0xbb27d872 0x17e6fffc (data)
137 0x27244275 0xed1310a6 0xbab5171f 0x17d75d34 (data)
136 0x75964d81 0xfa9d1aaf 0x7785df99 0x17c7ba6c (data)
135 0xe3b12a28 0xae3138fe 0xb261a739 0x17b817a4 (data)
134 0xb2a9a161 0xdfb74189 0x5fd79a27 0x17a874dc (data)
133 0x29be9604 0x2eef02fb 0x6cb897dd 0x1798d214 (data)
132 0xbc5a515c 0xbf734b23 0xfa3b896b 0x17892f4c (data)
131 0x2d9f9b62 0xfb39876e 0xfba94606 0x17798c84 (data)
130 0xe90af33f 0xb81baf36 0xf37df620 0x1769e9bc (data)
129 0xb8127876 0xc99dd641 0x1ecbcb3e 0x175a46f4 (data)
128 0x27e51207 0xcd8f1a14 0xe59f4beb 0x174aa42c (data)
127 0xe12e73ff 0x97244af4 0x9f157f4a 0x173b0164 (data)
126 0xd148c97d 0x1088d3da 0x255f91f0 0x172b5e9c (data)
125 0x806627d  0xeb04dbc8 0x77d1de10 0x171bbbd4 (data)
124 0xe0dafee7 0xe8a54132 0xcdcd0e55 0x170c190c (data)
123 0x7d64d130 0x9b4b476a 0xe44a6e06 0x16fc7644 (data)
122 0x422b7361 0x448b42c2 0x8d3ba650 0x16ecd37c (data)
121 0x55c1dc4d 0xab17ca83 0x810b8588 0x16dd30b4 (data)
120 0xfc445f78 0xc65842f9 0xd314c962 0x16cd8dec (data)
119 0xdb43aa58 0x3bbf195  0xab614c7a 0x16bdeb24 (data)
118 0x11fcac46 0x867c7e17 0xba9af00d 0x16ae485c (data)
117 0x9ab66bf5 0x61086ff2 0xad93b755 0x169ea594 (data)
116 0x84186b1e 0x17e037cf 0x2c19eebb 0x168f02cc (data)
115 0x15dda120 0x53aafb82 0x2d8b21d6 0x167f6004 (data)
114 0x5cad11f2 0xa134761b 0x14a57fb2 0x166fbd3c (data)
113 0x476faed4 0x4424f18b 0xe0bbe950 0x16601a74 (data)
112 0x80504234 0x610eaaad 0xc8e9acee 0x165077ac (data)
111 0x5e9560ef 0x295c5454 0x2df0c74d 0x1640d4e4 (data)
110 0x1dee6de3 0x12e0acf5 0xe16eccbd 0x1631321c (data)
109 0x22a1cfb2 0xcd20a95d 0x881f04eb 0x16218f54 (data)
108 0x354b609e 0x22bc211c 0x842f2733 0x1611ec8c (data)
107 0xbbc9168b 0x8a101a0a 0xae45eec1 0x160249c4 (data)
106 0xaad75dea 0x400cd65  0x8935d03f 0x15f2a6fc (data)
105 0x637c6c67 0x3cc45bde 0x96f97fc8 0x15e30434 (data)
104 0xd22f67e7 0x9984d0d  0x3ecfb640 0x15d3616c (data)
103 0xcc256967 0xa350e06e 0xf7b2ae08 0x15c3bea4 (data)
102 0xf698ab3f 0xad581206 0x7a617e   0x15b41bdc (data)
101 0xf2b9a659 0x788e9793 0x976bb0a5 0x15a47914 (data)
100 0xa00ba9ad 0x6f009d9a 0x5a5b7823 0x1594d64c (data)
99  0x362cce04 0x3bacbfcb 0x9fbf0083 0x15853384 (data)
98  0x6734454d 0x4a2ac6bc 0x72093d9d 0x157590bc (data)
97  0x2d88d761 0x954c35db 0x5b242207 0x1565edf4 (data)
96  0xfa8a6a9a 0x39c4c0e4 0x5b8e5dce 0x15564b2c (data)
95  0xc5c5c8cb 0xe604c54c 0x32ff9598 0x1546a864 (data)
94  0x3f339ab2 0x959c84bd 0x1fb6ce89 0x1537059c (data)
93  0xaef6508c 0xd1d648f0 0x1e2401e4 0x152762d4 (data)
92  0xc910c5c  0x35a44da3 0x6877cff5 0x1517c00c (data)
91  0x6a6338d1 0x92f460a8 0x16f0b1c2 0x15081d44 (data)
90  0x3b7bb398 0xe37219df 0xfb468cdc 0x14f87a7c (data)
89  0xa6c59c4f 0x909c1f87 0xd2c1ec8f 0x14e8d7b4 (data)
88  0x414a3d8  0x7f98092a 0x2c25e2a0 0x14d934ec (data)
87  0x998a3e1e 0x4f5c1a2f 0xbbb024d9 0x14c99224 (data)
86  0x77091456 0xc38868a5 0x5af107ea 0x14b9ef5c (data)
85  0x8e609132 0xa0c0926e 0xb7800701 0x14aa4c94 (data)
84  0xe2e727   0x86ca978  0x9deacef3 0x149aa9cc (data)
83  0x9de2a525 0x7a989210 0xe152c0a6 0x148b0704 (data)
82  0xc276f1b  0x3ed25e5d 0xe0c00fcb 0x147b643c (data)
81  0xc8b20746 0x7df07605 0xe814bfed 0x146bc174 (data)
80  0x99aa8c0f 0xc760f72  0x5a282f3  0x145c1eac (data)
79  0x3b5b0189 0xa0580c82 0x45542af6 0x144c7be4 (data)
78  0x2cb1aea5 0x4fc484c3 0x4964092e 0x143cd91c (data)
77  0xa233d8b0 0xe768bfd5 0x630ec0dc 0x142d3654 (data)
76  0x219a16c4 0x1d0e739  0xd01eb7   0x141d938c (data)
75  0xb47ed19c 0x904caee1 0x96530001 0x140df0c4 (data)
74  0x25bb1ba2 0xd40662ac 0x97c1cf6c 0x13fe4dfc (data)
73  0xb036f8b6 0xe6a23383 0x72a34254 0x13eeab34 (data)
72  0x12c77530 0x4a8c3073 0x3255ea51 0x13df086c (data)
71  0x52dda1c  0xa510b832 0x3e65c989 0x13cf65a4 (data)
70  0x8bafac09 0xdbc8324  0x140f007b 0x13bfc2dc (data)
69  0x59c1ae3f 0x32cca9b6 0x6131b0be 0x13b02014 (data)
68  0xc8046401 0x768665fb 0x60a37fd3 0x13a07d4c (data)
67  0x5d898715 0x442234d4 0x85c1f2eb 0x1390da84 (data)
66  0xc037a8c2 0x37cc328c 0xac4692b8 0x138137bc (data)
65  0xff780a93 0xe80c3724 0xc5375aee 0x137194f4 (data)
64  0xe892a5bf 0x790bf65  0xc9077936 0x1361f22c (data)
63  0x84432d3e 0xa2377f71 0x9573f4e4 0x13524f64 (data)
62  0x0        0x0        0x0        0x1342ac9c
61  0x6610d3aa 0xaf3c8473 0xe36db0c4 0x133309d4 (data)
60  0x0        0x0        0x0        0x1323670c
59  0xd2d02fac 0x606ff0ed 0xcf52edb9 0x1313c444 (data)
58  0x0        0x0        0x0        0x1304217c
57  0x0        0x0        0x0        0x12f47eb4
56  0x4734e8f4 0xf1f3b935 0x59d1f30f 0x12e4dbec (data)
55  0xd6f122ca 0xb5b97578 0x58433c62 0x12d53924 (data)
54  0x12644a97 0xf69b5d20 0x50978c44 0x12c5965c (data)
53  0xf667e374 0xc4afafe6 0xf1e73a87 0x12b5f394 (data)
52  0xfdd7dbf3 0x3137bb0e 0xbb665252 0x12a650cc (data)
51  0x0        0x0        0x0        0x1296ae04
50  0x437cc1de 0x871d2457 0xbd21b15a 0x12870b3c (data)
49  0xdec2ee09 0xf4f3220f 0x94a6d109 0x12776874 (data)
48  0xe18d4c58 0x2b3327a7 0xfdd7195f 0x1267c5ac (data)
47  0x78e59561 0x6c0394f0 0xdb8df375 0x125822e4 (data)
46  0x0        0x0        0x0        0x1248801c
45  0x0        0x0        0x0        0x1238dd54
44  0x68331cab 0xa0abf2d6 0x2de54ce4 0x12293a8c (data)
43  0x0        0x0        0x0        0x121997c4
42  0xf9f6d695 0xe4e13e9b 0x2c778389 0x1209f4fc (data)
41  0x0        0x0        0x0        0x11fa5234
40  0x0        0x0        0x0        0x11eaaf6c
39  0x0        0x0        0x0        0x11db0ca4
38  0x0        0x0        0x0        0x11cb69dc
37  0x0        0x0        0x0        0x11bbc714
36  0x0        0x0        0x0        0x11ac244c
35  0x0        0x0        0x0        0x119c8184
34  0x0        0x0        0x0        0x118cdebc
33  0x0        0x0        0x0        0x117d3bf4
32  0x0        0x0        0x0        0x116d992c
31  0x0        0x0        0x0        0x115df664
30  0x0        0x0        0x0        0x114e539c
29  0x0        0x0        0x0        0x113eb0d4
28  0x0        0x0        0x0        0x112f0e0c
27  0x0        0x0        0x0        0x111f6b44
26  0x0        0x0        0x0        0x110fc87c
25  0x0        0x0        0x0        0x110025b4
24  0x0        0x0        0x0        0x10f082ec
23  0x0        0x0        0x0        0x10e0e024
22  0x0        0x0        0x0        0x10d13d5c
21  0x0        0x0        0x0        0x10c19a94
20  0x0        0x0        0x0        0x10b1f7cc
19  0x0        0x0        0x0        0x10a25504
18  0x0        0x0        0x0        0x1092b23c
17  0x0        0x0        0x0        0x10830f74
16  0x0        0x0        0x0        0x10736cac
15  0x0        0x0        0x0        0x1063c9e4
14  0x0        0x0        0x0        0x1054271c
13  0x0        0x0        0x0        0x10448454
12  0x0        0x0        0x0        0x1034e18c
11  0x0        0x0        0x0        0x10253ec4
10  0x0        0x0        0x0        0x10159bfc
9   0x0        0x0        0x0        0x1005f934
8   0x0        0x0        0x0        0xff6566c
7   0x0        0x0        0x0        0xfe6b3a4
6   0x0        0x0        0x0        0xfd710dc
5   0x0        0x0        0x0        0xfc76e14
4   0x0        0x0        0x0        0xfb7cb4c
3   0x0        0x0        0x0        0xfa82884
2   0x0        0x0        0x0        0xf9885bc
1   0x0        0x0        0x0        0xf88e2f4
0   0x0        0x0        0x0        0xf79402c
hash size:150
sizeof(T_HashInfo)     :1024700
sizeof(T_HashInfo) % 4 :0
hash clear
hash show
No hash1    hash2     hash3    valueaddr
hash size:0
Hello World!
D:\Qtexample\git\qtexample\hash_table-build-desktop-Qt_4_8_1_for_Desktop_-_MinGW__Qt_SDK____\debug\hash_table.exe ÍË³ö£¬ÍË³ö´úÂë: 0
 {1 ?}

*/
