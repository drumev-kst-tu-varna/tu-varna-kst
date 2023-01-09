/* Данеел Дамянов Друмев,
    спец. КСТ, II курс, 
    1б гр., ф.№ 21621412,
    ТУ-Варна */

// Курсова работа ООП1
// Задание 5.

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>

using namespace std;

/* 5-I. */
class CLaptop{
    private:
    string m_strProducer;
    int m_iScreenSize;
    int m_iCapacity;
    string m_strStorageType;
    public:
    enum StorageType{SSD,HDD}m_eStorageType;
    /* I.1. Constructors */
    // default constructor
    CLaptop():m_strProducer(""),m_iScreenSize(0),m_eStorageType(SSD),m_iCapacity(0){}
    // explicit constructor - for manufacturer and size 
    CLaptop(string prod,int size):m_strProducer(prod),m_iScreenSize(size){}
    // explicit constructor - for size
    CLaptop(int size):m_iScreenSize(size){}
    // copy constructor
    CLaptop(const CLaptop&p):m_strProducer(p.m_strProducer),m_iScreenSize(p.m_iScreenSize),
        m_eStorageType(p.m_eStorageType),m_iCapacity(p.m_iCapacity){}
    
    /* I.2. Member variable accessors for reading */
    int GetScreenSize()const{return m_iScreenSize;}
    string GetProducer()const{return m_strProducer;}
    int GetCapacity()const{return m_iCapacity;}
    StorageType GetDriveType()const{return m_eStorageType;}

    /* I.3. Output stream */
    void Output(ostream& out)const{
        out<<"Manufacturer: "<<m_strProducer<<endl;
        out<<"Screen size: "<<m_iScreenSize<<endl;
        out<<"Storage type: "
            <<(m_eStorageType==SSD?"SSD":"HDD")<<endl;
        out<<"Capacity: "<<m_iCapacity<<endl;
    }

    /* I.4. Input stream */
    void Input(istream& in){
        cout<<"Manufacturer: ";
        getline(in,m_strProducer);
        cout<<"Screen size: ";
        in>>m_iScreenSize;
        cout<<"Storage type: ";
        
        getline(in,m_strStorageType);
        if(m_strStorageType=="SSD")m_eStorageType=SSD;
        else if(m_strStorageType=="HDD")m_eStorageType=HDD;
        cout<<"Capacity: ";
        in>>m_iCapacity;
    }

    /* I.5. Operator= (assignment) */
    CLaptop& operator=(const CLaptop& obj){
        if(this!=&obj){
            m_strProducer=obj.m_strProducer;
            m_iScreenSize=obj.m_iScreenSize;
            m_eStorageType=obj.m_eStorageType;
            m_iCapacity=obj.m_iCapacity;
        }
        return *this;
    }

    /* I.6. Operator< (less than) - for screen size */
    bool operator<(const CLaptop& obj)const{
        return m_iScreenSize<obj.m_iScreenSize;
    }

    /* I.7. Operator== (equal to) - for screen size */
    bool operator==(const CLaptop& obj)const{
        return m_iScreenSize==obj.m_iScreenSize;
    }

    /* I.8. Operator<< (output) - for manufacturer and screen size */
    friend ostream& operator<<(ostream& out,const CLaptop& obj){
        if(&out==&cout){
            out<<"Manufacturer: "<<obj.m_strProducer
                <<"Screen size: "<<obj.m_iScreenSize;
        }
        else{
            out<<obj.m_strProducer<<" "<<obj.m_iScreenSize<<endl;
        }
        return out;
    }

    /* I.9. Operator>> (input) - for manufacturer and screen size */
    friend istream& operator>>(istream& in,CLaptop& obj){
        if(&in==&cin){
            cout<<"Manufacturer: "<<"Screen size: ";
            cout<<"Storage type: "<<"Capacity: ";
        }
        in>>obj.m_strProducer>>obj.m_iScreenSize;
        in>>obj.m_strStorageType>>obj.m_iCapacity;
        return in;
    }

};

