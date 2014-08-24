#ifndef RANGE_H
#define RANGE_H

namespace Wrench
{
	template<class T>
	class Range
	{
	protected:
		T min;
		T max;
		T value;

	public:
		Range();
		Range(T Minimum, T Maximum, T Val);
		void Setup(T Minimum, T Maximum, T Val);

		T Min();
		T Max();
		T Value();

		void Min(T newMin);
		void Max(T newMax);
		T Value(T newValue);

		bool AtMin();
		bool AtMax();
	};

	template<class T>
	Range<T>::Range()
	{

	};

	template<class T>
	Range<T>::Range(T Minimum, T Maximum, T Val)
	{
		Setup(Minimum, Maximum, Val);
	};

	template<class T>
	void Range<T>::Setup(T Minimum, T Maximum, T Val)
	{
		min = Minimum;
		max = Maximum;
		value = Val;
	};

	template<class T>
	T Range<T>::Min()
	{
		return min;
	};

	template<class T>
	T Range<T>::Max()
	{
		return max;
	};

	template<class T>
	T Range<T>::Value()
	{
		return value;
	};

	template<class T>
	void Range<T>::Min(T newMin)
	{
		min = newMin;
	};

	template<class T>
	void Range<T>::Max(T newMax)
	{
		max = newMax;
	};

	template<class T>
	T Range<T>::Value(T newValue)
	{
		value = newValue;

		if(value < min)
			value = min;

		if(value > max)
			value = max;

		return value;
	};

	template<class T>
	bool Range<T>::AtMin()
	{
		if(value == min)
			return true;
		return false;
	};

	template<class T>
	bool Range<T>::AtMax()
	{
		if(value == max)
			return true;
		return false;
	};
}
#endif
