#include <iostream>
#include <vector>

bool sum_of_subset(std::vector<int>& arr, std::vector<int>& subset, int i, int maxsum, int tsum, int sum)
{
    
    if(tsum == sum)
        return true;
    

    for(; i < arr.size() - 1; i++)
    {
           
           
        if(tsum + arr[i] <= sum)
        {
            tsum += arr[i];
            maxsum -= arr[i];
            subset[i] = 1;
            
            if(sum_of_subset(arr, subset, i + 1, maxsum, tsum, sum))  
                return true;
            else {
                subset[i] = 0;   
                tsum -= arr[i];
            }
    
        
        } 
        else maxsum -= arr[i];
    
    }
    
    return false;
}

int main()
{
    int size{}, sum{};
    
    std::cin >> size >> sum;
    
    std::vector<int> arr;
    int temp{}, i{}, maxsum{};
    
    for(; i < size; i++)
    {
            std::cin >> temp;
            maxsum += temp;
            arr.push_back(temp);
    }
    
    std::vector<int> subset;
    
    for(i = 0; i < size; i++)
    {
        subset.push_back(0);
    }
    
    int tsum{};
    
    
    if(sum_of_subset(arr, subset, 0, maxsum, tsum, sum) == false)
    {
        std::cout << "solution does not exist ";
        return 0;
    }
    
    
    std::cout << "Position\t element\n";
        
       
    for(i = 0; i < size; i++)
    {   
        if(subset[i] == 1)
        std::cout << i + 1 << "\t\t" << arr[i] <<'\n';
    }
        
    return 0;
}