#include "DecisionTree.h"
double DecisionTree::Entropy(BinaryTree<info> a){
	//set of current leabels
	std::set<double> uniqueElems;
	//vector of pair(label,no aparition)
	std::vector<std::pair<double,int>> fr;
	unsigned int setSize=uniqueElems.size();
	double entropy=0;
	//calculate how much of each label is in the current node
	for(auto el:a.Element().labels){
		uniqueElems.insert(el);
		if(uniqueElems.size()==setSize)
		{
			auto it= uniqueElems.find(el);
			int i=0;
			for (auto els:fr){
				if (els.first==*it){
					fr[i]=std::make_pair(els.first,els.second+1);
				}
				i++;
			}
		}
		else{
			setSize++;
			fr.push_back(std::make_pair((double)(el),1));
		}
	}
	//calulate the entropy
	for(auto el:fr){
		double probability = double(el.second)/a.Element().labels.size();
		entropy -= ((probability*log2(probability))*probability);
	}
	return entropy;
}

//modify the tree in current put in the left node and right node the remaining labels and items and if it's only one type then set it's type to leaf 
//and set the prediction value
void DecisionTree::applyQuestion(){
	int i=0;
	// the default info struct values
	info basic;
	for(auto el:curent.Element().remaining_items)
		basic.remaining_items.push_back(std::vector<double>());
	BinaryTree<info> st(basic),dr(basic);
	//separate the remaining items and labels in left and right node
	for(auto el: curent.Element().remaining_items[curent.Element().featureAsked]){
			if(curent.Element().question(el)){
				for(int k=0;k<curent.Element().remaining_items.size();k++)
				st.Element().remaining_items[k].push_back(curent.Element().remaining_items[k][i]);
				st.Element().labels.push_back(curent.Element().labels[i]);
			}
			else{
				for(int k=0;k<curent.Element().remaining_items.size();k++)
				dr.Element().remaining_items[k].push_back(curent.Element().remaining_items[k][i]);
				dr.Element().labels.push_back(curent.Element().labels[i]);
			}
			i++;
		}
		std::set<double> t;
		//set the type to node or leaf for left child
		for(auto el:st.Element().labels){
			t.insert(el);
		}
		if(t.size()==1){
			st.Element().tip="leaf";
			auto it=t.begin();
			double val=*it;
			st.Element().prediction=val;
		}
		else
			st.Element().tip="nod";
		t.clear();

		//set the type to node or leaf for right child
		for(auto el:dr.Element().labels){
			t.insert(el);
		}
		if(t.size()==1){
			dr.Element().tip="leaf";
			double val=*(t.begin());
			dr.Element().prediction=val;
		}
		else
			dr.Element().tip="nod";
		curent.adaugaSubDrept(dr);
		curent.adaugaSubStang(st);

}


BinaryTree<info> DecisionTree::tryQuestion(std::function<bool(double)> question){
	int i=0;
	info basic;
	BinaryTree<info> a{curent};
	for(auto el:a.Element().remaining_items)
		basic.remaining_items.push_back(std::vector<double>());
	BinaryTree<info> st(basic),dr(basic);
	for(auto el: a.Element().remaining_items[curent.Element().featureAsked]){
			if(question(el)){
				for(int k=0;k<a.Element().remaining_items.size();k++)
				st.Element().remaining_items[k].push_back(a.Element().remaining_items[k][i]);
				st.Element().labels.push_back(a.Element().labels[i]);
			}
			else{
				for(int k=0;k<a.Element().remaining_items.size();k++)
				dr.Element().remaining_items[k].push_back(a.Element().remaining_items[k][i]);
				dr.Element().labels.push_back(a.Element().labels[i]);
			}
			i++;
		}
		std::set<double> t;
		for(auto el:st.Element().labels){
			t.insert(el);
		}
		if(t.size()==1){
			st.Element().tip="leaf";
			auto it=t.begin();
			double val=*it;
			st.Element().prediction=val;
		}
		else
			st.Element().tip="nod";
		t.clear();
		for(auto el:dr.Element().labels){
			t.insert(el);
		}
		if(t.size()==1){
			dr.Element().tip="leaf";
			double val=*(t.begin());
			dr.Element().prediction=val;
		}
		else dr.Element().tip="nod";
		a.adaugaSubDrept(dr);
		a.adaugaSubStang(st);
		return a;
}


