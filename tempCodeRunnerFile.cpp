 if (ShowDetails.is_movie)
                {
                    book_seats(movieSeats, ShowDetails);
                }
                else if (ShowDetails.is_play)
                {
                    clearScreen();
                    book_seats(playSeats, ShowDetails);
                }
                else
                {
                    clearScreen();
                    book_seats(concertSeats, ShowDetails);
                }
                clearScreen();