/*
创新点：删去了Reader类和加入书车这一操作，用户直接选择借书数量，然后直接借书。
        用户账号不用图书管理者添加可以自己申请。添加了索书号和馆藏地方便读者找书。
		另，同一书目数量有限，不能无限外接。添加了应还书日期和逾期不予借书的操作 
*/ 

#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <typeinfo>
#include <cstring>
#include <string>
using namespace std;

const int LIMIT=5;    //读者借书限额
enum  State
{
	READER,LIB,SHELF   
};     //图书的状态（在读者处、读者归还但是图书管理员还未来得及上架、在书架上）


class object       //建立一个object类，多态的时候有用 
{
};



class Date:public object      //创建一个Date类
{
	private:
		int year,month,day; 
		int DayOfMonth(int y,int m)const    //返回第y年的第m个月有多少天 ,这是一个private函数！！！
		{
			int d = 0;
			switch(m)
			{
				case 1:case 3:case 5: case 7:case 8:case 10:case 12:
				d=31;
				break;
				case 4:case 6: case 9:case 11:
				d=30;
				break;
				case 2:
					d = 28 + IsLeapyear(y);     //是否为闰年 
					break;
			}
			return d;
		 } 
	
	public:
		Date()                        
		{
			//time_t是一种时间表示方式，总秒数，long类型 
			time_t curtime = time(NULL);          //timer=NULL时得到机器日历时间 
			tm tim = *localtime(&curtime);        // 返回一个以tm结构表达的机器时间信息 ,tm就有年月日等方便读 
			day = tim.tm_mday ;                    
			month = tim.tm_mon + 1;               // int tm_mon;  /*月,从一月算起，0-11*/  1 + p->tm_mon
			year = tim.tm_year + 1900;            // int tm_year;  /*年,从1900至今已经多少年*/  1900 + p->tm_year 
		}
		
		Date(int y,int m,int d):year(y),month(m),day(d)
		{
			if ( (y<=0) || (m<=0 || m>12) || (d<=0 || d>DayOfMonth(y,m) ) ) 
			{
				cout<<"Invaild date, date has been set to 1900-1-1"<<endl;   //日期不合法
				year = 1900;
				month = day =1;        //默认设置为1900-1-1 
			}
		}
		
		void SetDate(int y,int m,int d)
		{
			year=y;
			month=m;
			day=d;
			if ( (y<=0) || (m<=0 || m>12) || (d<=0 || d>DayOfMonth(y,m) ) ) 
			{
				cout<<"Invaild date, date has been set to 1900-1-1"<<endl;   //日期不合法
				year = 1900;
				month = day =1;        //默认设置为1900-1-1 
			}
		} 
		virtual ~Date()  { }       //虚析构函数
		
		int GetYear()const
		{
			return year;
		 } 
		 
		int GetMonth()const
		{
			return month;
		 } 
		 
		int GetDay()const
		{
			return day;
		 } 
		
		bool IsLeapyear()const       //判断当前日期的年是否为闰年
		{
			if ((year%4==0 ||year%100==0) && year%400!=0)
			return true;
			else
			return false;
		 } 
		 
		 bool IsLeapyear(const int y)const       //判断y（任意）是否为闰年 
		{
			if ((y%4==0 && y%100!=0) || y%400==0)
			return true;
			else
			return false;
		 } 
		 
		 void display()const                  //显示日期 
		 {
		 	cout<<year<<"-"<<month<<"-"<<day;
		 }
		 
		 void operator = (Date date)   //重载赋值符 
		 {
		 	year=date.year;
		 	month=date.month;
		 	day=date.day;
		 }
		 
		 bool operator < (Date date)   //重载比较符 
		 {
		 	if (year<date.year)
		 	return true;
		 	else if (year==date.year)
		 	{
		 		if(month<date.month)
		 		return true;
		 		else if (month==date.month)
		 		{
		 			if (day<date.day)
		 			return true;
		 			else
		 			return false;
				 }
				else 
				return false;
			 }
		    else
		    return false;
		  } 
	
};

