
#include<iostream> 

class item
{
    public:
            float profit;
            int weight;
            float pw;
            
};

 int greedymax(item object[], int n, int maxwt, item sobject[]) 
 {
     int i{}, j{}, m{};
     item temp;
     
     for(; i < n; i++) {
         object[i].pw = object[i].profit / object[i].weight;
     }
     for(i = 0;i < n-1; i++) {
         for(j = i + 1;j < n; j++) {
             if(object[j].pw > object[i].pw) {
                 temp = object[i];
                 object[i] = object[j];
                 object[j] = temp;
             }
         }
     }
     
     for(i = 0; i < n; i++)
     {
         if (maxwt == 0) {
            return i; 
         }
         
         if(object[i].weight <= maxwt) {
            sobject[i] = object[i];
            maxwt -= object[i].weight;
         }
         else {
             temp = object[i];
             temp.weight = maxwt;   
             temp.profit = object[i].profit * maxwt/object[i].weight;
             maxwt -= object[i].weight;
             sobject[i] = temp;
             maxwt -= temp.weight;
         }
     }
     
     
 }

int main() 
{
    item object[20];
    int n{}, maxwt{}, i{};
    
    std::cin >> n >> maxwt;
    
    for(;i < n;i++) {
        std::cin >> object[i].profit >> object[i].weight ;
        object[i].pw = 0;
    }
    
    int m{};
    item sobject[20];
    
    float maxprofit {};
    
    m = greedymax(object, n, maxwt, sobject);
    
    std::cout << "selected objects \n";
    std::cout << "weights \t profits \n";
    for(i = 0;i < m - 1; i++) 
    {
        std::cout << sobject[i].weight << "\t\t" << sobject[i].profit << '\n';
        maxprofit += sobject[i].profit;
    }
    
    std::cout << "max profit is " << maxprofit;
    
    return 0;
}