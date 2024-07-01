#include <stdio.h>
// getchar(), scanf(), printf(), fprintf()
#include <stdlib.h>
// malloc(), calloc()
#include <string.h>
#define MAX_DIGITS 5
#define MAX_QUOTE_SIZE 301
#define FILE_NAME_SIZE 250

/*********** STRUCT: ****************/
struct Answers
{
  char **quotes_list;
  char **fav_quotes;
  char file_name[FILE_NAME_SIZE];
  int num_quotes;
  int num_favs;
};
/*********** FUNCTIONS: *************/
// populate quotes array

// char populate_quotes(char **quotes_list)
void clear_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
void populate_quotes(struct Answers *ans)
{
  // promptuser
  int num_quotes;
  // char num_quotes_char[MAX_DIGITS];
  printf("How many quotes do you plan on entering? (>0)\n");
  scanf("%d", &num_quotes);
  clear_buffer();
  ans->num_quotes = num_quotes;
  // Dynamically allocate memory to hold addresses of all quotes
  char **temp = malloc(num_quotes * sizeof(char *));
  char user_input[MAX_QUOTE_SIZE];
  // Prompt user to enter quotes
  for (int i = 0; i < num_quotes; i++)
  {
    printf("Please enter quote %d (>300 characters!): \n", (i + 1));
    if (fgets(user_input, sizeof(user_input), stdin) != NULL)
    {
      // printf("good!\n");
    };
    // printf("here 1\n");
    size_t size = (strlen(user_input) + 1) * sizeof(char);
    // printf("here 2\n");
    char *this_quote = malloc(size);
    // printf("here 3\n");
    memcpy(this_quote, user_input, size);
    //    printf("here 4\n");
    temp[i] = this_quote;
  }
  ans->quotes_list = temp;
  printf("here 6\n");
  // return num_quotes;
}

// void print_quotes(int print_favs, char **quotes_list, int num_quotes)
void print_quotes(int print_favs, struct Answers *ans)
{
  printf("You've entered:\n");
  if (print_favs == 0)
  {
    for (int i = 0; i < (ans->num_quotes); i++)
    {
      printf("Quote %d: %s\n", (i + 1), (ans->quotes_list)[i]);
    }
  }
  else
  {
    // print favorites
    for (int i = 0; i < (ans->num_favs); i++)
    {
      printf("Quote: %s\n", (ans->fav_quotes)[i]);
    }
  }
}

void print_asci(char *str)
{
  for (int i = 0; i <= strlen(str); i++)
  {
    printf("ASCII**********%d*********\n", str[i]);
  }
}

// int populate_favorites(char **quotes_list, char **fav_quotes)
void populate_favorites(struct Answers *ans)
{
  // char num_favs_char[MAX_DIGITS];
  int num_favs;
  printf("How many favorite quotes do want (%d >=)?\n", ans->num_quotes);
  scanf("%d", &num_favs);
  clear_buffer();
  ans->num_favs = num_favs;
  // allocate space for an array of 8 byte quote addresses
  char **temp = malloc(sizeof(char *) * num_favs);
  // populate favorite quotes
  for (int i = 0; i < num_favs; i++)
  {
    printf("Which quote do you want to enter (enter a number from 1 - %d)? \n", ans->num_quotes);
    int quote_num;
    scanf("%d", &quote_num);
    clear_buffer();
    // String includes a carraige retrun (10) and a null terminator (0)
    size_t size = (1 + strlen(ans->quotes_list[quote_num - 1])) * sizeof(char);
    temp[i] = malloc(size);
    if (temp[i] == NULL)
    {
      fprintf(stderr, "Allocation for fav quote %d failed :(\n", quote_num);
    }
    else
    {
      strncpy(temp[i], ans->quotes_list[quote_num - 1], size);
    }
  }
  ans->fav_quotes = temp;
}

int get_file_name(char *file_name)
{
  printf("Do you want to save your quotes as a file? (Enter <yes> or <no>) \n");
  char *user_input = malloc(500 * sizeof(char));
  fgets(user_input, (500 * sizeof(char)), stdin);
  if (strcmp(user_input, "yes\n") == 0)
  {
    // Save to file
    printf("Please enter a file name: \n");
    fgets(file_name, sizeof(file_name), stdin);
    //  printf("File NAME:***%s***\n", file_name);
    //    print_asci(file_name);
    // printf("WHISKEY\n");
    free(user_input);
    return 1;
  }
  else if (strcmp(user_input, "no\n") == 0)
  {
    // Do not save to file
    file_name = NULL;
    free(user_input);
    return 0;
  }
  else
  {
    // invalid input
    fprintf(stderr, "ERROR! Invalid input :( %s\n", user_input);
    file_name = NULL;
    free(user_input);
    return 0;
  }
}

void create_file(char *file_name, struct Answers *ans)
{
  FILE *fp;
  fp = fopen(file_name, "a");
  fprintf(fp, "Inspiring Quotes: \n");
  for (int i = 0; i < ans->num_quotes; i++)
  {
    fprintf(fp, "%s", (ans->quotes_list)[i]);
  }
  fprintf(fp, "My Favorites Are: \n");
  for (int i = 0; i < ans->num_favs; i++)
  {
    fprintf(fp, "%s", (ans->fav_quotes)[i]);
  }
  fclose(fp);
}

// free everything
void free_all(struct Answers *ans)
{
  printf("Freeing all variables...\n");
  for (int i = 0; i < ans->num_quotes; i++)
  {
    free(ans->quotes_list[i]);
  }
  free(ans->quotes_list);
  for (int i = 0; i < ans->num_favs; i++)
  {
    free(ans->fav_quotes[i]);
  }
  free(ans->fav_quotes);
  printf("DONE!!\n");
  free(ans);
}

int main()
{
  // string pointers
  struct Answers *answers = malloc(sizeof(struct Answers));
  char file_name[FILE_NAME_SIZE];
  // Get all quotes
  populate_quotes(answers);
  // Print all quotes
  print_quotes(0, answers);
  // Store favorites
  populate_favorites(answers);
  // Print favorites
  print_quotes(1, answers);
  if (get_file_name(file_name))
  {
    // make a file
    printf("Your file has been created... \n");
    create_file(file_name, answers);
  }
  else
  {
    // exit the program
    printf("Have a good day! :) \n");
  };
  free_all(answers);
}
