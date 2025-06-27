#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Decimal implementation with linked list

//******************************************************/
//* TASK 1 - Define the struct for digit and decimal   */
//******************************************************/

typedef struct s_digit
{
    char data; // 0-9
    struct s_digit *next;
} *digit;

typedef struct s_decimal
{
    // e.g. -3.14 is represented as -314*10^{-2}
    // is_negative = 1, [4 (head) -> 1 -> 3], e = -2
    char is_negative; // 1 for negative, 0 for positive
    digit head;       // linked list starting from the **LOWEST** digit
    int e;            // exponent of 10
} *decimal;

//******************************************************/
//* TASK 2 - Memory allocation and free                */
//******************************************************/

// Allocate memory for a new decimal
// Note: the decimal has no digit yet, we consider it as NaN
decimal new_decimal()
{
    decimal d = (decimal)malloc(sizeof(struct s_decimal));
    d->is_negative = 0;
    d->head = NULL;
    d->e = 0;
    return d;
}

// Allocate memory for a new digit
digit new_digit(char data, digit next)
{
    digit d = (digit)malloc(sizeof(struct s_digit));
    d->data = data;
    d->next = next;
    return d;
}

// Free the memory of a linked list of digits
void free_digits(digit head)
{
    digit cur = head;
    while (cur != NULL)
    {
        digit next = cur->next;
        free(cur);
        cur = next;
    }
}

// Free the memory of a decimal
void free_decimal(decimal d)
{
    free_digits(d->head);
    free(d);
}

//******************************************************/
//* TASK 3 - Parse a string to get a decimal           */
//******************************************************/

// Parse a string to set the decimal
decimal new_decimal_by_string(char *s)
{
    decimal d = new_decimal();

    // TODO

    return d;
}

void debug_print_decimal(decimal d)
{
    printf("is_negative: %d, e: %d\n", d->is_negative, d->e);
    printf("digits: [head]");
    for (digit cur = d->head; cur != NULL; cur = cur->next)
        printf("%d->", cur->data);
    printf("NULL\n");
}

void test_task_3_parser()
{
    char *test_cases[] = {
        "123456",
        "12.3456",
        "12345.6",
        "0.123456",
        "0.00123456",
        "123456.0",
        "-123456",
        "-12.3456",
        "-12345.6",
        "-0.123456",
        "-0.00123456",
        "-123456.0",
        ".123456",
        "-.123456",
        "123456.",
        "-123456.",
        // bonus: exponential notation (optional)
        // "123456e-3",
        // "123456e3",
        // "123456e0",
        // "123456e20",
        // "123456e-10",
        // "12.3456e3",
        // "12.3456e4",
        // "12.3456e6",
        // "12.3456e-1",
        // "12.3456e-2",
        // "12.3456e-3",
        // "-123456e-3",
        // "-123456e3",
        // "-123456e0",
        // "-123456e20",
        // "-123456e-10",
        // "-12.3456e3",
        // "-12.3456e4",
        // "-12.3456e6",
        // "-12.3456e-1",
        // "-12.3456e-2",
        // "-12.3456e-3",
    };

    decimal d;

    for (int i = 0; i < sizeof(test_cases) / sizeof(char *); i++)
    {
        d = new_decimal_by_string(test_cases[i]);
        printf("\nTest parsing %s\n", test_cases[i]);
        debug_print_decimal(d);
        free_decimal(d);
    }
}

// Note: In VSCode, Press Ctrl[Command] + / to uncomment selected lines

// //******************************************************/
// //* TASK 4 - Reverse a linked list of digits           */
// //******************************************************/

// // Reverse the linked list of digits, returning the new head
// digit _reverse_digits(digit head, int *len_output)
// {
//     // TODO
// }

// void test_task_4_reverse()
// {
//     decimal d = new_decimal_by_string("-12.3456");

//     printf("Original: \n");
//     debug_print_decimal(d);
//     printf("\n");

//     int len = 0;
//     digit rev_head = _reverse_digits(d->head, &len);

//     d->head = rev_head;

//     printf("Reversed: \n");
//     debug_print_decimal(d);
//     printf("\nLength: %d\n\n", len);
// }

// //******************************************************/
// //* TASK 5 - Print a decimal out                       */
// //******************************************************/

// // Print the decimal
// void print_decimal(decimal d)
// {
//     // Handle NaN (Not a Number)
//     if (d->head == NULL)
//     {
//         printf("NaN\n");
//         return;
//     }

//     // Negative Sign
//     if (d->is_negative)
//         printf("-");

//     // Reverse the digits to print from the highest digit
//     int length = 0; // Get the length of the digits at the same time

//     // TODO