/* 5.II. */
class CLaptopShop{
    private:
    vector<CLaptop>m_vSales;
    public:
    /* II.1. Constructors */
    // explicit constructor - by file name
    CLaptopShop(const string& fName){
        // open file and read data
        ifstream iStream(fName,ios::in);
        if(iStream.is_open()){
            readIn(iStream);
            iStream.close();
        }
        else throw runtime_error("\nFile not found or empty.\n");
    }
    // explicit constructor
    CLaptopShop(vector<CLaptop>& sales):m_vSales(sales){}
    // default constructor
    CLaptopShop(){}

    /* II.2. Input stream */
    void readIn(istream& iStream){
        CLaptop laptop;
        while(iStream>>laptop)
            m_vSales.push_back(laptop);
    }

    /* II.3. Output stream */
    void WriteTo(ostream& oStream){
        for(const auto& laptop:m_vSales)
            oStream<<laptop<<endl;
    }

    /* II.4. Count sales by manufacturer */
    map<string,int>countSalesByProducer(){
        map<string,int>m_mSalesByProducer;
        for(const auto& laptop:m_vSales)
            ++m_mSalesByProducer[laptop.GetProducer()];
        return m_mSalesByProducer;
    }

    /* II.5. Maximum sales by manufacturer - return name and № of sales */
    void maxSalesByProducer(string& strProducer,int& iNum){
        map<string,int>m_mSalesByProducer=countSalesByProducer();
        int iMaxNumSales=0;
        for(const auto& pair:m_mSalesByProducer){
            const auto& prod=pair.first;
            const auto& num=pair.second;
            if(num>iMaxNumSales){
                iMaxNumSales=num;
                strProducer=prod;
            }
        }
        iNum=iMaxNumSales;
    }
    /* II.6. Maximum sales by size - return name and № of sales */
    void maxSalesBySize(int& iScreenSize,int& iNum){
        map<int,int>m_mSalesBySize;
        for(const auto& laptop:m_vSales)
            ++m_mSalesBySize[laptop.GetScreenSize()];
        int iMaxNumSales=0;
        for(const auto& pair:m_mSalesBySize){
            const auto& size=pair.first;
            const auto& num=pair.second;
            if(num>iMaxNumSales){
                iMaxNumSales=num;
                iScreenSize=size;
            }
        }
        iNum=iMaxNumSales;
    }

    /* II.7. Maximum sales by disk capacity - return name and № of sales */
    void maxSalesByCapacity(CLaptop::StorageType type,int& iCapacity,int& iNum){
        map<int,int>m_mSalesByCapacity;
        int iMaxNumSales=0;
        for(const auto& laptop:m_vSales){
            if(laptop.GetDriveType()==type){
                ++m_mSalesByCapacity[laptop.GetCapacity()];
            }
        }
        for(const auto& pair:m_mSalesByCapacity){
            const auto& capacity=pair.first;
            const auto& num=pair.second;
            if(num>iMaxNumSales){
                iMaxNumSales=num;
                iCapacity=capacity;
            }
        }
        iNum=iMaxNumSales;
    }
};

/* III.1. Main function */
int main(){
    CLaptopShop shop("laptop.txt");

    // Count sales by manufacturer
    map<string,int>salesByProducer=shop.countSalesByProducer();
    for(const auto& pair:salesByProducer){
        const auto& prod=pair.first;
        const auto& num=pair.second;
        cout<<prod<<" "<<num<<endl;
    }
    
    // Find the manufacturer with the maximum number of sales
    string maxProducer;
    int maxNumSales=0;
    shop.maxSalesByProducer(maxProducer,maxNumSales);
    cout<<"MAX SALES BY PRODUCER: "<<maxProducer<<" "<<maxNumSales<<endl;

    // Find the screen size with the maximum number of sales
    int maxSize=0;
    shop.maxSalesBySize(maxSize,maxNumSales);
    cout<<"MAX SALES BY SIZE: "<<maxSize<<" "<<maxNumSales<<endl;

    // Find the storage capacity with the maximum number of sales
    int maxCapacity=0;
    shop.maxSalesByCapacity(CLaptop::SSD,maxCapacity,maxNumSales);
    cout<<"MAX SALES BY CAPACITY SSD: "<<maxCapacity<<" "<<maxNumSales<<endl;
    return 0;
}
