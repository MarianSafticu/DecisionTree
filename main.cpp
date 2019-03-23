#include <iostream>
#include "BinaryTree.h"
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <set>
#include <math.h>
#include "DecisionTree.h"
#include <fstream>

using namespace std;


void afisare(BinaryTree<info> a){
	auto it=a.iteratorLatime();
	int i=1,p=0,nl=0,nla=0;
	string space="       ";
	while(it.valid()){
		auto x=it.element();
		if(x.tip=="nod"){
			cout<<x.intrebare<<space;
			i--;
		}
		if(x.tip=="leaf"){
			nl++;
			i--;
			cout<<"is "<<x.prediction<<space;
		}
		if(i==0){
			nla*=2;
			nla+=nl;
			i=1;
			for(int j=0;j<=p;j++){
				i*=2;
			}
			cout<<"\n";
			for(int j=0;j<nla;j++){
				i-=2;
//				cout<<space;
			}
			p++;
			nl=0;
		}
		it.next();
	}
}
int main(){
	info s,n1,n2;
	s.question=[&](double a){return a==1;};
	s.tip="nod";
	std::vector<std::vector<double>> features,f2;
	std::vector<double> labels,lab;
	features.push_back(std::vector<double>());
	features.push_back(std::vector<double>());
	features.push_back(std::vector<double>());
	features.push_back(std::vector<double>());
	f2.push_back(std::vector<double>());
	f2.push_back(std::vector<double>());
	f2.push_back(std::vector<double>());
	f2.push_back(std::vector<double>());

ifstream f("data/in.txt");
	for(int i=0;i<135;i++){
		double x;
		f>>x;
		features[0].push_back(x);
		f>>x;
		features[1].push_back(x);
		f>>x;
		features[2].push_back(x);
		f>>x;
		features[3].push_back(x);
		f>>x;
		labels.push_back(x);
	}
	for(int i=0;i<15;i++){
			double x;
			f>>x;
			f2[0].push_back(x);
			f>>x;
			f2[1].push_back(x);
			f>>x;
			f2[2].push_back(x);
			f>>x;
			f2[3].push_back(x);
			f>>x;
	}
	DecisionTree a;
	a.fit(features,labels);

	lab=a.predict(f2);
	cout<<"prediction :";
	for(auto el:lab){
		cout<<el<<"  ";
	}
/*	cout<<"\n";
	afisare(a.Tree());
	BinaryTree<int> arb(3);


	arb.adaugaSubDrept(BinaryTree<int>(2));
	arb.adaugaSubStang(BinaryTree<int>(23));
	arb.stang().adaugaSubDrept(BinaryTree<int>(12));
	arb.stang().adaugaSubStang(BinaryTree<int>(1));
	arb.drept().adaugaSubDrept(BinaryTree<int>(223));
	arb.drept().adaugaSubStang(BinaryTree<int>(7));

	auto it=arb.iteratorLatime();
	bool afis=true;
	while(it.valid()){
		auto e=it.element();
		if(e!=arb.Element())
		{
			if(afis){
				std::cout<<e<<"  ";
				afis=false;}
			else
				afis=true;
		}
		else{
			std::cout<<e<<"  ";
		}
		it.next();
	}*/

	return 0;
}