//     // -d->e >= length: the floating point is before the valid digits
//     // print the '0.' and all the leading zeros
//     if (-d->e >= length)
//     {
//         // TODO
//     }

//     // Now, print the digits
//     for (int i = 0; i < length; i++)
//     {
//         // -d->e < length && d->e < 0: the point is in the middle of the valid digits
//         // print the point when encountered.

//         // if (-d->e < length && d->e < 0 &&  ??????  )    // TODO
//         {
//             printf(".");
//         }

//         // TODO
//     }

//     // d->e >= 0: the floating point is after the valid digits
//     // print the final zeros
//     if (-d->e < length && d->e >= 0)
//     {
//         // TODO
//     }

//     // Reverse (restore) the digits

//     // TODO

//     printf("\n");
// }

// void test_task_5_print()
// {
//     decimal d;

//     char *test_cases[] = {
//         "123456",
//         "12.3456",
//         "12345.6",
//         "0.123456",
//         "0.00123456",
//         "123456.0",
//         "-123456",
//         "-12.3456",
//         "-12345.6",
//         "-0.123456",
//         "-0.00123456",
//         "-123456.0",
//         ".123456",
//         "-.123456",
//         "123456.",
//         "-123456.",
//     };

//     for (int i = 0; i < sizeof(test_cases) / sizeof(char *); i++)
//     {
//         d = new_decimal_by_string(test_cases[i]);
//         printf("Test parse then print %s: ", test_cases[i]);
//         print_decimal(d);
//         free_decimal(d);
//     }
// }

// //***********************************************************/
// //* TASK 6 - Add/subtract the abs value of two decimals     */
// //***********************************************************/

// // abs(a) + abs(b) -> abs(c)
// // Add the absolute values of a and b, store the result in c
// // Only the digits and exponent are calculated,
// // the sign should be set outside and will be neglected
// void _add_positive(decimal a, decimal b, decimal c)
// {
//     // Adding zeros to align a and b
//     int a_zeros_added = 0, b_zeros_added = 0; // Zeros should be removed after calculation
//     if (a->e > b->e)
//     {
//         for (int i = 0; i < a->e - b->e; i++)
//         {
//             // TODO

//             a_zeros_added++;
//         }
//         a->e = b->e;
//     }
//     else
//     {
//         for (int i = 0; i < b->e - a->e; i++)
//         {
//             // TODO

//             b_zeros_added++;
//         }
//         b->e = a->e;
//     }

//     // Now a->e == b->e, and a and b are aligned
//     c->e = a->e;

//     // Adding digits from the lowest digit
//     digit cur_a = a->head;
//     digit cur_b = b->head;
//     int carry = 0;
//     while (cur_a != NULL && cur_b != NULL)
//     {
//         // TODO
//     }

//     // Add the remaining higher digits
//     while (cur_a != NULL)
//     {
//         // TODO
//     }
//     while (cur_b != NULL)
//     {
//         // TODO
//     }

//     // Add the last carry
//     if (carry)
//     {
//         // TODO
//     }

//     // Remove leading zeros on higher digits
//     while (c->head->data == 0 && c->head->next != NULL)
//     {
//         // TODO
//     }
//     if (c->head->data == 0 && c->head->next == NULL)
//     {
//         // Normalize zero
//         c->e = 0;
//         c->is_negative = 0;
//     }

//     // Revert the digits
//     c->head = _reverse_digits(c->head, NULL);

//     // Remove added zeros
//     for (int i = 0; i < a_zeros_added; i++)
//     {
//         // TODO
//     }
//     for (int i = 0; i < b_zeros_added; i++)
//     {
//         // TODO
//     }
// }

// void test_task_6_add_positive()
// {    
//     char *test_a_add_b_eq_c[] = {
//         // unsigned integer add
//         "2", "3", "5", 
//         /*
//         "1", "23", "24", 
//         "12", "3", "15", 
//         "12", "34", "46", 
//         "12345678", "123", "12345801", 
//         "12345678", "12345678", "24691356", 
//         "123", "12345678", "12345801", 
//         // unsigned decimal add
//         "0.1", "0.2", "0.3", 
//         "0.1", "0.02", "0.12", 
//         "123.4", "23.45", "146.85", 
//         "12000", "0.00012", "12000.00012",
//         // zeroed add
//         "0", "0", "0", 
//         ".0", "0.", "0", 
//         "0.00", "000", "0", 
//         "-0", "0", "0", 
//         "-0", "-0", "0", 
//         */
//     };

//     decimal a, b, c;

//     for (int i = 0; i < sizeof(test_a_add_b_eq_c) / sizeof(char *); i += 3)
//     {
//         a = new_decimal_by_string(test_a_add_b_eq_c[i]);
//         b = new_decimal_by_string(test_a_add_b_eq_c[i + 1]);
//         c = new_decimal();

