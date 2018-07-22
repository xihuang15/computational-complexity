#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include <fstream>
#include <string>

using namespace std;

int main()
{
        int m, n, o;
        /*cout << "please enter the elements number of U = " << endl;
        cin >> n ;
        cout << "please enter the number of subsets = " << endl;
        cin >> m ;
        cout << "please enter the sum of all subsets size = " << endl;
        cin >> o ;
        */
		srand((unsigned)time(NULL));
        for (n = 20; n <= 40; n = n + 1)
        {
                for (int i = 0; i < 10; i++)
                {
                        m = 400;
                        o = 2000;

                        /*generator*/
                        vector <set<int> > subset(m, set<int>());

                        

                        int j, k;
			k = (rand() % m);
			subset[k].insert(n);
                        
                        for (int i=0;i<m;i++)
                        while (subset[i].size()<2)
			{
                                k = (rand() % n) + 1;
                                subset[i].insert(k);
			}

                        for (unsigned int i = 0; i < o; i++)
                        {

				j = (rand() % m);
                                k = (rand() % n) + 1;
                                subset[j].insert(k);    // put the k-th element in U to the j-th+1 subset
                        }
			
			/*for (unsigned int i = 0; i < m; i++)
                        {
				while (subset[i].size()<5)
				{
					k = (rand() % n) + 1;
					subset[i].insert(k);    // put the k-th element in U to the j-th+1 subset
				}
                        }*/

                        /*reduction*/
                        string n_str = to_string(n);
                        string i_str = to_string(i);
                        string instance = n_str + "_"+i_str;

                        ofstream outfile("instance/" + instance);
                        outfile << "p cnf " << n << " " << 2*m << endl;
                        for (int i = 0; i < m; i++)
                        {
                                for (set<int>::iterator j = subset[i].begin(); j != subset[i].end(); j++)       // at least one element of subset S_i is in S
                                {
                                        outfile << *j << " ";
                                }
                                outfile << "0 " << endl;
                        }
                        for (int i = 0; i < m; i++)
                        {
                                for (set<int>::iterator j = subset[i].begin(); j != subset[i].end(); j++)       // at least one element of subset S_i is not in S
                                {
                                        outfile << "-" << *j << " ";
                                }
                                outfile << "0 " << endl;
                        }
                }
        }
        return 0;
}

