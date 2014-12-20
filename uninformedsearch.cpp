#include<iostream>
#include<sstream>
#include<queue>
#include<fstream>
#include<string>
#include<list>
#include<algorithm>
#include<stdlib.h>
#include<vector>

using namespace std;

typedef struct P{
	string initial_state;
	string goal_test;
	int operators;
	int numNodes;
}Problem;


typedef struct N{
	struct N* parent;
	struct N* children;
	string* state;

	int depth;
	int path_cost;

}Node;


void BreadthFirstSearch(Problem* problem, vector< vector<int> > &matrix,vector<string> &nodeList){
	
	int i=0;
	string *temp;
	Node* tempNode;
	vector<string> result;
	int resultDepth;
	vector< int > visited(problem->numNodes,0);
	vector<Node *> sortedNodes;
	list<Node *>::iterator list_iter;
	bool found = false;
	bool inserted = false;

	list<Node *> currentList;
	list<Node *> nextList;

	vector<Node *>::iterator it2;
	int cost = 0;
	string log;

	Node* node = (Node*)malloc(sizeof(Node));
	node->state = &(problem->initial_state);
	node->depth = 0;
	node->path_cost = 0;
	currentList.push_back(node);

	for(int k = 0; k<problem->numNodes; k++){
			if(nodeList[k] == *(node->state)){
				visited[k] = 1;
				break;
			}
	}

	ofstream out("output.txt");

	while(!currentList.empty()){
		
		node = currentList.front();
		currentList.pop_front();
		log = log + *(node->state);
		
		if(problem->goal_test == *(node->state)){
			
			found = true;
			resultDepth = node->depth;
			cost = node->path_cost;
			string temp;

			while(*node->state != problem->initial_state){
				result.push_back(*node->state);
				node=node->parent;
			}

			result.push_back(*node->state);
			
			string output;
			int i=0;

			for(i = resultDepth; i>0 ; i--){	
				temp = result[i];
				if(!temp.empty() && temp[temp.length() - 1] == '\n'){
					temp.erase(temp.length() - 1);
				}						
				output = output + temp + '-';
			}
			
			output = output + result[i];
			output.erase(remove(output.begin(), output.end(), '\n'), output.end());
			output.erase(remove(output.begin(), output.end(), '\r'), output.end());
			log.erase(remove(log.begin(), log.end(), '\n'), log.end());
			log.erase(remove(log.begin(), log.end(), '\r'), log.end());
			out << log;
			out << endl;
			out << output;
			out << endl;
			out << cost;
			out.close();
			break;
		}

		log = log + '-';

		for(i = 0; i<problem->numNodes; i++){
			if(nodeList[i] == *(node->state)){
				break;
			}
		}

		for(int j = 0; j < problem->numNodes; j++){
			if(matrix[i][j] != 0 && (visited[j] != 1)){

				 tempNode = (Node*)malloc(sizeof(Node));
				 temp = (string*) malloc(sizeof(nodeList[j]));
				 temp = &nodeList[j];
				 tempNode->state = temp;
				 tempNode->parent = node;
				 tempNode->depth = (node->depth) + 1;
				 tempNode->path_cost = (node->path_cost) + matrix[i][j];
				 visited[j] = 1;

				 if(nextList.empty()){
					 nextList.push_back(tempNode);
				 }
				 else{
					 list_iter = nextList.begin();
					 while(list_iter != nextList.end()){
							if(tempNode->depth == (*list_iter)->depth){
								do{
									if(inserted){
										break;
									}
									if((tempNode->state)->compare(*(*list_iter)->state) < 0){
										inserted = true;
										nextList.insert(list_iter,tempNode);
									}
									list_iter++;
								}while(list_iter != nextList.end() && tempNode->depth == (*list_iter)->depth);

								if(list_iter == nextList.end()){
									if(!inserted){
										inserted = true;
										nextList.push_back(tempNode);
									}
								}
								else{
									if(!inserted){
										inserted = true;
										nextList.insert(list_iter,tempNode);
									}
								}
								break;
							}
							list_iter++;
						}
					if(!inserted){
						nextList.push_back(tempNode);
					}
				 }
					inserted = false;
			}
		}

		if(currentList.empty()){
			currentList = nextList;
			nextList.clear();
		}
	}
		
	if(currentList.empty() && !found){
		out << "NoPathAvailable" << endl;
	}	

}