class BookData:public object
{
	private:
		long long BookID;            //图书条形码，独一无二
		char SearchBookID[20];       // 索书号，相同的书的索书号一样 
		char PlaceOfBook [40];       // 书本的馆藏地 
		char name[40];
		State state;
		long long PIN;               //若已借出，借书读者id
		
	public:
		BookData(long long BookID,const char *searchbookid,const char *name,
		       const char *place,State state=SHELF,long long PIN=0)  //默认在架上，无读者借阅 
		{
			SetID(BookID);
			SetName(name);
			SetSeachID(searchbookid);
			SetPlaceOfBook(place);
			SetState(state);
			SetPIN(PIN); 
		 } 
		BookData()     //这个一般不调用吧。。。 
		{
			BookID = 0;
			PIN = 0;
		}
		const long long GetID()
		{
			return BookID;
		}
		const char * GetName()
		{
			return name;
		}
		State GetState()
		{
			return state;
		}
		long long GetPIN()
		{
			return PIN;
		}
		void ShowData()
		{
			cout<<BookID<<"\t"<<SearchBookID<<"\t"<<name<<"\t";
			switch(state)             //改 ,书籍状态的打印问题，只能打印出枚举型的数字，不能打印出中文
			{
				case 0: cout<<"READER";
				break;
				case 1: cout<<"LIB";
				break;
				case 2: cout<<"SHELF";
				break;
			}
			cout<<"\t"<<PlaceOfBook<<"\t"<<PIN<<"\t"<<endl;
		}
		void SetID(long long BookID)
		{
			this->BookID = BookID; 
		}
		void SetName(const char *i_name)
		{
			strcpy(name,i_name);
		}
		void SetSeachID(const char *i_SearchBookID)
		{
			strcpy(SearchBookID,i_SearchBookID);
		}
		void SetPlaceOfBook(const char *place)
		{
			strcpy(PlaceOfBook,place);
		}
		void SetState(State state)
		{
			this->state = state;
		}
		void SetPIN(long long PIN)
		{
			this->PIN = PIN;
		}
};


class ReaderData : public object      //读者所借书 -类                   
{
	protected:
		long long PIN;                //读者的借书证号
		char name[20];                //读者姓名 
		long long BookList[LIMIT];    //借书列表，存的应该是bookid,初始状态为0 
		Date BorrowDate[LIMIT];       //借书日期，没有传参就默认当前时间
		Date ReturnDate[LIMIT];       //还书日期，逾期不还书，不给予借书的权利。 
		int NumOfBorrowed;            //已借书数数 
		
	public:
		ReaderData(long long PIN,const char *name)
		{
			SetID(PIN);
			SetName(name);
			NumOfBorrowed = 0;
			for(int i=0;i<LIMIT;i++)
			BookList[i]=0;     
		 } 
		ReaderData()     //这个一般也不用。。。。 
		{
			PIN = 0;
			NumOfBorrowed = 0;
			for(int i=0;i<LIMIT;++i)
			BookList[i]=0;
			
		 } 
		void SetID(long long PIN)
		{
			this->PIN = PIN;
		}
		void SetName(const char *i_name)
		{
			strcpy(name,i_name);
		}
		long long GetID()
		{	
			return PIN;
		}
	
		const char * GetName()
		{
			return name;
		}
		int GetNumOfBorrowed()
		{
			return NumOfBorrowed;
		}

        long long BorrowBook(long long BookID)    //书ID 
		{
		    Date daynow;
			for (int i=0;i<LIMIT;i++) 
			{
				
				if (BookList[i]!=0 && ReturnDate[i]<daynow)
				{
					cout<<"Overdue book,please return !"<<endl;
					return 0;
				}
			}
			for (int i=0;i<LIMIT;i++)   //借书名不是按顺序存储的 
			{
				if(BookList[i]==0)
				{
					BookList[i]=BookID;
					BorrowDate[i]=daynow;
					ReturnDate[i].SetDate(daynow.GetYear(),daynow.GetMonth()+3,daynow.GetDay());    //还书期限为三个月 
					NumOfBorrowed++;
					return BookID;      
				}
			}
			cout<<"Book reach the limit!"<<endl;   //图书超过额度，不能借书了 
			return 0;
		}   
        		
