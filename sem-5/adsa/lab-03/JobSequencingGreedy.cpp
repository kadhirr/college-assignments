
#include <iostream>

class job
{
    public:
            int profit;
            int deadline;
            
};

int jobsequence(job detail[], int n, int slot[])
{
    int i{}, j{}, maxtime{};
    
    for(;i < n; i++)
    {
        if(maxtime < detail[i].deadline)
        {
             maxtime = detail[i].deadline;
        }
    }
 
    for(i = 0; i < maxtime; i++)
        slot[i] = 0;
    
    job temp;
    
    for(i = 0;i < n;i++)
    {   for(j = i + 1; j < n; j++){
        
            if(detail[i].profit < detail[j].profit)    {
                temp = detail[i];
                detail[i] = detail[j];
                detail[j] = temp;
            }
        }    
    }
    
    
    for(i = 0;i < maxtime; i++)
    {
        for(j = detail[i].deadline-1;j >= 0; j--){
            if(slot[j] == 0){
                slot[j] = i+1;
                std::cout << slot[2];
                j = -1;}
        }
    }
    return maxtime;
}

int main()
{
    int n{}, i{};
    job detail[20];
    
    std::cin >> n;
    
    for(;i < n; i++)
    {
        std::cin >> detail[i].profit >> detail[i].deadline;
    }
    
    int slot[20], size{};
    
    size = jobsequence(detail, n, slot);
    
    std::cout << "Job Sequence\n";
    std::cout << "Slot\t" << "Job\tProfit \n";
        
    int maxprofit {};
    
   for(i = 0; i < size; i++)
    {
        std::cout << '\n' << i+1 << '\t'<< slot[i] << "\t" << detail[slot[i] - 1].profit;
        maxprofit += detail[slot[i] - 1].profit;
    }
    
    std::cout << "\n maxprofit is " << maxprofit;
    return 0;
}