# CS2250 Midterm

Created Date: April 6, 2026
Type: Assignment

# Github Information

- NOTE: Github repo was created to store programs and notes for all coding related classes moving forward, directions to get to the CPP folder and view all the programs for this assignment are in the [`README.md`](http://README.md)
- Github Link: https://github.com/shane-david/swe-knowledge-base

# Rogue Analysis

## Game loop

- Step 1: After creating a new save file or after dying in a run, the player completely restart. They create a new character and are brought back into the first level in the dungeon after the rooms and items within it have been randomly generated.
- Step 2: The player is spawned into an ASCII room with the following starting stats: 12 Hits, 16  Strength, 5 Armor, 0 Gold, Level 1. The rooms contain items, enemies, and doors within them, these are randomly generated.
- Step 3: Rogue is a turn-based game. After entering a new room the player can do several things with their turn:
    - Move: Move one tile in any direction (Up, down, left, right, diagonal).
    - Attack: Attacking is the same as moving but if the player moves on to a tile that a monster is at they will attempt to attack the monster.
    - Pick up an item: Picking up an item is the same as moving, if the player moves on to the same square that an item is at, they will pick it up and it will be added to their pack.
    - Use an item: The player can view their pack with `i` and change which item their are wielding with `w`. They can then use a variety of different key presses to use different items.
    - Drop an item: The player can drop an item by pressing `d` and selecting which item to drop.
    - Search: The player can search around them with `s` to reveal any hidden doors or traps.
    - Rest: The player can rest by pressing the space bar or period to allow their HP to regenerate, however this counts as a move and therefore they can still be attacked by enemies.
- Step 4: Within a room the player kills all enemies and collects all items before progressing.
    - Killing enemies: the player moves onto the same square as enemies trading back and forth between hits until they or the enemy are dead. Whether an attack hits or not and how much damage it does to the enemy is determined by RNG.
    - Picking up items: Items are denoted by several different ASCII characters the player must pick up these items, use them if needed, equip better items, and drop worse items to become strong enough to progress in the game.
- Step 5: Once the player has done everything they want to in the room they can exit the room through any of the breaks in the walls.
- Step 6: DEATH CONDITION: If the player’s Hits drop at or below 0 in any of the rooms they will die. They will not be respawned and have to completely restart at Step 1, even creating a new character.
- Step 7: LEVEL PROGRESSION: Fighting monsters gives the player experience points so that they can level up. This is integral to the game loop because monsters and rooms get harder as the player progresses so they must get stronger.
- Step 8: After the player goes through the door a new square will be reveled after every move showing the player where they can go. They can keep moving onto the newly revealed square until they enter a new room and repeat steps 3-7 in each room.
- Step 9: The player traverses rooms looking growing stronger looking for staircases. The player must keep descending until they reach level 26 and retrieve the Amulet of Yendor.
- Step 10: Once the player retrieves the amulet of Yendor they must then ascend back up the 26 levels and escape the dungeon.
- WIN CONDITION: Descending the dungeon retrieving the amulet, the ascending the dungeon and escaping with the amulet in the player’s inventory.

## Flowchart

- General Process
    
    ![image.png](image.png)
    
- Randomly generating dungeon
    
    ![image.png](image%201.png)
    
- Rendering map with ASCII
    
    ![image.png](image%202.png)
    

## Pseudocode

- Logic and Reasoning:
    - Since this game has so many unique items and entities abstraction would be very useful here
    - Items could be abstracted into a base Item class that defines a virtual `use` method
    - This method can then be overridden by each item so that the player can have an Inventory of `Item` objects and when they want to use an item they just select that item based off of index and the program can call `Item.Use()` to use it
    - Enemies can be abstracted in a different way. Since monsters really only differ from each other in stat changes they can all just be different instances of an `Enemy` class and then be built with different stats via the constructor. Building these monsters can then exist in a `MonsterFactory` class that has methods to create any monster with the constructor. Function pointers to each of these methods could exist in an array that can be randomly indexed to get a random monster.
    - It then contains a dungeon class that holds all of the logic for randomly generating a dungeon and moving things around. It uses a 2D array because the dungeon will be a fixed width and heigh and all that changes is what is in the array. The array stores cells which have an ID that dictate what they are and what exists within them. The array will just hold a null value if nothing is there.
- PseudoCode:
    
    ```cpp
    
    //---------------------------
    //Classes to use in Game Loop
    //---------------------------
    
    //Item ABSTRACT CLASS
    	//virtual void Use(Player player) = 0 
    	
    //Weapon, Armor, Potion, Scroll, Food ect inherit from Item and implent use 
    //for example:
    //Potion : public Item
    	//int healAmount 
    	//void use(Player player) override
    		//player.hp += healAmount 
    		
    //Inventory Class
    	//List<Item> inventory
    	//int size 
    	//AddItem(Item item)
    		//if inventory.size() < size
    			//inventory.add(Item)
    	//RemoveItem(int index)
    		//inventory.removeAt(index)
    		
    //GameEntity Class
    	//posX
    	//posY
    	//health 
    	//maxHealth
    	//position
    	//strength 
    	//isAlive()
    		//return hp > 0 
    	//virtual void Die()
    		//destroy *this 
    	//void Attack(GameEntity other)
    		//damage is rand() % strenght
    		//other.health -= damage
    	
    //Player Class inherits from GameEntity
    	//Inventory playerInventory
    	//int experiencePoints
    	//bool hasAmulet
    	
    	//void gainXp(int amount)
    		//experiencePoints += amount 
    		//if experiencePoints > 100
    			//levelUp()
    			
    	//void levelUp
    		//level++
    		//increase stats
    		
    	//void useItem(index)
    		//item = playerInventory.get(index)
    		//item.use()
    		//playerInventory.removeItem(index)
    		
    	//void dropItem(index)
    		//playerInventory.dropItem(index)
    		
    //Monster inherits from GameEntity
    	//string name 
    	//int xpValue 
    	//int dungeonLevel[]
    	//Item carriedItem
    
    	//int getRandomDirection()
    		//int dir = rand() % 8 
    		//return dir + 1 
    		
    //MonsterFactory Class
      //int monsters 
    	//Monster (*monsterCreaters[monsters]) [ARRAY OF FUNCTION POINTERS TO EACH CREATOR METHOD]
    	
    	//MonsterFactory()
    		//initialize monsterCreaters with all creator functions 
    	
    	//this class holds all the methods to create a specific monster, for example:
    	//Monster createGoblin()
    		//return Monster(10, 4, 5...) [STATS ARE PASSED IN TO CONSTRUCTOR] 
    		
    	//Monster getRandomMonster()
    		//return monsterCreateors[rand() % monsters] 
    	
    //Cell
    	//char type
    	//Monster* monster
    	//Item* item
    	//bool isVisible
    	
    //Dungeon
    	//int width, height
    	//Cell[][] grid
    	//List<Monster> monsters
    	//List<Item> items
    	//List<Door> doors
    	
    	//generate(int dungeon Level)
    	
    		//get random number of rooms
    		// for random number of rooms
    			//get random size
    			//get random location 
    			//while room is next to another room 
    			
    			//create room
    			//for each side of room 
    				//random chance for door
    				//ad door to door list
    		//connect all rooms with hall cells
    				
    		//for rows in widht
    			//for cols in height
    				//get random number 
    				//if random number is 0
    					//spawn an item
    					//add item to item list
    				//if random number is 
    					//spawn a monster accoring to dungeon level
    					//add monster to monster list 
    				//if random number is 3
    					//spawn a secret 
    					
    		//getMonsters
    			//return monsters
    			
    		//get doors
    			//return doors 
    				
    		
    //Renderer
    
    	//renderMap(Dunegon&)
    		//for row in dungeon
    			//for cell in dunveon
    				//if cell.isVisible 
    					//cout << cell.type
    		
    		
    //--------------------------
    //Controlling the Game loop
    //--------------------------
    
    //GAME class 
    //Player* pleyr
    //Dungeon* dungeon
    //int dungeonLevel = 1
    //Renderer* renderer
    //bool isRunning
    
    //Constructor 
    //Game()
    	//initalize objects
    	//dungeon.generate(dungeonLevel) 
    	
    //run()
    	//while isRunning
    		//renderer.renderMap(dungeon)
    		
    		//playerTurn()
    		
    		//renderer.renderMap(dungeon)
    		
    		//monsterTurn() 
    		
    		// if player is not alive
    			//gameover()
    			//break
    		
    		// if player is on starcase 
    			// goToNextLevel()
    	
    //playerTurn()
    	//get player input 
    	
    	//switch (playerInput)
    		//case 'i'
    			//openPack()
    		//case 'd'
    			//openDropMenu()
    		//case 's'
    			//search()
    		//case 'q' //NOTE DIFFERENT INPUTS FOR DIFFERENT ITEM USAGES
    			//usePotion()
    		//case movementKey
    			//handleMovement(int direction) 
    			
    //all opening methods just render a select screen over the map, the map will be rerendered at the top of the loop
    
    //handleMovement(int direction) 
    	
    	//switch direction 
    		//case 1
    			//move up 
    		//case 2
    			//move down
    		//case 3
    			//move left
    		//case 4
    			//move right
    		//case 5
    			//move up left
    		//case 6
    			//move up right
    		//case 7
    			//move down left
    		//case 8 
    			//move down right 
    		
    	//for monsters in dungeon.GetMonsters()
    		//if player.x && player.y == monster.x && monster.y
    			//palyer.attack(monster)
    
    	//foor doors in dungeon.getDoors()
    		//if player.x && player.y == door.x && door.y
    			//dungeon.reavelNextCell() 
    			
    //monsterTurn()
    	
    	//for monster in dungeon.getMonsters()
    		//int dx = player.x - monster.x
    		//int dy - player.y - monster.y
    		
    		//move monster with dx & dy 
    		
    		//if monster.x && monster.y == player.x && player.y
    			//monster.attack(player)
    			
    //gameOver()
    	//isRunning = false 
    	//report loss
    	//restart game
    	
    //goToNextLevel()
    	//if player.hasAmulet
    		//dungeonLevel--
    	//else 
    		//dungeonLevel++
    		
    	//if dungeonLevel == 1 && player.hasAmulet
    		//winGame() 
    	//else 
    		//dungeon.generate(dungeonLevel)
    			
    //winGame
    	//isRunning = false 
    	//report win
    	//restart game 
    	
    ```