//         _add_positive(a, b, c);

//         printf("Test add %s + %s = %s -> ",
//                test_a_add_b_eq_c[i],
//                test_a_add_b_eq_c[i + 1],
//                test_a_add_b_eq_c[i + 2]);

//         print_decimal(c);

//         free_decimal(a);
//         free_decimal(b);
//         free_decimal(c);
//     }
// }

// // abs(a) - abs(b) -> abs(c)
// // Subtract the absolute values of b from a, store the result in c
// // Only the digits and exponent are calculated, the sign should be set outside
// // Note: Make sure abs(a) >= abs(b) !!!
// void _subtract_positive(decimal a, decimal b, decimal c)
// {
//     // TODO

//     // Hint: Modify function _add_positive
// }

// void test_task_6_subtract_positive()
// {
//     // TODO
// }

// //***********************************************************/
// //* TASK 7 - Compare the abs value of two decimals          */
// //***********************************************************/

// // Compare the absolute values of a and b
// // Return 1 if |a| > |b|, -1 if |a| < |b|, 0 if |a| == |b|
// int _compare_abs(decimal a, decimal b)
// {
//     // TODO

//     // Hints:
//     // - Reverse the digits to compare from the highest digit
//     // - Get the length of the digits at the same time
//     // - Remove leading zeros on higher digits (if any)
//     // - Decide which decimal has higher digits -> return
//     // - If a and b are aligned on the highest digit -> Compare the digits one by one
//     // - If all public digits are the same -> The one with more digits is larger
//     // - Don't forget to restore the digits before returning at any return point !
// }

// void test_task_7_compare_abs()
// {
//     // TODO
// }

// //***********************************************************/
// //* TASK 8 - Add/subtract two decimals                      */
// //***********************************************************/

// decimal add(decimal a, decimal b)
// {
//     decimal c = new_decimal();

//     if (a->head == NULL || b->head == NULL)
//     {
//         printf("Warning: trying to add NaN\n");
//         return c;
//     }

//     // TODO

//     // Hints:
//     // - Discuss the sign of a and b
//     // - Call _add_positive or _subtract_positive based on the sign of a and b
//     // - (You might need to compare their abs value before calling calc functions)

//     return c;
// }

// decimal sub(decimal a, decimal b)
// {
//     decimal c = new_decimal();

//     if (a->head == NULL || b->head == NULL)
//     {
//         printf("Warning: trying to add NaN\n");
//         return c;
//     }

//     // TODO

//     // Hint: same as add

//     return c;
// }

// void test_task_8_add_sub()
// {
//     char *test_a_add_b_eq_c[] = {
//         // unsigned integer add
//         "2", "3", "5", 
//         /*
//         "1", "23", "24", 
//         "12", "3", "15", 
//         "12", "34", "46", 
//         "12345678", "123", "12345801", 
//         "12345678", "12345678", "24691356", 
//         "123", "12345678", "12345801", 
//         // signed integer add (negative)
//         "-12345678", "-123", "-12345801", 
//         "-12345678", "-12345678", "-24691356", 
//         "-123", "-12345678", "-12345801",
//         // signed integer add (with different signs)
//         "12345678", "-123", "12345555",  
//         "-123", "12345678", "12345555",  
//         "-12345678", "123", "-12345555",  
//         "123", "-12345678", "-12345555",  
//         "12345678", "-12345678", "0", 
//          "-12345678", "12345678", "0",
//         // unsigned decimal add
//         "0.1", "0.2", "0.3", 
//         "0.1", "0.02", "0.12", 
//         "123.4", "23.45", "146.85", 
//         "12000", "0.00012", "12000.00012",
//         // signed decimal add
//         "-0.00012", "12000", "11999.99988",
//         // zeroed add
//         "0", "0", "0", 
//         ".0", "0.", "0", 
//         "0.00", "000", "0", 
//         "-0", "0", "0", 
//         "-0", "-0", "0", 
//         "123", "-123", "0", 
//         "-1.23", "1.23", "0", 
//         "123000", "-123000", "0",
//         */
//     };

//     for (int i = 0; i < sizeof(test_a_add_b_eq_c) / sizeof(char *); i += 3)
//     {
//         // TODO: Verification
//         // a + b = c, b + a = c
//         // c - a = b, c - b = a
//     }
// }

//***********************************************************/
//* MAIN FUNCTION                                           */  
//***********************************************************/

int main()
{
    // test_task_3_parser();

    // test_task_4_reverse();

    // test_task_5_print();

    // test_task_6_add_positive();

    // test_task_6_subtract_positive();

    // test_task_7_compare_abs();
    
    // test_task_8_add_sub();

    return 0;
}