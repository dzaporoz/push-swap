# Push-swap. School 42 project
In this project there is a set of int values, 2 stacks and a set of instructions to manipulate both stacks.
I wrote two programs:
- the first, named **push_swap** which calculates and displays on the standard output the smallest progam using Push_swap instruction language that sorts integer arguments received;
- the second one called **checker** which takes integer arguments and reads instructions on the standard output. Once read, checker executes them and displays **OK** if integers are sorted. Otherwise, it will display **KO**.

The the following operations is allowed:
- sa : swap a - swap the first 2 elements at the top of stack a;
- sb : swap b - swap the first 2 elements at the top of stack b;
- ss : sa and sb at the same time;
- pa : push a - take the first element at the top of b and put it at the top of a;
- pb : push b - take the first element at the top of a and put it at the top of b;
- ra : rotate a - shift up all elements of stack a by 1. The first element becomes the last one;
- rb : rotate b - shift up all elements of stack b by 1. The first element becomes the last one;
- rr : ra and rb at the same time;
- rra: reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one;
- rrb: reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one;
- rrr : rra and rrb at the same time.

## Usage
Run **make** to compile programs. Then:
- run `./push_swap [numbers]` to see set of sorting instructions;
- run `./push_swap [numbers] | ./checker [the same numbers]` to see is this set correct;
- you can use environement variables: `ARG="3 4 1 5 2 0"; ./push_swap $ARG | ./checker $ARG`
- as well as randomly create a set of numbers: 
      
      ARG=`ruby -e "puts (1..50).to_a.shuffle.join(' ')"`
