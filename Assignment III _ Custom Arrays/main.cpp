// ASSIGNMENT 3 :: OOP [programming 2]

/*
	ASSIGNMNET 3 - PROG2 - CS213
	PROJECT :: Diffrent Arrays 
	DATE    :: winter 2021.12.24 
	AUTHORS ::
		1 - David George Monir 			ID : 20201059
		2 - Maher Mohsen Bahig  		ID : 20200415
*/


#include <bits/stdc++.h>
#include <fstream>

using namespace std ;

// enum Array_types { FloatArray , SortedArray , FrontArray , PostiveArray , NegativeArray } ;

/*
    // Float Array
            // size
            // dynamic array 
            // parameterized constructor takes array size 
            // method add takes a float and add it to end of the array we have 
            // extracton >>
            // insetion  <<
            
*/

class FloatArray {
        public : 
            int size_ ; 
            int fill = 0 ; 
            float *array_ ;

            FloatArray( int size ) {
                fill = 0 ;
                size_ = size ; 
                array_ = new float [size_] ;
            }
            virtual void add ( float value ) {
                array_[fill++] = value ; 
            } 

            // read from file 
            friend ifstream & operator >> ( ifstream & in , FloatArray & obj ) {
                    float value ; 
                    int n = obj.size_ ; 
                    for ( int i = 0 ; i < n ; i++ ) {
                        // in >> '\t' >> value ; 
                        in >> value ; 
                        obj.add(value) ; 
                    }
                    return in ; 
            }

            // out to file 
            friend ofstream & operator << ( ofstream & out , FloatArray  & obj ) {
                    out << obj.size_ << '|' ;
                    for ( int i = 0 ; i < obj.size_ ; i++ ) {
                        out << '\t' << obj.array_[i] ; 
                    }
                    out << endl ;
                    return out ;
            }

            ~FloatArray() {
                delete [] array_ ; 
            }

};

/*
    //SortedArray inhertis from Float_Array
            // parameterized constructor takes array size 
            // method add takes a float and add it to right place array we have 

*/

class SortedArray : public FloatArray {

        public :
            SortedArray ( int size ) : FloatArray (size) {}
            virtual void add ( float value ) {
                bool done = 0 ;
                for ( int i = 0 ; i < fill ; i++ ) {
                    if ( value <= array_[i] ) {
                            // left shift 
                            for ( int j = fill  ; j > i ; j-- ) {
                                array_[j]  = array_[j - 1] ; 
                            }
                            array_[i] = value ; 
                            done = 1 ; 
                            break ; 
                    }
                }
                if (!done) {
                    array_[fill] = value ; 
                }
                fill++;
            }

};

/*
    //FrontArray inhertis from Float_Array
            // parameterized constructor takes array size 
            // method add takes a float and add it to the fornt of array we have 
*/

class FrontArray : public FloatArray {
        public :
            FrontArray ( int size ) : FloatArray (size) {}
            virtual void add ( float value ) {
                array_[ size_ - fill - 1 ] = value ;
                fill++ ;
            }

};

/*
    //PostiveArray inhertis from sorted_Array
            // parameterized constructor takes array size 
            // method add takes a float and add it only if it is postive to array we have 

*/

class PostiveArray : public SortedArray {

        public :
            PostiveArray( int size ) : SortedArray ( size ) {}
            virtual void add ( float value ) {
                if ( value > 0 ) {
                    SortedArray :: add ( value ) ; 
                }
                else {
                    size_ -- ; 
                }
            }
};

/*
    //NegativeArray inhertis from sorted_Array
            // parameterized constructor takes array size 
            // method add takes a float and add it only if it is negative to array we have 

*/

class NegativeArray : public SortedArray {

        public :
            NegativeArray( int size ) : SortedArray ( size ) {}
            virtual void add ( float value ) {
                if ( value < 0 ) { 
                    SortedArray :: add ( value ) ; 
                }
                else {
                    size_ -- ;
                }
            }
};

/*
    // main :
        // take input file name 
        // take output file name
        // open files one for in and other for out 
        // a pointer of base class FloatArray = nullptr
        // loop 10 times insert from file and brust into file 
            // insert from file string 
            // insert from file an integer 
            // decide which child to point into 
                // Array   
                // Sorted
                // Front 
                // Postive 
                // Negative 
                    // point to right the right derived class 
                        // and at the same step pass the int value to it's parameterixed constructor 
                        // do process 
                            // entering from a input  file using extraction >> 
                            // writing  to   a output file using insertion  << 
                            // return the pointer agin to nullptr 

            // enum Array_types { FloatArray , SortedArray , FrontArray , PostiveArray , NegativeArray }
*/

int main() {
    ifstream infile  ;
    ofstream outfile ; 
    string input , output  ; 
    while (  cout << "Please , Enter a valid name of input  file  :" << endl , cin >> input  ,  infile.open(  input.c_str() )  , infile.fail()  ) {}
    while (  cout << "Please , Enter a valid name of output file  :" << endl , cin >> output , outfile.open( output.c_str() )  , outfile.fail() ) {}
    FloatArray * FloatArray_ptr = nullptr ; 
    for ( int i = 0 ; i < 10 ; i++ ) {
        string type ; 
        int size ; 

        // read from file 
        infile >> type >> size ; 

        // determine type 
        if ( type == "Array" ) {
            FloatArray_ptr = new FloatArray(size) ;
        }
        else if ( type == "Sorted" ) {
            FloatArray_ptr = new SortedArray(size) ;
        }
        else if ( type == "Front" ) {
            FloatArray_ptr = new FrontArray(size) ;
        }
        else if ( type == "Positive" ) {
            FloatArray_ptr = new PostiveArray(size) ;
        }
        else if ( type == "Negative" ) {
            FloatArray_ptr = new NegativeArray(size) ;
        }

        // Files Processes
        infile  >> *FloatArray_ptr ; 
        outfile << *FloatArray_ptr ; 
        
        // avoid this 
        FloatArray_ptr = nullptr ; 

    }

    return 0 ; 
}
