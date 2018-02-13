float get_probability (int a, int move);

float drone_flight_planner (int **map, int **policies, float **values, float delivery_fee, float battery_drop_cost, float dronerepair_cost, float discount_per_cycle)
{

	// PUT YOUR CODE HERE
	// access the map using "map[y][x]"
	// access the policies using "policies[y][x]"
	// access the values using "values[y][x]"
	// y between 0 and 5
	// x between 0 and 5
	// function must return the value of the cell corresponding to the starting position of the drone
	// 
	float qmax,q,p,cost,delta,gamma=1-discount_per_cycle,prev_values[6][6] = {{0}};
	int i,j,x,y,a,amax,newx,newy;
	bool converge = false;


	// iterations
	while(!converge)
	{
		converge = true;
		// loop through all states
		for(y=0;y<6;y++)
		{
			for(x=0;x<6;x++)
			{
				if(map[y][x]==2)
				{
					qmax = delivery_fee;
				}
				else if(map[y][x]==3)
				{
					qmax = -1*dronerepair_cost;
				}
				else
				{
					qmax=-9999999.9;
					for(a=1;a<=8;a++)
					{
						q=0;

						cost = -1*battery_drop_cost;
						if(a>4)
							{cost = -2*battery_drop_cost;}

						//State 1
						newx = x+1;
						newy = y;
						if(newx>5)
							{newx = x;}
						p = get_probability(a,4);
						q += p*(cost+gamma*prev_values[newy][newx]);
						//State 2
						newx = x;
						newy = y+1;
						if(newy>5)
							{newy = y;}
						p = get_probability(a,1);
						q += p*(cost+gamma*prev_values[newy][newx]);
						//State 3
						newx = x-1;
						newy = y;
						if(newx<0)
							{newx = x;}
						p = get_probability(a,2);
						q += p*(cost+gamma*prev_values[newy][newx]);
						//State 4
						newx = x;
						newy = y-1;
						if(newy<0)
							{newy = y;}
						p = get_probability(a,3);
						q += p*(cost+gamma*prev_values[newy][newx]);

						if(q>qmax)
						{
							qmax=q;
						}


					}
				}
				delta = prev_values[y][x] - qmax;
				if(delta<0)
					{delta=-1*delta;}	
				if(delta>0.000000001)
				{
					converge = false;
				}
				values[y][x] = qmax;
			}
		}

		for(i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				prev_values[i][j] = values[i][j];
			}
		}

	}


	for(y=0;y<6;y++)
	{
		for(x=0;x<6;x++)
		{
			amax=0;
			if(map[y][x]==0 || map[y][x]==1)
			{
				qmax=-9999999.9;
				for(a=1;a<=8;a++)
				{
					q=0;

					cost = -1*battery_drop_cost;
					if(a>4)
						{cost = -2*battery_drop_cost;}

					//State 1
					newx = x+1;
					newy = y;
					if(newx>5)
						{newx = x;}
					p = get_probability(a,4);
					q += p*(cost+gamma*prev_values[newy][newx]);
					//State 2
					newx = x;
					newy = y+1;
					if(newy>5)
						{newy = y;}
					p = get_probability(a,1);
					q += p*(cost+gamma*prev_values[newy][newx]);
					//State 3
					newx = x-1;
					newy = y;
					if(newx<0)
						{newx = x;}
					p = get_probability(a,2);
					q += p*(cost+gamma*prev_values[newy][newx]);
					//State 4
					newx = x;
					newy = y-1;
					if(newy<0)
						{newy = y;}
					p = get_probability(a,3);
					q += p*(cost+gamma*prev_values[newy][newx]);

					if(q>qmax)
					{
						qmax=q;
						amax=a;
					}
				}
			}
			policies[y][x] = amax;
		}
	}

	for(i=0;i<6;i++)
		{
			for(j=0;j<6;j++)
			{
				if(map[i][j]==1)
				{
					return values[i][j];
				}
			}
		}
	return 0;
}


float get_probability (int a, int move)
{
	// Move: 1 is South, 2 is West, 3 is North, 4 is East 
	float bonus = 0;
	switch(a)
	{
		case 5:
			bonus = 0.1;
		case 1:
			if(move==1)
				return (0.7+bonus);
			if(move==2 || move==4)
				return (0.15-bonus/2);
			break;
		case 6:
			bonus = 0.1;
		case 2:
			if(move==2)
				return (0.7+bonus);
			if(move==1 || move==3)
				return (0.15-bonus/2);
			break;
		case 7:
			bonus = 0.1;
		case 3:
			if(move==3)
				return (0.7+bonus);
			if(move==2 || move==4)
				return (0.15-bonus/2);
			break;
		case 8:
			bonus = 0.1;
		case 4:
			if(move==4)
				return (0.7+bonus);
			if(move==1 || move==3)
				return (0.15-bonus/2);
			break;
		default:
			break;
	}
	return 0;
}






