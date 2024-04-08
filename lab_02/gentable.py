import random
def main():
    authors = [
    "Tolstoy", "Dostoevsky", "Chekhov", "Gogol", "Pushkin", "Hemingway", "Orwell", 
    "Fitzgerald", "Austen", "Dickens", "Hugo", "Shakespeare", "Woolf", "Twain", 
    "Camus", "Murakami", "Saramago", "Garcia Marquez", "Nabokov", "Proust", "Dumas", 
    "Steinbeck", "Wilde", "Tolkien", "Kafka", "Verne", "Cervantes", "Melville", 
    "Dante", "Plato", "Aristotle", "Homer", "Balzac", "Goethe", "Kundera", "Voltaire", 
    "Hesse", "Mann", "Joyce", "Conrad", "Swift", "Eliot", "Wells", "London", "Austen", 
    "Bronte", "Dumas", "Stendhal", "Shelley", "Poe", "Maupassant", "Whitman", "Woolf", 
    "Wilde", "Turgenev", "Gaiman", "Gutierrez", "Amir", "Anders", "Barnes", "Barr", 
    "Cassidy", "Choi", "Cisneros", "Cooper", "Cunningham", "Daniel", "Davidson", 
    "Dixon", "Dolan", "Drake", "Evans", "Flores", "Garza", "Gutierrez", "Hall", "Hawkins", 
    "Hayes", "Hernandez", "Herrera", "Holmes", "Hudson", "Hunt", "Jackson", "Jefferson", 
    "Johnson", "Jones", "Kaur", "Kim", "Larson", "Lawrence", "Lee", "Levine", "Lopez", 
    "Manning", "Martinez", "Mason", "May", "McCarthy", "McGee", "Miller", "Morales", 
    "Morgan", "Murphy", "Myers", "Neal", "Nelson", "Nguyen", "Norton", "O'Connor", 
    "Oliver", "Owens", "Parker", "Patel", "Perez", "Perry", "Peterson", "Phillips", 
    "Powell", "Ramirez", "Reed", "Reyes", "Reynolds", "Rice", "Richardson", "Rivera", 
    "Roberts", "Robinson", "Rodriguez", "Rogers", "Romero", "Ross", "Russell", "Sanchez", 
    "Sanders", "Schmidt", "Scott", "Sharp", "Simon", "Smith", "Snyder", "Spencer", 
    "Stewart", "Sullivan", "Taylor", "Thomas", "Thompson", "Torres", "Turner", "Walker", 
    "Ward", "Watson", "Webb", "White", "Williams", "Wilson", "Wood", "Wright", "Young"]
    
    title = [
    "1984", "A Christmas Carol", "A Farewell to Arms", "A Game of Thrones", "A Midsummer Night's Dream", "A Passage to India", "A Portrait of the Artist as a Young Man", "A Tale of Two Cities", "A Thousand Splendid Suns", "Adventures of Huckleberry Finn", "Alice's Adventures in Wonderland", "All Quiet on the Western Front",
    "American Gods", "Animal Farm", "Anna Karenina", "Around the World in Eighty Days", "Brave New World", "Breakfast at Tiffany's", "Candide", "Catch-22", "Crime and Punishment", "David Copperfield", "Dune", "Emma", "Fahrenheit 451", "Frankenstein",
    "Gone with the Wind", "Great Expectations", "Hamlet", "Potter and the Chamber of Secrets", "Potter and the Deathly Hallows", "Potter and the Goblet of Fire", "Potter and the Half-Blood Prince", "Potter and the Order of the Phoenix", "Potter and the Philosopher's Stone", "Potter and the Prisoner of AzkabanVintage Classics", "Heart of Darkness", "Jane Eyre", "Les Miserables", "Little Women", "Lolita", "Lord of the Flies", "Mansfield Park", "Moby-Dick",
    "Mrs. Dalloway", "Nineteen Eighty-Four", "Northanger Abbey", "Of Mice and Men", "Oliver Twist", "One Hundred Years of Solitude", "Outlander", "Pride and Prejudice", "Romeo and Juliet", "Sense and Sensibility", "Slaughterhouse-Five", "Snow Crash", "The Adventures of Sherlock Holmes", "The Alchemist",
    "The Call of the Wild", "The Catcher in the Rye", "The Chronicles of Narnia", "The Color Purple", "The Count of Monte Cristo", "The Da Vinci Code", "The Diary of a Young Girl", "The Divine Comedy", "The Fault in Our Stars", "The Fellowship of the Ring", "The Giver", "The Godfather", "The Golden Compass",
    "The Grapes of Wrath", "The Great Gatsby", "The Handmaid's Tale", "The Hobbit", "The Hunger Games", "The Jungle Book", "The Kite Runner", "The Little Prince", "The Lord of the Rings", "The Metamorphosis", "The Odyssey", "The Old Man and the Sea", "The Picture of Dorian Gray", "The Princess Bride",
    "The Scarlet Letter", "The Secret Garden", "The Shining", "The Silmarillion", "The Sound and the Fury", "The Sun Also Rises", "The Tale of Peter Rabbit", "The Tell-Tale Heart", "The Thorn Birds", "The Time Machine", "The Adventures of Tom Sawyer", "The Trial", "The Turn of the Screw",
    "The War of the Worlds", "The Wind in the Willows", "The Wonderful Wizard of Oz", "To Kill a Mockingbird", "Treasure Island", "Ulysses", "War and Peace", "Where the Wild Things Are", "Wuthering Heights", "Alice in Wonderland", "To the Lighthouse", "The Iliad", "The Odyssey",
    "Sense and Sensibility", "The Time Traveler's Wife", "The Old Man and the Sea", "The Great Gatsby", "Oliver Twist", "The Picture of Dorian Gray", "The Adventures of Huckleberry Finn", "Moby Dick", "The Grapes of Wrath",
    "1984", "Brave New World", "Pride and Prejudice", "Catch-22", "One Hundred Years of Solitude", "The Catcher in the Rye", "The Lord of the Rings", "Potter and the Sorcerer's Stone", "Twilight", "The Hunger Games",
    "Fifty Shades of Grey", "Jane Eyre", "Wuthering Heights", "Gone with the Wind", "To Kill a Mockingbird", "The Hobbit", "The Chronicles of Narnia", "Animal Farm", "The Little Prince", "The Fault in Our Stars",
    "The Alchemist", "Potter and the Chamber of Secrets", "Potter and the Prisoner of AzkabanVintage Classics", "Potter and the Goblet of Fire", "Potter and the Order of the Phoenix", "Potter and the Half-Blood Prince", "Potter and the Deathly Hallows", "The Da Vinci Code", "Angels and Demons",
    "The Girl with the Dragon Tattoo", "The Girl Who Played with Fire", "The Girl Who Kicked the Hornet's Nest", "The Adventures of Sherlock Holmes", "Memoirs of a Geisha", "The Shining", "It", "Misery", "Carrie",
    "Cujo", "The Outsiders", "The Giver", "Ender's Game", "1984", "Animal Farm", "Brave New World", "Nineteen Eighty-Four", "The Handmaid's Tale", "Fahrenheit 451", "A Clockwork Orange", "Dune", "The Martian Chronicles",
    "The War of the Worlds", "I, Robot", "Snow Crash", "Neuromancer", "Do Androids Dream of Electric Sheep?", "The Left Hand of Darkness", "Gateway", "Foundation", "Ender's Game", "Hyperion", "A Canticle for Leibowitz",
    "Starship Troopers", "Ringworld", "The Mote in God's Eye", "2001: A Space Odyssey", "The Forever War", "Doomsday Book", "Flatland", "The Stand", "The Andromeda Strain", "Jurassic Park", "Timeline", "Prey", "Next",
    "The Lost World", "Congratualtions", "Revolutionary Road", "The Secret Life of Bees", "Another Roadside Attraction", "Peyton Place", "The Agony and the Ecstasy", "The Year of Living Dangerously", "A Mango-Shaped Space",
    "Escape from Mr. Lemoncello's Library", "The Graveyard Book", "The Westing Game", "The Miraculous Journey of Edward Tulane", "Bud, Not Buddy", "Ella Enchanted", "The Invention of Hugo Cabret", "Walk Two Moons",
    "Bridge to Terabithia", "Chains", "The One and Only Ivan", "Tuck Everlasting", "The Tale of Despereaux", "The View from Saturday", "The Egypt Game", "Shiloh", "From the Mixed-Up Files of Mrs. Basil E. Frankweiler",
    "Holes", "The Courage of Sarah Noble", "The Cricket in Times Square", "A Wrinkle in Time", "Where the Red Fern Grows", "Hatchet", "Number the Stars", "Roll of Thunder, Hear My Cry", "Charlotte's Web", "Coraline",
    "The Lightning Thief", "The Twig", "The BFG", "Matilda", "James and the Giant Peach", "The Secret Garden", "Black Beauty", "To Sir, With Love", "Bless Me, Ultima", "Potter and the Philosopher's Stone",
    "Potter and the Half-Blood Prince", "Potter and the Deathly Hallows", "Potter and the Chamber of Secrets", "Potter and the Prisoner of AzkabanVintage Classics", "Potter and the Goblet of Fire", "Potter and the Order of the Phoenix", "Alice's Adventures in Wonderland", "Through the Looking-Glass",
    "The Wonderful Wizard of Oz", "Around the World in Eighty Days", "The Adventures of Tom Sawyer", "The Adventures of Huckleberry Finn", "Treasure Island", "Kim", "White Fang", "The Call of the Wild", "Moby-Dick",
    "The Count of Monte Cristo", "The Three Musketeers", "Twenty Thousand Leagues Under the Sea", "Journey to the Center of the Earth", "David Copperfield", "Great Expectations", "Oliver Twist", "A Tale of Two Cities",
    "A Christmas Carol", "The Picture of Dorian Gray", "Dracula", "Frankenstein", "The Strange Case of Dr. Jekyll and Mr. Hyde", "Jane Eyre", "Wuthering Heights", "Pride and Prejudice", "Sense and Sensibility", "Emma",
    "Mansfield Park", "Northanger Abbey", "Persuasion", "The Scarlet Letter", "Little Women", "Anne of Green Gables", "Jane Austen", "Charlotte Bronte", "Emily Bronte", "Louisa May Alcott", "L. Frank Baum", "Mark Twain", "Jules Verne"]
    
    publish = [
    "Penguin Random House", "Hachette Book Group", "Simon & Schuster", "HarperCollins", "Macmillan Publishers", "Wiley", "Scholastic Corporation", "Pearson Education", "Bloomsbury Publishing", "Oxford University Press", "Cambridge University Press", "Puffin Books", "Knopf Doubleday Publishing Group",
    "Penguin Classics", "Vintage Books", "Penguin Press", "Little, Brown and Company", "Abrams Books", "Chronicle Books", "Random House Children's Books", "Disney Publishing Worldwide", "Pan Macmillan", "Usborne Publishing", "Harlequin Enterprises", "Workman Publishing", "Gallery Books", "Hodder & Stoughton",
    "Houghton Mifflin Harcourt", "Scribner", "Faber and Faber", "Canongate Books", "Grove Atlantic", "Perseus Books", "Bloomsbury Children's Books", "Quirk Books", "Dutton Books", "Harper Perennial", "Sourcebooks", "Tor Books", "Picador", "HarperOne", "William Morrow", "Tor Teen", "Alfred A. Knopf", "Del Rey Books",
    "Ballantine Books", "University of Chicago Press", "Viking", "Harper Voyager", "Gollancz", "Scholastic Press", "Ecco Press", "Quercus", "Viking Press", "Dark Horse Comics", "Allen Lane", "St. Martin's Press", "Piatkus", "Pegasus Books", "Scholastic Corporation", "Zondervan", "Penguin Books", "Vintage Classics",
    "Thomas Nelson", "Avon Books", "Grand Central Publishing", "Hogarth Press", "HarperFestival", "Windmill Books", "Soho Press", "MacLehose Press", "HarperCollins Children's Books", "HarperTeen", "Canongate", "Headline Publishing Group", "Mira Books", "Fourth Estate", "Penguin Modern Classics", "Hogarth", "Mariner Books",
    "Roaring Brook Press", "Grove Press", "St. Martin's Griffin", "Penguin Essentials", "Norton Publishing", "Houghton Mifflin", "Grove Weidenfeld", "Simon Pulse", "Bloomsbury Academic", "St. James Press", "Faber & Faber", "Anchor Books", "Verso Books", "Liveright Publishing Corporation", "Melville House Publishing"]

    industry = [
    "Automotive", "Technology", "Retail", "Healthcare", "Finance", "Hospitality", "Education", "Entertainment", "Telecommunications", "Manufacturing", "Construction", "Aerospace", "Energy", "E-commerce", "Media", "Food and Beverage", "Transportation",
    "Fitness", "Insurance", "Real Estate", "Fashion", "Pharmaceutical", "Information Technology", "Travel and Tourism", "Logistics", "Consulting", "Biotechnology", "Sports", "Advertising", "Legal", "Telecom", "Music", "Gaming", "Insurance",
    "Renewable Energy", "Retail", "Healthcare", "Transportation", "Finance", "Hospitality", "Education", "Entertainment", "Telecommunications", "Manufacturing", "Construction", "Aerospace", "Energy", "E-commerce", "Media", "Food and Beverage",
    "Transportation", "Fitness", "Insurance", "Real Estate", "Fashion", "Pharmaceutical", "Information Technology", "Travel and Tourism", "Logistics", "Consulting", "Biotechnology", "Sports", "Advertising", "Legal", "Telecom", "Music", "Gaming",
    "Insurance", "Renewable Energy", "Retail", "Healthcare", "Finance", "Hospitality", "Education", "Entertainment", "Telecommunications", "Manufacturing", "Construction", "Aerospace", "Energy", "E-commerce", "Media", "Food and Beverage",
    "Transportation", "Fitness", "Insurance", "Real Estate", "Fashion", "Pharmaceutical", "Information Technology", "Travel and Tourism", "Logistics", "Consulting", "Biotechnology", "Sports", "Advertising", "Legal", "Telecom", "Music", "Gaming"]
    file = open('file_in.txt', 'w')
    for i in range(1000):
        file.write(random.choice(authors) + "\n")
        file.write(random.choice(title) + "\n")
        file.write(random.choice(publish) + "\n")
        file.write(str(random.randint(1, 1000)) + "\n")
        tpy = random.randint(1, 3)
        file.write(str(tpy) + "\n")
        if (tpy == 1):
            file.write(random.choice(industry) + "\n")
            file.write(str(random.randint(0, 1)) + "\n")
            file.write(str(random.randint(0, 1)) + "\n")
            file.write(str(random.randint(1500, 2023)) + "\n")
        elif (tpy == 2):
            file.write(str(random.randint(1, 3)) + "\n")
        else:
            file.write(str(random.randint(0, 18)) + "\n")
            file.write(str(random.randint(1, 2)) + "\n")
    file.close

if __name__ == "__main__":
    main()
