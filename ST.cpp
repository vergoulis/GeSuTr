/* Copyright (C) 2019 Thanasis Vergoulis
 *
 * This file is part of GeSuTr. 
 *
 * GeSuTr is a free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GeSuTr is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Contact email: vergoulis@athenarc.gr
 */

#include "ST.h"

ST::ST()
{
	this->_st_root=NULL;
}

ST::ST(string* strs, long strs_num)
{
	this->_st_root = new STnode(NULL,0,0,strs[0].length()-1); //create root node
	this->strInsertNaive(strs, strs_num); //insert all strings in the tree one-by-one
}

ST::~ST()
{
	//Destruct an object
}

int ST::strInsertNaive(string str)
{
	cout<<"- Inserting string '"<<str<<"' to the string registry..."<<endl;
	int str_id = this->strRegister(str); //register str in the registry of strings
	cout<<"- String inserted..."<<endl;

	string suffix;

	if( this->_st_root == NULL) //empty tree - build from scratch
	{
		//Create and initialise the root node (no parent, no label)
		this->_st_root = new STnode(NULL,str_id,0,str.length()-1); 
	}

	for( long i=0; i<this->_strs[str_id].length(); i++ )
	{
		cout<<"\t - Inserting suffix '"<<this->_strs[str_id].substr(i,this->_strs[str_id].length()-i)<<"' to the tree..."<<endl; //DEBUG
		this->insertSuffix(str_id,i,this->_strs[str_id].length()-1); //insert the i-th suffix to the tree
		cout<<"\t - Suffix inserted..."<<endl;
		//this->print(); //DEBUG
	}

	//this->print(); //DEBUG
	return 0;
}

int ST::strInsertNaive(string* strs, long str_num)
{
	for(long i=0; i<str_num; i++)
		this->strInsertNaive(strs[i]);
	return 0; 
}

int ST::insertSuffix(long str_id, long suf_start, long suf_end)
{
	STnode* cur_node = this->_st_root;
	STnode* init_node = this->_st_root;
	long chars_matched; 
	string suffix = this->_strs[str_id].substr(suf_start,suf_end-suf_start+1);

	//Traverse the tree based on the suffix & add nodes where needed
	long str_len = suffix.length(); //string length
	long chars_read = 0; //read characters
	string remaining_str = suffix;
	long label_len;

	STnode* new_node;

	while(chars_read!=str_len)
	{
		remaining_str = suffix.substr(chars_read,str_len-chars_read);
		//cout<<"To traverse based on '"<<remaining_str<<"'"<<endl; //DEBUG
		chars_matched = this->traverseNodeNaive(cur_node,remaining_str);
		label_len = cur_node->getInLabelEnd()-cur_node->getInLabelStart()+1;

		//cout<<"Reached node with in label [str="<<cur_node->getRefStrId()<<", st="<<cur_node->getInLabelStart()<<", en="<<cur_node->getInLabelEnd()<<"] label size = "<<label_len<<endl; //DEBUG	
		//cout<<"--- matched: "<<chars_matched<<", str_len: "<<str_len<<", chars_read: "<<chars_read<<endl; //DEBUG

		if( chars_matched == 0 ) //no character matched - no children with proper label of incoming edge
		{	
			//cout<<"no match in the edge"<<endl; //DEBUG
			new_node = new STnode(cur_node,str_id,suf_start+chars_read+chars_matched,suf_end); //create new child 
			new_node->addOccPos(str_id,suf_start); //This is a leaf, so add its info.
			cur_node->addChild(new_node); //update parent
			break;
		}
		else if( chars_matched==label_len ) //whole edge was read
		{
			//cout<<"whole edge was read"<<endl; //DEBUG
			//cout<<"[current: "<<cur_node->getInLabelStart()<<","<<cur_node->getInLabelEnd()<<"]"<<endl; //DEBUG
			if( cur_node->isLeaf() )
			{
				cur_node->addOccPos(str_id,suf_start);
			}
		}
		else
		{	
			//cout<<"part of edge matches, chars_read="<<chars_read<<", chars_matched="<<chars_matched<<", suf_start="<<suf_start<<endl; //DEBUG
			//get details from old end-node to use them 
			STnode* end_node_children = cur_node->getChildren();
			long old_end = cur_node->getInLabelEnd();
			long old_str_id = cur_node->getRefStrId();
			OccPos* old_leaf_occs = cur_node->getOccPos(); //leaf's suffix occurrences (it will not be a leaf anymore)
			
			//change the old end-node to become the new init node's (intermediate) child
			cur_node->setInLabelEnd(cur_node->getInLabelStart()+chars_matched-1);
			cur_node->setOccPos(NULL); //not a leaf anymore
			//cout<<"[intermediate: "<<cur_node->getInLabelStart()<<","<<cur_node->getInLabelEnd()<<"]"<<endl; //DEBUG

			//create a new node to be the child of the intermediate node
			new_node = new STnode(cur_node,old_str_id,cur_node->getInLabelEnd()+1,old_end);
			new_node->setChildren(end_node_children);
			new_node->setOccPos(old_leaf_occs); //get the suffix occurrences from the old leaf
			cur_node->setChildren(new_node); //make this to be the first child
			//cout<<"[intermediate ch1: "<<new_node->getInLabelStart()<<","<<new_node->getInLabelEnd()<<"]"<<endl; //DEBUG

			//add a new node based on the rest of the str
			new_node = new STnode(cur_node,str_id,suf_start+chars_read+chars_matched,suf_end);
			new_node->addOccPos(str_id,suf_start); //add new suffix occurrence
			cur_node->addChild(new_node); //add this as an extra child
			//cout<<"[intermediate ch2: "<<new_node->getInLabelStart()<<","<<new_node->getInLabelEnd()<<"]"<<endl; //DEBUG

			break;
		}
		chars_read += chars_matched; 
	}


	return 0;
}

