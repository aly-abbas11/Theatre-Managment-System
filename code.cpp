
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

const int row = 15;
const int col = 15;
string person_name;
bool seats[row][col];
bool movie_seats[row][col];
bool play_seats[row][col];
bool concert_seats[row][col];

// Structure to hold selected details
struct show_details
{
    string name;
    string date;
    string time;
    string category;
    double price;
    int tickets;
    // int tickets_buy;
    double total_price;
    bool is_movie;
    bool is_play;
    bool is_concert;
    double loyalty_points;
    double snack_price;
    int premium_count = 0;
};

// Function prototypes
void clearScreen();
void info();
void display();
void choices();
void initialize_seats(bool seats[row][col]);
void display_seats(bool seats[row][col]);
void book_seats(bool seats[row][col], show_details &show_details);
void choice_menu(show_details &show_details);
void purchase_snacks(show_details &show_details);
void recipt(show_details &show_details);

// Function to clear the screen
void clearScreen()
{
    system("cls");
}

void info()
{
    string cnic;
    cout << setw(90) << "=-=-=-=-=-=-=-=-=--=-=-=-=-=--=-=--=-=-=-=-=--=-=" << endl;
    cout << setw(90) << setw(70) << "USER LOGIN" << endl;
    cout << setw(90) << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << endl;
    do
    {
        cout << setw(60) << "Name : ";
        getline(cin, person_name);
        transform(person_name.begin(), person_name.end(), person_name.begin(), ::toupper);
        if (person_name.length() < 3)
        {
            cout << setw(62) << "Invalid Input" << endl;
        }

    } while (person_name.length() < 3);

    cout << endl;
    do
    {
        cout << setw(70) << "CNIC (xxxxxxxx) :";
        cin >> cnic;
        if (cnic.length() < 13)
        {
            cout << setw(62) << "Invalid Input" << endl;
        }

    } while (cnic.length() < 13);
}

// Function to display the title
void display()
{
    cout << endl;
    cout << setw(100) << "-----------------------------------------------------------------------" << endl;
    cout << setw(100) << "-                                                                     -" << endl;
    cout << setw(100) << "-               WELCOME TO THEATRE MANAGEMENT SYSTEM                  -" << endl;
    cout << setw(100) << "-                                                                     -" << endl;
    cout << setw(100) << "-----------------------------------------------------------------------" << endl;
}

// Function to display choices
void choices()
{
    cout << setw(90) << "- - - - - - - - - - - - - - - - - - - -  - - - - -" << endl;
    cout << setw(90) << "- What Do You Want to See?                       -" << endl;
    cout << setw(90) << "- - - - - - -  - - - - - - - - - - - - - - - - - -" << endl;
    cout << setw(90) << "-  A. MOVIE                                      -" << endl;
    cout << setw(90) << endl;
    cout << setw(90) << "-  B. PLAYS                                      -" << endl;
    cout << endl;
    cout << setw(90) << "- C. CONCERT                                     -" << endl;
    cout << endl;
    cout << setw(90) << "- - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}

// Function to initialize all seats to true (available)
void initialize_seats(bool seats[row][col])
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            seats[i][j] = true;
        }
    }
}

// Function to display seat arrangement
void display_seats(bool seats[row][col])
{
    cout << "=-=--=-=-=-=--=-=-=-=-=-=--=-=SCREEN=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << endl;
    cout << "     ";
    for (int i = 0; i < col; i++)
    {
        cout << setw(5) << i << "";
    }
    cout << endl;

    for (int i = 0; i < row; i++)
    {
        cout << static_cast<char>(i + 'A') << "    ";
        for (int j = 0; j < col; ++j)
        {
            cout << (seats[i][j] ? "-    " : "x    ");
        }
        cout << endl;
    }
    cout << endl;
}

