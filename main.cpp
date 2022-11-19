#include <iostream>
#include <cmath>
#include <array>

using namespace std;

float m;
float b;
float c;

void extractNums(char str[], array<float, 20>& arr, float n) //Doesn't work with triple digits yet
{
    int o=0;
    for(int i=0;i<n*5;i++)
    {
        if(str[i]=='0'||str[i]=='1'||str[i]=='2'||str[i]=='3'||str[i]=='4'||str[i]=='5'||str[i]=='6'||str[i]=='7'||str[i]=='8'||str[i]=='9')
        {
            if(str[i-1]=='-')
                arr[o]=-1*atof(&str[i]); //set all negative numbers in str to array of floats
            else
                arr[o]=atof(&str[i]); //set all positive numbers in str to array of floats
            o++;
        }
        for(int m=1;m<5;m++) //Correct double digits repeating last digit
        {
            if(floor(log10(arr[o-1]) + 1)>m)
            {
                i+=m+1;
            }
        }
    }
}

void calculateLinear(array<float, 20>& arr)
{
    m = (arr[3]-arr[1])/(arr[2]-arr[0]);
    b = arr[1]-m*arr[0];
}

void calculateExpo(array<float, 20>& arr)
{
    float temp1 = arr[1]/arr[3];
    float temp2 = 1.0/(arr[0]-arr[2]);
    m = pow(temp1,temp2);
    b = arr[1]/pow(m,arr[0]);
}

void calculateQuad(array<float, 20>& arr)
{
    m=(arr[0]*(arr[5]-arr[3])+arr[2]*(arr[1]-arr[5])+arr[4]*(arr[3]-arr[1]))/((arr[0]-arr[2])*(arr[0]-arr[4])*(arr[2]-arr[4]));
    b=(arr[3]-arr[1])/(arr[2]-arr[0])-m*(arr[0]+arr[2]);
    c=arr[1]-m*pow(arr[0],2)-b*arr[0];
}

int main()
{
    float pointN;
    char coords[200];
    cout<<"Input number of points: ";
    cin>>pointN;
    for(int i=0;i<10;i++)
    {
        if(pointN<=0 || pointN<i && pointN>i-1) //checks if pointN is an integer
        {
            cout<<"Please enter an integer ie. 1, 5, 8";
            return 0;
        }
    }
    array<float, 20> nums{};
    cout<<"Enter points with something other than a space separating the numbers: ";
    cin>>coords;
    extractNums(coords, nums, pointN);
    int eq;
    for(int i=0;i<sizeof(nums)/sizeof(nums[0]);i++)
        cout<<nums[i]<<endl;
    if (pointN<2)
    {
        cout<<"Please Enter a number of points that is greater than or equal to 2";
        system("pause");
        return 0;
    }
    else if(pointN==2)
    {
        eq=1;
        calculateLinear(nums);
        cout<<"y="<<m<<"x+"<<b<<endl;
        system("pause");
        return 0;
    }
    else if(pointN>2)
    {
        calculateLinear(nums);
        int o=0;
        for (int i=0; i<pointN*2; i+=2) {
            if(nums[i+1]==m*nums[i]+b)
            {
                o++;
                if(o>pointN-1)
                {
                    cout<<"y="<<m<<"x+"<<b<<endl;
                    eq=1;
                }
            }
            else
            {
                break;
            }
        }
        calculateExpo(nums);
        o=0;
        for (int i=0; i<pointN*2; i+=2) {
            if(nums[i+1]==b*pow(m,nums[i]))
            {
                o++;
                if(o>pointN-1)
                {
                    cout<<"y="<<b<<"*"<<m<<"^x"<<endl;
                    eq=2;
                }
            }
            else
            {
                break;
            }
        }
        calculateQuad(nums);
        o=0;
        for (int i=0; i<pointN*2; i+=2)
        {
            if(nums[i+1]==(m*pow(nums[i],2)+b*nums[i]+c))
            {
                o++;
                if(o>pointN-1)
                {
                    cout<<"y="<<m<<"x^2+"<<b<<"x+"<<c<<endl;
                    eq=3;
                }
            }
            else
            {
                    cout<<"Error: Points do not equate to a graph";
                    system("pause");
                    return 1;
            }
        }
    }
    system("pause");
    return 0;
}

