/*
���µ㣺ɾȥ��Reader��ͼ����鳵��һ�������û�ֱ��ѡ�����������Ȼ��ֱ�ӽ��顣
        �û��˺Ų���ͼ���������ӿ����Լ����롣���������ź͹ݲصط���������顣
		��ͬһ��Ŀ�������ޣ�����������ӡ������Ӧ�������ں����ڲ������Ĳ��� 
*/ 

#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include <typeinfo>
#include <cstring>
#include <string>
using namespace std;

const int LIMIT=5;    //���߽����޶�
enum  State
{
	READER,LIB,SHELF   
};     //ͼ���״̬���ڶ��ߴ������߹黹����ͼ�����Ա��δ���ü��ϼܡ�������ϣ�


class object       //����һ��object�࣬��̬��ʱ������ 
{
};



class Date:public object      //����һ��Date��
{
	private:
		int year,month,day; 
		int DayOfMonth(int y,int m)const    //���ص�y��ĵ�m�����ж����� ,����һ��private����������
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
					d = 28 + IsLeapyear(y);     //�Ƿ�Ϊ���� 
					break;
			}
			return d;
		 } 
	
	public:
		Date()                        
		{
			//time_t��һ��ʱ���ʾ��ʽ����������long���� 
			time_t curtime = time(NULL);          //timer=NULLʱ�õ���������ʱ�� 
			tm tim = *localtime(&curtime);        // ����һ����tm�ṹ���Ļ���ʱ����Ϣ ,tm���������յȷ���� 
			day = tim.tm_mday ;                    
			month = tim.tm_mon + 1;               // int tm_mon;  /*��,��һ������0-11*/  1 + p->tm_mon
			year = tim.tm_year + 1900;            // int tm_year;  /*��,��1900�����Ѿ�������*/  1900 + p->tm_year 
		}
		
		Date(int y,int m,int d):year(y),month(m),day(d)
		{
			if ( (y<=0) || (m<=0 || m>12) || (d<=0 || d>DayOfMonth(y,m) ) ) 
			{
				cout<<"Invaild date, date has been set to 1900-1-1"<<endl;   //���ڲ��Ϸ�
				year = 1900;
				month = day =1;        //Ĭ������Ϊ1900-1-1 
			}
		}
		
		void SetDate(int y,int m,int d)
		{
			year=y;
			month=m;
			day=d;
			if ( (y<=0) || (m<=0 || m>12) || (d<=0 || d>DayOfMonth(y,m) ) ) 
			{
				cout<<"Invaild date, date has been set to 1900-1-1"<<endl;   //���ڲ��Ϸ�
				year = 1900;
				month = day =1;        //Ĭ������Ϊ1900-1-1 
			}
		} 
		virtual ~Date()  { }       //����������
		
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
		
		bool IsLeapyear()const       //�жϵ�ǰ���ڵ����Ƿ�Ϊ����
		{
			if ((year%4==0 ||year%100==0) && year%400!=0)
			return true;
			else
			return false;
		 } 
		 
		 bool IsLeapyear(const int y)const       //�ж�y�����⣩�Ƿ�Ϊ���� 
		{
			if ((y%4==0 && y%100!=0) || y%400==0)
			return true;
			else
			return false;
		 } 
		 
		 void display()const                  //��ʾ���� 
		 {
		 	cout<<year<<"-"<<month<<"-"<<day;
		 }
		 
		 void operator = (Date date)   //���ظ�ֵ�� 
		 {
		 	year=date.year;
		 	month=date.month;
		 	day=date.day;
		 }
		 
		 bool operator < (Date date)   //���رȽϷ� 
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
		long long BookID;            //ͼ�������룬��һ�޶�
		char SearchBookID[20];       // ����ţ���ͬ����������һ�� 
		char PlaceOfBook [40];       // �鱾�Ĺݲص� 
		char name[40];
		State state;
		long long PIN;               //���ѽ�����������id
		
	public:
		BookData(long long BookID,const char *searchbookid,const char *name,
		       const char *place,State state=SHELF,long long PIN=0)  //Ĭ���ڼ��ϣ��޶��߽��� 
		{
			SetID(BookID);
			SetName(name);
			SetSeachID(searchbookid);
			SetPlaceOfBook(place);
			SetState(state);
			SetPIN(PIN); 
		 } 
		BookData()     //���һ�㲻���ðɡ����� 
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
			switch(state)             //�� ,�鼮״̬�Ĵ�ӡ���⣬ֻ�ܴ�ӡ��ö���͵����֣����ܴ�ӡ������
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


