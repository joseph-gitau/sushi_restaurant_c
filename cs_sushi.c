// Program name
//
// This program was written by [your name] (z5555555)
// on [date]
//
// TODO: Description of program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Additional libraries here

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define TRUE 1
#define FALSE 0

#define MAX_STRING_LENGTH 100
#define EMPTY_CUSTOMER "EMPTY"

#define COMMAND_ADD_TABLE 'a'
#define COMMAND_ADD_CUSTOMER 'c'
// print all tables
#define COMMAND_PRINT_TABLES 'p'
// add plate to sushi train
#define COMMAND_ADD_PLATE 'r'
// print train 't'
#define COMMAND_PRINT_TRAIN 't'
// order plate 'o'
#define COMMAND_ADD_ORDER 'o'
// calculate bill 'b'
#define COMMAND_CALCULATE_BILL 'b'
// close restautant 'q'
#define COMMAND_CLOSE_RESTAURANT 'q'
// reverse train 's'
#define COMMAND_REVERSE_TRAIN 's'

// TODO: you may choose to add additional #defines here.

// Provided Enums

// the numerical value is the cost of that plate color
enum plate_colour
{
    RED = 3,
    GREEN = 4,
    BLUE = 5,
    PURPLE = 6,
    ORANGE = 7
};

enum sushi_type
{
    VEGETARIAN,
    SEAFOOD,
    CHICKEN,
    TEMPURA
};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided structs
struct table
{
    char customer[MAX_STRING_LENGTH];
    struct plate *orders;
    struct table *next;
};

struct plate
{
    char roll_name[MAX_STRING_LENGTH];
    enum plate_colour colour;
    enum sushi_type type;
    struct plate *next;
};

struct restaurant
{
    struct table *tables;
    struct plate *plates;
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Helper Functions
void print_restaurant(struct restaurant *restaurant);
int scanf_command(char *command);
void interpret_line(
    char buffer[MAX_STRING_LENGTH], char name[MAX_STRING_LENGTH],
    enum plate_colour *colour, enum sushi_type *type);

void interpret_order(
    char buffer[MAX_STRING_LENGTH], char customer[MAX_STRING_LENGTH],
    char roll[MAX_STRING_LENGTH]);

enum plate_colour string_to_colour(char colour[MAX_STRING_LENGTH]);
enum sushi_type string_to_type(char type[MAX_STRING_LENGTH]);
void remove_newline(char input[MAX_STRING_LENGTH]);
char color_to_char(enum plate_colour colour);
void to_type(char types[MAX_STRING_LENGTH], enum sushi_type type);
void to_colour(char cols[MAX_STRING_LENGTH], enum plate_colour colour);

// TODO: Your function prototypes here

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    // a pointer to the restaurant struct
    struct restaurant *sushi_restaurant;

    printf("Welcome to CSE Sushi Restaurant!\n");
    // Your code here!
    // STAGE 1.1
    // initalize the "sushi_restaurant" struct defined above!
    sushi_restaurant = malloc(sizeof(struct restaurant));
    sushi_restaurant->tables = NULL;
    sushi_restaurant->plates = NULL;
    // Then, call the provided print_restaurant function to print the restaurant
    print_restaurant(sushi_restaurant);

