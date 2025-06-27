#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Decimal implementation with linked list

//******************************************************/
//* TASK 1 - Define the struct for digit and decimal   */
//******************************************************/

// 定义两个结构体类型，分别存储小数（整个链表）和每位数字（结点）
typedef struct s_digit // 其实是给结构体指针起了别名 typedef struct s_digit *digit
{
    char data; // 0-9 char占的空间更少，用int太浪费了
    struct s_digit *next; // 自引用结构
} *digit;


typedef struct s_decimal
{
    // e.g. -3.14 is represented as -314*10^{-2}
    // is_negative = 1, [4 (head) -> 1 -> 3], e = -2
    char is_negative; // 1 for negative, 0 for positive
    digit head;       // linked list starting from the **LOWEST** digit 头结点:最低位(最后一位)，方便加法运算(进位)
    int e;            // exponent of 10 
} *decimal;


//******************************************************/
//* TASK 2 - Memory allocation and free                */
//******************************************************/

// Allocate memory for a new decimal
// Note: the decimal has no digit yet, we consider it as NaN
decimal new_decimal() // 创建新链表
{
    decimal d = (decimal)malloc(sizeof(struct s_decimal)); // sizeof中是结构体类型（给一个链表要空间）
    d->is_negative = 0;
    d->head = NULL;
    d->e = 0;
    return d;
}

// Allocate memory for a new digit
digit new_digit(char data, digit next) // 创建新结点，放在当前结点的前面
{
    digit d = (digit)malloc(sizeof(struct s_digit)); // sizeof中是结构体类型（给一个结点要空间）
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
        digit next = cur->next; // 先存储再释放，如果不存储直接释放，那么next指针一并释放，则永远找不到第二个结点
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
    if (s[0] == '-') d->is_negative = 1; // 解析负号
    int point_seen = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '.') point_seen = 1; // 记录小数点出现状态
        else if (s[i] >= '0' && s[i] <= '9')
        {
            d->head = new_digit(s[i] - '0', d->head); // s[i] - '0'把字符转换成数字，因为之后打印是%d，而且也方便计算
            d->e -= point_seen; // 小数点后每添加一位有效数字 指数项e减少1
        }
    }
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
digit _reverse_digits(digit head, int *len_output)
{
    // TODO
    digit prev = NULL, cur = head;
    digit next = NULL;
    *len_output = 0;
    while (cur != NULL) // 逐个结点遍历
    {
        next = cur->next; // 临时变量, 预存next指针，避免修改后信息丢失
        cur->next = prev; // 将指向下个结点的指针修改为指向上个结点
        prev = cur; // 后移至下一个结点
        cur = next;
        (*len_output)++;
    }
    return prev;
}

void test_task_4_reverse()
{
    decimal d = new_decimal_by_string("-12.3456");

    printf("Original: \n");
    debug_print_decimal(d);
    printf("\n");

    int len = 0;
    digit rev_head = _reverse_digits(d->head, &len);

    d->head = rev_head;

    printf("Reversed: \n");
    debug_print_decimal(d);
    printf("\nLength: %d\n\n", len);
}

// //******************************************************/
// //* TASK 5 - Print a decimal out                       */
// //******************************************************/

// // Print the decimal
void print_decimal(decimal d)
{
    // Handle NaN (Not a Number)
    if (d->head == NULL)
    {
        printf("NaN\n");
        return;
    }

    // Negative Sign
    if (d->is_negative)
        printf("-");
    
    // 去除无用的0
    while (d->head->data == 0 && d->head->next != NULL)
    {
        d->head = d->head->next;
        d->e++;
    }
    // Reverse the digits to print from the highest digit
    int length = 0; // Get the length of the digits at the same time

    // TODO-->Done
    d->head = _reverse_digits(d->head, &length);

    // -d->e >= length: the floating point is before the valid digits
    // print the '0.' and all the leading zeros
    if (-d->e >= length)
    {
        // TODO-->Done
        printf("0.");
        for (int i = 0; i < -d->e - length; i++)
        {
            printf("0");
        }
    }
    
    digit cur = d->head;
    // Now, print the digits
    for (int i = 0; i < length; i++)
    {
        // -d->e < length && d->e < 0: the point is in the middle of the valid digits
        // print the point when encountered.

        printf("%d", cur->data);
        cur = cur->next;
        if (-d->e < length && d->e < 0 && i == length + d->e - 1)
        {
            printf(".");
        }
        // TODO-->Done
    }

    // d->e >= 0: the floating point is after the valid digits
    // print the final zeros
    if (-d->e < length && d->e >= 0)
    {
        // TODO-->Done
        for (int j = 0; j < d->e; j++)
        {
            printf("0");
        }
    }

    // Reverse (restore) the digits

    // TODO-->Done
    d->head = _reverse_digits(d->head, &length);

    printf("\n");
}

