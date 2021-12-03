#include <iostream>
#include <vector>


void ip(std::vector<std::vector<int>>& graph, int size)
{
    int i{}, j{}, temp{};
    std::vector<int> row;
    
    for(i = 0;i < size; i++)
    {
        
        for(j = 0; j < size; j++)
        {
            std::cin >> temp;
            if(temp == -1)
                temp = INT16_MAX;
            row.push_back(temp);
           
        }    
        graph.push_back(row);
        row.clear();
       
        
    }
    
}

void op(std::vector<std::vector<int>>& graph, int size)
{
     
    int i{}, j{};
    
    for(; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            std::cout << graph[i][j] << '\t';
            
        }    
        std::cout << std::endl;
    }
    
}

int cost(std::vector<std::vector<int>>& graph, int size)
{
    int min{}, i{}, j{};
    std::vector<int> minr;
    std::vector<int> minc;
    
    int t = INT16_MAX;
    
    for(i = 0; i < size; i++)
    {
        min = graph[i][0];
        for(j = 1; j < size; j++)
        {
            min = std::min(min,graph[i][j]);
        }
        minr.push_back(min);
    }
    
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(minr[i] == t or graph[i][j] == t)
                continue;
            graph[i][j] -= minr[i];
        }
        
    }
    
    for(i = 0; i < size; i++)
    {
        min = graph[0][i];
        for(j = 1; j < size ; j++)
        {
            min = std::min(min,graph[j][i]);
            
        }
        minc.push_back(min);
    }
    
    
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {   
            if(minc[i] == t or graph[i][j] == t)
                continue;
           graph[j][i] -= minc[i];
        }
    }
    
    min = 0;
    
    for(i = 0; i < size; i++)
    {   
        if(minr[i] != t)
        {
            min +=  minr[i];    
        }
        
        
        if(minc[i] != t)
        {
            min +=  minc[i];
        }
        
        
    }
    
    return min;
}

void change(std::vector<std::vector<int>>& graph, int size, int j, int i, std::vector<int>& ans)
{
    int k{};
    for(; k < size; k++)
    {
        graph[i][k] = INT16_MAX;
    }
    
    for(k = 0; k < size; k++)
    {
        graph[k][j] = INT16_MAX;
    }
    
    graph[i][j] = INT16_MAX;
    graph[j][i] = INT16_MAX;
    
    for( k = i - 1; i >= 0; i--)
    {
        graph[ans[i]][j] = INT16_MAX;
        graph[j][ans[i]] = INT16_MAX;
    }
    
}


int BBts(std::vector<std::vector<int>>& graph, std::vector<int>& set,std::vector<int>& ans, int size, int i, int prec)
{   
    
    if(i == size)
    {  
        return prec;
    }   
    
    int c{};
    std::vector<std::vector<int>> temp;
    
   
    int min = INT16_MAX, position = 0;
    for(int j = 0; j < size; j++)
    {
        if(set[j] >= 0 )
           continue;
            
        temp = graph;
        change(temp, size, j, ans[i - 1], ans);
        c = cost(temp, size) + graph[ans[i - 1]][j] + prec ;
            
        if(c < min)
        {
            position = j;
            min = c;
        }
            
        temp.clear();
            
    }
        
    position;
    set[position] = i;
    ans[i] = position;
        
    temp = graph;
    
    change(temp, size, position, ans[i - 1], ans);
        
    c = cost(temp, size) + prec + graph[ans[i - 1]][position];
    graph = temp;
    prec = c;
    prec = BBts(graph, set, ans, size, i + 1, c);
    
    return prec;
}

int main()
{
    int size{} , c{};
    
    std::cin >> size;
    
    std::vector<std::vector<int>> graph ;
    
    ip(graph, size);
    
    c = cost(graph, size);
    
    std::vector<int> set;
    std::vector<int> ans;
   
    set.push_back(0);
    set.resize(size, -1);
    
    ans.push_back(0);
    ans.resize(size);
    
    c = BBts(graph, set, ans, size, 1, c);
    
    for(int k = 0; k < size; k++)
        std::cout << ans[k] + 1 << "-";
    
    std::cout << 1 << std::endl << " travel cost is :" << c;
    
    return 0;
}