void DecisionTree::bestQuestion(){
	auto curentEntropy=Entropy(curent);
	std::function<bool(double)> corectquestion;
	std::set<double> uniqueL; // unique labels
	std::vector<std::string> intrebari; //intrebarile puse
	std::vector<std::pair<std::function<bool(double)>,std::pair<double,int>>> QuestionsGain;

	//put all unique labels into uniqueL
	for(auto label:curent.Element().labels){
		uniqueL.insert(label);
	}
	std::set<double> type;
	//for each label
	for(auto label:uniqueL){
		int i=0;
		//for each item
		for(auto item:curent.Element().remaining_items){
			int j=0;
			curent.Element().featureAsked=i;
			//for each feature of the items that has the curent label
			for(auto feature:curent.Element().remaining_items[i]){
				if (curent.Element().labels[j]==label){
					//insert the feature into a set
					type.insert(feature);
				}
				j++;
			}
			//gain calculate how good a question is;
			//question gain takes the curent question and the question gain
			//if for all labels of a type , the feature is the same , ask if are elements with that exact feature
			if(type.size()==1){
				auto it=type.begin();
				double condoub=*it;
				auto q=[condoub](double a){

					return a==(double)condoub;};
				intrebari.push_back("=="+std::to_string(condoub));
				auto nodes=tryQuestion(q);
				auto entropy=Entropy(nodes.stang())+Entropy(nodes.drept());
				double gain=curentEntropy-entropy;
				QuestionsGain.push_back(std::make_pair(q,std::make_pair(gain,i)));
			}
			//if for all labels of a type , there are more then 1 feature, ask if are elements are greater than the minimim value of the feature
			//or less than maximum value of the feature
			else{
				for(auto curentVal :type){

					double condoubl=curentVal;
					auto qg=[condoubl](double a){
						return a>=condoubl;};
					intrebari.push_back(">="+std::to_string(condoubl));
					auto nodes2=tryQuestion(qg);
					auto entropy2=Entropy(nodes2.stang())+Entropy(nodes2.drept());
					double gain2=curentEntropy-entropy2;
					QuestionsGain.push_back(std::make_pair(qg,std::make_pair(gain2,i)));

					double condoub2=curentVal;
					auto ql=[condoub2](double a){

						return a<=(double)condoub2;};
					intrebari.push_back("<="+std::to_string(condoub2));
					auto nodes3=tryQuestion(ql);
					auto entropy3=Entropy(nodes3.stang())+Entropy(nodes3.drept());
					double gain3=curentEntropy-entropy3;
					QuestionsGain.push_back(std::make_pair(ql,std::make_pair(gain3,i)));
				}
			}
			type.clear();
			i++;
		}

	}
	double maxGain=0;
	int poz=-1;
	int f;
	int i=0;
	//find the max gain, position of question with max gain 
	for(auto el:QuestionsGain){
		if(el.second.first>maxGain){
			poz=i;
			maxGain=el.second.first;
			f=el.second.second;
		}
		i++;
	}
	//if we find a question that has some gain we apply it
	if(poz!= -1){
		corectquestion=QuestionsGain[poz].first;
		curent.Element().featureAsked=f;
		curent.Element().question=corectquestion;
		curent.Element().intrebare=intrebari[poz];
		applyQuestion();
	}
	//no more gain, so the node is a leaf and the prediction is the biggest number of same labels remaining
	else{
		curent.Element().tip="leaf";
		int max=0;
		double elMax;
		for(auto el :uniqueL){
			int nr=0;
			for(auto label:curent.Element().labels){
				if(label==el){
					nr++;
				}
			}
			if(max<nr){
				max=nr;
				elMax=el;
			}
		}
		curent.Element().prediction=elMax;
	}
}

//train function
void DecisionTree::train(BinaryTree<info>& ab){
	if (ab.Element().tip=="leaf"){
		return;
	}
	bestQuestion();
	//find and apply the best question
	//if there is no question to ask the node will become leaf and
	//the prediction will be random from the labels that remains in node
	if (ab.Element().tip=="leaf"){
			return;
		}
	auto st=curent.stang().getRad();

	auto dr=curent.drept().getRad();
	curent.setRad(st);
	train(curent);
	curent.setRad(dr);
	train(curent);
}
void DecisionTree::fit(std::vector<std::vector<double>> features,std::vector<double> labels){
	//root initialization
	info root;
	root.remaining_items=features;
	root.labels=labels;
	tree.adaugaElement(root);
	curent.setRad(tree.getRad());
	curent.Element().tip="nod";
	//train;
	train(curent);

	curent.setRad(tree.getRad());

}
std::vector<double> DecisionTree::predict(std::vector<std::vector<double>> features){
	//predict the value
	std::vector<double> labels;
	int i=0;
	for(auto el:features[0]){
		while(curent.Element().tip!="leaf"){

			if(curent.Element().question(features[curent.Element().featureAsked][i])){
				curent.setRad(curent.stang().getRad());
			}
			else
				curent.setRad(curent.drept().getRad());
		}
		labels.push_back(curent.Element().prediction);
		curent.setRad(tree.getRad());

		i++;
	}
	return labels;
}