void test_task_5_print()
{
    decimal d;

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
    };

    for (int i = 0; i < sizeof(test_cases) / sizeof(char *); i++)
    {
        d = new_decimal_by_string(test_cases[i]);
        printf("Test parse then print %s: ", test_cases[i]);
        print_decimal(d);
        free_decimal(d);
    }
}

// //***********************************************************/
// //* TASK 6 - Add/subtract the abs value of two decimals     */
// //***********************************************************/

// // abs(a) + abs(b) -> abs(c)
// // Add the absolute values of a and b, store the result in c
// // Only the digits and exponent are calculated,
// // the sign should be set outside and will be neglected
void _add_positive(decimal a, decimal b, decimal c)
{
    // Adding zeros to align a and b
    int a_zeros_added = 0, b_zeros_added = 0; // Zeros should be removed after calculation
    int a_e = a->e;
    int b_e = b->e;
    if (a->e > b->e)
    {
        for (int i = 0; i < a->e - b->e; i++)
        {
            // TODO-->Done
            a->head = new_digit(0, a->head); // 给a补零，补在最前面
            a_zeros_added++;
        }
        a->e = b->e;
    }
    else
    {
        for (int i = 0; i < b->e - a->e; i++)
        {
            // TODO-->Done
            b->head = new_digit(0, b->head); // 给b补零，补在最前面
            b_zeros_added++;
        }
        b->e = a->e;
    }
    // Now a->e == b->e, and a and b are aligned
    c->e = a->e;

    // Adding digits from the lowest digit
    digit cur_a = a->head;
    digit cur_b = b->head;
    int carry = 0; // 进位
    while (cur_a != NULL && cur_b != NULL)
    {
        // TODO-->Done
        c->head = new_digit((cur_a->data + cur_b->data + carry) % 10, c->head);
        carry = (cur_a->data + cur_b->data + carry) / 10;
        cur_a = cur_a->next;
        cur_b = cur_b->next;
    }
    // Add the remaining higher digits
    while (cur_a != NULL)
    {
        // TODO-->Done
        c->head = new_digit((cur_a->data + carry) % 10, c->head);
        carry = (cur_a->data + carry) / 10;
        cur_a = cur_a->next;
    }
    while (cur_b != NULL)
    {
        // TODO-->Done
        c->head = new_digit((cur_b->data + carry) % 10, c->head);
        carry = (cur_b->data + carry) / 10;
        cur_b = cur_b->next;
    }

    // Add the last carry
    if (carry)
    {
        // TODO-->Done
        c->head = new_digit(carry, c->head);
    }

    // Remove leading zeros on higher digits
    while (c->head->data == 0 && c->head->next != NULL)
    {
        // TODO-->Done
        c->head = c->head->next;
    }
    if (c->head->data == 0 && c->head->next == NULL)
    {
        // Normalize zero
        c->e = 0;
        c->is_negative = 0;
    }

    // Revert the digits
    int length = 0;
    c->head = _reverse_digits(c->head, &length);

    // Remove added zeros
    for (int i = 0; i < a_zeros_added; i++)
    {
        // TODO-->Done
        a->head = a->head->next;
    }
    for (int i = 0; i < b_zeros_added; i++)
    {
        // TODO-->Done
        b->head = b->head->next;
    }
    a->e = a_e;
    b->e = b_e;
}

