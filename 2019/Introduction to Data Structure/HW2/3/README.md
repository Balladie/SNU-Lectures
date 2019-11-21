# P3

 There are three methods of arithmetic expression.
 
 ---
- Prefix Notation : operator is written ahead of operands; e.g.) +ab
- Infix Notation : operators are used in between operands; e.g.) a+b
- Postfix Notation : operator is written after the operands; e.g.) ab+
---

For example, the expression ‘(5–6)*7’ in infix notation can be written as ‘*(-56)7’ or ‘*-567’ in prefix notation, or can be written as ‘56-7*’ in postfix notation. However, it is difficult for a computer to interpret the infix notation immediately because this notation has the disadvantage of changing the calculation order according to the operator’s priority. Therefore, the expression should be converted into prefix notation or postfix notation that can be calculated in order regardless of the operator’s priority. In this problem, we would like to implement a calculator that (1) converts the expression written in infix notation into postfix notation and (2) derives the calculation results using the Stack and Queue classes implemented above.

※ In this problem, only one-digit integer (0~9) operands are used.

(1) Converting from infix notation into postfix notation

Stack is required to convert infix notation to postfix notation. For example, when the expression ‘1+2’ is entered in infix notation, operand 1 can be output immediately, but operator + should be output after operand 2. In this case, the operator + is stored in the stack and operand 2 is printed first. Also, consider the case where the input expression is ‘5-2*3’. After 5 and 2 are printed and operator – is stored in the stack, operator * should be output first because operator * has a higher priority than operator -. Thus, for incoming operators to be output first, the LIFO structure, stack, is suitable as the data structure for operator storage.
However, operators that come later are not always output first. In the case of ‘5*2- 3’, ‘2-3’ is calculated first using the above method, so the operator has to be prioritized. Basically, open and closed brackets (‘(‘, ‘)’) have the lowest operator priority, followed by addition and subtraction, multiplication and division, and power. Since the expression in parentheses is always calculated first, if the open bracket (‘(‘) appears, add it to the stack, and if the closed bracket (‘)’) appears, pop must be performed until the open bracket (‘(‘) is found in the stack.

The following pseudo code shows the method of converting infix notation to
postfix notation.

---
exp_infix ← expression in infix notation (no space)
exp_postfix ← empty expression
stack ← empty stack
for (character ch in exp_infix) { // repeat from exp_infix[0] to exp_infix[size-1]
if (ch is an operand) { add ch to exp_postfix }
else if (stack is empty) { push operator ch to stack }
else if (top node of stack has lower priority than ch)
{ push operator ch to stack }
else if (top node of stack has higher priority than ch) {
pop operators in stack until the top node of stack has lower priority than ch and add the results to exp_postfix
push operator ch to stack }
}
pop all operators in stack and add the results to exp_postfix
return exp_postfix
---

The pseudo code above does not take parenthesis into account, so you must
consider parenthesis when implementation.

(2) Calculating using postfix notation

Since the operators are arranged in sequence as the infix notation is converted to
the postfix notation, the following calculations can be repeated until all operations
are performed using the stack.

---
1) Push it to the stack when meeting operand
2) Pop two operands from the stack when meeting operator, and push the results to the stack after performing the operation
---

e.g.)
The expression ‘(2+5)*3^(2+1)’ is converted to ‘25+321+^*’ in postfix notation,
and the process for calculating this is as follows.
 1) push(2), push(5) 
 2) pop() 2 and 5, and push(2+5)
 3) push(3), push(2), push(1)
 4) pop() 2 and 1, and push(2+1)
 5) pop() 3 and 3, and push(3^3) 
 6) pop() 7 and 27, and push(7*27)
 7) pop() the final result 189

Then, complete the Calculator class in HW2_Calculator.cpp to satisfy the following conditions by referring to the given HW2_Calculator.h.

Files to submit : HW2_Calculator.cpp

(※ Use Stack class in HW2_Stack.h and do NOT change the Stack class)
(※ In Calculator class, you CANNOT add or modify member variables but you can add member functions if necessary)
