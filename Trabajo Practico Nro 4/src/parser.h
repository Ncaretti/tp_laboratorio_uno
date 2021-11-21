/*
 * parser.h
 *
 *  Created on: Nov 20, 2021
 *      Author: Seether
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee);
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee);


#endif /* SRC_PARSER_H_ */