void test_task_6_add_positive()
{
    char *test_a_add_b_eq_c[] = {
        // unsigned integer add
        "2", "3", "5", 
        "1", "23", "24", 
        "12", "3", "15", 
        "12", "34", "46", 
        "12345678", "123", "12345801", 
        "12345678", "12345678", "24691356", 
        "123", "12345678", "12345801", 
        // unsigned decimal add
        "0.1", "0.2", "0.3", 
        "0.1", "0.02", "0.12", 
        "123.4", "23.45", "146.85", 
        "12000", "0.00012", "12000.00012",
        "1.5","2.5","4",
        // zeroed add
        "0", "0", "0", 
        ".0", "0.", "0", 
        "0.00", "000", "0", 
        "-0", "0", "0", 
        "-0", "-0", "0",   
    };

    decimal a, b, c;

    for (int i = 0; i < sizeof(test_a_add_b_eq_c) / sizeof(char *); i += 3)
    {

        a = new_decimal_by_string(test_a_add_b_eq_c[i]);
        b = new_decimal_by_string(test_a_add_b_eq_c[i + 1]);
        c = new_decimal();

        _add_positive(a, b, c);

        printf("Test add %s + %s = %s -> ",
               test_a_add_b_eq_c[i],
               test_a_add_b_eq_c[i + 1],
               test_a_add_b_eq_c[i + 2]);

        print_decimal(c);

        free_decimal(a);
        free_decimal(b);
        free_decimal(c);
    }
}

// abs(a) - abs(b) -> abs(c)
// Subtract the absolute values of b from a, store the result in c
// Only the digits and exponent are calculated, the sign should be set outside
// Note: Make sure abs(a) >= abs(b) !!!
void _subtract_positive(decimal a, decimal b, decimal c)
{
    // TODO-->Done
    // Adding zeros to align a and b
    int a_zeros_added = 0, b_zeros_added = 0; // Zeros should be removed after calculation
    int a_e = a->e;
    int b_e = b->e;
    if (a->e > b->e)
    {
        for (int i = 0; i < a->e - b->e; i++)
        {
            // TODO-->Done
            a->head = new_digit(0, a->head); 
            a_zeros_added++;
        }
        a->e = b->e;
    }
    else
    {
        for (int i = 0; i < b->e - a->e; i++)
        {
            // TODO-->Done
            b->head = new_digit(0, b->head); 
            b_zeros_added++;
        }
        b->e = a->e;
    }
    // Now a->e == b->e, and a and b are aligned
    c->e = a->e;

    // Adding digits from the lowest digit
    digit cur_a = a->head;
    digit cur_b = b->head;
    int borrow = 0; // 借位

    while (cur_a != NULL && cur_b != NULL)
    {
        // TODO-->Done
        c->head = new_digit(borrow, c->head);
        int sub = cur_a->data - cur_b->data + borrow;
        if (sub < 0) borrow = -1;
        else borrow = 0;
        
        c->head->data = (sub + 10) % 10;
        cur_a = cur_a->next;
        cur_b = cur_b->next;
    }
    // Add the remaining higher digits
    while (cur_a != NULL)
    {
        // TODO-->Done
        c->head = new_digit(borrow, c->head);
        char difference = cur_a->data + borrow;
        if (difference < 0) borrow = -1; // 发生借位

        else borrow = 0; // 不需要借位
        
        c->head->data = (difference + 10) % 10;
        cur_a = cur_a->next;
    }

    // Add the last carry
    if (borrow)
    {
         // TODO-->Done
        printf("a<b, error! \n");
        return;
    }

    // Remove leading zeros on higher digits
    while (c->head->data == 0 && c->head->next != NULL)
    {
        // TODO-->Done
        c->head = c->head->next;
    }
    if (c->head->data == 0 && c->head->next == NULL)
    {
        // Normalize zero
        c->e = 0;
        c->is_negative = 0;
    }

    // Revert the digits
    int length = 0;
    c->head = _reverse_digits(c->head, &length);

    // Remove added zeros
    for (int i = 0; i < a_zeros_added; i++)
    {
        // TODO-->Done
        a->head = a->head->next;
    }
    for (int i = 0; i < b_zeros_added; i++)
    {
        // TODO-->Done
        b->head = b->head->next;
    }

    a->e = a_e;
    b->e = b_e;
}

