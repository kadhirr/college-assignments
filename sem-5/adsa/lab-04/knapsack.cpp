#include <iostream>
#include <vector>

struct pair
{
  float profit{};
  float weight{};
  
};

void costCalc(std::vector<struct pair> arr,std::vector<int> set, float& upperbound, float& cost, int maxweight, int j)
{
        
    int temp{}, size = arr.size();
    float pw{};
    
    for(int i = 0; i < size; i++)
    {   
        
        if(j == i or set[i] == 0)
        continue;
        
        if(temp + arr[i].weight <= maxweight)
        {
            temp       += arr[i].weight;
            upperbound += arr[i].profit;
            cost       += arr[i].profit; 
            
        }
        else if(maxweight - temp > 0) {
                
                pw = (arr[i].profit / arr[i].weight) * (maxweight - temp);
                cost += pw;
                break;
        }
        
            
    }
    
    upperbound *= -1;
    cost *= -1;
    
    //std::cout << upperbound << '\t' << cost << '\n';
    
   
    
}


void BBKS(std::vector<struct pair> arr, std::vector<int>& set, float& upperbound, float& cost, int maxweight, int i)
{
    if(i >= arr.size())
        return ;
    float c1{}, c2{}, ub1{}, ub2{};
    
    c1 = cost;
    ub1 = upperbound;
    
    costCalc(arr, set, ub2, c2, maxweight, i);
    
    
    int count{};
    
    for(int j = 0; j <= i ; j++)
    {
        if(set[j] == 1)
        {
            count += arr[j].weight;
        }
    }
    
    
    
    if(c1 < c2 && count <= maxweight)
    {   
        set[i] = 1;
        BBKS(arr, set, ub1, c1, maxweight, i + 1);
    }
    else 
    {
        set[i] = 0;
        BBKS(arr, set, ub2, c2, maxweight, i + 1);
    }
    
    
    
}

int main()
{
    int size{}, maxweight{};
    
    std::cin >> size >> maxweight;
    
    std::vector<struct pair> arr; 
    std::vector<int> set;
    
    int i{};
    
    struct pair t;
    
    for(;i < size; i++)
    {
        std::cin >> t.profit >> t.weight;
        arr.push_back(t);
        set.push_back(1);
        
    }
    
    //sort
    for(i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(arr[i].weight > arr[j].weight)
            {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
    
    float upperbound{}, cost{};
    
    costCalc(arr, set, upperbound, cost, maxweight, -1);
    
    BBKS(arr, set, upperbound, cost, maxweight, 0);


    int maxprofit{};
    
    

    for(i = 0; i < size; i++)
    {
        
        if(set[i] == 1) {
            
            std::cout << arr[i].weight << ' ';
            maxprofit += arr[i].profit;
        }    
    }
    std::cout << '\n';
    for(i = 0; i < size; i++)
        std::cout << set[i] <<' ';
    
    std::cout << '\n' << "maxprofit  " << maxprofit;
    
    return 0;
}


















