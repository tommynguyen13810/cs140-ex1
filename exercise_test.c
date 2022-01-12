/* File:     exercise_test.c
 *
 * Purpose:  Unit tests for functions defined in exercise.c 
 *
 * Compile:  gcc -g -Wall -o exercise exercise.c exercise_test.c
 * Run:      ./exercise
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minunit.h"
#include "exercise.h"


/*-------------------------------------------------------------------
 * Test exchange() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *exchange_test(void) {
  int* a;
  int* b;
  a = (int*)malloc(sizeof(int));
  b = (int*)malloc(sizeof(int));
  *a = 1;
  *b = 2;

  int ret = exchange(a,b);
  mu_assert("Error in exchange_test with non-NULL values", ret == SUCC);
  mu_assert("Error in exchange_test with result a", (*a == 2));
  mu_assert("Error in exchange_test with result b", (*b == 1));
  ret = exchange(NULL, b);
  mu_assert("Error in exchange_test with NULL value", ret == FAIL);
  ret = exchange(a, NULL);
  mu_assert("Error in exchange_test with NULL value", ret == FAIL);

  free(a);
  free(b);
  return NULL;
}  

/*-------------------------------------------------------------------
 * Test reverse_array() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *reverse_array_test(void) {
  /*Your solution*/
  int* a;
  int size = 4;
  a = (int*)calloc(size,sizeof(int));
  for(int i = 0; i < size;i++) {
    a[i] = i;
  }
  int ret = reverse_array(a, size);
  mu_assert("Error in reverse_array with valid inputs", ret == SUCC);
  for(int i = 0; i < size; i++) {
    mu_assert("Error in reverse_array with results", a[i] == size-1-i);
  }
  ret = reverse_array(NULL, size);
  mu_assert("Error in reverse_array with NULL array", ret == FAIL);
  ret = reverse_array(a, 0);
  mu_assert("Error in reverse_array with invalid size", ret == FAIL);
  return NULL;
}  

/*-------------------------------------------------------------------
 * Test match_add() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *match_add_test(void) {
  /*Your solution*/
  int arg = 0;
  char* cmd = "add1";
  int ret = match_add(cmd,arg);
  mu_assert("Error in match_add with add1",ret==1);
  cmd = "add2";
  ret = match_add(cmd,arg);
  mu_assert("Error in match_add with add2",ret==2);
  cmd = "add3";
  ret = match_add(cmd,arg);
  mu_assert("Error in match_add with add3",ret==3);
  ret = match_add(NULL,arg);
  mu_assert("Error in match_add with NULL cmd", ret==arg);

  return NULL;
}  

/*-------------------------------------------------------------------
 * Check the result of testing after calling  set_key_action() 
 * If failed, return a message string showing the failed point
 * If succesful, return NULL 
 */
char *check_key_action_return(char *expected_key,int (*expected_func)(int),  int ret, struct key_action *rec) {
  mu_assert("Error in set_key_action with del1 key", strcmp(expected_key, rec->cmd)==0);
  mu_assert("Error in set_key_action with del1 value", rec->func == expected_func);
  mu_assert("Error in set_key_action with del1 value", ret== SUCC);
  return NULL;
}

/*-------------------------------------------------------------------
 * Test set_key_action() 
 * If failed, return a message string showing the failed point
 * If succesful, return NULL 
 */
int del1(int x){
  return x-1;
}

int del2(int x){
  return x-2;
}

char * set_key_action_test(void){
  char *key="del1";
  int ret=set_key_action(NULL, key, del1);
  mu_assert("Error in set_key_action with NULL value", ret == FAIL);

  struct key_action *rec = (struct key_action *) malloc(sizeof(struct key_action));
  ret = set_key_action(rec, key, del1);
  char *msg = check_key_action_return(key, del1, ret, rec);
  free(rec);
  /*All comparisons/tests are valid*/
  return msg;
}

/*-------------------------------------------------------------------
 * Test match_action() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
struct key_action map[] = {
  { "del1", del1 },
  { "del2", del2 },
  { 0, 0 }
};

char *match_action_test(void){
  /*Your solution*/
  char* cmd = "del1";
  int arg = 2;
  int ret = match_action(map, cmd, arg);
  mu_assert("Error in match_action with del1", ret == 1);
  cmd = "del2";
  ret = match_action(map, cmd, arg);
  mu_assert("Error in match_action with del2", ret == 0);
  cmd = "del3";
  ret = match_action(map, cmd, arg);
  mu_assert("Error in match_action with nonexistent cmd", ret == 2);
  ret = match_action(map, NULL, arg);
  mu_assert("Error in match_action with NULL cmd", ret == 2);
  ret = match_action(NULL, cmd, arg);
  mu_assert("Error in match_action with NULL cmd", ret == 2);

  return NULL;
}  