void test_task_6_subtract_positive()
{
    // TODO
   // 案例都满足|a|>=|b|
    char *test_a_sub_b_eq_c[] = {
        // unsigned integer subtract
        "5", "3", "2",
        "24", "1", "23",
        "15", "3", "12",
        "46", "34", "12",
        "321", "319", "2",
        "12345801", "123", "12345678",
        "24691356", "12345678", "12345678",
        "12345801", "123", "12345678",
        // unsigned decimal subtract
        "0.3", "0.2", "0.1",
        "0.12", "0.1", "0.02",
        "146.85", "23.45", "123.4",
        "12000.00012", "0.00012", "12000",
        // zeroed subtract
        "0", "0", "0", 
        ".0", "0.", "0", 
        "0.00", "000", "0", 
        "-0", "0", "0", 
        "-0", "-0", "0", 
    };


    decimal a, b, c;

    for (int i = 0; i < sizeof(test_a_sub_b_eq_c) / sizeof(char *); i += 3)
    {
        a = new_decimal_by_string(test_a_sub_b_eq_c[i]);
        b = new_decimal_by_string(test_a_sub_b_eq_c[i + 1]);
        c = new_decimal();

        _subtract_positive(a, b, c);

        printf("Test subtract %s - %s = %s -> ",
               test_a_sub_b_eq_c[i],
               test_a_sub_b_eq_c[i + 1],
               test_a_sub_b_eq_c[i + 2]);

        print_decimal(c);

        free_decimal(a);
        free_decimal(b);
        free_decimal(c);
    }
}

// //***********************************************************/
// //* TASK 7 - Compare the abs value of two decimals          */
// //***********************************************************/

// Compare the absolute values of a and b
// Return 1 if |a| > |b|, -1 if |a| < |b|, 0 if |a| == |b|
int _compare_abs(decimal a, decimal b)
{
    // TODO-->Done

    // Hints:
    // - Reverse the digits to compare from the highest digit
    // - Get the length of the digits at the same time
    // - Remove leading zeros on higher digits (if any)
    // - Decide which decimal has higher digits -> return
    // - If a and b are aligned on the highest digit -> Compare the digits one by one
    // - If all public digits are the same -> The one with more digits is larger
    // - Don't forget to restore the digits before returning at any return point !

    
    int len_a = 0;
    int len_b = 0;
    // 反转链表，从高位开始比较
    a->head = _reverse_digits(a->head, &len_a);
    b->head = _reverse_digits(b->head, &len_b);
    digit cur_a = a->head;
    digit cur_b = b->head;
    int is_zero_a = 0;
    int is_zero_b = 0;
    
    while (cur_a->data == 0)
    {
        if (cur_a->next == NULL)
        {
            is_zero_a = 1;
            break;
        }
        cur_a = cur_a->next;
        len_a--;
    }
    while (cur_b->data == 0)
    {
        if (cur_b->next == NULL)
        {
            is_zero_b = 1;
            break;
        }
        cur_b = cur_b->next;
        len_b--;
    }

        if (is_zero_a || is_zero_b)
    {
        a->head = _reverse_digits(a->head, &len_a);
        b->head = _reverse_digits(b->head, &len_b);
        if (is_zero_a == 1 && is_zero_b != 1) return -1;
        
        else if (is_zero_b == 1 && is_zero_a != 1) return 1;
        
        else return 0;
        
    }

     // 比较 len_a + a->e 和 len_b + b->e
    int effective_a = len_a + a->e;  
    int effective_b = len_b + b->e;

    if (effective_a > effective_b) {
        // a 的有效位数和指数更大
        a->head = _reverse_digits(a->head, &len_a);
        b->head = _reverse_digits(b->head, &len_b);
        return 1;  
    }
    else if (effective_a < effective_b) {
        a->head = _reverse_digits(a->head, &len_a);
        b->head = _reverse_digits(b->head, &len_b);
        return -1;  
    }

    // 逐位比较
        cur_a = a->head;
    cur_b = b->head;
    while (cur_a != NULL && cur_b != NULL) {
        if (cur_a->data == cur_b->data) {
            cur_a = cur_a->next;
            cur_b = cur_b->next;
        }
        else{
            a->head = _reverse_digits(a->head, &len_a);
            b->head = _reverse_digits(b->head, &len_b);
            return cur_a->data > cur_b->data ? 1 : -1;
        }
    }
    
     // 如果整数部分相同，但有一个数的最低位有效数字未消耗完，表示该数更大
    if (cur_a != NULL)
    {
        // a 有更多有效数字
        a->head = _reverse_digits(a->head, &len_a);
        b->head = _reverse_digits(b->head, &len_b);
        return 1;
    }
    else if (cur_b != NULL)
    {
        a->head = _reverse_digits(a->head, &len_a);
        b->head = _reverse_digits(b->head, &len_b);
        return -1;
    }
    // 如果所有有效数字都相同，则两数相等
    a->head = _reverse_digits(a->head, &len_a);
    b->head = _reverse_digits(b->head, &len_b);
    return 0;
}