    printf("Enter command: ");
    // STAGE 1.2
    // Create your command loop here!
    // You will need to use the provided scanf_command function to read in the
    // command.
    // You will also need to use the provided interpret_line function to read in
    // the line.
    // You will need to use the provided print_restaurant function to print the
    // restaurant
    // after each command.
    char command;
    char buffer[MAX_STRING_LENGTH];
    char name[MAX_STRING_LENGTH];
    enum plate_colour colour;
    enum sushi_type type;
    while (scanf_command(&command) == TRUE)
    {
        if (command == COMMAND_ADD_TABLE)
        {
            // ask table name
            printf("Enter table name: ");
            fgets(buffer, MAX_STRING_LENGTH, stdin);
            remove_newline(buffer);
            strcpy(name, buffer);
            // add table
            struct table *new_table = malloc(sizeof(struct table));
            strcpy(new_table->customer, name);
            new_table->orders = NULL;
            new_table->next = sushi_restaurant->tables;
            sushi_restaurant->tables = new_table;
        }
        else if (command == COMMAND_ADD_CUSTOMER)
        {
            // ask for customer name
            printf("Enter customer name: ");
            fgets(name, MAX_STRING_LENGTH, stdin);
            remove_newline(name);
            // ask for order
            printf("Enter order: ");
            fgets(buffer, MAX_STRING_LENGTH, stdin);
            remove_newline(buffer);
            // add order
            struct plate *new_plate = malloc(sizeof(struct plate));
            strcpy(new_plate->roll_name, buffer);
            new_plate->colour = colour;
            new_plate->type = type;
            new_plate->next = sushi_restaurant->plates;
            sushi_restaurant->plates = new_plate;
            // add customer
            struct table *new_table = malloc(sizeof(struct table));
            strcpy(new_table->customer, name);
            new_table->orders = new_plate;
            new_table->next = sushi_restaurant->tables;
            sushi_restaurant->tables = new_table;
        }
        else if (command == COMMAND_PRINT_TABLES)
        {
            // print tables
            print_restaurant(sushi_restaurant);
        }
        // add plates using COMMAND_ADD_PLATE
        else if (command == COMMAND_ADD_PLATE)
        {
            // place the users input into the `remaining_input` string
            char remaining_input[MAX_STRING_LENGTH];
            fgets(remaining_input, MAX_STRING_LENGTH, stdin);

            char dish_name[MAX_STRING_LENGTH];
            enum plate_colour colour;
            enum sushi_type type;
            // parse the users input into the variables above
            interpret_line(remaining_input, dish_name, &colour, &type);
            // add to plates
            struct plate *new_plate = malloc(sizeof(struct plate));
            strcpy(new_plate->roll_name, dish_name);
            new_plate->colour = colour;
            new_plate->type = type;
            new_plate->next = sushi_restaurant->plates;
            sushi_restaurant->plates = new_plate;
        }
        // print train using COMMAND_PRINT_TRAIN
        else if (command == COMMAND_PRINT_TRAIN)
        {
            // print train
            struct plate *current_plate = sushi_restaurant->plates;
            while (current_plate != NULL)
            {
                printf("%s %c %d \n", current_plate->roll_name,
                       color_to_char(current_plate->colour),
                       current_plate->type);
                current_plate = current_plate->next;
            }
            // if there are no plates, print "EMPTY"
            if (sushi_restaurant->plates == NULL)
            {
                printf("EMPTY :( \n");
            }
        }
        // add order using COMMAND_ADD_ORDER
        else if (command == COMMAND_ADD_ORDER)
        {
            // place the users input into the `remaining_input` string
            char remaining_input[MAX_STRING_LENGTH];
            fgets(remaining_input, MAX_STRING_LENGTH, stdin);

            char customer_name[MAX_STRING_LENGTH];
            char dish_name[MAX_STRING_LENGTH];
            // parse the users input into the variables above
            interpret_order(remaining_input, customer_name, dish_name);
            // check if customer exists
            struct table *current_table = sushi_restaurant->tables;
            while (current_table != NULL)
            {
                if (strcmp(current_table->customer, customer_name) == 0)
                {
                    // add order to customer
                    // check if plate exists
                    struct plate *current_plate = sushi_restaurant->plates;
                    while (current_plate != NULL)
                    {
                        if (strcmp(current_plate->roll_name, dish_name) == 0)
                        {
                            // add plate to customer
                            struct plate *new_plate = malloc(sizeof(struct plate));
                            strcpy(new_plate->roll_name, dish_name);
                            new_plate->colour = current_plate->colour;
                            new_plate->type = current_plate->type;
                            new_plate->next = current_table->orders;
                            current_table->orders = new_plate;
                            break;
                        }
                        current_plate = current_plate->next;
                    }
                    break;
                    // if plate does not exist, print "NO SUCH PLATE" and ask user to add plate
                    if (current_plate == NULL)
                    {
                        printf("NO SUCH PLATE :( \n");
                        printf("Enter command to add plate: ");
                    }
                }
                current_table = current_table->next;
            }
            // if customer does not exist, print "Customer does not exist"
            if (current_table == NULL)
            {
                printf("Customer does not exist :( \n");
            }
        }
        // calculate bill using COMMAND_CALCULATE_BILL
        else if (command == COMMAND_CALCULATE_BILL)
        {
            //    prompt for customer name
            printf("Enter customer name: ");
            fgets(name, MAX_STRING_LENGTH, stdin);
            remove_newline(name);
            //    check if customer exists
            struct table *current_table = sushi_restaurant->tables;
            while (current_table != NULL)
            {
                if (strcmp(current_table->customer, name) == 0)
                {
                    // calculate bill
                    int bill = 0;
                    struct plate *current_plate = current_table->orders;
                    while (current_plate != NULL)
                    {
                        bill += current_plate->type;
                        current_plate = current_plate->next;
                    }
                    printf("Bill for %s is %d \n", name, bill);
                    break;
                }
                current_table = current_table->next;
            }

            // if customer does not exist, print "Customer does not exist"
            if (current_table == NULL)
            {
                printf("Customer does not exist :( \n");
            }
        }
        // close restaurant using COMMAND_CLOSE_RESTAURANT/ clear all memory
        else if (command == COMMAND_CLOSE_RESTAURANT)
        {
            // free all memory
            struct table *current_table = sushi_restaurant->tables;
            while (current_table != NULL)
            {
                struct table *next_table = current_table->next;
                struct plate *current_plate = current_table->orders;
                while (current_plate != NULL)
                {
                    struct plate *next_plate = current_plate->next;
                    free(current_plate);
                    current_plate = next_plate;
                }
                free(current_table);
                current_table = next_table;
            }
            struct plate *current_plate = sushi_restaurant->plates;
            while (current_plate != NULL)
            {
                struct plate *next_plate = current_plate->next;
                free(current_plate);
                current_plate = next_plate;
            }
            free(sushi_restaurant);
            break;
        }
        // reverse train using COMMAND_REVERSE_TRAIN
        else if (command == COMMAND_REVERSE_TRAIN)
        {
            // reverse train
            struct plate *current_plate = sushi_restaurant->plates;
            struct plate *previous_plate = NULL;
            struct plate *next_plate = NULL;
            while (current_plate != NULL)
            {
                next_plate = current_plate->next;
                current_plate->next = previous_plate;
                previous_plate = current_plate;
                current_plate = next_plate;
            }
            sushi_restaurant->plates = previous_plate;
        }
        // if command is not valid, print "Invalid command"
        else
        {
            printf("Invalid command :( \n");
        }

        // nw
        printf("Enter command: ");
    }

