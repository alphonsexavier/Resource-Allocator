/* Resource Allocator

Arrays price and capacity hold the values of the cost for running the machine per hour and the capacity of the machines respectively.

The arrays cnt and cnt2 hold the values for the number of machines that will be required and using the values stored in these arrays
the price is calculated.

*/

#include<iostream>
using namespace std;

int price[6][3]={{120,140,110},{230,0,220},{450,413,0},{774,890,670},{1400,1300,1180},{2820,2970,0}};
int capacity[6][3]={{10,10,10}, {20,0,20},{40,40,0},{80,80,80},{160,160,160},{320,320,0}}, cnt[6]={0}, cnt2[6]={0};
int  hours, upper_limit, f_index, index, index2, div, rem_units, eff_cost=0, region=0;

/*
This function is used for finding the upper limit
*/

void upper(int units)
{
    for(int j=4;j>=0;j--)
            {
                if(units>=capacity[j][region] && capacity[j][region]!=0) //This condition checks and allows only machines that are available in a particular region i.e. India does not have X Large machine (20), hence the upper limit cannot be 20 for India
                {
                    upper_limit=capacity[j][region];
                    index=j;
                    break;
                }
            }
}

/*
This function is used to copy the values from cnt to cnt2
By copying the values from cnt to cnt2, we get hold of the count of the number of machines that needs to be run in order to get the efficient cost
Once it is copied, the whole cnt array is reinitialized with the value zero
*/

void copyCount()
{
    for(int i=0;i<6;i++)
    {
        cnt2[i]=cnt[i];
    }
}

void reInit()
{
    for(int i=0;i<6;i++)
    {
        cnt[i]=0;
    }
}

//Once a region is completed, this function is used to get the array cnt2 ready for the next region by reinitializing all the values in it to zero

void reInit2()
{
    for(int i=0;i<6;i++)
    {
        cnt2[i]=0;
    }
}

//This function is used for printing the machine that will be used in a particular region to achieve the efficient cost and also gives us the number of times the machine is run

void print2()
{
    for(int i=5;i>=0;i--)
    {
            switch(i)
        {
            case 0 : if(cnt2[i]>=1)
                        cout<<"\nLarge: "<<cnt2[i];
                    break;
            case 1 : if(cnt2[i]>=1)
                        cout<<"\nxLarge: "<<cnt2[i];
                    break;
            case 2 : if(cnt2[i]>=1)
                        cout<<"\n2xLarge: "<<cnt2[i];
                    break;
            case 3 : if(cnt2[i]>=1)
                        cout<<"\n4xLarge: "<<cnt2[i];
                    break;
            case 4 : if(cnt2[i]>=1)
                        cout<<"\n8xLarge: "<<cnt2[i];
                    break;
            case 5 : if(cnt2[i]>=1)
                        cout<<"\n10xLarge: "<<cnt2[i];
                    break;
        }
    }
    cout<<"\n";
}

//This function is used for printing the efficient cost for the three regions

void print()
{
    switch(region)
    {
        case 0: cout<<"\nRegion: New York";
                cout<<"\nTotal Cost: "<<eff_cost * hours ;
                break;
        case 1: cout<<"\nRegion: India";
                cout<<"\nTotal Cost: "<<eff_cost * hours;
                break;
        case 2: cout<<"\nRegion: China";
                cout<<"\nTotal Cost: "<<eff_cost * hours;
                break;
    }
}

int main()
{
    int  units, cost=0, flag=0;


    cout<<"\nEnter the no of hours the machine is required to run: ";
    cin>>hours;

/* Test Case 1: To test if the hours entered is valid*/

    while(1)
    {
        if(hours<=0)
        {
            cout<<"\nPlease enter a valid hour";
            cin>>hours;
        }
        else
            break;
    }
    cout<<"\nEnter the no of units required: ";
    cin>>units;

/* Test Case 2: To test if the units entered is a multiple of 10*/

     while(1)
    {
        if(units%10!=0)
        {
            cout<<"\nPlease enter the units in multiples of 10";
            cin>>units;
        }
        else
            break;
    }

//Since there are three regions, the loop is executed three times

    for(;region<3;region++)
    {

        if(units > 320) // To find the upper limit if the entered unit is greater than 320 units
        {
            if(region==2)//Except for China, USA and India have a 10x Large (320) Machine, so the first high functioning machine will be (160)
            {
               upper_limit=160;
               index=4;
            }
            else
            {
                upper_limit=320;
                index=5;
            }
        }
        else // To find the upper limit if the entered unit is less than 320 units
        {
            for(int j=4;j>=0;j--)
            {
                if(units>=capacity[j][region]&&capacity[j][region]!=0)
                {
                    upper_limit=capacity[j][region];
                    index=j;
                    break;
                }
            }
        }

        rem_units=units;
        f_index=index;
        index2=index;

// The below code tries to find the efficient cost by making each machine capacity as its upper limit

        for(;index2>=0;)
        {
            for(;;)
            {
                if(capacity[index][region]==0)
                {
                    index--;
                }
                cnt[index]=rem_units/capacity[index][region]; //Used for finding the number of times a machine is run and also acts as a marker for that machine
                rem_units=rem_units%capacity[index][region]; //Used for finding the remaining units that needs to be allocated a machine
                if(rem_units!=0)
                {
                    upper(rem_units);
                }
                else
                    break;
            }

            for(int i=0;i<6;i++)
            {
                if(cnt[i]>=1)
                cost=cost + ( cnt[i] * price[i][region] ); //The cost is calculated here
            }

//If the new cost found is efficient than the older one, the cost value is changed and the values from cnt are copied over to cnt2

            if(cost<eff_cost && flag==1)
            {
                eff_cost=cost;
                copyCount();
            }

            if(flag==0)
            {
                eff_cost=cost;//Stores the first cost that is calculated for each region and the flag value is changed later in the code, so that this block of code is run only once for a region
                copyCount();
            }

            rem_units=units;
            index=--index2;
            flag=1;
            cost=0;
            reInit();
        }

        print();
        print2();
        reInit2();
        cost=0;
        eff_cost=0;
        flag=0;
    }

}
