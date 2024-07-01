#include <stdio.h>
// gcc -o out bit_decode.c
// ./out
// #ifdef PROMPT

// Takes a hex value and returns it rotated one left
// Example: 0001 1001 --> 0011 0010 (25 -> 50)
// Logic:
// Input: 0001 1001
// 0001 1001 << 1 = 0011 0010 (intermediate)
// If input >= 128, then intermediate ++; else return intermediate
int rotate_left(int hex_num)
{
  int intermediate = hex_num << 1;
  if (hex_num >= 128)

  {
    return intermediate++;
  }
  else
  {
    return intermediate;
  }
  return -1;
}

// Takes a hex value and returns it rotated one right
// Example: 0001 1001 --> 1000 1100 (25 -> 140)
// Logic:
// Input: 0001 1001
// 0001 1001 >> 1 = 0000 1100 (intermediate)
// if input is odd, then return intermediate + 128; else return intermediate
int rotate_right(int hex_num)
{
  int intermediate = hex_num >> 1;
  if (hex_num % 2 == 0)
  {
    return intermediate;
  }
  else
  {
    return (intermediate + 128);
  }
  return -1;
}

// Prompts the user for a 4-bit key to decrypt the data
// Read in 4 digits of the key and return the 8-bit key to the calling function
// Logic:
// Input: 1101
// 1101 OR 0000 0000 = 0000 1101
// 1101 ls 0000 OR 0000 1101
// 1101 1101
// int intermediate = bitmask | user_input
int create_key()
{
  char user_input;
  int intermediate = 0;
  printf("Enter 4-bit key: ");
  int count = 4;
  while (((user_input = getchar()) != '\n') && count)
  {
    count--;
    // Convert the ascii value to integer 1 or 0.
    user_input = user_input - '0';
    // Shift the user_input to the left by count-1
    intermediate = intermediate | (user_input << (count));
  }
  int intermediate2 = intermediate << 4;
  int key = intermediate2 | intermediate;
  return key;
}

// Prompts the user to input the encrypted text message
// When '\n' is read, use putchar() to output a newline
int main()
{
  int key = create_key();
  printf("Enter encoded text: ");
  printf("Your key is: %d...\n", key);
  int hex_num = 0;
  int count = 1;
  int scan_result;
  int intermediate;
  // 10 is the asci value for a LF
  while ((scan_result = scanf("%2x", &hex_num)) == 1)
  {
    // printf("You entered: %d... at COUNT %d!!!\n", hex_num, count);
    // if(hex_num == 10){
    //   putchar('\n');
    //   break;
    // }
    if (count % 2 == 0)
    {
      // rotated right if even (second char)
      //  so rotate left to decode
      intermediate = rotate_left(hex_num);
    }
    else
    {
      // rotated left if odd (first char)
      // so rotate right to decode
      intermediate = rotate_right(hex_num);
    }

    int final = key | intermediate;
    // printf("PUTTING:");
    putchar(final);
    // printf("HAd PUT\n");
    count++;
  }
  if (scan_result == 0)
  {
    printf("scanned 0\n");
  }
  else if (scan_result == EOF)
  {
    printf("EOF reached.\n");
  }
  else
  {
    printf("Done! \n");
  }
  return 0;
}
// #endif