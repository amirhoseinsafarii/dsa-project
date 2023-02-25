#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
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


int main() {

    int n;
   
    float avg_workflow_time;
    float avg_waiting_time;
  
    int total_workflow_time = 0;
    int total_waiting_time = 0;

    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));

    cout << setprecision(2) << fixed;

cout<<" please enter  number of patient (max number of patients=1000) : ";
    cin>>n;
      struct patient p[n];

      int no_of_bed;
 cout<<" please enter number of bed (max number of patients=1000) : ";
    cin>>no_of_bed;


         if (n ==0 || no_of_bed ==0  )
    {
        throw ; // invalid input handling
    }

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

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].cure_time < mn) {
                    mn = p[i].cure_time;
                    idx = i;
                }
                if(p[i].cure_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].cure_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].cure_time;
            p[idx].workflow_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].workflow_time - p[idx].cure_time;
            p[idx].start_time - p[idx].arrival_time > p[idx].priority ? p[idx].isdead=1 : p[idx].isdead=0;
            
            total_workflow_time += p[idx].workflow_time;
            total_waiting_time += p[idx].waiting_time;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_workflow_time = (float) total_workflow_time / n;
    avg_waiting_time = (float) total_waiting_time / n;

    cout<<endl<<endl;

 cout<<"#SSN\t"<<"arrival_time\t"<<"needed time\t"<<"reception time\t"<<"waiting time\t"<<"isdead"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
cout<<p[i].ssn<<"\t \t"<<p[i].arrival_time<<"\t \t"<<p[i].cure_time<<"\t \t"<<p[i].start_time<<"\t "<<"\t"<<p[i].waiting_time<<"\t \t \t"<<p[i].isdead<<"\t"<<"\n"<<endl;    }
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
 


}