class ReaderData : public object      //���������� -��                   
{
	protected:
		long long PIN;                //���ߵĽ���֤��
		char name[20];                //�������� 
		long long BookList[LIMIT];    //�����б����Ӧ����bookid,��ʼ״̬Ϊ0 
		Date BorrowDate[LIMIT];       //�������ڣ�û�д��ξ�Ĭ�ϵ�ǰʱ��
		Date ReturnDate[LIMIT];       //�������ڣ����ڲ����飬����������Ȩ���� 
		int NumOfBorrowed;            //�ѽ������� 
		
	public:
		ReaderData(long long PIN,const char *name)
		{
			SetID(PIN);
			SetName(name);
			NumOfBorrowed = 0;
			for(int i=0;i<LIMIT;i++)
			BookList[i]=0;     
		 } 
		ReaderData()     //���һ��Ҳ���á������� 
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

        long long BorrowBook(long long BookID)    //��ID 
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
			for (int i=0;i<LIMIT;i++)   //���������ǰ�˳��洢�� 
			{
				if(BookList[i]==0)
				{
					BookList[i]=BookID;
					BorrowDate[i]=daynow;
					ReturnDate[i].SetDate(daynow.GetYear(),daynow.GetMonth()+3,daynow.GetDay());    //��������Ϊ������ 
					NumOfBorrowed++;
					return BookID;      
				}
			}
			cout<<"Book reach the limit!"<<endl;   //ͼ�鳬����ȣ����ܽ����� 
			return 0;
		}   
        		
		void ShowData()  //��ӡ���ߵ����н�������Ϣ 
		{
			cout<<PIN<<"\t"<<name<<endl;   //���߽���֤�ż����� 
			
			for (int i=0;i<LIMIT;i++)
			{
				if(BookList[i])
				{
					cout<<i+1<<": "<<BookList[i]<<"\t";  
					BorrowDate[i].display();
					cout<<"\t";
					ReturnDate[i].display();
					cout<<endl ;      //��š����id���������ڣ��������� 
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


template <class T>           //T��ʾ���Ǽ�¼�����ͣ���˿�����ReaderData��BookData 
class Database: public object
{
	private:
		fstream File;
		char FileName[40];      //�ļ���
		long long FileLen,rec_size;             //�ļ���С����¼����
		typedef map< long long,T,less<long long> > mtype;         //ǰ�ؼ��֣�������ֵ���˴���less��������Ϊ����ʡ�� 
		mtype RecMap;         //���ݼ�¼��,���ݴ洢λ�� 
	public:
		Database(const char * FileName)
		{
			strcpy(this->FileName,FileName);
			File.open(FileName,ios::in|ios::binary);    
			rec_size = sizeof(T);
			if(File.is_open())
			{
				File.seekg(0,ios::end);  //��ָ�뵽�ļ�β 
				if ( (FileLen = File.tellg() )>0 )  //filelenΪ�ļ��ܳ��ȣ�������0ʱִ�� 
				{
         		    T Object;
					File.seekg(0,ios::beg);    //��ָ���Ƶ��ļ�ͷ 
					do{
						File.read((char *) &Object,rec_size);
						//value_type ��pair���͵ģ�����ֵ��Ա�����޸ģ�������Ա�����޸�
						RecMap.insert(typename mtype::value_type(Object.GetID(),Object));   //��Object��ID(PIN)��Ϊ��ֵ
					  } while(File.tellg()<FileLen);
					
				}
			}
			File.close();
		}
		~Database()
		{
			SaveMap();          //��RecMap(STL)�е����ݱ��浽�ļ��� 
		}
		void Insert(T & Object)
		{   
			if(RecMap.count(Object.GetID()))    //��ֹ�ظ���� 
			cout<<"already included!"<<endl;
			else 
			RecMap.insert(typename mtype::value_type(Object.GetID(),Object));   
			//cout<<typeid(T).name()<<"inserted"<<endl;	
		}
		void Delete(long long objID)
		{
			 Query(objID);   //�ҵ���ֵΪObjID�ļ�¼
			 RecMap.erase(objID); 
		}
		T *Query(long long ObjID)        //�������ҵ���ֵΪObjID�ļ�¼ 
		{
			typename mtype::iterator iter;
			iter = RecMap.find(ObjID);
			if(iter==RecMap.end())
			{
				cout<<ObjID<<" not found!"<<endl;
				return NULL;
			 } 
			 else
			 return &(iter->second);       //��������ֵ����ΪBookData����ReaderData���� 
		}
		bool QueryName(const char * objName,long long *pointID)  //����name(part)ΪobjName��ID����PIN 
		{
			typename mtype::iterator iter;
			int i=0;
			for(iter=RecMap.begin();iter!=RecMap.end();++iter)
			{
				if(strstr((iter->second).GetName(),objName)!=NULL)  //strstr�������غ��ַ�����һ�γ�����ǰ�ַ����е�λ�� 
				pointID[i++]=iter->second.GetID();
			//	return &(iter->second);      //ֻҪ�й����Ӵ��ͷ��� 
			}
			if(i==0) 
			{
				 cout<<objName<<" in "<<typeid(T).name()<<" not found!"<<endl;   //typeid�ǲ���������֪һ�������ľ������� 
				return false;
			}
			else
			return true;
		}
		void SaveMap()      //��RecMap(STL)�е����ݱ��浽�ļ��� 
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
		long long ID;    //��ʶ������Աid 
		char name[20];        //����Ա����
		char passwd[9];             //����,�����ǹ̶��ģ�Ӧ�ÿ����Ż� 
		
	public:
		Librarian(long long ID,const char *name):ID(ID)  //����Ա������ID��������ֻ��Ҫ���� 
		{
			strcpy(this->name ,name);
			strcpy(passwd,"123");
		 } 
		 char login()   //��¼�ɹ�����X,ʧ�ܷ���E 
		 {
		 	char pw[9];
		 	for (int i=0;i<3;i++)   //�����λ����������� 
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
//                        mian ������ʵ��                              //
//////////////////////////////////////////////////////////////////////////
int main ()
{
	Database<BookData> BookBase("mybooks.dat");  //���鼮���ݿ�
	Database<ReaderData> ReaderBase("myreader.dat");  //�򿪶������ݿ�
	char choice ='X';
	while(!(choice=='E' || choice=='e')) //  ���˳�ʱ,��ʶ���Сд 
	{
		cout<<"(L)ibrarian entry, (R)eader entry, Re(t)urn book, (E)xit: ";
		cin>>choice;
		Librarian *mqr=NULL;
		ReaderData *rdr=NULL;
		
		switch(choice)
		{
			//--------------------------����Ա���-------------------------------------//
			case 'L':case 'l':
				mqr=new Librarian(101,"yjc");  //�������Ҫ�ɲ�Ҫ�� 
				choice = mqr->login();     //�ɹ�����'X',ʧ�ܷ���'E'
				while (!(choice=='E'||choice=='e'))     //��¼�ɹ�ʱ 
				{
					cout<<"(A)dd Book, ";
					cout<<"(P)ut book to shelf, (S)howAllData, (E)xit: "; //�˴���ShowΪ��ӡ������Ͷ��� 
					cin>>choice;
					switch(choice)
					{
						long long ID;
						char name[40];
						case 'A':case 'a':          //����鼮
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
			//----------------------����Ա�˳�--------------------//
			//----------------------�������----------------------//
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
					if (ReaderBase.Query(PIN)!=NULL)  //�Ѿ��ڶ��߿��д��� 
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
			
			while (!(choice=='E'||choice=='e'))    //��¼�ɹ������˳�
			{
				cout<<"(B)orrow book, (Q)uery book by name, (L)ist my books, (E)xit:";
				cin>>choice;
				switch(choice)
				{
					case 'B':case 'b':      //����,һ���ԡ����� �� 
						int num;      //��ʾ��Ҫ���ͼ����
						cout<<"intput the number of books you wanna borrow:";
						cin>>num; 
						t1=rdr->GetNumOfBorrowed();     //�Ѿ����˵�ͼ���� 
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
								if (rdr->BorrowBook(BookID)>0)   //�������ID��Ӧ�÷ֽ���ɹ�����ʧ��
								{
									BookBase.Query(BookID)->SetState(READER);
									BookBase.Query(BookID)->SetPIN(PIN);
									i++;									
								}
								else;
							}          

						}
						break;
					case 'Q':case 'q':       //������������ѯ�鼮 
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
					case 'L':case 'l':     //��ѯ�鵥 
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
			//-------------------------�����˳�--------------------------//
			//--------------------------�������--------------------------//
			case 'T':case 't':
				cout<<"Input a book ID:";   
				cin>>BookID;
				if(BookBase.Query(BookID)!=NULL)  //������д��� 
				{
					BookBase.Query(BookID)->SetState(LIB);   //��δ�ϼ� 
					if((PIN=BookBase.Query(BookID)->GetPIN())>0)   //�����ˣ��ѽ��
					{ 
						ReaderBase.Query(PIN)->ReturnBook(BookID);
						BookBase.Query(BookID)->SetPIN(0);
					}
				 } 
				break;
			case 'E':case 'e':   //�˳� 
				break;
			default:
				cout<<"Unavailable function !"<<endl;
		}      //switch
	}          //while
						 
	return 0;
}
 
//�������⣬�ϼ����⣬û�н��ȥ������Ի����Ѿ��ڼ��ϵ�������ϼܣ�ֻ�ǲ���û�иı����� 
