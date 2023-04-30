# DSA-Hilbert-R-Tree
Assignment for CS F211

Group 37 -- PROJECT 2
AADEESH GARG        2021A7PS0446P
AKSHAT SHETYE       2021A7PS2426P
AMANDEEP SINGH      2021A7PS0575P
RIJUL BASSAMBOO     2021A7PS0009P
VEDANT TULI         2021A7PS0435P


To compile the code and run it, write the folowing on the unix terminal -

gcc DSA_assignment_group_37.c
./a.out

-- m , M and CurveOrder of the Hilbert Function need to be passed as a global variable.



Explanation of main function -

--  str -> Stores the name of the file that has the datapoints. 
           Ensure the datafile "*.txt" is in the same directory as your "*.c" file.

--  x_high  -> upperbound x for query rectangle in Search function
    x_low   -> lowerbound x for query rectangle in Search function
    y_high  -> upperbound y for query rectangle in Search function
    y_low   -> lowerbound y for query rectangle in Search function

-- we the declare a TREE variable 't' and readData into it.
-- then we run a pre_order_traversal on it.
-- then we execute the search function over the query rectangle stated in the variables x_low , x_high , y_low , y_high.
   and print all the points that lie in/on the rectangle.