void DepthFirstSearch(Problem* problem, vector< vector<int> > &matrix,vector<string> &nodeList){

	list<Node *> currentList;
	int i=0;
	string *temp;
	Node* tempNode;
	vector<string> result;
	int resultDepth;
	vector< int > visited(problem->numNodes,0);
	vector<Node *> sortedNodes;
	list<Node *>::iterator list_iter;
	bool found = false;
	bool inserted = false;
	int cost = 0;
	Node* node = (Node*)malloc(sizeof(Node));
	node->state = &(problem->initial_state);
	node->depth = 0;
	node->path_cost = 0;
	string log;

	currentList.push_back(node);

	for(int k = 0; k<problem->numNodes; k++){
			if(nodeList[k] == *(node->state)){
				visited[k] = 1;
				break;
			}
	}

	ofstream out("output.txt");

	while(true){

		if(currentList.empty()){
			out << "NoPathAvailable" << endl;
			break;
		}

		node = currentList.front();
		currentList.pop_front();
		log = log + *(node->state);
		

		if(problem->goal_test == *(node->state)){
			
			found = true;
			resultDepth = node->depth;
			cost = node->path_cost;

			while(*node->state != problem->initial_state){
				result.push_back(*node->state);
				node=node->parent;
			}

			result.push_back(*node->state);
			
			string output;
			int i = 0;
			for(i = resultDepth; i>0 ; i--){
				output = output + result[i] + '-';
			}
			
			output = output + result[i];
			out << log;
			out << endl;
			out << output;
			out << endl;
			out << cost;
			out.close();
			break;
		}

		log = log + '-';

		for(i = 0; i<problem->numNodes; i++){
			if(nodeList[i] == *(node->state)){
				break;
			}
		}

		for(int j = 0; j < problem->numNodes; j++){
			if(matrix[i][j] != 0 && (visited[j] != 1)){

				tempNode = (Node*)malloc(sizeof(Node));
				temp = (string*) malloc(sizeof(nodeList[j]));
				temp = &nodeList[j];
				tempNode->state = temp;
				tempNode->parent = node;
				tempNode->depth = (node->depth) + 1;
				tempNode->path_cost = (node->path_cost) + matrix[i][j];

				 list_iter = currentList.begin();
					 while(list_iter != currentList.end()){
							if(tempNode->depth == (*list_iter)->depth){
								do{
									if((tempNode->state)->compare(*(*list_iter)->state) < 0){
										inserted = true;
										currentList.insert(list_iter,tempNode);
									}
									list_iter++;
								}while(list_iter != currentList.end() && tempNode->depth == (*list_iter)->depth);

								if(list_iter == currentList.end()){
									inserted = true;
									currentList.push_back(tempNode);
								}
								else{
									if(!inserted){
										inserted = true;
										currentList.insert(list_iter,tempNode);
									}
								}
								break;
							}
							list_iter++;
						}
					if(!inserted){
						currentList.push_front(tempNode);
					}

					visited[j] = 1;
					inserted = false;
			}
		}

	}
	
}

