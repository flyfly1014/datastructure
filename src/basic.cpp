#include "./nthu_bike.h"
#include "vector.h"
#include <fstream>
#include <iostream>
#include <utility>
#include "./global.h"
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>

#define eol std::endl

vector<std::pair<Station,int>> basic_graph[1005];

    //store all the bike
vector<Bike> basic_distribution;

//store users' request
vector<User> basic_users;

int basic_table[1100][1100];
using namespace myself;

inline int max(int a,int b)
{
    return a>b?a:b;
}


inline int parse_string(std::string u)
{
        return stoi(u.substr(1));
}

inline void basic_construct(std::string selectedCase)
{
    std::ifstream input0("./testcases/"+selectedCase+"/bike_info.txt");
    std::ifstream input1("./testcases/"+selectedCase+"/user.txt");
    std::ifstream input2("./testcases/"+selectedCase+"/bike.txt");
    if(!input0.is_open()&&!input1.is_open()&&!input2.is_open())
    {
        std::cout<<"file can not open"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    //------------------------------------
    //Initalizing the bike_info.txt first
    //------------------------------------
    input0>>myself::depreciation;
    input0>>myself::Rental_Limit;
    vector<Bike_Type> category;
    std::string type;
    int price;
    while(input0>>type>>price)
    {   
       category.push_back(Bike_Type(type,price));
    }

    //------------------------------
    //Initalizing the bike.txt first
    //------------------------------
    
    // Bike_Type, Bike_Id, Station_Id, Rental_Price, and Rental_Count
    std::string btype;
    int Bike_Id;
    std::string Station_Id;
    double Rental_Price;
    int Rental_Count;
    while(input2>>btype>>Bike_Id>>Station_Id>>Rental_Price>>Rental_Count)
    {
        int origin=parse_string(Station_Id);
        myself::max_bike_id=max(myself::max_bike_id,Bike_Id);

        Bike x=Bike(btype,Bike_Id,Rental_Price,Rental_Count);
        x.set_source(origin);
        basic_distribution.push_back(x);
    }
    
    //------------------------------
    //Initalizing the user.txt first
    //------------------------------
    std::string request,User_ID,s;
    int Start_Time,End_Time;
    std::string Start_Point,End_Point;
    //int _User_ID,std::string request,int _Start_Time,int _End_Time,int _Start_Point,int _End_Point
    while(input1>>User_ID>>s>>Start_Time>>End_Time>>Start_Point>>End_Point)
    {
        basic_users.push_back(User(parse_string(User_ID),s,Start_Time,End_Time,parse_string(Start_Point),parse_string(End_Point)));
    }

    // for(int i=0;i<users.Size();i++)
    // {
    //     users[i].print_user_info();
    // }
    //---------------------
    //closing all the file 
    //--------------------
    input0.close();
    input1.close();
    input2.close();
}


void basic_build_graph(std::string selectedCase)
{
    std::ifstream myfile("./testcases/"+selectedCase+"/map.txt");
    if(!myfile.is_open())
    {
        std::cout<<"file can not open"<<std::endl;
        exit(EXIT_FAILURE);
    }
    std::string u,v;
    int dist;
    while(myfile>>v>>u>>dist)
    {
        int a=parse_string(v);
        int b=parse_string(u);
        myself::max_vertex_number=max(myself::max_vertex_number,max(a,b));
        basic_graph[a].push_back({Station(u),dist});
    }
    myfile.close(); 
}


inline void swap(User& a,User& b)
{
    User temp;
    temp.User_ID=a.User_ID;
    temp.Start_Time=a.Start_Time;
    temp.End_Time=a.End_Time;
    temp.Start_Point=a.Start_Point;
    temp.End_Point=a.End_Point;
    temp.Accept_Bike_Type=a.Accept_Bike_Type;
    //---------------------------------------
    a.User_ID=b.User_ID;
    a.Start_Time=b.Start_Time;
    a.End_Time=b.End_Time;
    a.Start_Point=b.Start_Point;
    a.End_Point=b.End_Point;
    a.Accept_Bike_Type=b.Accept_Bike_Type;
    //-------------------------------------
    b.User_ID=temp.User_ID;
    b.Start_Time=temp.Start_Time;
    b.End_Time=temp.End_Time;
    b.Start_Point=temp.Start_Point;
    b.End_Point=temp.End_Point;
    b.Accept_Bike_Type=temp.Accept_Bike_Type;
}

inline void swap(record & a,record &b)
{
    record temp;
    temp.set_bike_id(a.get_bike_id());
    temp.set_station_id(a.get_station_id());
    temp.set_rental_count(a.get_rental_count());
    temp.set_rental_price(a.get_rental_price());
    temp.set_bike_type(a.get_bike_type());

    a.set_bike_id(b.get_bike_id());
    a.set_station_id(b.get_station_id());
    a.set_rental_count(b.get_rental_count());
    a.set_rental_price(b.get_rental_price());
    a.set_bike_type(b.get_bike_type());

    b.set_bike_id(temp.get_bike_id());
    b.set_station_id(temp.get_station_id());
    b.set_rental_count(temp.get_rental_count());
    b.set_rental_price(temp.get_rental_price());
    b.set_bike_type(temp.get_bike_type());
}




inline int partition(vector<record>& a, int low, int high) 
{
    int i = (low - 1);   
   
    for (int j = low; j <= high- 1; j++) 
    { 
        //if current element is smaller than pivot, increment the low element
        //swap elements at i and j
        if(a[j].get_station_id()<a[high].get_station_id()) 
        { 
            i++;    // increment index of smaller element 
            swap(a[i], a[j]); 
        }
        else if(a[j].get_station_id()==a[high].get_station_id())
        {
            if(a[j].get_bike_id()<a[high].get_bike_id())
            {
                i++;
                swap(a[i], a[j]); 
            }
        }
    } 
    swap(a[i + 1],a[high]); 
    return (i + 1); 
}

inline int partition(vector<User>& a, int low, int high) 
{
    int i = (low - 1);   
   
    for (int j = low; j <= high- 1; j++) 
    { 
        //if current element is smaller than pivot, increment the low element
        //swap elements at i and j
        if(a[j].get_start_time()<a[high].get_start_time()) 
        { 
            i++;    // increment index of smaller element 
            swap(a[i], a[j]); 
        }
        else if(a[j].Start_Time==a[high].Start_Time)
        {
            if(a[j].User_ID<a[high].User_ID)
            {
                i++;
                swap(a[i], a[j]); 
            }
        }
    } 
    swap(a[i + 1],a[high]); 
    return (i + 1); 
}

   
//quicksort algorithm
template<typename T>
inline void quickSort(vector<T>& a, int low, int high) 
{ 
    if (low < high) 
    { 
        int pivot = partition(a, low, high); 
        quickSort(a, low, pivot - 1); 
        quickSort(a, pivot + 1, high); 
    } 
} 


void basic(std::string selectedCase)
{
    // insert your code here
    std::cout << "start your basic version of data structure final from here!" <<eol;
    //---------------------------
    
    
    //for the station_status.txt
    vector<record> records;

    basic_build_graph(selectedCase);
    basic_construct(selectedCase);

    // for(int i=0;i<=max_vertex_number;i++)
    // {
    //     for(int j=0;j<graph[i].Size();j++)
    //     {
    //         std::cout<<graph[i][j].first<<" "<<graph[i][j]<<eol;
    //     }
    // }

    
    //----------------------------
    //memset(table,0,1005*1005*sizeof(int));
    //check vertex number
    //std::cout<<max_vertex_number<<eol;

    //initalizing the table
    for(int i=0;i<=myself::max_vertex_number;i++)
    {
        for(int j=0;j<basic_graph[i].Size();j++)
        {
            std::string temp=basic_graph[i][j].first.get_ID();
            int k=parse_string(temp);
            basic_table[i][k]=basic_graph[i][j].second;
            basic_table[k][i]=basic_graph[i][j].second;
        }
    }

    //---------------
    //print the table
    //---------------
    // for(int i=0;i<=myself::max_vertex_number;i++)
    // {
    //     for(int j=0;j<=myself::max_vertex_number;j++)
    //     {
    //         std::cout<<table[i][j]<<" ";
    //     }
    //     std::cout<<eol;
    // }
    
    //find all source shortest path
    for(int k=0;k<=myself::max_vertex_number;k++)
        for(int i=0;i<=myself::max_vertex_number;i++)
            for(int j=0;j<=myself::max_vertex_number;j++)
                if(basic_table[i][k]+basic_table[k][j]<basic_table[i][j])
                    basic_table[i][j]=basic_table[i][k]+basic_table[k][j];

    // ---------------
    // print the table
    // ---------------
    // for(int i=0;i<=myself::max_vertex_number;i++)
    // {
    //     for(int j=0;j<=myself::max_vertex_number;j++)
    //     {
    //         std::cout<<table[i][j]<<" ";
    //     }
    //     std::cout<<eol;
    // }
    
    //----------------------------------------
    //opening all the file that need to output
    //----------------------------------------
    std::ofstream output0;
    std::ofstream output1;
    std::ofstream output2;
    output0.open("./result/"+selectedCase+"/user_result.txt");
    output1.open("./result/"+selectedCase+"/station_status.txt");
    output2.open("./result/"+selectedCase+"/transfer_log.txt");
    if(!output0.is_open()&&!output1.is_open()&&!output2.is_open())
    {
        std::cout<<"file can not open"<<std::endl;
        exit(EXIT_FAILURE);
    }

    //accept or reject the request
    int AcceptOrNot;

    /*
        flag=0 find user wanted bicycle type
    */
    int flag;

    //紀錄目前能找到的最大的rental price
    double target=-1;
    //紀錄腳踏車的id
    int wanted_id=-1;
    //output bike id
    int out_bid;
    //std::cout<<max_bike_id<<eol;
    // for(int i=0;i<basic_users.Size();i++)
    //     std::cout<<basic_users[i].get_id()<<eol;
    // std::cout<<basic_users.Size()<<eol;
    quickSort(basic_users,0,basic_users.Size()-1);
    

    for(int i=0;i<basic_users.Size();i++)
    {
        //update bike information also let the bike retire
        // std::cout<<users[i].get_id()<<" "<<users[i].get_start_point()<<" "<<users[i].get_end_point()<<" "
        // <<users[i].get_start_time()<<" "<<users[i].get_end_time()<<eol;
        //iterate all the bike
        for(int j=0;j<basic_distribution.Size();j++)
        {
            //find rental price
            if(i==0) break;
            if(basic_users[i].get_start_time()>=basic_distribution[j].get_arrival_time()&& basic_distribution[j].check() && basic_distribution[j].Used())
            {
                basic_distribution[j].set_used();
            }
        }
        flag=0;
        int source=basic_users[i].get_start_point();
        int destination=basic_users[i].get_end_point();
        int start_time=basic_users[i].get_start_time();
        int end_time=basic_users[i].get_end_time();
        int ans=start_time+basic_table[source][destination];
        vector<std::string> request=basic_users[i].get_bike_type();

        //accerlating 
        if(ans>end_time)
        {
            flag=1;
            AcceptOrNot=0;
        }
        
        vector<int> idx;
        for(int j=0;j<request.Size();j++) //user's bike type
        {
            if(flag==1) break;
            auto head=request[j];
            for(int k=0;k<basic_distribution.Size();k++) //iterate all the bike
            {
                if(basic_distribution[k].get_bike_type()==head && 
                basic_distribution[k].check() && !basic_distribution[k].Used()
                && ans<end_time&& basic_users[i].get_start_point()==basic_distribution[k].get_source())
                {
                    // if(users[i].get_id()==39)
                    // {
                    //     std::cout<<distribution[k].get_bike_id()<<eol;
                    // }
                    idx.push_back(basic_distribution[k].get_bike_id());
                }
            }
            target=-1;
            wanted_id=INT_MAX;
            
            for(int k=0;k<idx.Size();k++)
            {
                if(basic_distribution[idx[k]].get_rental_price()>target)
                {
                    target=basic_distribution[idx[k]].get_rental_price();
                    wanted_id=idx[k];
                }
                else if(basic_distribution[idx[k]].get_rental_price()==target)
                {
                    if(basic_distribution[idx[k]].get_bike_id()<wanted_id)
                    {
                        wanted_id=idx[k];
                    }
                }
            }
            // std::cout<<"target"<<eol;
            // std::cout<<target<<eol;
            // std::cout<<"id"<<eol;
        }
        // std::cout<<wanted_id<<eol;
        if(target!=-1 && wanted_id!=INT_MAX && flag==0)
        {
            //pick this bike s
            basic_distribution[wanted_id].set_used();
            revenue=floor(basic_distribution[wanted_id].get_rental_price()*basic_table[source][destination]);
            basic_distribution[wanted_id].set_arrival_time(ans);
            out_bid=basic_distribution[wanted_id].get_bike_id();
            //更新站點
            basic_distribution[wanted_id].set_source(destination);
            end_time=ans;
            basic_distribution[wanted_id].update();
            AcceptOrNot=1;
        }
        else AcceptOrNot=0;
        
        
        if(AcceptOrNot==0)
        {
            //output to user_result.txt
            output0<<'U'<<basic_users[i].get_id()<<" "<<"0"<<" "<<"0"<<" "<<"0"<<" "<<"0"<<" "<<"0"<<"\n";
        }
        else 
        {
            //output to user_result.txt
            output0<<'U'<<basic_users[i].get_id()<<" "<<AcceptOrNot<<" "<<out_bid<<" "<<start_time<<" "<<end_time<<" "<<revenue<<"\n";
            //output to transfer_log.txt
            output2<<out_bid<<" "<<"S"<<source<<" "<<"S"<<destination<<" "<<start_time<<" "<<ans<<" "<<'U'<<basic_users[i].get_id()<<"\n";
        }
    }
    int station_id;
    int bike_id;
    std::string bike_type;
    double rental_price;
    int rental_count;

    for(int i=0;i<basic_distribution.Size();i++)
    {
        station_id=basic_distribution[i].get_source();
        bike_id=basic_distribution[i].get_bike_id();
        bike_type=basic_distribution[i].get_bike_type();
        rental_price=basic_distribution[i].get_rental_price();
        rental_count=basic_distribution[i].get_rental_count();
        records.push_back(record(station_id,bike_id,bike_type,rental_price,rental_count));
    }
    
    quickSort(records,0,records.Size()-1);
    //output to station_status.txt
    for(int i=0;i<records.Size();i++)
    {
        //
        output1<<'S'<<records[i].get_station_id()<<" "<<records[i].get_bike_id()<<" "<<records[i].get_bike_type()<<" "<<
        records[i].get_rental_price()<<std::setiosflags (std::ios::fixed) <<std::setprecision (1)<<" "<<records[i].get_rental_count()<<"\n";
    }
    //---------------------
    //closing all the file
    //---------------------
    output0.close();
    output1.close();
    output2.close();
}