void book_seats(bool seats[row][col], show_details &show_details)
{
    cout << "Select Your " << show_details.tickets << " Seats in Theatre Seating Hall" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "P. Premium Seat (Rows A-C)   Increment of 5 Dollars " << endl;
    cout << "S. Standard Seat             Price remains same" << endl;
    cout << endl;
    display_seats(seats);

    for (int i = 0; i < show_details.tickets; i++)
    {
        char seat_choice;
        char row_char;
        int col_no;
        cout << "Which Ticket You Wanna Book Premium or Standard (P/S) for Seat  " << i + 1 << " : ";
        cin >> seat_choice;
        seat_choice = toupper(seat_choice);
        while (seat_choice != 'P' && seat_choice != 'S')
        {
            cout << "Please Select Valid Seat Type . Try Again" << endl;
            cout << "Which Ticket You Wanna Book Premium or Standard (P/S) for Seat " << i + 1 << " : ";
            cin >> seat_choice;
            seat_choice = toupper(seat_choice);
        }
        cout << "Entre Your Row No (A-O) for Seat " << i + 1 << " : ";
        cin >> row_char;
        row_char = toupper(row_char);
        while (row_char < 'A' && row_char > 'O')
        {
            cout << "Please Select Valid Row.Try Again. " << endl;
            cout << "Entre  Row No (A-O) for Seat " << i + 1 << " : ";
            cin >> row_char;
            row_char = toupper(row_char);
        }
        cout << "Entre  Column No (0-14) for Seat " << i + 1 << " : ";
        cin >> col_no;
        row_char = toupper(row_char);
        while (col_no < 0 && col_no > 14)
        {
            cout << "Please Select Valid Column.Try Again." << endl;
            cout << "Entre Your Column No (A-O) for Seat " << i + 1 << " : ";
            cin >> col_no;
        }

        int row_no = row_char - 'A'; // Assuming 'A' is the first row

        // Check if the row and column are within the valid range
        if ((row_no >= 0 && row_no < row) && (col_no >= 0 && col_no < col))
        {
            // Check seat type and validity
            if (toupper(seat_choice) == 'P' && row_no >= 0 && row_no <= 2)
            {
                // Premium seat logic
                if (seats[row_no][col_no])
                {
                    seats[row_no][col_no] = false;
                    cout << "Premium Seat (" << row_char << ", " << col_no << ") booked successfully!" << endl;
                    show_details.total_price += 5;
                    show_details.premium_count++;
                }
                else
                {
                    cout << "Premium Seat (" << row_char << ", " << col_no << ") is already booked" << endl;
                    i--; // Retry the current ticket
                }
            }
            else if (toupper(seat_choice) == 'S' && row_no > 2)
            {
                // Standard seat logic
                if (seats[row_no][col_no])
                {
                    seats[row_no][col_no] = false;
                    cout << "Standard Seat (" << row_char << ", " << col_no << ") booked successfully!" << endl;
                    // Update price or count for standard seats if needed
                }
                else
                {
                    cout << "Standard Seat (" << row_char << ", " << col_no << ") is already booked" << endl;
                    i--; // Retry the current ticket
                }
            }
            else
            {
                cout << "Invalid seat choice.Select Seat According to Your Seat Type." << endl;
                i--; // Retry the current ticket
            }
        }
        else
        {
            cout << "Invalid seat. Try again." << endl;
            i--; // Retry the current ticket
        }
    }
}