int ST::strRegister(string str)
{
	this->_strs.push_back(str); //save str in the registry (vector) of strings
	return (this->_strs.size()-1); //return the index of str in the registry (vector) of strings
}

int ST::strRegister(string* strs, int strs_num)
{
	//register strings one-by-one
	for(int i=0; i<strs_num; i++)
		this->strRegister(strs[i]);
	return 0;
}

void ST::printRegistry()
{
	vector<string>::iterator cur_str;
	cout<<"== String registry =="<<endl;
	cur_str = this->_strs.begin();
	while( cur_str != this->_strs.end() )
	{
		cout<<(*cur_str)<<endl;
		cur_str++;
	}
	cout<<endl;
}

long ST::traverseNodeNaive( STnode*& node, string str)
{
	long chars_matched; //number of label matching characters between str's prefix and a proper edge
	long str_len, label_len; 

	STnode* next_node = findChildByStr(node,str[0]); //find child having label of incoming edge starting with str[0]

	if( next_node == NULL ) //no such child
	{
		return 0; //no characters found
	}

	chars_matched = 1; //1st character was matching
	node = next_node; //this is the node where the selected edge ends

	str_len = str.length();
	label_len = node->getInLabelLength();

	if( str_len < label_len)
		label_len = str_len;

	while( chars_matched<label_len )
	{
		if( getLabelChar(node,chars_matched)!=str[chars_matched] )
		{
			break;
		}
		chars_matched++; //prepare to read the next character (hope that it matches)
	}

	return chars_matched;
}

STnode* ST::findChildByStr(STnode* node, char character)
{
	STnode* ch_node = node->getChildren();	//Point to the first child

	while(ch_node != NULL)
	{  
		if( this->getLabelChar(ch_node,0)== character )
			return ch_node;

		ch_node = ch_node->getRightSibling();	//Check the next sibling
	}

	return NULL; //no proper sibling found
}

void ST::findStr(string str, vector<OccPos*>& occs)
{
	STnode* cur_node = this->_st_root; 
	long read_chr = 0; //the number of read characters
	long str_len = str.length(); //the initial length of the string
	
	while( str_len !=0 ) //while there is still part of the string unread
	{
		read_chr = traverseNodeNaive( cur_node, str); //traverse to the next level

		if( read_chr == 0 ) //nowhere to go
			return; //no recorded occurrence

		str_len -= read_chr;
		str = str.substr(read_chr,str_len);
	}

	cur_node->getSubtreeOccs(occs);
}

char ST::getLabelChar(STnode* node,long char_id)
{
	return this->_strs[node->getRefStrId()][node->getInLabelStart()+char_id];
}

string ST::getLabel(STnode* node)
{
	return this->_strs[node->getRefStrId()].substr(node->getInLabelStart(),node->getInLabelLength());
}

void ST::print(void)
{
	this->printNode( this->_st_root, 0);
}

void ST::printNode( STnode* src_node, long depth)
{
	STnode* node2 = src_node->getChildren();	//Get the first of the node's children
	long d = depth;
	long start = src_node->getInLabelStart();
	long end = src_node->getInLabelEnd();
	long str_id = src_node->getRefStrId();

	//If depth == 0 (root) then print nothing, just call STprintNode for the first child.
	if (depth == 0)
    {
	    cout << "[~] (" << src_node->getOccsNum() << ")" << endl;
    }
	else
	{
		//Print the branches coming from higher nodes
		while( d>1)
		{
			cout<<"|";
			d--;
		}
		cout<<"+";
		
		cout<<this->_strs[str_id].substr(start,end-start+1)<<"[";
		src_node->printOccPos();
		cout<<"]"<< " (" << src_node->getOccsNum() << ")"<<endl;
	}
	//Recursive call for all node1's children
	while( node2!=NULL)
	{
		printNode(node2, depth+1);
		node2 = node2->getRightSibling();
	}
}

void ST::updNodeCnts()
{
	this->updNodeCnt(this->_st_root);
}

void ST::updNodeCnt( STnode* cur_node)
{
	cur_node->updateSubtreeOccNum();
	cur_node = cur_node->getChildren();
	if( cur_node!= NULL )
	{
		this->updNodeCnt(cur_node); //get first child
	}
	while( cur_node!= NULL )
	{
		cur_node = cur_node->getRightSibling(); //get rest children
		if( cur_node == NULL )
			break;
		this->updNodeCnt(cur_node);
	}
}
