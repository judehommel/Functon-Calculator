#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iterator>
#include <fstream>

using namespace std;

float m;
float b;
float c;

vector<float> extractNums(string data)
{
    vector<float> shrtData;
    vector<float> nothing;

    unsigned delim1 = data.find(',');
    //if there is stuff between start and ,
    if (delim1 - 1 >= 0)
        shrtData.push_back(stof(data.substr(0, delim1))); //record number
    else
        return nothing;
    //erase data that was already read
    data.erase(data.begin(), data.begin() + delim1 + 1);

    //count stops loop from ending earily
    int count = data.size();
    while(data.find(',') < 500)
    {
        //find first ,
        delim1 = data.find(',');
        //check if data isn't only equal to , or nothing
        shrtData.push_back(stof(data.substr(0, delim1))); //record number
        //erase data that was already read
        data.erase(data.begin(), data.begin() + delim1 + 1);
    }
    shrtData.push_back(stof(data));
    return shrtData;
}

void calculateLinear(vector<float>& arr)
{
    m = (arr[3] - arr[1]) / (arr[2] - arr[0]);
    b = arr[1] - m * arr[0];
}

void calculateExpo(vector<float>& arr)
{
    float temp1 = arr[1] / arr[3];
    float temp2 = 1.0 / (arr[0] - arr[2]);
    m = pow(temp1, temp2);
    b = arr[1] / pow(m, arr[0]);
}

void calculateQuad(vector<float>& arr)
{
    m = (arr[0] * (arr[5] - arr[3]) + arr[2] * (arr[1] - arr[5]) + arr[4] * (arr[3] - arr[1])) / ((arr[0] - arr[2]) * (arr[0] - arr[4]) * (arr[2] - arr[4]));
    b = (arr[3] - arr[1]) / (arr[2] - arr[0]) - m * (arr[0] + arr[2]);
    c = arr[1] - m * pow(arr[0], 2) - b * arr[0];
}

int main()
{
    float pointN;
    string coords;
    cout << "Input number of points: ";
    cin >> pointN;
    if (pointN <= 1 && !(floor(pointN) == pointN)) //checks if pointN is an integer
    {
        cout << "Please enter a whole number bigger than 1";
        return 0;
    }
    cout << "Enter points with something other than a space separating the numbers: ";
    cin >> coords;
    vector <float> nums = extractNums(coords);
    int eq;
    for (int i = 0; i < nums.size(); i++)
        cout << nums[i] << endl;
    if (pointN < 2)
    {
        cout << "Please Enter a number of points that is greater than or equal to 2";
        system("pause");
        return 0;
    }
    else if (pointN == 2)
    {
        eq = 1;
        calculateLinear(nums);
        cout << "y=" << m << "x+" << b << endl;
        system("pause");
        return 0;
    }
    else if (pointN > 2)
    {
        calculateLinear(nums);
        int o = 0;
        for (int i = 0; i < pointN * 2; i += 2) {
            if (nums[i + 1] == m * nums[i] + b)
            {
                o++;
                if (o > pointN - 1)
                {
                    cout << "y=" << m << "x+" << b << endl;
                    eq = 1;
                }
            }
            else
            {
                break;
            }
        }
        calculateExpo(nums);
        o = 0;
        for (int i = 0; i < pointN * 2; i += 2) {
            if (nums[i + 1] == b * pow(m, nums[i]))
            {
                o++;
                if (o > pointN - 1)
                {
                    cout << "y=" << b << "*" << m << "^x" << endl;
                    eq = 2;
                }
            }
            else
            {
                break;
            }
        }
        calculateQuad(nums);
        o = 0;
        for (int i = 0; i < pointN * 2; i += 2)
        {
            if (nums[i + 1] == (m * pow(nums[i], 2) + b * nums[i] + c))
            {
                o++;
                if (o > pointN - 1)
                {
                    cout << "y=" << m << "x^2+" << b << "x+" << c << endl;
                    eq = 3;
                }
            }
            else
            {
                cout << "Error: Points do not equate to a graph";
                system("pause");
                return 1;
            }
        }
    }
    system("pause");

    return 0;
}

