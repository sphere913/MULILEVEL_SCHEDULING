/* MADHUSUDAN SINGH reg no.-11612945 */
#include <bits/stdc++.h>
using namespace std;

class process_information
{
	public:
	int number;
	int processid;  
	int arrivaltime; 
	int bursttime;
	int priority; 
	int finishtime; 
	int remainingtime;
	int waitingtime; 
	int starttime; 
	int restarttime;

};

 process_information current;
typedef  process_information p_inf ;

bool idsort(const p_inf& a , const p_inf& b)
{
	return a.processid < b.processid;
}
/** Sorting on the base of arrival time if that match then on priority of priority also  match than on the base of Process Id**/
bool arrivalordering( const p_inf& p ,const p_inf& q)
{
	if(p.arrivaltime < p.arrivaltime)
		return true;
	else if(p.arrivaltime > p.arrivaltime)
		return false;
	if(p.priority < p.priority)
		return true;
	else if(p.priority > p.priority)
		return false;
	if(p.processid < p.processid)
		return true;

	return false;
}


bool numbersort( const p_inf& m ,const p_inf& n)
{
	return m.number < n.number;
}
/*Sorting on the base of priority if that same then on the base of processid*/
struct comPare
{
	bool operator()(const p_inf& x ,const p_inf& y)
	{
		if( x.priority > y.priority )
			return true;
		else if( x.priority < y.priority )
			return false;
		if( x.processid > y.processid )
			return true;

		return false;
		
	}
	
};

/**To check the givenuserinput **/
void my_check(vector<p_inf> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" processid :"<<mv[i].processid<<" _time : "<<mv[i].arrivaltime<<" bursttime : "<<mv[i].bursttime<<" priority : "<<mv[i].priority<<endl;
	}

}

int main()
{
	int i;
	vector< p_inf > givenuserinput;
	vector<p_inf> givenuserinput_copy;
	p_inf temp;
	int pq_process = 0; // for PQ process
	int rq_process = 0; // for RQ process
	int arrivaltime;
	int bursttime;
	int processid;
	int priority;
	int n;
	int clock;
	int totalexecutiontime = 0;
	cout<<"\nEnter the no. of process\n";
	cin>>n;
	for( i= 0; i< n; i++ )
	{
		cout<<"\nEnter the following detail for process  "<<i+1 <<"  below :\n";
		cout<<"\nEnter process Id :";
		
		cin>>processid;
		cout<<"\nEnter Arrival Time :";
		cin>>arrivaltime;
		cout<<"\nEnter burst time :";
		
		cin>>bursttime;
		cout<<"\nEnter priority :";
		cin>>priority;
		temp.number = i+1;
		temp.arrivaltime = arrivaltime;
		temp.bursttime = bursttime;
		temp.remainingtime = bursttime;
		temp.processid = processid;
		temp.priority = priority;
		givenuserinput.push_back(temp);
	}
	givenuserinput_copy = givenuserinput;
	sort( givenuserinput.begin(), givenuserinput.end(), arrivalordering );
    //cout<<"arrivalordering : "<<endl;
    //my_check( givenuserinput ); // To check the sort unomment it
    totalexecutiontime = totalexecutiontime + givenuserinput[0].arrivaltime;
    for( i= 0 ;i< n; i++ )
    {
    	if( totalexecutiontime >= givenuserinput[i].arrivaltime )
    	{
    		totalexecutiontime = totalexecutiontime +givenuserinput[i].bursttime;
    	}
    	else
    	{
    		int diff = (givenuserinput[i].arrivaltime - totalexecutiontime);
    		totalexecutiontime = totalexecutiontime + diff + bursttime;

    	}
    }

	int ghant_array[totalexecutiontime]={0}; //ghant_array Chart
	for( i= 0; i< totalexecutiontime; i++ )
	{
		ghant_array[i]=-1;
	}
	//cout<<"totalexecutiontime : "<<totalexecutiontime<<endl;

	priority_queue < p_inf ,vector<process_information> ,comPare> pq; //priority Queue PQ

	queue< p_inf > rq; //Round Robin Queue RQ
	int cpu_state = 0; //idle if 0 then Idle if 1 the Busy
	int quantum = 4 ; //Time Quantum
	current.processid = -2;
	current.priority = 999999;

	for ( clock = 0; clock< totalexecutiontime; clock++ )
	{
		/**Insert the process with same Arrival time in priority Queue**/
		for( int j = 0; j< n ; j++ )
		{
			if(clock == givenuserinput[j].arrivaltime)
			{
				pq.push(givenuserinput[j]);
			}
		}
		

		if(cpu_state == 0) //If CPU idle
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4; 
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1) //If cpu has any procss
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().priority < current.priority ) //If new process has high priority
				{
					rq.push(current); //push current in RQ
					current = pq.top();
					pq.pop();
					quantum = 4; 
				}
			}
			else if(rq_process == 1 && (!pq.empty())) //If process is from RQ and new process come  in PQ
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}
			

		}


		if(current.processid != -2) // Process Execution
		{
			current.remainingtime--;
			quantum--;
			ghant_array[clock] = current.processid;
			if(current.remainingtime == 0) //If process Finish
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.processid = -2;
				current.priority = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 ) //If time Qunatum of a current running process Finish
			{
				rq.push(current);
				current.processid = -2;
				current.priority = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;

			}

		}
		
	}


	sort( givenuserinput.begin(), givenuserinput.end(), idsort );
	
	for(int i=0;i<n;i++)
	{
		for(int k=totalexecutiontime;k>=0;k--)
		{
			if(ghant_array[k]==i+1)
			{
				givenuserinput[i].finishtime=k+1;
				break;

			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<totalexecutiontime;k++)
		{

			if(ghant_array[k]==i+1)
			{
				givenuserinput[i].starttime=k;
				break;
			}
		}
	}
	
	sort( givenuserinput.begin(), givenuserinput.end(), numbersort );

	for(int i=0;i<n;i++)
	{
		givenuserinput[i].restarttime=givenuserinput[i].starttime-givenuserinput[i].arrivaltime;
		givenuserinput[i].waitingtime=(givenuserinput[i].finishtime-givenuserinput[i].arrivaltime)-givenuserinput[i].bursttime;

	}
	cout<<"Process Id   restart time            finish time            waiting time\n";
	for(int i=0;i<n;i++)
	{
		cout<<givenuserinput[i].processid<<"                   "<<givenuserinput[i].restarttime<<"                     "<<givenuserinput[i].finishtime<<"                       "<<givenuserinput[i].waitingtime<<endl;
		
	}	
	return 0;
}
