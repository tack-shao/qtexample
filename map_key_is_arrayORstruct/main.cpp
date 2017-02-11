//#include <map>
//#include <string>
//#include <iostream>

//using namespace std;

//typedef struct tagStudentInfo

//{

//    int      nID;

//    string   strName;

//}StudentInfo, *PStudentInfo;  //学生信息



//class sort

//{

//public:

//    bool operator() (StudentInfo const &_A, StudentInfo const &_B) const

//    {

//        if(_A.nID < _B.nID) return true;

//        if(_A.nID == _B.nID) return _A.strName.compare(_B.strName) < 0;

//        return false;

//    }

//};


//void test_insert_1_fmt(void)
//{
//    //用学生信息映射分数

//    map<StudentInfo, int, sort>mapStudent;

//    StudentInfo studentInfo;

//    studentInfo.nID = 1;

//    studentInfo.strName = "student_one";

//    mapStudent.insert(pair<StudentInfo, int>(studentInfo, 90));

//    studentInfo.nID = 2;

//    studentInfo.strName = "student_two";

//    mapStudent.insert(pair<StudentInfo, int>(studentInfo, 80));

//    cout << "map size :" << mapStudent.size();
//    cout << endl;
//    mapStudent.clear();

//}


//void test_insert_2_fmt(void)
//{
//    //用学生信息映射分数

//    map<StudentInfo, int, sort>mapStudent;

//    StudentInfo studentInfo;

//    studentInfo.nID = 1;

//    studentInfo.strName = "student_one";

//    mapStudent.insert(make_pair(studentInfo, 90));

//    studentInfo.nID = 2;

//    studentInfo.strName = "student_two";

//    mapStudent.insert(make_pair(studentInfo, 80));

//    cout << "map size :" << mapStudent.size();
//    cout << endl;
//    mapStudent.clear();

//}




//int main()

//{
//    test_insert_1_fmt();
//    test_insert_2_fmt();

//}

