/**
 * @file main.c
 * @brief demonstrate SCIP with an initail solution
 * @author Koya KATO (Shimada Ayako)
 * @date 2024-06-12 10:36:00
 */

#include "scip/scip.h"
#include "scip/scipdefplugins.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/**
 * @fn int GetRandom(int min, int max)
 * @brief Get random value
 * @param (int min) the lower bound of the random value
 * @param (int max) the upper bound of the random value
 * @return min <= random value <= max
 */
int GetRandom(int min, int max){
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}


/**
 * @fn int main(void)
 * @brief Main function to demonstrate SCIP with an initail solution
 * @return 0 if the program completes successfully.
 */ 
int main(int argc, char *argv[]){
	// help
    if(argc != 3){
        printf("Usage: %s <number of items>  <limit of knapsack>\n", argv[0]);
       	exit(1);
    }
	char *endptr_num;
	char *endptr_limit;
	const long int num = strtol(argv[1], &endptr_num, 10); // number of items
	SCIP_Longint limit = strtol(argv[2], &endptr_limit, 10); // limit of knapsack

	// create the problem1 - knapsack problem
	SCIP* scip = NULL;
	SCIP_CALL(SCIPcreate(&scip));
	SCIP_CALL(SCIPincludeDefaultPlugins(scip));
	SCIP_CALL(SCIPcreateProbBasic(scip, "knapsack1"));

	// set variable
	SCIP_VAR* items[num];
	for(int i = 0; i < num; ++i){
		char varname[SCIP_MAXSTRLEN];
		snprintf(varname, SCIP_MAXSTRLEN, "item_%d", i);
		SCIP_CALL( SCIPcreateVarBasic(scip, &items[i], varname, 0.0, 1.0, 1.0, SCIP_VARTYPE_BINARY));
		SCIP_CALL(SCIPaddVar(scip, items[i]));
	}

	// set object function
	SCIP_CALL(SCIPsetObjsense(scip, SCIP_OBJSENSE_MAXIMIZE));
	SCIP_Real values[num];
	for(int i = 0; i < num; ++i){
		values[i] = GetRandom(1.0, 10.0);
	}
	for(int i = 0; i < num; ++i){
		SCIP_CALL( SCIPaddVarObj(scip, items[i], values[i]));
	}

	// // add constraints
	SCIP_CONS* cons;
	SCIP_Longint weights[num];
	for(int i = 0; i < num; ++i){
		weights[i] = GetRandom(1.0, 10.0);
	}
	SCIP_CALL( SCIPcreateConsBasicKnapsack(scip, &cons, "knapsack", num, items, weights,  limit)); 
	SCIP_CALL(SCIPaddCons(scip, cons));

	// solve the problem
	SCIP_CALL( SCIPsolve(scip) );

	// get the best solution and show the result
	SCIP_SOL* sol = SCIPgetBestSol(scip);
	if (sol != NULL)
	{
		printf("Optimal solution found:\n");
		for(int i = 0; i < num; ++i){
			SCIP_Real val = SCIPgetSolVal(scip, sol, items[i]);
			if(val == 0.0){
				// printf("items[%d] = %f\n", i, val);
			}
			// printf("items[%d] = %f\n", i, val);
		}
	}else{
		printf("No optimal solution found.\n");
	}

	// set the initial solution, solve the same problem
   	printf("second time\n");
	SCIP* scip2 = NULL;
	SCIP_CALL(SCIPcreate(&scip2));
	SCIP_CALL(SCIPincludeDefaultPlugins(scip2));
	SCIP_CALL(SCIPcreateProbBasic(scip2, "knapsack2"));


	// set variable
	SCIP_VAR* items2[num];
	for(int i = 0; i < num; ++i){
		char varname[SCIP_MAXSTRLEN];
		snprintf(varname, SCIP_MAXSTRLEN, "item_%d", i);
		SCIP_CALL( SCIPcreateVarBasic(scip2, &items2[i], varname, 0.0, 1.0, 1.0, SCIP_VARTYPE_BINARY));
		SCIP_CALL(SCIPaddVar(scip2, items2[i]));
	}

	// set object function
	SCIP_CALL(SCIPsetObjsense(scip2, SCIP_OBJSENSE_MAXIMIZE));
	for(int i = 0; i < num; ++i){
		// use the same values of problem1
		SCIP_CALL( SCIPaddVarObj(scip2, items2[i], values[i]));
	}

	// // add constraints
	SCIP_CONS* cons2;
	// use the same weights of problem1
	SCIP_CALL( SCIPcreateConsBasicKnapsack(scip2, &cons2, "knapsack", num, items2, weights, limit));
	SCIP_CALL(SCIPaddCons(scip2, cons2));

	// set initial solution
	SCIP_SOL* sol_init = NULL;
	SCIP_CALL(SCIPcreateSol(scip2, &sol_init, NULL));
	for(int i = 0; i < num; ++i){
		// set the best solution of problem1
		SCIP_Real val = SCIPgetSolVal(scip, sol, items[i]);
		SCIP_CALL(SCIPsetSolVal(scip2, sol_init, items2[i], val));
	}

	// check if the initial solution satisfies the constraints
	SCIP_Bool feasible;
	SCIP_CALL(SCIPcheckSol(scip2, sol_init, TRUE, TRUE, TRUE, TRUE, TRUE, &feasible));
	if(feasible){
		printf("The initial solution satisfies all constraints.\n");
	}else{
		printf("The initial solution do not satisfy the constratins.\n");
	}

	SCIP_Bool stored;
	// set the initial solution
	SCIP_CALL(SCIPaddSolFree(scip2, &sol_init, &stored));
	if(stored){
		printf("successfully\n");
	}

	// check the constraints
	int nconss = SCIPgetNConss(scip2);
	SCIP_CONS **conss = SCIPgetConss(scip2);

	// print constraints
	printf("nconss = %d\n", nconss); 
	// if you check the constraints, please remove comment out
	// for(int i = 0; i < nconss; ++i){
	// 	SCIPprintCons(scip2, conss[i], NULL);
	// }

	// solve the problem using the initial solution
	SCIP_CALL( SCIPsolve(scip2) );

	// get the best solution and show result
	SCIP_SOL* sol2 = SCIPgetBestSol(scip2);
	if (sol2 != NULL)
	{
		printf("Optimal solution found:\n");
		for(int i = 0; i < num; ++i){
			SCIP_Real val = SCIPgetSolVal(scip2, sol2, items[i]);
			if(val == 0.0){
				// printf("items[%d] = %f\n", i, val);
			}
			// printf("items[%d] = %f\n", i, val);
		}
	}else{
		printf("No optimal solution found.\n");
	}

	return 0;
}