/*-------------------------------------------------------------------
 * Test if the  matrix-vector multiplicatioon result is expected.
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 * m is number of rows and n is the number of columns
 */
char*  test_vect(double y[], int m, int n){
  int i;
  double expected= n*(n-1)/2;
  for (i = 0; i < m; i++){
#ifdef DEBUG1
    printf("Expected %f actual %f in mat_vect_mult\n", expected, y[i]); 
#endif
    mu_assert("Error in mat_vect_mult, one mismatch", y[i] ==expected); 
  }
  return NULL;
}

/*-------------------------------------------------------------------
 * Test matrix vector multiplciation 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char* mat_vect_mult_test1(int m, int n) {
  int i,j;
  char *msg;
  double *A = malloc(m*n*sizeof(double));
  double *x = malloc(n*sizeof(double));
  double *y = malloc(m*sizeof(double));
  for (j = 0; j < n; j++) {
    x[j]=j;
  }
  for (i = 0; i < m; i++) {
    y[i]=0;
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) A[i*n+j]=1;
  }

  int ret=mat_vect_mult(A, x, y, m, n);
  msg=test_vect(y, m, n);  
  free(A);
  free(x);
  free(y);

  if(msg !=NULL)
    return msg;

  if(ret!=SUCC)
    return "Error in mat_vect_mult return value";

  return NULL;
}  

/*-------------------------------------------------------------------
 * Test matrix vector multiplication.
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *mat_vect_mult_test(void) {
  return  mat_vect_mult_test1(2,4);
}  

char *mat_vect_mult_test_null(void) {
  double A=1; 
  int n=1;  
  int ret=mat_vect_mult(NULL, NULL, NULL, n, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
  ret=mat_vect_mult(&A, &A, &A, 0, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
  return  NULL;
}  

char*  test_mat(double C[], int n){
  int i;
  double expected=n;
  for (i = 0; i < n; i++){
#ifdef DEBUG1
    printf("Expected %f actual %f in mat_vect_mult\n", expected, C[i]); 
#endif
    mu_assert("Error in mat_vect_mult, one mismatch", C[i] ==expected); 
  }
  return NULL;
}

char *mat_mat_mult_test1(int n){
  int i,j;
  char *msg;
  double *A = malloc(n*n*sizeof(double));
  double *B = malloc(n*n*sizeof(double));
  double *C = malloc(n*n*sizeof(double));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      A[i*n+j]=1;
      B[i*n+j]=1;
      C[i*n+j]=0;
    }
  }

  int ret=mat_mat_mult(A, B, C, n);
  msg=test_mat(C, n);  
  free(A);
  free(B);
  free(C);

  if(msg !=NULL)
    return msg;

  if(ret!=SUCC)
    return "Error in mat_vect_mult return value";

  return NULL;
}
/*-------------------------------------------------------------------
 * Test matrix matrix multiplication 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *mat_mat_mult_test(void){
   /* Your solution*/
  return mat_mat_mult_test1(2);
}  

char *mat_mat_mult_test_null(void) {
  double A=1; 
  int n=1;  
  int ret=mat_mat_mult(NULL, NULL, NULL, n);
  mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
  ret=mat_mat_mult(&A, &A, &A, 0);
  mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
  return  NULL;
}  

/*-------------------------------------------------------------------
 * Run all tests.  Ignore returned messages.
 */
void run_all_tests(void) {
  /* Call all tests.  You can add more tests*/
  mu_run_test(exchange_test);
  mu_run_test(reverse_array_test);
  mu_run_test(match_add_test);
  mu_run_test(set_key_action_test);
  mu_run_test(match_action_test);
  mu_run_test(mat_vect_mult_test);
  mu_run_test(mat_vect_mult_test_null);
  mu_run_test(mat_mat_mult_test);
  mu_run_test(mat_mat_mult_test_null);
}

/*-------------------------------------------------------------------
 * The main entrance to run all tests.  
 * If failed, return a message string showing the first failed point
 * Print the test stats
 */
int main(int argc, char* argv[]) {
  run_all_tests();
  
  mu_print_test_summary("Summary:");  
  return 0;
}
