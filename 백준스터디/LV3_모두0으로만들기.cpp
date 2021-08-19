#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

long long Copy_And_Calculate_Sum(vector<int>& A, vector<long long>& Weight)
{
    long long Sum = 0;
    for (int i = 0; i < A.size(); i++)
    {
        Sum += A[i];
        Weight[i] = (long long)(A[i]);
    }
    return Sum;
}

void Make_Tree(vector<vector<int>> Edges, vector<int>& LeafNode, vector<int>& EdgeCnt, vector<vector<int>>& Tree, int NodeCnt)
{
    for (int i = 0; i < Edges.size(); i++)
    {
        int N1 = Edges[i][0];
        int N2 = Edges[i][1];
        Tree[N1].push_back(N2);
        Tree[N2].push_back(N1);
        EdgeCnt[N1]++;
        EdgeCnt[N2]++;
    }
    for (int i = 0; i < NodeCnt; i++)
    {
        if (EdgeCnt[i] == 1) LeafNode.push_back(i);
    }
}

void Func(long long& answer, vector<long long> Weight, vector<int> Leaf, vector<int> Edge_Cnt, vector<vector<int>> Tree, int Node_Cnt)
{
    vector<bool> Visit(Node_Cnt, false);
    queue<int> Q;
    for (int i = 0; i < Leaf.size(); i++) Q.push(Leaf[i]);

    while (Q.empty() == false)
    {
        int Cur = Q.front();
        long long Cur_Weight = Weight[Cur];
        Visit[Cur] = true;
        Q.pop();

        for (int i = 0; i < Tree[Cur].size(); i++)
        {
            int Next = Tree[Cur][i];
            if (Visit[Next] == true) continue;

            Weight[Cur] -= Cur_Weight;
            Weight[Next] += Cur_Weight;
            answer += abs(Cur_Weight);
            Edge_Cnt[Next]--;
            if (Edge_Cnt[Next] == 1) Q.push(Next);
        }
    }
}

long long solution(vector<int> a, vector<vector<int>> edges)
{
    long long answer = 0;

    vector<long long> Weight(a.size(), 0);
    long long Result = Copy_And_Calculate_Sum(a, Weight);
    if (Result != 0) return -1;

    vector<int> LeafNode;
    vector<int> Edge_Cnt(a.size(), 0);
    vector<vector<int>> Tree(a.size(), vector<int>());
    Make_Tree(edges, LeafNode, Edge_Cnt, Tree, a.size());
    Func(answer, Weight, LeafNode, Edge_Cnt, Tree, a.size());
    return answer;
}