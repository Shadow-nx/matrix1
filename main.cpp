#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

void show_matrix(int **matrix,int x,int y) {
	if(matrix==nullptr) {
		cout<<"matrix is empty"<<endl;
		return;
	}
	for(int i=0; i<x; i++) {
		for(int j=0; j<y; j++)
			cout<<setw(4)<<matrix[i][j];
		cout<<endl;
	}
}
void create_matrix(int **&matrix,int &x,int &y,int argc,char *argv[]) {
	int z=0;
	bool arg=false;
	string matrix_size;
	while(z<strlen(argv[1])) {
		if(argv[1][z]=='x' || argv[1][z]=='X') {
			arg=true;
			matrix_size="";
			z++;
		}
		if(arg==false && (argv[1][z]>='0' && argv[1][z]<='9')) {
			matrix_size=argv[1][z];
			x=x*10+atoi(matrix_size.c_str());
		} else if(arg==true && (argv[1][z]>='0' && argv[1][z]<='9')) {
			matrix_size=argv[1][z];
			y=y*10+atoi(matrix_size.c_str());
		}
		z++;
	}
	z=0;
	if(x!=0 && y!=0) {
		matrix=new int*[x];
		for (int i = 0; i < x; i++)
			matrix[i]= new int [y];
		for(int i=0; i<x; i++)
			for(int j=0; j<y; j++)
				matrix[i][j]=0;
		if(argc>3) {
			for(int i=0,k=2; i<x; i++)
				for(int j=0; j<y; j++,k++) {
					if(k<argc)
						matrix[i][j]=atoi(argv[k]);
				}
		} else if(argc==3) {
			string number;
			for(int i=0; i<x && argv[2][z]!='\0'; i++) {
				for(int j=0; j<y && argv[2][z]!='\0'; j++) {
					int a=1;
					if(argv[2][z]=='-') {
						a=-1;
						z++;
					}
					while(argv[2][z]>='0' && argv[2][z]<='9') {
						number=argv[2][z];
						matrix[i][j]=matrix[i][j]*10+atoi(number.c_str());
						z++;
						number="";
					}
					matrix[i][j]*=a;
					z++;
				}
			}
		}
	} else
		cout<<"incorrect size! matrix can't be created"<<endl;
}
void summ_matrix(int **&matrix,int &x,int &y) {
	if(matrix==nullptr) {
		cout<<"matrix is empty"<<endl;
		return;
	}
	int **matrix_sum=new int*[x];
	for(int i=0; i<x; i++)
		matrix_sum[i]=new int[y];
	cout<<"please enter matrix:"<<x<<"x"<<y<<endl;
	for(int i=0; i<x; i++)
		for(int j=0; j<y; j++)
			cin>>matrix_sum[i][j];

	for(int i=0; i<x; i++)
		for(int j=0; j<y; j++)
			matrix[i][j]=matrix[i][j]+matrix_sum[i][j];
	for(int i=0; i<x; i++) {
		for(int j=0; j<y; j++)
			cout<<setw(4)<<matrix[i][j];
		cout<<endl;
	}

}
void multiply_matrix(int **&matrix,int &x,int &y) {
	if(matrix==nullptr) {
		cout<<"matrix is empty"<<endl;
		return;
	}
	string matrix_size;
	int x_m=0;
	int y_m=0;
	cout << "please enter size matrix" << endl;
	cin>>matrix_size;
	x_m=atoi(matrix_size.c_str());
	if(matrix_size.find('x')!=string::npos)
		matrix_size.erase(0,matrix_size.find('x')+1);
	if(matrix_size.find('X')!=string::npos)
		matrix_size.erase(0,matrix_size.find('X')+1);
	y_m=atoi(matrix_size.c_str());

	if (y != x_m || y_m==0) {
		cout << "wrong size" << endl;
		return;
	} else {
		int **matrix1=new int*[x_m];
		int **matrix_m=new int*[x];
		for(int i=0; i<x; i++)
			matrix_m[i]=new int[y_m];
		for(int i=0; i<x_m; i++)
			matrix1[i]=new int[y_m];
		for(int i=0; i<x_m; i++)
			for(int j=0; j<y_m; j++)
				cin>>matrix1[i][j];
		for(int i=0; i<x; i++)
			for(int j=0; j<y_m; j++)
				matrix_m[i][j]=0;
		for (int i = 0; i < x; i++)
			for (int j = 0; j < y_m; j++)
				for (int p = 0; p < y; p++)
					matrix_m[i][j] += matrix[i][p] * matrix1[p][j];
	    for(int i=0;i<x;i++)
	        delete []matrix[i];
		delete [] matrix;
		x=x;
		y=y_m;
		matrix=nullptr;
		matrix=matrix_m;
	}
}

void transpose_matrix(int **&matrix,int &x,int &y) {
	if(matrix==nullptr) {
		cout<<"matrix is empty"<<endl;
		return;
	}
	int **matrix_t=new int*[y];
	for(int i=0; i<y; i++)
		matrix_t[i]=new int[x];

	for(int i=0; i<y; i++)
		for(int j=0; j<x; j++)
			matrix_t[i][j]=matrix[j][i];
    for(int i=0;i<x;i++)
        delete []matrix[i];
	delete [] matrix;
	matrix=nullptr;
	matrix=matrix_t;
	swap(x,y);
}

void print_menu() {
	cout<<endl;
	cout<<"choise operation"<<endl;
	cout<<"1: show matrix"<<endl;
	cout<<"2: add up matrix"<<endl;
	cout<<"3: multiply matrix"<<endl;
	cout<<"4: transpose matrix"<<endl;
	cout<<"5: save the matrix to a file"<<endl;
	cout<<"6: load matrix from file"<<endl;
	cout<<"7: sort matrix"<<endl;
	cout<<"8: exit"<<endl;
	cout<<endl;
}
int main(int argc,char *argv[]) {
	int **matrix=nullptr;
	int x=0;
	int y=0;
	if(argc>=2)
		create_matrix(matrix,x,y,argc,argv);
	int choice_exit;
	while(1) {
		int choice;
		print_menu();
		cin>>choice;
		switch(choice) {
			case 1:
				show_matrix(matrix,x,y);
				break;
			case 2:
				summ_matrix(matrix,x,y);
				break;
			case 3:
				multiply_matrix(matrix,x,y);
				break;
			case 4:
				transpose_matrix(matrix,x,y);
				break;
			case 8:
				return 0;
		}
	}
	return 0;
}