// Function to handle movie selection menu
void choice_menu(show_details &show_details)
{
    // char again_asking;
    char genre_choice;
    const int n = 5;
    string fantasy_movies[n] = {"LOOKIE", "OPEN HEIMER", "BARBIE", "INCEPTION", "BATMAN"};
    string action_movies[n] = {"SUPERMAN", "TERMINATOR", "FAST & FURIOUS", "KUNGFU KING", "THE LAST MAN"};
    string sad_movies[n] = {"TITANIC", "PIECES OF A WOMAN", "LION", "A WALK TO REMEMBER", "ME BEFORE YOU"};
    string romantic_movies[n] = {"BIN ROYE", "LOVER", "ARMAAN", "ASIDE", "PRESTIGE"};
    string animated_movies[n] = {"KUNGFU PANDA", "BIG HERO 6", "FROZEN", "BEN 10", "TEKKEN"};
    string thrilled_movies[n] = {"WAR Z", "AATLAS", "ESCAPE ROOM", "DEMON", "VERONICA"};
    string dates[n] = {"6-23-24", "7-23-24", "8-23-24", "9-23-24", "10-23-24"};
    string times[n] = {"9:00PM TO 11:00PM", "11:00PM TO 12:00PM", "12:00PM TO 2:00PM", "2:00PM TO 6:00PM", "5:00PM TO 8:00PM"};
    int movie_prices[n] = {10, 7, 9, 11, 7};
    string selected_movies[n];
    string comedy_play[n] = {"NOISE OFF", "THE OLD COUPLE", "A MID SUMMER", "ONE MAN TWO GUVNORS", "NO WEALTH"};
    string tragedy_play[n] = {"LAST BYE", "HAMLET", "OEDIPUS REX", "DEATH OF SALESMAN", "MACBETH"};
    string romantic_play[n] = {"ROMEO AND JULIET", "PRIDE AND PREJUDICE", "AS YOU LIKE IT", "A DOLLS HOUSE", "PYGMALION"};
    string melodrama_play[n] = {"THE OCTOROON", "EAST LYNE", "UNCLE TOM'S", "DRUNKARD", "SWEENY TOOD"};
    string motivational_play[n] = {"OUR TOWN", "THE COLOR PURPLE", "MIRACLE WORKER", "RAISIN IN SUN", "VERONICA"};
    string play_dates[n] = {"6-23-24", "7-23-24", "8-23-24", "9-23-24", "10-23-24"};
    string play_times[n] = {"9:00AM TO 10:00AM", "11:00AM TO 12:00AM", "12:00AM TO 1:00AM", "1:00AM TO 2:00AM", "2:00AM TO 3:00AM"};
    int play_prices[n] = {5, 5, 8, 10, 6};
    string selected_plays[n];

    string concert[n] = {"LOVELY", "FADED", "ALL FALLS DOWN", "SPECTRE", "DIAMOND"};
    string concert_dates[n] = {"6-23-24", "7-23-24", "8-23-24", "9-23-24", "10-23-24"};
    string concert_times[n] = {"5:00AM TO 7:00AM", "8:00AM TO 10:00AM", "10:00AM TO 11:00AM", "12:00AM TO 1:00AM", "2:00AM TO 3:00AM"};
    int concert_prices[n] = {15, 7, 8, 10, 6};
    string selected_concerts[n];
    string choice;
    cout << "Enter Your Choice: ";
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
    while (choice != "A" && choice != "B" && choice != "C")
    {
        cout << "Please Choose a Valid Option" << endl;
        cin.clear(); // Clear any error flags that may be set
        cin.ignore();
        cout << "Enter Your Choice: ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
    }

    if (choice == "A")
    {

        show_details.is_movie = true;
        show_details.is_play = false;
        show_details.is_concert = false;
        do
        {
            clearScreen();
            cout << "Cool! You Wanna See Movies." << endl;
            cout << endl;
            cout << "We Have these Genres:" << endl;
            cout << endl;
            cout << "1.FANTASY" << endl;
            cout << endl;
            cout << "2.ACTION" << endl;
            cout << endl;
            cout << "3.SAD" << endl;
            cout << endl;
            cout << "4.ROMANTIC" << endl;
            cout << endl;
            cout << "5.ANIMATED" << endl;
            cout << endl;
            cout << "6.THRILLED" << endl;
            cout << endl;

            cout << "Which Genre Movie you Wanna See? Enter Below: ";
            cin >> show_details.category;

            while (show_details.category != "1" && show_details.category != "2" && show_details.category != "3" && show_details.category != "4" && show_details.category != "5" && show_details.category != "6")
            {
                cout << "Please Select a Valid Option !!!!" << endl;
                cout << endl;
                cout << "Which Genre Movie you Wanna See? Enter Below: ";
                cin >> show_details.category;
            }

            if (show_details.category == "1")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_movies[i] = fantasy_movies[i];
                }
                show_details.category = "Fanatsy";
            }
            else if (show_details.category == "2")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_movies[i] = action_movies[i];
                }
                show_details.category = "Action";
            }
            else if (show_details.category == "3")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_movies[i] = sad_movies[i];
                }
                show_details.category = "Sad ";
            }
            else if (show_details.category == "4")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_movies[i] = romantic_movies[i];
                }
                show_details.category = "Romantic";
            }
            else if (show_details.category == "5")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_movies[i] = animated_movies[i];
                }
                show_details.category = "Animated";
            }
            else if (show_details.category == "6")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_movies[i] = thrilled_movies[i];
                }
                show_details.category = "Thrilled";
            }
            else
            {
                cout << "This Genre Movie is not available" << endl;
            }

            clearScreen();
            cout << left;
            cout << setw(5) << "No" << setw(30) << "MOVIE" << setw(20) << "GENRE" << setw(15) << "DATE" << setw(20) << "TIMINGS" << setw(10) << "PRICE" << endl;
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < n; i++)
            {
                cout << setw(5) << (i + 1) << setw(30) << selected_movies[i] << setw(20) << show_details.category << setw(15) << dates[i] << setw(20) << times[i] << "$" << movie_prices[i] << endl;
            }
            cout << endl;
            cout << "Do You Want To Change Your Genre(Y/N) :" << endl;
            cin >> genre_choice;
            genre_choice = toupper(genre_choice);
        } while (genre_choice == 'Y' && genre_choice != 'N');

        cout << endl;

        int movie_index;
        cout << "Which Movie You Wanna See of " << show_details.category << " GENRE (Enter Number): ";
        cin >> movie_index;

        while (cin.fail() || movie_index < 1 || movie_index > 5)
        {
            cin.clear();  // Clear the error state of the input stream
            cin.ignore(); // Ignore any remaining characters in the input buffer

            cout << "Please Choose a Valid Option. Try Again." << endl;
            cout << "Which Concert You Wanna See of " << movie_index << " GENRE (Enter Number): ";
            cin >> movie_index;
        }
        show_details.name = selected_movies[movie_index - 1];
        show_details.category = show_details.category;
        show_details.date = dates[movie_index - 1];
        show_details.time = times[movie_index - 1];
        show_details.price = movie_prices[movie_index - 1];
        cout << "Enter the Number of Tickets: ";
        cin >> show_details.tickets;
        show_details.total_price = show_details.tickets * movie_prices[movie_index - 1];
        show_details.loyalty_points = show_details.total_price * 0.1;
    }
    else if (choice == "B")
    {
        show_details.is_play = true;
        show_details.is_movie = false;
        show_details.is_concert = false;
        do
        {
            clearScreen();
            cout << "Cool! You Wanna See Plays." << endl;
            cout << endl;
            cout << "We Have these Genres:" << endl;
            cout << endl;
            cout << "1.COMEDY" << endl;
            cout << endl;
            cout << "2.TRAGEDY" << endl;
            cout << endl;
            cout << "3.ROMANTIC" << endl;
            cout << endl;
            cout << "4.MELODRAMA" << endl;
            cout << endl;
            cout << "5.MOTIVATIONAL" << endl;
            cout << endl;
            cout << "Which Genre Play you Wanna See? Enter Below: ";
            cin >> show_details.category;
            cout << endl;
            while (show_details.category != "1" && show_details.category != "2" && show_details.category != "3" && show_details.category != "4" && show_details.category != "5")
            {
                cout << "Please Select a Valid Option !!!!" << endl;
                cout << "Which Genre Movie you Wanna See? Enter Below: ";
                cin >> show_details.category;
                cout << endl;
            }

            if (show_details.category == "1")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_plays[i] = comedy_play[i];
                }
                show_details.category = "Comedy";
            }
            else if (show_details.category == "2")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_plays[i] = tragedy_play[i];
                }
                show_details.category = "Tragedy";
            }
            else if (show_details.category == "3")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_plays[i] = romantic_play[i];
                }
                show_details.category = "Romantic";
            }
            else if (show_details.category == "4")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_plays[i] = melodrama_play[i];
                }
                show_details.category = "Melodarama";
            }
            else if (show_details.category == "5")
            {
                for (int i = 0; i < n; i++)
                {
                    selected_plays[i] = motivational_play[i];
                }
                show_details.category = "Motivational ";
            }
            else
            {
                cout << "This Genre Play is not available" << endl;
                return;
            }

            clearScreen();
            cout << left;
            cout << setw(5) << "No" << setw(30) << "PLAY" << setw(20) << "GENRE" << setw(15) << "DATE" << setw(20) << "TIMINGS" << setw(10) << "PRICE" << endl;
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < n; i++)
            {
                cout << setw(5) << (i + 1) << setw(30) << selected_plays[i] << setw(20) << show_details.category << setw(15) << play_dates[i] << setw(20) << play_times[i] << "$" << play_prices[i] << endl;
            }
            cout << endl;
            cout << "Do You Want To Change Your Genre(Y/N) :" << endl;
            cin >> genre_choice;
            genre_choice = toupper(genre_choice);
        } while (genre_choice == 'Y' && genre_choice != 'N');

        cout << endl;
        int play_index;
        cout << "Which Play You Wanna See of " << show_details.category << " GENRE (Enter Number): ";
        cin >> play_index;
        while (cin.fail() || play_index < 1 || play_index > 5)
        {
            cin.clear();  // Clear the error state of the input stream
            cin.ignore(); // Ignore any remaining characters in the input buffer
            cout << "Please Choose a Valid Option. Try Again." << endl;
            cout << "Which Concert You Wanna See of " << show_details.category << " GENRE (Enter Number): ";
            cin >> play_index;
        }

        if (play_index >= 1 && play_index <= n)
        {
            show_details.name = selected_plays[play_index - 1];
            show_details.category = show_details.category;
            show_details.date = play_dates[play_index - 1];
            show_details.time = play_times[play_index - 1];
            show_details.price = play_prices[play_index - 1];
            cout << "Enter the Number of Tickets: ";
            cin >> show_details.tickets;
            show_details.total_price = show_details.tickets * play_prices[play_index - 1];
            show_details.loyalty_points = show_details.total_price * 0.1;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
    else if (choice == "C")
    {
        clearScreen();
        cout << "Cool ! You Wanna See Concert " << endl;
        cout << endl;
        cout << "For this Week We Have All The Concerts By ALANWALKER (FAST REVERB)" << endl;
        cout << endl;
        show_details.category = "FAST";
        cout << left;
        cout << setw(5) << "No" << setw(30) << "Concert" << setw(20) << "GENRE" << setw(15) << "DATE" << setw(20) << "TIMINGS" << setw(10) << "PRICE" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        for (int i = 0; i < n; ++i)
        {
            cout << setw(5) << (i + 1) << setw(30) << concert[i] << setw(20) << show_details.category << setw(15) << concert_dates[i] << setw(20) << concert_times[i] << "$" << concert_prices[i] << endl;
        }
        cout << endl;
        int concert_index;
        int total_price;
        cout << "Which Concert You Wanna See of " << show_details.category << " GENRE (Enter Number): ";
        cin >> concert_index;
        while (cin.fail() || concert_index < 1 || concert_index > 5)
        {
            cin.clear();  // Clear the error state of the input stream
            cin.ignore(); // Ignore any remaining characters in the input buffer

            cout << "Please Choose a Valid Option. Try Again." << endl;
            cout << "Which Concert You Wanna See of " << show_details.category << " GENRE (Enter Number): ";
            cin >> concert_index;
        }

        if (concert_index >= 1 && concert_index <= n)
        {
            show_details.name = concert[concert_index - 1];
            show_details.category = show_details.category;
            show_details.date = concert_dates[concert_index - 1];
            show_details.time = concert_times[concert_index - 1];
            show_details.price = concert_prices[concert_index - 1];
            cout << "Enter the Number of Tickets: ";
            cin >> show_details.tickets;
            show_details.total_price = show_details.tickets * concert_prices[concert_index - 1];
            show_details.loyalty_points = show_details.total_price * 0.1;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }
}
void purchase_snacks(show_details &show_details)
{
    clearScreen();
    const int num_items = 5;
    string items[num_items] = {"Popcorn", "Soda", "BubbleGum", "Juice", "Ice Cream"};
    int prices[num_items] = {5, 3, 2, 4, 3};
    int quantities[num_items] = {0};
    char choice;
    cout << "=-=-=-=-=-=-=-=-=SNACKS HERE=-=-=-=-=-=-=-=-=-=:" << endl;
    for (int i = 0; i < num_items; i++)
    {
        cout << i + 1 << ". " << items[i] << " - $" << prices[i] << endl;
    }
    cout << "Would you like to purchase any snacks? (Y/N): ";
    cin >> choice;
    choice = toupper(choice);

    while (choice == 'Y')
    {
        int item_choice;
        int quantity;
        do
        {
            cout << "Enter the item number: ";
            cin >> item_choice;
            if (item_choice != 1 && item_choice != 2 && item_choice != 3 && item_choice != 4 && item_choice != 5)
            {
                cout << "Invalid Choice . Try Again" << endl;
            }

        } while (item_choice != 1 && item_choice != 2 && item_choice != 3 && item_choice != 4 && item_choice != 5);
        cout << "Enter the quantity: ";
        cin >> quantity;
        quantities[item_choice - 1] += quantity;
        cout << "Would you like to purchase more snacks? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);
    }
    double snack_total = 0.0;
    cout << "Your Snack Purchases:" << endl;
    for (int i = 0; i < num_items; i++)
    {
        if (quantities[i] > 0)
        {
            snack_total += prices[i] * quantities[i];
        }
    }
    double gst = snack_total * 0.07;
    double total = snack_total + gst;
    cout << "Total (including 7% GST): $" << total << endl;
    show_details.snack_price += total;
    show_details.total_price += snack_total;
    show_details.loyalty_points += total * 0.1;
}

void recipt(show_details &show_details)
{
    clearScreen();
    cout << "------------------------------------------------------------" << endl;
    cout << "     YOUR TICKETS HAVE BEEN BOOKED " << person_name << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Your Selected show_details are:" << endl;
    cout << "------------------------------" << endl;
    cout << "Name: " << show_details.name << endl;
    cout << "Catogery: " << show_details.category << endl;
    cout << "Date: " << show_details.date << endl;
    cout << "Time: " << show_details.time << endl;
    cout << "Price: $" << fixed << setprecision(2) << show_details.price << endl;
    cout << "Number of Tickets: " << show_details.tickets << endl;
    cout << "Number of Premium Seats Addition of $5: " << show_details.premium_count << endl;
    cout << "Snacks Price Including 7% GST: $" << fixed << setprecision(2) << show_details.snack_price << endl;
    cout << "Your Total Price is: $" << fixed << setprecision(2) << show_details.total_price << endl;
    cout << "Loyalty Points Earned: $" << fixed << setprecision(2) << show_details.loyalty_points << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << endl;
}
//***********************************************************************************************
int main()
{
    char while_choice;
    int menu_option;
    show_details show_details;
    char continuation;
    string feedback;
    bool continue_program;
    // info();
    clearScreen();
    display();
    choices();
    choice_menu(show_details);
    if (show_details.is_movie)
    {
        clearScreen();
        cout << "You Have Selected a Movie." << endl;
        cout << endl;
        initialize_seats(movie_seats);
        book_seats(movie_seats, show_details);
    }
    else if (show_details.is_play)
    {
        clearScreen();
        cout << "You Have Selected a Play." << endl;
        initialize_seats(play_seats);
        book_seats(play_seats, show_details);
    }
    else
    {
        clearScreen();
        cout << "You Have Selected a Concert " << endl;
        initialize_seats(concert_seats);
        book_seats(concert_seats, show_details);
    }
    purchase_snacks(show_details);
    do

    {
        clearScreen();
        cout << endl;
        cout << "=-=--==-=-=-=-=-==MENU-=--=-=-=-=-=-=-=-=" << endl;
        cout << endl;
        cout << "1.Wanna See Your Reserved Seats" << endl;
        cout << endl;
        cout << "2.Change Your Reserved Seats" << endl;
        cout << endl;
        cout << "3.Get Recipt" << endl;
        cout << endl;
        cout << "4.Exit" << endl;
        cout << endl;

        cout << "Choose an Option ." << endl;
        cin >> menu_option;
        cin.ignore();
        switch (menu_option)
        {
        case 1:
            clearScreen();
            continue_program = true;
            if (show_details.is_movie)
            {
                display_seats(movie_seats);
            }
            else if (show_details.is_play)
            {
                display_seats(play_seats);
            }
            else
            {
                display_seats(concert_seats);
            }

            break;
        case 2:
            clearScreen();
            continue_program = true;
            if (show_details.is_movie)
            {
                initialize_seats(movie_seats);
                book_seats(movie_seats, show_details);
                break;
            }
            else if (show_details.is_play)
            {
                initialize_seats(play_seats);
                book_seats(play_seats, show_details);
                break;
            }
            else
            {
                initialize_seats(concert_seats);
                book_seats(concert_seats, show_details);
                break;
            }

        case 3:
            continue_program = true;
            recipt(show_details);
            cout << "Want To Continue The Program Again (Y/N)" << endl;
            cin >> continuation;
            continuation = toupper(continuation);
            if (continuation == 'Y')
            {

                show_details.total_price = 0.0;
                show_details.snack_price = 0.0;
                show_details.premium_count = 0;
                show_details.loyalty_points = 0;

                clearScreen();
                display();
                choices();
                choice_menu(show_details);
                if (show_details.is_movie)
                {
                    cout << "You Have Selected a Movie." << endl;
                    book_seats(movie_seats, show_details);
                    initialize_seats(play_seats);
                    initialize_seats(concert_seats);
                }
                else if (show_details.is_play)
                {
                    clearScreen();
                    cout << "You Have Selected a Play." << endl;
                    book_seats(play_seats, show_details);
                    initialize_seats(movie_seats);
                    initialize_seats(concert_seats);
                }
                else
                {
                    clearScreen();
                    cout << "You Have Selected a Concert." << endl;
                    book_seats(concert_seats, show_details);
                    initialize_seats(movie_seats);
                    initialize_seats(play_seats);
                }
                purchase_snacks(show_details);
                break;
            }
            else
            {
                break;
            }

        case 4:
            continue_program = false;
            clearScreen();
            cout << "Please Entre Your Feedback What We Do To Make Our System Better in 1 to 2 Lines : ";
            getline(cin, feedback);
            break;
        default:
            cout << "Entre Valid Option.Try Again" << endl;
            break;
        }
        if (continue_program && menu_option != 4)
        {
            cout << "Press Y to continue: ";
            cin >> while_choice;
            while_choice = toupper(while_choice);
            if (while_choice != 'Y')
            {
                continue_program = false;
            }
        }

    } while (continue_program);
    clearScreen();
    cout << endl;
    cout << "Your FeedBack Has Taken." << endl;
    cout << endl;
    cout << " ThankYOU " << person_name << " For Choosing Us !!!!! " << endl;
    return 0;
}