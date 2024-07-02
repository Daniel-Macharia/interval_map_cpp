#include<iostream>
#include <map>

using std::cout;
using std::endl;
using std::map;

template<typename K, typename V>
class interval_map 
{
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;

public:
	// constructor associates whole range of K with val
	interval_map(V const& val) : m_valBegin(val)
	{

  }

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) 
  {
    // INSERT YOUR SOLUTION HERE
    //This should be O(n): execution time grows linearly with respect to input size i.e N
    if(! (keyBegin < keyEnd) )
    {
      cout<<"Entered range is invalid!"<<endl;
      cout<<"Insert a valid range."<<endl;
      return;
    }

    if( m_map.size() == 0 )//first insertion into the data structure
    {
      if( val != m_valBegin )
      {
        //insert the value for the specified range
        m_map.insert({keyBegin, val});
        m_map.insert({keyEnd, NULL});//set upper interval bound to null
      }
      else
      {
        //new value cannot match the default value
        cout<<"Entered value is similar to the default one!"<<endl;
        cout<<"Please enter a different value"<<endl;
        return;
      }

    }
    else//consecutive insertions
    {
      auto it = m_map.end();//get last map element
      it--;
      
      if( !(it->second) )//only when the last element has a null value
      {
        m_map.erase(it);//remove null element
      }

      auto lastElement = m_map.end();
      auto currentElement = m_map.begin();
      lastElement--;

      while( currentElement != m_map.end() )
      {
        if( currentElement->first > keyBegin )
        {
          --currentElement;
          break;
        }
         currentElement++;
      }

      if( currentElement->second == val )//dont insert similar consecutive values
      {
        cout<<"Similar value("<<val<<") at key "<<keyBegin<<" exists!"<<endl;
        cout<<"Please enter a different value"<<endl;
        return;
      }

      m_map.insert( {keyBegin, val});

      m_map.erase((m_map.upper_bound(keyBegin)), (m_map.lower_bound(keyEnd)) );

    }

    /*
        void IntervalMapTest()
        {
          interval_map<int, char> m('V');

          m.assign(1,10,'A');
          m.assign(20, 30, 'B');
          m.assign(25, 30, 'C');
          m.assign(40, 45, 'Y');
          m.assign(50, 68, 'M');
          m.assign(22, 27, 'D');
          m.assign(30, 37, 'E');
          m.assign(14, 18, 'S');
          m.assign(33, 40, 'J');
          m.assign(26, 32, 'K');
          m.assign(35, 39, 'J');
          m.assign(35, 32, 'J');

          auto it = m.m_map.begin();

          while( it != m.m_map.end() )
          {
            cout<<it->first<<" ===> "<<it->second<<endl;
            it++;
          }

        }
    */

	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const 
  {

		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) 
    {
			return m_valBegin;
		}
    else
    {
			return (--it)->second;
		}

	}

};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

void IntervalMapTest()
{
  interval_map<int, char> m('V');

  m.assign(1,10,'A');
  m.assign(20, 30, 'B');
  m.assign(25, 30, 'C');
  m.assign(40, 45, 'Y');
  m.assign(50, 68, 'M');
  m.assign(22, 27, 'D');
  m.assign(30, 37, 'E');
  m.assign(14, 18, 'S');
  m.assign(33, 40, 'J');
  m.assign(26, 32, 'K');
  m.assign(35, 39, 'J');
  m.assign(35, 32, 'J');

  auto it = m.m_map.begin();

  while( it != m.m_map.end() )
  {
    cout<<it->first<<" ===> "<<it->second<<endl;
    it++;
  }

}

int main()
{
  IntervalMapTest();
  return 0;
}