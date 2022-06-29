#pragma once
#include <iostream>

class Time
{
private:
	int day;
	int hour;

public:

	Time()
	{
		day = 0;
		hour = 0;
	}


	Time(int d, int h)
	{
		day = d;
		hour = h;
	}



	int getDay()
	{
		return day;
	}

	int getHour()
	{
		return hour;
	}


	void setDay(int d)
	{
		day = d;
	}

	void setHour(int h)
	{
		hour = h;
	}

	bool TimeEqual(Time t2)
	{
		if (this->getDay() == t2.getDay())
		{
			if (this->getHour() == t2.getHour())
				return true;
		}
		return false;
	}

	void IncrementTime()
	{
		if (hour == 23)
		{
			day++;
			hour = 0;
			return;
		}
		else
		{
			hour++;
			return;
		}
	
	}

	Time Timediff(Time a, Time b)
	{
		Time c;
		c.setDay(a.day - b.day);
		c.setHour(hourDiff(a, b));
		return c;
	}

	static int hourDiff(Time a, Time b)
	{
		int sum = abs(a.day - b.day) * 24;
		sum += a.hour - b.hour;
		return sum;
	}

	static int dayDiff(Time a, Time b)
	{
		return abs(a.day - b.day);
	}

	static Time sumTimeTime(Time a, Time b)
	{
		int sumH = a.hour + b.hour;
		int sumD = a.day + b.day;
		if (sumH >= 24)
		{
			sumD += sumH / 24;
			sumH = sumH % 24;
		}

		Time c = Time(sumD, sumH);
		return c;
	}

	static Time sumTimeHour(Time a, int h)
	{
		Time C(0, 0);
		int sum = a.hour + h;

		if (sum >= 24)
		{
			C.day = a.day + sum / 24;
			C.hour =
				sum % 24;
		}
		return C;
	}


};