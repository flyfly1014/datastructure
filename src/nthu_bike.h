#ifndef nthu
#define nthu
#include <iostream>
#include "./vector.h"
#include "./global.h"
#include <sstream>

void basic(std::string selectedCase);
void advanced(std::string selectedCase);
using namespace myself;



//-------------------------------------------------
//Below is the bike type class
//-------------------------------------------------
class Bike_Type
{
    std::string type;
    //useless?
    int initial_price;
    public:
    //dollars per minute
    Bike_Type();
    Bike_Type(std::string Type,int price);
    //void get_type();
    //friend class Bike;
};


//================================================
//Below is the Bike class
//================================================
class Bike
{
    private:
    double Rental_Price;
    int Rental_Count;
    std::string btype;
    int Bike_ID;
    bool used;
    int source;
    int start_time;
    int arrival_time;
    int destination;
    int interval;
    public:
    Bike();
    Bike(std::string _btype,int _Bike_ID,double _Rental_Price,int _Rental_Count);
    //update the result after every request
    bool check();
    void update();
    //get/set method
    double get_rental_price(); 
    int get_rental_count();
    int get_bike_id();
    std::string get_bike_type();
    void set_used();
    bool Used();

    void set_source(int a);
    int get_source();

    void set_arrival_time(int a);
    int get_arrival_time();

    void set_start_time(int a);
    int get_start_time();

    void set_interval(int a);
    int get_interval();
};



//================================================
//Below is the User class
//================================================

class User
{
    public:
    vector<std::string> Accept_Bike_Type;
    int User_ID;
    int Start_Time;
    int End_Time;
    int Start_Point;
    int End_Point;
    User(){};
    User(int _User_ID,std::string request,int _Start_Time,int _End_Time,int _Start_Point,int _End_Point);
    //---------------------------------------
    void build_type(std::string s);
    int get_start_time();
    int get_end_time();
    int  get_start_point();
    int get_end_point();
    int get_id();
    void print_user_info();
    vector<std::string>& get_bike_type();
};



//================================================
//Below is the Station class
//================================================

class Station
{
    private:
    // station_id, bike_id, bike_type, rental_price, and rental_count
    std::string id;
    //vector<Station> neighbor;
    public:
    Station();
    Station(std::string _id);
    //inline void push(std::string s);
    inline std::string get_ID();
};




// inline void Station::push(std::string s)
// {
//     neighbor.push_back(s);
// }


//================================================
//Below is the record class
//================================================
class record
{
    private:
    // station_id, bike_id, bike_type, rental_price, and
    // rental_count
    int station_id;
    int bike_id;
    std::string bike_type;
    double rental_price;
    int rental_count;

    public:
    record();
    record(int _station_id,int _bike_id,std::string _bike_type,
    double _rental_price,int _rental_count);
    //get/set method
    int get_station_id();
    int get_bike_id();
    std::string get_bike_type();
    double get_rental_price();
    int get_rental_count();
    //----------------------
    void set_station_id(int x);
    void set_bike_id(int x);
    void set_bike_type(std::string x);
    void set_rental_price(double x);
    void set_rental_count(int x);
};


inline Bike_Type::Bike_Type(){}
inline Bike_Type::Bike_Type(std::string Type,int price):type(Type),initial_price(price){}
inline Bike::Bike()
{
    interval=0;
    used=false;
}
inline Bike::Bike(std::string _btype,int _Bike_ID,double _Rental_Price,int _Rental_Count):btype(_btype),
 Bike_ID(_Bike_ID),Rental_Price(_Rental_Price),Rental_Count(_Rental_Count)
{
    interval=0;
    used=false;
}
inline User::User(int _User_ID,std::string request,int _Start_Time,int _End_Time,int _Start_Point,int _End_Point)
{
    User_ID=_User_ID;
    build_type(request);
    Start_Time=_Start_Time;
    Start_Point=_Start_Point;
    End_Time=_End_Time;
    End_Point=_End_Point;

}

inline void Bike::set_start_time(int a)
{
    start_time=a;
}

inline int Bike::get_start_time()
{
    return start_time;
}

inline void Bike::set_interval(int a)
{
    this->interval=a;
}

inline int Bike::get_interval()
{
    return interval;
}
inline Station::Station(){}
inline Station::Station(std::string _id):id(_id){}
inline record::record(){};
inline record::record(int _station_id,int _bike_id,std::string _bike_type,
    double _rental_price,int _rental_count):station_id(_station_id),bike_id(_bike_id),bike_type(_bike_type),
    rental_price(_rental_price),rental_count(_rental_count){}

inline std::string Bike::get_bike_type()
{
    return btype;
}

inline void Bike::set_source(int a)
{
    this->source=a;
}

inline int Bike::get_source()
{
    return source;
}

inline void Bike::set_arrival_time(int a)
{
    arrival_time=a;
}

inline int Bike::get_arrival_time()
{
    return arrival_time;
}

inline void Bike::set_used()
{
    used=!used;
}

inline bool Bike::Used()
{
    return used==true;
}

inline int Bike::get_rental_count()
{
    return Rental_Count;
}

inline double Bike::get_rental_price()
{
    return Rental_Price;
}

inline int Bike::get_bike_id()
{
    return Bike_ID;
}

//for finding suitable bike
inline bool Bike::check()
{
    if(Rental_Count>=myself::Rental_Limit)
    {
        return false;
    }
    return true;
}

inline void Bike::update()
{
    this->Rental_Count+=1;
    this->Rental_Price-=myself::depreciation;
}

//for debuging 
inline void User::print_user_info()
{
    for(int i=0;i<Accept_Bike_Type.Size();i++)
    {
        std::cout<<Accept_Bike_Type[i]<<" ";
    }
    std::cout<<std::endl;
}
inline int User::get_id()
{
    return User_ID;
}

inline vector<std::string>& User::get_bike_type()
{
    return Accept_Bike_Type;
    
}

inline int User::get_start_time()
{
    return Start_Time;
}

inline int User::get_end_time()
{
    return End_Time;
}
inline int User::get_start_point()
{
    return Start_Point;
}
inline int User::get_end_point()
{
    return End_Point;
}
inline void User::build_type(std::string s)
{
    std::stringstream ss(s);
    std::string temp;
    while(getline(ss,temp,','))
    {
        this->Accept_Bike_Type.push_back(temp);
    }
}


inline std::string record::get_bike_type()
{
    return bike_type;
}
inline double record::get_rental_price()
{
    return rental_price;
}

inline int record::get_rental_count()
{
    return rental_count;
}

inline void record::set_bike_id(int x)
{
    this->bike_id=x;
}

inline void record::set_station_id(int x)
{
    this->station_id=x;
}

inline int record::get_bike_id()
{
    return bike_id;
}

inline int record::get_station_id()
{
    return station_id;
}

inline void record::set_bike_type(std::string x)
{
    this->bike_type=x;
}

inline void record::set_rental_price(double x)
{
    this->rental_price=x;
}

inline void record::set_rental_count(int x)
{
    this->rental_count=x;
}

inline std::string Station::get_ID()
{
    return id;
}


#endif