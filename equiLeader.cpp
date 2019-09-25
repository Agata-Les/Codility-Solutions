/* A non-empty array A consisting of N integers is given. The leader of this array is the value 
that occurs in more than half of the elements of A. An equi leader is an index S such that 0 ≤ S < N − 1
and two sequences A[0], A[1], ..., A[S] and A[S + 1], A[S + 2], ..., A[N − 1] have leaders of the same value.

For example, given array A such that:
    A[0] = 4
    A[1] = 3
    A[2] = 4
    A[3] = 4
    A[4] = 4
    A[5] = 2
we can find two equi leaders:
0, because sequences: (4) and (3, 4, 4, 4, 2) have the same leader, whose value is 4.
2, because sequences: (4, 3, 4) and (4, 4, 2) have the same leader, whose value is 4.
The goal is to count the number of equi leaders.

Write a function that, given a non-empty array A consisting of N integers, returns the number of equi leaders.
For example, given the array above the function should return 2, as explained above.

Write an efficient algorithm for the following assumptions:
N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000,000..1,000,000,000]. */

#include <stack>

int FindDominator(vector<int> &A);

int FindEquiLeader(vector<int> &A)
{
   int LeaderPosition = FindALeader(A);
   if(LeaderPosition == -1) return 0;
   
   int Leader = A[LeaderPosition];
   int HowManyLeadersCounter = 0;
   int result = 0;
   
    for(auto item : A)
    {
        if(item == Leader) HowManyLeadersCounter++;
    }
   
   float LeadersInLeftBucket = 0.0;
   float LeadersInRightBucket = HowManyLeadersCounter;
   
   for(unsigned int i = 0; i < A.size() - 1; ++i)
   {
        if(A[i] == Leader)
        {
            LeadersInLeftBucket++;
            LeadersInRightBucket--;
        }

        if (LeadersInLeftBucket / float(i + 1.0) > 0.5)
        {
            if(LeadersInRightBucket / float(A.size() - 1.0 - i) > 0.5) result++;
        }
   }
    
   return result;
}

int FindDominator(vector<int> &A)
{
    if(A.size() == 0) return -1;
    if(A.size() == 1) return 0;

    std::stack<int> Stack;
    Stack.push( A[0] );
    
    for(unsigned int i = 1; i < A.size(); ++i)
    {
        if(Stack.empty() || Stack.top() == A[i])
        {
            Stack.push(A[i]);
        }
        
        else
        {
            Stack.pop();
        }
    }

    int Candidate;
    
    if(!Stack.empty()) Candidate = Stack.top();
    else return -1;
    
    unsigned int Counter = 0;
    int Result = -1;
    
    for(unsigned int i = 0; i < A.size(); ++i)
    {
        if(A[i] == Candidate)
        {
            ++Counter;
            Result = i;
        }
    }

    if(Counter / float(A.size()) > 0.5) return Result;
    
    return -1;
}