		void ShowData()  //打印读者的所有借的书的信息 
		{
			cout<<PIN<<"\t"<<name<<endl;   //读者借书证号及姓名 
			
			for (int i=0;i<LIMIT;i++)
			{
				if(BookList[i])
				{
					cout<<i+1<<": "<<BookList[i]<<"\t";  
					BorrowDate[i].display();
					cout<<"\t";
					ReturnDate[i].display();
					cout<<endl ;      //序号、书的id、借书日期，还书日期 
				}
			}
		}
		
		long long ReturnBook(long long BookID)
		{
			for (int i=0;i<LIMIT;i++)
			{
				if (BookList[i]==BookID)
				{
					BookList[i]=0;
					--NumOfBorrowed;
					Date now;
					ReturnDate[i]=now;
					BorrowDate[i]=now;
					return BookID;
				}
			}
			return 0;
		 } 
};


template <class T>           //T表示的是记录的类型，因此可以是ReaderData和BookData 
class Database: public object
{
	private:
		fstream File;
		char FileName[40];      //文件名
		long long FileLen,rec_size;             //文件大小，记录长度
		typedef map< long long,T,less<long long> > mtype;         //前关键字，后数据值，此处的less函数我认为可以省略 
		mtype RecMap;         //数据记录库,数据存储位置 
	public:
		Database(const char * FileName)
		{
			strcpy(this->FileName,FileName);
			File.open(FileName,ios::in|ios::binary);    
			rec_size = sizeof(T);
			if(File.is_open())
			{
				File.seekg(0,ios::end);  //读指针到文件尾 
				if ( (FileLen = File.tellg() )>0 )  //filelen为文件总长度，并大于0时执行 
				{
         		    T Object;
					File.seekg(0,ios::beg);    //读指针移到文件头 
					do{
						File.read((char *) &Object,rec_size);
						//value_type 是pair类型的，它的值成员可以修改，但键成员不能修改
						RecMap.insert(typename mtype::value_type(Object.GetID(),Object));   //以Object的ID(PIN)作为键值
					  } while(File.tellg()<FileLen);
					
				}
			}
			File.close();
		}
		~Database()
		{
			SaveMap();          //将RecMap(STL)中的数据保存到文件中 
		}
		void Insert(T & Object)
		{   
			if(RecMap.count(Object.GetID()))    //防止重复添加 
			cout<<"already included!"<<endl;
			else 
			RecMap.insert(typename mtype::value_type(Object.GetID(),Object));   
			//cout<<typeid(T).name()<<"inserted"<<endl;	
		}
		void Delete(long long objID)
		{
			 Query(objID);   //找到键值为ObjID的记录
			 RecMap.erase(objID); 
		}
		T *Query(long long ObjID)        //作用是找到键值为ObjID的记录 
		{
			typename mtype::iterator iter;
			iter = RecMap.find(ObjID);
			if(iter==RecMap.end())
			{
				cout<<ObjID<<" not found!"<<endl;
				return NULL;
			 } 
			 else
			 return &(iter->second);       //返回数据值，即为BookData或者ReaderData类型 
		}
		bool QueryName(const char * objName,long long *pointID)  //返回name(part)为objName的ID或者PIN 
		{
			typename mtype::iterator iter;
			int i=0;
			for(iter=RecMap.begin();iter!=RecMap.end();++iter)
			{
				if(strstr((iter->second).GetName(),objName)!=NULL)  //strstr函数返回后字符串第一次出现在前字符串中的位置 
				pointID[i++]=iter->second.GetID();
			//	return &(iter->second);      //只要有公共子串就返回 
			}
			if(i==0) 
			{
				 cout<<objName<<" in "<<typeid(T).name()<<" not found!"<<endl;   //typeid是操作符，获知一个变量的具体类型 
				return false;
			}
			else
			return true;
		}
		void SaveMap()      //将RecMap(STL)中的数据保存到文件中 
		{
			typename mtype::const_iterator  iter;
			T Object;     
			File.open(FileName,ios::out|ios::binary|ios::trunc);
			for (iter=RecMap.begin();iter!=RecMap.end();++iter)
			{
				File.write((char *)&iter->second,rec_size); 
			 } 
			 File.close();
			
		}
		void ShowAllData()
		{
			typename mtype::iterator  iter;
			T Object;    
			cout<<"Date in "<<typeid(T).name()<<":"<<endl;
			for (iter=RecMap.begin();iter!=RecMap.end();++iter)
			(iter->second).ShowData();
		}
		 
};