void UniformCostSearch(Problem* problem, vector< vector<int> > &matrix,vector<string> &nodeList){

	list<Node *> open;
	list<Node *> closed;
	list<Node *> children;
	string *temp;
	int i = 0;
	bool found = false;
	int resultDepth = 0;
	int cost = 0;
	vector<string> result;
	string log;

	list<Node *>::iterator list_iter;
	Node* tempNode;
	Node* child;
	bool found_open = false;
	bool found_closed = false;
	bool inserted = false;

	Node* node = (Node*)malloc(sizeof(Node));
	node->state = &(problem->initial_state);
	node->depth = 0;
	node->path_cost = 0;
	open.push_back(node);
	ofstream out("output.txt");
	while(true){

		if(open.empty()){
			out << "NoPathAvailable" << endl;
			break;
		}

		node = open.front();
		log = log + *(node->state);
		open.pop_front();


		if(problem->goal_test == *(node->state)){
			
			found = true;
			resultDepth = node->depth;
			cost = node->path_cost;

			while(*node->state != problem->initial_state){
				result.push_back(*node->state);
				node=node->parent;
			}

			result.push_back(*node->state);
			
			string output;
			int i = 0;
			for(i = resultDepth; i>0 ; i--){
				output = output + result[i] + '-';
			}
			
			output = output + result[i];
			out << log;
			out << endl;
			out << output;
			out << endl;
			out << cost;
			out.close();
			break;
		}

		log = log + '-';
		for(i = 0; i<problem->numNodes; i++){
			if(nodeList[i] == *(node->state)){
				break;
			}
		}

		for(int j = 0; j < problem->numNodes; j++){
			
			if(matrix[i][j] != 0){

				 tempNode = (Node*)malloc(sizeof(Node));
				 temp = (string*) malloc(sizeof(nodeList[j]));
				 temp = &nodeList[j];
				 tempNode->state = temp;
				 tempNode->parent = node;
				 tempNode->depth = (node->depth) + 1;
				 tempNode->path_cost = (node->path_cost) + matrix[i][j];

				 children.push_back(tempNode);
			}
	
		}

		while(!children.empty()){
			
			child = children.front();
			children.pop_front();

			if(!open.empty()){
				
				list_iter = open.begin();
				while(list_iter != open.end()){
					if(*(child->state) == *((*list_iter)->state)){
						if(child->path_cost < (*list_iter)->path_cost){
							open.erase(list_iter);
							list_iter = open.begin();
							while(list_iter != open.end()){

								while(list_iter != open.end() && child->path_cost == (*list_iter)->path_cost){
									if((child->state)->compare(*(*list_iter)->state) < 0){
										inserted = true;
										open.insert(list_iter,child);
										break;
									}
									
									list_iter++;
								}

								if(inserted || list_iter == open.end()){
									break;
								}

								if(child->path_cost < (*list_iter)->path_cost){
									open.insert(list_iter,child);
									inserted = true;
									break;
								}
								list_iter++;
							}
							if(!inserted){
								open.push_back(child);
							}
						}
						found_open = true;
					}
					if(list_iter != open.end()){
						list_iter++;
					}
				}

			}

			if(!closed.empty() && !found_open){
				list_iter = closed.begin();
				while(list_iter != closed.end()){
					if(*(child->state) == *((*list_iter)->state)){
						if(child->path_cost < (*list_iter)->path_cost){
							closed.erase(list_iter);
							list_iter = open.begin();
							while(list_iter != open.end()){

								while(list_iter != open.end() && child->path_cost == (*list_iter)->path_cost){
									if((child->state)->compare(*(*list_iter)->state) < 0){
										inserted = true;
										open.insert(list_iter,child);
										break;
									}
									
									list_iter++;
								}

								if(inserted || list_iter == open.end()){
									break;
								}

								if(child->path_cost < (*list_iter)->path_cost){
									open.insert(list_iter,child);
									inserted = true;
									break;
								}
								list_iter++;
							}
							if(!inserted){
								open.push_back(child);
							}
						}
						found_closed = true;
					}
					list_iter++;
				}
			}

			if(!found_open && !found_closed){
				list_iter = open.begin();
				while(list_iter != open.end()){

					while(list_iter != open.end() && child->path_cost == (*list_iter)->path_cost){
						if((child->state)->compare(*(*list_iter)->state) < 0){
							inserted = true;
							open.insert(list_iter,child);
							break;
						}
						list_iter++;
					}

					if(inserted || list_iter == open.end()){
						break;
					}

					if(child->path_cost < (*list_iter)->path_cost){
						open.insert(list_iter,child);
						inserted = true;
						break;
					}
					list_iter++;
				}
				
				if(!inserted){
					open.push_back(child);
				}
			}
			found_open = false;
			found_closed = false;
			inserted = false;
		}
			closed.push_back(node);
	}
	
}


int main(){
	string line;
	string numNodes;
	string operators;
	string nodes[5];
	string buffer;
	string temp;
	ifstream myFile("input.txt");

	Problem problem;
	queue<Node> myQueue;

	getline(myFile,operators);
	getline(myFile,problem.initial_state);
	getline(myFile,problem.goal_test);
	getline(myFile,numNodes);

	istringstream nn(numNodes);
	nn >> problem.numNodes;

	istringstream op(operators);
	op >> problem.operators;

	vector<string> arrNodes;

	for(int i=0;i<problem.numNodes;i++){
		getline(myFile,buffer);
		
		arrNodes.push_back(buffer);
	}

	vector< vector<int> > mat(problem.numNodes);

	for(int i=0;i<problem.numNodes; i++){
		getline(myFile,buffer);
		istringstream temp(buffer);
		int c;
		while(temp >> c){
			mat[i].push_back(c);	
		}
	}

	if(problem.operators == 1){
		BreadthFirstSearch(&problem,mat,arrNodes);
	
	}
	
	if(problem.operators == 2){
		DepthFirstSearch(&problem,mat,arrNodes);
	}

	if(problem.operators == 3){
		UniformCostSearch(&problem,mat,arrNodes);
	}

	while(myFile.good()){
		getline(myFile,line);
	}
	
	
	return 0;
}