void test_task_7_compare_abs()
{
    // TODO-->Done
    char *test_a_b_abs[][3] = {
        {"123", "123", "0"},
        {"123", "124", "-1"},
        {"124", "123", "1"},
        {"123.45", "123.45", "0"},
        {"123.45", "123.46", "-1"},
        {"123.46", "123.45", "1"},
        {"0.123", "0.123", "0"},
        {"0.123", "0.124", "-1"},
        {"0.124", "0.123", "1"},
        {"123", "0.123", "1"},
        {"0.123", "123", "-1"},
        {"0.0", "0", "0"},
        {"0", "0.0", "0"},
        {"0.00","000","0"},
        {"-0","0","0",},
        {".0","0.","0",},
        {"12000.00012","12000","1"},
        {"0.12","0.1","1"}
    };

    for (int i = 0; i < sizeof(test_a_b_abs) / sizeof(test_a_b_abs[0]); i++)
    {
        decimal a = new_decimal_by_string(test_a_b_abs[i][0]);
        decimal b = new_decimal_by_string(test_a_b_abs[i][1]);
        int expected = atoi(test_a_b_abs[i][2]);
        int result = _compare_abs(a, b);
        printf("Compare %s and %s: expected %d, got %d\n",
               test_a_b_abs[i][0], test_a_b_abs[i][1], expected, result);
        free_decimal(a);
        free_decimal(b);
    }
}

//***********************************************************/
//* TASK 8 - Add/subtract two decimals                      */
//***********************************************************/

decimal add(decimal a, decimal b)
{
    decimal c = new_decimal();

    if (a->head == NULL || b->head == NULL)
    {
        printf("Warning: trying to add NaN\n");
        return c;
    }

   // TODO-->Done

    // Hints:
    // - Discuss the sign of a and b
    // - Call _add_positive or _subtract_positive based on the sign of a and b
    // - (You might need to compare their abs value before calling calc functions)

    if (a->is_negative == b->is_negative)
    {
        if (_compare_abs(a, b) == 0 && a->head->next == NULL && a->head->data == 0)
        {
            _add_positive(a, b, c);
            c->is_negative = 0;
        }
        else
        {
            _add_positive(a, b, c);
            if (a->is_negative == 1) c->is_negative = 1;
        }
    }
    else{
        if (_compare_abs(a, b) == 1)
        {
            _subtract_positive(a, b, c);
            if (a->is_negative == 1) c->is_negative = 1;
        }
        else if (_compare_abs(a, b) == 0)
        {
            _subtract_positive(a, b, c);
            c->is_negative = 0;
        }
        else
        {
            _subtract_positive(b, a, c);
            if (b->is_negative == 1) c->is_negative = 1;
        }
    }

    return c;
}

