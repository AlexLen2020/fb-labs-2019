#include <fstream>
 #include <iostream>	
 #include <string>
 #include <math.h>
 
 
 using namespace std;
 
 int main()
 {
 	setlocale(LC_ALL, "RUS");
 	wifstream in("vsebigamibezprobelov.txt");
 	wofstream out("output.txt");
 	wifstream in2("tekstbezprobelov.txt");
 	wstring t,r;
 	int i = 0, e = 0;
 	double f=0.0, entropia = 0.0,ren,logar=0.0;
 	while(1)
	{
		in>>t;
		
		in2>>r;
		
 		for(int s=0;s<r.length(); s+=2)
 		{
 			if(t[0]==r[s] and t[1]==r[s+1])
 				e++;
		}
		out<<e<<endl;
		
		cout<<i<<endl;
		if(e!=0)
		{
			//f = (double)e/1024417;
			f= (double)e/512209;
			cout<<"�������: "<<f<<" ";
			logar=log10(f)/log10(2);
			cout<<"�������� :"<<logar<<endl;
			ren=f*logar;
			entropia+=ren;	
		}
		
		e=0;
		i++;
		
 		if(in.eof())
 			break;	
 		
	}
	entropia = entropia-ren;
	cout<<"� �������� � ��� ��� ����: "<<(entropia*-(1))/2;
 }
 
