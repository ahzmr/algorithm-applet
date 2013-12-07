/**
 * 农夫过河问题的解法
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const size_t SIZE=3;
const size_t MAXTEP=8;

class Bank {
  private:
	bool isorno[SIZE];
	bool man;
	static bool arcs[SIZE][SIZE];
	static string name[SIZE];
  public:
	Bank(bool x) {
		man=0;
		for(size_t i=0; i!=SIZE; i++)
			isorno[i]=x;
	}
	bool isok() {
		for(size_t i=0; i!=SIZE; i++) {
			for(size_t j=i+1; j!=SIZE; j++)
				if(arcs[i][j]&&isorno[i]&&isorno[j])
					return false;
		}
		return true;
	}
	bool isok(size_t k) {
		bool temp;
		isorno[k]=!isorno[k];
		temp=isok();
		isorno[k]=!isorno[k];
		return temp;
	}
	void mset() {
		man=!man;
		return;
	}
	void bset(size_t i) {
		if(i>=0&&i<SIZE) isorno[i]=!isorno[i];
		return;
	}
	bool mget() {
		return man;
	}
	bool bget(size_t i) {
		if(i>=0&&i<SIZE)
			return isorno[i];
		else
			return false;
	}
	bool iszero() {
		for(size_t i=0; i!=SIZE; i++)
			if(isorno[i])
				return false;
		return true;
	}
	bool iszero(size_t i) {
		if(isorno[i]==false) return false;
		for(size_t j=0; j!=SIZE; j++) {
			if(i==j) continue;
			else if(isorno[j]==true) return false;
		}
		return true;
	}
	static string nameget(size_t i) {
		if(i>=0&&i<SIZE)
			return name[i];
		else
			return string("空");
	}
};

bool Bank::arcs[SIZE][SIZE]= {
	{0,1,0},
	{1,0,1},
	{0,1,0}
};
string Bank::name[SIZE]= {"狼","羊","菜"};

void printAn(vector< vector<int> > an) {
	string temp;
	size_t i,j,k;
	if(an.size())
		cout<<"本题的答案是："<<endl<<endl;
	else
		cout<<"本题没答案。"<<endl<<endl;
	for(i=0; i!=an.size(); i++) {
		Bank lb(1),rb(0);
		lb.mset();
		if(an.size()!=1)
			cout<<"答案"<<i+1<<"："<<endl;
		for(j=0; j!=(an[i]).size(); j++) {
			cout<<j+1<<":  "<<(Bank::nameget(an[i][j]));
			if(j%2==0)
				cout<<"->右岸   左岸:";
			else
				cout<<"->左岸   左岸:";
			lb.bset(an[i][j]);
			rb.bset(an[i][j]);
			temp="";
			for(k=0; k!=SIZE; k++) {
				if(lb.bget(k))
					cout<<(Bank::nameget(k))<<" ";
				else
					temp+="   ";
			}
			cout<<temp<<"   右岸:";
			temp="";
			for(k=0; k!=SIZE; k++) {
				if(rb.bget(k))
					cout<<(Bank::nameget(k))<<" ";
				else
					temp+="   ";
			}
			cout<<temp<<endl;
		}
		cout<<"结束"<<endl<<endl;
	}
}
void printAnGrp(vector< vector<int> > an) {
	const size_t MRow=3;
	string str[MRow];
	if(an.size())
		cout<<"本题的答案是："<<endl<<endl;
	else
		cout<<"本题没答案。"<<endl<<endl;
	for(size_t i=0; i!=an.size(); i++) {
		if(an.size()!=1)
			cout<<string(12,'*')<<"答案"<<i+1<<string(12,'*')<<endl;
		Bank bk(1);
		for(size_t k=0; k!=an[i].size()+1; k++) {
			for(size_t j=0; j!=MRow; j++) {
				string temp;
				int move;
				if(k==an[i].size())
					move=SIZE;
				else
					move=an[i][k];
				temp=Bank::nameget(move);
				str[j]+=" ";
				if(bk.bget(j)&&move!=j)
					str[j]+=Bank::nameget(j);
				else
					str[j]+="  ";
				str[j]+=" ";
				if(j==1&&!temp.empty()&&k%2==0)
					str[j]+=temp;
				else
					str[j]+="  ";
				if(j!=1)
					str[j]+="||||||";
				else if(k%2==0)
					str[j]+="->->->";
				else if(k%2==1)
					str[j]+="<-<-<-";
				if(j==1&&!temp.empty()&&k%2==1)
					str[j]+=temp;
				else
					str[j]+="  ";
				str[j]+=" ";
				if(!bk.bget(j)&&move!=j)
					str[j]+=Bank::nameget(j);
				else
					str[j]+="  ";
				str[j]+="   ";
				if(!j) {
					if(k%2==0)
						cout<<endl;
					cout<<"步骤"<<k<<":"<<string(str[j].size()-6,' ');
					if(k%2==1||k==an[i].size())
						cout<<endl;
				}
				if(k%2==1||k==an[i].size()) {
					cout<<str[j]<<endl;
					str[j]="";
				}
			}
			if(k!=an[i].size())
				bk.bset(an[i][k]);
		}
		cout<<endl;
	}
}

void solve(Bank lb,Bank rb,vector<int> answer1,vector< vector<int> > &answers,bool mnull,int n,size_t iset) {
	Bank *bank=NULL;
	++n;
	if(n) {
		answer1.push_back(iset);
		lb.mset();
		rb.mset();
	}
	if(iset!=SIZE) {
		lb.bset(iset);
		rb.bset(iset);
	}
	if(lb.iszero()) {
		answers.push_back(answer1);
		return;
	}
	if(lb.mget())
		bank=&lb;
	else
		bank=&rb;
	if(lb.isok()&&rb.isok()&&mnull) {
		mnull=false;
		if(answer1.size()>MAXTEP)
			return;
		solve(lb,rb,answer1,answers,mnull,n,SIZE);
	}
	for(size_t i=0; i!=SIZE; i++) {
		if( ( !n || i!=answer1[answer1.size()-1] )
				&& (*bank).bget(i) && (*bank).isok(i)
				&& ( !n || !rb.iszero(i) ) ) {
			mnull=true;
			if(n>MAXTEP)
				return;
			solve(lb,rb,answer1,answers,mnull,n,i);
		}
	}
	return;
}

int main() {
	Bank lb(1),rb(0);
	lb.mset();
	vector<int> answer1;
	vector< vector<int> > answers;
	solve(lb,rb,answer1,answers,false,-1,SIZE);
	printAn(answers);
	printAnGrp(answers);
	return 0;
}