    printf("Thank you for dining with CSE Sushi Restaurant!\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: you may need to add additional functions here

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
/////////////////////////// (DO NOT EDIT BELOW HERE) ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided Function - DO NOT EDIT
void print_restaurant(struct restaurant *restaurant)
{
    int i;
    if (restaurant == NULL)
    {
        printf("ERROR: No restaurant!\n");
        return;
    };

    printf("CSE Sushi Restaurant\n");
    struct table *table = restaurant->tables;
    int table_num = 0;
    while (table != NULL)
    {
        int table_length = 5;
        if (strcmp(table->customer, EMPTY_CUSTOMER) != 0)
        {
            table_length = strlen(table->customer) + 4;
        }
        // calculate number of plates
        int number_of_plates = 0;
        struct plate *curr = table->orders;
        while (curr != NULL)
        {
            number_of_plates++;
            curr = curr->next;
        }

        printf(" ");
        for (i = 0; i < table_length; i++)
        {
            printf("_");
        }
        printf(" ");

        // print out the top row
        for (i = 0; i < number_of_plates; i++)
        {
            printf("    _____ ");
        }

        printf("\n");

        // print out the data
        int occupied = FALSE;
        if (strcmp(table->customer, "EMPTY") != 0)
        {
            occupied = TRUE;
        }
        if (occupied)
        {
            printf("|  %s  |-->", table->customer);
        }
        else
        {
            printf("|  %d  |-->", table_num);
        }

        // print out the plates
        struct plate *order = table->orders;
        while (order != NULL)
        {
            printf("|  %c  |-->", color_to_char(order->colour));

            order = order->next;
        }

        printf("\n");
        printf(".");
        for (i = 0; i < table_length; i++)
        {
            printf("-");
        }
        printf(".");
        // print out the top row
        for (i = 0; i < number_of_plates; i++)
        {
            printf("   |-----|");
        }

        printf("\n");
        table = table->next;
        table_num++;
    }
}

// Helper Function
// scans a single character from the user and returns the value of scanf;
//
// Parameters:
//  - command: a pointer to a character to store the command
//
// Returns:
//  - the value that scanf returns (this will be 1 if it was successfully read);
//
// Usage:
//  ```
//  char command;
//  while (scanf_command(&command) == 1) {
//  ```
// this function does some wizadry that you **do not need to understand**
// for you to ensure that subsequent
// calls to fgets works correctlly.
int scanf_command(char *command)
{
    // read in character + newline + null-terminator
    char buffer[3];
    char *result = fgets(buffer, 3, stdin);
    if (result == NULL)
    {
        return EOF;
    }

    // a non a-z character probably means not a char
    if (buffer[0] < 'a' || buffer[0] > 'z')
    {
        return EOF;
    }

    // set the character
    *command = buffer[0];
    return 1;
}

// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the format: [string] [enum1] [enum2]
// This function will extract the relevant values into the given variables.
// The function will also remove any newline characters.
//
// For example, if given: "salmon red seafood"
// The function will copy the string:
//     "salmon" into the 'name' array
// And will copy the enums:
//     red      into the colour pointer
//     seafood  into the type pointer
//
// If you are interested, `strtok` is a function which takes a string,
// and splits it up into before and after a "token" (the second argument)
//
// Parameters:
//     buffer  = A null terminated string in the following format
//               [string] [enum1] [enum2]
//     name    = An array for the [string] to be copied into
//     colour  = A pointer to where [enum1] should be stored
//     type    = A pointer to where [enum2] should be stored
// Returns:
//     None
void interpret_line(
    char buffer[MAX_STRING_LENGTH], char name[MAX_STRING_LENGTH],
    enum plate_colour *colour, enum sushi_type *type)
{
    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as string (sushi roll name)
    char *name_str = strtok(buffer, " ");
    if (name_str != NULL)
    {
        // Extract word
        strcpy(name, name_str);
    }

    // Extract value 2 as str, then enum
    char *colour_str = strtok(NULL, " ");
    if (colour_str != NULL)
    {
        *colour = string_to_colour(colour_str);
    }

    // Extract value 2 as str, then enum
    char *type_str = strtok(NULL, " ");
    if (type_str != NULL)
    {
        *type = string_to_type(type_str);
    }

    if (name_str == NULL || colour_str == NULL || type_str == NULL)
    {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }
}

// Helper Function
// You DO NOT NEED TO UNDERSTAND THIS FUNCTION, and will not need to change it.
//
// Given a raw string in the following foramt: [string1] [string2]
// This function will extract the relevant values into the given variables.
// The function will also remove any newline characters.
//
// For example, if given: "Gab salmon"
// The function will put:
//     "Gab" into the 'customer' array
//     "salmon" into the 'roll' array
//
// Parameters:
//     buffer   = A null terminated string in the following format
//                [string1] [string2]
//     customer = An array for the [string1] to be copied into
//     roll     = An array for the [string2] to be copied into
// Returns:
//     None
void interpret_order(
    char buffer[MAX_STRING_LENGTH], char customer[MAX_STRING_LENGTH],
    char roll[MAX_STRING_LENGTH])
{
    // Remove extra newline
    remove_newline(buffer);

    // Extract value 1 as string
    char *customer_str = strtok(buffer, " ");
    if (customer_str != NULL)
    {
        strcpy(customer, customer_str);
    }

    // Extract value 2 as string
    char *roll_str = strtok(NULL, " ");
    if (roll_str != NULL)
    {
        strcpy(roll, roll_str);
    }

    if (customer_str == NULL || roll_str == NULL)
    {
        // If any of these are null, there were not enough words.
        printf("Could not properly interpret line: %s.\n", buffer);
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will remove and first newline it sees.
// The newline character wil be replaced with a null terminator ('\0')
void remove_newline(char input[MAX_STRING_LENGTH])
{
    // Find the newline or end of string
    int index = 0;
    while (input[index] != '\n' && input[index] != '\0')
    {
        index++;
    }
    // Goto the last position in the array and replace with '\0'
    // Note: will have no effect if already at null terminator
    input[index] = '\0';
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum plate_colour will return the first letter of enum, or ? if the
// value is not one of the plate_colour values.
// Parameters:
//     colour  = enum plate_colour for a plate
// Returns:
//     char    = character represtning the first letter of the plate colour
char color_to_char(enum plate_colour colour)
{
    if (colour == RED)
    {
        return 'r';
    }
    else if (colour == GREEN)
    {
        return 'g';
    }
    else if (colour == BLUE)
    {
        return 'b';
    }
    else if (colour == PURPLE)
    {
        return 'p';
    }
    else if (colour == ORANGE)
    {
        return 'o';
    }
    else
    {
        return '?';
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will return the corresponding enum plate_colour, or FALSE
// if the string doesn't correspond with the enums.
// Parameters:
//     colour  = string representing the corresponding enum plate_colour value
// Returns:
//     enum plate_colour
enum plate_colour string_to_colour(char colour[MAX_STRING_LENGTH])
{
    if (strcmp(colour, "red") == 0)
    {
        return RED;
    }
    else if (strcmp(colour, "green") == 0)
    {
        return GREEN;
    }
    else if (strcmp(colour, "blue") == 0)
    {
        return BLUE;
    }
    else if (strcmp(colour, "purple") == 0)
    {
        return PURPLE;
    }
    else if (strcmp(colour, "orange") == 0)
    {
        return ORANGE;
    }
    return FALSE;
}

// Helper Function
// You likely do not need to change this function.
//
// Given a raw string will return the corresponding enum sushi_type, or FALSE
// if the string doesn't correspond with the enums.
// Parameters:
//     type  = string representing the corresponding enum sushi_type value
// Returns:
//     enum sushi_type
enum sushi_type string_to_type(char type[MAX_STRING_LENGTH])
{
    if (strcmp(type, "vegetarian") == 0)
    {
        return VEGETARIAN;
    }
    else if (strcmp(type, "seafood") == 0)
    {
        return SEAFOOD;
    }
    else if (strcmp(type, "chicken") == 0)
    {
        return CHICKEN;
    }
    else if (strcmp(type, "tempura") == 0)
    {
        return TEMPURA;
    }
    return FALSE;
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum sushi_type will return the enum name as a string, or "ERROR" if
// the value was not one of the given enums.
// Parameters:
//     types  = string to store the name of the enum in
//     type   = sushi_type enum to have the name stored in types.
// Returns:
//     None
void to_type(char types[MAX_STRING_LENGTH], enum sushi_type type)
{
    if (type == VEGETARIAN)
    {
        strcpy(types, "vegetarian");
    }
    else if (type == SEAFOOD)
    {
        strcpy(types, "seafood");
    }
    else if (type == CHICKEN)
    {
        strcpy(types, "chicken");
    }
    else if (type == TEMPURA)
    {
        strcpy(types, "tempura");
    }
    else
    {
        strcpy(types, "ERROR");
    }
}

// Helper Function
// You likely do not need to change this function.
//
// Given an enum plate_colour will return the enum name as a string, or "ERROR"
// if the value was not one of the given enums.
// Parameters:
//     cols   = string to store the name of the enum in
//     colour = plate_colour enum to have the name stored in cols
// Returns:
//     None
void to_colour(char cols[MAX_STRING_LENGTH], enum plate_colour colour)
{
    if (colour == RED)
    {
        strcpy(cols, "red");
    }
    else if (colour == BLUE)
    {
        strcpy(cols, "blue");
    }
    else if (colour == GREEN)
    {
        strcpy(cols, "green");
    }
    else if (colour == PURPLE)
    {
        strcpy(cols, "purple");
    }
    else if (colour == ORANGE)
    {
        strcpy(cols, "orange");
    }
    else
    {
        strcpy(cols, "ERROR");
    }
}