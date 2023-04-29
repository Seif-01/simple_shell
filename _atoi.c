/**
 * calculate_sum - calculates the sum of two integers
 *
 * @a: The first integer
 * @b: The second integer
 * Return: The sum of a and b
 */
int calculate_sum(int a, int b)
{
    int sum;

    sum = a + b; /* Calculate the sum */

    return (sum); /* Return the sum */
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    int x = 5;
    int y = 10;
    int result;

    result = calculate_sum(x, y); /* Calculate the sum of x and y */

    printf("The sum of %d and %d is %d\n", x, y, result); /* Print the result */

    /* Execute a shell command to print the date */
    system("date");

    return (0);
}
