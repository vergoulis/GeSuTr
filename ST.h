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

#ifndef ST_H
#define ST_H

#include <iostream>
#include <string>
#include <vector>
#include "STnode.h"
using namespace std;

/**
 * The class represented the (generalised) suffix tree.  
 *
 * @var _strs A registry (vector) containing all strings to be inserted in the tree. 
 * @var _st_root Pointer to the root node of the tree. 
 *
 * @author Thanasis Vergoulis
 */
class ST
{
public:
	/** 
	 * The class constrcutor. It constracts the tree for a given set of strings.
	 *
	 * @param strs Array containing the strings to be included in the tree.
	 * @param strs_num The number of strings in strs. 
	 *
	 * @author Thanasis Vergoulis
	 */
	ST(string* strs, long strs_num);

	/**
	 * The class destructor. 
	 */
	~ST(); 			

	/**
	 * Inserts a given string in the suffix tree using the naive construction method (i.e., not Ukkonen's).
	 *
	 * @param str The string to be inserted. 
	 *
	 * @return It returns 0 on success.
	 *
	 * @author Thanasis Vergoulis
	 */
	int strInsertNaive(string str);

	/**
	 * Inserts one-by-one the strings contained in a given array to the tree. It calls strInsertNaive() multiple times. 
	 *
	 * @param strs The array of strings to be inserted.
	 * @param strs_num The number of strings in strs.
	 *
	 * @return It returns 0 on success. 
	 *
	 * @author Thanasis Vergoulis
	 */
	int strInsertNaive(string* strs, long strs_num);

	/**
	 * Inserts a suffix of the str_id-th string of the registry in the tree. 
	 *
	 * @param str_id The id of the string in the registry.
	 * @param suf_start The start position of the suffix in the string. 
	 * @param suf_end The end position of the suffix in the string. 
	 *
	 * @return It returns 0 on success. 
	 */
	int insertSuffix(long str_id, long suf_start, long suf_end);

	/**
	 * Inserts a given string in the registry (vector) of strings. 
	 *
	 * @param str The string to be registered.
	 *
	 * @return The index of the str in the registry (vector).
	 *
	 * @author Thanasis Vergoulis
	 */
	int strRegister(string str);

	/**
	 * Batch insertion of given strings in the registry (vector) of strings.
	 *
	 * @param strs Array of strings to be registered. 
	 * @param strs_num The number of strings to be registered.
	 *
	 * @return Zero in case of success.
	 *
	 * @author Thanasis Vergoulis
	 */
	int strRegister(string* strs, int strs_num);

	/**
	 * Prints the contents of the string registry. 
	 *
	 * @author Thanasis Vergoulis
	 */
	void printRegistry(void);

	/**
	 * Use str to go down from a given (initial) node. After the execution, param 'node' (is accessed by 
	 * reference) will  point:
	 *    (a) to the initial node (if no outgoing edge matching a prefix of str was found), or
	 *    (b) to the end-node of the matching outgoing edge (the end-node is a child of the init node)
	 *
	 * @param node Pointer to the initial node (by reference).  
	 * @param str The string used for the traversal.
	 *
	 * @return The number of matching characters between the prefix of str and the matching edge (if any).
	 *
	 * @author Thanasis Vergoulis
	 */
	long traverseNodeNaive( STnode*& node, string str);

	/**
	 * Finds a child's node having label of incoming edge starting with a given character.
	 *
	 * @param node Pointer to the initial node. 
	 * @param character The given character. 
	 *
	 * @return Pointer to the child node that has the desired property. NULL pointer otherwise.  
	 *
	 * @author Thanasis Vergoulis
	 */
	STnode* findChildByStr(STnode* node, char character);

	/**
	 * Returns a pointer to a set of positions in which a particular query string occurs (exact occurrence).
	 *
	 * @param str The query string.
	 * @param occs A vector containing all occurrences (call by reference).
	 *
	 * @author Thanasis Vergoulis 
	 */
	void findStr(string str, vector<OccPos*>& occs);

	/**
	 * Returns a particular character from the label of the incoming edge of a given node.
	 *
	 * @param node The node.
	 * @param char_id The id of the character (e.g., 1st, 2nd etc).
	 *
	 * @return The corresponding character.
	 *
	 * @author Thanasis Vergoulis
	 */
	char getLabelChar(STnode* node,long char_id);
	
	/**
	 * Returns the input edge's label of a given node.
	 *
	 * @param node The node.
	 *
	 * @return The label. 
	 *
	 * @author Thanasis Vergoulis
	 */
	string getLabel(STnode* node);

	/**
	 * Prints the suffix tree. 
	 *
	 * @author Thanasis Vergoulis
	 */
	void print();

	/**
	 * Supporting function to the print() function. It prints info about a node's children. 
	 *
	 * @param src_node The node for the children of which 
	 * @param depth The depth of the node. 
	 *
	 * @author Thanasis Vergoulis
	 */
	void printNode(STnode* src_node, long depth);

private:
	//All variables are explained in the javadoc comments of the STnode class.
	vector<string> _strs; 
	STnode* _st_root;
};

#endif /* ST_H*/
