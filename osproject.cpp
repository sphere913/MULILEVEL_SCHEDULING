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
bool arrivalsort( const p_inf& p ,const p_inf& q)
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

/**To check the Input **/
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
	vector< p_inf > input;
	vector<p_inf> input_copy;
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
	cin>>n;
	for( i= 0; i< n; i++ )
	{
		cin>>processid>>arrivaltime>>bursttime>>priority;
		temp.number = i+1;
		temp.arrivaltime = arrivaltime;
		temp.bursttime = bursttime;
		temp.remainingtime = bursttime;
		temp.processid = processid;
		temp.priority = priority;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );
    //cout<<"arrivalsort : "<<endl;
    //my_check( input ); // To check the sort unomment it
    totalexecutiontime = totalexecutiontime + input[0].arrivaltime;
    for( i= 0 ;i< n; i++ )
    {
    	if( totalexecutiontime >= input[i].arrivaltime )
    	{
    		totalexecutiontime = totalexecutiontime +input[i].bursttime;
    	}
    	else
    	{
    		int diff = (input[i].arrivaltime - totalexecutiontime);
    		totalexecutiontime = totalexecutiontime + diff + bursttime;

    	}
    }

	int Ghant[totalexecutiontime]={0}; //Ghant Chart
	for( i= 0; i< totalexecutiontime; i++ )
	{
		Ghant[i]=-1;
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
			if(clock == input[j].arrivaltime)
			{
				pq.push(input[j]);
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
			Ghant[clock] = current.processid;
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


	sort( input.begin(), input.end(), idsort );
	
	for(int i=0;i<n;i++)
	{
		for(int k=totalexecutiontime;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].finishtime=k+1;
				break;

			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<totalexecutiontime;k++)
		{

			if(Ghant[k]==i+1)
			{
				input[i].starttime=k;
				break;
			}
		}
	}
	
	sort( input.begin(), input.end(), numbersort );

	for(int i=0;i<n;i++)
	{
		input[i].restarttime=input[i].starttime-input[i].arrivaltime;
		input[i].waitingtime=(input[i].finishtime-input[i].arrivaltime)-input[i].bursttime;

	}
	
	for(int i=0;i<n;i++)
	{
		cout<<input[i].processid<<" "<<input[i].restarttime<<" "<<input[i].finishtime<<" "<<input[i].waitingtime<<endl;
		
	}	
	return 0;
}
