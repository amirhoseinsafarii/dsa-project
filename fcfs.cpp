
#include <iostream>
#include <algorithm> 
#include <iomanip> 
using namespace std;

struct patient {
   long long  int pid;
    int arrival_time;
    int cure_time;
  
    int start_time;
    int completion_time;
    int workflow_time;
    int waiting_time;
  
     int isdead;
    int priority;
    long long int ssn;
    int hospital_id=-1;
};

bool compareArrival(patient p1, patient p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(patient p1, patient p2) 
{  
    return p1.pid < p2.pid;
}

int main() {

    int n;
    
    float avg_workflow_time;
    float avg_waiting_time;

    int total_workflow_time = 0;
    int total_waiting_time = 0;
 

    cout << setprecision(2) << fixed;

    cout<<" please enter number of patient (max number of patients=1000) : ";
    cin>>n;
int no_of_bed;
 cout<<" please enter number of bed (max number of patients=1000) : ";
    cin>>no_of_bed;

    
       if (n ==0 )
    {
        throw ; // invalid input handling
    }

  struct patient p[n];
    for(int i = 0; i < n; i++) {
        
         cout<<"Enter SSN of patient :  "<<endl;
        cin>>p[i].ssn;
        
        cout<<"Enter arrival time of patient "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter needed time of patient "<<i+1<<": ";
        cin>>p[i].cure_time;
            cout<< "Enter priority of patient  "<<i+1<<": "<<endl;
        cin>>p[i].priority;
        p[i].pid = i+1;
    
    }

    sort(p,p+n,compareArrival);

    for(int i = 0; i < n; i++) {
        p[i].start_time = (i == 0)?p[i].arrival_time:max(p[i-1].completion_time,p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].cure_time;
        p[i].workflow_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].workflow_time - p[i].cure_time;
        
        p[i].start_time - p[i].arrival_time > p[i].priority ? p[i].isdead=1 : p[i].isdead=0;
        
        

        total_workflow_time += p[i].workflow_time;
        total_waiting_time += p[i].waiting_time;
        
    }

    avg_workflow_time = (float) total_workflow_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    sort(p,p+n,compareID);

    cout<<endl;
    cout<<"#SSN\t"<<"arrival_time\t"<<"needed time\t"<<"reception time\t"<<"waiting time\t"<<"isdead"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
        cout<<p[i].ssn<<"\t \t"<<p[i].arrival_time<<"\t \t"<<p[i].cure_time<<"\t \t"<<p[i].start_time<<"\t "<<"\t"<<p[i].waiting_time<<"\t \t \t"<<p[i].isdead<<"\t"<<"\n"<<endl;
    }
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    
  


}