class Librarian :public object
{
	private:
		long long ID;    //标识，管理员id 
		char name[20];        //管理员姓名
		char passwd[9];             //口令,好像是固定的，应该可以优化 
		
	public:
		Librarian(long long ID,const char *name):ID(ID)  //管理员好像不用ID和姓名，只需要密码 
		{
			strcpy(this->name ,name);
			strcpy(passwd,"123");
		 } 
		 char login()   //登录成功返回X,失败返回E 
		 {
		 	char pw[9];
		 	for (int i=0;i<3;i++)   //有三次机会输入密码 
		 	{
		 		cout<<"Enter password:";
		 		cin>>pw;
		 		if(strcmp(pw,passwd)==0)
		 		return 'X';
			 }
			 cout<<"Login fail !"<<endl;
			 return 'E';
		 }
};


///////////////////////////////////////////////////////////////////////////
//                        mian 函数的实现                              //
//////////////////////////////////////////////////////////////////////////
int main ()
{
	Database<BookData> BookBase("mybooks.dat");  //打开书籍数据库
	Database<ReaderData> ReaderBase("myreader.dat");  //打开读者数据库
	char choice ='X';
	while(!(choice=='E' || choice=='e')) //  不退出时,不识别大小写 
	{
		cout<<"(L)ibrarian entry, (R)eader entry, Re(t)urn book, (E)xit: ";
		cin>>choice;
		Librarian *mqr=NULL;
		ReaderData *rdr=NULL;
		
		switch(choice)
		{
			//--------------------------管理员入口-------------------------------------//
			case 'L':case 'l':
				mqr=new Librarian(101,"yjc");  //这个都可要可不要的 
				choice = mqr->login();     //成功返回'X',失败返回'E'
				while (!(choice=='E'||choice=='e'))     //登录成功时 
				{
					cout<<"(A)dd Book, ";
					cout<<"(P)ut book to shelf, (S)howAllData, (E)xit: "; //此处的Show为打印所以书和读者 
					cin>>choice;
					switch(choice)
					{
						long long ID;
						char name[40];
						case 'A':case 'a':          //添加书籍
						{
							char place[40];
							char search[20];
							cout<<"Input a book ID and a searchbookID and a name and a place:";
							cin>>ID;
							cin.ignore();
							cin.get(search,20,' ');
							cin.ignore();
							cin.get(place,40,' ');
							cin.ignore();
							cin.get(name,40,'\n');  
							BookData s = BookData(ID,search,place,name);
							BookBase.Insert(s);
							break;
						}
						case 'P':case 'p':
							cout<<"Input a book ID:";
							cin>>ID;
							if(BookBase.Query(ID)==NULL )
							cout<<"No such a book!"<<endl;
							else
							BookBase.Query(ID)->SetState(SHELF);
							break;
						case 'S':case 's':
							ReaderBase.ShowAllData();
							BookBase.ShowAllData();
							break;
						case 'E':case 'e':
							break;
						default:
							cout<<"Unavailable function !\n";
					}
				}
											
			delete mqr;
			choice='X';
			break;
			//----------------------管理员退出--------------------//
			//----------------------读者入口----------------------//
			case 'R':case 'r':
			long long PIN,BookID;
			int i,t1,t2;
			char name[40];
			char a;
			cout<<"already a reader ?: (Y)es, (N)o,but want to sign: ";
			cin>>a;
			if (a=='Y' ||a=='y')
			{
				for (i=0;i<3;++i)
				{
					cout<<"Input PIN:";
					cin>>PIN;
					if (ReaderBase.Query(PIN)!=NULL)  //已经在读者库中存在 
					{
						rdr=ReaderBase.Query(PIN); 
						break; 
					}
				}
				if(i==3)
				{
					cout<<"Check in failed!"<<endl;
					choice='E';
				 }
			}
			else if (a=='N' || a=='n')
			{
				cout<<"Input a reader PIN and input a name: ";
 				cin>>PIN;      //PIN
				cin.ignore() ;
				cin.get(name,20,'\n');
				ReaderData s(PIN,name);
				ReaderBase.Insert( s );
				rdr=ReaderBase.Query(PIN); 
				
			}
			else 
			{
				cout<<"Unavailable function!\n";
				choice = 'E';
				
			}
			
			while (!(choice=='E'||choice=='e'))    //登录成功并不退出
			{
				cout<<"(B)orrow book, (Q)uery book by name, (L)ist my books, (E)xit:";
				cin>>choice;
				switch(choice)
				{
					case 'B':case 'b':      //借书,一次性“借完 ” 
						int num;      //表示想要借的图书数
						cout<<"intput the number of books you wanna borrow:";
						cin>>num; 
						t1=rdr->GetNumOfBorrowed();     //已经借了的图书数 
						if (num<=0 || num>LIMIT-t1)
						{
							cout<<"Invalid number!"<<endl;
							break;
						}
						for (i=0;i<num;)
						{
							cout<<"input the BookID:";
							cin>>BookID;
							if(BookBase.Query(BookID)==NULL);
							else if (BookBase.Query(BookID)->GetState()!=SHELF)
							cout <<"not available!"<<endl;
							 
							 else
							{
								if (rdr->BorrowBook(BookID)>0)   //返回书的ID，应该分借书成功或者失败
								{
									BookBase.Query(BookID)->SetState(READER);
									BookBase.Query(BookID)->SetPIN(PIN);
									i++;									
								}
								else;
							}          

						}
						break;
					case 'Q':case 'q':       //输入书名，查询书籍 
					{
					    long long * pointid;
					    long long bookid[10]={0};
					    pointid = bookid;
						cout<<"Input a book name(part):";
						cin.ignore();
						cin.get(name,40,'\n');
						if(BookBase.QueryName(name,pointid))
						{
							for (int i=0;bookid[i]!=0;i++)
							BookBase.Query(bookid[i])->ShowData(); 
						}
						break;
					}
					case 'L':case 'l':     //查询书单 
						ReaderBase.Query(PIN)->ShowData();
						break;
					case 'E':case 'e':
						break;
					default:
						cout<<"Unavailable function!"<<endl;
				}
			}
			 
		//	delete mgr;
			choice ='X';
			break;
			//-------------------------读者退出--------------------------//
			//--------------------------还书入口--------------------------//
			case 'T':case 't':
				cout<<"Input a book ID:";   
				cin>>BookID;
				if(BookBase.Query(BookID)!=NULL)  //书库中有此书 
				{
					BookBase.Query(BookID)->SetState(LIB);   //还未上架 
					if((PIN=BookBase.Query(BookID)->GetPIN())>0)   //有主人，已借出
					{ 
						ReaderBase.Query(PIN)->ReturnBook(BookID);
						BookBase.Query(BookID)->SetPIN(0);
					}
				 } 
				break;
			case 'E':case 'e':   //退出 
				break;
			default:
				cout<<"Unavailable function !"<<endl;
		}      //switch
	}          //while
						 
	return 0;
}
 
//还书问题，上架问题，没有借出去的书可以还，已经在架上的书可以上架，只是操作没有改变结果。 
