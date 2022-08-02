#include<iostream>
#include<math.h>
#include<iomanip>

using namespace std;

int main()
{
    int n;
    //input
    cout << "\nEnter the number of processes:";
    cin >> n;
    int bt[n]/*burst time*/, p[n] /*priority*/, s[n]/*shortnesscomponent*/, wt[n] /*waiting time*/, tat[n] /*turnaround time*/, ts /*time slice*/, its[n] /*intelligent time slice*/, tq[n][n] /*dynamic time quantum*/, rbt[n] /*remaining burst time*/, ord[n] /*processID*/;
    //initializing arrays
    for (int i = 0; i < n; i++)
    {
        wt[i] = tat[i] = 0;
        s[i] = 1;
        for (int j = 0; j < n; j++)
            tq[i][j] = 0;
    }
    cout << "\nEnter the initial time slice: ";
    cin >> ts;
    for (int i = 0; i < n; i++)
    {
        ord[i] = i + 1;
        cout << "\nEnter burst time for process " << i + 1 << ":";
        cin >> bt[i];
        cout << "\nEnter the priority of the process " << i + 1 << ":";
        cin >> p[i];
    }
    
    //sort based on burst times
    int flag = 0, j = 0;
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (bt[j] > bt[j - 1])
            {
                int t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;
                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
                t = ord[j];
                ord[j] = ord[j + 1];
                ord[j + 1] = t;
            }
    /*cout<<"after bt sorting\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << bt[i];
        cout << "\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << p[i];
        cout << "\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << ord[i];
        cout << "\n";
        cout << "\n";*/
   cout<<"after priority addition\n";
    for (int i = 0; i < n; i++)
        p[i] += i;
    for (int i = 0; i < n; i++)
        cout << setw(5) << p[i];
        cout << "\n"; 
        cout << "\n";
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            if (p[j] > p[j + 1])
            {
                int t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;
                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
                t = ord[j];
                ord[j] = ord[j + 1];
                ord[j + 1] = t;
            }
    cout<<"after priority sorting\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << bt[i];
        cout << "\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << p[i];
        cout << "\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << ord[i];
        cout << "\n";
        cout << "\n";
    for (int i = 0; i < n; i++)
        rbt[i] = bt[i];
    
    //main algorithm   
    while (!flag)
    {
        for (int i = 0; i < n; i++)
        {   
            //assigning priority
            if (p[i] > 0.5 * n)
                p[i] = 0;
            else if (p[i] > 0.2 * n)
                p[i] = 1;
            else
                p[i] = 2;
                cout<<"i-"<<i<<"pid-"<<ord[i]<<"prio-"<<p[i]<<"\n";
            //calculating shortness component
            if (i != 0)
                if ((bt[i] - bt[i - 1]) > 0)
                    s[i] = 0;
                  cout<<"i-"<<i<<"pid-"<<ord[i]<<"sc-"<<s[i]<<"\n";
            //calculating intelligent time slice
            its[i] = ts + bt[i] + s[i] + p[i];
            
            //assigning dtq for round 1.
            if (j == 0)
            {
                if (s[i] == 1)
                    tq[j][i] = its[i];
                else
                    tq[j][i] = ceil(0.5 * (float)its[i]);
                if (rbt[i] < tq[j][i])
                    tq[j][i] = rbt[i];
                rbt[i] = rbt[i] - tq[j][i];
            }
            else
            //assigning dtq for other rounds based on rbt
            {
                if (rbt[i] <= 0)
                    tq[j][i] = 0;
                else if (s[i] == 1)
                    tq[j][i] = 2 * tq[j - 1][i];
                else
                    tq[j][i] = 1.5 * tq[j - 1][i];
                if (rbt[i] < tq[j][i])
                    tq[j][i] = rbt[i];
                rbt[i] = rbt[i] - tq[j][i];
            }
        cout<<"\n";
        for (int i = 0; i < n; i++){
        for(int j=0; j<n;j++){
        cout << tq[i][j]<<' ';
        }
        cout<<endl;
        }
        
    }
        j++;
        flag = -1;
        for (int i = 0; i < n; i++)
            if (rbt[i] > 0)
                flag = 0;
    }
    cout<<"\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << p[i];
    cout << "\n\nProcess no.:\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << ord[i];
    cout << "\n\nBurst Times for the processes:\n";
    for (int i = 0; i < n; i++)
        cout << setw(5) << bt[i];
    cout << "\n\nDynamic Time Quantums for the processes:\n";
    for (int x = 0; x < j; x++)
    {
        cout << "Round " << x + 1 << ": " << endl;
        for (int y = 0; y < n; y++)
            cout << setw(5) << tq[x][y];
        cout << endl;
    }
    
    //calculating tat and wt
    for (int x = 0; x < n; x++)
    {
        flag = -1;
        for (int y = 0; y < j; y++)
        {
            for (int z = 0; z < n; z++)
            {
                if (z != x){
                    wt[x] += tq[y][z];
                }
                else if (z == x && tq[y + 1][z] == 0)
                {
                    flag = 0;
                    break;
                }
            }
            tat[x] += tq[y][x];
            if (flag == 0)
                break;
        }
        tat[x] += wt[x];
    }
    //printing
    
    cout<<"\nPID\tBT\tPr\tTAT\tWT\n";
    for(int i=0;i<n;i++){
        cout<<ord[i]<<"\t"<<bt[i]<<"\t"<<p[i]<<"\t"<<tat[i]<<"\t"<<wt[i]<<"\n";
    }
    
    float avwt = 0, avtat = 0;
    for (int i = 0; i < n; i++)
    {
        avwt += wt[i];
        avtat += tat[i];
    }
    avwt /= n;
    avtat /= n;
    cout << "\n\nAverage waiting time: " << avwt << endl;
    cout << "\nAverage turnaround time: " << avtat << endl;
    return 0;
}
