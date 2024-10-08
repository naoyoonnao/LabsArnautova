class Book: 
    def __init__(self, title: str, author: str, year: int, genre: str):
        self.title = title 
        self.author = author 
        self.year = year 
        self.genre = genre 
    
    def show_info(self):
        print(f"Name: {self.title}\nAuthor: {self.author}\nYear: {self.year}\nGenre: {self.genre}")

    def __str__(self):
        return f"'{self.title}' by {self.author}, {self.year} ({self.genre})"


class Library: 
    def __init__(self):
        self.books = []

    def add_book(self, book: Book):
        self.books.append(book)
        print(f"The book '{book.title}' was added to the library.")

    def remove_book(self, title: str):
        for book in self.books:
            if book.title == title:
                self.books.remove(book)
                print(f"The book '{book.title}' was deleted from the library.")
                return 
        print(f"The book '{title}' was not found.")
    
    def search_by_author(self, author: str):
        results = [book for book in self.books if book.author == author]
        if results:
            print(f"Books by author '{author}':")
            for book in results:
                print(book)
        else:
            print(f"No books by '{author}' were found.")
    
    def search_by_genre(self, genre: str):
        results = [book for book in self.books if book.genre == genre]
        if results: 
            print(f"Books in the genre '{genre}':")
            for book in results:
                print(book)
        else:
            print(f"No books in the genre '{genre}' were found.")

    def sorted_by_year(self):
        self.books.sort(key=lambda book: book.year)
        print("Books sorted by year:")
        for book in self.books:
            print(book)

    def display_books(self):
        if self.books:
            print("List of books in the library:")
            for book in self.books:
                print(book)
        else:
            print("The library is empty!")


library = Library()

library.add_book(Book("Being and Time", "Martin Heidegger", 1927, "Philosophy"))
library.add_book(Book("Beyond Good and Evil", "Friedrich Nietzsche", 1886, "Philosophy"))
library.add_book(Book("The Republic", "Plato", -375, "Philosophy"))

library.display_books()
library.search_by_author("Friedrich Nietzsche")
library.search_by_genre("Philosophy")
library.remove_book("Being and Time") 
library.display_books()
library.sorted_by_year()
