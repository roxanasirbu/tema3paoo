#include <iostream>
using namespace std;
#include <mutex>
// thread
#include <thread>
using namespace std;
mutex mtx;

class Student 
{
public:
    int id_student;
    int lockStd;
    Student(int id_student){
        this->id_student = id_student;
        cout<<"\n Constructor Student \n";
    };
    ~Student(){
        cout<<"\n Destructor Student \n";
    }
    void getID(){
        cout<<"The student has this id: " << id_student <<endl;
    }

    void setlockStd(int lockStd){
        this->lockStd = lockStd;
    }
};

Student *createStudent(const int id_student){
    return new Student(id_student);
};

void lock(Student& student){
    student.setlockStd(1); //1 = true
    cout<<"locked"<<endl;
};

void unlock(Student& student){
    student.setlockStd(0); // 0 = false
    cout<<"unlocked"<<endl;
};

class Uncopyable
{
protected:           // allow construction
    Uncopyable() {}  // and destruction of
    ~Uncopyable() {} // derived objects...
private:
    Uncopyable(const Uncopyable &); // ...but prevent copying
    Uncopyable &operator=(const Uncopyable &);
};

class Lock: Uncopyable{
    private:
       Student &StudentP;

    public:
        Lock(Student &ptr): StudentP(ptr){ //constructorul face lock
            lock(StudentP);
        }
        ~Lock(){ 
            unlock(StudentP);  //destructorul face unlock
        }
};

int main(){
    auto_ptr<Student> st1(createStudent(7)); //se creaza studentul cu id = 7 
    st1->getID();
    auto_ptr<Student> st2(st1);   //se copiaza in st2 pe st1
     st2->getID();
     Student st(2);  //declarare student cu id = 2
    Lock lockedStd(st); //utilizarea clasei Lock
    st.getID();
   
    return 0;
}