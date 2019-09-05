#include<bits/stdc++.h>
using namespace std;
struct Node
{
	bool isEndOfWord;	
	Node * children[26];
};

Node * createNode()
{
	Node * trie = new Node();
	for(int i=0;i<26;i++)
		trie->children[i]=NULL;
	trie->isEndOfWord = false;
}

void insert(Node *root,string s)
{
	Node * temp = root;
	for(int i=0;i<s.length();i++)
	{
		int ind = s[i]-'a';
		if(!temp->children[ind])
		{
			temp->children[ind]=createNode();
		}
		temp = temp->children[ind];
	}
	temp->isEndOfWord = true;
}

bool search(Node *root, string s)
{
	int i;
	for(i=0;i<s.length();i++)
	{
		int ind = s[i]-'a';
		if(root->children[ind])
			root=root->children[ind];
		else break;
	}
	return (i==s.length() && root->isEndOfWord);
}

vector<string> ans;

void go(Node * root, string s)
{
	if(root==NULL)return;
	
	if(root->isEndOfWord)
		ans.push_back(s);
	
	for(int i=0;i<26;i++)
	{
		go(root->children[i],s+(char)(i+'a'));
	}
}

void findSimilar(Node *root,string s)
{
	for(int i=0;i<s.length();i++)
	{
		int ind = s[i]-'a';
		if(!root->children[ind])
		{
			return;
		}
		else
		{
			root = root->children[ind];
		}
	}
	go(root,s);
}
int main()
{
	vector<string> s{"asheesh","ash","jagadeesh","ash","aston"};
	Node * trie = createNode();
	
	
	string data;
	fstream dictionary;

	dictionary.open("dictionary.txt", fstream::in); //read dictionary file into trie tree structure
	if (dictionary.is_open())
	{	
		while (dictionary)
		{
			dictionary >> data;
			insert(trie,data);
		}
	}	
	else
	{
		std::cout << "error:  file not open." << std::endl;
		return -1;
	}
	dictionary.close();
	
	data.clear();
	cout<<"finished loading ......"<<endl;
	cout<<"enter the prefix : "<<endl;
	string st;
	getline(cin,st);
	
	findSimilar(trie,st);
	
	for(string x: ans)cout<<x<<" ";
	cout<<endl;
	return 0;
}
