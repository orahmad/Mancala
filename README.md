# Mancala
Object Oriented Game

	The process of implementation began with the Board class. Inside the private section of the class, another class named hole was created. 
Inside hole, there were various public member functions such as being able to set the amount of beans that hole has. 
Additionally there was also a getter for the number of beans made as well. An enum was also made to decide if each hole was a regular 
South hole, North hole, South pot, or North pot. Outside of the hole class, a vector of pointers to holes were made. 
The vector was then made by creating as many holes were needed for both North and South holes and pots. 
The beginning of the vector was hole South #1, which was followed by hole #2 until the amount of holes were reached. 
Next the South pot was pushed back in the vector followed by a similar format for the North side. A problem that had to be solved
was that the last North hole needed to be inserted and it had to be in the opposite order to fit the way the spec outlined it. 
The vector was made instead of an array so I didn’t have to deal with dynamically allocated arrays, and could push_back each hole. 
Using multiple for loops and other loops, each function was relatively easy to implement except for the sow function. 
The problem I faced with the sow function was that when reaching the end of the vector, I had to restart it back at the front. 
This was done by simply resetting int i in the for loop. In addition, both a copy constructor and assignment operator
had to be created for use later on.   
  
  The next class I had to implement was the Player class. Alongside the parent class Player, I needed to create three additional
subclasses of Player which were known as BadPlayer, HumanPlayer, and SmartPlayer. SmartPlayer was the hardest to implement so I
didn’t work on it until the very end. For BadPlayer, I had to come up with a random legal move. At first, I tried using a random
number generator, but after a lot of struggles with it, I decided to come up with a new way of finding a random legal move. 
Instead, I created a for loop in which I looped through the respective side, starting at hole 1 and finding the first legal move. 
Essentially the hole closest to the north pot was selected. HumanPlayer was also a little challenging to create since I was having
struggles using Polymorphism and the keyword virtual.
  
  The last class I had to implement was the Game class. Some of the private data members that were needed was a Board,
two pointers to Players, one labeled as South, and one as North. Lastly a Side object was created in order to figure out
whose turn it was. The game class had mostly easy functions. Since the spec was a little open ended when it came to describing
how to implement the display. I essentially used the cout function with a couple of clever for loops to handle this. 
Two functions that were especially hard to implement were the move and play functions. The move function used sow really heavily, 
but it was hard to figure out when a turn ended. Moreover, I had to figure out when a Player landed in the Pot and needed another turn. 
Additionally, I had to figure out how and when the capture needed to take place. After dealing with these problems, 
I had to then deal with figuring how to get play to work. It was hard figuring out where exactly the display function had to be 
implemented. 
