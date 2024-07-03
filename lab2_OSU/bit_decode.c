#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// gcc -o out bit_decode.c
// ./out
// #ifdef PROMPT
#define MAX_INPUT 1000
// input: 24 88 12 23 00 83 24 23 04 84 01 8a
// input: 01 01

// Takes a hex value and returns it rotated one left
// Example: 0001 1001 --> 0011 0010 (25 -> 50)
// Logic:
// Input: 0001 1001
// 0001 1001 << 1 = 0011 0010 (intermediate)
// If input >= 128, then intermediate ++; else return intermediate
int rotate_left(int hex_num)
{
  // printf("RLI:%d...\n", hex_num);
  int intermediate = hex_num << 1;
  if (hex_num >= 128)

  {
    // printf("RLO:%d...\n", intermediate++);
    intermediate++;
    return intermediate;
  }
  else
  {
    // printf("RLO:%d...\n", intermediate);
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
  // printf("RRI:%d...\n", hex_num);
  int intermediate = hex_num >> 1;
  if (hex_num % 2 == 0)
  {
    // printf("RRO%d...\n", intermediate);
    return intermediate;
  }
  else
  {
    // printf("RRO%d...\n", intermediate + 128);
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
  // printf("KEY:%d...\n", key);
  return key;
}

// Prompts the user to input the encrypted text message
// When '\n' is read, use putchar() to output a newline
int main()
{
  int key = create_key();
  int input_len = 0;
  printf("Enter encoded text: ");
  // printf("Your key is: %d...\n", key);
  char user_input[MAX_INPUT];
  char message[MAX_INPUT / 2];
  char this_ascii[3];
  this_ascii[2] = '\0';
  // Read in user input
  if (fgets(user_input, MAX_INPUT, stdin) != NULL)
  {
    input_len = strlen(user_input);
  }
  else
  {
    printf("Error: failed to read in user input");
    return 0;
  }
  int hex_digit = 0;
  // Process user input if we get there
  // aa aa aa aa aa \n
  // a aaa aa a
  int char_count = 0;
  int intermediate;
  int input;
  for (int i = 0; i < input_len; i++)
  {
    input = (int)user_input[i];
    if (user_input[i] == '\n')
    {
      // printf("End of the line \n");
      message[char_count] = '\0';
      // hex_digit = 0;
      break;
    }
    else if (input == 32)
    {
      continue;
    }
    else if ((input < 97 || input > 102) && (input < 48 || input > 57) && (input < 65 || input > 70))
    {
      // invalid ascii: not a-f, not 0-9, and not A-F
      printf("Invalid ascii entered, %c \n", user_input[i]);
      break;
    }
    else if (hex_digit == 1)
    {
      // valid ascii, this is the second hex digit
      this_ascii[1] = user_input[i];
      int hex_from_str = strtol(this_ascii, NULL, 16);
      // get the argument to rotate_funcs()
      if (char_count % 2 == 0)
      {
        // char 1, 3, 5, ... rotate right to decode
        intermediate = rotate_right(hex_from_str);
      }
      else
      {
        // char 0, 2, 4, ... rotate left to decode
        intermediate = rotate_left(hex_from_str);
      }
      // get final character being coded
      int final = key ^ intermediate;
      // 116
      // printf("FINAL:%d...\n", final);
      // Add that to the output
      message[char_count] = (char) final;
      // add to the char_count
      char_count++;
      hex_digit = 0;
    }
    else if (hex_digit == 0)
    {
      // valid ascii, this is the first hex digit
      this_ascii[0] = user_input[i];
      hex_digit = 1;
    }
    else
    {
      printf("What happened here? \n");
      continue; // idk how we'd possibly end up here
    }
  }
  // char* final_message = malloc(sizeof(char)*(char_count + 1));
  // memcpy(final_message, message, char_count)
  printf("Your message is:\n");
  printf("%s\n", message);
  // printf("Whith word count: %d", char_count);
  return 0;
}
// #endif