decimal sub(decimal a, decimal b)
{
    decimal c = new_decimal();

    if (a->head == NULL || b->head == NULL)
    {
        printf("Warning: trying to add NaN\n");
        return c;
    }

    // TODO-->Done
    // Hint: same as add
    // Determine the sign of the result
    if (a->is_negative == b->is_negative)
    {
        // Both have the same sign, subtract the smaller from the larger
        if (_compare_abs(a, b) == 1)
        {
            _subtract_positive(a, b, c);
            if (a->is_negative == 1) c->is_negative = 1;
        }
        else if(_compare_abs(a, b) == -1)
        {
            _subtract_positive(b, a, c);
            if (b->is_negative == 0) c->is_negative = 1;

        }
        else
        {
            _subtract_positive(a, b, c);
            c->is_negative = 0;
        }
    }
    else
    {
        // Different signs, add the absolute values
        _add_positive(a, b, c);
        if (a->is_negative == 1) c->is_negative = 1;
    }

    return c;
}

void test_task_8_add_sub()
{
    char *test_a_add_b_eq_c[] = {
        // unsigned integer add
        "2", "3", "5", 
        "1", "23", "24", 
        "12", "3", "15", 
        "12", "34", "46", 
        "12345678", "123", "12345801", 
        "12345678", "12345678", "24691356", 
        "123", "12345678", "12345801", 
        // signed integer add (negative)
        "-12345678", "-123", "-12345801", 
        "-12345678", "-12345678", "-24691356", 
        "-123", "-12345678", "-12345801",
        // signed integer add (with different signs)
        "12345678", "-123", "12345555",  
        "-123", "12345678", "12345555",  
        "-12345678", "123", "-12345555",  
        "123", "-12345678", "-12345555",  
        "12345678", "-12345678", "0", 
         "-12345678", "12345678", "0",
        // unsigned decimal add
        "0.1", "0.2", "0.3", 
        "0.1", "0.02", "0.12", 
        "123.4", "23.45", "146.85", 
        "12000", "0.00012", "12000.00012",
        // signed decimal add
        "-0.00012", "12000", "11999.99988",
        // zeroed add
        "0", "0", "0", 
        ".0", "0.", "0", 
        "0.00", "000", "0", 
        "-0", "0", "0", 
        "-0", "-0", "0", 
        "123", "-123", "0", 
        "-1.23", "1.23", "0", 
        "123000", "-123000", "0",
    };
    
    for (int i = 0; i < sizeof(test_a_add_b_eq_c) / sizeof(char *); i += 3)
    {
        // TODO: Verification-->Done
        // a + b = c, b + a = c
        // c - a = b, c - b = a
        decimal a = new_decimal_by_string(test_a_add_b_eq_c[i]);
        decimal b = new_decimal_by_string(test_a_add_b_eq_c[i + 1]);
        decimal expected = new_decimal_by_string(test_a_add_b_eq_c[i + 2]);

        decimal result_add = add(a, b);
        decimal result_sub_a = sub(expected, a);
        decimal result_sub_b = sub(expected, b);

        printf("Test add %s + %s = %s -> ", test_a_add_b_eq_c[i], test_a_add_b_eq_c[i + 1], test_a_add_b_eq_c[i + 2]);
        print_decimal(result_add);

        printf("Test sub %s - %s = %s -> ", test_a_add_b_eq_c[i + 2], test_a_add_b_eq_c[i], test_a_add_b_eq_c[i + 1]);
        print_decimal(result_sub_a);

        printf("Test sub %s - %s = %s -> ", test_a_add_b_eq_c[i + 2], test_a_add_b_eq_c[i + 1], test_a_add_b_eq_c[i]);
        print_decimal(result_sub_b);

        free_decimal(a);
        free_decimal(b);
        free_decimal(expected);
        free_decimal(result_add);
        free_decimal(result_sub_a);
        free_decimal(result_sub_b);
    }
}



//***********************************************************/
//* MAIN FUNCTION                                           */
//***********************************************************/

int main()
{
    test_task_3_parser();

    test_task_4_reverse();

    test_task_5_print();

    test_task_6_add_positive();

    test_task_6_subtract_positive();

    test_task_7_compare_abs();

    test_task_8_add_sub();

    return 0;
}